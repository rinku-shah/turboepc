/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <pif_common.h>

/* Table related defines */

/* Table 0 : ingress::ip_op_tun_s2_downlink */
#define PIF_TABLE_ACTIONDATA_SIZE_0 16
#define PIF_TABLE_MAX_ENTRIES_0 65001
#define PIF_TABLE_SHIFT_0 4

/* Table 1 : ingress::uekey_guti_map */
#define PIF_TABLE_ACTIONDATA_SIZE_1 16
#define PIF_TABLE_MAX_ENTRIES_1 65001
#define PIF_TABLE_SHIFT_1 4

/* Table 2 : ingress::uekey_uestate_map */
#define PIF_TABLE_ACTIONDATA_SIZE_2 16
#define PIF_TABLE_MAX_ENTRIES_2 65001
#define PIF_TABLE_SHIFT_2 4

/* Table 3 : ingress::arp_tbl */
#define PIF_TABLE_ACTIONDATA_SIZE_3 16
#define PIF_TABLE_MAX_ENTRIES_3 65001
#define PIF_TABLE_SHIFT_3 4

/* Table 4 : ingress::ip_op_tun_s2_uplink */
#define PIF_TABLE_ACTIONDATA_SIZE_4 16
#define PIF_TABLE_MAX_ENTRIES_4 65001
#define PIF_TABLE_SHIFT_4 4

/* DCFL related table storage */
__export __emem __align256K uint32_t dcfl_ct_0[DCFL_TABLE_SIZE / 4];
__export __emem __align256K uint32_t dcfl_ct_1[DCFL_TABLE_SIZE / 4];
__export __emem __align256K uint32_t dcfl_ct_2[DCFL_TABLE_SIZE / 4];
__export __emem __align256K uint32_t dcfl_ct_3[DCFL_TABLE_SIZE / 4];
__export __emem __align256K uint32_t dcfl_ct_4[DCFL_TABLE_SIZE / 4];

/* PIF related table storage */
__export __emem uint32_t pif_actiondata_table_0_ingress__ip_op_tun_s2_downlink[2 * PIF_TABLE_MAX_ENTRIES_0 * (PIF_TABLE_ACTIONDATA_SIZE_0 / 4)];
__export __emem uint32_t pif_actiondata_table_1_ingress__uekey_guti_map[2 * PIF_TABLE_MAX_ENTRIES_1 * (PIF_TABLE_ACTIONDATA_SIZE_1 / 4)];
__export __emem uint32_t pif_actiondata_table_2_ingress__uekey_uestate_map[2 * PIF_TABLE_MAX_ENTRIES_2 * (PIF_TABLE_ACTIONDATA_SIZE_2 / 4)];
__export __emem uint32_t pif_actiondata_table_3_ingress__arp_tbl[2 * PIF_TABLE_MAX_ENTRIES_3 * (PIF_TABLE_ACTIONDATA_SIZE_3 / 4)];
__export __emem uint32_t pif_actiondata_table_4_ingress__ip_op_tun_s2_uplink[2 * PIF_TABLE_MAX_ENTRIES_4 * (PIF_TABLE_ACTIONDATA_SIZE_4 / 4)];

__export __emem struct pif_actiondata_table_desc pif_actiondata_table_descs[PIF_TABLE_COUNT] = {
        {
            /* .table_address = */ 0,
            /* .rule_count = */ 0,
            /* .reserved = */ 0,
            /* .record_shift = */  PIF_TABLE_SHIFT_0,
            /* .flags = */ 0,
        },
        {
            /* .table_address = */ 0,
            /* .rule_count = */ 0,
            /* .reserved = */ 0,
            /* .record_shift = */  PIF_TABLE_SHIFT_1,
            /* .flags = */ 0,
        },
        {
            /* .table_address = */ 0,
            /* .rule_count = */ 0,
            /* .reserved = */ 0,
            /* .record_shift = */  PIF_TABLE_SHIFT_2,
            /* .flags = */ 0,
        },
        {
            /* .table_address = */ 0,
            /* .rule_count = */ 0,
            /* .reserved = */ 0,
            /* .record_shift = */  PIF_TABLE_SHIFT_3,
            /* .flags = */ 0,
        },
        {
            /* .table_address = */ 0,
            /* .rule_count = */ 0,
            /* .reserved = */ 0,
            /* .record_shift = */  PIF_TABLE_SHIFT_4,
            /* .flags = */ 0,
        },
    };
