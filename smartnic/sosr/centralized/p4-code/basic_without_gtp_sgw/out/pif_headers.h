/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_HEADERS_H__
#define __PIF_HEADERS_H__

/* Generated C source defining PIF headers, metadata and registers */
/* Warning: your edits to this file may be lost */

/*
 * Packet headers
 */

/* ue_context_rel_req (34B) */
struct pif_header_ue_context_rel_req {
    unsigned int ue_ip:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* ue_teid [16;16] */
    unsigned int ue_teid:16;
    /* ue_teid [16;0] */
    unsigned int __ue_teid_1:16;
    /* sep2 [16;32] */
    unsigned int sep2:16;
    /* sep2 [32;0] */
    unsigned int __sep2_1:32;
    unsigned int sgw_teid:32;
    /* sep3 [32;16] */
    unsigned int sep3:32;
    /* sep3 [16;0] */
    unsigned int __sep3_1:16;
    /* ue_num [16;16] */
    unsigned int ue_num:16;
    /* ue_num [16;0] */
    unsigned int __ue_num_1:16;
};

/* ue_context_rel_req field accessor macros */
#define PIF_HEADER_GET_ue_context_rel_req___ue_ip(_hdr_p) (((_hdr_p)->ue_ip)) /* ue_context_rel_req.ue_ip [32;0] */

#define PIF_HEADER_SET_ue_context_rel_req___ue_ip(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_ip = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_req.ue_ip[32;0] */

#define PIF_HEADER_GET_ue_context_rel_req___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* ue_context_rel_req.sep1 [32;0] */

#define PIF_HEADER_SET_ue_context_rel_req___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_req.sep1[32;0] */

#define PIF_HEADER_GET_ue_context_rel_req___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* ue_context_rel_req.sep1 [16;32] */

#define PIF_HEADER_SET_ue_context_rel_req___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* ue_context_rel_req.sep1[16;32] */

#define PIF_HEADER_GET_ue_context_rel_req___ue_teid(_hdr_p) (((_hdr_p)->ue_teid << 16) | ((_hdr_p)->__ue_teid_1)) /* ue_context_rel_req.ue_teid [32;0] */

#define PIF_HEADER_SET_ue_context_rel_req___ue_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_teid = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__ue_teid_1 = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_req.ue_teid[32;0] */

#define PIF_HEADER_GET_ue_context_rel_req___sep2___0(_hdr_p) (((_hdr_p)->__sep2_1)) /* ue_context_rel_req.sep2 [32;0] */

#define PIF_HEADER_SET_ue_context_rel_req___sep2___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__sep2_1 = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_req.sep2[32;0] */

#define PIF_HEADER_GET_ue_context_rel_req___sep2___1(_hdr_p) (((_hdr_p)->sep2)) /* ue_context_rel_req.sep2 [16;32] */

#define PIF_HEADER_SET_ue_context_rel_req___sep2___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep2 = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_req.sep2[16;32] */

#define PIF_HEADER_GET_ue_context_rel_req___sgw_teid(_hdr_p) (((_hdr_p)->sgw_teid)) /* ue_context_rel_req.sgw_teid [32;0] */

#define PIF_HEADER_SET_ue_context_rel_req___sgw_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->sgw_teid = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_req.sgw_teid[32;0] */

#define PIF_HEADER_GET_ue_context_rel_req___sep3___0(_hdr_p) ((((_hdr_p)->sep3 & 0xffff) << 16) | ((_hdr_p)->__sep3_1)) /* ue_context_rel_req.sep3 [32;0] */

#define PIF_HEADER_SET_ue_context_rel_req___sep3___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep3_1 = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_req.sep3[32;0] */

#define PIF_HEADER_GET_ue_context_rel_req___sep3___1(_hdr_p) ((((_hdr_p)->sep3 >> 16) & 0xffff)) /* ue_context_rel_req.sep3 [16;32] */

#define PIF_HEADER_SET_ue_context_rel_req___sep3___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xffff); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* ue_context_rel_req.sep3[16;32] */

#define PIF_HEADER_GET_ue_context_rel_req___ue_num(_hdr_p) (((_hdr_p)->ue_num << 16) | ((_hdr_p)->__ue_num_1)) /* ue_context_rel_req.ue_num [32;0] */

#define PIF_HEADER_SET_ue_context_rel_req___ue_num(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_num = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__ue_num_1 = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_req.ue_num[32;0] */


/* initial_ctxt_setup_resp (24B) */
struct pif_header_initial_ctxt_setup_resp {
    unsigned int ue_teid:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* ue_key [16;16] */
    unsigned int ue_key:16;
    /* ue_key [16;0] */
    unsigned int __ue_key_1:16;
    /* sep2 [16;32] */
    unsigned int sep2:16;
    /* sep2 [32;0] */
    unsigned int __sep2_1:32;
    unsigned int ue_ip:32;
};

/* initial_ctxt_setup_resp field accessor macros */
#define PIF_HEADER_GET_initial_ctxt_setup_resp___ue_teid(_hdr_p) (((_hdr_p)->ue_teid)) /* initial_ctxt_setup_resp.ue_teid [32;0] */

#define PIF_HEADER_SET_initial_ctxt_setup_resp___ue_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_teid = (unsigned)(((_val))); \
    } while (0) /* initial_ctxt_setup_resp.ue_teid[32;0] */

#define PIF_HEADER_GET_initial_ctxt_setup_resp___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* initial_ctxt_setup_resp.sep1 [32;0] */

#define PIF_HEADER_SET_initial_ctxt_setup_resp___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* initial_ctxt_setup_resp.sep1[32;0] */

#define PIF_HEADER_GET_initial_ctxt_setup_resp___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* initial_ctxt_setup_resp.sep1 [16;32] */

#define PIF_HEADER_SET_initial_ctxt_setup_resp___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* initial_ctxt_setup_resp.sep1[16;32] */

#define PIF_HEADER_GET_initial_ctxt_setup_resp___ue_key(_hdr_p) (((_hdr_p)->ue_key << 16) | ((_hdr_p)->__ue_key_1)) /* initial_ctxt_setup_resp.ue_key [32;0] */

#define PIF_HEADER_SET_initial_ctxt_setup_resp___ue_key(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_key = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__ue_key_1 = (unsigned)(((_val))); \
    } while (0) /* initial_ctxt_setup_resp.ue_key[32;0] */

#define PIF_HEADER_GET_initial_ctxt_setup_resp___sep2___0(_hdr_p) (((_hdr_p)->__sep2_1)) /* initial_ctxt_setup_resp.sep2 [32;0] */

#define PIF_HEADER_SET_initial_ctxt_setup_resp___sep2___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__sep2_1 = (unsigned)(((_val))); \
    } while (0) /* initial_ctxt_setup_resp.sep2[32;0] */

#define PIF_HEADER_GET_initial_ctxt_setup_resp___sep2___1(_hdr_p) (((_hdr_p)->sep2)) /* initial_ctxt_setup_resp.sep2 [16;32] */

#define PIF_HEADER_SET_initial_ctxt_setup_resp___sep2___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep2 = (unsigned)(((_val))); \
    } while (0) /* initial_ctxt_setup_resp.sep2[16;32] */

#define PIF_HEADER_GET_initial_ctxt_setup_resp___ue_ip(_hdr_p) (((_hdr_p)->ue_ip)) /* initial_ctxt_setup_resp.ue_ip [32;0] */

#define PIF_HEADER_SET_initial_ctxt_setup_resp___ue_ip(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_ip = (unsigned)(((_val))); \
    } while (0) /* initial_ctxt_setup_resp.ue_ip[32;0] */


/* tcp (20B) */
struct pif_header_tcp {
    unsigned int src_port:16;
    unsigned int dst_port:16;
    unsigned int seq_no:32;
    unsigned int ack_no:32;
    unsigned int data_offset:4;
    unsigned int res:3;
    unsigned int ecn:3;
    unsigned int ctrl:6;
    unsigned int window:16;
    unsigned int checksum:16;
    unsigned int urgent_ptr:16;
};

/* tcp field accessor macros */
#define PIF_HEADER_GET_tcp___src_port(_hdr_p) (((_hdr_p)->src_port)) /* tcp.src_port [16;0] */

#define PIF_HEADER_SET_tcp___src_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->src_port = (unsigned)(((_val))); \
    } while (0) /* tcp.src_port[16;0] */

#define PIF_HEADER_GET_tcp___dst_port(_hdr_p) (((_hdr_p)->dst_port)) /* tcp.dst_port [16;0] */

#define PIF_HEADER_SET_tcp___dst_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->dst_port = (unsigned)(((_val))); \
    } while (0) /* tcp.dst_port[16;0] */

#define PIF_HEADER_GET_tcp___seq_no(_hdr_p) (((_hdr_p)->seq_no)) /* tcp.seq_no [32;0] */

#define PIF_HEADER_SET_tcp___seq_no(_hdr_p, _val) \
    do { \
        (_hdr_p)->seq_no = (unsigned)(((_val))); \
    } while (0) /* tcp.seq_no[32;0] */

#define PIF_HEADER_GET_tcp___ack_no(_hdr_p) (((_hdr_p)->ack_no)) /* tcp.ack_no [32;0] */

#define PIF_HEADER_SET_tcp___ack_no(_hdr_p, _val) \
    do { \
        (_hdr_p)->ack_no = (unsigned)(((_val))); \
    } while (0) /* tcp.ack_no[32;0] */

#define PIF_HEADER_GET_tcp___data_offset(_hdr_p) (((_hdr_p)->data_offset)) /* tcp.data_offset [4;0] */

#define PIF_HEADER_SET_tcp___data_offset(_hdr_p, _val) \
    do { \
        (_hdr_p)->data_offset = (unsigned)(((_val))); \
    } while (0) /* tcp.data_offset[4;0] */

#define PIF_HEADER_GET_tcp___res(_hdr_p) (((_hdr_p)->res)) /* tcp.res [3;0] */

#define PIF_HEADER_SET_tcp___res(_hdr_p, _val) \
    do { \
        (_hdr_p)->res = (unsigned)(((_val))); \
    } while (0) /* tcp.res[3;0] */

#define PIF_HEADER_GET_tcp___ecn(_hdr_p) (((_hdr_p)->ecn)) /* tcp.ecn [3;0] */

