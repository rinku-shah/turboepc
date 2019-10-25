/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_TCP_H__
#define __PIF_PLUGIN_TCP_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* tcp (20B) */
struct pif_plugin_tcp {
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



#define PIF_PLUGIN_tcp_T __lmem struct pif_plugin_tcp

/*
 * Access function prototypes
 */

int pif_plugin_hdr_tcp_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_tcp_T *pif_plugin_hdr_get_tcp(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_tcp_T *pif_plugin_hdr_readonly_get_tcp(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_tcp_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_tcp_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_tcp_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_tcp_VALID(_ctl);
}

__forceinline PIF_PLUGIN_tcp_T *pif_plugin_hdr_get_tcp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_tcp_DIRTY(_ctl);
    return (PIF_PLUGIN_tcp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_tcp_OFF_LW);
}

__forceinline PIF_PLUGIN_tcp_T *pif_plugin_hdr_readonly_get_tcp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_tcp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_tcp_OFF_LW);
}

__forceinline int pif_plugin_hdr_tcp_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T6_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_tcp_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_tcp_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_tcp_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_tcp_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_TCP_H__ */
