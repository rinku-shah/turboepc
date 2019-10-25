/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_OFFLOAD_INITIAL_CTXT_SETUP_RESP_H__
#define __PIF_PLUGIN_OFFLOAD_INITIAL_CTXT_SETUP_RESP_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* offload_initial_ctxt_setup_resp (34B) */
struct pif_plugin_offload_initial_ctxt_setup_resp {
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



#define PIF_PLUGIN_offload_initial_ctxt_setup_resp_T __lmem struct pif_plugin_offload_initial_ctxt_setup_resp

/*
 * Access function prototypes
 */

int pif_plugin_hdr_offload_initial_ctxt_setup_resp_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_offload_initial_ctxt_setup_resp_T *pif_plugin_hdr_get_offload_initial_ctxt_setup_resp(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_offload_initial_ctxt_setup_resp_T *pif_plugin_hdr_readonly_get_offload_initial_ctxt_setup_resp(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_offload_initial_ctxt_setup_resp_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_offload_initial_ctxt_setup_resp_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_offload_initial_ctxt_setup_resp_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_offload_initial_ctxt_setup_resp_VALID(_ctl);
}

__forceinline PIF_PLUGIN_offload_initial_ctxt_setup_resp_T *pif_plugin_hdr_get_offload_initial_ctxt_setup_resp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_offload_initial_ctxt_setup_resp_DIRTY(_ctl);
    return (PIF_PLUGIN_offload_initial_ctxt_setup_resp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_offload_initial_ctxt_setup_resp_OFF_LW);
}

__forceinline PIF_PLUGIN_offload_initial_ctxt_setup_resp_T *pif_plugin_hdr_readonly_get_offload_initial_ctxt_setup_resp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_offload_initial_ctxt_setup_resp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_offload_initial_ctxt_setup_resp_OFF_LW);
}

__forceinline int pif_plugin_hdr_offload_initial_ctxt_setup_resp_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T8_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_offload_initial_ctxt_setup_resp_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_offload_initial_ctxt_setup_resp_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_offload_initial_ctxt_setup_resp_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_offload_initial_ctxt_setup_resp_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_OFFLOAD_INITIAL_CTXT_SETUP_RESP_H__ */