#define PIF_HEADER_SET_tcp___ecn(_hdr_p, _val) \
    do { \
        (_hdr_p)->ecn = (unsigned)(((_val))); \
    } while (0) /* tcp.ecn[3;0] */

#define PIF_HEADER_GET_tcp___ctrl(_hdr_p) (((_hdr_p)->ctrl)) /* tcp.ctrl [6;0] */

#define PIF_HEADER_SET_tcp___ctrl(_hdr_p, _val) \
    do { \
        (_hdr_p)->ctrl = (unsigned)(((_val))); \
    } while (0) /* tcp.ctrl[6;0] */

#define PIF_HEADER_GET_tcp___window(_hdr_p) (((_hdr_p)->window)) /* tcp.window [16;0] */

#define PIF_HEADER_SET_tcp___window(_hdr_p, _val) \
    do { \
        (_hdr_p)->window = (unsigned)(((_val))); \
    } while (0) /* tcp.window[16;0] */

#define PIF_HEADER_GET_tcp___checksum(_hdr_p) (((_hdr_p)->checksum)) /* tcp.checksum [16;0] */

#define PIF_HEADER_SET_tcp___checksum(_hdr_p, _val) \
    do { \
        (_hdr_p)->checksum = (unsigned)(((_val))); \
    } while (0) /* tcp.checksum[16;0] */

#define PIF_HEADER_GET_tcp___urgent_ptr(_hdr_p) (((_hdr_p)->urgent_ptr)) /* tcp.urgent_ptr [16;0] */

#define PIF_HEADER_SET_tcp___urgent_ptr(_hdr_p, _val) \
    do { \
        (_hdr_p)->urgent_ptr = (unsigned)(((_val))); \
    } while (0) /* tcp.urgent_ptr[16;0] */


/* packet_in (2B) */
struct pif_header_packet_in {
    unsigned int ingress_port:16;
};

/* packet_in field accessor macros */
#define PIF_HEADER_GET_packet_in___ingress_port(_hdr_p) (((_hdr_p)->ingress_port)) /* packet_in.ingress_port [16;0] */

#define PIF_HEADER_SET_packet_in___ingress_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->ingress_port = (unsigned)(((_val))); \
    } while (0) /* packet_in.ingress_port[16;0] */


/* offload_initial_ctxt_setup_resp (34B) */
struct pif_header_offload_initial_ctxt_setup_resp {
    unsigned int ue_teid:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* ue_key [16;16] */
    unsigned int ue_key:16;
    /* ue_key [16;0] */
    unsigned int __ue_key_1:16;
    /* sep2 [16;32] */
    unsigned int sep2:16;
    /* sep2 [32;0] */
    unsigned int __sep2_1:32;
    unsigned int ue_ip:32;
    /* sep3 [32;16] */
    unsigned int sep3:32;
    /* sep3 [16;0] */
    unsigned int __sep3_1:16;
    /* sgw_teid [16;16] */
    unsigned int sgw_teid:16;
    /* sgw_teid [16;0] */
    unsigned int __sgw_teid_1:16;
};

/* offload_initial_ctxt_setup_resp field accessor macros */
#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___ue_teid(_hdr_p) (((_hdr_p)->ue_teid)) /* offload_initial_ctxt_setup_resp.ue_teid [32;0] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___ue_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_teid = (unsigned)(((_val))); \
    } while (0) /* offload_initial_ctxt_setup_resp.ue_teid[32;0] */

#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* offload_initial_ctxt_setup_resp.sep1 [32;0] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* offload_initial_ctxt_setup_resp.sep1[32;0] */

#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* offload_initial_ctxt_setup_resp.sep1 [16;32] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* offload_initial_ctxt_setup_resp.sep1[16;32] */

#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___ue_key(_hdr_p) (((_hdr_p)->ue_key << 16) | ((_hdr_p)->__ue_key_1)) /* offload_initial_ctxt_setup_resp.ue_key [32;0] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___ue_key(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_key = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__ue_key_1 = (unsigned)(((_val))); \
    } while (0) /* offload_initial_ctxt_setup_resp.ue_key[32;0] */

#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___sep2___0(_hdr_p) (((_hdr_p)->__sep2_1)) /* offload_initial_ctxt_setup_resp.sep2 [32;0] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___sep2___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__sep2_1 = (unsigned)(((_val))); \
    } while (0) /* offload_initial_ctxt_setup_resp.sep2[32;0] */

#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___sep2___1(_hdr_p) (((_hdr_p)->sep2)) /* offload_initial_ctxt_setup_resp.sep2 [16;32] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___sep2___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep2 = (unsigned)(((_val))); \
    } while (0) /* offload_initial_ctxt_setup_resp.sep2[16;32] */

#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___ue_ip(_hdr_p) (((_hdr_p)->ue_ip)) /* offload_initial_ctxt_setup_resp.ue_ip [32;0] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___ue_ip(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_ip = (unsigned)(((_val))); \
    } while (0) /* offload_initial_ctxt_setup_resp.ue_ip[32;0] */

#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___sep3___0(_hdr_p) ((((_hdr_p)->sep3 & 0xffff) << 16) | ((_hdr_p)->__sep3_1)) /* offload_initial_ctxt_setup_resp.sep3 [32;0] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___sep3___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep3_1 = (unsigned)(((_val))); \
    } while (0) /* offload_initial_ctxt_setup_resp.sep3[32;0] */

#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___sep3___1(_hdr_p) ((((_hdr_p)->sep3 >> 16) & 0xffff)) /* offload_initial_ctxt_setup_resp.sep3 [16;32] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___sep3___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xffff); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* offload_initial_ctxt_setup_resp.sep3[16;32] */

#define PIF_HEADER_GET_offload_initial_ctxt_setup_resp___sgw_teid(_hdr_p) (((_hdr_p)->sgw_teid << 16) | ((_hdr_p)->__sgw_teid_1)) /* offload_initial_ctxt_setup_resp.sgw_teid [32;0] */

#define PIF_HEADER_SET_offload_initial_ctxt_setup_resp___sgw_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->sgw_teid = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__sgw_teid_1 = (unsigned)(((_val))); \
    } while (0) /* offload_initial_ctxt_setup_resp.sgw_teid[32;0] */


/* initial_ctxt_setup_req (11B) */
struct pif_header_initial_ctxt_setup_req {
    unsigned int epc_traffic_code:8;
    /* sep1 [24;24] */
    unsigned int sep1:24;
    /* sep1 [24;0] */
    unsigned int __sep1_1:24;
    /* sgw_teid [8;24] */
    unsigned int sgw_teid:8;
    /* sgw_teid [24;0] */
    unsigned int __sgw_teid_1:24;
};

/* initial_ctxt_setup_req field accessor macros */
#define PIF_HEADER_GET_initial_ctxt_setup_req___epc_traffic_code(_hdr_p) (((_hdr_p)->epc_traffic_code)) /* initial_ctxt_setup_req.epc_traffic_code [8;0] */

#define PIF_HEADER_SET_initial_ctxt_setup_req___epc_traffic_code(_hdr_p, _val) \
    do { \
        (_hdr_p)->epc_traffic_code = (unsigned)(((_val))); \
    } while (0) /* initial_ctxt_setup_req.epc_traffic_code[8;0] */

#define PIF_HEADER_GET_initial_ctxt_setup_req___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xff) << 24) | ((_hdr_p)->__sep1_1)) /* initial_ctxt_setup_req.sep1 [32;0] */

#define PIF_HEADER_SET_initial_ctxt_setup_req___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffffff00); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 24) & 0xff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* initial_ctxt_setup_req.sep1[32;0] */

#define PIF_HEADER_GET_initial_ctxt_setup_req___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 8) & 0xffff)) /* initial_ctxt_setup_req.sep1 [16;32] */

#define PIF_HEADER_SET_initial_ctxt_setup_req___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xff0000ff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 8)); \
    } while (0) /* initial_ctxt_setup_req.sep1[16;32] */

#define PIF_HEADER_GET_initial_ctxt_setup_req___sgw_teid(_hdr_p) (((_hdr_p)->sgw_teid << 24) | ((_hdr_p)->__sgw_teid_1)) /* initial_ctxt_setup_req.sgw_teid [32;0] */

#define PIF_HEADER_SET_initial_ctxt_setup_req___sgw_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->sgw_teid = (unsigned)(((_val) >> 24)); \
        (_hdr_p)->__sgw_teid_1 = (unsigned)(((_val))); \
    } while (0) /* initial_ctxt_setup_req.sgw_teid[32;0] */


/* auth_step_three (18B) */
struct pif_header_auth_step_three {
    unsigned int imsi:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* res [16;48] */
    unsigned int res:16;
    /* res [32;16] */
    unsigned int __res_1:32;
    /* res [16;0] */
    unsigned int __res_2:16;
};

/* auth_step_three field accessor macros */
#define PIF_HEADER_GET_auth_step_three___imsi(_hdr_p) (((_hdr_p)->imsi)) /* auth_step_three.imsi [32;0] */

#define PIF_HEADER_SET_auth_step_three___imsi(_hdr_p, _val) \
    do { \
        (_hdr_p)->imsi = (unsigned)(((_val))); \
    } while (0) /* auth_step_three.imsi[32;0] */

#define PIF_HEADER_GET_auth_step_three___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* auth_step_three.sep1 [32;0] */

#define PIF_HEADER_SET_auth_step_three___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* auth_step_three.sep1[32;0] */

#define PIF_HEADER_GET_auth_step_three___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* auth_step_three.sep1 [16;32] */

#define PIF_HEADER_SET_auth_step_three___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* auth_step_three.sep1[16;32] */

#define PIF_HEADER_GET_auth_step_three___res___0(_hdr_p) ((((_hdr_p)->__res_1 & 0xffff) << 16) | ((_hdr_p)->__res_2)) /* auth_step_three.res [32;0] */

#define PIF_HEADER_SET_auth_step_three___res___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__res_1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->__res_1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__res_2 = (unsigned)(((_val))); \
    } while (0) /* auth_step_three.res[32;0] */

#define PIF_HEADER_GET_auth_step_three___res___1(_hdr_p) (((_hdr_p)->res << 16) | (((_hdr_p)->__res_1 >> 16) & 0xffff)) /* auth_step_three.res [32;32] */

