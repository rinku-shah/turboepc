/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_DATA_H__
#define __PIF_PLUGIN_DATA_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* data (7B) */
struct pif_plugin_data {
    unsigned int epc_traffic_code:8;
    /* sep [24;24] */
    unsigned int sep:24;
    /* sep [24;0] */
    unsigned int __sep_1:24;
};

/* data field accessor macros */
#define PIF_HEADER_GET_data___epc_traffic_code(_hdr_p) (((_hdr_p)->epc_traffic_code)) /* data.epc_traffic_code [8;0] */

#define PIF_HEADER_SET_data___epc_traffic_code(_hdr_p, _val) \
    do { \
        (_hdr_p)->epc_traffic_code = (unsigned)(((_val))); \
    } while (0) /* data.epc_traffic_code[8;0] */

#define PIF_HEADER_GET_data___sep___0(_hdr_p) ((((_hdr_p)->sep & 0xff) << 24) | ((_hdr_p)->__sep_1)) /* data.sep [32;0] */

#define PIF_HEADER_SET_data___sep___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep &= (unsigned)(0xffffff00); \
        (_hdr_p)->sep |= (unsigned)((((_val) >> 24) & 0xff)); \
        (_hdr_p)->__sep_1 = (unsigned)(((_val))); \
    } while (0) /* data.sep[32;0] */

#define PIF_HEADER_GET_data___sep___1(_hdr_p) ((((_hdr_p)->sep >> 8) & 0xffff)) /* data.sep [16;32] */

#define PIF_HEADER_SET_data___sep___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep &= (unsigned)(0xff0000ff); \
        (_hdr_p)->sep |= (unsigned)((((_val) & 0xffff) << 8)); \
    } while (0) /* data.sep[16;32] */



#define PIF_PLUGIN_data_T __lmem struct pif_plugin_data

/*
 * Access function prototypes
 */

int pif_plugin_hdr_data_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_data_T *pif_plugin_hdr_get_data(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_data_T *pif_plugin_hdr_readonly_get_data(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_data_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_data_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_data_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_data_VALID(_ctl);
}

__forceinline PIF_PLUGIN_data_T *pif_plugin_hdr_get_data(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_data_DIRTY(_ctl);
    return (PIF_PLUGIN_data_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_data_OFF_LW);
}

__forceinline PIF_PLUGIN_data_T *pif_plugin_hdr_readonly_get_data(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_data_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_data_OFF_LW);
}

__forceinline int pif_plugin_hdr_data_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T5_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_data_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_data_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_data_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_data_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_DATA_H__ */
