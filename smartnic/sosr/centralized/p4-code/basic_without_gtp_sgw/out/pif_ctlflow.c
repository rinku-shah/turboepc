/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/me.h>
#include "pif_common.h"

/****************************************
 * ingress_flow                         *
 ****************************************/

/* State transition functions */

static int handle_ingress_flow__condition_2(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_2_register_7;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_2");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_2: ((((ethernet.etherType) == (2054))) and (((ethernet.dstAddr) == (219902325555))))
    {
    unsigned int pif_expression__condition_2_register_0;
    unsigned int pif_expression__condition_2_register_1;
    unsigned int pif_expression__condition_2_register_2;
    unsigned int pif_expression__condition_2_register_3;
    unsigned int pif_expression__condition_2_register_4;
    unsigned int pif_expression__condition_2_register_5;
    unsigned int pif_expression__condition_2_register_6;
    //subexpression 6: 2054
    // constant : 0x806

    //subexpression 1: (ethernet.etherType)==(2054)
    pif_expression__condition_2_register_1 = ethernet->etherType;
    pif_expression__condition_2_register_2 = 0x806;
    /* implicit cast 12 -> 16 */
    pif_expression__condition_2_register_3 = pif_expression__condition_2_register_2 & 0xfff;
    pif_expression__condition_2_register_0 = (pif_expression__condition_2_register_1 == pif_expression__condition_2_register_3);
    //subexpression 4: 219902325555
    // constant : 0x3333333333

    //subexpression 2: (ethernet.dstAddr)==(219902325555)
    pif_expression__condition_2_register_1 = ((ethernet->dstAddr & 0xffff) << 16) | ethernet->__dstAddr_1;
    pif_expression__condition_2_register_2 = ((ethernet->dstAddr >> 16) & 0xffff);
    pif_expression__condition_2_register_4 = 0x33333333;
    pif_expression__condition_2_register_5 = 0x33;
    /* implicit cast 38 -> 48 */
    pif_expression__condition_2_register_6 = pif_expression__condition_2_register_4;
    pif_expression__condition_2_register_7 = pif_expression__condition_2_register_5 & 0x3f;
    pif_expression__condition_2_register_3 = (pif_expression__condition_2_register_1 == pif_expression__condition_2_register_6) && (pif_expression__condition_2_register_2 == pif_expression__condition_2_register_7);
    //subexpression 0: (((ethernet.etherType)==(2054)))and(((ethernet.dstAddr)==(219902325555)))
    pif_expression__condition_2_register_7 = (pif_expression__condition_2_register_0) && (pif_expression__condition_2_register_3);
    }

    if (pif_expression__condition_2_register_7)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_1;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_3;
}