#define PIF_HEADER_SET_auth_step_three___res___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->res = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__res_1 &= (unsigned)(0xffff); \
        (_hdr_p)->__res_1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* auth_step_three.res[32;32] */


/* ue_context_rel_command (7B) */
struct pif_header_ue_context_rel_command {
    unsigned int epc_traffic_code:8;
    /* sep1 [24;24] */
    unsigned int sep1:24;
    /* sep1 [24;0] */
    unsigned int __sep1_1:24;
};

/* ue_context_rel_command field accessor macros */
#define PIF_HEADER_GET_ue_context_rel_command___epc_traffic_code(_hdr_p) (((_hdr_p)->epc_traffic_code)) /* ue_context_rel_command.epc_traffic_code [8;0] */

#define PIF_HEADER_SET_ue_context_rel_command___epc_traffic_code(_hdr_p, _val) \
    do { \
        (_hdr_p)->epc_traffic_code = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_command.epc_traffic_code[8;0] */

#define PIF_HEADER_GET_ue_context_rel_command___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xff) << 24) | ((_hdr_p)->__sep1_1)) /* ue_context_rel_command.sep1 [32;0] */

#define PIF_HEADER_SET_ue_context_rel_command___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffffff00); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 24) & 0xff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_command.sep1[32;0] */

#define PIF_HEADER_GET_ue_context_rel_command___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 8) & 0xffff)) /* ue_context_rel_command.sep1 [16;32] */

#define PIF_HEADER_SET_ue_context_rel_command___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xff0000ff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 8)); \
    } while (0) /* ue_context_rel_command.sep1[16;32] */


/* attach_accept (11B) */
struct pif_header_attach_accept {
    unsigned int epc_traffic_code:8;
    /* sep1 [24;24] */
    unsigned int sep1:24;
    /* sep1 [24;0] */
    unsigned int __sep1_1:24;
    /* ue_key [8;24] */
    unsigned int ue_key:8;
    /* ue_key [24;0] */
    unsigned int __ue_key_1:24;
};

/* attach_accept field accessor macros */
#define PIF_HEADER_GET_attach_accept___epc_traffic_code(_hdr_p) (((_hdr_p)->epc_traffic_code)) /* attach_accept.epc_traffic_code [8;0] */

#define PIF_HEADER_SET_attach_accept___epc_traffic_code(_hdr_p, _val) \
    do { \
        (_hdr_p)->epc_traffic_code = (unsigned)(((_val))); \
    } while (0) /* attach_accept.epc_traffic_code[8;0] */

#define PIF_HEADER_GET_attach_accept___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xff) << 24) | ((_hdr_p)->__sep1_1)) /* attach_accept.sep1 [32;0] */

#define PIF_HEADER_SET_attach_accept___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffffff00); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 24) & 0xff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* attach_accept.sep1[32;0] */

#define PIF_HEADER_GET_attach_accept___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 8) & 0xffff)) /* attach_accept.sep1 [16;32] */

#define PIF_HEADER_SET_attach_accept___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xff0000ff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 8)); \
    } while (0) /* attach_accept.sep1[16;32] */

#define PIF_HEADER_GET_attach_accept___ue_key(_hdr_p) (((_hdr_p)->ue_key << 24) | ((_hdr_p)->__ue_key_1)) /* attach_accept.ue_key [32;0] */

#define PIF_HEADER_SET_attach_accept___ue_key(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_key = (unsigned)(((_val) >> 24)); \
        (_hdr_p)->__ue_key_1 = (unsigned)(((_val))); \
    } while (0) /* attach_accept.ue_key[32;0] */


/* detach_req (34B) */
struct pif_header_detach_req {
    unsigned int ue_ip:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* ue_teid [16;16] */
    unsigned int ue_teid:16;
    /* ue_teid [16;0] */
    unsigned int __ue_teid_1:16;
    /* sep2 [16;32] */
    unsigned int sep2:16;
    /* sep2 [32;0] */
    unsigned int __sep2_1:32;
    unsigned int sgw_teid:32;
    /* sep3 [32;16] */
    unsigned int sep3:32;
    /* sep3 [16;0] */
    unsigned int __sep3_1:16;
    /* ue_num [16;16] */
    unsigned int ue_num:16;
    /* ue_num [16;0] */
    unsigned int __ue_num_1:16;
};

/* detach_req field accessor macros */
#define PIF_HEADER_GET_detach_req___ue_ip(_hdr_p) (((_hdr_p)->ue_ip)) /* detach_req.ue_ip [32;0] */

#define PIF_HEADER_SET_detach_req___ue_ip(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_ip = (unsigned)(((_val))); \
    } while (0) /* detach_req.ue_ip[32;0] */

#define PIF_HEADER_GET_detach_req___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* detach_req.sep1 [32;0] */

#define PIF_HEADER_SET_detach_req___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* detach_req.sep1[32;0] */

#define PIF_HEADER_GET_detach_req___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* detach_req.sep1 [16;32] */

#define PIF_HEADER_SET_detach_req___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* detach_req.sep1[16;32] */

#define PIF_HEADER_GET_detach_req___ue_teid(_hdr_p) (((_hdr_p)->ue_teid << 16) | ((_hdr_p)->__ue_teid_1)) /* detach_req.ue_teid [32;0] */

#define PIF_HEADER_SET_detach_req___ue_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_teid = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__ue_teid_1 = (unsigned)(((_val))); \
    } while (0) /* detach_req.ue_teid[32;0] */

#define PIF_HEADER_GET_detach_req___sep2___0(_hdr_p) (((_hdr_p)->__sep2_1)) /* detach_req.sep2 [32;0] */

#define PIF_HEADER_SET_detach_req___sep2___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__sep2_1 = (unsigned)(((_val))); \
    } while (0) /* detach_req.sep2[32;0] */

#define PIF_HEADER_GET_detach_req___sep2___1(_hdr_p) (((_hdr_p)->sep2)) /* detach_req.sep2 [16;32] */

#define PIF_HEADER_SET_detach_req___sep2___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep2 = (unsigned)(((_val))); \
    } while (0) /* detach_req.sep2[16;32] */

#define PIF_HEADER_GET_detach_req___sgw_teid(_hdr_p) (((_hdr_p)->sgw_teid)) /* detach_req.sgw_teid [32;0] */

#define PIF_HEADER_SET_detach_req___sgw_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->sgw_teid = (unsigned)(((_val))); \
    } while (0) /* detach_req.sgw_teid[32;0] */

#define PIF_HEADER_GET_detach_req___sep3___0(_hdr_p) ((((_hdr_p)->sep3 & 0xffff) << 16) | ((_hdr_p)->__sep3_1)) /* detach_req.sep3 [32;0] */

#define PIF_HEADER_SET_detach_req___sep3___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep3_1 = (unsigned)(((_val))); \
    } while (0) /* detach_req.sep3[32;0] */

#define PIF_HEADER_GET_detach_req___sep3___1(_hdr_p) ((((_hdr_p)->sep3 >> 16) & 0xffff)) /* detach_req.sep3 [16;32] */

#define PIF_HEADER_SET_detach_req___sep3___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xffff); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* detach_req.sep3[16;32] */

#define PIF_HEADER_GET_detach_req___ue_num(_hdr_p) (((_hdr_p)->ue_num << 16) | ((_hdr_p)->__ue_num_1)) /* detach_req.ue_num [32;0] */

#define PIF_HEADER_SET_detach_req___ue_num(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_num = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__ue_num_1 = (unsigned)(((_val))); \
    } while (0) /* detach_req.ue_num[32;0] */


/* ipv4 (20B) */
struct pif_header_ipv4 {
    unsigned int version:4;
    unsigned int ihl:4;
    unsigned int diffserv:8;
    unsigned int totalLen:16;
    unsigned int identification:16;
    unsigned int flags:3;
    unsigned int fragOffset:13;
    unsigned int ttl:8;
    unsigned int protocol:8;
    unsigned int hdrChecksum:16;
    unsigned int srcAddr:32;
    unsigned int dstAddr:32;
};

/* ipv4 field accessor macros */
#define PIF_HEADER_GET_ipv4___version(_hdr_p) (((_hdr_p)->version)) /* ipv4.version [4;0] */

#define PIF_HEADER_SET_ipv4___version(_hdr_p, _val) \
    do { \
        (_hdr_p)->version = (unsigned)(((_val))); \
    } while (0) /* ipv4.version[4;0] */

#define PIF_HEADER_GET_ipv4___ihl(_hdr_p) (((_hdr_p)->ihl)) /* ipv4.ihl [4;0] */

#define PIF_HEADER_SET_ipv4___ihl(_hdr_p, _val) \
    do { \
        (_hdr_p)->ihl = (unsigned)(((_val))); \
    } while (0) /* ipv4.ihl[4;0] */

#define PIF_HEADER_GET_ipv4___diffserv(_hdr_p) (((_hdr_p)->diffserv)) /* ipv4.diffserv [8;0] */

#define PIF_HEADER_SET_ipv4___diffserv(_hdr_p, _val) \
    do { \
        (_hdr_p)->diffserv = (unsigned)(((_val))); \
    } while (0) /* ipv4.diffserv[8;0] */

#define PIF_HEADER_GET_ipv4___totalLen(_hdr_p) (((_hdr_p)->totalLen)) /* ipv4.totalLen [16;0] */

#define PIF_HEADER_SET_ipv4___totalLen(_hdr_p, _val) \
    do { \
        (_hdr_p)->totalLen = (unsigned)(((_val))); \
    } while (0) /* ipv4.totalLen[16;0] */

#define PIF_HEADER_GET_ipv4___identification(_hdr_p) (((_hdr_p)->identification)) /* ipv4.identification [16;0] */

#define PIF_HEADER_SET_ipv4___identification(_hdr_p, _val) \
    do { \
        (_hdr_p)->identification = (unsigned)(((_val))); \
    } while (0) /* ipv4.identification[16;0] */

#define PIF_HEADER_GET_ipv4___flags(_hdr_p) (((_hdr_p)->flags)) /* ipv4.flags [3;0] */

#define PIF_HEADER_SET_ipv4___flags(_hdr_p, _val) \
    do { \
        (_hdr_p)->flags = (unsigned)(((_val))); \
    } while (0) /* ipv4.flags[3;0] */

