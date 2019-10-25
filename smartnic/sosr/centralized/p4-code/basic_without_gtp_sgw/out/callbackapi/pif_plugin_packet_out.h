/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_PACKET_OUT_H__
#define __PIF_PLUGIN_PACKET_OUT_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* packet_out (2B) */
struct pif_plugin_packet_out {
    unsigned int egress_port:16;
};

/* packet_out field accessor macros */
#define PIF_HEADER_GET_packet_out___egress_port(_hdr_p) (((_hdr_p)->egress_port)) /* packet_out.egress_port [16;0] */

#define PIF_HEADER_SET_packet_out___egress_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_port = (unsigned)(((_val))); \
    } while (0) /* packet_out.egress_port[16;0] */



#define PIF_PLUGIN_packet_out_T __lmem struct pif_plugin_packet_out

/*
 * Access function prototypes
 */

int pif_plugin_hdr_packet_out_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_packet_out_T *pif_plugin_hdr_get_packet_out(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_packet_out_T *pif_plugin_hdr_readonly_get_packet_out(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_packet_out_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_packet_out_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_packet_out_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_packet_out_VALID(_ctl);
}

__forceinline PIF_PLUGIN_packet_out_T *pif_plugin_hdr_get_packet_out(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_packet_out_DIRTY(_ctl);
    return (PIF_PLUGIN_packet_out_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_packet_out_OFF_LW);
}

__forceinline PIF_PLUGIN_packet_out_T *pif_plugin_hdr_readonly_get_packet_out(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_packet_out_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_packet_out_OFF_LW);
}

__forceinline int pif_plugin_hdr_packet_out_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T1_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_packet_out_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_packet_out_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_packet_out_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_packet_out_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_PACKET_OUT_H__ */
