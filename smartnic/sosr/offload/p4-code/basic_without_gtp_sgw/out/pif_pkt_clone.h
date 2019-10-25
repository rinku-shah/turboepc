/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PKT_CLONE_H__
#define __PIF_PKT_CLONE_H__
#include <nfp.h>

#define PIF_MAX_NUM_CLONES      1

/* Generated C source defining pkt_recurse related bits and bobs  */
/* Warning: your edits to this file may be lost */


#define PIF_PKT_CLONE_FIELDLIST_ID_fl 1
#define PIF_PKT_CLONE_FIELDLIST_LAST 1

#define PIF_CLONE_PACKET
extern __nnr uint32_t clone_field_list;

void pif_clone_pkt_with_cls_pkt_info();
uint32_t pif_clone_packet_submit(__lmem uint32_t *parrep, uint32_t replication_id);

void pif_clone_packet(__lmem uint32_t *parrep, uint32_t clone_id);

void pif_clone_i2e(__lmem uint32_t *parrep, uint32_t clone_id);

#endif /* __PIF_PKT_CLONE_H__ */
