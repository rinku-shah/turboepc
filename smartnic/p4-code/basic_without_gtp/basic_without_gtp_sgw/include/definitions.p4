#ifndef __DEFINE__
#define __DEFINE__
const bit<16> TYPE_IPV4 = 0x0800;
const bit<16> TYPE_VLAN = 0x8100;
const bit<16> TYPE_ARP = 0x0806;
const bit<9> CONTROLLER_PORT = 3;
const bit<24> CONTROLLER_PKT_TYPE = 2;
const bit<32> CLONE_SESSION_ID = 500;
typedef bit<16> port_t;
// @vikas : in hardware implemetation, at SGW the contoller is sniffing packet on SGW port v0.0 (768)
const port_t CPU_PORT = 768;

const bit<8> DEFAULT_IPV4_TTL = 64;

//string format doesn't work
// const bit<32> s1u_dgw_addr = 192.168.2.2; 
// const bit<32> s1u_sgw_addr = 192.168.2.3;

// hex format works

const bit<32> s1u_dgw_addr = 0xC0A80202;

// IP address of 1st,2nd,3rd,3th chains in SGW
// s1u - 1st chain
// s2u - 2nd chain
// s3u - 3rd chain
// s4u - 4th chain

const bit<32> s1u_sgw_addr = 0xC0A80203;
const bit<32> s2u_sgw_addr = 0xC0A80603;
const bit<32> s3u_sgw_addr = 0xC0A80803;
const bit<32> s4u_sgw_addr = 0xC0A80C03;
const bit<32> s5u_sgw_addr = 0xC0A80F03;
const bit<32> s6u_sgw_addr = 0xC0A81103;


const bit<32> s1u_pgw_addr =0xC0A80304;

const bit<32> sink_ip =0xC0A80405;

// MAC addresses of RANs
const bit<48> ran1 = 0x00163ec6a2aa;
const bit<48> ran2 = 0x00163e982233;
const bit<48> ran3 = 0x00163e5f329a;
const bit<48> ran4 = 0x00163e73d06d;
const bit<48> ran5 = 0x00163e8dccbe;
const bit<48> ran6 = 0x00163e714c4f;

// MAC addresses of SGWs
const bit<48> sgw1 = 0x00163e1f04f2;
const bit<48> sgw2 = 0x00163e3f0d83;
const bit<48> sgw3 = 0x00163ee0eb61;
const bit<48> sgw4 = 0x00163e4c02a8;
const bit<48> sgw5 = 0x00163ee90a21;
const bit<48> sgw6 = 0x00163edf5287;


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

const bit<4> BMV2_V1MODEL_INSTANCE_TYPE_NORMAL        = 0;
const bit<4> BMV2_V1MODEL_INSTANCE_TYPE_INGRESS_CLONE = 1;
const bit<4> BMV2_V1MODEL_INSTANCE_TYPE_EGRESS_CLONE  = 2;
const bit<4> BMV2_V1MODEL_INSTANCE_TYPE_COALESCED     = 3;
const bit<4> BMV2_V1MODEL_INSTANCE_TYPE_RECIRC        = 4;
const bit<4> BMV2_V1MODEL_INSTANCE_TYPE_REPLICATION   = 5;
const bit<4> BMV2_V1MODEL_INSTANCE_TYPE_RESUBMIT      = 6;

const bit<32> I2E_CLONE_SESSION_ID = 500;

#endif
