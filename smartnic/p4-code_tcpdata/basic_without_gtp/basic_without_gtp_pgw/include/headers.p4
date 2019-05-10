#ifndef __CUSTOM_HEADERS__
#define __CUSTOM_HEADERS__
#include "definitions.p4"

/*************************************************************************
*********************** H E A D E R S  ***********************************
*************************************************************************/

typedef bit<16>  egressSpec_t;
typedef bit<48> macAddr_t;
typedef bit<32> ip4Addr_t;
typedef bit<24>  code_t;

header ethernet_t {
    macAddr_t dstAddr;
    macAddr_t srcAddr;
    bit<16>   etherType;
}

header vlan_t{
        bit<3> pcp;
        bit<1> dei;
        bit<12> vid;
        bit<16> vlan_type;
}

header ipv4_t {
    bit<4>    version;
    bit<4>    ihl;
    bit<8>    diffserv;
    bit<16>   totalLen;
    bit<16>   identification;
    bit<3>    flags;
    bit<13>   fragOffset;
    bit<8>    ttl;
    bit<8>    protocol;
    bit<16>   hdrChecksum;
    ip4Addr_t srcAddr;
    ip4Addr_t dstAddr;
}

header udp_t {
    bit<16> srcPort;
    bit<16> dstPort;
    bit<16> length_;
    bit<16> checksum;
}

header tcp_t {
    bit<16> src_port;
    bit<16> dst_port;
    bit<32> seq_no;
    bit<32> ack_no;
    bit<4>  data_offset;
    bit<3>  res;
    bit<3>  ecn;
    bit<6>  ctrl;
    bit<16> window;
    bit<16> checksum;
    bit<16> urgent_ptr;
}


// header gtpu_t{
//     bit<3>  version;    /* version */
//     bit<1>  pt;         /* protocol type */
//     bit<1>  x;      /* reserved */
//     bit<1>  ex_flag;    /* next extension hdr present? */
//     bit<1>  seq_flag;   /* sequence no. */
//     bit<1>  npdu_flag;  /* n-pdn number present ? */
//     bit<8>  msgtype;    /* message type */
//     bit<16> msglen;     /* message length */
//     bit<32> teid;       /* tunnel endpoint id */

// }


// Packet-in header. Prepended to packets sent to the controller and used to
// carry the original ingress port where the packet was received.
@controller_header("packet_in")
header packet_in_header_t {
    bit<16> ingress_port;
}

// Packet-out header. Prepended to packets received by the controller and used
// to tell the switch on which port this packet should be forwarded.
@controller_header("packet_out")
header packet_out_header_t {
    bit<16> egress_port;
}
 
// this header will match on msg type and forward to controller or reply back as per msg type after a local table lookup
header data_t {
    bit<8> epc_traffic_code; // Auth-1:001, Auth-2:002, ...
    bit<48> sep;
}

// ATTACH messages
header auth_step_one_t{
    bit<32> imsi;
    bit<48> sep1;
    bit<8> ue_nw_capability;
    bit<48> sep2;
    bit<256> ksi_asme;   
    bit<48> sep3;
    bit<32> sqn;
    bit<48> sep4;
    bit<64> tai;
}

header auth_step_three_t{
    bit<32> imsi;
    bit<48> sep1;
    bit<64>res; 
}

header nas_step_two_t{
    bit<160> encrypted_hash;  
    bit<48> sep1;
    bit<32> imsi;
}

header send_apn_t{
    bit<64> apn;  
    bit<48>sep1;
    bit<32> key;   
}

header send_ue_teid_t{
    bit<32> ue_teid;  
    bit<48> sep1;
    bit<32> key; 
}

//DETACH REQUEST
header detach_req_t{
    bit<32> ue_ip;
    bit<48> sep1;
    bit<32> ue_teid;
    bit<48> sep2;
    bit<32> sgw_teid;
    bit<48> sep3;
    bit<32> ue_num;
}

