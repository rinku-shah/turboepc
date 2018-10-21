/* -*- P4_16 -*- */
#include <core.p4>
#include <v1model.p4>
#include "include/headers.p4"
#include "include/parser.p4"
#include "include/checksums.p4"
#include "include/definitions.p4"
#define MAX_PORTS 255

/*************************************************************************
**************  I N G R E S S   P R O C E S S I N G   *******************
*************************************************************************/

control c_ingress(inout headers hdr,
                  inout metadata meta,
                  inout standard_metadata_t standard_metadata) {

    // We use these counters to count packets/bytes received/sent on each port.
    // For each counter we instantiate a number of cells equal to MAX_PORTS.
    counter(MAX_PORTS, CounterType.packets_and_bytes) tx_port_counter;
    counter(MAX_PORTS, CounterType.packets_and_bytes) rx_port_counter;

    // action ipv4_forward(macAddr_t dstAddr, egressSpec_t port) {
    action ipv4_forward(egressSpec_t port) {

        standard_metadata.egress_spec = port;
        //  commenting these after seeing mytunnel p4
        // hdr.ethernet.srcAddr = hdr.ethernet.dstAddr;
        // hdr.ethernet.dstAddr = dstAddr;
        // hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

    action send_to_cpu() {
        standard_metadata.egress_spec = CPU_PORT;
        // Packets sent to the controller needs to be prepended with the
        // packet-in header. By setting it valid we make sure it will be
        // deparsed on the wire (see c_deparser).
        hdr.packet_in.setValid();
        hdr.packet_in.ingress_port = standard_metadata.ingress_port;
    }

    action _drop() {
        mark_to_drop();
    }

    // Table counter used to count packets and bytes matched by each entry of
    // t_l2_fwd table.
    direct_counter(CounterType.packets_and_bytes) l3_fwd_counter;

    table t_l3_fwd {
        key = {
            // hdr.ipv4.dstAddr : lpm;
            hdr.data.epc_traffic_code : ternary;
            standard_metadata.ingress_port  : ternary;
            hdr.ethernet.dstAddr            : ternary;
            hdr.ethernet.srcAddr            : ternary;
            hdr.ethernet.etherType          : ternary;
        }
        actions = {
            ipv4_forward;
            send_to_cpu;
            _drop;
            NoAction;
        }
        size = 1024;
        default_action =  NoAction();
        counters = l3_fwd_counter;
    }


   // ***************** Uplink Tunnel(DGW->PGW) Setup *******************************
    action populate_ip_op_tun_s1_uplink(bit<32> op_tunnel_s1,bit<9> egress_port_s1){
        //vlan based forwarding
        // hdr.vlan.setValid();
        // standard_metadata.egress_spec = egress_port_s1;
        // hdr.vlan.vid = op_tunnel_s1;
        // hdr.vlan.vlan_type = hdr.ethernet.etherType;
        // hdr.ethernet.etherType = TYPE_VLAN;
        // hdr.ipv4.ttl = hdr.ipv4.ttl - 1;

        // gtp based forwarding
        hdr.gtpu_ipv4.setValid();
        hdr.gtpu_ipv4.version = IP_VERSION_4;
        hdr.gtpu_ipv4.ihl = IPV4_MIN_IHL;
        hdr.gtpu_ipv4.diffserv = 0;
        hdr.gtpu_ipv4.totalLen = hdr.ipv4.totalLen
                + (IPV4_HDR_SIZE + UDP_HDR_SIZE + GTP_HDR_SIZE);
        hdr.gtpu_ipv4.identification = 0; 
        hdr.gtpu_ipv4.flags = 0;
        hdr.gtpu_ipv4.fragOffset = 0;
        hdr.gtpu_ipv4.ttl = hdr.ipv4.ttl-1;
        hdr.gtpu_ipv4.protocol = PROTO_UDP;
        hdr.gtpu_ipv4.srcAddr = s1u_dgw_addr;
        hdr.gtpu_ipv4.dstAddr = s1u_sgw_addr;
        hdr.gtpu_ipv4.hdrChecksum = 0; // Updated later

        hdr.gtpu_udp.setValid();
        hdr.gtpu_udp.srcPort = UDP_PORT_GTPU;
        hdr.gtpu_udp.srcPort = hdr.tcp.src_port;
        hdr.gtpu_udp.dstPort = UDP_PORT_GTPU;
        hdr.gtpu_udp.length_= hdr.ipv4.totalLen
                + (UDP_HDR_SIZE + GTP_HDR_SIZE);
        hdr.gtpu_udp.checksum = 0; // Updated later
        
        hdr.gtpu.setValid();
        hdr.gtpu.version = GTPU_VERSION;
        hdr.gtpu.pt = GTP_PROTOCOL_TYPE_GTP;
        hdr.gtpu.x = 0;
        hdr.gtpu.ex_flag = 0;
        hdr.gtpu.seq_flag = 0;
        hdr.gtpu.npdu_flag = 0;
        hdr.gtpu.msgtype = GTP_GPDU;
        hdr.gtpu.msglen = hdr.ipv4.totalLen;
        hdr.gtpu.teid = op_tunnel_s1;

        standard_metadata.egress_spec = egress_port_s1;
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

    action dummyaction(bit<9> egress_port){
         standard_metadata.egress_spec = egress_port;
    }
    table dummy{
        key={
            hdr.auth_step_one.imsi : exact;
        }
        actions={
            dummyaction;
        }
        size=1024;
    }

   table ip_op_tun_s1_uplink{
       key={
           // need to match on dstaddr to form ingress tunnel
           hdr.ipv4.srcAddr : exact;
           hdr.ipv4.dstAddr : exact;
       }
       actions={
           populate_ip_op_tun_s1_uplink;
           NoAction;
       }
       size = 4096;
       default_action = NoAction();
   }

    action populate_ip_op_tun_s2_uplink(bit<32> op_tunnel_s2,bit<9> egress_port_s2){
        standard_metadata.egress_spec = egress_port_s2;
        // hdr.vlan.vid = op_tunnel_s2;

        // mapping between parser and deparser headers
        hdr.gtpu_ipv4 = hdr.ipv4;
        hdr.gtpu_udp = hdr.udp;
        hdr.ipv4 = hdr.inner_ipv4;
        hdr.tcp = hdr.inner_tcp;

        // hdr.udp = hdr.inner_udp;
        hdr.udp.setInvalid();


        // no need to set udp header if inner_udp header is not valid 
        // if (hdr.inner_udp.isValid()) {
        //     hdr.udp = hdr.inner_udp;
        // } else {
        //     hdr.udp.setInvalid();
        // }

        // not implementing this as we are not matching on any of ip based fields we are matching on gtp tunnel id
        // hdr.gtpu_ipv4.srcAddr =s1u_sgw_addr;
        // hdr.gtpu_ipv4.dstAddr = s1u_pgw_addr;
        hdr.gtpu.teid = op_tunnel_s2;
        hdr.gtpu_ipv4.ttl = hdr.gtpu_ipv4.ttl - 1;
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

   table ip_op_tun_s2_uplink{
       key={
            // match on the VLAN ID field vid and set the vid to the outgoing tunnel and set egress port
            //    hdr.vlan.vid : exact;
            
            // match on gtp teid field and set the corressponding egress port
            hdr.gtpu.teid : exact;
       }
       actions={
           populate_ip_op_tun_s2_uplink;
           NoAction;
       }
       size = 1024;
       default_action = NoAction();
   }

    action populate_tun_egress_s3_uplink(bit<9> egress_port_s3){
        standard_metadata.egress_spec = egress_port_s3;
        // hdr.ethernet.etherType = hdr.vlan.vlan_type;
        // hdr.vlan.setInvalid();

        hdr.gtpu_ipv4 = hdr.ipv4;
        hdr.gtpu_udp = hdr.udp;
        hdr.ipv4 = hdr.inner_ipv4;
        hdr.tcp = hdr.inner_tcp;

        // hdr.udp = hdr.inner_udp;
        hdr.udp.setInvalid();

        // Downlink trafiic 
         if(hdr.inner_ipv4.srcAddr==sink_ip){
        // else if(standard_metadata.ingress_port==2){
            if(hdr.tcp.src_port == 13001){
                hdr.ethernet.dstAddr = ran1;
            }
            else if(hdr.tcp.src_port == 23001){
                hdr.ethernet.dstAddr = ran2;
            }
            else if(hdr.tcp.src_port == 33001){
                hdr.ethernet.dstAddr = ran3;
            }
            else if(hdr.tcp.src_port == 43001){
                hdr.ethernet.dstAddr = ran4;
            }
            else if(hdr.tcp.src_port == 44001){
                hdr.ethernet.dstAddr = ran5;
            }
            else if(hdr.tcp.src_port == 45001){
                hdr.ethernet.dstAddr = ran6;
            }

        }
        // we need to set the destination src MAC address otherwise the packet will not be accepted by the next hop interface as it is host
        // on UL we have 4 chains incoming at PGW on ports 1,2,3,4 
        else if(standard_metadata.ingress_port==1 || standard_metadata.ingress_port==2 || standard_metadata.ingress_port==3 || standard_metadata.ingress_port==4  || standard_metadata.ingress_port==5  || standard_metadata.ingress_port==6){
            // this check is not required as all pkts have to be sent to sink
            if(hdr.ethernet.srcAddr==ran1 || hdr.ethernet.srcAddr==ran2 || hdr.ethernet.srcAddr==ran3 || hdr.ethernet.srcAddr==ran4 || hdr.ethernet.srcAddr==ran5 || hdr.ethernet.srcAddr==ran6 ){
                hdr.ethernet.dstAddr = sink;
            }
        }

     

        // no need to set udp header if inner_udp header is not valid 
        // if (hdr.inner_udp.isValid()) {
        //     hdr.udp = hdr.inner_udp;
        // } else {
        //     hdr.udp.setInvalid();
        // }

        hdr.gtpu.setInvalid();
        hdr.gtpu_ipv4.setInvalid();
        hdr.gtpu_udp.setInvalid();

        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

    // tunnel to egress port map for s3
    table tun_egress_s3_uplink{
        key={
            // match on vlan ID field and set the corressponding egress port
            //  hdr.vlan.vid : exact;

            // match on gtp teid field and set the corressponding egress port
            hdr.gtpu.teid : exact;

        }
        actions={
            populate_tun_egress_s3_uplink;
            NoAction;
        }
        size = 1024;
        default_action = NoAction();
    }

   // ***************** Downlink Tunnel(PGW->DGW) Setup *******************************

//    action populate_ip_op_tun_s3_downlink(bit<12> op_tunnel_s3,bit<9> egress_port_s3){
//         hdr.vlan.setValid();
//         standard_metadata.egress_spec = egress_port_s3;
//         hdr.vlan.vid = op_tunnel_s3;
//         hdr.vlan.vlan_type = hdr.ethernet.etherType;
//         hdr.ethernet.etherType = TYPE_VLAN;
//         hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
//    }
//    table ip_op_tun_s3_downlink{
//       key={
//           // match on the VLAN ID field vid and set the vid to the outgoing tunnel and set egress port
//             hdr.ipv4.dstAddr:lpm;
//       }
//       actions={
//           populate_ip_op_tun_s3_downlink;
//           NoAction;
//       }
//       size = 1024;
//       default_action = NoAction();
//   }

   action populate_ip_op_tun_s2_downlink(bit<32> op_tunnel_s2,bit<9> egress_port_s2){
       standard_metadata.egress_spec = egress_port_s2;
    //    hdr.vlan.vid = op_tunnel_s2;
       
        // mapping between parser and deparser headers
        hdr.gtpu_ipv4 = hdr.ipv4;
        hdr.gtpu_udp = hdr.udp;
        hdr.ipv4 = hdr.inner_ipv4;
        hdr.tcp = hdr.inner_tcp;

        // hdr.udp = hdr.inner_udp;
        hdr.udp.setInvalid();


        // hdr.gtpu_ipv4.srcAddr =s1u_sgw_addr;
        // hdr.gtpu_ipv4.dstAddr = s1u_pgw_addr;
        hdr.gtpu.teid = op_tunnel_s2;
        hdr.gtpu_ipv4.ttl = hdr.gtpu_ipv4.ttl - 1;
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;

   }
  table ip_op_tun_s2_downlink{
      key={
            // match on the VLAN ID field vid and set the vid to the outgoing tunnel and set egress port
            //   hdr.vlan.vid : exact;
            // match on gtp teid field and set the corressponding egress port
            hdr.gtpu.teid : exact;
      }
      actions={
          populate_ip_op_tun_s2_downlink;
          NoAction;
      }
      size = 1024;
      default_action = NoAction();
  }

//    action populate_tun_egress_s1_downlink(bit<9> egress_port_s1){
//        standard_metadata.egress_spec = egress_port_s1;
//        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
//        hdr.ethernet.etherType = hdr.vlan.vlan_type;
//        hdr.vlan.setInvalid();
//    }
//    // tunnel to egress port map for s1 for Downlink
//    table tun_egress_s1_downlink{
//        key={
//            // match on vlan ID field and set the corressponding egress port
//             hdr.vlan.vid : exact;
//        }
//        actions={
//            populate_tun_egress_s1_downlink;
//            NoAction;
//        }
//        size = 1024;
//        default_action = NoAction();
//    }

    apply {
        if (standard_metadata.ingress_port == CPU_PORT) {
            // Packet received from CPU_PORT, this is a packet-out sent by the
            // controller. Skip table processing, set the egress port as
            // requested by the controller (packet_out header) and remove the
            // packet_out header.
            standard_metadata.egress_spec = hdr.packet_out.egress_port;
            hdr.packet_out.setInvalid();
        } else {
            // Packet received from data plane port.
            // Applies table t_l2_fwd to the packet.
            if (t_l3_fwd.apply().hit) {
                // Packet hit an entry in t_l2_fwd table. A forwarding action
                // has already been taken. No need to apply other tables, exit
                // this control block.
                return;
            }
            
          // if data packet then
          //  1. set the outgoing tunnel ID for incoming tunnel ID
          //  2. Set the egress port after looking up incoming tunnel ID
          //  Note : tunnel ID is gtp vid
          if (hdr.ipv4.isValid() && !hdr.gtpu.isValid()) {
            //    if(hdr.ipv4.ttl == 64){
                // Process only non-tunneled IPv4 packets.
                    ip_op_tun_s1_uplink.apply();
                    // dummy.apply();
                    return;
            // }
          }

            // if (hdr.vlan.isValid()) {
            if (hdr.gtpu.isValid()) {
                // Process all tunneled packets.
                if(hdr.ipv4.ttl == 63){
                    // if ingress port is 1 on SGW it means it is a UPLINK tunnel packet (RAN -> Sink)
                    if(standard_metadata.ingress_port==1){
                            ip_op_tun_s2_uplink.apply();
                            return;
                    }
                    // if the ingress port is 2 then it a DOWNLINK tunnel packet (Sink -> RAN)
                    if(standard_metadata.ingress_port==2){
                            ip_op_tun_s2_downlink.apply();
                            return;
                    }
                }
                // to identify PGW switch during uplink we use ttl 62
                if(hdr.ipv4.ttl == 62){
                    tun_egress_s3_uplink.apply();
                    return;
                }
            }
            
         }
             // Update port counters at index = ingress or egress port.
             if (standard_metadata.egress_spec < MAX_PORTS) {
                 tx_port_counter.count((bit<32>) standard_metadata.egress_spec);
             }
             if (standard_metadata.ingress_port < MAX_PORTS) {
                 rx_port_counter.count((bit<32>) standard_metadata.ingress_port);
             }

    }
}
/*************************************************************************
****************  E G R E S S   P R O C E S S I N G   *******************
*************************************************************************/

control c_egress(inout headers hdr,
                 inout metadata meta,
                 inout standard_metadata_t standard_metadata) {
        apply {
        // Nothing to do here, we assume checksum is always correct.
        }

}
/*************************************************************************
***********************  S W I T C H  *******************************
*************************************************************************/
V1Switch(c_parser(),
         c_verify_checksum(),
         c_ingress(),
         c_egress(),
         c_compute_checksum(),
         c_deparser()) main;
