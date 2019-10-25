/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_NAS_STEP_TWO_H__
#define __PIF_PLUGIN_NAS_STEP_TWO_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* nas_step_two (30B) */
struct pif_plugin_nas_step_two {
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



#define PIF_PLUGIN_nas_step_two_T __lmem struct pif_plugin_nas_step_two

/*
 * Access function prototypes
 */

int pif_plugin_hdr_nas_step_two_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_nas_step_two_T *pif_plugin_hdr_get_nas_step_two(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_nas_step_two_T *pif_plugin_hdr_readonly_get_nas_step_two(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_nas_step_two_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_nas_step_two_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_nas_step_two_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_nas_step_two_VALID(_ctl);
}

__forceinline PIF_PLUGIN_nas_step_two_T *pif_plugin_hdr_get_nas_step_two(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_nas_step_two_DIRTY(_ctl);
    return (PIF_PLUGIN_nas_step_two_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_nas_step_two_OFF_LW);
}

__forceinline PIF_PLUGIN_nas_step_two_T *pif_plugin_hdr_readonly_get_nas_step_two(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_nas_step_two_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_nas_step_two_OFF_LW);
}

__forceinline int pif_plugin_hdr_nas_step_two_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T6_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_nas_step_two_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_nas_step_two_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_nas_step_two_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_nas_step_two_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_NAS_STEP_TWO_H__ */
