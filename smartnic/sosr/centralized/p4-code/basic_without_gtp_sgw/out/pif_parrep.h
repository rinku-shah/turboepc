/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PARREP_H__
#define __PIF_PARREP_H__

/* Generated C source defining layout of parsed representation */
/* Warning: your edits to this file may be lost */

/*
 * Parsed representation control data
 */
struct pif_parrep_ctldata {
    unsigned int valid:1;
    unsigned int t0_valid:1;
    unsigned int t0_dirty:1;
    unsigned int t0_orig_len:1;
    unsigned int t1_valid:1;
    unsigned int t1_dirty:1;
    unsigned int t1_orig_len:1;
    unsigned int t2_valid:1;
    unsigned int t2_dirty:1;
    unsigned int t2_orig_len:1;
    unsigned int t3_valid:1;
    unsigned int t3_dirty:1;
    unsigned int t3_orig_len:1;
    unsigned int t4_valid:1;
    unsigned int t4_dirty:1;
    unsigned int t4_orig_len:1;
    unsigned int t5_valid:1;
    unsigned int t5_dirty:1;
    unsigned int t5_orig_len:1;
    unsigned int t6_valid:1;
    unsigned int t6_type:4;
    unsigned int t6_dirty:1;
    unsigned int t6_orig_len:7;
    unsigned int t7_valid:1;
    unsigned int t7_dirty:1;
    unsigned int t7_orig_len:1;
    unsigned int t8_valid:1;
    unsigned int t8_dirty:1;
    unsigned int t8_orig_len:1;
    unsigned int t9_valid:1;
    unsigned int t9_dirty:1;
    unsigned int t9_orig_len:1;
    unsigned int t10_valid:1;
    unsigned int t10_dirty:1;
    unsigned int t10_orig_len:1;
    unsigned int t11_valid:1;
    unsigned int t11_dirty:1;
    unsigned int t11_orig_len:1;
};

#define PIF_PARREP_CTLDATA_OFF_LW 0
#define PIF_PARREP_CTLDATA_LEN_LW 2

/*
 * Parsed representation layout
 */

/* Parsed represention tier types */
/* tier 6 */
#define PIF_PARREP_TYPE_send_ue_teid 0
#define PIF_PARREP_TYPE_auth_step_three 1
#define PIF_PARREP_TYPE_send_apn 2
#define PIF_PARREP_TYPE_ue_service_req 3
#define PIF_PARREP_TYPE_initial_ctxt_setup_resp 4
#define PIF_PARREP_TYPE_ue_context_rel_req 5
#define PIF_PARREP_TYPE_detach_req 6
#define PIF_PARREP_TYPE_nas_step_two 7
#define PIF_PARREP_TYPE_tcp 8
#define PIF_PARREP_TYPE_auth_step_one 9

/* Parse state values */
#define PIF_PARREP_STATE_exit -1
#define PIF_PARREP_STATE_parse_send_apn 4
#define PIF_PARREP_STATE_parse_ipv4 1
#define PIF_PARREP_STATE_parse_tcp 2
#define PIF_PARREP_STATE_parse_auth_step_one 5
#define PIF_PARREP_STATE_parse_udp 3
#define PIF_PARREP_STATE_parse_initial_ctxt_setup_resp 6
#define PIF_PARREP_STATE_parse_detach_req 7
#define PIF_PARREP_STATE_start 0
#define PIF_PARREP_STATE_parse_nas_step_two 8
#define PIF_PARREP_STATE_parse_ue_context_release 9
#define PIF_PARREP_STATE_parse_auth_step_three 10
#define PIF_PARREP_STATE_parse_send_ue_teid 11
#define PIF_PARREP_STATE_parse_ue_service_req 12
#define PIF_PARREP_MAX_STATE 12

/* Tier 0 */
#define PIF_PARREP_T0_OFF_LW 2
#define PIF_PARREP_T0_LEN_LW 1
#define PIF_PARREP_packet_in_OFF_LW (PIF_PARREP_T0_OFF_LW)
#define PIF_PARREP_packet_in_LEN_LW 1
#define PIF_PARREP_packet_in_LEN_B 2

/* Tier 1 */
#define PIF_PARREP_T1_OFF_LW 3
#define PIF_PARREP_T1_LEN_LW 1
#define PIF_PARREP_packet_out_OFF_LW (PIF_PARREP_T1_OFF_LW)
#define PIF_PARREP_packet_out_LEN_LW 1
#define PIF_PARREP_packet_out_LEN_B 2

