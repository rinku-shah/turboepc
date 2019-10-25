/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_AUTH_STEP_ONE_H__
#define __PIF_PLUGIN_AUTH_STEP_ONE_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* auth_step_one (73B) */
struct pif_plugin_auth_step_one {
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



#define PIF_PLUGIN_auth_step_one_T __lmem struct pif_plugin_auth_step_one

/*
 * Access function prototypes
 */

int pif_plugin_hdr_auth_step_one_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_auth_step_one_T *pif_plugin_hdr_get_auth_step_one(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_auth_step_one_T *pif_plugin_hdr_readonly_get_auth_step_one(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_auth_step_one_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_auth_step_one_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_auth_step_one_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_auth_step_one_VALID(_ctl);
}

__forceinline PIF_PLUGIN_auth_step_one_T *pif_plugin_hdr_get_auth_step_one(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_auth_step_one_DIRTY(_ctl);
    return (PIF_PLUGIN_auth_step_one_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_auth_step_one_OFF_LW);
}

__forceinline PIF_PLUGIN_auth_step_one_T *pif_plugin_hdr_readonly_get_auth_step_one(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_auth_step_one_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_auth_step_one_OFF_LW);
}

__forceinline int pif_plugin_hdr_auth_step_one_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T6_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_auth_step_one_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_auth_step_one_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_auth_step_one_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_auth_step_one_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_AUTH_STEP_ONE_H__ */