#define PIF_HEADER_GET_ipv4___fragOffset(_hdr_p) (((_hdr_p)->fragOffset)) /* ipv4.fragOffset [13;0] */

#define PIF_HEADER_SET_ipv4___fragOffset(_hdr_p, _val) \
    do { \
        (_hdr_p)->fragOffset = (unsigned)(((_val))); \
    } while (0) /* ipv4.fragOffset[13;0] */

#define PIF_HEADER_GET_ipv4___ttl(_hdr_p) (((_hdr_p)->ttl)) /* ipv4.ttl [8;0] */

#define PIF_HEADER_SET_ipv4___ttl(_hdr_p, _val) \
    do { \
        (_hdr_p)->ttl = (unsigned)(((_val))); \
    } while (0) /* ipv4.ttl[8;0] */

#define PIF_HEADER_GET_ipv4___protocol(_hdr_p) (((_hdr_p)->protocol)) /* ipv4.protocol [8;0] */

#define PIF_HEADER_SET_ipv4___protocol(_hdr_p, _val) \
    do { \
        (_hdr_p)->protocol = (unsigned)(((_val))); \
    } while (0) /* ipv4.protocol[8;0] */

#define PIF_HEADER_GET_ipv4___hdrChecksum(_hdr_p) (((_hdr_p)->hdrChecksum)) /* ipv4.hdrChecksum [16;0] */

#define PIF_HEADER_SET_ipv4___hdrChecksum(_hdr_p, _val) \
    do { \
        (_hdr_p)->hdrChecksum = (unsigned)(((_val))); \
    } while (0) /* ipv4.hdrChecksum[16;0] */

#define PIF_HEADER_GET_ipv4___srcAddr(_hdr_p) (((_hdr_p)->srcAddr)) /* ipv4.srcAddr [32;0] */

#define PIF_HEADER_SET_ipv4___srcAddr(_hdr_p, _val) \
    do { \
        (_hdr_p)->srcAddr = (unsigned)(((_val))); \
    } while (0) /* ipv4.srcAddr[32;0] */

#define PIF_HEADER_GET_ipv4___dstAddr(_hdr_p) (((_hdr_p)->dstAddr)) /* ipv4.dstAddr [32;0] */

#define PIF_HEADER_SET_ipv4___dstAddr(_hdr_p, _val) \
    do { \
        (_hdr_p)->dstAddr = (unsigned)(((_val))); \
    } while (0) /* ipv4.dstAddr[32;0] */


/* udp (8B) */
struct pif_header_udp {
    unsigned int srcPort:16;
    unsigned int dstPort:16;
    unsigned int length_:16;
    unsigned int checksum:16;
};

/* udp field accessor macros */
#define PIF_HEADER_GET_udp___srcPort(_hdr_p) (((_hdr_p)->srcPort)) /* udp.srcPort [16;0] */

#define PIF_HEADER_SET_udp___srcPort(_hdr_p, _val) \
    do { \
        (_hdr_p)->srcPort = (unsigned)(((_val))); \
    } while (0) /* udp.srcPort[16;0] */

#define PIF_HEADER_GET_udp___dstPort(_hdr_p) (((_hdr_p)->dstPort)) /* udp.dstPort [16;0] */

#define PIF_HEADER_SET_udp___dstPort(_hdr_p, _val) \
    do { \
        (_hdr_p)->dstPort = (unsigned)(((_val))); \
    } while (0) /* udp.dstPort[16;0] */

#define PIF_HEADER_GET_udp___length_(_hdr_p) (((_hdr_p)->length_)) /* udp.length_ [16;0] */

#define PIF_HEADER_SET_udp___length_(_hdr_p, _val) \
    do { \
        (_hdr_p)->length_ = (unsigned)(((_val))); \
    } while (0) /* udp.length_[16;0] */

#define PIF_HEADER_GET_udp___checksum(_hdr_p) (((_hdr_p)->checksum)) /* udp.checksum [16;0] */

#define PIF_HEADER_SET_udp___checksum(_hdr_p, _val) \
    do { \
        (_hdr_p)->checksum = (unsigned)(((_val))); \
    } while (0) /* udp.checksum[16;0] */


/* send_apn (18B) */
struct pif_header_send_apn {
    /* apn [32;32] */
    unsigned int apn:32;
    /* apn [32;0] */
    unsigned int __apn_1:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* key [16;16] */
    unsigned int key:16;
    /* key [16;0] */
    unsigned int __key_1:16;
};

/* send_apn field accessor macros */
#define PIF_HEADER_GET_send_apn___apn___0(_hdr_p) (((_hdr_p)->__apn_1)) /* send_apn.apn [32;0] */

#define PIF_HEADER_SET_send_apn___apn___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__apn_1 = (unsigned)(((_val))); \
    } while (0) /* send_apn.apn[32;0] */

#define PIF_HEADER_GET_send_apn___apn___1(_hdr_p) (((_hdr_p)->apn)) /* send_apn.apn [32;32] */

#define PIF_HEADER_SET_send_apn___apn___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->apn = (unsigned)(((_val))); \
    } while (0) /* send_apn.apn[32;32] */

#define PIF_HEADER_GET_send_apn___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* send_apn.sep1 [32;0] */

#define PIF_HEADER_SET_send_apn___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* send_apn.sep1[32;0] */

#define PIF_HEADER_GET_send_apn___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* send_apn.sep1 [16;32] */

#define PIF_HEADER_SET_send_apn___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* send_apn.sep1[16;32] */

#define PIF_HEADER_GET_send_apn___key(_hdr_p) (((_hdr_p)->key << 16) | ((_hdr_p)->__key_1)) /* send_apn.key [32;0] */

#define PIF_HEADER_SET_send_apn___key(_hdr_p, _val) \
    do { \
        (_hdr_p)->key = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__key_1 = (unsigned)(((_val))); \
    } while (0) /* send_apn.key[32;0] */


/* data (7B) */
struct pif_header_data {
    unsigned int epc_traffic_code:8;
    /* sep [24;24] */
    unsigned int sep:24;
    /* sep [24;0] */
    unsigned int __sep_1:24;
};

/* data field accessor macros */
#define PIF_HEADER_GET_data___epc_traffic_code(_hdr_p) (((_hdr_p)->epc_traffic_code)) /* data.epc_traffic_code [8;0] */

#define PIF_HEADER_SET_data___epc_traffic_code(_hdr_p, _val) \
    do { \
        (_hdr_p)->epc_traffic_code = (unsigned)(((_val))); \
    } while (0) /* data.epc_traffic_code[8;0] */

#define PIF_HEADER_GET_data___sep___0(_hdr_p) ((((_hdr_p)->sep & 0xff) << 24) | ((_hdr_p)->__sep_1)) /* data.sep [32;0] */

#define PIF_HEADER_SET_data___sep___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep &= (unsigned)(0xffffff00); \
        (_hdr_p)->sep |= (unsigned)((((_val) >> 24) & 0xff)); \
        (_hdr_p)->__sep_1 = (unsigned)(((_val))); \
    } while (0) /* data.sep[32;0] */

#define PIF_HEADER_GET_data___sep___1(_hdr_p) ((((_hdr_p)->sep >> 8) & 0xffff)) /* data.sep [16;32] */

#define PIF_HEADER_SET_data___sep___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep &= (unsigned)(0xff0000ff); \
        (_hdr_p)->sep |= (unsigned)((((_val) & 0xffff) << 8)); \
    } while (0) /* data.sep[16;32] */


/* send_ue_teid (14B) */
struct pif_header_send_ue_teid {
    unsigned int ue_teid:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* key [16;16] */
    unsigned int key:16;
    /* key [16;0] */
    unsigned int __key_1:16;
};

/* send_ue_teid field accessor macros */
#define PIF_HEADER_GET_send_ue_teid___ue_teid(_hdr_p) (((_hdr_p)->ue_teid)) /* send_ue_teid.ue_teid [32;0] */

#define PIF_HEADER_SET_send_ue_teid___ue_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_teid = (unsigned)(((_val))); \
    } while (0) /* send_ue_teid.ue_teid[32;0] */

#define PIF_HEADER_GET_send_ue_teid___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* send_ue_teid.sep1 [32;0] */

#define PIF_HEADER_SET_send_ue_teid___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* send_ue_teid.sep1[32;0] */

#define PIF_HEADER_GET_send_ue_teid___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* send_ue_teid.sep1 [16;32] */

#define PIF_HEADER_SET_send_ue_teid___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* send_ue_teid.sep1[16;32] */

#define PIF_HEADER_GET_send_ue_teid___key(_hdr_p) (((_hdr_p)->key << 16) | ((_hdr_p)->__key_1)) /* send_ue_teid.key [32;0] */

#define PIF_HEADER_SET_send_ue_teid___key(_hdr_p, _val) \
    do { \
        (_hdr_p)->key = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__key_1 = (unsigned)(((_val))); \
    } while (0) /* send_ue_teid.key[32;0] */


/* offload_ue_service_req (34B) */
struct pif_header_offload_ue_service_req {
    unsigned int ue_key:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* ksi_asme [16;16] */
    unsigned int ksi_asme:16;
    /* ksi_asme [16;0] */
    unsigned int __ksi_asme_1:16;
    /* sep2 [16;32] */
    unsigned int sep2:16;
    /* sep2 [32;0] */
    unsigned int __sep2_1:32;
    unsigned int ue_ip:32;
    /* sep3 [32;16] */
    unsigned int sep3:32;
    /* sep3 [16;0] */
    unsigned int __sep3_1:16;
    /* sgw_teid [16;16] */
    unsigned int sgw_teid:16;
    /* sgw_teid [16;0] */
    unsigned int __sgw_teid_1:16;
};

/* offload_ue_service_req field accessor macros */
#define PIF_HEADER_GET_offload_ue_service_req___ue_key(_hdr_p) (((_hdr_p)->ue_key)) /* offload_ue_service_req.ue_key [32;0] */

#define PIF_HEADER_SET_offload_ue_service_req___ue_key(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_key = (unsigned)(((_val))); \
    } while (0) /* offload_ue_service_req.ue_key[32;0] */

#define PIF_HEADER_GET_offload_ue_service_req___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* offload_ue_service_req.sep1 [32;0] */

#define PIF_HEADER_SET_offload_ue_service_req___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* offload_ue_service_req.sep1[32;0] */

