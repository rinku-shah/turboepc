/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_UE_CONTEXT_REL_COMMAND_H__
#define __PIF_PLUGIN_UE_CONTEXT_REL_COMMAND_H__

/* This file is generated, edit at your peril */

/*
 * Header type definition
 */

/* ue_context_rel_command (7B) */
struct pif_plugin_ue_context_rel_command {
    unsigned int epc_traffic_code:8;
    /* sep1 [24;24] */
    unsigned int sep1:24;
    /* sep1 [24;0] */
    unsigned int __sep1_1:24;
};

/* ue_context_rel_command field accessor macros */
#define PIF_HEADER_GET_ue_context_rel_command___epc_traffic_code(_hdr_p) (((_hdr_p)->epc_traffic_code)) /* ue_context_rel_command.epc_traffic_code [8;0] */

#define PIF_HEADER_SET_ue_context_rel_command___epc_traffic_code(_hdr_p, _val) \
    do { \
        (_hdr_p)->epc_traffic_code = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_command.epc_traffic_code[8;0] */

#define PIF_HEADER_GET_ue_context_rel_command___sep1___0(_hdr_p) ((((_hdr_p)->sep1 & 0xff) << 24) | ((_hdr_p)->__sep1_1)) /* ue_context_rel_command.sep1 [32;0] */

#define PIF_HEADER_SET_ue_context_rel_command___sep1___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xffffff00); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) >> 24) & 0xff)); \
        (_hdr_p)->__sep1_1 = (unsigned)(((_val))); \
    } while (0) /* ue_context_rel_command.sep1[32;0] */

#define PIF_HEADER_GET_ue_context_rel_command___sep1___1(_hdr_p) ((((_hdr_p)->sep1 >> 8) & 0xffff)) /* ue_context_rel_command.sep1 [16;32] */

#define PIF_HEADER_SET_ue_context_rel_command___sep1___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->sep1 &= (unsigned)(0xff0000ff); \
        (_hdr_p)->sep1 |= (unsigned)((((_val) & 0xffff) << 8)); \
    } while (0) /* ue_context_rel_command.sep1[16;32] */



#define PIF_PLUGIN_ue_context_rel_command_T __lmem struct pif_plugin_ue_context_rel_command

/*
 * Access function prototypes
 */

int pif_plugin_hdr_ue_context_rel_command_present(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_ue_context_rel_command_T *pif_plugin_hdr_get_ue_context_rel_command(EXTRACTED_HEADERS_T *extracted_headers);

PIF_PLUGIN_ue_context_rel_command_T *pif_plugin_hdr_readonly_get_ue_context_rel_command(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_ue_context_rel_command_add(EXTRACTED_HEADERS_T *extracted_headers);

int pif_plugin_hdr_ue_context_rel_command_remove(EXTRACTED_HEADERS_T *extracted_headers);






/*
 * Access function implementations
 */

#include "pif_parrep.h"

__forceinline int pif_plugin_hdr_ue_context_rel_command_present(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return PIF_PARREP_ue_context_rel_command_VALID(_ctl);
}

__forceinline PIF_PLUGIN_ue_context_rel_command_T *pif_plugin_hdr_get_ue_context_rel_command(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    PIF_PARREP_SET_ue_context_rel_command_DIRTY(_ctl);
    return (PIF_PLUGIN_ue_context_rel_command_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_ue_context_rel_command_OFF_LW);
}

__forceinline PIF_PLUGIN_ue_context_rel_command_T *pif_plugin_hdr_readonly_get_ue_context_rel_command(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    return (PIF_PLUGIN_ue_context_rel_command_T *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_ue_context_rel_command_OFF_LW);
}

__forceinline int pif_plugin_hdr_ue_context_rel_command_add(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (PIF_PARREP_T9_VALID(_ctl))
        return -1; /* either already present or incompatible header combination */
    PIF_PARREP_SET_ue_context_rel_command_VALID(_ctl);
    return 0;
}

__forceinline int pif_plugin_hdr_ue_context_rel_command_remove(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_parrep_ctldata *_ctl = (__lmem struct pif_parrep_ctldata *)extracted_headers;
    if (!PIF_PARREP_ue_context_rel_command_VALID(_ctl))
        return -1; /* header is not present */
    PIF_PARREP_CLEAR_ue_context_rel_command_VALID(_ctl);
    return 0;
}

#endif /* __PIF_PLUGIN_UE_CONTEXT_REL_COMMAND_H__ */
