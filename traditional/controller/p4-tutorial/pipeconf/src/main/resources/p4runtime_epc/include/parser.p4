#ifndef __PARSER__
#define __PARSER__
#include "definitions.p4"
/*************************************************************************
*********************** P A R S E R  ***********************************
*************************************************************************/

parser MyParser(packet_in packet,
                out headers hdr,
                inout metadata meta,
                inout standard_metadata_t standard_metadata) {

    state start {
        transition parse_ethernet;
    }

    state parse_ethernet {
        packet.extract(hdr.ethernet);
        transition select(hdr.ethernet.etherType) {
            TYPE_IPV4: parse_ipv4;
            TYPE_VLAN : parse_vlan;
            default: accept;
        }
    }

    state parse_vlan{
        packet.extract(hdr.vlan);
        transition select(hdr.vlan.vlan_type) {
            TYPE_IPV4: parse_ipv4;
            default : accept;
        }
    }
    state parse_ipv4 {
        packet.extract(hdr.ipv4);
        transition parse_udp;
    }

    state parse_udp{
        packet.extract(hdr.udp);
        transition parse_data;
    }

    state parse_data{
        packet.extract(hdr.data);
        transition select(hdr.data.epc_traffic_code) {
            CONTROLLER_PKT_TYPE  : parse_kv;
            3:parse_kv;
            default : accept;
        }
    }
    state parse_kv{
        packet.extract(hdr.kv);
        transition accept;
    }


}

/*************************************************************************
***********************  D E P A R S E R  *******************************
*************************************************************************/

control MyDeparser(packet_out packet, in headers hdr) {
    apply {
        packet.emit(hdr.ethernet);
        packet.emit(hdr.vlan);
        packet.emit(hdr.ipv4);
        packet.emit(hdr.udp);
        packet.emit(hdr.data);
        packet.emit(hdr.kv);

    }
}
#endif