#define PIF_HEADER_GET_offload_ue_service_req___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* offload_ue_service_req.sep1 [16;32] */

#define PIF_HEADER_SET_offload_ue_service_req___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* offload_ue_service_req.sep1[16;32] */

#define PIF_HEADER_GET_offload_ue_service_req___ksi_asme(_hdr_p) (((_hdr_p)->ksi_asme << 16) | ((_hdr_p)->__ksi_asme_1)) /* offload_ue_service_req.ksi_asme [32;0] */

#define PIF_HEADER_SET_offload_ue_service_req___ksi_asme(_hdr_p, _val) \
    do { \
        (_hdr_p)->ksi_asme = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__ksi_asme_1 = (unsigned)(((_val))); \
    } while (0) /* offload_ue_service_req.ksi_asme[32;0] */

#define PIF_HEADER_GET_offload_ue_service_req___sep2___0(_hdr_p) (((_hdr_p)->__sep2_1)) /* offload_ue_service_req.sep2 [32;0] */

#define PIF_HEADER_SET_offload_ue_service_req___sep2___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__sep2_1 = (unsigned)(((_val))); \
    } while (0) /* offload_ue_service_req.sep2[32;0] */

#define PIF_HEADER_GET_offload_ue_service_req___sep2___1(_hdr_p) (((_hdr_p)->sep2)) /* offload_ue_service_req.sep2 [16;32] */

#define PIF_HEADER_SET_offload_ue_service_req___sep2___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep2 = (unsigned)(((_val))); \
    } while (0) /* offload_ue_service_req.sep2[16;32] */

#define PIF_HEADER_GET_offload_ue_service_req___ue_ip(_hdr_p) (((_hdr_p)->ue_ip)) /* offload_ue_service_req.ue_ip [32;0] */

#define PIF_HEADER_SET_offload_ue_service_req___ue_ip(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_ip = (unsigned)(((_val))); \
    } while (0) /* offload_ue_service_req.ue_ip[32;0] */

#define PIF_HEADER_GET_offload_ue_service_req___sep3___0(_hdr_p) ((((_hdr_p)->sep3 & 0xffff) << 16) | ((_hdr_p)->__sep3_1)) /* offload_ue_service_req.sep3 [32;0] */

#define PIF_HEADER_SET_offload_ue_service_req___sep3___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep3_1 = (unsigned)(((_val))); \
    } while (0) /* offload_ue_service_req.sep3[32;0] */

#define PIF_HEADER_GET_offload_ue_service_req___sep3___1(_hdr_p) ((((_hdr_p)->sep3 >> 16) & 0xffff)) /* offload_ue_service_req.sep3 [16;32] */

#define PIF_HEADER_SET_offload_ue_service_req___sep3___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xffff); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* offload_ue_service_req.sep3[16;32] */

#define PIF_HEADER_GET_offload_ue_service_req___sgw_teid(_hdr_p) (((_hdr_p)->sgw_teid << 16) | ((_hdr_p)->__sgw_teid_1)) /* offload_ue_service_req.sgw_teid [32;0] */

#define PIF_HEADER_SET_offload_ue_service_req___sgw_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->sgw_teid = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__sgw_teid_1 = (unsigned)(((_val))); \
    } while (0) /* offload_ue_service_req.sgw_teid[32;0] */


/* ue_service_req (24B) */
struct pif_header_ue_service_req {
    unsigned int ue_key:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* ksi_asme [16;16] */
    unsigned int ksi_asme:16;
    /* ksi_asme [16;0] */
    unsigned int __ksi_asme_1:16;
    /* sep2 [16;32] */
    unsigned int sep2:16;
    /* sep2 [32;0] */
    unsigned int __sep2_1:32;
    unsigned int ue_ip:32;
};

/* ue_service_req field accessor macros */
#define PIF_HEADER_GET_ue_service_req___ue_key(_hdr_p) (((_hdr_p)->ue_key)) /* ue_service_req.ue_key [32;0] */

#define PIF_HEADER_SET_ue_service_req___ue_key(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_key = (unsigned)(((_val))); \
    } while (0) /* ue_service_req.ue_key[32;0] */

#define PIF_HEADER_GET_ue_service_req___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* ue_service_req.sep1 [32;0] */

#define PIF_HEADER_SET_ue_service_req___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* ue_service_req.sep1[32;0] */

#define PIF_HEADER_GET_ue_service_req___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* ue_service_req.sep1 [16;32] */

#define PIF_HEADER_SET_ue_service_req___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* ue_service_req.sep1[16;32] */

#define PIF_HEADER_GET_ue_service_req___ksi_asme(_hdr_p) (((_hdr_p)->ksi_asme << 16) | ((_hdr_p)->__ksi_asme_1)) /* ue_service_req.ksi_asme [32;0] */

#define PIF_HEADER_SET_ue_service_req___ksi_asme(_hdr_p, _val) \
    do { \
        (_hdr_p)->ksi_asme = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__ksi_asme_1 = (unsigned)(((_val))); \
    } while (0) /* ue_service_req.ksi_asme[32;0] */

#define PIF_HEADER_GET_ue_service_req___sep2___0(_hdr_p) (((_hdr_p)->__sep2_1)) /* ue_service_req.sep2 [32;0] */

#define PIF_HEADER_SET_ue_service_req___sep2___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__sep2_1 = (unsigned)(((_val))); \
    } while (0) /* ue_service_req.sep2[32;0] */

#define PIF_HEADER_GET_ue_service_req___sep2___1(_hdr_p) (((_hdr_p)->sep2)) /* ue_service_req.sep2 [16;32] */

#define PIF_HEADER_SET_ue_service_req___sep2___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep2 = (unsigned)(((_val))); \
    } while (0) /* ue_service_req.sep2[16;32] */

#define PIF_HEADER_GET_ue_service_req___ue_ip(_hdr_p) (((_hdr_p)->ue_ip)) /* ue_service_req.ue_ip [32;0] */

#define PIF_HEADER_SET_ue_service_req___ue_ip(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_ip = (unsigned)(((_val))); \
    } while (0) /* ue_service_req.ue_ip[32;0] */


/* nas_step_two (30B) */
struct pif_header_nas_step_two {
    /* encrypted_hash [32;128] */
    unsigned int encrypted_hash:32;
    /* encrypted_hash [32;96] */
    unsigned int __encrypted_hash_1:32;
    /* encrypted_hash [32;64] */
    unsigned int __encrypted_hash_2:32;
    /* encrypted_hash [32;32] */
    unsigned int __encrypted_hash_3:32;
    /* encrypted_hash [32;0] */
    unsigned int __encrypted_hash_4:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    /* imsi [16;16] */
    unsigned int imsi:16;
    /* imsi [16;0] */
    unsigned int __imsi_1:16;
};

/* nas_step_two field accessor macros */
#define PIF_HEADER_GET_nas_step_two___encrypted_hash___0(_hdr_p) (((_hdr_p)->__encrypted_hash_4)) /* nas_step_two.encrypted_hash [32;0] */

#define PIF_HEADER_SET_nas_step_two___encrypted_hash___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__encrypted_hash_4 = (unsigned)(((_val))); \
    } while (0) /* nas_step_two.encrypted_hash[32;0] */

#define PIF_HEADER_GET_nas_step_two___encrypted_hash___1(_hdr_p) (((_hdr_p)->__encrypted_hash_3)) /* nas_step_two.encrypted_hash [32;32] */

#define PIF_HEADER_SET_nas_step_two___encrypted_hash___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->__encrypted_hash_3 = (unsigned)(((_val))); \
    } while (0) /* nas_step_two.encrypted_hash[32;32] */

#define PIF_HEADER_GET_nas_step_two___encrypted_hash___2(_hdr_p) (((_hdr_p)->__encrypted_hash_2)) /* nas_step_two.encrypted_hash [32;64] */

#define PIF_HEADER_SET_nas_step_two___encrypted_hash___2(_hdr_p, _val) \
    do { \
        (_hdr_p)->__encrypted_hash_2 = (unsigned)(((_val))); \
    } while (0) /* nas_step_two.encrypted_hash[32;64] */

#define PIF_HEADER_GET_nas_step_two___encrypted_hash___3(_hdr_p) (((_hdr_p)->__encrypted_hash_1)) /* nas_step_two.encrypted_hash [32;96] */

#define PIF_HEADER_SET_nas_step_two___encrypted_hash___3(_hdr_p, _val) \
    do { \
        (_hdr_p)->__encrypted_hash_1 = (unsigned)(((_val))); \
    } while (0) /* nas_step_two.encrypted_hash[32;96] */

#define PIF_HEADER_GET_nas_step_two___encrypted_hash___4(_hdr_p) (((_hdr_p)->encrypted_hash)) /* nas_step_two.encrypted_hash [32;128] */

#define PIF_HEADER_SET_nas_step_two___encrypted_hash___4(_hdr_p, _val) \
    do { \
        (_hdr_p)->encrypted_hash = (unsigned)(((_val))); \
    } while (0) /* nas_step_two.encrypted_hash[32;128] */

#define PIF_HEADER_GET_nas_step_two___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* nas_step_two.sep1 [32;0] */

#define PIF_HEADER_SET_nas_step_two___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* nas_step_two.sep1[32;0] */

#define PIF_HEADER_GET_nas_step_two___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* nas_step_two.sep1 [16;32] */

#define PIF_HEADER_SET_nas_step_two___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* nas_step_two.sep1[16;32] */

#define PIF_HEADER_GET_nas_step_two___imsi(_hdr_p) (((_hdr_p)->imsi << 16) | ((_hdr_p)->__imsi_1)) /* nas_step_two.imsi [32;0] */

#define PIF_HEADER_SET_nas_step_two___imsi(_hdr_p, _val) \
    do { \
        (_hdr_p)->imsi = (unsigned)(((_val) >> 16)); \
        (_hdr_p)->__imsi_1 = (unsigned)(((_val))); \
    } while (0) /* nas_step_two.imsi[32;0] */


/* packet_out (2B) */
struct pif_header_packet_out {
    unsigned int egress_port:16;
};

/* packet_out field accessor macros */
#define PIF_HEADER_GET_packet_out___egress_port(_hdr_p) (((_hdr_p)->egress_port)) /* packet_out.egress_port [16;0] */