/* Tier 2 */
#define PIF_PARREP_T2_OFF_LW 4
#define PIF_PARREP_T2_LEN_LW 4
#define PIF_PARREP_ethernet_OFF_LW (PIF_PARREP_T2_OFF_LW)
#define PIF_PARREP_ethernet_LEN_LW 4
#define PIF_PARREP_ethernet_LEN_B 14

/* Tier 3 */
#define PIF_PARREP_T3_OFF_LW 8
#define PIF_PARREP_T3_LEN_LW 5
#define PIF_PARREP_ipv4_OFF_LW (PIF_PARREP_T3_OFF_LW)
#define PIF_PARREP_ipv4_LEN_LW 5
#define PIF_PARREP_ipv4_LEN_B 20

/* Tier 4 */
#define PIF_PARREP_T4_OFF_LW 13
#define PIF_PARREP_T4_LEN_LW 2
#define PIF_PARREP_udp_OFF_LW (PIF_PARREP_T4_OFF_LW)
#define PIF_PARREP_udp_LEN_LW 2
#define PIF_PARREP_udp_LEN_B 8

/* Tier 5 */
#define PIF_PARREP_T5_OFF_LW 15
#define PIF_PARREP_T5_LEN_LW 2
#define PIF_PARREP_data_OFF_LW (PIF_PARREP_T5_OFF_LW)
#define PIF_PARREP_data_LEN_LW 2
#define PIF_PARREP_data_LEN_B 7

/* Tier 6 */
#define PIF_PARREP_T6_OFF_LW 17
#define PIF_PARREP_T6_LEN_LW 19
#define PIF_PARREP_send_ue_teid_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_send_ue_teid_LEN_LW 4
#define PIF_PARREP_send_ue_teid_LEN_B 14
#define PIF_PARREP_auth_step_three_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_auth_step_three_LEN_LW 5
#define PIF_PARREP_auth_step_three_LEN_B 18
#define PIF_PARREP_send_apn_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_send_apn_LEN_LW 5
#define PIF_PARREP_send_apn_LEN_B 18
#define PIF_PARREP_ue_service_req_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_ue_service_req_LEN_LW 6
#define PIF_PARREP_ue_service_req_LEN_B 24
#define PIF_PARREP_initial_ctxt_setup_resp_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_initial_ctxt_setup_resp_LEN_LW 6
#define PIF_PARREP_initial_ctxt_setup_resp_LEN_B 24
#define PIF_PARREP_ue_context_rel_req_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_ue_context_rel_req_LEN_LW 9
#define PIF_PARREP_ue_context_rel_req_LEN_B 34
#define PIF_PARREP_detach_req_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_detach_req_LEN_LW 9
#define PIF_PARREP_detach_req_LEN_B 34
#define PIF_PARREP_nas_step_two_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_nas_step_two_LEN_LW 8
#define PIF_PARREP_nas_step_two_LEN_B 30
#define PIF_PARREP_tcp_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_tcp_LEN_LW 5
#define PIF_PARREP_tcp_LEN_B 20
#define PIF_PARREP_auth_step_one_OFF_LW (PIF_PARREP_T6_OFF_LW)
#define PIF_PARREP_auth_step_one_LEN_LW 19
#define PIF_PARREP_auth_step_one_LEN_B 73

/* Tier 7 */
#define PIF_PARREP_T7_OFF_LW 36
#define PIF_PARREP_T7_LEN_LW 9
#define PIF_PARREP_offload_ue_service_req_OFF_LW (PIF_PARREP_T7_OFF_LW)
#define PIF_PARREP_offload_ue_service_req_LEN_LW 9
#define PIF_PARREP_offload_ue_service_req_LEN_B 34

/* Tier 8 */
#define PIF_PARREP_T8_OFF_LW 45
#define PIF_PARREP_T8_LEN_LW 9
#define PIF_PARREP_offload_initial_ctxt_setup_resp_OFF_LW (PIF_PARREP_T8_OFF_LW)
#define PIF_PARREP_offload_initial_ctxt_setup_resp_LEN_LW 9
#define PIF_PARREP_offload_initial_ctxt_setup_resp_LEN_B 34

/* Tier 9 */
#define PIF_PARREP_T9_OFF_LW 54
#define PIF_PARREP_T9_LEN_LW 2
#define PIF_PARREP_ue_context_rel_command_OFF_LW (PIF_PARREP_T9_OFF_LW)
#define PIF_PARREP_ue_context_rel_command_LEN_LW 2
#define PIF_PARREP_ue_context_rel_command_LEN_B 7

