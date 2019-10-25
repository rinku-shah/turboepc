/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_UE_CONTEXT_REL_REQ_H__
#define __PIF_PLUGIN_UE_CONTEXT_REL_REQ_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* ue_context_rel_req (34B) */
struct pif_plugin_ue_context_rel_req {
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



#define PIF_PLUGIN_ue_context_rel_req_T __lmem struct pif_plugin_ue_context_rel_req

/*
 * Access function prototypes
 */

int pif_plugin_hdr_ue_context_rel_req_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_ue_context_rel_req_T *pif_plugin_hdr_get_ue_context_rel_req(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_ue_context_rel_req_T *pif_plugin_hdr_readonly_get_ue_context_rel_req(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_ue_context_rel_req_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_ue_context_rel_req_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_ue_context_rel_req_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_ue_context_rel_req_VALID(_ctl);
}

__forceinline PIF_PLUGIN_ue_context_rel_req_T *pif_plugin_hdr_get_ue_context_rel_req(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_ue_context_rel_req_DIRTY(_ctl);
    return (PIF_PLUGIN_ue_context_rel_req_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_ue_context_rel_req_OFF_LW);
}

__forceinline PIF_PLUGIN_ue_context_rel_req_T *pif_plugin_hdr_readonly_get_ue_context_rel_req(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_ue_context_rel_req_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_ue_context_rel_req_OFF_LW);
}

__forceinline int pif_plugin_hdr_ue_context_rel_req_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T6_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_ue_context_rel_req_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_ue_context_rel_req_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_ue_context_rel_req_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_ue_context_rel_req_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_UE_CONTEXT_REL_REQ_H__ */
