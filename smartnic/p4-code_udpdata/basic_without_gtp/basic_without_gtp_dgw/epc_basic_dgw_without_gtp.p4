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

    // action send_to_cpu(bit<16> cpu_port) {
    //     standard_metadata.egress_spec = cpu_port;
    //     // Packets sent to the controller needs to be prepended with the
    //     // packet-in header. By setting it valid we make sure it will be
    //     // deparsed on the wire (see c_deparser).
    //     hdr.packet_in.setValid();
    //     hdr.packet_in.ingress_port = standard_metadata.ingress_port;
    // }

    // action _drop() {
    //     mark_to_drop();
    // }

    // // this table will send tha packet to SGW controller, though it is not required in DGW but we keep it for completeness
    // table send_to_controller {
    //     key = {
    //         standard_metadata.ingress_port  : exact;
    //     }
    //     actions = {
    //         send_to_cpu;
    //         _drop;
    //         NoAction;
    //     }
    //     size = 1024;
    //     default_action =  NoAction();
    //     // counters = l3_fwd_counter;
    // }

   // ***************** Uplink Tunnel(DGW->PGW) Setup *******************************
    // action populate_ip_op_tun_s1_uplink(bit<32> op_tunnel_s1,bit<16> egress_port_s1){
    action populate_ip_op_tun_s1_uplink(bit<16> egress_port_s1){
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
       size = 65000;
       default_action = NoAction();
   }

   // ***************** Downlink Tunnel(PGW->DGW) Setup *******************************
    action populate_tun_egress_s3_uplink(bit<16> egress_port_s3){
        standard_metadata.egress_spec = egress_port_s3;

        // Downlink trafiic at DWG comes from Sink and it has to be forwarded to RAN
         if(hdr.ipv4.srcAddr==sink_ip){
             if(hdr.tcp.src_port == 13001){
                hdr.ethernet.dstAddr = ran1;
            }
        }
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

    // tunnel to egress port map for DGW
    table tun_egress_s3_uplink{
        key={
            // @adding dummy field as we are assuiming we will not pass data in hardware
            hdr.ue_service_req.ue_key:exact;
            // match on gtp teid field and set the corressponding egress port
            // hdr.gtpu.teid : exact;
            // @vikas : withouth gtpu we need to think of something else to match on or we can leave it empty as well
        }
        actions={
            populate_tun_egress_s3_uplink;
            NoAction;
        }
        size = 65000;
        default_action = NoAction();
    }

    // ARP packets forwarding tables 
    action fwd_act( bit<16> prt) {
        standard_metadata.egress_spec = prt;
    }

    action drop_act() {
        mark_to_drop();
    }

    table arp_tbl {
        key={
            standard_metadata.ingress_port : exact;
        }
        actions={
            fwd_act;
            drop_act;
        }
        size = 65000;
    }

    apply {
         // @vikas : forwarding ARP packets via SmartNICs
          if(hdr.ethernet.etherType==TYPE_ARP){
                arp_tbl.apply();
                return;
          }
            // if the packet is a Data packet or it is a Control packet 
          else if (hdr.ipv4.isValid()) {

                    //  from RAN to local onos at DGW 
                    //  if ingrees port is logical v0.0(768) then it means it is a packet from RAN running at DGW
                   if(standard_metadata.ingress_port==768 ){
                            // @offload design: to be on safe side we are using ip proto to distinguish between data and control traffic 
                            //  if we use above code then sometimes it gets stuck because tcp data can also contain hdr.data.epc_traffic_code 
                            //TC means data packet
                            // going with this to be on safe side 
                            if(hdr.ipv4.protocol == PROTO_UDP && hdr.udp.dstPort == 8001){
                                standard_metadata.egress_spec = 0;
                                //ip_op_tun_s1_uplink.apply();
                                return;
                            }
                            // UDP means control traffic so forward it to SGW which is connected at physical port "p0"(0)
                            else if(hdr.ipv4.protocol == PROTO_UDP){
                                    standard_metadata.egress_spec = 0;
                                    hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
                                    return;
                            }
                   }
                    // process reply from SGW. DGW and SGW are connected via physical port "p0"(0) 
                    else if(standard_metadata.ingress_port==0){
                                // forward the packet to NF v0.0 (768)
                                standard_metadata.egress_spec = 768;
                                hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
                                return;
                    }
          }

            // if (hdr.gtpu.isValid()) {
                // @vikas : since we are removing GTP but we need to keep the state tables so adding this dummy check condition
            if (hdr.ipv4.ttl == 100) {
                // Process all tunneled packets at DGW
                    tun_egress_s3_uplink.apply();
                    ip_op_tun_s1_uplink.apply();
                    return;
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

        }  // apply close
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