#define PIF_HEADER_SET_packet_out___egress_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_port = (unsigned)(((_val))); \
    } while (0) /* packet_out.egress_port[16;0] */


/* ethernet (14B) */
struct pif_header_ethernet {
    /* dstAddr [32;16] */
    unsigned int dstAddr:32;
    /* dstAddr [16;0] */
    unsigned int __dstAddr_1:16;
    /* srcAddr [16;32] */
    unsigned int srcAddr:16;
    /* srcAddr [32;0] */
    unsigned int __srcAddr_1:32;
    unsigned int etherType:16;
};

/* ethernet field accessor macros */
#define PIF_HEADER_GET_ethernet___dstAddr___0(_hdr_p) ((((_hdr_p)->dstAddr & 0xffff) << 16) | ((_hdr_p)->__dstAddr_1)) /* ethernet.dstAddr [32;0] */

#define PIF_HEADER_SET_ethernet___dstAddr___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->dstAddr &= (unsigned)(0xffff0000); \
        (_hdr_p)->dstAddr |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__dstAddr_1 = (unsigned)(((_val))); \
    } while (0) /* ethernet.dstAddr[32;0] */

#define PIF_HEADER_GET_ethernet___dstAddr___1(_hdr_p) ((((_hdr_p)->dstAddr >> 16) & 0xffff)) /* ethernet.dstAddr [16;32] */

#define PIF_HEADER_SET_ethernet___dstAddr___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->dstAddr &= (unsigned)(0xffff); \
        (_hdr_p)->dstAddr |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* ethernet.dstAddr[16;32] */

#define PIF_HEADER_GET_ethernet___srcAddr___0(_hdr_p) (((_hdr_p)->__srcAddr_1)) /* ethernet.srcAddr [32;0] */

#define PIF_HEADER_SET_ethernet___srcAddr___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__srcAddr_1 = (unsigned)(((_val))); \
    } while (0) /* ethernet.srcAddr[32;0] */

#define PIF_HEADER_GET_ethernet___srcAddr___1(_hdr_p) (((_hdr_p)->srcAddr)) /* ethernet.srcAddr [16;32] */

#define PIF_HEADER_SET_ethernet___srcAddr___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->srcAddr = (unsigned)(((_val))); \
    } while (0) /* ethernet.srcAddr[16;32] */

#define PIF_HEADER_GET_ethernet___etherType(_hdr_p) (((_hdr_p)->etherType)) /* ethernet.etherType [16;0] */

#define PIF_HEADER_SET_ethernet___etherType(_hdr_p, _val) \
    do { \
        (_hdr_p)->etherType = (unsigned)(((_val))); \
    } while (0) /* ethernet.etherType[16;0] */


/* auth_step_one (73B) */
struct pif_header_auth_step_one {
    unsigned int imsi:32;
    /* sep1 [32;16] */
    unsigned int sep1:32;
    /* sep1 [16;0] */
    unsigned int __sep1_1:16;
    unsigned int ue_nw_capability:8;
    /* sep2 [8;40] */
    unsigned int sep2:8;
    /* sep2 [32;8] */
    unsigned int __sep2_1:32;
    /* sep2 [8;0] */
    unsigned int __sep2_2:8;
    /* ksi_asme [24;232] */
    unsigned int ksi_asme:24;
    /* ksi_asme [32;200] */
    unsigned int __ksi_asme_1:32;
    /* ksi_asme [32;168] */
    unsigned int __ksi_asme_2:32;
    /* ksi_asme [32;136] */
    unsigned int __ksi_asme_3:32;
    /* ksi_asme [32;104] */
    unsigned int __ksi_asme_4:32;
    /* ksi_asme [32;72] */
    unsigned int __ksi_asme_5:32;
    /* ksi_asme [32;40] */
    unsigned int __ksi_asme_6:32;
    /* ksi_asme [32;8] */
    unsigned int __ksi_asme_7:32;
    /* ksi_asme [8;0] */
    unsigned int __ksi_asme_8:8;
    /* sep3 [24;24] */
    unsigned int sep3:24;
    /* sep3 [24;0] */
    unsigned int __sep3_1:24;
    /* sqn [8;24] */
    unsigned int sqn:8;
    /* sqn [24;0] */
    unsigned int __sqn_1:24;
    /* sep4 [8;40] */
    unsigned int sep4:8;
    /* sep4 [32;8] */
    unsigned int __sep4_1:32;
    /* sep4 [8;0] */
    unsigned int __sep4_2:8;
    /* tai [24;40] */
    unsigned int tai:24;
    /* tai [32;8] */
    unsigned int __tai_1:32;
    /* tai [8;0] */
    unsigned int __tai_2:8;
};

/* auth_step_one field accessor macros */
#define PIF_HEADER_GET_auth_step_one___imsi(_hdr_p) (((_hdr_p)->imsi)) /* auth_step_one.imsi [32;0] */

#define PIF_HEADER_SET_auth_step_one___imsi(_hdr_p, _val) \
    do { \
        (_hdr_p)->imsi = (unsigned)(((_val))); \
    } while (0) /* auth_step_one.imsi[32;0] */

#define PIF_HEADER_GET_auth_step_one___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xffff) << 16) | ((_hdr_p)->__sep1_1)) /* auth_step_one.sep1 [32;0] */

#define PIF_HEADER_SET_auth_step_one___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff0000); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* auth_step_one.sep1[32;0] */

#define PIF_HEADER_GET_auth_step_one___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 16) & 0xffff)) /* auth_step_one.sep1 [16;32] */

#define PIF_HEADER_SET_auth_step_one___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* auth_step_one.sep1[16;32] */

#define PIF_HEADER_GET_auth_step_one___ue_nw_capability(_hdr_p) (((_hdr_p)->ue_nw_capability)) /* auth_step_one.ue_nw_capability [8;0] */

#define PIF_HEADER_SET_auth_step_one___ue_nw_capability(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_nw_capability = (unsigned)(((_val))); \
    } while (0) /* auth_step_one.ue_nw_capability[8;0] */

#define PIF_HEADER_GET_auth_step_one___sep2___0(_hdr_p) ((((_hdr_p)->__sep2_1 & 0xffffff) << 8) | ((_hdr_p)->__sep2_2)) /* auth_step_one.sep2 [32;0] */

#define PIF_HEADER_SET_auth_step_one___sep2___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__sep2_1 &= (unsigned)(0xff000000); \
        (_hdr_p)->__sep2_1 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__sep2_2 = (unsigned)(((_val))); \
    } while (0) /* auth_step_one.sep2[32;0] */

#define PIF_HEADER_GET_auth_step_one___sep2___1(_hdr_p) (((_hdr_p)->sep2 << 8) | (((_hdr_p)->__sep2_1 >> 24) & 0xff)) /* auth_step_one.sep2 [16;32] */

#define PIF_HEADER_SET_auth_step_one___sep2___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep2 = (unsigned)(((_val) >> 8)); \
        (_hdr_p)->__sep2_1 &= (unsigned)(0xffffff); \
        (_hdr_p)->__sep2_1 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.sep2[16;32] */

#define PIF_HEADER_GET_auth_step_one___ksi_asme___0(_hdr_p) ((((_hdr_p)->__ksi_asme_7 & 0xffffff) << 8) | ((_hdr_p)->__ksi_asme_8)) /* auth_step_one.ksi_asme [32;0] */

#define PIF_HEADER_SET_auth_step_one___ksi_asme___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__ksi_asme_7 &= (unsigned)(0xff000000); \
        (_hdr_p)->__ksi_asme_7 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__ksi_asme_8 = (unsigned)(((_val))); \
    } while (0) /* auth_step_one.ksi_asme[32;0] */

#define PIF_HEADER_GET_auth_step_one___ksi_asme___1(_hdr_p) ((((_hdr_p)->__ksi_asme_6 & 0xffffff) << 8) | (((_hdr_p)->__ksi_asme_7 >> 24) & 0xff)) /* auth_step_one.ksi_asme [32;32] */

#define PIF_HEADER_SET_auth_step_one___ksi_asme___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->__ksi_asme_6 &= (unsigned)(0xff000000); \
        (_hdr_p)->__ksi_asme_6 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__ksi_asme_7 &= (unsigned)(0xffffff); \
        (_hdr_p)->__ksi_asme_7 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.ksi_asme[32;32] */

#define PIF_HEADER_GET_auth_step_one___ksi_asme___2(_hdr_p) ((((_hdr_p)->__ksi_asme_5 & 0xffffff) << 8) | (((_hdr_p)->__ksi_asme_6 >> 24) & 0xff)) /* auth_step_one.ksi_asme [32;64] */

