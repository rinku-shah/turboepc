/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_UE_SERVICE_REQ_H__
#define __PIF_PLUGIN_UE_SERVICE_REQ_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* ue_service_req (24B) */
struct pif_plugin_ue_service_req {
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



#define PIF_PLUGIN_ue_service_req_T __lmem struct pif_plugin_ue_service_req

/*
 * Access function prototypes
 */

int pif_plugin_hdr_ue_service_req_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_ue_service_req_T *pif_plugin_hdr_get_ue_service_req(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_ue_service_req_T *pif_plugin_hdr_readonly_get_ue_service_req(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_ue_service_req_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_ue_service_req_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_ue_service_req_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_ue_service_req_VALID(_ctl);
}

__forceinline PIF_PLUGIN_ue_service_req_T *pif_plugin_hdr_get_ue_service_req(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_ue_service_req_DIRTY(_ctl);
    return (PIF_PLUGIN_ue_service_req_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_ue_service_req_OFF_LW);
}

__forceinline PIF_PLUGIN_ue_service_req_T *pif_plugin_hdr_readonly_get_ue_service_req(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_ue_service_req_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_ue_service_req_OFF_LW);
}

__forceinline int pif_plugin_hdr_ue_service_req_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T6_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_ue_service_req_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_ue_service_req_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_ue_service_req_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_ue_service_req_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_UE_SERVICE_REQ_H__ */
