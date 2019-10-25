/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp.h>
#include <nfp/me.h>
#include <nfp/cls.h>
#include <std/reg_utils.h>
#include <blm/blm.h>
#include <pif_common.h>
#include <pif_counters.h>
#include <pif_pkt.h>
#include "pkt_clone.h"

/* Generated C source defining pkt_recurse related bits and bobs  */
/* Warning: your edits to this file may be lost */

__nnr uint32_t clone_field_list = 0;

void pif_clone_packet(__lmem uint32_t *parrep, uint32_t clone_id)
{
    /* No cloning actions */
    return;
}

uint32_t pif_clone_packet_submit(__lmem uint32_t *parrep, uint32_t replication_id)
{
    __gpr uint32_t i;

    replication_id++;

    switch (pkt_dup_state.type) {
        case PIF_PKT_INSTANCE_TYPE_I2E_CLONE: 

            if (clone_field_list != 0) {
                /*
                 * If a field list has been provided with the action,
                 * apply the field list to the metadata.
                 * The metadata to use is in CLS, copy the specified fields in the field list
                 * from local memory to the CLS.
                 */

                __gpr uint32_t field_id;
                __gpr uint32_t i;

                field_id = clone_field_list;
                switch (field_id)
                {
                    case 1:
                    {
                        __lmem struct pif_header_standard_metadata *lm_standard_metadata_ptr = (__lmem struct pif_header_standard_metadata *) (parrep + PIF_PARREP_standard_metadata_OFF_LW);
                        __cls struct pif_header_standard_metadata *cls_standard_metadata_ptr = (__cls struct pif_header_standard_metadata *) (parrep_copy + PIF_PARREP_standard_metadata_OFF_LW);
                        __xread struct pif_header_standard_metadata xr_data;
                        __xwrite struct pif_header_standard_metadata xw_data;
                        __gpr struct pif_header_standard_metadata write_data;

                        cls_read(&xr_data, cls_standard_metadata_ptr, sizeof(xr_data));

                        reg_cp(&write_data, &xr_data, sizeof(xr_data));

                        write_data.checksum_error = lm_standard_metadata_ptr->checksum_error; 
                        write_data.clone_spec = lm_standard_metadata_ptr->clone_spec; 
                        write_data.egress_instance = lm_standard_metadata_ptr->egress_instance; 
                        write_data.egress_port = lm_standard_metadata_ptr->egress_port; 
                        write_data.egress_spec = lm_standard_metadata_ptr->egress_spec; 
                        write_data.ingress_port = lm_standard_metadata_ptr->ingress_port; 
                        write_data.instance_type = lm_standard_metadata_ptr->instance_type; 
                        write_data.packet_length = lm_standard_metadata_ptr->packet_length; 
                        write_data.parser_error_location = lm_standard_metadata_ptr->parser_error_location; 
                        write_data.parser_status = lm_standard_metadata_ptr->parser_status; 

                        reg_cp(&xw_data, &write_data, sizeof(xw_data));
                        cls_write(&xw_data, cls_standard_metadata_ptr, sizeof(xw_data));
                    }
                    break;

                } // switch

                /* Clear clone_field_list */
                clone_field_list = 0x00;
            }

            /*
             * Copy packet info in CLS to global packet info in NN registers
             * The MU ptr and CTM packet num etc have already been setup for cloned packet in microc_clone_i2e()
             */
            retrieve_parrep((__lmem uint32_t *)parrep, (__cls uint32_t *)parrep_copy, PIF_PARREP_LEN_LW);
            retrieve_pkt_info((__cls void*)&pif_pkt_info_copy);

            {
                __lmem struct pif_header_standard_metadata *lm_ptr = (__lmem struct pif_header_standard_metadata *) (parrep + PIF_PARREP_standard_metadata_OFF_LW);

                lm_ptr->egress_instance = replication_id;
                lm_ptr->instance_type = pkt_dup_state.type;
                if (lm_ptr->clone_spec & (1 << 31))
                    lm_ptr->egress_port = lm_ptr->clone_spec;
                else
                    lm_ptr->egress_port = lm_ptr->egress_spec;
            }

            return replication_id;

        break;

    } //switch

    return replication_id;
}
void pif_clone_i2e(__lmem uint32_t *parrep, uint32_t clone_id)
{
    {
        /* Proceed with normal packet. */
        __lmem struct pif_header_standard_metadata *std_meta = (__lmem struct pif_header_standard_metadata *) (parrep + PIF_PARREP_standard_metadata_OFF_LW);

        std_meta->egress_instance = clone_id;
        std_meta->clone_spec = 0;
    }

    PIF_DUP_ACTION_CLEAR(pkt_dup_state);
    PIF_COUNT(CLONE_I2E);
    return;
}

void pif_clone_pkt_with_cls_pkt_info()
{
    /* Setup packet info to reflect new pkt and buffer */

    __gpr struct pkt_clone_destination  destination;
    __xread struct pif_pkt_info         rd_pkt_info;
    __xwrite struct pif_pkt_info        wr_pkt_info;
    __gpr uint32_t                      temp;

    cls_read((__xread void *)&rd_pkt_info, (__cls void *)&pif_pkt_info_copy.pkt, sizeof(rd_pkt_info));
    reg_cp((void *)&wr_pkt_info, &rd_pkt_info, sizeof(rd_pkt_info));

    destination = pkt_clone(pif_pkt_info_global.p_nbi.pnum, 
               pif_pkt_info_global.p_ctm_size,
               (__mem __addr40 uint32_t *) blm_buf_handle2ptr(pif_pkt_info_global.p_nbi.muptr),
               pif_pkt_info_global.p_bls, // BLM_BLQ_0 ??
               pif_pkt_info_global.p_offset,
               pif_pkt_info_global.p_len, 
               pif_pkt_info_global.p_is_split 
    );

    /* Replace the changed fields for new clone in CLS pkt_info*/

    temp = (__ISLAND << 26 | destination.ctm_pkt_num << 16);
    temp = (temp | (rd_pkt_info.p_bls << 2) | rd_pkt_info.p_len);
    wr_pkt_info.__raw[0] = temp;

    temp = blm_buf_ptr2handle(destination.mu_ptr);
    wr_pkt_info.__raw[1] = (rd_pkt_info.p_is_split << 31) | temp;

    temp = (rd_pkt_info.p_ctm_size << 30) | (rd_pkt_info.p_orig_len << 16);
    wr_pkt_info.__raw[2] = temp | (rd_pkt_info.p_offset);

    /* Set all sequenced bits equal to 0 */

    temp = rd_pkt_info.__raw[4] & 0x3ff; 
    temp |= (0 << 16 | 0 << 11 | 0 << 10) | temp; 
    wr_pkt_info.__raw[4] = temp;

    cls_write((__xwrite void *)&wr_pkt_info, (__cls void *)&pif_pkt_info_copy.pkt, sizeof(wr_pkt_info));

    {
        /* Write metadata to start of CTM buffer.*/
        __xwrite uint32_t buf_xw[2];
        __mem __addr40 void *ctm_ptr;

        ctm_ptr = pkt_ctm_ptr40(0, destination.ctm_pkt_num, 0);
        buf_xw[0] = pif_pkt_info_global.__raw[0];
        buf_xw[1] = pif_pkt_info_global.__raw[1];
        mem_write32(buf_xw, ctm_ptr, sizeof(buf_xw));
    }

    return;
}