#define PIF_HEADER_SET_auth_step_one___ksi_asme___2(_hdr_p, _val) \
    do { \
        (_hdr_p)->__ksi_asme_5 &= (unsigned)(0xff000000); \
        (_hdr_p)->__ksi_asme_5 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__ksi_asme_6 &= (unsigned)(0xffffff); \
        (_hdr_p)->__ksi_asme_6 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.ksi_asme[32;64] */

#define PIF_HEADER_GET_auth_step_one___ksi_asme___3(_hdr_p) ((((_hdr_p)->__ksi_asme_4 & 0xffffff) << 8) | (((_hdr_p)->__ksi_asme_5 >> 24) & 0xff)) /* auth_step_one.ksi_asme [32;96] */

#define PIF_HEADER_SET_auth_step_one___ksi_asme___3(_hdr_p, _val) \
    do { \
        (_hdr_p)->__ksi_asme_4 &= (unsigned)(0xff000000); \
        (_hdr_p)->__ksi_asme_4 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__ksi_asme_5 &= (unsigned)(0xffffff); \
        (_hdr_p)->__ksi_asme_5 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.ksi_asme[32;96] */

#define PIF_HEADER_GET_auth_step_one___ksi_asme___4(_hdr_p) ((((_hdr_p)->__ksi_asme_3 & 0xffffff) << 8) | (((_hdr_p)->__ksi_asme_4 >> 24) & 0xff)) /* auth_step_one.ksi_asme [32;128] */

#define PIF_HEADER_SET_auth_step_one___ksi_asme___4(_hdr_p, _val) \
    do { \
        (_hdr_p)->__ksi_asme_3 &= (unsigned)(0xff000000); \
        (_hdr_p)->__ksi_asme_3 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__ksi_asme_4 &= (unsigned)(0xffffff); \
        (_hdr_p)->__ksi_asme_4 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.ksi_asme[32;128] */

#define PIF_HEADER_GET_auth_step_one___ksi_asme___5(_hdr_p) ((((_hdr_p)->__ksi_asme_2 & 0xffffff) << 8) | (((_hdr_p)->__ksi_asme_3 >> 24) & 0xff)) /* auth_step_one.ksi_asme [32;160] */

#define PIF_HEADER_SET_auth_step_one___ksi_asme___5(_hdr_p, _val) \
    do { \
        (_hdr_p)->__ksi_asme_2 &= (unsigned)(0xff000000); \
        (_hdr_p)->__ksi_asme_2 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__ksi_asme_3 &= (unsigned)(0xffffff); \
        (_hdr_p)->__ksi_asme_3 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.ksi_asme[32;160] */

#define PIF_HEADER_GET_auth_step_one___ksi_asme___6(_hdr_p) ((((_hdr_p)->__ksi_asme_1 & 0xffffff) << 8) | (((_hdr_p)->__ksi_asme_2 >> 24) & 0xff)) /* auth_step_one.ksi_asme [32;192] */

#define PIF_HEADER_SET_auth_step_one___ksi_asme___6(_hdr_p, _val) \
    do { \
        (_hdr_p)->__ksi_asme_1 &= (unsigned)(0xff000000); \
        (_hdr_p)->__ksi_asme_1 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__ksi_asme_2 &= (unsigned)(0xffffff); \
        (_hdr_p)->__ksi_asme_2 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.ksi_asme[32;192] */

#define PIF_HEADER_GET_auth_step_one___ksi_asme___7(_hdr_p) (((_hdr_p)->ksi_asme << 8) | (((_hdr_p)->__ksi_asme_1 >> 24) & 0xff)) /* auth_step_one.ksi_asme [32;224] */

#define PIF_HEADER_SET_auth_step_one___ksi_asme___7(_hdr_p, _val) \
    do { \
        (_hdr_p)->ksi_asme = (unsigned)(((_val) >> 8)); \
        (_hdr_p)->__ksi_asme_1 &= (unsigned)(0xffffff); \
        (_hdr_p)->__ksi_asme_1 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.ksi_asme[32;224] */

#define PIF_HEADER_GET_auth_step_one___sep3___0(_hdr_p) ((((_hdr_p)->sep3 & 0xff) << 24) | ((_hdr_p)->__sep3_1)) /* auth_step_one.sep3 [32;0] */

#define PIF_HEADER_SET_auth_step_one___sep3___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xffffff00); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) >> 24) & 0xff)); \
        (_hdr_p)->__sep3_1 = (unsigned)(((_val))); \
    } while (0) /* auth_step_one.sep3[32;0] */

#define PIF_HEADER_GET_auth_step_one___sep3___1(_hdr_p) ((((_hdr_p)->sep3 >> 8) & 0xffff)) /* auth_step_one.sep3 [16;32] */

#define PIF_HEADER_SET_auth_step_one___sep3___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep3 &= (unsigned)(0xff0000ff); \
        (_hdr_p)->sep3 |= (unsigned)((((_val) & 0xffff) << 8)); \
    } while (0) /* auth_step_one.sep3[16;32] */

#define PIF_HEADER_GET_auth_step_one___sqn(_hdr_p) (((_hdr_p)->sqn << 24) | ((_hdr_p)->__sqn_1)) /* auth_step_one.sqn [32;0] */

#define PIF_HEADER_SET_auth_step_one___sqn(_hdr_p, _val) \
    do { \
        (_hdr_p)->sqn = (unsigned)(((_val) >> 24)); \
        (_hdr_p)->__sqn_1 = (unsigned)(((_val))); \
    } while (0) /* auth_step_one.sqn[32;0] */

#define PIF_HEADER_GET_auth_step_one___sep4___0(_hdr_p) ((((_hdr_p)->__sep4_1 & 0xffffff) << 8) | ((_hdr_p)->__sep4_2)) /* auth_step_one.sep4 [32;0] */

#define PIF_HEADER_SET_auth_step_one___sep4___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__sep4_1 &= (unsigned)(0xff000000); \
        (_hdr_p)->__sep4_1 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__sep4_2 = (unsigned)(((_val))); \
    } while (0) /* auth_step_one.sep4[32;0] */

#define PIF_HEADER_GET_auth_step_one___sep4___1(_hdr_p) (((_hdr_p)->sep4 << 8) | (((_hdr_p)->__sep4_1 >> 24) & 0xff)) /* auth_step_one.sep4 [16;32] */

#define PIF_HEADER_SET_auth_step_one___sep4___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep4 = (unsigned)(((_val) >> 8)); \
        (_hdr_p)->__sep4_1 &= (unsigned)(0xffffff); \
        (_hdr_p)->__sep4_1 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.sep4[16;32] */

#define PIF_HEADER_GET_auth_step_one___tai___0(_hdr_p) ((((_hdr_p)->__tai_1 & 0xffffff) << 8) | ((_hdr_p)->__tai_2)) /* auth_step_one.tai [32;0] */

#define PIF_HEADER_SET_auth_step_one___tai___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__tai_1 &= (unsigned)(0xff000000); \
        (_hdr_p)->__tai_1 |= (unsigned)((((_val) >> 8) & 0xffffff)); \
        (_hdr_p)->__tai_2 = (unsigned)(((_val))); \
    } while (0) /* auth_step_one.tai[32;0] */

#define PIF_HEADER_GET_auth_step_one___tai___1(_hdr_p) (((_hdr_p)->tai << 8) | (((_hdr_p)->__tai_1 >> 24) & 0xff)) /* auth_step_one.tai [32;32] */

#define PIF_HEADER_SET_auth_step_one___tai___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->tai = (unsigned)(((_val) >> 8)); \
        (_hdr_p)->__tai_1 &= (unsigned)(0xffffff); \
        (_hdr_p)->__tai_1 |= (unsigned)((((_val) & 0xff) << 24)); \
    } while (0) /* auth_step_one.tai[32;32] */


/*
 * Metadata
 */

/* ingress::uekey_guti (8B) */
struct pif_header_ingress__uekey_guti {
    unsigned int ue_key:32;
    unsigned int guti:32;
};

/* ingress::uekey_guti field accessor macros */
#define PIF_HEADER_GET_ingress__uekey_guti___ue_key(_hdr_p) (((_hdr_p)->ue_key)) /* ingress::uekey_guti.ue_key [32;0] */

#define PIF_HEADER_SET_ingress__uekey_guti___ue_key(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_key = (unsigned)(((_val))); \
    } while (0) /* ingress::uekey_guti.ue_key[32;0] */

#define PIF_HEADER_GET_ingress__uekey_guti___guti(_hdr_p) (((_hdr_p)->guti)) /* ingress::uekey_guti.guti [32;0] */

#define PIF_HEADER_SET_ingress__uekey_guti___guti(_hdr_p, _val) \
    do { \
        (_hdr_p)->guti = (unsigned)(((_val))); \
    } while (0) /* ingress::uekey_guti.guti[32;0] */


/* tmpvar (2B) */
struct pif_header_tmpvar {
    unsigned int tmpUdpPort:16;
};

/* tmpvar field accessor macros */
#define PIF_HEADER_GET_tmpvar___tmpUdpPort(_hdr_p) (((_hdr_p)->tmpUdpPort)) /* tmpvar.tmpUdpPort [16;0] */

#define PIF_HEADER_SET_tmpvar___tmpUdpPort(_hdr_p, _val) \
    do { \
        (_hdr_p)->tmpUdpPort = (unsigned)(((_val))); \
    } while (0) /* tmpvar.tmpUdpPort[16;0] */


/* uekey_sgwteid (8B) */
struct pif_header_uekey_sgwteid {
    unsigned int ue_key:32;
    unsigned int sgw_teid:32;
};

/* uekey_sgwteid field accessor macros */
#define PIF_HEADER_GET_uekey_sgwteid___ue_key(_hdr_p) (((_hdr_p)->ue_key)) /* uekey_sgwteid.ue_key [32;0] */

#define PIF_HEADER_SET_uekey_sgwteid___ue_key(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_key = (unsigned)(((_val))); \
    } while (0) /* uekey_sgwteid.ue_key[32;0] */

#define PIF_HEADER_GET_uekey_sgwteid___sgw_teid(_hdr_p) (((_hdr_p)->sgw_teid)) /* uekey_sgwteid.sgw_teid [32;0] */

#define PIF_HEADER_SET_uekey_sgwteid___sgw_teid(_hdr_p, _val) \
    do { \
        (_hdr_p)->sgw_teid = (unsigned)(((_val))); \
    } while (0) /* uekey_sgwteid.sgw_teid[32;0] */


/* vlan (4B) */
struct pif_header_vlan {
    unsigned int pcp:3;
    unsigned int dei:1;
    unsigned int vid:12;
    unsigned int vlan_type:16;
};

/* vlan field accessor macros */
#define PIF_HEADER_GET_vlan___pcp(_hdr_p) (((_hdr_p)->pcp)) /* vlan.pcp [3;0] */

#define PIF_HEADER_SET_vlan___pcp(_hdr_p, _val) \
    do { \
        (_hdr_p)->pcp = (unsigned)(((_val))); \
    } while (0) /* vlan.pcp[3;0] */

#define PIF_HEADER_GET_vlan___dei(_hdr_p) (((_hdr_p)->dei)) /* vlan.dei [1;0] */

#define PIF_HEADER_SET_vlan___dei(_hdr_p, _val) \
    do { \
        (_hdr_p)->dei = (unsigned)(((_val))); \
    } while (0) /* vlan.dei[1;0] */

#define PIF_HEADER_GET_vlan___vid(_hdr_p) (((_hdr_p)->vid)) /* vlan.vid [12;0] */

#define PIF_HEADER_SET_vlan___vid(_hdr_p, _val) \
    do { \
        (_hdr_p)->vid = (unsigned)(((_val))); \
    } while (0) /* vlan.vid[12;0] */

#define PIF_HEADER_GET_vlan___vlan_type(_hdr_p) (((_hdr_p)->vlan_type)) /* vlan.vlan_type [16;0] */

