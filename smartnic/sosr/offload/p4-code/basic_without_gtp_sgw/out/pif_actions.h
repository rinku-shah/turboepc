/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_ACTIONS_H__
#define __PIF_ACTIONS_H__

/* Warning: generated file - your edits to this file may be lost */

/* Action operation IDs */

#define PIF_ACTION_ID_ingress__act_8 0
#define PIF_ACTION_ID_ingress__fwd_act 1
#define PIF_ACTION_ID_ingress__act_9 2
#define PIF_ACTION_ID_ingress__act_0 3
#define PIF_ACTION_ID_ingress__act_1 4
#define PIF_ACTION_ID_ingress__act_2 5
#define PIF_ACTION_ID_ingress__act_3 6
#define PIF_ACTION_ID_ingress__act_4 7
#define PIF_ACTION_ID_ingress__act_5 8
#define PIF_ACTION_ID_ingress__act_6 9
#define PIF_ACTION_ID_ingress__act_7 10
#define PIF_ACTION_ID_ingress__populate_ip_op_tun_s2_downlink 11
#define PIF_ACTION_ID_ingress__populate_service_req_uekey_sgwteid_map 12
#define PIF_ACTION_ID_ingress__act 13
#define PIF_ACTION_ID_ingress__populate_uekey_uestate_map 14
#define PIF_ACTION_ID_ingress__populate_ip_op_tun_s2_uplink 15
#define PIF_ACTION_ID_ingress__populate_ctxt_setup_uekey_sgwteid_map 16
#define PIF_ACTION_ID_ingress__drop_act 17
#define PIF_ACTION_ID_egress__act_20 18
#define PIF_ACTION_ID_ingress__populate_uekey_guti_map 19
#define PIF_ACTION_ID_ingress__act_12 20
#define PIF_ACTION_ID_ingress__act_13 21
#define PIF_ACTION_ID_ingress__act_10 22
#define PIF_ACTION_ID_ingress__act_11 23
#define PIF_ACTION_ID_ingress__act_14 24
#define PIF_ACTION_ID_egress__act_19 25
#define PIF_ACTION_ID_egress__act_18 26
#define PIF_ACTION_ID_egress__populate_ctxt_release_uekey_sgwteid_map 27
#define PIF_ACTION_ID_egress__act_17 28
#define PIF_ACTION_ID_egress__act_16 29
#define PIF_ACTION_ID_egress__act_15 30
#define PIF_ACTION_ID_MAX 30

/* Match action data structure */

__packed struct pif_action_actiondata_ingress__act_8 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__fwd_act {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
    uint8_t __pif_padding[2]; /* padding */
    uint16_t prt;
};

__packed struct pif_action_actiondata_ingress__act_9 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_0 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_1 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_2 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_3 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_4 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_5 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_6 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_7 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__populate_ip_op_tun_s2_downlink {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
    uint8_t __pif_padding[2]; /* padding */
    uint16_t egress_port_s2;
};

__packed struct pif_action_actiondata_ingress__populate_service_req_uekey_sgwteid_map {
    uint32_t sgwteid;
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__populate_uekey_uestate_map {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
    uint8_t __pif_padding[3]; /* padding */
    uint8_t uestate;
};

__packed struct pif_action_actiondata_ingress__populate_ip_op_tun_s2_uplink {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
    uint8_t __pif_padding[2]; /* padding */
    uint16_t egress_port_s2;
};

__packed struct pif_action_actiondata_ingress__populate_ctxt_setup_uekey_sgwteid_map {
    uint32_t sgwteid;
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__drop_act {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_egress__act_20 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__populate_uekey_guti_map {
    uint32_t guti;
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_12 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_13 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_10 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_11 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_ingress__act_14 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_egress__act_19 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_egress__act_18 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_egress__populate_ctxt_release_uekey_sgwteid_map {
    uint32_t sgwteid;
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_egress__act_17 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_egress__act_16 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

__packed struct pif_action_actiondata_egress__act_15 {
    uint32_t __pif_rule_no;
    uint32_t __pif_table_no;
};

#endif /* __PIF_ACTIONS_H__ */
