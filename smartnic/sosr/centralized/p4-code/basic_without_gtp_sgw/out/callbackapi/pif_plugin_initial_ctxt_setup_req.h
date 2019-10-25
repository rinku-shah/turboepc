/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_INITIAL_CTXT_SETUP_REQ_H__
#define __PIF_PLUGIN_INITIAL_CTXT_SETUP_REQ_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* initial_ctxt_setup_req (11B) */
struct pif_plugin_initial_ctxt_setup_req {
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



#define PIF_PLUGIN_initial_ctxt_setup_req_T __lmem struct pif_plugin_initial_ctxt_setup_req

/*
 * Access function prototypes
 */

int pif_plugin_hdr_initial_ctxt_setup_req_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_initial_ctxt_setup_req_T *pif_plugin_hdr_get_initial_ctxt_setup_req(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_initial_ctxt_setup_req_T *pif_plugin_hdr_readonly_get_initial_ctxt_setup_req(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_initial_ctxt_setup_req_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_initial_ctxt_setup_req_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_initial_ctxt_setup_req_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_initial_ctxt_setup_req_VALID(_ctl);
}

__forceinline PIF_PLUGIN_initial_ctxt_setup_req_T *pif_plugin_hdr_get_initial_ctxt_setup_req(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_initial_ctxt_setup_req_DIRTY(_ctl);
    return (PIF_PLUGIN_initial_ctxt_setup_req_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_initial_ctxt_setup_req_OFF_LW);
}

__forceinline PIF_PLUGIN_initial_ctxt_setup_req_T *pif_plugin_hdr_readonly_get_initial_ctxt_setup_req(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_initial_ctxt_setup_req_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_initial_ctxt_setup_req_OFF_LW);
}

__forceinline int pif_plugin_hdr_initial_ctxt_setup_req_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T10_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_initial_ctxt_setup_req_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_initial_ctxt_setup_req_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_initial_ctxt_setup_req_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_initial_ctxt_setup_req_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_INITIAL_CTXT_SETUP_REQ_H__ */
