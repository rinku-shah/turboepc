#ifndef __CUSTOM_HEADERS__
#define __CUSTOM_HEADERS__
#include "definitions.p4"

/*************************************************************************
*********************** H E A D E R S  ***********************************
*************************************************************************/

typedef bit<9>  egressSpec_t;
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

header data_t {
    code_t epc_traffic_code; // Auth-1:001, Auth-2:002, ...
}
// key valuse header
header kv_t{
    // key is of 16Bytes
    bit<128> key1;
    bit<128> value;
}
// header s1_ip_op_tunnel_t{
//     bit<128> ip_tunnel_s1;
//     bit<128> op_tunnel_s1;
// }
//
// header s1_ip_tunnel_egress_t{
//     bit<128> ip_tunnel_s1;
//     bit<9> egress_port_s1;
// }
//
// header s2_ip_op_tunnel_t{
//     bit<128> ip_tunnel_s2;
//     bit<128> op_tunnel_s2;
// }
//
// header s2_ip_tunnel_egress_t{
//     bit<128> ip_tunnel_s2;
//     bit<9> egress_port_s2;
// }
//
// header s3_ip_tunnel_egress_t{
//     bit<128> ip_tunnel_s3;
//     bit<9> egress_port_s3;
// }

struct metadata {
    /* empty */
}

struct headers {
    ethernet_t   ethernet;
    vlan_t       vlan;
    ipv4_t       ipv4;
    udp_t       udp;
    data_t     data;
    kv_t        kv;
    // s1_ip_op_tunnel_t s1_ip_op_tunnel;
    // s1_ip_tunnel_egress_t s1_ip_tunnel_egress;
    // s2_ip_op_tunnel_t s2_ip_op_tunnel;
    // s2_ip_tunnel_egress_t s2_ip_tunnel_egress;
    // s3_ip_tunnel_egress_t s3_ip_tunnel_egress;
}
#endif
