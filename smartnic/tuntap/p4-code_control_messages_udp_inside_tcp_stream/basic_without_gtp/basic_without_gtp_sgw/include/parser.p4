#ifndef __PARSER__
#define __PARSER__
#include "definitions.p4"

/*************************************************************************
*********************** P A R S E R  ***********************************
*************************************************************************/

parser c_parser(packet_in packet,
                out headers hdr,
                inout metadata meta,
                inout standard_metadata_t standard_metadata) {

    state start {
        transition select(standard_metadata.ingress_port) {
            // CPU_PORT: parse_packet_out;
            default: parse_ethernet;
        }
    }

    state parse_packet_out {
        packet.extract(hdr.packet_out);
        transition parse_ethernet;
    }

    state parse_ethernet {
        packet.extract(hdr.ethernet);
        transition select(hdr.ethernet.etherType) {
            TYPE_IPV4: parse_ipv4;
            default: accept;
        }
    }

   
    state parse_ipv4 {
        packet.extract(hdr.ipv4);
        transition select(hdr.ipv4.protocol) {
            PROTO_TCP: parse_tcp;
            PROTO_UDP: parse_udp;
            default: accept;
        }
    }

    state parse_udp{
        packet.extract(hdr.udp);
        transition select(hdr.udp.dstPort) {
            // if UDP_PORT_GTPU i.e. 2152 is present then parse gtpu header (on switch SGW and PGW)
            // UDP_PORT_GTPU : parse_gtpu;
            // else we are on DGW switch extract the data and take the decision accordingly
            default: parse_data;
        }
    }
  
    state parse_tcp{
        packet.extract(hdr.tcp);
        transition select(hdr.tcp.ctrl) {
            PSHACK : parse_control_ipv4;    // COntrol TCP stream carrying UDP data
            default : accept;   // normal TCP data packet
            //16 : accept;  // ACK
            //2 : accept;  // SYN
            //18 : accept; // SYN+ACK
            //1 : accept;  // FIN
            //17 : accept; // FIN+ACK
            //default : parse_control_ipv4;
        }
        // transition accept;
    }

    state parse_control_ipv4{
        packet.extract(hdr.control_ipv4);
        transition select(hdr.control_ipv4.protocol) {
            // PROTO_TCP: parse_tcp;
            PROTO_UDP: parse_control_udp;
            default: accept;
          
        }
    }

    state parse_control_udp{
        packet.extract(hdr.control_udp);
        transition parse_data;
        //transition select(hdr.control_udp.dstPort) {
        //    default: parse_data;
        //}
    }

    // state parse_gtpu {
    //     packet.extract(hdr.gtpu);
    //     transition parse_gtpu_ipv4;
    // }

    state parse_data{
        packet.extract(hdr.data);
        // transition accept;
        transition select(hdr.data.epc_traffic_code) {
            1  : parse_auth_step_one;
            3  : parse_auth_step_three;
            20 : parse_nas_step_two;
            5  : parse_send_apn;
            7  : parse_send_ue_teid;
            9  : parse_detach_req;
            14 : parse_ue_context_release;
            17 : parse_ue_service_req;
            19 : parse_initial_ctxt_setup_resp;
            // deafult is 12(request_starting_ip) so accept it 
            default : accept;
        }
    }
    state parse_auth_step_one{
        packet.extract(hdr.auth_step_one);
        transition accept;
    }

    state parse_auth_step_three{
        packet.extract(hdr.auth_step_three);
        transition accept;
    }

    state parse_nas_step_two{
        packet.extract(hdr.nas_step_two);
        transition accept;
    }

    state parse_send_apn{
        packet.extract(hdr.send_apn);
        transition accept;
    }

    state parse_send_ue_teid{
        packet.extract(hdr.send_ue_teid);
        transition accept;
    }

    state parse_detach_req{
        packet.extract(hdr.detach_req);
        transition accept;
    }
    
    state parse_ue_context_release{
        packet.extract(hdr.ue_context_rel_req);
        transition accept;
    }

    state parse_ue_service_req{
        packet.extract(hdr.ue_service_req);
        transition accept;
    }

    state parse_initial_ctxt_setup_resp{
        packet.extract(hdr.initial_ctxt_setup_resp);
        transition accept;
    }
}

/*************************************************************************
***********************  D E P A R S E R  *******************************
*************************************************************************/

control c_deparser(packet_out packet, in headers hdr) {
    apply {
        packet.emit(hdr.packet_in);
        packet.emit(hdr.packet_out);

        packet.emit(hdr.ethernet);
       
        packet.emit(hdr.ipv4);
        packet.emit(hdr.control_ipv4);
        packet.emit(hdr.tcp);
        packet.emit(hdr.udp);
        packet.emit(hdr.control_udp);

        packet.emit(hdr.data);
        // ATTACH messages
        packet.emit(hdr.auth_step_one);
        packet.emit(hdr.auth_step_three);
        packet.emit(hdr.nas_step_two);
        packet.emit(hdr.send_apn);
        packet.emit(hdr.send_ue_teid);
        //DETACH REQUEST
        packet.emit(hdr.detach_req);
        // CONTEXT RELEASE
        packet.emit(hdr.ue_context_rel_req);
        // SERVICE REQUEST
        packet.emit(hdr.ue_service_req);
        packet.emit(hdr.initial_ctxt_setup_resp);

        // @offload design send these messages to local onos 
        packet.emit(hdr.offload_ue_service_req);
        packet.emit(hdr.offload_initial_ctxt_setup_resp);

        // directly reply to RAN
        packet.emit(hdr.ue_context_rel_command);
        packet.emit(hdr.initial_ctxt_setup_req);
        packet.emit(hdr.attach_accept);
    
    }
}
#endif
