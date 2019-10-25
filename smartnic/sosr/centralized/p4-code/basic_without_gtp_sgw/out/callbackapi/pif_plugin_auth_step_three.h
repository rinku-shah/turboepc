/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_AUTH_STEP_THREE_H__
#define __PIF_PLUGIN_AUTH_STEP_THREE_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* auth_step_three (18B) */
struct pif_plugin_auth_step_three {
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



#define PIF_PLUGIN_auth_step_three_T __lmem struct pif_plugin_auth_step_three

/*
 * Access function prototypes
 */

int pif_plugin_hdr_auth_step_three_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_auth_step_three_T *pif_plugin_hdr_get_auth_step_three(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_auth_step_three_T *pif_plugin_hdr_readonly_get_auth_step_three(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_auth_step_three_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_auth_step_three_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_auth_step_three_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_auth_step_three_VALID(_ctl);
}

__forceinline PIF_PLUGIN_auth_step_three_T *pif_plugin_hdr_get_auth_step_three(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_auth_step_three_DIRTY(_ctl);
    return (PIF_PLUGIN_auth_step_three_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_auth_step_three_OFF_LW);
}

__forceinline PIF_PLUGIN_auth_step_three_T *pif_plugin_hdr_readonly_get_auth_step_three(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_auth_step_three_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_auth_step_three_OFF_LW);
}

__forceinline int pif_plugin_hdr_auth_step_three_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T6_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_auth_step_three_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_auth_step_three_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_auth_step_three_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_auth_step_three_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_AUTH_STEP_THREE_H__ */
