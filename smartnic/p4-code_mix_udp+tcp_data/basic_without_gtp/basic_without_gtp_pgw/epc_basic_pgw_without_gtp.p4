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

       // At PGW for the Uplink traffic comes from RAN and it has to be forwarded to Sink
        // we need to set the destination src MAC address otherwise the packet will not be accepted by the next hop interface as it is host

        // @vikas : removing as we have only 1 chain in hardware

        // else if(standard_metadata.ingress_port==1 || standard_metadata.ingress_port==2 || standard_metadata.ingress_port==3 || standard_metadata.ingress_port==4  || standard_metadata.ingress_port==5  || standard_metadata.ingress_port==6){
            // this check is not required as all pkts have to be sent to sink
            if(hdr.ethernet.srcAddr==ran1){
                hdr.ethernet.dstAddr = sink;
            }
        // }
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

    // tunnel to egress port map for s3
    table tun_egress_s3_uplink{
        key={
            // @adding dummy field as we are assuiming we will not pass data in hardware
             hdr.ue_service_req.ue_key:exact;
            // match on gtp teid field and set the corressponding egress port
            // hdr.gtpu.teid : exact;
            // @vikas : without gtpu we need to think of something else to match on or we can leave it empty as well
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
            // if the packet is either a Data packet or it is a cntxt release/ Service request packet 
          if (hdr.ipv4.isValid() ) {
                    // process reply from Sink to RAN at PGW (Downlink Packets)
                    // @vikas : since the response comes from PGW machine we assume the port is v0.0
                    //  assuming mapping is v0.0 => 768 
                   if(standard_metadata.ingress_port==768){

                            // @offload design: to be on safe side we are using ip proto to distinguish between data and control traffic 
                            //  if we use above code then sometimes it gets stuck because tcp data can also contain hdr.data.epc_traffic_code 
                            //TC means data packet
                            // going with this to be on safe side 
                            if(hdr.ipv4.protocol == PROTO_UDP || hdr.ipv4.protocol == PROTO_TCP){
                                standard_metadata.egress_spec = 0;
                                //ip_op_tun_s1_uplink.apply();
                                return;
                            }

                            // @modular : there will be no UDP packets to be processed at PGW
                            // UDP means control traffic
                            // else if(hdr.ipv4.protocol == PROTO_UDP){
                            //         standard_metadata.egress_spec = 2;
                            //         hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
                            //         // return;
                            // }
                   }
            }  // if close

            // if (hdr.gtpu.isValid()) {
                  // @vikas : since we are removing GTP but we need to keep the state tables so adding this dummy check condition
            // if (hdr.ipv4.ttl == 100) {
            // process Uplink packets from RAN to Sink since SGW and PGW are connected via "p0"(0) 
            if(standard_metadata.ingress_port==0){
                // Process all tunneled packets at PGW
                    standard_metadata.egress_spec = 768;
                    //tun_egress_s3_uplink.apply();
                    return;
            }
            if(hdr.ipv4.ttl == 250){
                ip_op_tun_s1_uplink.apply();
                tun_egress_s3_uplink.apply();
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