static int handle_ingress_flow_ingress__tbl_act_1(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_1");
#endif

    {
        struct pif_action_actiondata_ingress__act_0 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_0 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_0 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_5; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow__condition_16(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_16_register_2;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_16");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_16: ((((standard_metadata.ingress_port) == (0))) and (((ipv4.dstAddr) == (3232236034))))
    {
    unsigned int pif_expression__condition_16_register_0;
    unsigned int pif_expression__condition_16_register_1;
    unsigned int pif_expression__condition_16_register_3;
    //subexpression 6: 0
    // constant : 0x0

    //subexpression 1: (standard_metadata.ingress_port)==(0)
    pif_expression__condition_16_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_16_register_2 = 0x0;
    /* implicit cast 1 -> 16 */
    pif_expression__condition_16_register_3 = pif_expression__condition_16_register_2 & 0x1;
    pif_expression__condition_16_register_0 = (pif_expression__condition_16_register_1 == pif_expression__condition_16_register_3);
    //subexpression 4: 3232236034
    // constant : 0xc0a80202

    //subexpression 2: (ipv4.dstAddr)==(3232236034)
    pif_expression__condition_16_register_1 = ipv4->dstAddr;
    pif_expression__condition_16_register_2 = 0xc0a80202;
    pif_expression__condition_16_register_3 = (pif_expression__condition_16_register_1 == pif_expression__condition_16_register_2);
    //subexpression 0: (((standard_metadata.ingress_port)==(0)))and(((ipv4.dstAddr)==(3232236034)))
    pif_expression__condition_16_register_2 = (pif_expression__condition_16_register_0) && (pif_expression__condition_16_register_3);
    }

    if (pif_expression__condition_16_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_10;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_17;
}

static int handle_ingress_flow__condition_17(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_17_register_0;
    __lmem struct pif_header_ingress__scalars *ingress__scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_17");
#endif

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    //expression _condition_17: (not((ingress::scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_17_register_1;
    //subexpression 0: not((ingress::scalars.hasReturned_0))
    pif_expression__condition_17_register_1 = ingress__scalars->hasReturned_0;
    pif_expression__condition_17_register_0 = (pif_expression__condition_17_register_1 == 0);
    }

    if (pif_expression__condition_17_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_18;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow;
}

static int handle_ingress_flow__condition_4(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_4_register_2;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_4");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_4: ((((ipv4.protocol) == (6))) and (((ipv4.dstAddr) == (3232236036))))
    {
    unsigned int pif_expression__condition_4_register_0;
    unsigned int pif_expression__condition_4_register_1;
    unsigned int pif_expression__condition_4_register_3;
    //subexpression 6: 6
    // constant : 0x6

    //subexpression 1: (ipv4.protocol)==(6)
    pif_expression__condition_4_register_1 = ipv4->protocol;
    pif_expression__condition_4_register_2 = 0x6;
    /* implicit cast 3 -> 8 */
    pif_expression__condition_4_register_3 = pif_expression__condition_4_register_2 & 0x7;
    pif_expression__condition_4_register_0 = (pif_expression__condition_4_register_1 == pif_expression__condition_4_register_3);
    //subexpression 4: 3232236036
    // constant : 0xc0a80204

    //subexpression 2: (ipv4.dstAddr)==(3232236036)
    pif_expression__condition_4_register_1 = ipv4->dstAddr;
    pif_expression__condition_4_register_2 = 0xc0a80204;
    pif_expression__condition_4_register_3 = (pif_expression__condition_4_register_1 == pif_expression__condition_4_register_2);
    //subexpression 0: (((ipv4.protocol)==(6)))and(((ipv4.dstAddr)==(3232236036)))
    pif_expression__condition_4_register_2 = (pif_expression__condition_4_register_0) && (pif_expression__condition_4_register_3);
    }

    if (pif_expression__condition_4_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_3;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_5;
}

static int handle_ingress_flow__condition_5(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_5_register_0;
    __lmem struct pif_header_ingress__scalars *ingress__scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_5");
#endif

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    //expression _condition_5: (not((ingress::scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_5_register_1;
    //subexpression 0: not((ingress::scalars.hasReturned_0))
    pif_expression__condition_5_register_1 = ingress__scalars->hasReturned_0;
    pif_expression__condition_5_register_0 = (pif_expression__condition_5_register_1 == 0);
    }

    if (pif_expression__condition_5_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_4;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_6;
}

static int handle_ingress_flow__condition_10(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_10_register_0;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_10");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_10: ((ipv4.protocol) == (17))
    {
    unsigned int pif_expression__condition_10_register_1;
    unsigned int pif_expression__condition_10_register_2;
    unsigned int pif_expression__condition_10_register_3;
    //subexpression 2: 17
    // constant : 0x11

    //subexpression 0: (ipv4.protocol)==(17)
    pif_expression__condition_10_register_1 = ipv4->protocol;
    pif_expression__condition_10_register_2 = 0x11;
    /* implicit cast 5 -> 8 */
    pif_expression__condition_10_register_3 = pif_expression__condition_10_register_2 & 0x1f;
    pif_expression__condition_10_register_0 = (pif_expression__condition_10_register_1 == pif_expression__condition_10_register_3);
    }

    if (pif_expression__condition_10_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_6;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_11;
}

static int handle_ingress_flow__condition_11(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_11_register_0;
    __lmem struct pif_header_ingress__scalars *ingress__scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_11");
#endif

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    //expression _condition_11: (not((ingress::scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_11_register_1;
    //subexpression 0: not((ingress::scalars.hasReturned_0))
    pif_expression__condition_11_register_1 = ingress__scalars->hasReturned_0;
    pif_expression__condition_11_register_0 = (pif_expression__condition_11_register_1 == 0);
    }

    if (pif_expression__condition_11_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_12;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_17;
}

static int handle_ingress_flow__condition_3(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_3_register_2;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_3");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_3: ((((ipv4.protocol) == (6))) and (((ipv4.dstAddr) == (3232236034))))
    {
    unsigned int pif_expression__condition_3_register_0;
    unsigned int pif_expression__condition_3_register_1;
    unsigned int pif_expression__condition_3_register_3;
    //subexpression 6: 6
    // constant : 0x6

    //subexpression 1: (ipv4.protocol)==(6)
    pif_expression__condition_3_register_1 = ipv4->protocol;
    pif_expression__condition_3_register_2 = 0x6;
    /* implicit cast 3 -> 8 */
    pif_expression__condition_3_register_3 = pif_expression__condition_3_register_2 & 0x7;
    pif_expression__condition_3_register_0 = (pif_expression__condition_3_register_1 == pif_expression__condition_3_register_3);
    //subexpression 4: 3232236034
    // constant : 0xc0a80202

    //subexpression 2: (ipv4.dstAddr)==(3232236034)
    pif_expression__condition_3_register_1 = ipv4->dstAddr;
    pif_expression__condition_3_register_2 = 0xc0a80202;
    pif_expression__condition_3_register_3 = (pif_expression__condition_3_register_1 == pif_expression__condition_3_register_2);
    //subexpression 0: (((ipv4.protocol)==(6)))and(((ipv4.dstAddr)==(3232236034)))
    pif_expression__condition_3_register_2 = (pif_expression__condition_3_register_0) && (pif_expression__condition_3_register_3);
    }

    if (pif_expression__condition_3_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_2;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_4;
}

static int handle_ingress_flow_ingress__tbl_act_0(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_0");
#endif

    {
        struct pif_action_actiondata_ingress__act actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_5; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act_6(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_6");
#endif

    {
        struct pif_action_actiondata_ingress__act_6 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_6 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_6 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_11; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow__condition_1(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_1_register_7;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_1");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_1: ((((ethernet.etherType) == (2054))) and (((ethernet.dstAddr) == (73300775185))))
    {
    unsigned int pif_expression__condition_1_register_0;
    unsigned int pif_expression__condition_1_register_1;
    unsigned int pif_expression__condition_1_register_2;
    unsigned int pif_expression__condition_1_register_3;
    unsigned int pif_expression__condition_1_register_4;
    unsigned int pif_expression__condition_1_register_5;
    unsigned int pif_expression__condition_1_register_6;
    //subexpression 6: 2054
    // constant : 0x806

    //subexpression 1: (ethernet.etherType)==(2054)
    pif_expression__condition_1_register_1 = ethernet->etherType;
    pif_expression__condition_1_register_2 = 0x806;
    /* implicit cast 12 -> 16 */
    pif_expression__condition_1_register_3 = pif_expression__condition_1_register_2 & 0xfff;
    pif_expression__condition_1_register_0 = (pif_expression__condition_1_register_1 == pif_expression__condition_1_register_3);
    //subexpression 4: 73300775185
    // constant : 0x1111111111

    //subexpression 2: (ethernet.dstAddr)==(73300775185)
    pif_expression__condition_1_register_1 = ((ethernet->dstAddr & 0xffff) << 16) | ethernet->__dstAddr_1;
    pif_expression__condition_1_register_2 = ((ethernet->dstAddr >> 16) & 0xffff);
    pif_expression__condition_1_register_4 = 0x11111111;
    pif_expression__condition_1_register_5 = 0x11;
    /* implicit cast 37 -> 48 */
    pif_expression__condition_1_register_6 = pif_expression__condition_1_register_4;
    pif_expression__condition_1_register_7 = pif_expression__condition_1_register_5 & 0x1f;
    pif_expression__condition_1_register_3 = (pif_expression__condition_1_register_1 == pif_expression__condition_1_register_6) && (pif_expression__condition_1_register_2 == pif_expression__condition_1_register_7);
    //subexpression 0: (((ethernet.etherType)==(2054)))and(((ethernet.dstAddr)==(73300775185)))
    pif_expression__condition_1_register_7 = (pif_expression__condition_1_register_0) && (pif_expression__condition_1_register_3);
    }

    if (pif_expression__condition_1_register_7)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_0;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_2;
}

static int handle_ingress_flow__condition_7(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_7_register_0;
    __lmem struct pif_header_ethernet *ethernet;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_7");
#endif

    ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);

    //expression _condition_7: ((ethernet.etherType) == (2054))
    {
    unsigned int pif_expression__condition_7_register_1;
    unsigned int pif_expression__condition_7_register_2;
    unsigned int pif_expression__condition_7_register_3;
    //subexpression 2: 2054
    // constant : 0x806

    //subexpression 0: (ethernet.etherType)==(2054)
    pif_expression__condition_7_register_1 = ethernet->etherType;
    pif_expression__condition_7_register_2 = 0x806;
    /* implicit cast 12 -> 16 */
    pif_expression__condition_7_register_3 = pif_expression__condition_7_register_2 & 0xfff;
    pif_expression__condition_7_register_0 = (pif_expression__condition_7_register_1 == pif_expression__condition_7_register_3);
    }

    if (pif_expression__condition_7_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__arp_tbl;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_8;
}

static int handle_ingress_flow__condition_8(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_8_register_0;
    __lmem struct pif_header_ingress__scalars *ingress__scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_8");
#endif

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    //expression _condition_8: (not((ingress::scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_8_register_1;
    //subexpression 0: not((ingress::scalars.hasReturned_0))
    pif_expression__condition_8_register_1 = ingress__scalars->hasReturned_0;
    pif_expression__condition_8_register_0 = (pif_expression__condition_8_register_1 == 0);
    }

    if (pif_expression__condition_8_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_9;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow;
}

static int handle_ingress_flow__condition_6(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_6_register_0;
    __lmem struct pif_header_ingress__scalars *ingress__scalars;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_6");
#endif

    ingress__scalars = (__lmem struct pif_header_ingress__scalars *) (_pif_parrep + PIF_PARREP_ingress__scalars_OFF_LW);

    //expression _condition_6: (not((ingress::scalars.hasReturned_0)))
    {
    unsigned int pif_expression__condition_6_register_1;
    //subexpression 0: not((ingress::scalars.hasReturned_0))
    pif_expression__condition_6_register_1 = ingress__scalars->hasReturned_0;
    pif_expression__condition_6_register_0 = (pif_expression__condition_6_register_1 == 0);
    }

    if (pif_expression__condition_6_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_7;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_8;
}

static int handle_ingress_flow_ingress__tbl_act_5(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_5");
#endif

    {
        struct pif_action_actiondata_ingress__act_5 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_5 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_5 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_8; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__ip_op_tun_s2_downlink(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__ip_op_tun_s2_downlink");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__ip_op_tun_s2_downlink, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__uekey_guti_map(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__uekey_guti_map");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__uekey_guti_map, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s2_uplink; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__ip_op_tun_s2_uplink(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__ip_op_tun_s2_uplink");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__ip_op_tun_s2_uplink, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s2_downlink; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow__condition_15(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_15_register_2;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_15");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_15: ((((standard_metadata.ingress_port) == (0))) and (((ipv4.dstAddr) == (3232236035))))
    {
    unsigned int pif_expression__condition_15_register_0;
    unsigned int pif_expression__condition_15_register_1;
    unsigned int pif_expression__condition_15_register_3;
    //subexpression 6: 0
    // constant : 0x0

    //subexpression 1: (standard_metadata.ingress_port)==(0)
    pif_expression__condition_15_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_15_register_2 = 0x0;
    /* implicit cast 1 -> 16 */
    pif_expression__condition_15_register_3 = pif_expression__condition_15_register_2 & 0x1;
    pif_expression__condition_15_register_0 = (pif_expression__condition_15_register_1 == pif_expression__condition_15_register_3);
    //subexpression 4: 3232236035
    // constant : 0xc0a80203

    //subexpression 2: (ipv4.dstAddr)==(3232236035)
    pif_expression__condition_15_register_1 = ipv4->dstAddr;
    pif_expression__condition_15_register_2 = 0xc0a80203;
    pif_expression__condition_15_register_3 = (pif_expression__condition_15_register_1 == pif_expression__condition_15_register_2);
    //subexpression 0: (((standard_metadata.ingress_port)==(0)))and(((ipv4.dstAddr)==(3232236035)))
    pif_expression__condition_15_register_2 = (pif_expression__condition_15_register_0) && (pif_expression__condition_15_register_3);
    }

    if (pif_expression__condition_15_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_9;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_16;
}

static int handle_ingress_flow__condition_18(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_18_register_0;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_18");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_18: ((ipv4.ttl) == (250))
    {
    unsigned int pif_expression__condition_18_register_1;
    unsigned int pif_expression__condition_18_register_2;
    //subexpression 2: 250
    // constant : 0xfa

    //subexpression 0: (ipv4.ttl)==(250)
    pif_expression__condition_18_register_1 = ipv4->ttl;
    pif_expression__condition_18_register_2 = 0xfa;
    pif_expression__condition_18_register_0 = (pif_expression__condition_18_register_1 == pif_expression__condition_18_register_2);
    }

    if (pif_expression__condition_18_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__uekey_uestate_map;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow;
}

static int handle_ingress_flow_ingress__uekey_uestate_map(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__uekey_uestate_map");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__uekey_uestate_map, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__uekey_guti_map; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__arp_tbl(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__arp_tbl");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_ingress__arp_tbl, _pif_parrep, actbuf, actbuf_off);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_5; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow__condition_9(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_9_register_0;
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_9");
#endif

    //expression _condition_9: (valid(ipv4))
    {
    //subexpression 0: valid(ipv4)
    pif_expression__condition_9_register_0 = PIF_PARREP_ipv4_VALID(prdata);
    }

    if (pif_expression__condition_9_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_10;
    else
        return PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow;
}

static int handle_ingress_flow__condition_0(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_0_register_0;
    __lmem struct pif_header_standard_metadata *standard_metadata;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_0");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);

    //expression _condition_0: ((standard_metadata.ingress_port) == (768))
    {
    unsigned int pif_expression__condition_0_register_1;
    unsigned int pif_expression__condition_0_register_2;
    unsigned int pif_expression__condition_0_register_3;
    //subexpression 2: 768
    // constant : 0x300

    //subexpression 0: (standard_metadata.ingress_port)==(768)
    pif_expression__condition_0_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_0_register_2 = 0x300;
    /* implicit cast 10 -> 16 */
    pif_expression__condition_0_register_3 = pif_expression__condition_0_register_2 & 0x3ff;
    pif_expression__condition_0_register_0 = (pif_expression__condition_0_register_1 == pif_expression__condition_0_register_3);
    }

    if (pif_expression__condition_0_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_1;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_6;
}

static int handle_ingress_flow__condition_12(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_12_register_0;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_12");
#endif

    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_12: ((ipv4.protocol) == (6))
    {
    unsigned int pif_expression__condition_12_register_1;
    unsigned int pif_expression__condition_12_register_2;
    unsigned int pif_expression__condition_12_register_3;
    //subexpression 2: 6
    // constant : 0x6

    //subexpression 0: (ipv4.protocol)==(6)
    pif_expression__condition_12_register_1 = ipv4->protocol;
    pif_expression__condition_12_register_2 = 0x6;
    /* implicit cast 3 -> 8 */
    pif_expression__condition_12_register_3 = pif_expression__condition_12_register_2 & 0x7;
    pif_expression__condition_12_register_0 = (pif_expression__condition_12_register_1 == pif_expression__condition_12_register_3);
    }

    if (pif_expression__condition_12_register_0)
        return PIF_CTLFLOW_STATE_ingress_flow__condition_13;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_17;
}

static int handle_ingress_flow__condition_14(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_14_register_2;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_14");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_14: ((((standard_metadata.ingress_port) == (1))) and (((ipv4.dstAddr) == (3232236036))))
    {
    unsigned int pif_expression__condition_14_register_0;
    unsigned int pif_expression__condition_14_register_1;
    unsigned int pif_expression__condition_14_register_3;
    //subexpression 6: 1
    // constant : 0x1

    //subexpression 1: (standard_metadata.ingress_port)==(1)
    pif_expression__condition_14_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_14_register_2 = 0x1;
    /* implicit cast 1 -> 16 */
    pif_expression__condition_14_register_3 = pif_expression__condition_14_register_2 & 0x1;
    pif_expression__condition_14_register_0 = (pif_expression__condition_14_register_1 == pif_expression__condition_14_register_3);
    //subexpression 4: 3232236036
    // constant : 0xc0a80204

    //subexpression 2: (ipv4.dstAddr)==(3232236036)
    pif_expression__condition_14_register_1 = ipv4->dstAddr;
    pif_expression__condition_14_register_2 = 0xc0a80204;
    pif_expression__condition_14_register_3 = (pif_expression__condition_14_register_1 == pif_expression__condition_14_register_2);
    //subexpression 0: (((standard_metadata.ingress_port)==(1)))and(((ipv4.dstAddr)==(3232236036)))
    pif_expression__condition_14_register_2 = (pif_expression__condition_14_register_0) && (pif_expression__condition_14_register_3);
    }

    if (pif_expression__condition_14_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_8;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_15;
}

static int handle_ingress_flow_ingress__tbl_act_2(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_2");
#endif

    {
        struct pif_action_actiondata_ingress__act_1 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_1 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_1 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_5; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act_4(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_4");
#endif

    {
        struct pif_action_actiondata_ingress__act_3 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_3 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_3 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_6; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act_3(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_3");
#endif

    {
        struct pif_action_actiondata_ingress__act_2 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_2 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_2 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_5; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act_10(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_10");
#endif

    {
        struct pif_action_actiondata_ingress__act_10 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_10 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_10 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_17; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act_9(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_9");
#endif

    {
        struct pif_action_actiondata_ingress__act_9 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_9 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_9 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_17; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow__condition_13(__lmem uint32_t *_pif_parrep)
{
    unsigned int pif_expression__condition_13_register_2;
    __lmem struct pif_header_standard_metadata *standard_metadata;
    __lmem struct pif_header_ipv4 *ipv4;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow__condition_13");
#endif

    standard_metadata = (__lmem struct pif_header_standard_metadata *) (_pif_parrep + PIF_PARREP_standard_metadata_OFF_LW);
    ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);

    //expression _condition_13: ((((standard_metadata.ingress_port) == (1))) and (((ipv4.dstAddr) == (3232236035))))
    {
    unsigned int pif_expression__condition_13_register_0;
    unsigned int pif_expression__condition_13_register_1;
    unsigned int pif_expression__condition_13_register_3;
    //subexpression 6: 1
    // constant : 0x1

    //subexpression 1: (standard_metadata.ingress_port)==(1)
    pif_expression__condition_13_register_1 = standard_metadata->ingress_port;
    pif_expression__condition_13_register_2 = 0x1;
    /* implicit cast 1 -> 16 */
    pif_expression__condition_13_register_3 = pif_expression__condition_13_register_2 & 0x1;
    pif_expression__condition_13_register_0 = (pif_expression__condition_13_register_1 == pif_expression__condition_13_register_3);
    //subexpression 4: 3232236035
    // constant : 0xc0a80203

    //subexpression 2: (ipv4.dstAddr)==(3232236035)
    pif_expression__condition_13_register_1 = ipv4->dstAddr;
    pif_expression__condition_13_register_2 = 0xc0a80203;
    pif_expression__condition_13_register_3 = (pif_expression__condition_13_register_1 == pif_expression__condition_13_register_2);
    //subexpression 0: (((standard_metadata.ingress_port)==(1)))and(((ipv4.dstAddr)==(3232236035)))
    pif_expression__condition_13_register_2 = (pif_expression__condition_13_register_0) && (pif_expression__condition_13_register_3);
    }

    if (pif_expression__condition_13_register_2)
        return PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_7;
    else
        return PIF_CTLFLOW_STATE_ingress_flow__condition_14;
}

static int handle_ingress_flow_ingress__tbl_act_7(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_7");
#endif

    {
        struct pif_action_actiondata_ingress__act_7 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_7 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_7 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_17; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act");
#endif

    {
        struct pif_action_actiondata_ingress__act_4 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_4 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_4 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_0; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

static int handle_ingress_flow_ingress__tbl_act_8(__lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off, int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_ingress__tbl_act_8");
#endif

    {
        struct pif_action_actiondata_ingress__act_8 actdata;
        __xwrite struct {
            union pif_action_opdata opdata;
            struct pif_action_actiondata_ingress__act_8 actdata;
            } wr_buf;

        wr_buf.opdata.val32 = (PIF_ACTION_ID_ingress__act_8 << PIF_ACTION_OPDATA_ACTION_ID_off) | ((sizeof(actdata) / 4) << PIF_ACTION_OPDATA_ACTDATA_CNT_off);
        actdata.__pif_table_no = 0xffffffff;
        actdata.__pif_rule_no = 0x0;
        wr_buf.actdata = actdata;

        mem_write32(&wr_buf,
                    actbuf + actbuf_off,
                    sizeof(wr_buf));
        *actlen = sizeof(wr_buf)/4;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow__condition_17; /* always */

    if (*actlen > 0) {
        __critical_path();
        ret = pif_action_execute(_pif_parrep, actbuf, actbuf_off, *actlen);
        if (ret < 0)
            return ret;
        __critical_path();
        if (ret > 0)
            next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;
        __critical_path();
    }

    *state = next_state;
    return 0;
}

/* Control flow entry point */

int pif_ctlflow_ingress_flow(int *start_state, __lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off)
{
    __gpr int actlen, totlen = 0;
    __gpr int ret;
    int pif_ctlflow_state_ingress_flow = PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act;

    while (pif_ctlflow_state_ingress_flow != PIF_CTLFLOW_STATE_ingress_flow_DONE) {
        PIF_DEBUG_SET_STATE(PIF_DEBUG_STATE_CONTROL, ((0 << 16) + pif_ctlflow_state_ingress_flow));
#ifdef PIF_DEBUG
        __debug_label("pif_ctlflow_state_ingress_flow");
#endif
        switch (pif_ctlflow_state_ingress_flow) {
        case PIF_CTLFLOW_STATE_ingress_flow__condition_2:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_2(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_1:
            ret = handle_ingress_flow_ingress__tbl_act_1(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_16:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_16(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_17:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_17(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_4:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_4(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_5:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_5(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_10:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_10(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_11:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_11(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_3:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_3(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_0:
            ret = handle_ingress_flow_ingress__tbl_act_0(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_6:
            ret = handle_ingress_flow_ingress__tbl_act_6(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_1:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_1(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_7:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_7(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_8:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_8(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_6:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_6(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_5:
            ret = handle_ingress_flow_ingress__tbl_act_5(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s2_downlink:
            ret = handle_ingress_flow_ingress__ip_op_tun_s2_downlink(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__uekey_guti_map:
            ret = handle_ingress_flow_ingress__uekey_guti_map(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__ip_op_tun_s2_uplink:
            ret = handle_ingress_flow_ingress__ip_op_tun_s2_uplink(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_15:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_15(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_18:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_18(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__uekey_uestate_map:
            ret = handle_ingress_flow_ingress__uekey_uestate_map(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__arp_tbl:
            ret = handle_ingress_flow_ingress__arp_tbl(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_9:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_9(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_0:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_0(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_12:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_12(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_14:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_14(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_2:
            ret = handle_ingress_flow_ingress__tbl_act_2(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_4:
            ret = handle_ingress_flow_ingress__tbl_act_4(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_3:
            ret = handle_ingress_flow_ingress__tbl_act_3(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_10:
            ret = handle_ingress_flow_ingress__tbl_act_10(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_9:
            ret = handle_ingress_flow_ingress__tbl_act_9(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow__condition_13:
            pif_ctlflow_state_ingress_flow = handle_ingress_flow__condition_13(_pif_parrep);
            continue;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_7:
            ret = handle_ingress_flow_ingress__tbl_act_7(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act:
            ret = handle_ingress_flow_ingress__tbl_act(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        case PIF_CTLFLOW_STATE_ingress_flow_ingress__tbl_act_8:
            ret = handle_ingress_flow_ingress__tbl_act_8(_pif_parrep, actbuf, actbuf_off + totlen, (int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        }
        if (actlen < 0) /* error! */
            return actlen & ((~(1 << PIF_LOOKUP_ERROR_BIT)));
        __critical_path();
        totlen += actlen;
        if (ret < 0)
            return -totlen;
    }

    return totlen;
}

/* Empty control flow */
int pif_ctlflow_egress_flow(int *start_state, __lmem uint32_t *_pif_parrep, __mem __addr40 uint32_t *actbuf, unsigned int actbuf_off)
{
    return 0;
}
