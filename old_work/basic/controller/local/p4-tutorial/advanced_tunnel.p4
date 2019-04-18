/* -*- P4_16 -*- */
#include <core.p4>
#include <v1model.p4>
#include "include/headers.p4"
#include "include/parser.p4"
#include "include/checksums.p4"


/*************************************************************************
**************  I N G R E S S   P R O C E S S I N G   *******************
*************************************************************************/

control MyIngress(inout headers hdr,
                  inout metadata meta,
                  inout standard_metadata_t standard_metadata) {
    action drop() {
        mark_to_drop();
    }

    action ipv4_forward(macAddr_t dstAddr, egressSpec_t port) {
        standard_metadata.egress_spec = port;
        hdr.ethernet.srcAddr = hdr.ethernet.dstAddr;
        hdr.ethernet.dstAddr = dstAddr;
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

    table ipv4_lpm {
        key = {
            hdr.ipv4.dstAddr: lpm;
        }
        actions = {
            ipv4_forward;
            drop;
            NoAction;
        }
        size = 1024;
        default_action = drop();
    }

    action match_key_get_val(code_t  val) {
      hdr.data. epc_traffic_code  = val;
    }


    table match_key {
       key = {
           hdr.data.epc_traffic_code : exact;
       }
        actions = {
             match_key_get_val;
             NoAction;
       }
      size = 1024;
      default_action = NoAction();
   }

   action send_to_controller(){
       standard_metadata.egress_spec = CONTROLLER_PORT;
   }

   table controller{
       key={}
       actions = {
           send_to_controller;
           NoAction;
       }
        size = 1024;
        default_action = NoAction();
   }

   action populate_kv(bit<128> value){
       hdr.kv.value = value;
       standard_metadata.egress_spec = standard_metadata.ingress_port;
       hdr.udp.dstPort = 65500;
   }
   table kv_store{
       key={
           hdr.kv.key1 : exact;
       }
       actions={
           populate_kv;
           NoAction;
       }
       size = 1024;
       default_action = NoAction();
   }



   // ***************** Uplink Tunnel(h1->h2) Setup *******************************

    action populate_ip_op_tun_s1_uplink(bit<12> op_tunnel_s1,bit<9> egress_port_s1){
        standard_metadata.egress_spec = egress_port_s1;
        hdr.vlan.vid = op_tunnel_s1;
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }
   table ip_op_tun_s1_uplink{
       key={
           // match on the VLAN ID field vid and set the vid to the outgoing tunnel and set egress port
           hdr.vlan.vid : exact;
       }
       actions={
           populate_ip_op_tun_s1_uplink;
           NoAction;
       }
       size = 1024;
       default_action = NoAction();
   }

    action populate_ip_op_tun_s2_uplink(bit<12> op_tunnel_s2,bit<9> egress_port_s2){
        standard_metadata.egress_spec = egress_port_s2;
        hdr.vlan.vid = op_tunnel_s2;
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }
   table ip_op_tun_s2_uplink{
       key={
           // match on the VLAN ID field vid and set the vid to the outgoing tunnel and set egress port
           hdr.vlan.vid : exact;
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
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }
    // tunnel to egress port map for s3
    table tun_egress_s3_uplink{
        key={
            // match on vlan ID field and set the corressponding egress port
             hdr.vlan.vid : exact;
        }
        actions={
            populate_tun_egress_s3_uplink;
            NoAction;
        }
        size = 1024;
        default_action = NoAction();
    }



   // ***************** Downlink Tunnel(h2->h1) Setup *******************************

   action populate_ip_op_tun_s3_downlink(bit<12> op_tunnel_s3,bit<9> egress_port_s3){
       standard_metadata.egress_spec = egress_port_s3;
       hdr.vlan.vid = op_tunnel_s3;
       hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
   }
   table ip_op_tun_s3_downlink{
      key={
          // match on the VLAN ID field vid and set the vid to the outgoing tunnel and set egress port
          hdr.vlan.vid : exact;
      }
      actions={
          populate_ip_op_tun_s3_downlink;
          NoAction;
      }
      size = 1024;
      default_action = NoAction();
  }

   action populate_ip_op_tun_s2_downlink(bit<12> op_tunnel_s2,bit<9> egress_port_s2){
       standard_metadata.egress_spec = egress_port_s2;
       hdr.vlan.vid = op_tunnel_s2;
       hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
   }
  table ip_op_tun_s2_downlink{
      key={
          // match on the VLAN ID field vid and set the vid to the outgoing tunnel and set egress port
          hdr.vlan.vid : exact;
      }
      actions={
          populate_ip_op_tun_s2_downlink;
          NoAction;
      }
      size = 1024;
      default_action = NoAction();
  }

   action populate_tun_egress_s1_downlink(bit<9> egress_port_s1){
       standard_metadata.egress_spec = egress_port_s1;
       hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
   }
   // tunnel to egress port map for s1 for Downlink
   table tun_egress_s1_downlink{
       key={
           // match on vlan ID field and set the corressponding egress port
            hdr.vlan.vid : exact;
       }
       actions={
           populate_tun_egress_s1_downlink;
           NoAction;
       }
       size = 1024;
       default_action = NoAction();
   }

    apply {
        // if data packet then
        //  1. set the outgoing tunnel ID for incoming tunnel ID
        //  2. Set the egress port after looking up incoming tunnel ID
        //  Note : tunnel ID is vlan vid
        if(hdr.data.epc_traffic_code==7){
            // to identify switch1 we use ttl 64
            if(hdr.ipv4.ttl == 64){
                ip_op_tun_s1_uplink.apply();
            }
            // to identify switch2 we use ttl 63
            if(hdr.ipv4.ttl == 63){
                ip_op_tun_s2_uplink.apply();
            }
            // to identify switch1 we use ttl 62
            if(hdr.ipv4.ttl == 62){
                tun_egress_s3_uplink.apply();
            }
        }
        else if(hdr.data.epc_traffic_code==8){
            // to identify switch1 we use ttl 64
            if(hdr.ipv4.ttl == 64){
                ip_op_tun_s3_downlink.apply();
            }
            // to identify switch2 we use ttl 63
            if(hdr.ipv4.ttl == 63){
                ip_op_tun_s2_downlink.apply();
            }
            // to identify switch1 we use ttl 62
            if(hdr.ipv4.ttl == 62){
                tun_egress_s1_downlink.apply();
            }
        }

         else if ( hdr.ipv4.isValid()) {
            ipv4_lpm.apply();
            if((hdr.data.epc_traffic_code==2 || hdr.data.epc_traffic_code==5) && standard_metadata.ingress_port !=3){
                controller.apply();
            }
            if(hdr.data.epc_traffic_code==1)  {
                match_key.apply();
            }
            if(hdr.data.epc_traffic_code==3){
                kv_store.apply();
            }

         }

    }
}

/*************************************************************************
****************  E G R E S S   P R O C E S S I N G   *******************
*************************************************************************/

control MyEgress(inout headers hdr,
                 inout metadata meta,
                 inout standard_metadata_t standard_metadata) {


    apply {

    }

}



/*************************************************************************
***********************  S W I T C H  *******************************
*************************************************************************/

V1Switch(
MyParser(),
MyVerifyChecksum(),
MyIngress(),
MyEgress(),
MyComputeChecksum(),
MyDeparser()
) main;