#define PIF_HEADER_SET_vlan___vlan_type(_hdr_p, _val) \
    do { \
        (_hdr_p)->vlan_type = (unsigned)(((_val))); \
    } while (0) /* vlan.vlan_type[16;0] */


/* ingress::uekey_uestate (5B) */
struct pif_header_ingress__uekey_uestate {
    unsigned int ue_key:32;
    unsigned int ue_state:8;
};

/* ingress::uekey_uestate field accessor macros */
#define PIF_HEADER_GET_ingress__uekey_uestate___ue_key(_hdr_p) (((_hdr_p)->ue_key)) /* ingress::uekey_uestate.ue_key [32;0] */

#define PIF_HEADER_SET_ingress__uekey_uestate___ue_key(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_key = (unsigned)(((_val))); \
    } while (0) /* ingress::uekey_uestate.ue_key[32;0] */

#define PIF_HEADER_GET_ingress__uekey_uestate___ue_state(_hdr_p) (((_hdr_p)->ue_state)) /* ingress::uekey_uestate.ue_state [8;0] */

#define PIF_HEADER_SET_ingress__uekey_uestate___ue_state(_hdr_p, _val) \
    do { \
        (_hdr_p)->ue_state = (unsigned)(((_val))); \
    } while (0) /* ingress::uekey_uestate.ue_state[8;0] */


/* kv (32B) */
struct pif_header_kv {
    /* key1 [32;96] */
    unsigned int key1:32;
    /* key1 [32;64] */
    unsigned int __key1_1:32;
    /* key1 [32;32] */
    unsigned int __key1_2:32;
    /* key1 [32;0] */
    unsigned int __key1_3:32;
    /* value [32;96] */
    unsigned int value:32;
    /* value [32;64] */
    unsigned int __value_1:32;
    /* value [32;32] */
    unsigned int __value_2:32;
    /* value [32;0] */
    unsigned int __value_3:32;
};

/* kv field accessor macros */
#define PIF_HEADER_GET_kv___key1___0(_hdr_p) (((_hdr_p)->__key1_3)) /* kv.key1 [32;0] */

#define PIF_HEADER_SET_kv___key1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__key1_3 = (unsigned)(((_val))); \
    } while (0) /* kv.key1[32;0] */

#define PIF_HEADER_GET_kv___key1___1(_hdr_p) (((_hdr_p)->__key1_2)) /* kv.key1 [32;32] */

#define PIF_HEADER_SET_kv___key1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->__key1_2 = (unsigned)(((_val))); \
    } while (0) /* kv.key1[32;32] */

#define PIF_HEADER_GET_kv___key1___2(_hdr_p) (((_hdr_p)->__key1_1)) /* kv.key1 [32;64] */

#define PIF_HEADER_SET_kv___key1___2(_hdr_p, _val) \
    do { \
        (_hdr_p)->__key1_1 = (unsigned)(((_val))); \
    } while (0) /* kv.key1[32;64] */

#define PIF_HEADER_GET_kv___key1___3(_hdr_p) (((_hdr_p)->key1)) /* kv.key1 [32;96] */

#define PIF_HEADER_SET_kv___key1___3(_hdr_p, _val) \
    do { \
        (_hdr_p)->key1 = (unsigned)(((_val))); \
    } while (0) /* kv.key1[32;96] */

#define PIF_HEADER_GET_kv___value___0(_hdr_p) (((_hdr_p)->__value_3)) /* kv.value [32;0] */

#define PIF_HEADER_SET_kv___value___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__value_3 = (unsigned)(((_val))); \
    } while (0) /* kv.value[32;0] */

#define PIF_HEADER_GET_kv___value___1(_hdr_p) (((_hdr_p)->__value_2)) /* kv.value [32;32] */

#define PIF_HEADER_SET_kv___value___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->__value_2 = (unsigned)(((_val))); \
    } while (0) /* kv.value[32;32] */

#define PIF_HEADER_GET_kv___value___2(_hdr_p) (((_hdr_p)->__value_1)) /* kv.value [32;64] */

#define PIF_HEADER_SET_kv___value___2(_hdr_p, _val) \
    do { \
        (_hdr_p)->__value_1 = (unsigned)(((_val))); \
    } while (0) /* kv.value[32;64] */

#define PIF_HEADER_GET_kv___value___3(_hdr_p) (((_hdr_p)->value)) /* kv.value [32;96] */

#define PIF_HEADER_SET_kv___value___3(_hdr_p, _val) \
    do { \
        (_hdr_p)->value = (unsigned)(((_val))); \
    } while (0) /* kv.value[32;96] */


/* standard_metadata (16B) */
struct pif_header_standard_metadata {
    unsigned int clone_spec:32;
    unsigned int egress_spec:16;
    unsigned int egress_port:16;
    unsigned int ingress_port:16;
    unsigned int packet_length:14;
    unsigned int checksum_error:1;
    unsigned int _padding_0:1;
    unsigned int egress_instance:10;
    unsigned int parser_error_location:8;
    unsigned int instance_type:4;
    unsigned int parser_status:3;
    unsigned int _padding_1:7;
};

/* standard_metadata field accessor macros */
#define PIF_HEADER_GET_standard_metadata___clone_spec(_hdr_p) (((_hdr_p)->clone_spec)) /* standard_metadata.clone_spec [32;0] */

#define PIF_HEADER_SET_standard_metadata___clone_spec(_hdr_p, _val) \
    do { \
        (_hdr_p)->clone_spec = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.clone_spec[32;0] */

#define PIF_HEADER_GET_standard_metadata___egress_spec(_hdr_p) (((_hdr_p)->egress_spec)) /* standard_metadata.egress_spec [16;0] */

#define PIF_HEADER_SET_standard_metadata___egress_spec(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_spec = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.egress_spec[16;0] */

#define PIF_HEADER_GET_standard_metadata___egress_port(_hdr_p) (((_hdr_p)->egress_port)) /* standard_metadata.egress_port [16;0] */

#define PIF_HEADER_SET_standard_metadata___egress_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_port = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.egress_port[16;0] */

#define PIF_HEADER_GET_standard_metadata___ingress_port(_hdr_p) (((_hdr_p)->ingress_port)) /* standard_metadata.ingress_port [16;0] */

#define PIF_HEADER_SET_standard_metadata___ingress_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->ingress_port = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.ingress_port[16;0] */

#define PIF_HEADER_GET_standard_metadata___packet_length(_hdr_p) (((_hdr_p)->packet_length)) /* standard_metadata.packet_length [14;0] */

#define PIF_HEADER_SET_standard_metadata___packet_length(_hdr_p, _val) \
    do { \
        (_hdr_p)->packet_length = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.packet_length[14;0] */

#define PIF_HEADER_GET_standard_metadata___checksum_error(_hdr_p) (((_hdr_p)->checksum_error)) /* standard_metadata.checksum_error [1;0] */

#define PIF_HEADER_SET_standard_metadata___checksum_error(_hdr_p, _val) \
    do { \
        (_hdr_p)->checksum_error = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.checksum_error[1;0] */

#define PIF_HEADER_GET_standard_metadata____padding_0(_hdr_p) (((_hdr_p)->_padding_0)) /* standard_metadata._padding_0 [1;0] */

#define PIF_HEADER_SET_standard_metadata____padding_0(_hdr_p, _val) \
    do { \
        (_hdr_p)->_padding_0 = (unsigned)(((_val))); \
    } while (0) /* standard_metadata._padding_0[1;0] */

#define PIF_HEADER_GET_standard_metadata___egress_instance(_hdr_p) (((_hdr_p)->egress_instance)) /* standard_metadata.egress_instance [10;0] */

#define PIF_HEADER_SET_standard_metadata___egress_instance(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_instance = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.egress_instance[10;0] */

#define PIF_HEADER_GET_standard_metadata___parser_error_location(_hdr_p) (((_hdr_p)->parser_error_location)) /* standard_metadata.parser_error_location [8;0] */

#define PIF_HEADER_SET_standard_metadata___parser_error_location(_hdr_p, _val) \
    do { \
        (_hdr_p)->parser_error_location = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.parser_error_location[8;0] */

#define PIF_HEADER_GET_standard_metadata___instance_type(_hdr_p) (((_hdr_p)->instance_type)) /* standard_metadata.instance_type [4;0] */

#define PIF_HEADER_SET_standard_metadata___instance_type(_hdr_p, _val) \
    do { \
        (_hdr_p)->instance_type = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.instance_type[4;0] */

#define PIF_HEADER_GET_standard_metadata___parser_status(_hdr_p) (((_hdr_p)->parser_status)) /* standard_metadata.parser_status [3;0] */

#define PIF_HEADER_SET_standard_metadata___parser_status(_hdr_p, _val) \
    do { \
        (_hdr_p)->parser_status = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.parser_status[3;0] */

#define PIF_HEADER_GET_standard_metadata____padding_1(_hdr_p) (((_hdr_p)->_padding_1)) /* standard_metadata._padding_1 [7;0] */

#define PIF_HEADER_SET_standard_metadata____padding_1(_hdr_p, _val) \
    do { \
        (_hdr_p)->_padding_1 = (unsigned)(((_val))); \
    } while (0) /* standard_metadata._padding_1[7;0] */


/* ingress::scalars (4B) */
struct pif_header_ingress__scalars {
    unsigned int hasReturned_0:1;
    unsigned int _padding_0:31;
};

/* ingress::scalars field accessor macros */
#define PIF_HEADER_GET_ingress__scalars___hasReturned_0(_hdr_p) (((_hdr_p)->hasReturned_0)) /* ingress::scalars.hasReturned_0 [1;0] */

#define PIF_HEADER_SET_ingress__scalars___hasReturned_0(_hdr_p, _val) \
    do { \
        (_hdr_p)->hasReturned_0 = (unsigned)(((_val))); \
    } while (0) /* ingress::scalars.hasReturned_0[1;0] */

#define PIF_HEADER_GET_ingress__scalars____padding_0(_hdr_p) (((_hdr_p)->_padding_0)) /* ingress::scalars._padding_0 [31;0] */

#define PIF_HEADER_SET_ingress__scalars____padding_0(_hdr_p, _val) \
    do { \
        (_hdr_p)->_padding_0 = (unsigned)(((_val))); \
    } while (0) /* ingress::scalars._padding_0[31;0] */



/*
 * Registers
 */

#endif /* __PIF_HEADERS_H__ */
