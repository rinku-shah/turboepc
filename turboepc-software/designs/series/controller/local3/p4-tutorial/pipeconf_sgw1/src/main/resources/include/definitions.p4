#ifndef __DEFINE__
#define __DEFINE__
const bit<16> TYPE_IPV4 = 0x0800;
const bit<16> TYPE_VLAN = 0x8100;
const bit<9> CONTROLLER_PORT = 3;
const bit<24> CONTROLLER_PKT_TYPE = 2;
const bit<32> CLONE_SESSION_ID = 500;
typedef bit<9> port_t;
const port_t CPU_PORT = 255;

const bit<8> DEFAULT_IPV4_TTL = 64;

//string format doesn't work
// const bit<32> s1u_dgw_addr = 192.168.2.2; 
// const bit<32> s1u_sgw_addr = 192.168.2.3;

// hex format works

const bit<32> s1u_dgw_ipaddr = 0xc0a80201;  // 192.168.2.1


// IP address of 1st,2nd,3rd,3th chains in SGW
// s11,s12 - 1st chain
// s21,s22 - 2nd chain
// s31,s32 - 3rd chain
// s41,s42 - 4th chain

const bit<32> s11_sgw_ipaddr = 0xc0a80202;  //192.168.2.2
const bit<32> s12_sgw_ipaddr = 0xc0a80302;  //192.168.3.2
const bit<32> s13_sgw_ipaddr = 0xc0a80402; //192.168.4.2
const bit<32> s22_sgw_ipaddr = 0xc0a80702; //192.168.7.2
const bit<32> s31_sgw_ipaddr = 0xc0a80a02;  //192.168.10.2
const bit<32> s32_sgw_ipaddr = 0xc0a80b02; //192.168.11.2
const bit<32> s41_sgw_ipaddr = 0xc0a80e02;  // 192.168.14.2
const bit<32> s42_sgw_ipaddr = 0xc0a80f02; //192.168.15.2


const bit<32> sink_ip =0xc0a81502;  // 192.168.21.2


// MAC addresses of SGWs
const bit<48> sgw11 = 0x00163e416103;
const bit<48> sgw12 = 0x00163e8f0eae;
//const bit<48> sgw21 = 0x00163e73b569;
const bit<48> sgw13 = 0x00163e750e1c;

const bit<48> sgw31 = 0x00163e362217;
const bit<48> sgw32 = 0x00163e65bbf4;
const bit<48> sgw41 = 0x00163e4646a8;
const bit<48> sgw42 = 0x00163e2fd5eb;

// MAC addresses of RANs
const bit<48> ran1 = 0x00163ec6a2aa;
const bit<48> ran2 = 0x00163e982233;
const bit<48> ran3 = 0x00163e5f329a;
const bit<48> ran4 = 0x00163e73d06d;
const bit<48> ran5 = 0x00163e8dccbe;
const bit<48> ran6 = 0x00163e714c4f;


const bit<48> pgw = 0x00163e48994c;

const bit<48> sink = 0x00163ede0a60;

const bit<48> bcast = 0xffffffffffff;

#define IPV4_HDR_SIZE 20
#define UDP_HDR_SIZE 8
#define GTP_HDR_SIZE 8

#define IP_VERSION_4 4
const bit<4> IPV4_MIN_IHL = 5;

const bit<8> PROTO_UDP = 17;
const bit<8> PROTO_TCP = 6;

// GTP 
#define UDP_PORT_GTPU 2152
#define GTPU_VERSION 0x01
#define GTP_PROTOCOL_TYPE_GTP 0x01
#define GTP_GPDU 0xff


// These definitions are derived from the numerical values of the enum
// named "PktInstanceType" in the p4lang/behavioral-model source file
// targets/simple_switch/simple_switch.h

// https://github.com/p4lang/behavioral-model/blob/master/targets/simple_switch/simple_switch.h#L126-L134

const bit<32> BMV2_V1MODEL_INSTANCE_TYPE_NORMAL        = 0;
const bit<32> BMV2_V1MODEL_INSTANCE_TYPE_INGRESS_CLONE = 1;
const bit<32> BMV2_V1MODEL_INSTANCE_TYPE_EGRESS_CLONE  = 2;
const bit<32> BMV2_V1MODEL_INSTANCE_TYPE_COALESCED     = 3;
const bit<32> BMV2_V1MODEL_INSTANCE_TYPE_RECIRC        = 4;
const bit<32> BMV2_V1MODEL_INSTANCE_TYPE_REPLICATION   = 5;
const bit<32> BMV2_V1MODEL_INSTANCE_TYPE_RESUBMIT      = 6;

const bit<32> I2E_CLONE_SESSION_ID = 500;


const bit<32> LB11 = 100;
const bit<32> UB11 = 124;
const bit<32> LB12 = 125;
const bit<32> UB12 = 149;
const bit<32> LB13 = 150;
const bit<32> UB13 = 174;

#endif
