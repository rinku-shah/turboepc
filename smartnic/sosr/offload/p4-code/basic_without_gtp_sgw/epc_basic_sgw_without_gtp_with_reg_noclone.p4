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

register<bit<16>>(65000) s2_downlink_egress_port;
register<bit<8>>(65000) reg_uestate;
bit<16> del_port = 65535;
bit<16> port_egress = 0;
bit<8> state_idle = 0;
bit<8> state_busy = 1;

   // ***************** Uplink Tunnel(DGW->PGW) Setup *******************************

    // action populate_ip_op_tun_s2_uplink(bit<32> op_tunnel_s2,bit<16> egress_port_s2){
    action populate_ip_op_tun_s2_uplink(bit<16> egress_port_s2){
        standard_metadata.egress_spec = egress_port_s2;
        hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
    }

   table ip_op_tun_s2_uplink{
       key={
            // @adding dummy field as we are assuiming we will not pass data in hardware
            hdr.ue_service_req.ue_key:exact;
            // match on gtp teid field and set the corressponding egress port
            // hdr.gtpu.teid : exact;
            // @vikas : withouth gtpu we need to think of something else to match on or we can leave it empty as well
       }
       actions={
           populate_ip_op_tun_s2_uplink;
           NoAction;
       }
       size = 65000;
       default_action = NoAction();
   }

   // ***************** Downlink Tunnel(PGW->DGW) Setup *******************************

//    action populate_ip_op_tun_s2_downlink(bit<32> op_tunnel_s2,bit<16> egress_port_s2){
   action populate_ip_op_tun_s2_downlink(bit<32> egress_port_s2){
       //standard_metadata.egress_spec = egress_port_s2;
       //hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
       //egress_port_s2 is the index to the register
       hdr.tmpreg.tmp_index = egress_port_s2; 
   }
  table ip_op_tun_s2_downlink{
      key={
            // @adding dummy field as we are assuiming we will not pass data in hardware
            // hdr.ue_service_req.ue_key:exact;
            hdr.tmpreg.ue_key:exact;
            // match on gtp teid field and set the corressponding egress port
            // hdr.gtpu.teid : exact;
            // @vikas : withouth gtpu we need to think of something else to match on or we can leave it empty as well
      }
      actions={
          populate_ip_op_tun_s2_downlink;
          NoAction;
      }
      size = 65000;
      default_action = NoAction();
  }


