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



    // dummy table is for testing purpose only
    // action dummyaction(bit<9> egress_port){
    //      standard_metadata.egress_spec = egress_port;
    // }
    // table dummy{
    //     key={
    //         hdr.auth_step_one.imsi : exact;
    //     }
    //     actions={
    //         dummyaction;
    //     }
    //     size=1024;
    // }
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
       size = 2048;
       default_action = NoAction();
   }

 

   // ***************** Downlink Tunnel(PGW->DGW) Setup *******************************

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
      size = 2048;
      default_action = NoAction();
  }



/* definig offload tables here which will be used on SGW for Context Release and Service Request */
    action populate_uekey_uestate_map(bit<8> uestate){
       hdr.uekey_uestate.ue_state = uestate;
    }

    table uekey_uestate_map{
      key={
            hdr.uekey_uestate.ue_key : exact;
      }
      actions={
          populate_uekey_uestate_map;
          NoAction;
      }
      size = 2048;
      default_action = NoAction();
    }

    action populate_uekey_guti_map(bit<32> guti){
       hdr.uekey_guti.guti = guti;
    }

    table uekey_guti_map{
      key={
            hdr.uekey_guti.ue_key : exact;
      }
      actions={
          populate_uekey_guti_map;
          NoAction;
      }
      size = 2048;
      default_action = NoAction();
    }

    // @offload design : handling service request at SGW for local onos processing
    action populate_service_req_uekey_sgwteid_map(bit<32> sgwteid){
    //    hdr.uekey_sgwteid.sgw_teid = sgwteid;

        // copy the original header(ue_service_req) to new header(offload_ue_service_req) and add sgwteid from the lookup to new service request header
        hdr.offload_ue_service_req.setValid();

        hdr.offload_ue_service_req.ue_key = hdr.ue_service_req.ue_key;
        hdr.offload_ue_service_req.sep1 = hdr.ue_service_req.sep1;
        hdr.offload_ue_service_req.ksi_asme = hdr.ue_service_req.ksi_asme;
        hdr.offload_ue_service_req.sep2 = hdr.ue_service_req.sep2;
        hdr.offload_ue_service_req.ue_ip = hdr.ue_service_req.ue_ip;
        hdr.offload_ue_service_req.sep3 = hdr.ue_service_req.sep2;
        hdr.offload_ue_service_req.sgw_teid = sgwteid;

        // setinvalid the ue_service-req header, data header will still be in place
        hdr.ue_service_req.setInvalid();

        // send the packet to local onos 
        standard_metadata.egress_spec = CPU_PORT;
        // Packets sent to the controller needs to be prepended with the
        // packet-in header. By setting it valid we make sure it will be
        // deparsed on the wire (see c_deparser).
        hdr.packet_in.setValid();
        hdr.packet_in.ingress_port = standard_metadata.ingress_port;
    }

    table service_req_uekey_sgwteid_map{
      key={
          // @offload design : we can match on ue_key of service request as well as intial_ctxt_setup_setup_resp  using ternary match also but in that case we need to have different actions as well so for now splitting the table into two
            // hdr.uekey_sgwteid.ue_key : exact;
            hdr.ue_service_req.ue_key :  exact;
            // hdr.ipv4.srcAddr : exact;
      }
      actions={
          populate_service_req_uekey_sgwteid_map;
          NoAction;
      }
      size = 2048;
      default_action = NoAction();
    }

    // @offload design : handling ctxt_setup_resp request from RAN at SGW for local onos processing
    action populate_ctxt_setup_uekey_sgwteid_map(bit<32> sgwteid){
    //    hdr.uekey_sgwteid.sgw_teid = sgwteid;

        // copy the original header(ue_service_req) to new header(offload_ue_service_req) and add sgwteid from the lookup to new service request header
        hdr.offload_initial_ctxt_setup_resp.setValid();

        hdr.offload_initial_ctxt_setup_resp.ue_teid = hdr.initial_ctxt_setup_resp.ue_teid;
        hdr.offload_initial_ctxt_setup_resp.sep1 = hdr.initial_ctxt_setup_resp.sep1;
        hdr.offload_initial_ctxt_setup_resp.ue_key = hdr.initial_ctxt_setup_resp.ue_key;
        hdr.offload_initial_ctxt_setup_resp.sep2 = hdr.initial_ctxt_setup_resp.sep2;
        hdr.offload_initial_ctxt_setup_resp.ue_ip = hdr.initial_ctxt_setup_resp.ue_ip;
        hdr.offload_initial_ctxt_setup_resp.sep3 = hdr.initial_ctxt_setup_resp.sep2;
        hdr.offload_initial_ctxt_setup_resp.sgw_teid = sgwteid;

        // setinvalid the initial_ctxt_setup_resp header, data header will still be in place
        hdr.initial_ctxt_setup_resp.setInvalid();

        // send the packet to local onos 
        standard_metadata.egress_spec = CPU_PORT;
        // Packets sent to the controller needs to be prepended with the
        // packet-in header. By setting it valid we make sure it will be
        // deparsed on the wire (see c_deparser).
        hdr.packet_in.setValid();
        hdr.packet_in.ingress_port = standard_metadata.ingress_port;
    }

    table ctxt_setup_uekey_sgwteid_map{
      key={
          // @offload design : we can match on ue_key of service request as well as intial_ctxt_setup_setup_resp  using ternary match also but in that case we need to have different actions as well so for now splitting the table into two
            // hdr.uekey_sgwteid.ue_key : exact;
            hdr.initial_ctxt_setup_resp.ue_key :  exact;
            // hdr.ipv4.srcAddr : exact;

      }
      actions={
          populate_ctxt_setup_uekey_sgwteid_map;
          NoAction;
      }
      size = 2048;
      default_action = NoAction();
    }

    //@vikas : To implement the if condition statement as match entry lookup we need a seperate tables for entry lookup.

    /*************************** LOKKUP TABLES *************************************/
    table ue_context_rel_req_lookup_lb1_ub1{
        key={
            hdr.ue_context_rel_req.ue_num : exact;
        }
        actions = {
            NoAction;
        }
        size = 2048;
        default_action = NoAction();
    }

    table initial_ctxt_setup_resp_lookup_lb1_ub1{
        key={
            hdr.initial_ctxt_setup_resp.ue_key : exact;
        }
        actions = {
            NoAction;
        }
        size = 2048;
        default_action = NoAction();
    }

    table ue_service_req_lookup_lb1_ub1{
          key={
            hdr.ue_service_req.ue_key : exact;
        }
        actions = {
            NoAction;
        }
        size = 2048;
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
        
                // otherwise we are at SGW so we do a lookup on table service_req_uekey_sgwteid_map extract the sgwteid map append it to one of header fields and send it to local onos 
                // clone the original pkt and reply backt o RAN 

                    // @serial : @SGW1 uplink control packet 
                    if(standard_metadata.ingress_port == 1){

                        // do some lookup on hit clone and populate rules using local ONOS of SGW1 else on MISS forward to SGW2 on port 2
                             // HIT on the switch for 100 <= ue_num <=103 
                        if((ue_context_rel_req_lookup_lb1_ub1.apply().hit)|| (initial_ctxt_setup_resp_lookup_lb1_ub1.apply().hit) || (ue_service_req_lookup_lb1_ub1.apply().hit)) {
                             
                                // clone packet and reply back to RAN in egress processing
                                clone3(CloneType.I2E, I2E_CLONE_SESSION_ID, standard_metadata);

                                // handle context release message 
                                if(hdr.data.epc_traffic_code == 14){
                                    // send the original packet back to RAN by appending the reply packet
                                    standard_metadata.egress_spec = CPU_PORT;
                                    // Packets sent to the controller needs to be prepended with the
                                    // packet-in header. By setting it valid we make sure it will be
                                    // deparsed on the wire (see c_deparser).
                                    hdr.packet_in.setValid();
                                    hdr.packet_in.ingress_port = standard_metadata.ingress_port;
                                    // return;
                                }

                                else if(hdr.data.epc_traffic_code == 17){
                                    // send the original packet to local onos by appending the sgw_teid field
                                    service_req_uekey_sgwteid_map.apply();
                                    // return;
                                }

                                else if(hdr.data.epc_traffic_code == 19){
                                    // send the original packet to local onos by appending the sgw_teid field
                                    ctxt_setup_uekey_sgwteid_map.apply();
                                    // return;
                                }
                        }

                        //since its a miss, send to SGW2
                        // else if((ue_context_rel_req_lookup_lb2_ub2.apply().hit)|| (initial_ctxt_setup_resp_lookup_lb2_ub2.apply().hit) || (ue_service_req_lookup_lb2_ub2.apply().hit)) {
                        else{    
                                standard_metadata.egress_spec = 2;
                                hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
                        }
                    }
                     // @serial : @SGW1_1 downlink control packet originating from root ONOS via SGW1_2 
                    else if(standard_metadata.ingress_port == 2){
                        // forward directly to RAN
                        standard_metadata.egress_spec = 1;
                        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
                    }


          }  // control packet if over

        if (hdr.gtpu.isValid()) {
                // Process all tunneled packets at SGW
                if(hdr.ipv4.ttl == 63){
                    // if ingress port is 1 on SGW it means it is a UPLINK tunnel packet (RAN -> Sink)
                    if(standard_metadata.ingress_port==1){
                            ip_op_tun_s2_uplink.apply();
                            return;
                    }
                    // if the ingress port is 2 then it a DOWNLINK tunnel packet (Sink -> RAN)
                    else if(standard_metadata.ingress_port==2){
                            ip_op_tun_s2_downlink.apply();
                            return;
                    }
                }
        }

            // compiler removes tables which are not used, to prevent offload tables from being removed lets make an if check with large ttl values so that it is not removed.
            if(hdr.ipv4.ttl == 250){
                uekey_uestate_map.apply();
                uekey_guti_map.apply();
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

         // @offload design : handling service request at SGW for local onos processing
        action populate_ctxt_release_uekey_sgwteid_map(bit<32> sgwteid){
		
		bit<32> tmp_ue_num;
		tmp_ue_num =  hdr.ue_service_req.ue_key;
                hdr.initial_ctxt_setup_req.setValid();
                hdr.initial_ctxt_setup_req.epc_traffic_code = 18;
                hdr.initial_ctxt_setup_req.sep1 = hdr.ue_service_req.sep1;
                hdr.initial_ctxt_setup_req.sgw_teid = sgwteid;
                // set invalid the incoming headers as we are appending new one
                hdr.data.setInvalid();
                hdr.ue_service_req.setInvalid();
                standard_metadata.egress_spec = 1;

                hdr.ipv4.ttl = 64;
                hdr.ethernet.dstAddr =  hdr.ethernet.srcAddr;
                hdr.ipv4.dstAddr = hdr.ipv4.srcAddr;

                 // we need to send reply from sgw1,sgw2,sge3,sgw4 as per the chain
                if(hdr.ethernet.srcAddr == ran1  && (tmp_ue_num >= LB1 && tmp_ue_num <= UB1)){
                    hdr.ethernet.srcAddr = sgw1;
                    hdr.ipv4.srcAddr = s1u_sgw_addr;
                }
		        else if(hdr.ethernet.srcAddr == ran1  && (tmp_ue_num >= LB2 && tmp_ue_num <= UB2)){
                    hdr.ethernet.srcAddr = sgw2;
                    hdr.ipv4.srcAddr = s2u_sgw_addr;
                }
                else if(hdr.ethernet.srcAddr == ran2){
                    hdr.ethernet.srcAddr = sgw2;
                    hdr.ipv4.srcAddr = s2u_sgw_addr;
                }
                else if(hdr.ethernet.srcAddr == ran3){
                    hdr.ethernet.srcAddr = sgw3;
                    hdr.ipv4.srcAddr = s3u_sgw_addr;

                }
                else if(hdr.ethernet.srcAddr == ran4){
                    hdr.ethernet.srcAddr = sgw4;
                    hdr.ipv4.srcAddr = s4u_sgw_addr;
                }
                else if(hdr.ethernet.srcAddr == ran5){
                    hdr.ethernet.srcAddr = sgw5;
                    hdr.ipv4.srcAddr = s5u_sgw_addr;

                }
                else if(hdr.ethernet.srcAddr == ran6){
                        hdr.ethernet.srcAddr = sgw6;
                    hdr.ipv4.srcAddr = s6u_sgw_addr;
                }


                hdr.tmpvar.tmpUdpPort = hdr.udp.srcPort;
                hdr.udp.srcPort = hdr.udp.dstPort;
                hdr.udp.dstPort = hdr.tmpvar.tmpUdpPort;
                hdr.tmpvar.setInvalid();

                hdr.udp.length_ = 11 + UDP_HDR_SIZE;
                hdr.ipv4.totalLen =  hdr.udp.length_ + IPV4_HDR_SIZE;
        }

        table ctxt_release_uekey_sgwteid_map{
            key={
                // @offload design : we can match on ue_key of service request as well as intial_ctxt_setup_setup_resp  using ternary match also but in that case we need to have different actions as well so for now splitting the table into two
                    // hdr.uekey_sgwteid.ue_key : exact;
                    hdr.ue_service_req.ue_key :  exact;
            }
            actions={
                populate_ctxt_release_uekey_sgwteid_map;
                NoAction;
            }
            size = 2048;
            default_action = NoAction();
        }

        apply {
                if (IS_I2E_CLONE(standard_metadata)) {
                                    // @clone design: we are at SGW : beacuse ttl = 63 and we received a cloned packet in 
                                    // we have got cloned packet
                                    // output port is already set by mirrioring add using the CLI
                                    // as per the msg type do lookup append the necessary headers and send to local ONOS

                            // since we hae already made the clone check checking ttl is overkill
                            // if(hdr.ipv4.ttl == 63){

                            // handle context release message 
			                bit<32> tmp_ue_num1;
                            if(hdr.data.epc_traffic_code == 14){
                                    // send the packet back to RAN
				                    tmp_ue_num1 =  hdr.ue_context_rel_req.ue_num;
                                    hdr.ue_context_rel_command.setValid();
                                    hdr.ue_context_rel_command.epc_traffic_code = 15;
                                    hdr.ue_context_rel_command.sep1 = hdr.ue_context_rel_req.sep1;
                                    // set invalid the incoming headers as we are appending new one
                                    hdr.data.setInvalid();
                                    hdr.ue_context_rel_req.setInvalid();
                                    standard_metadata.egress_spec = 1;

                                    // setting ipv4 ttl back as 64 so that DGW can handle the packet                    
                                    hdr.ipv4.ttl = 64;
                                    hdr.ethernet.dstAddr =  hdr.ethernet.srcAddr;
                                    hdr.ipv4.dstAddr = hdr.ipv4.srcAddr;

                                    // we need to send reply from sgw1,sgw2,sge3,sgw4 as per the chain
                                    if(hdr.ethernet.srcAddr == ran1 && (tmp_ue_num1 >= LB1 && tmp_ue_num1 <= UB1)){
                                         hdr.ethernet.srcAddr = sgw1;
                                        hdr.ipv4.srcAddr = s1u_sgw_addr;
                                    }
			                        else if(hdr.ethernet.srcAddr == ran1 && (tmp_ue_num1 >= LB2 && tmp_ue_num1 <= UB2)){
                                        hdr.ethernet.srcAddr = sgw2;
                                        hdr.ipv4.srcAddr = s2u_sgw_addr;
                                    }
                                    else if(hdr.ethernet.srcAddr == ran2){
                                         hdr.ethernet.srcAddr = sgw2;
                                        hdr.ipv4.srcAddr = s2u_sgw_addr;
                                    }
                                    else if(hdr.ethernet.srcAddr == ran3){
                                         hdr.ethernet.srcAddr = sgw3;
                                        hdr.ipv4.srcAddr = s3u_sgw_addr;

                                    }
                                    else if(hdr.ethernet.srcAddr == ran4){
                                         hdr.ethernet.srcAddr = sgw4;
                                        hdr.ipv4.srcAddr = s4u_sgw_addr;
                                    }
                                     else if(hdr.ethernet.srcAddr == ran5){
                                         hdr.ethernet.srcAddr = sgw5;
                                        hdr.ipv4.srcAddr = s5u_sgw_addr;

                                    }
                                    else if(hdr.ethernet.srcAddr == ran6){
                                         hdr.ethernet.srcAddr = sgw6;
                                        hdr.ipv4.srcAddr = s6u_sgw_addr;
                                    }


                                    hdr.tmpvar.tmpUdpPort = hdr.udp.srcPort;
                                    hdr.udp.srcPort = hdr.udp.dstPort;
                                    hdr.udp.dstPort = hdr.tmpvar.tmpUdpPort;
                                    hdr.tmpvar.setInvalid();

                                    hdr.udp.length_ = 7 + UDP_HDR_SIZE;
                                    hdr.ipv4.totalLen =  hdr.udp.length_ + IPV4_HDR_SIZE;

                            }

                            else if(hdr.data.epc_traffic_code == 17){
                                    // send the packet back to RAN
                                    ctxt_release_uekey_sgwteid_map.apply();
                            }

                            else if(hdr.data.epc_traffic_code == 19){
                                    // send the packet back to RAN
                                    hdr.attach_accept.setValid();
                                    hdr.attach_accept.epc_traffic_code = 8;
                                    hdr.attach_accept.sep1 = hdr.initial_ctxt_setup_resp.sep1;
                                    hdr.attach_accept.ue_key = hdr.initial_ctxt_setup_resp.ue_key;
                                    // set invalid the incoming headers as we are appending new one
                                    hdr.data.setInvalid();
                                    hdr.initial_ctxt_setup_resp.setInvalid();
                                    // send the packet back to RAN
                                    standard_metadata.egress_spec = 1;
                                    hdr.ipv4.ttl = 64;

                                    hdr.ethernet.dstAddr =  hdr.ethernet.srcAddr;
                                    hdr.ipv4.dstAddr = hdr.ipv4.srcAddr;

                                    if(hdr.ethernet.srcAddr == ran1 && (hdr.attach_accept.ue_key >= LB1 && hdr.attach_accept.ue_key <= UB1)){
                                         hdr.ethernet.srcAddr = sgw1;
                                        hdr.ipv4.srcAddr = s1u_sgw_addr;

                                    }
				                     else if(hdr.ethernet.srcAddr == ran1 && (hdr.attach_accept.ue_key >= LB2 && hdr.attach_accept.ue_key <= UB2)){
                                        hdr.ethernet.srcAddr = sgw2;
                                        hdr.ipv4.srcAddr = s2u_sgw_addr;

                                    }
                                    else if(hdr.ethernet.srcAddr == ran2){
                                         hdr.ethernet.srcAddr = sgw2;
                                        hdr.ipv4.srcAddr = s2u_sgw_addr;

                                    }
                                    else if(hdr.ethernet.srcAddr == ran3){
                                         hdr.ethernet.srcAddr = sgw3;
                                        hdr.ipv4.srcAddr = s3u_sgw_addr;

                                    }
                                    else if(hdr.ethernet.srcAddr == ran4){
                                         hdr.ethernet.srcAddr = sgw4;
                                        hdr.ipv4.srcAddr = s4u_sgw_addr;

                                    }
                                    else if(hdr.ethernet.srcAddr == ran5){
                                         hdr.ethernet.srcAddr = sgw5;
                                        hdr.ipv4.srcAddr = s5u_sgw_addr;

                                    }
                                    else if(hdr.ethernet.srcAddr == ran6){
                                         hdr.ethernet.srcAddr = sgw6;
                                        hdr.ipv4.srcAddr = s6u_sgw_addr;
                                    }

                                    hdr.tmpvar.tmpUdpPort = hdr.udp.srcPort;
                                    hdr.udp.srcPort = hdr.udp.dstPort;
                                    hdr.udp.dstPort = hdr.tmpvar.tmpUdpPort;
                                    hdr.tmpvar.setInvalid();

                                    hdr.udp.length_ = 11 + UDP_HDR_SIZE;
                                    hdr.ipv4.totalLen =  hdr.udp.length_ + IPV4_HDR_SIZE;
                                     // return;
                            }

                }  // if close

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

