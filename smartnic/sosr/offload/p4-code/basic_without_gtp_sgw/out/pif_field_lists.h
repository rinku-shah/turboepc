/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_FIELD_LISTS_H__
#define __PIF_FIELD_LISTS_H__

/* Generated C source defining layout of field lists in memory */
/* Warning: your edits to this file may be lost */

struct pif_field_list_field_list_1 {
    union {
        struct {
            /* ipv4.srcAddr[32;0] */
            unsigned int __ipv4__srcAddr:32;
            /* ipv4.dstAddr[32;0] */
            unsigned int __ipv4__dstAddr:32;
            /* ipv4.totalLen[16;0] */
            unsigned int __ipv4__totalLen:16;
            /* ipv4.identification[16;0] */
            unsigned int __ipv4__identification:16;
            unsigned int _padding_0:3;
            /* ipv4.fragOffset[13;0] */
            unsigned int __ipv4__fragOffset:13;
            /* ipv4.diffserv[8;0] */
            unsigned int __ipv4__diffserv:8;
            /* ipv4.ttl[8;0] */
            unsigned int __ipv4__ttl:8;
            unsigned int _padding_1:13;
            /* ipv4.protocol[8;0] */
            unsigned int __ipv4__protocol:8;
            /* ipv4.version[4;0] */
            unsigned int __ipv4__version:4;
            /* ipv4.ihl[4;0] */
            unsigned int __ipv4__ihl:4;
            /* ipv4.flags[3;0] */
            unsigned int __ipv4__flags:3;
        };
        uint32_t _raw[5];
    };
};

struct pif_field_list_field_list_1_packed {
    union {
        __packed struct {
            /* ipv4.version[4;0] */
            unsigned int __ipv4__version:4;
            /* ipv4.ihl[4;4] */
            unsigned int __ipv4__ihl:4;
            /* ipv4.diffserv[8;8] */
            unsigned int __ipv4__diffserv:8;
            /* ipv4.totalLen[16;16] */
            unsigned int __ipv4__totalLen:16;
            /* ipv4.identification[16;32] */
            unsigned int __ipv4__identification:16;
            /* ipv4.flags[3;48] */
            unsigned int __ipv4__flags:3;
            /* ipv4.fragOffset[13;51] */
            unsigned int __ipv4__fragOffset:13;
            /* ipv4.ttl[8;64] */
            unsigned int __ipv4__ttl:8;
            /* ipv4.protocol[8;72] */
            unsigned int __ipv4__protocol:8;
            /* ipv4.srcAddr[32;80] */
            unsigned int __ipv4__srcAddr:32;
            /* ipv4.dstAddr[32;112] */
            unsigned int __ipv4__dstAddr:32;
            unsigned int _padding:16;
        };
        uint32_t _raw[5];
    };
};

struct pif_field_list_fl {
    union {
        struct {
            /* standard_metadata.clone_spec[32;0] */
            unsigned int __standard_metadata__clone_spec:32;
            /* standard_metadata.ingress_port[16;0] */
            unsigned int __standard_metadata__ingress_port:16;
            /* standard_metadata.egress_spec[16;0] */
            unsigned int __standard_metadata__egress_spec:16;
            unsigned int _padding_0:2;
            /* standard_metadata.egress_port[16;0] */
            unsigned int __standard_metadata__egress_port:16;
            /* standard_metadata.packet_length[14;0] */
            unsigned int __standard_metadata__packet_length:14;
            unsigned int _padding_1:6;
            /* standard_metadata.egress_instance[10;0] */
            unsigned int __standard_metadata__egress_instance:10;
            /* standard_metadata.parser_error_location[8;0] */
            unsigned int __standard_metadata__parser_error_location:8;
            /* standard_metadata.instance_type[4;0] */
            unsigned int __standard_metadata__instance_type:4;
            /* standard_metadata.parser_status[3;0] */
            unsigned int __standard_metadata__parser_status:3;
            /* standard_metadata.checksum_error[1;0] */
            unsigned int __standard_metadata__checksum_error:1;
        };
        uint32_t _raw[4];
    };
};

struct pif_field_list_fl_packed {
    union {
        __packed struct {
            /* standard_metadata.ingress_port[16;0] */
            unsigned int __standard_metadata__ingress_port:16;
            /* standard_metadata.packet_length[14;16] */
            unsigned int __standard_metadata__packet_length:14;
            /* standard_metadata.egress_spec[16;30] */
            unsigned int __standard_metadata__egress_spec:16;
            /* standard_metadata.egress_port[16;46] */
            unsigned int __standard_metadata__egress_port:16;
            /* standard_metadata.egress_instance[10;62] */
            unsigned int __standard_metadata__egress_instance:10;
            /* standard_metadata.instance_type[4;72] */
            unsigned int __standard_metadata__instance_type:4;
            /* standard_metadata.clone_spec[32;76] */
            unsigned int __standard_metadata__clone_spec:32;
            /* standard_metadata.parser_error_location[8;108] */
            unsigned int __standard_metadata__parser_error_location:8;
            /* standard_metadata.parser_status[3;116] */
            unsigned int __standard_metadata__parser_status:3;
            /* standard_metadata.checksum_error[1;119] */
            unsigned int __standard_metadata__checksum_error:1;
            unsigned int _padding:8;
        };
        uint32_t _raw[4];
    };
};

#endif /* __PIF_FIELD_LISTS_H__ */
