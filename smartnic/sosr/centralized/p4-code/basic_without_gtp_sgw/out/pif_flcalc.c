/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/me.h>
#include "pif_common.h"

uint16_t calc_0(__lmem uint32_t *parrep, __lmem struct pif_parrep_ctldata *ctldata)
{
    __gpr uint16_t calc_fld = PIF_FLCALC_CSUM16_INIT;
    __lmem struct pif_header_ipv4 *ipv4 = (__lmem struct pif_header_ipv4 *)(parrep + PIF_PARREP_ipv4_OFF_LW);
    __lmem struct pif_field_list_field_list_1_packed input_field_list_1;

    input_field_list_1._raw[0] = ((__lmem uint32_t *)ipv4)[0];
    input_field_list_1._raw[1] = ((__lmem uint32_t *)ipv4)[1];
    input_field_list_1._raw[2] = ((ipv4->ttl) << 24) | ((ipv4->protocol) << 16) | ((ipv4->srcAddr) >> 16);
    input_field_list_1._raw[3] = ((((ipv4->srcAddr) & 0xffff)) << 16) | ((ipv4->dstAddr) >> 16);
    input_field_list_1._raw[4] = ((((ipv4->dstAddr) & 0xffff)) << 16);

    calc_fld = pif_flcalc_csum16_lmem(calc_fld, (__lmem uint32_t *) input_field_list_1._raw, 18);
    calc_fld = (~calc_fld & 0xffff);
    return calc_fld;
}

uint16_t calc(__lmem uint32_t *parrep, __lmem struct pif_parrep_ctldata *ctldata)
{
    __gpr uint16_t calc_fld = PIF_FLCALC_CSUM16_INIT;
    __lmem struct pif_header_ipv4 *ipv4 = (__lmem struct pif_header_ipv4 *)(parrep + PIF_PARREP_ipv4_OFF_LW);
    __lmem struct pif_field_list_field_list_1_packed input_field_list_1;

    input_field_list_1._raw[0] = ((__lmem uint32_t *)ipv4)[0];
    input_field_list_1._raw[1] = ((__lmem uint32_t *)ipv4)[1];
    input_field_list_1._raw[2] = ((ipv4->ttl) << 24) | ((ipv4->protocol) << 16) | ((ipv4->srcAddr) >> 16);
    input_field_list_1._raw[3] = ((((ipv4->srcAddr) & 0xffff)) << 16) | ((ipv4->dstAddr) >> 16);
    input_field_list_1._raw[4] = ((((ipv4->dstAddr) & 0xffff)) << 16);

    calc_fld = pif_flcalc_csum16_lmem(calc_fld, (__lmem uint32_t *) input_field_list_1._raw, 18);
    calc_fld = (~calc_fld & 0xffff);
    return calc_fld;
}

int pif_flcalc_verify(__lmem uint32_t *parrep)
{
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);

    /* ipv4.hdrChecksum */
    if (PIF_PARREP_ipv4_VALID(ctldata)) {
        uint16_t calc_fld;
        __lmem struct pif_header_ipv4 *ipv4 = (__lmem struct pif_header_ipv4 *)(parrep + PIF_PARREP_ipv4_OFF_LW);
        calc_fld = calc(parrep, ctldata);
        if (calc_fld != ipv4->hdrChecksum)
            return -PIF_PARSE_ERROR_CHECKSUM;
    }

    /* Enable incremental updates for supported calculated fields. */
    PIF_FLCALC_UPD_INCR_SET(PIF_FLCALC_CALC_0);

    return 0;
}

void pif_flcalc_update(__lmem uint32_t *parrep)
{
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);

    /* ipv4.hdrChecksum */
    if (PIF_FLCALC_UPD_INCR(PIF_FLCALC_CALC_0) == 0) {
        if (PIF_PARREP_ipv4_VALID(ctldata)) {
            if (PIF_PARREP_ipv4_DIRTY(ctldata)) {
                uint16_t calc_fld;
                __lmem struct pif_header_ipv4 *ipv4 = (__lmem struct pif_header_ipv4 *)(parrep + PIF_PARREP_ipv4_OFF_LW);
                calc_fld = calc_0(parrep, ctldata);
                ipv4->hdrChecksum = calc_fld;
            }
        }
    }

}

