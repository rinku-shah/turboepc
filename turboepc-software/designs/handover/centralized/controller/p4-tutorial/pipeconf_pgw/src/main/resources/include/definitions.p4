#ifndef __DEFINE__
#define __DEFINE__
const bit<16> TYPE_IPV4 = 0x0800;
const bit<16> TYPE_VLAN = 0x8100;
const bit<9> CONTROLLER_PORT = 3;
const bit<24> CONTROLLER_PKT_TYPE = 2;
typedef bit<9> port_t;
const port_t CPU_PORT = 255;

#define IPV4_HDR_SIZE 20
const bit<8> DEFAULT_IPV4_TTL = 64;

//string format doesn't work
// const bit<32> s1u_dgw_addr = 192.168.2.2; 
// const bit<32> s1u_sgw_addr = 192.168.2.3;

// hex format works
const bit<32> s1u_dgw_addr = 0xC0A80202;
const bit<32> s1u_sgw_addr = 0xC0A80203;
const bit<32> s1u_pgw_addr =0xC0A80304;

const bit<48> ran1 = 0x00163ec6a2aa;
const bit<48> ran2 = 0x00163e982233;
const bit<48> ran3 = 0x00163e5f329a;
const bit<48> ran4 = 0x00163e73d06d;
const bit<48> ran5 = 0x00163e8dccbe;
const bit<48> ran6 = 0x00163e714c4f;
const bit<48> bcast = 0xffffffffffff;

const bit<48> sink = 0x00163ede0a60;
const bit<48> pgw = 0x00163e48994c;


const bit<32> sink_ip =0xC0A80405;


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

#endif
