/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_INITIAL_CTXT_SETUP_RESP_H__
#define __PIF_PLUGIN_INITIAL_CTXT_SETUP_RESP_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* initial_ctxt_setup_resp (24B) */
struct pif_plugin_initial_ctxt_setup_resp {
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



#define PIF_PLUGIN_initial_ctxt_setup_resp_T __lmem struct pif_plugin_initial_ctxt_setup_resp

/*
 * Access function prototypes
 */

int pif_plugin_hdr_initial_ctxt_setup_resp_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_initial_ctxt_setup_resp_T *pif_plugin_hdr_get_initial_ctxt_setup_resp(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_initial_ctxt_setup_resp_T *pif_plugin_hdr_readonly_get_initial_ctxt_setup_resp(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_initial_ctxt_setup_resp_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_initial_ctxt_setup_resp_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_initial_ctxt_setup_resp_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_initial_ctxt_setup_resp_VALID(_ctl);
}

__forceinline PIF_PLUGIN_initial_ctxt_setup_resp_T *pif_plugin_hdr_get_initial_ctxt_setup_resp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_initial_ctxt_setup_resp_DIRTY(_ctl);
    return (PIF_PLUGIN_initial_ctxt_setup_resp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_initial_ctxt_setup_resp_OFF_LW);
}

__forceinline PIF_PLUGIN_initial_ctxt_setup_resp_T *pif_plugin_hdr_readonly_get_initial_ctxt_setup_resp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_initial_ctxt_setup_resp_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_initial_ctxt_setup_resp_OFF_LW);
}

__forceinline int pif_plugin_hdr_initial_ctxt_setup_resp_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T6_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_initial_ctxt_setup_resp_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_initial_ctxt_setup_resp_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_initial_ctxt_setup_resp_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_initial_ctxt_setup_resp_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_INITIAL_CTXT_SETUP_RESP_H__ */