/* definig offload tables here which will be used on SGW for Context Release and Service Request */
    //action populate_uekey_uestate_map(bit<8> uestate){
    action populate_uekey_uestate_map(bit<32> reg_index){
       //hdr.uekey_uestate.ue_state = uestate;
       hdr.tmpreg.tmp_index = reg_index;
    }

    table uekey_uestate_map{
      key={
            //hdr.uekey_uestate.ue_key : exact;
            hdr.tmpreg.ue_key : exact;
      }
      actions={
          populate_uekey_uestate_map;
          NoAction;
      }
      size = 65000;
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
      size = 65000;
      default_action = NoAction();
    }

    // @offload design : handling service request at SGW for local onos processing
    action populate_service_req_uekey_sgwteid_map(bit<32> sgwteid){
	/*
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

        // send the packet to python controller running at SGW 
        standard_metadata.egress_spec = CPU_PORT;
        // Packets sent to the controller needs to be prepended with the
        // packet-in header. By setting it valid we make sure it will be
        // deparsed on the wire (see c_deparser).
        hdr.packet_in.setValid();
        hdr.packet_in.ingress_port = standard_metadata.ingress_port; */

         hdr.initial_ctxt_setup_req.setValid();
         hdr.initial_ctxt_setup_req.epc_traffic_code = 18;
         hdr.initial_ctxt_setup_req.sep1 = hdr.ue_service_req.sep1;
         hdr.initial_ctxt_setup_req.sgw_teid = sgwteid;
         // set invalid the incoming headers as we are appending new one
         hdr.data.setInvalid();
         hdr.ue_service_req.setInvalid();

         hdr.ipv4.ttl = 64;
         hdr.ethernet.dstAddr =  hdr.ethernet.srcAddr;
         hdr.ipv4.dstAddr = hdr.ipv4.srcAddr;

         // we need to send reply from sgw1,sgw2,sge3,sgw4 as per the chain
         if(hdr.ethernet.srcAddr == ran1){
             hdr.ethernet.srcAddr = sgw1;
             hdr.ipv4.srcAddr = s1u_sgw_addr;
         }

         hdr.tmpvar.tmpUdpPort = hdr.udp.srcPort;
         hdr.udp.srcPort = hdr.udp.dstPort;
         hdr.udp.dstPort = hdr.tmpvar.tmpUdpPort;
         hdr.tmpvar.setInvalid();

         hdr.udp.length_ = 11 + UDP_HDR_SIZE;
         hdr.ipv4.totalLen =  hdr.udp.length_ + IPV4_HDR_SIZE;

         // forwarding the cloned packet back to RAN on "p1"(1)
         standard_metadata.egress_spec = 1;
    }

    table service_req_uekey_sgwteid_map{
      key={
          // @offload design : we can match on ue_key of service request as well as intial_ctxt_setup_setup_resp  using ternary match also but in that case we need to have different actions as well so for now splitting the table into two
            hdr.ue_service_req.ue_key :  exact;
      }
      actions={
          populate_service_req_uekey_sgwteid_map;
          NoAction;
      }
      size = 65000;
      default_action = NoAction();
    }

    // @offload design : handling ctxt_setup_resp request from RAN at SGW for local onos processing
    action populate_ctxt_setup_uekey_sgwteid_map(bit<32> sgwteid){

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

        // send the packet to python controller running at SGW 
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
            hdr.initial_ctxt_setup_resp.ue_key :  exact;
      }
      actions={
          populate_ctxt_setup_uekey_sgwteid_map;
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
        // in hardware our CPU port is v0.0 (768) as our NF is running on that port
        if (standard_metadata.ingress_port == CPU_PORT) {
            // Packet received from CPU_PORT, this is a packet-out sent by the
            // controller. Skip table processing, set the egress port as
            // requested by the controller (packet_out header) and remove the
            // packet_out header.
            
            // hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
            // hdr.packet_out.setInvalid();
            //Outgoing ARP reply for DGW(pcube)
            if(hdr.ethernet.etherType == 0x0806 && hdr.ethernet.dstAddr == 0x001111111111){
                    standard_metadata.egress_spec =1;
                    return;
            }
                     //Outgoing ARP reply for PGW(p4client)
             else if(hdr.ethernet.etherType == 0x0806 && hdr.ethernet.dstAddr == 0x003333333333){
                    standard_metadata.egress_spec =0;
                    return;
            }
                //Outgoing TCP data packet reply for DGW(pcube)
            else if( hdr.ipv4.protocol == PROTO_TCP && hdr.ipv4.dstAddr == s1u_dgw_addr){
                    //ip_op_tun_s2_uplink.apply();
                    standard_metadata.egress_spec = 1;
                    return;
            }
                //Outgoing TCP data packet reply for PGW(p4client)
            else if(hdr.ipv4.protocol == PROTO_TCP && hdr.ipv4.dstAddr == s1u_pgw_addr){
                    //ip_op_tun_s2_uplink.apply();
                    standard_metadata.egress_spec = 0;
                    return;
            }
                  
            // @smartnic : forward all control packets from controller to DGW
            standard_metadata.egress_spec = 1;
            return;
        }  // CPU_PORT if ends here

         // @vikas : forwarding ARP packets via SmartNICs
        if(hdr.ethernet.etherType==TYPE_ARP){
                 arp_tbl.apply();
                 return;
        }

          //either a Data packet or it is a cntxt release/ Service request packet 
          if (hdr.ipv4.isValid()) {
                    // process the control packet
                    if(hdr.ipv4.protocol == PROTO_UDP){
                    // handling attach detach via the java controller runnign at SGW   
                      if(hdr.data.epc_traffic_code == 1 || hdr.data.epc_traffic_code == 3 
         || hdr.data.epc_traffic_code == 20 || hdr.data.epc_traffic_code == 5 
         || hdr.data.epc_traffic_code == 7 || hdr.data.epc_traffic_code == 9){
                                // it means it is a attach or detach packet
                                //  so forward it to CPU_PORT(vf0_0) to controller
                                //standard_metadata.egress_spec = CPU_PORT;
                              //hdr.ipv4.ttl = hdr.ipv4.ttl - 1;
          // send the original packet back to RAN by appending the reply packet
                    // we are sending packet to the python controller running over SGW switch CPU_PORT here is "v0.0"(768)
                    standard_metadata.egress_spec = CPU_PORT;
                    // Packets sent to the controller needs to be prepended with the
                    // packet-in header. By setting it valid we make sure it will be
                    // deparsed on the wire (see c_deparser).
                    hdr.packet_in.setValid();
                    hdr.packet_in.ingress_port = standard_metadata.ingress_port;
                                return;
                    }

                    // handling CR,SR messages
                    // @clone design: we are at SGW so 
                    // in all 3msg types reply back to RAN 
                    // clone the original packet, handle the cloned pkt at egress to send back to RAN
                    // forward the original packet to lcoal onos
                    // we use I2E_CLONE_SESSION_ID = 500 and set the out port as "p0"(0) in egress pipeline to reply back to RAN
                    //clone3(CloneType.I2E, I2E_CLONE_SESSION_ID, standard_metadata);

                    // handle context release message 
                    /*if(hdr.data.epc_traffic_code == 14){
                        // send the original packet back to RAN by appending the reply packet
                        // we are sending packet to the python controller running over SGW switch CPU_PORT here is "v0.0"(768)
                        standard_metadata.egress_spec = CPU_PORT;
                        // Packets sent to the controller needs to be prepended with the
                        // packet-in header. By setting it valid we make sure it will be
                        // deparsed on the wire (see c_deparser).
                        hdr.packet_in.setValid();
                        hdr.packet_in.ingress_port = standard_metadata.ingress_port;
                        return;
                    }

                    else if(hdr.data.epc_traffic_code == 17){
                        // send the original packet to local onos by appending the sgw_teid field
                        service_req_uekey_sgwteid_map.apply();
                        return;
                    }

                    else if(hdr.data.epc_traffic_code == 19){
                        // send the original packet to local onos by appending the sgw_teid field
                        ctxt_setup_uekey_sgwteid_map.apply();
                        return;
                    }*/

                    if(hdr.data.epc_traffic_code == 14){
                      hdr.tmpreg.ue_key = hdr.ue_context_rel_req.ue_num;
                    }
		    if(hdr.data.epc_traffic_code == 17){
                        // send the original packet to local onos by appending the sgw_teid field
                        service_req_uekey_sgwteid_map.apply();
                        return;
                    }
                    if(hdr.data.epc_traffic_code == 19){
                      hdr.tmpreg.ue_key = hdr.initial_ctxt_setup_resp.ue_key;
                    }
                    if((hdr.data.epc_traffic_code == 14) || (hdr.data.epc_traffic_code == 19)){
                      ip_op_tun_s2_downlink.apply();
                    }
                    if(hdr.data.epc_traffic_code == 14){
                      s2_downlink_egress_port.write(hdr.tmpreg.tmp_index, del_port);
                    }
                    if(hdr.data.epc_traffic_code == 19){
                      s2_downlink_egress_port.write(hdr.tmpreg.tmp_index, port_egress);
                    }

                    if((hdr.data.epc_traffic_code == 14) || (hdr.data.epc_traffic_code == 19)){
                      uekey_uestate_map.apply();
                    }
                    if(hdr.data.epc_traffic_code == 14){
                      reg_uestate.write( hdr.tmpreg.tmp_index, state_idle);
		      
                      // send the packet back to RAN
                                    hdr.ue_context_rel_command.setValid();
                                    hdr.ue_context_rel_command.epc_traffic_code = 15;
                                    hdr.ue_context_rel_command.sep1 = hdr.ue_context_rel_req.sep1;
                                    // set invalid the incoming headers as we are appending new one
                                    hdr.data.setInvalid();
                                    hdr.ue_context_rel_req.setInvalid();

                                    // setting ipv4 ttl back as 64 so that DGW can handle the packet                    
                                    hdr.ipv4.ttl = 64;
                                    hdr.ethernet.dstAddr =  hdr.ethernet.srcAddr;
                                    hdr.ipv4.dstAddr = hdr.ipv4.srcAddr;

                                    // we need to send reply from sgw1,sgw2,sge3,sgw4 as per the chain
                                    if(hdr.ethernet.srcAddr == ran1){
                                         hdr.ethernet.srcAddr = sgw1;
                                        hdr.ipv4.srcAddr = s1u_sgw_addr;
                                    }

                                    hdr.tmpvar.tmpUdpPort = hdr.udp.srcPort;
                                    hdr.udp.srcPort = hdr.udp.dstPort;
                                    hdr.udp.dstPort = hdr.tmpvar.tmpUdpPort;
                                    hdr.tmpvar.setInvalid();
          			    hdr.tmpreg.setInvalid();

                                    hdr.udp.length_ = 7 + UDP_HDR_SIZE;
                                    hdr.ipv4.totalLen =  hdr.udp.length_ + IPV4_HDR_SIZE;
                                    // forwarding the cloned packet back to RAN on "p1"(1)
                                    //@rinku: changing port to spec
            			    standard_metadata.egress_spec = 1;
			            //standard_metadata.egress_port = 1;
				    return;

                    }
                    if(hdr.data.epc_traffic_code == 19){
                      reg_uestate.write(hdr.tmpreg.tmp_index, state_busy);

		      // send the packet back to RAN
                      hdr.attach_accept.setValid();
                      hdr.attach_accept.epc_traffic_code = 8;
                      hdr.attach_accept.sep1 = hdr.initial_ctxt_setup_resp.sep1;
                      hdr.attach_accept.ue_key = hdr.initial_ctxt_setup_resp.ue_key;
                      // set invalid the incoming headers as we are appending new one
                      hdr.data.setInvalid();
                      hdr.initial_ctxt_setup_resp.setInvalid();
                      // send the packet back to RAN
                      hdr.ipv4.ttl = 64;

                      hdr.ethernet.dstAddr =  hdr.ethernet.srcAddr;
                      hdr.ipv4.dstAddr = hdr.ipv4.srcAddr;

                      if(hdr.ethernet.srcAddr == ran1){
                          hdr.ethernet.srcAddr = sgw1;
                          hdr.ipv4.srcAddr = s1u_sgw_addr;
                      }

                      hdr.tmpvar.tmpUdpPort = hdr.udp.srcPort;
                      hdr.udp.srcPort = hdr.udp.dstPort;
                      hdr.udp.dstPort = hdr.tmpvar.tmpUdpPort;
                      hdr.tmpvar.setInvalid();
		      hdr.tmpreg.setInvalid();

                      hdr.udp.length_ = 11 + UDP_HDR_SIZE;
                      hdr.ipv4.totalLen =  hdr.udp.length_ + IPV4_HDR_SIZE;

                      // forwarding the cloned packet back to RAN on "p1"(1)
                      //@rinku: changing port to spec
                      standard_metadata.egress_spec = 1;
                      //standard_metadata.egress_port = 1;
                      return;
                    }

                   /* if((hdr.data.epc_traffic_code == 14) || (hdr.data.epc_traffic_code == 17) || (hdr.data.epc_traffic_code == 19)){
                      //mark_to_drop();
                      standard_metadata.egress_spec = CPU_PORT; //2;
                      return;
                    }*/ 
                }
                    
          }

            // if (hdr.gtpu.isValid()) {
                   // @vikas : since we are removing GTP but we need to keep the state tables so adding this dummy check condition
            // if (hdr.ipv4.ttl == 100) {
            // if it is a data traffic then forward it 
            if(hdr.ipv4.protocol == PROTO_TCP){

                // Process all tunneled packets at SGW
                    // if ingress port is "p1"(1) on SGW it means it is a UPLINK tunnel packet (RAN -> Sink)
                    if(standard_metadata.ingress_port==1 && hdr.ipv4.dstAddr == s1u_sgw_addr){
                            //ip_op_tun_s2_uplink.apply();
                            standard_metadata.egress_spec = CPU_PORT;
                            return;
                    }
                    else if(standard_metadata.ingress_port==1 && hdr.ipv4.dstAddr == s1u_pgw_addr){
                            //ip_op_tun_s2_uplink.apply();
                            standard_metadata.egress_spec = 0;
                            return;
                    }
                    // if the ingress port is "p0"(0) then it a DOWNLINK tunnel packet (Sink -> RAN)
                    else if(standard_metadata.ingress_port==0 && hdr.ipv4.dstAddr == s1u_sgw_addr){
                            //ip_op_tun_s2_downlink.apply();
                            standard_metadata.egress_spec = CPU_PORT;
                            return;
                    }
                    else if(standard_metadata.ingress_port==0 && hdr.ipv4.dstAddr == s1u_dgw_addr){
                            //ip_op_tun_s2_uplink.apply();
                            standard_metadata.egress_spec = 1;
                            return;
                    }
            }

            // compiler removes tables which are not used, to prevent offload tables from being removed lets make an if check with large ttl values so that it is not removed.
            if(hdr.ipv4.ttl == 250){
                //uekey_uestate_map.apply();
                uekey_guti_map.apply();
                ip_op_tun_s2_uplink.apply();
                //ip_op_tun_s2_downlink.apply();
                //service_req_uekey_sgwteid_map.apply();
                ctxt_setup_uekey_sgwteid_map.apply();
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

                hdr.initial_ctxt_setup_req.setValid();
                hdr.initial_ctxt_setup_req.epc_traffic_code = 18;
                hdr.initial_ctxt_setup_req.sep1 = hdr.ue_service_req.sep1;
                hdr.initial_ctxt_setup_req.sgw_teid = sgwteid;
                // set invalid the incoming headers as we are appending new one
                hdr.data.setInvalid();
                hdr.ue_service_req.setInvalid();

                hdr.ipv4.ttl = 64;
                hdr.ethernet.dstAddr =  hdr.ethernet.srcAddr;
                hdr.ipv4.dstAddr = hdr.ipv4.srcAddr;

                 // we need to send reply from sgw1,sgw2,sge3,sgw4 as per the chain
                if(hdr.ethernet.srcAddr == ran1){
                    hdr.ethernet.srcAddr = sgw1;
                    hdr.ipv4.srcAddr = s1u_sgw_addr;
                }

                hdr.tmpvar.tmpUdpPort = hdr.udp.srcPort;
                hdr.udp.srcPort = hdr.udp.dstPort;
                hdr.udp.dstPort = hdr.tmpvar.tmpUdpPort;
                hdr.tmpvar.setInvalid();

                hdr.udp.length_ = 11 + UDP_HDR_SIZE;
                hdr.ipv4.totalLen =  hdr.udp.length_ + IPV4_HDR_SIZE;

                 // forwarding the cloned packet back to RAN on "p1"(1)
                standard_metadata.egress_port = 1;
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
            size = 65000;
            default_action = NoAction();
        }

        apply {
                // if (IS_I2E_CLONE(standard_metadata)) {
                    
            // this identifies cloned packet in smartNIC
            if (standard_metadata.instance_type == (bit<4>) 0x8){

                                    // @clone design: we are at SGW : beacuse ttl = 63 and we received a cloned packet in 
                                    // we have got cloned packet
                                    // output port is already set by mirrioring add using the CLI
                                    // as per the msg type do lookup append the necessary headers and send to local ONOS

                            // since we hae already made the clone check checking ttl is overkill
                            // if(hdr.ipv4.ttl == 63){

                            // handle context release message 
                            if(hdr.data.epc_traffic_code == 14){
                                    // send the packet back to RAN
                                    hdr.ue_context_rel_command.setValid();
                                    hdr.ue_context_rel_command.epc_traffic_code = 15;
                                    hdr.ue_context_rel_command.sep1 = hdr.ue_context_rel_req.sep1;
                                    // set invalid the incoming headers as we are appending new one
                                    hdr.data.setInvalid();
                                    hdr.ue_context_rel_req.setInvalid();

                                    // setting ipv4 ttl back as 64 so that DGW can handle the packet                    
                                    hdr.ipv4.ttl = 64;
                                    hdr.ethernet.dstAddr =  hdr.ethernet.srcAddr;
                                    hdr.ipv4.dstAddr = hdr.ipv4.srcAddr;

                                    // we need to send reply from sgw1,sgw2,sge3,sgw4 as per the chain
                                    if(hdr.ethernet.srcAddr == ran1){
                                         hdr.ethernet.srcAddr = sgw1;
                                        hdr.ipv4.srcAddr = s1u_sgw_addr;
                                    }

                                    hdr.tmpvar.tmpUdpPort = hdr.udp.srcPort;
                                    hdr.udp.srcPort = hdr.udp.dstPort;
                                    hdr.udp.dstPort = hdr.tmpvar.tmpUdpPort;
                                    hdr.tmpvar.setInvalid();
            hdr.tmpreg.setInvalid();

                                    hdr.udp.length_ = 7 + UDP_HDR_SIZE;
                                    hdr.ipv4.totalLen =  hdr.udp.length_ + IPV4_HDR_SIZE;
                                    // forwarding the cloned packet back to RAN on "p1"(1)
                                    //@rinku: changing port to spec
            //standard_metadata.egress_spec = 1;
            standard_metadata.egress_port = 1;

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
                                    hdr.ipv4.ttl = 64;

                                    hdr.ethernet.dstAddr =  hdr.ethernet.srcAddr;
                                    hdr.ipv4.dstAddr = hdr.ipv4.srcAddr;

                                    if(hdr.ethernet.srcAddr == ran1){
                                         hdr.ethernet.srcAddr = sgw1;
                                        hdr.ipv4.srcAddr = s1u_sgw_addr;
                                    }

                                    hdr.tmpvar.tmpUdpPort = hdr.udp.srcPort;
                                    hdr.udp.srcPort = hdr.udp.dstPort;
                                    hdr.udp.dstPort = hdr.tmpvar.tmpUdpPort;
                                    hdr.tmpvar.setInvalid();

                                    hdr.udp.length_ = 11 + UDP_HDR_SIZE;
                                    hdr.ipv4.totalLen =  hdr.udp.length_ + IPV4_HDR_SIZE;

                                     // forwarding the cloned packet back to RAN on "p1"(1)
                                     //@rinku: changing port to spec
                                    // standard_metadata.egress_spec = 1;
                                    standard_metadata.egress_port = 1;
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