/* Tier 10 */
#define PIF_PARREP_T10_OFF_LW 56
#define PIF_PARREP_T10_LEN_LW 3
#define PIF_PARREP_initial_ctxt_setup_req_OFF_LW (PIF_PARREP_T10_OFF_LW)
#define PIF_PARREP_initial_ctxt_setup_req_LEN_LW 3
#define PIF_PARREP_initial_ctxt_setup_req_LEN_B 11

/* Tier 11 */
#define PIF_PARREP_T11_OFF_LW 59
#define PIF_PARREP_T11_LEN_LW 3
#define PIF_PARREP_attach_accept_OFF_LW (PIF_PARREP_T11_OFF_LW)
#define PIF_PARREP_attach_accept_LEN_LW 3
#define PIF_PARREP_attach_accept_LEN_B 11

/*
 * Metadata
 */

#define PIF_PARREP_tmpvar_OFF_LW 62
#define PIF_PARREP_tmpvar_LEN_LW 1

#define PIF_PARREP_uekey_sgwteid_OFF_LW 63
#define PIF_PARREP_uekey_sgwteid_LEN_LW 2

#define PIF_PARREP_vlan_OFF_LW 65
#define PIF_PARREP_vlan_LEN_LW 1

#define PIF_PARREP_kv_OFF_LW 66
#define PIF_PARREP_kv_LEN_LW 8

#define PIF_PARREP_standard_metadata_OFF_LW 74
#define PIF_PARREP_standard_metadata_LEN_LW 4

#define PIF_PARREP_ingress__uekey_guti_OFF_LW 78
#define PIF_PARREP_ingress__uekey_guti_LEN_LW 2

#define PIF_PARREP_ingress__uekey_uestate_OFF_LW 80
#define PIF_PARREP_ingress__uekey_uestate_LEN_LW 2

#define PIF_PARREP_ingress__scalars_OFF_LW 82
#define PIF_PARREP_ingress__scalars_LEN_LW 1

#define PIF_PARREP_LEN_LW 83

/* Parsing branches to a constant control entry point */
#define PIF_PARREP_NO_VARIABLE_EXIT

/* Control data macros */
#define PIF_PARREP_VALID(_ctl) (_ctl->valid)
#define PIF_PARREP_SET_VALID(_ctl) \
    do { _ctl->valid = 1; } while (0)

