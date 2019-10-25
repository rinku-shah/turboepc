/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_SEND_APN_H__
#define __PIF_PLUGIN_SEND_APN_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* send_apn (18B) */
struct pif_plugin_send_apn {
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



#define PIF_PLUGIN_send_apn_T __lmem struct pif_plugin_send_apn

/*
 * Access function prototypes
 */

int pif_plugin_hdr_send_apn_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_send_apn_T *pif_plugin_hdr_get_send_apn(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_send_apn_T *pif_plugin_hdr_readonly_get_send_apn(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_send_apn_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_send_apn_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_send_apn_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_send_apn_VALID(_ctl);
}

__forceinline PIF_PLUGIN_send_apn_T *pif_plugin_hdr_get_send_apn(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_send_apn_DIRTY(_ctl);
    return (PIF_PLUGIN_send_apn_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_send_apn_OFF_LW);
}

__forceinline PIF_PLUGIN_send_apn_T *pif_plugin_hdr_readonly_get_send_apn(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_send_apn_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_send_apn_OFF_LW);
}

__forceinline int pif_plugin_hdr_send_apn_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T6_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_send_apn_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_send_apn_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_send_apn_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_send_apn_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_SEND_APN_H__ */