// CONTEXT RELEASE
header ue_context_rel_req_t{
    bit<32> ue_ip;
    bit<48> sep1;
    bit<32> ue_teid;
    bit<48> sep2;
    bit<32> sgw_teid;
    bit<48> sep3;
    bit<32> ue_num;
}

// SERVICE REQUEST
header ue_service_req_t{
    bit<32> ue_key;
    bit<48> sep1;
    bit<32> ksi_asme;   
    bit<48> sep2;
    bit<32> ue_ip;
}
header initial_ctxt_setup_resp_t{
    bit<32> ue_teid;
    bit<48> sep1;
    bit<32> ue_key;
    bit<48> sep2;
    bit<32> ue_ip;
}

// @offload design we need to send sgw_teid along with the service request header to local onos for processing
header offload_ue_service_req_t{
    bit<32> ue_key;
    bit<48> sep1;
    bit<32> ksi_asme;   
    bit<48> sep2;
    bit<32> ue_ip;
    bit<48> sep3;
    bit<32> sgw_teid; 
}

header offload_initial_ctxt_setup_resp_t{
    bit<32> ue_teid;
    bit<48> sep1;
    bit<32> ue_key;
    bit<48> sep2;
    bit<32> ue_ip;
    bit<48> sep3;
    bit<32> sgw_teid; 
}

// Offload tables 
header uekey_uestate_t{
    bit<32> ue_key;
    bit<8> ue_state; 
}

header uekey_sgwteid_t{
    bit<32> ue_key;
    bit<32> sgw_teid; 
}

header uekey_guti_t{
    bit<32> ue_key;
    bit<32> guti; 
}

header ue_context_rel_command_t{
    bit<8> epc_traffic_code; 
    bit<48> sep1;
}

header initial_ctxt_setup_req_t{
    bit<8> epc_traffic_code; 
    bit<48> sep1;
    bit<32> sgw_teid; 
}

header attach_accept_t{
    bit<8> epc_traffic_code; 
    bit<48> sep1;
    bit<32> ue_key;
}

// key value header
header kv_t{
    bit<128> key1;
    bit<128> value;
}

header tmpvar_t{
    // used as tmp for swapping udp ports
    bit<16> tmpUdpPort; 
}

struct metadata {
    /* empty */
     
}

struct headers {
    packet_out_header_t packet_out;
    packet_in_header_t packet_in;
    ethernet_t   ethernet;
    vlan_t       vlan;
    ipv4_t       ipv4;
    udp_t       udp;
    tcp_t       tcp;
    // gtpu_t  gtpu;
    // ipv4_t  inner_ipv4;
    // ipv4_t  gtpu_ipv4;

    // udp_t   inner_udp;
    // tcp_t   inner_tcp;
    // udp_t   gtpu_udp;

    data_t     data;
    auth_step_one_t auth_step_one;
    auth_step_three_t auth_step_three;
    nas_step_two_t nas_step_two;
    send_apn_t send_apn;
    send_ue_teid_t send_ue_teid;
    detach_req_t detach_req;
    ue_context_rel_req_t ue_context_rel_req;
    ue_service_req_t ue_service_req;
    initial_ctxt_setup_resp_t initial_ctxt_setup_resp;

    // @offload design this request will go to local-onos
    offload_ue_service_req_t offload_ue_service_req;
    offload_initial_ctxt_setup_resp_t offload_initial_ctxt_setup_resp;

    // @offload design SGW will directly reply to RAN once cloning is implemented
    ue_context_rel_command_t ue_context_rel_command;
    initial_ctxt_setup_req_t initial_ctxt_setup_req;
    attach_accept_t attach_accept;

    // @offload design : these tables will be populated by root-onos controller
    uekey_uestate_t uekey_uestate;
    uekey_sgwteid_t uekey_sgwteid;
    uekey_guti_t uekey_guti;
    
    kv_t        kv;
    tmpvar_t tmpvar;
}
#endif