/* Tier 0 */
#define PIF_PARREP_T0_TYPE(ctl) ( ((ctl)->t0_type))
#define PIF_PARREP_T0_VALID(ctl) ( ((ctl)->t0_valid))
#define PIF_PARREP_packet_in_VALID(ctl) ( ((ctl)->t0_valid) )
#define PIF_PARREP_SET_packet_in_VALID(ctl) \
    do { \
        (ctl)->t0_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_packet_in_VALID(ctl) \
    do { \
        (ctl)->t0_valid = 0; \
    } while(0);

#define PIF_PARREP_packet_in_DIRTY(_ctl) ((_ctl)->t0_dirty)
#define PIF_PARREP_T0_DIRTY(_ctl) ((_ctl)->t0_dirty)
#define PIF_PARREP_CLEAR_T0_DIRTY(_ctl)     do { \
        (_ctl)->t0_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T0_DIRTY(_ctl)     do { \
        (_ctl)->t0_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_packet_in_DIRTY(_ctl) \
    do { \
        (_ctl)->t0_dirty = 1; \
    } while(0);

#define PIF_PARREP_T0_ORIG_LEN(ctl) (((ctl)->t0_orig_len) ? PIF_PARREP_packet_in_LEN_B : 0)
#define PIF_PARREP_SET_T0_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t0_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_packet_in_ORIG_LEN(ctl) (((ctl)->t0_orig_len) ? PIF_PARREP_packet_in_LEN_B : 0)
#define PIF_PARREP_CLEAR_packet_in_ORIG_LEN(ctl) \
    do { \
        (ctl)->t0_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_packet_in_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t0_orig_len = 1; \
    } while(0);

/* Tier 1 */
#define PIF_PARREP_T1_TYPE(ctl) ( ((ctl)->t1_type))
#define PIF_PARREP_T1_VALID(ctl) ( ((ctl)->t1_valid))
#define PIF_PARREP_packet_out_VALID(ctl) ( ((ctl)->t1_valid) )
#define PIF_PARREP_SET_packet_out_VALID(ctl) \
    do { \
        (ctl)->t1_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_packet_out_VALID(ctl) \
    do { \
        (ctl)->t1_valid = 0; \
    } while(0);

#define PIF_PARREP_packet_out_DIRTY(_ctl) ((_ctl)->t1_dirty)
#define PIF_PARREP_T1_DIRTY(_ctl) ((_ctl)->t1_dirty)
#define PIF_PARREP_CLEAR_T1_DIRTY(_ctl)     do { \
        (_ctl)->t1_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T1_DIRTY(_ctl)     do { \
        (_ctl)->t1_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_packet_out_DIRTY(_ctl) \
    do { \
        (_ctl)->t1_dirty = 1; \
    } while(0);

#define PIF_PARREP_T1_ORIG_LEN(ctl) (((ctl)->t1_orig_len) ? PIF_PARREP_packet_out_LEN_B : 0)
#define PIF_PARREP_SET_T1_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t1_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_packet_out_ORIG_LEN(ctl) (((ctl)->t1_orig_len) ? PIF_PARREP_packet_out_LEN_B : 0)
#define PIF_PARREP_CLEAR_packet_out_ORIG_LEN(ctl) \
    do { \
        (ctl)->t1_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_packet_out_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t1_orig_len = 1; \
    } while(0);

/* Tier 2 */
#define PIF_PARREP_T2_TYPE(ctl) ( ((ctl)->t2_type))
#define PIF_PARREP_T2_VALID(ctl) ( ((ctl)->t2_valid))
#define PIF_PARREP_ethernet_VALID(ctl) ( ((ctl)->t2_valid) )
#define PIF_PARREP_SET_ethernet_VALID(ctl) \
    do { \
        (ctl)->t2_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_ethernet_VALID(ctl) \
    do { \
        (ctl)->t2_valid = 0; \
    } while(0);

#define PIF_PARREP_ethernet_DIRTY(_ctl) ((_ctl)->t2_dirty)
#define PIF_PARREP_T2_DIRTY(_ctl) ((_ctl)->t2_dirty)
#define PIF_PARREP_CLEAR_T2_DIRTY(_ctl)     do { \
        (_ctl)->t2_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T2_DIRTY(_ctl)     do { \
        (_ctl)->t2_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_ethernet_DIRTY(_ctl) \
    do { \
        (_ctl)->t2_dirty = 1; \
    } while(0);

#define PIF_PARREP_T2_ORIG_LEN(ctl) (((ctl)->t2_orig_len) ? PIF_PARREP_ethernet_LEN_B : 0)
#define PIF_PARREP_SET_T2_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t2_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_ethernet_ORIG_LEN(ctl) (((ctl)->t2_orig_len) ? PIF_PARREP_ethernet_LEN_B : 0)
#define PIF_PARREP_CLEAR_ethernet_ORIG_LEN(ctl) \
    do { \
        (ctl)->t2_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_ethernet_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t2_orig_len = 1; \
    } while(0);

/* Tier 3 */
#define PIF_PARREP_T3_TYPE(ctl) ( ((ctl)->t3_type))
#define PIF_PARREP_T3_VALID(ctl) ( ((ctl)->t3_valid))
#define PIF_PARREP_ipv4_VALID(ctl) ( ((ctl)->t3_valid) )
#define PIF_PARREP_SET_ipv4_VALID(ctl) \
    do { \
        (ctl)->t3_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_ipv4_VALID(ctl) \
    do { \
        (ctl)->t3_valid = 0; \
    } while(0);

#define PIF_PARREP_ipv4_DIRTY(_ctl) ((_ctl)->t3_dirty)
#define PIF_PARREP_T3_DIRTY(_ctl) ((_ctl)->t3_dirty)
#define PIF_PARREP_CLEAR_T3_DIRTY(_ctl)     do { \
        (_ctl)->t3_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T3_DIRTY(_ctl)     do { \
        (_ctl)->t3_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_ipv4_DIRTY(_ctl) \
    do { \
        (_ctl)->t3_dirty = 1; \
    } while(0);

#define PIF_PARREP_T3_ORIG_LEN(ctl) (((ctl)->t3_orig_len) ? PIF_PARREP_ipv4_LEN_B : 0)
#define PIF_PARREP_SET_T3_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t3_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_ipv4_ORIG_LEN(ctl) (((ctl)->t3_orig_len) ? PIF_PARREP_ipv4_LEN_B : 0)
#define PIF_PARREP_CLEAR_ipv4_ORIG_LEN(ctl) \
    do { \
        (ctl)->t3_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_ipv4_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t3_orig_len = 1; \
    } while(0);

/* Tier 4 */
#define PIF_PARREP_T4_TYPE(ctl) ( ((ctl)->t4_type))
#define PIF_PARREP_T4_VALID(ctl) ( ((ctl)->t4_valid))
#define PIF_PARREP_udp_VALID(ctl) ( ((ctl)->t4_valid) )
#define PIF_PARREP_SET_udp_VALID(ctl) \
    do { \
        (ctl)->t4_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_udp_VALID(ctl) \
    do { \
        (ctl)->t4_valid = 0; \
    } while(0);

#define PIF_PARREP_udp_DIRTY(_ctl) ((_ctl)->t4_dirty)
#define PIF_PARREP_T4_DIRTY(_ctl) ((_ctl)->t4_dirty)
#define PIF_PARREP_CLEAR_T4_DIRTY(_ctl)     do { \
        (_ctl)->t4_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T4_DIRTY(_ctl)     do { \
        (_ctl)->t4_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_udp_DIRTY(_ctl) \
    do { \
        (_ctl)->t4_dirty = 1; \
    } while(0);

#define PIF_PARREP_T4_ORIG_LEN(ctl) (((ctl)->t4_orig_len) ? PIF_PARREP_udp_LEN_B : 0)
#define PIF_PARREP_SET_T4_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t4_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_udp_ORIG_LEN(ctl) (((ctl)->t4_orig_len) ? PIF_PARREP_udp_LEN_B : 0)
#define PIF_PARREP_CLEAR_udp_ORIG_LEN(ctl) \
    do { \
        (ctl)->t4_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_udp_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t4_orig_len = 1; \
    } while(0);

/* Tier 5 */
#define PIF_PARREP_T5_TYPE(ctl) ( ((ctl)->t5_type))
#define PIF_PARREP_T5_VALID(ctl) ( ((ctl)->t5_valid))
#define PIF_PARREP_data_VALID(ctl) ( ((ctl)->t5_valid) )
#define PIF_PARREP_SET_data_VALID(ctl) \
    do { \
        (ctl)->t5_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_data_VALID(ctl) \
    do { \
        (ctl)->t5_valid = 0; \
    } while(0);

#define PIF_PARREP_data_DIRTY(_ctl) ((_ctl)->t5_dirty)
#define PIF_PARREP_T5_DIRTY(_ctl) ((_ctl)->t5_dirty)
#define PIF_PARREP_CLEAR_T5_DIRTY(_ctl)     do { \
        (_ctl)->t5_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T5_DIRTY(_ctl)     do { \
        (_ctl)->t5_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_data_DIRTY(_ctl) \
    do { \
        (_ctl)->t5_dirty = 1; \
    } while(0);

#define PIF_PARREP_T5_ORIG_LEN(ctl) (((ctl)->t5_orig_len) ? PIF_PARREP_data_LEN_B : 0)
#define PIF_PARREP_SET_T5_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t5_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_data_ORIG_LEN(ctl) (((ctl)->t5_orig_len) ? PIF_PARREP_data_LEN_B : 0)
#define PIF_PARREP_CLEAR_data_ORIG_LEN(ctl) \
    do { \
        (ctl)->t5_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_data_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t5_orig_len = 1; \
    } while(0);

/* Tier 6 */
#define PIF_PARREP_T6_TYPE(ctl) ( ((ctl)->t6_type))
#define PIF_PARREP_T6_VALID(ctl) ( ((ctl)->t6_valid & 0x1) )
#define PIF_PARREP_send_ue_teid_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_send_ue_teid) )
#define PIF_PARREP_SET_send_ue_teid_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_send_ue_teid; \
    } while(0);
#define PIF_PARREP_CLEAR_send_ue_teid_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);
#define PIF_PARREP_auth_step_three_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_auth_step_three) )
#define PIF_PARREP_SET_auth_step_three_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_auth_step_three; \
    } while(0);
#define PIF_PARREP_CLEAR_auth_step_three_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);
#define PIF_PARREP_send_apn_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_send_apn) )
#define PIF_PARREP_SET_send_apn_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_send_apn; \
    } while(0);
#define PIF_PARREP_CLEAR_send_apn_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);
#define PIF_PARREP_ue_service_req_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_ue_service_req) )
#define PIF_PARREP_SET_ue_service_req_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_ue_service_req; \
    } while(0);
#define PIF_PARREP_CLEAR_ue_service_req_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);
#define PIF_PARREP_initial_ctxt_setup_resp_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_initial_ctxt_setup_resp) )
#define PIF_PARREP_SET_initial_ctxt_setup_resp_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_initial_ctxt_setup_resp; \
    } while(0);
#define PIF_PARREP_CLEAR_initial_ctxt_setup_resp_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);
#define PIF_PARREP_ue_context_rel_req_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_ue_context_rel_req) )
#define PIF_PARREP_SET_ue_context_rel_req_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_ue_context_rel_req; \
    } while(0);
#define PIF_PARREP_CLEAR_ue_context_rel_req_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);
#define PIF_PARREP_detach_req_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_detach_req) )
#define PIF_PARREP_SET_detach_req_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_detach_req; \
    } while(0);
#define PIF_PARREP_CLEAR_detach_req_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);
#define PIF_PARREP_nas_step_two_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_nas_step_two) )
#define PIF_PARREP_SET_nas_step_two_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_nas_step_two; \
    } while(0);
#define PIF_PARREP_CLEAR_nas_step_two_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);
#define PIF_PARREP_tcp_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_tcp) )
#define PIF_PARREP_SET_tcp_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_tcp; \
    } while(0);
#define PIF_PARREP_CLEAR_tcp_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);
#define PIF_PARREP_auth_step_one_VALID(ctl) ( ((ctl)->t6_valid & 0x1) && ((ctl)->t6_type == PIF_PARREP_TYPE_auth_step_one) )
#define PIF_PARREP_SET_auth_step_one_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 1; \
        (ctl)->t6_type = PIF_PARREP_TYPE_auth_step_one; \
    } while(0);
#define PIF_PARREP_CLEAR_auth_step_one_VALID(ctl) \
    do { \
        (ctl)->t6_valid = 0; \
    } while(0);

#define PIF_PARREP_send_ue_teid_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_auth_step_three_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_send_apn_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_ue_service_req_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_initial_ctxt_setup_resp_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_ue_context_rel_req_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_detach_req_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_nas_step_two_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_tcp_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_auth_step_one_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_T6_DIRTY(_ctl) ((_ctl)->t6_dirty)
#define PIF_PARREP_CLEAR_T6_DIRTY(_ctl)     do { \
        (_ctl)->t6_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T6_DIRTY(_ctl)     do { \
        (_ctl)->t6_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_send_ue_teid_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);
#define PIF_PARREP_SET_auth_step_three_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);
#define PIF_PARREP_SET_send_apn_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);
#define PIF_PARREP_SET_ue_service_req_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);
#define PIF_PARREP_SET_initial_ctxt_setup_resp_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);
#define PIF_PARREP_SET_ue_context_rel_req_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);
#define PIF_PARREP_SET_detach_req_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);
#define PIF_PARREP_SET_nas_step_two_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);
#define PIF_PARREP_SET_tcp_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);
#define PIF_PARREP_SET_auth_step_one_DIRTY(_ctl) \
    do { \
        (_ctl)->t6_dirty = 1; \
    } while(0);

#define PIF_PARREP_T6_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_SET_T6_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_T6_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_send_ue_teid_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_send_ue_teid_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_send_ue_teid_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_send_ue_teid_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_auth_step_three_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_auth_step_three_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_auth_step_three_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_auth_step_three_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_send_apn_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_send_apn_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_send_apn_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_send_apn_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_ue_service_req_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_ue_service_req_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_ue_service_req_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_ue_service_req_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_initial_ctxt_setup_resp_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_initial_ctxt_setup_resp_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_initial_ctxt_setup_resp_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_initial_ctxt_setup_resp_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_ue_context_rel_req_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_ue_context_rel_req_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_ue_context_rel_req_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_ue_context_rel_req_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_detach_req_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_detach_req_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_detach_req_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_detach_req_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_nas_step_two_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_nas_step_two_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_nas_step_two_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_nas_step_two_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_tcp_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_tcp_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_tcp_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_tcp_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);
#define PIF_PARREP_auth_step_one_ORIG_LEN(ctl) ((ctl)->t6_orig_len)
#define PIF_PARREP_CLEAR_auth_step_one_ORIG_LEN(ctl) \
    do { \
        (ctl)->t6_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_auth_step_one_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len = len; \
    } while(0);
#define PIF_PARREP_INC_auth_step_one_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t6_orig_len += len; \
    } while(0);

/* Tier 7 */
#define PIF_PARREP_T7_TYPE(ctl) ( ((ctl)->t7_type))
#define PIF_PARREP_T7_VALID(ctl) ( ((ctl)->t7_valid))
#define PIF_PARREP_offload_ue_service_req_VALID(ctl) ( ((ctl)->t7_valid) )
#define PIF_PARREP_SET_offload_ue_service_req_VALID(ctl) \
    do { \
        (ctl)->t7_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_offload_ue_service_req_VALID(ctl) \
    do { \
        (ctl)->t7_valid = 0; \
    } while(0);

#define PIF_PARREP_offload_ue_service_req_DIRTY(_ctl) ((_ctl)->t7_dirty)
#define PIF_PARREP_T7_DIRTY(_ctl) ((_ctl)->t7_dirty)
#define PIF_PARREP_CLEAR_T7_DIRTY(_ctl)     do { \
        (_ctl)->t7_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T7_DIRTY(_ctl)     do { \
        (_ctl)->t7_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_offload_ue_service_req_DIRTY(_ctl) \
    do { \
        (_ctl)->t7_dirty = 1; \
    } while(0);

#define PIF_PARREP_T7_ORIG_LEN(ctl) (((ctl)->t7_orig_len) ? PIF_PARREP_offload_ue_service_req_LEN_B : 0)
#define PIF_PARREP_SET_T7_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t7_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_offload_ue_service_req_ORIG_LEN(ctl) (((ctl)->t7_orig_len) ? PIF_PARREP_offload_ue_service_req_LEN_B : 0)
#define PIF_PARREP_CLEAR_offload_ue_service_req_ORIG_LEN(ctl) \
    do { \
        (ctl)->t7_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_offload_ue_service_req_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t7_orig_len = 1; \
    } while(0);

/* Tier 8 */
#define PIF_PARREP_T8_TYPE(ctl) ( ((ctl)->t8_type))
#define PIF_PARREP_T8_VALID(ctl) ( ((ctl)->t8_valid))
#define PIF_PARREP_offload_initial_ctxt_setup_resp_VALID(ctl) ( ((ctl)->t8_valid) )
#define PIF_PARREP_SET_offload_initial_ctxt_setup_resp_VALID(ctl) \
    do { \
        (ctl)->t8_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_offload_initial_ctxt_setup_resp_VALID(ctl) \
    do { \
        (ctl)->t8_valid = 0; \
    } while(0);

#define PIF_PARREP_offload_initial_ctxt_setup_resp_DIRTY(_ctl) ((_ctl)->t8_dirty)
#define PIF_PARREP_T8_DIRTY(_ctl) ((_ctl)->t8_dirty)
#define PIF_PARREP_CLEAR_T8_DIRTY(_ctl)     do { \
        (_ctl)->t8_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T8_DIRTY(_ctl)     do { \
        (_ctl)->t8_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_offload_initial_ctxt_setup_resp_DIRTY(_ctl) \
    do { \
        (_ctl)->t8_dirty = 1; \
    } while(0);

#define PIF_PARREP_T8_ORIG_LEN(ctl) (((ctl)->t8_orig_len) ? PIF_PARREP_offload_initial_ctxt_setup_resp_LEN_B : 0)
#define PIF_PARREP_SET_T8_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t8_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_offload_initial_ctxt_setup_resp_ORIG_LEN(ctl) (((ctl)->t8_orig_len) ? PIF_PARREP_offload_initial_ctxt_setup_resp_LEN_B : 0)
#define PIF_PARREP_CLEAR_offload_initial_ctxt_setup_resp_ORIG_LEN(ctl) \
    do { \
        (ctl)->t8_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_offload_initial_ctxt_setup_resp_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t8_orig_len = 1; \
    } while(0);

/* Tier 9 */
#define PIF_PARREP_T9_TYPE(ctl) ( ((ctl)->t9_type))
#define PIF_PARREP_T9_VALID(ctl) ( ((ctl)->t9_valid))
#define PIF_PARREP_ue_context_rel_command_VALID(ctl) ( ((ctl)->t9_valid) )
#define PIF_PARREP_SET_ue_context_rel_command_VALID(ctl) \
    do { \
        (ctl)->t9_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_ue_context_rel_command_VALID(ctl) \
    do { \
        (ctl)->t9_valid = 0; \
    } while(0);

#define PIF_PARREP_ue_context_rel_command_DIRTY(_ctl) ((_ctl)->t9_dirty)
#define PIF_PARREP_T9_DIRTY(_ctl) ((_ctl)->t9_dirty)
#define PIF_PARREP_CLEAR_T9_DIRTY(_ctl)     do { \
        (_ctl)->t9_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T9_DIRTY(_ctl)     do { \
        (_ctl)->t9_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_ue_context_rel_command_DIRTY(_ctl) \
    do { \
        (_ctl)->t9_dirty = 1; \
    } while(0);

#define PIF_PARREP_T9_ORIG_LEN(ctl) (((ctl)->t9_orig_len) ? PIF_PARREP_ue_context_rel_command_LEN_B : 0)
#define PIF_PARREP_SET_T9_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t9_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_ue_context_rel_command_ORIG_LEN(ctl) (((ctl)->t9_orig_len) ? PIF_PARREP_ue_context_rel_command_LEN_B : 0)
#define PIF_PARREP_CLEAR_ue_context_rel_command_ORIG_LEN(ctl) \
    do { \
        (ctl)->t9_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_ue_context_rel_command_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t9_orig_len = 1; \
    } while(0);

/* Tier 10 */
#define PIF_PARREP_T10_TYPE(ctl) ( ((ctl)->t10_type))
#define PIF_PARREP_T10_VALID(ctl) ( ((ctl)->t10_valid))
#define PIF_PARREP_initial_ctxt_setup_req_VALID(ctl) ( ((ctl)->t10_valid) )
#define PIF_PARREP_SET_initial_ctxt_setup_req_VALID(ctl) \
    do { \
        (ctl)->t10_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_initial_ctxt_setup_req_VALID(ctl) \
    do { \
        (ctl)->t10_valid = 0; \
    } while(0);

#define PIF_PARREP_initial_ctxt_setup_req_DIRTY(_ctl) ((_ctl)->t10_dirty)
#define PIF_PARREP_T10_DIRTY(_ctl) ((_ctl)->t10_dirty)
#define PIF_PARREP_CLEAR_T10_DIRTY(_ctl)     do { \
        (_ctl)->t10_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T10_DIRTY(_ctl)     do { \
        (_ctl)->t10_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_initial_ctxt_setup_req_DIRTY(_ctl) \
    do { \
        (_ctl)->t10_dirty = 1; \
    } while(0);

#define PIF_PARREP_T10_ORIG_LEN(ctl) (((ctl)->t10_orig_len) ? PIF_PARREP_initial_ctxt_setup_req_LEN_B : 0)
#define PIF_PARREP_SET_T10_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t10_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_initial_ctxt_setup_req_ORIG_LEN(ctl) (((ctl)->t10_orig_len) ? PIF_PARREP_initial_ctxt_setup_req_LEN_B : 0)
#define PIF_PARREP_CLEAR_initial_ctxt_setup_req_ORIG_LEN(ctl) \
    do { \
        (ctl)->t10_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_initial_ctxt_setup_req_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t10_orig_len = 1; \
    } while(0);

/* Tier 11 */
#define PIF_PARREP_T11_TYPE(ctl) ( ((ctl)->t11_type))
#define PIF_PARREP_T11_VALID(ctl) ( ((ctl)->t11_valid))
#define PIF_PARREP_attach_accept_VALID(ctl) ( ((ctl)->t11_valid) )
#define PIF_PARREP_SET_attach_accept_VALID(ctl) \
    do { \
        (ctl)->t11_valid = 1; \
    } while(0);
#define PIF_PARREP_CLEAR_attach_accept_VALID(ctl) \
    do { \
        (ctl)->t11_valid = 0; \
    } while(0);

#define PIF_PARREP_attach_accept_DIRTY(_ctl) ((_ctl)->t11_dirty)
#define PIF_PARREP_T11_DIRTY(_ctl) ((_ctl)->t11_dirty)
#define PIF_PARREP_CLEAR_T11_DIRTY(_ctl)     do { \
        (_ctl)->t11_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_T11_DIRTY(_ctl)     do { \
        (_ctl)->t11_dirty = 0; \
    } while(0);
#define PIF_PARREP_SET_attach_accept_DIRTY(_ctl) \
    do { \
        (_ctl)->t11_dirty = 1; \
    } while(0);

#define PIF_PARREP_T11_ORIG_LEN(ctl) (((ctl)->t11_orig_len) ? PIF_PARREP_attach_accept_LEN_B : 0)
#define PIF_PARREP_SET_T11_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t11_orig_len = (len == 0 ? 0 : 1); \
    } while(0);
#define PIF_PARREP_attach_accept_ORIG_LEN(ctl) (((ctl)->t11_orig_len) ? PIF_PARREP_attach_accept_LEN_B : 0)
#define PIF_PARREP_CLEAR_attach_accept_ORIG_LEN(ctl) \
    do { \
        (ctl)->t11_orig_len = 0; \
    } while(0);
#define PIF_PARREP_SET_attach_accept_ORIG_LEN(ctl, len) \
    do { \
        (ctl)->t11_orig_len = 1; \
    } while(0);



void pif_value_set_scan_configs();

#endif /* __PIF_PARREP_H__ */
