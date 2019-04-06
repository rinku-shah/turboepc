/* -*- P4_16 -*- */
#include <core.p4>
#include <v1model.p4>
#include "include/headers.p4"
#include "include/parser.p4"
#include "include/checksums.p4"
#include "include/definitions.p4"
#define MAX_PORTS 255

#define IS_I2E_CLONE(std_meta) (std_meta.instance_type == BMV2_V1MODEL_INSTANCE_TYPE_INGRESS_CLONE)
#define IS_E2E_CLONE(std_meta) (std_meta.instance_type == BMV2_V1MODEL_INSTANCE_TYPE_EGRESS_CLONE)

    
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
    }

    action send_to_cpu() {
        standard_metadata.egress_spec = CPU_PORT;
        // Packets sent to the controller needs to be prepended with the
        // packet-in header. By setting it valid we make sure it will be
        // deparsed on the wire (see c_deparser).
        hdr.packet_in.setValid();
        hdr.packet_in.ingress_port = standard_metadata.ingress_port;
        // reason_code 100 means packet_in has to be sent to root contoller 
        hdr.packet_in.reason_code = 100; 
    }

    action _drop() {
        mark_to_drop();
    }

    // Table counter used to count packets and bytes matched by each entry of
    // t_l2_fwd table.
    direct_counter(CounterType.packets_and_bytes) l3_fwd_counter;

    table t_l3_fwd {
        key = {
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
        hdr.gtpu_ipv4.srcAddr = s1u_dgw_ipaddr;
        hdr.gtpu_ipv4.dstAddr = s11_sgw_ipaddr;
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



    action populate_tun_egress_s3_uplink(bit<9> egress_port_s3){
        standard_metadata.egress_spec = egress_port_s3;

        hdr.gtpu_ipv4 = hdr.ipv4;
        hdr.gtpu_udp = hdr.udp;
        hdr.ipv4 = hdr.inner_ipv4;
        hdr.tcp = hdr.inner_tcp;

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

        hdr.gtpu.setInvalid();
        hdr.gtpu_ipv4.setInvalid();
        hdr.gtpu_udp.setInvalid();

        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

    // tunnel to egress port map for s3
    table tun_egress_s3_uplink{
        key={

            // match on gtp teid field and set the corressponding egress port
            hdr.gtpu.teid : exact;

        }
        actions={
            populate_tun_egress_s3_uplink;
            NoAction;
        }
        size = 4096;
        default_action = NoAction();
    }



    apply {
        if (standard_metadata.ingress_port == CPU_PORT) {
            // Packet received from CPU_PORT, this is a packet-out sent by the
            // controller. Skip table processing, set the egress port as
            // requested by the controller (packet_out header) and remove the
            // packet_out header.
            standard_metadata.egress_spec = hdr.packet_out.egress_port;
            // hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
            hdr.packet_out.setInvalid();
            return;

        } else {
            // Packet received from data plane port.
            // Applies table t_l2_fwd to the packet.
            if (t_l3_fwd.apply().hit) {
                // Packet hit an entry in t_l2_fwd table. A forwarding action
                // has already been taken. No need to apply other tables, exit
                // this control block.
                return;
            }

            // if the packet misses in the t_l3_fwd table then it means it either a Data packet or it is a cntxt release/ Service request packet 
            if (hdr.ipv4.isValid() && !hdr.gtpu.isValid()) {
                // process reply from Sink to RAN at PGW 
                   if(standard_metadata.ingress_port==5){

                            // @clone design: we are at DGW so simply forward as of now

                            // @offload design: to be on safe side we are using ip proto to distinguish between data and control traffic 
                            //  if we use above code then sometimes it gets stuck because tcp data can also contain hdr.data.epc_traffic_code 
                            //TC means data packet
                            // going with this to be on safe side 
                            if(hdr.ipv4.protocol == PROTO_TCP){
                                ip_op_tun_s1_uplink.apply();
                                return;
                            }
                   }
            }  // control packet if over

            if (hdr.gtpu.isValid()) {
		            // Process tunneled data packets coming from SGWs
                    tun_egress_s3_uplink.apply();
                    return;
            }
            
         } // else over
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

                     apply{
                         
                     }


} // egress control close


/*************************************************************************
***********************  S W I T C H  *******************************
*************************************************************************/
V1Switch(c_parser(),
         c_verify_checksum(),
         c_ingress(),
         c_egress(),
         c_compute_checksum(),
         c_deparser()) main;

