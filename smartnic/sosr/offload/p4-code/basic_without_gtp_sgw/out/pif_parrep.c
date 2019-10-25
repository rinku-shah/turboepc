/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/me.h>
#include <hashmap.h>
#include "pif_common.h"

extern __forceinline
pif_parrep_extract(__lmem uint32_t *_pif_parrep, __mem __addr40 uint8_t *_pif_parrep_pktdata, unsigned int _pif_parrep_pktlen, __lmem uint32_t *_pif_parrep_fk_ptr, __gpr uint32_t *_pif_parrep_fk_len)
{
    __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
    PIF_PKT_INFO_TYPE struct pif_pkt_info *pkt_info = &pif_pkt_info_global;
    __xread uint32_t _pif_read_xbuf[24];
    unsigned int _pif_read_xbuf_off = 2;
    __gpr unsigned int _pif_parrep_pktoff = -2;
    unsigned int _pif_t_index;
    __gpr int _pif_parrep_state = 0;
    __gpr int _pif_parrep_error = 0;
    int i;

    /* First zero the parsed representation control data fields */
    for (i = 0; i < PIF_PARREP_CTLDATA_LEN_LW; i++)
        _pif_parrep[PIF_PARREP_CTLDATA_OFF_LW + i] = 0;

    _pif_parrep_pktdata -= _pif_read_xbuf_off;
    mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
    _pif_t_index = ((__ctx() << 5) | __xfer_reg_number(_pif_read_xbuf)) << 2;
__label_start:
    { /* implementation of parse node start */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_ethernet *ethernet;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_start");
#endif

        ethernet = (__lmem struct pif_header_ethernet *) (_pif_parrep + PIF_PARREP_ethernet_OFF_LW);
        {
            /* extract(ethernet) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_ethernet_LEN_LW;
                    sizeB = PIF_PARREP_ethernet_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_ethernet_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 4 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 4 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 4 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 4 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_ethernet_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_start;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_ethernet_VALID(_pif_ctldata);
                PIF_PARREP_SET_ethernet_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
        {
            __lmem struct pif_global_flowkey_ethernet *_pif_fk = (__lmem struct pif_global_flowkey_ethernet *)(_pif_parrep_fk_ptr + (*_pif_parrep_fk_len));
            _pif_fk->ethernet__srcAddr = ethernet->srcAddr;
            _pif_fk->ethernet____srcAddr_1 = ethernet->__srcAddr_1;
            _pif_fk->ethernet__etherType = ethernet->etherType;
            _pif_fk->ethernet__dstAddr = ethernet->dstAddr;
            _pif_fk->ethernet____dstAddr_1 = ethernet->__dstAddr_1;
            _pif_fk->__padding = 0;
            (*_pif_parrep_fk_len) += 4;
        }
#endif
        if (((ethernet->etherType) == (0x800))) {
            __critical_path(); /* prioritize the fall through */
        } else {
            goto _pif_parrep_label_exit;
        }
    } /* end of implementation of parse node start */
__label_parse_ipv4:
    { /* implementation of parse node parse_ipv4 */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_ipv4 *ipv4;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_ipv4");
#endif

        ipv4 = (__lmem struct pif_header_ipv4 *) (_pif_parrep + PIF_PARREP_ipv4_OFF_LW);
        {
            /* extract(ipv4) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_ipv4_LEN_LW;
                    sizeB = PIF_PARREP_ipv4_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_ipv4_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_ipv4_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_ipv4;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_ipv4_VALID(_pif_ctldata);
                PIF_PARREP_SET_ipv4_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
        {
            __lmem struct pif_global_flowkey_ipv4 *_pif_fk = (__lmem struct pif_global_flowkey_ipv4 *)(_pif_parrep_fk_ptr + (*_pif_parrep_fk_len));
            _pif_fk->ipv4__srcAddr = ipv4->srcAddr;
            _pif_fk->ipv4__dstAddr = ipv4->dstAddr;
            _pif_fk->ipv4__protocol = ipv4->protocol;
            _pif_fk->ipv4__ttl = ipv4->ttl;
            _pif_fk->__padding = 0;
            (*_pif_parrep_fk_len) += 3;
        }
#endif
        if (((ipv4->protocol) == (0x6))) {
            __critical_path(); /* prioritize the fall through */
        } else if (((ipv4->protocol) == (0x11))) {
            goto __label_parse_udp;
        } else {
            goto _pif_parrep_label_exit;
        }
    } /* end of implementation of parse node parse_ipv4 */
__label_parse_tcp:
    { /* implementation of parse node parse_tcp */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_tcp *tcp;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_tcp");
#endif

        tcp = (__lmem struct pif_header_tcp *) (_pif_parrep + PIF_PARREP_tcp_OFF_LW);
        {
            /* extract(tcp) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_tcp_LEN_LW;
                    sizeB = PIF_PARREP_tcp_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_tcp_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_tcp_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_tcp;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_tcp_VALID(_pif_ctldata);
                PIF_PARREP_SET_tcp_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_tcp */
__label_parse_udp:
    { /* implementation of parse node parse_udp */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_data *data;
        __lmem struct pif_header_udp *udp;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_udp");
#endif

        data = (__lmem struct pif_header_data *) (_pif_parrep + PIF_PARREP_data_OFF_LW);
        udp = (__lmem struct pif_header_udp *) (_pif_parrep + PIF_PARREP_udp_OFF_LW);
        {
            /* extract(udp) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_udp_LEN_LW;
                    sizeB = PIF_PARREP_udp_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_udp_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 2 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 2 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_udp_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_udp;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_udp_VALID(_pif_ctldata);
                PIF_PARREP_SET_udp_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
        {
            /* extract(data) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_data_LEN_LW;
                    sizeB = PIF_PARREP_data_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_data_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 2 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 2 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_data_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_udp;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_data_VALID(_pif_ctldata);
                PIF_PARREP_SET_data_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
        {
            __lmem struct pif_global_flowkey_data *_pif_fk = (__lmem struct pif_global_flowkey_data *)(_pif_parrep_fk_ptr + (*_pif_parrep_fk_len));
            _pif_fk->data__epc_traffic_code = data->epc_traffic_code;
            _pif_fk->__padding = 0;
            (*_pif_parrep_fk_len) += 1;
        }
#endif
        if (((data->epc_traffic_code) == (0x1))) {
            goto __label_parse_auth_step_one;
        } else if (((data->epc_traffic_code) == (0x3))) {
            goto __label_parse_auth_step_three;
        } else if (((data->epc_traffic_code) == (0x14))) {
            goto __label_parse_nas_step_two;
        } else if (((data->epc_traffic_code) == (0x5))) {
            __critical_path(); /* prioritize the fall through */
        } else if (((data->epc_traffic_code) == (0x7))) {
            goto __label_parse_send_ue_teid;
        } else if (((data->epc_traffic_code) == (0x9))) {
            goto __label_parse_detach_req;
        } else if (((data->epc_traffic_code) == (0xe))) {
            goto __label_parse_ue_context_release;
        } else if (((data->epc_traffic_code) == (0x11))) {
            goto __label_parse_ue_service_req;
        } else if (((data->epc_traffic_code) == (0x13))) {
            goto __label_parse_initial_ctxt_setup_resp;
        } else {
            goto _pif_parrep_label_exit;
        }
    } /* end of implementation of parse node parse_udp */
__label_parse_send_apn:
    { /* implementation of parse node parse_send_apn */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_send_apn *send_apn;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_send_apn");
#endif

        send_apn = (__lmem struct pif_header_send_apn *) (_pif_parrep + PIF_PARREP_send_apn_OFF_LW);
        {
            /* extract(send_apn) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_send_apn_LEN_LW;
                    sizeB = PIF_PARREP_send_apn_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_send_apn_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_send_apn_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_send_apn;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_send_apn_VALID(_pif_ctldata);
                PIF_PARREP_SET_send_apn_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_send_apn */
__label_parse_auth_step_one:
    { /* implementation of parse node parse_auth_step_one */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_auth_step_one *auth_step_one;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_auth_step_one");
#endif

        auth_step_one = (__lmem struct pif_header_auth_step_one *) (_pif_parrep + PIF_PARREP_auth_step_one_OFF_LW);
        {
            /* extract(auth_step_one) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_auth_step_one_LEN_LW;
                    sizeB = PIF_PARREP_auth_step_one_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_auth_step_one_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 5 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 6 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 7 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 8 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 9 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 10 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 11 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 12 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 13 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 14 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 15 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 16 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 17 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 18 of 19 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_auth_step_one_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_auth_step_one;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_auth_step_one_VALID(_pif_ctldata);
                PIF_PARREP_SET_auth_step_one_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_auth_step_one */
__label_parse_initial_ctxt_setup_resp:
    { /* implementation of parse node parse_initial_ctxt_setup_resp */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_initial_ctxt_setup_resp *initial_ctxt_setup_resp;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_initial_ctxt_setup_resp");
#endif

        initial_ctxt_setup_resp = (__lmem struct pif_header_initial_ctxt_setup_resp *) (_pif_parrep + PIF_PARREP_initial_ctxt_setup_resp_OFF_LW);
        {
            /* extract(initial_ctxt_setup_resp) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_initial_ctxt_setup_resp_LEN_LW;
                    sizeB = PIF_PARREP_initial_ctxt_setup_resp_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_initial_ctxt_setup_resp_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 5 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_initial_ctxt_setup_resp_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_initial_ctxt_setup_resp;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_initial_ctxt_setup_resp_VALID(_pif_ctldata);
                PIF_PARREP_SET_initial_ctxt_setup_resp_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
        {
            __lmem struct pif_global_flowkey_initial_ctxt_setup_resp *_pif_fk = (__lmem struct pif_global_flowkey_initial_ctxt_setup_resp *)(_pif_parrep_fk_ptr + (*_pif_parrep_fk_len));
            _pif_fk->initial_ctxt_setup_resp__ue_key = initial_ctxt_setup_resp->ue_key;
            _pif_fk->initial_ctxt_setup_resp____ue_key_1 = initial_ctxt_setup_resp->__ue_key_1;
            (*_pif_parrep_fk_len) += 1;
        }
#endif
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_initial_ctxt_setup_resp */
__label_parse_detach_req:
    { /* implementation of parse node parse_detach_req */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_detach_req *detach_req;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_detach_req");
#endif

        detach_req = (__lmem struct pif_header_detach_req *) (_pif_parrep + PIF_PARREP_detach_req_OFF_LW);
        {
            /* extract(detach_req) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_detach_req_LEN_LW;
                    sizeB = PIF_PARREP_detach_req_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_detach_req_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 5 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 6 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 7 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 8 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_detach_req_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_detach_req;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_detach_req_VALID(_pif_ctldata);
                PIF_PARREP_SET_detach_req_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_detach_req */
__label_parse_nas_step_two:
    { /* implementation of parse node parse_nas_step_two */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_nas_step_two *nas_step_two;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_nas_step_two");
#endif

        nas_step_two = (__lmem struct pif_header_nas_step_two *) (_pif_parrep + PIF_PARREP_nas_step_two_OFF_LW);
        {
            /* extract(nas_step_two) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_nas_step_two_LEN_LW;
                    sizeB = PIF_PARREP_nas_step_two_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_nas_step_two_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 8 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 8 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 8 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 8 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 8 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 5 of 8 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 6 of 8 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 7 of 8 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_nas_step_two_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_nas_step_two;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_nas_step_two_VALID(_pif_ctldata);
                PIF_PARREP_SET_nas_step_two_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_nas_step_two */
__label_parse_ue_context_release:
    { /* implementation of parse node parse_ue_context_release */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_ue_context_rel_req *ue_context_rel_req;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_ue_context_release");
#endif

        ue_context_rel_req = (__lmem struct pif_header_ue_context_rel_req *) (_pif_parrep + PIF_PARREP_ue_context_rel_req_OFF_LW);
        {
            /* extract(ue_context_rel_req) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_ue_context_rel_req_LEN_LW;
                    sizeB = PIF_PARREP_ue_context_rel_req_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_ue_context_rel_req_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 5 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 6 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 7 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 8 of 9 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_ue_context_rel_req_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_ue_context_release;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_ue_context_rel_req_VALID(_pif_ctldata);
                PIF_PARREP_SET_ue_context_rel_req_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_ue_context_release */
__label_parse_auth_step_three:
    { /* implementation of parse node parse_auth_step_three */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_auth_step_three *auth_step_three;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_auth_step_three");
#endif

        auth_step_three = (__lmem struct pif_header_auth_step_three *) (_pif_parrep + PIF_PARREP_auth_step_three_OFF_LW);
        {
            /* extract(auth_step_three) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_auth_step_three_LEN_LW;
                    sizeB = PIF_PARREP_auth_step_three_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_auth_step_three_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 5 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_auth_step_three_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_auth_step_three;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_auth_step_three_VALID(_pif_ctldata);
                PIF_PARREP_SET_auth_step_three_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_auth_step_three */
__label_parse_send_ue_teid:
    { /* implementation of parse node parse_send_ue_teid */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_send_ue_teid *send_ue_teid;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_send_ue_teid");
#endif

        send_ue_teid = (__lmem struct pif_header_send_ue_teid *) (_pif_parrep + PIF_PARREP_send_ue_teid_OFF_LW);
        {
            /* extract(send_ue_teid) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_send_ue_teid_LEN_LW;
                    sizeB = PIF_PARREP_send_ue_teid_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_send_ue_teid_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 4 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 4 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 4 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 4 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_send_ue_teid_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_send_ue_teid;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_send_ue_teid_VALID(_pif_ctldata);
                PIF_PARREP_SET_send_ue_teid_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_send_ue_teid */
__label_parse_ue_service_req:
    { /* implementation of parse node parse_ue_service_req */
        __lmem struct pif_parrep_ctldata *_pif_ctldata = (__lmem struct pif_parrep_ctldata *)(_pif_parrep + PIF_PARREP_CTLDATA_OFF_LW);
        __lmem struct pif_header_ue_service_req *ue_service_req;
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state_parse_ue_service_req");
#endif

        ue_service_req = (__lmem struct pif_header_ue_service_req *) (_pif_parrep + PIF_PARREP_ue_service_req_OFF_LW);
        {
            /* extract(ue_service_req) */

            /* primitive body */
            {
                __gpr uint32_t _pif_parrep_hdrsz = 0;

                {
                    __lmem uint32_t *lm32;
                    unsigned int sizeLW, sizeB;
                    unsigned int lmoff;
                    unsigned int i;

                    sizeLW = PIF_PARREP_ue_service_req_LEN_LW;
                    sizeB = PIF_PARREP_ue_service_req_LEN_B;
                    lm32 = _pif_parrep + PIF_PARREP_ue_service_req_OFF_LW;

                    if (_pif_read_xbuf_off + sizeB > 24 * 4) {
                        _pif_parrep_pktoff += _pif_read_xbuf_off;
                        _pif_parrep_pktdata += _pif_read_xbuf_off;
                        mem_read32(_pif_read_xbuf, _pif_parrep_pktdata, sizeof(_pif_read_xbuf));
                        _pif_read_xbuf_off = 0;
                    }
                    __critical_path();


                    if (_pif_read_xbuf_off & 0x3) {
                        unsigned int lmval;

                        local_csr_write(local_csr_t_index_byte_index, _pif_t_index + _pif_read_xbuf_off);
                        __asm byte_align_be[--, *$index++];
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                        __asm byte_align_be[lmval, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    } else {
                        unsigned int lmval;

                        __critical_path();
                        local_csr_write(local_csr_t_index, _pif_t_index + _pif_read_xbuf_off);
                         /* unroll lw 0 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 1 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 2 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 3 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 4 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                         /* unroll lw 5 of 6 */
                        __asm alu[lmval, --, B, *$index++];
                        *lm32 = lmval;
                        lm32 += 1;
                    }
                        __implicit_read(_pif_read_xbuf);
                    _pif_read_xbuf_off += sizeB;
                }
                _pif_parrep_hdrsz = PIF_PARREP_ue_service_req_LEN_B;

                if (_pif_parrep_pktoff + _pif_read_xbuf_off > _pif_parrep_pktlen) {
                    _pif_parrep_error = PIF_PARSE_ERROR_OUT_OF_PACKET;
                    _pif_parrep_state = PIF_PARREP_STATE_parse_ue_service_req;
                    goto _pif_parrep_label_error;
                }
                __critical_path();
                PIF_PARREP_SET_ue_service_req_VALID(_pif_ctldata);
                PIF_PARREP_SET_ue_service_req_ORIG_LEN(_pif_ctldata, _pif_parrep_hdrsz);
            }
        }
#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
        {
            __lmem struct pif_global_flowkey_ue_service_req *_pif_fk = (__lmem struct pif_global_flowkey_ue_service_req *)(_pif_parrep_fk_ptr + (*_pif_parrep_fk_len));
            _pif_fk->ue_service_req__ue_key = ue_service_req->ue_key;
            (*_pif_parrep_fk_len) += 1;
        }
#endif
        goto _pif_parrep_label_exit;
    } /* end of implementation of parse node parse_ue_service_req */
_pif_parrep_label_exit:
    pif_pkt_info_spec.pkt_pl_off = _pif_parrep_pktoff + _pif_read_xbuf_off;
    PIF_PARREP_SET_VALID(_pif_ctldata);
#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
    {
        __lmem struct pif_header_standard_metadata *standard_metadata = (__lmem struct pif_header_standard_metadata *)(parrep + PIF_PARREP_standard_metadata_OFF_LW);
        __lmem struct pif_global_flowkey_metadata *_pif_fk = (__lmem struct pif_global_flowkey_metadata *)(_pif_parrep_fk_ptr + *_pif_parrep_fk_len);
        _pif_fk->standard_metadata__ingress_port = standard_metadata->ingress_port;
        _pif_fk->standard_metadata__instance_type = standard_metadata->instance_type;
        _pif_fk->__padding = 0;
        (*_pif_parrep_fk_len) += 1;
        }
    _pif_parrep_fk_ptr[(*_pif_parrep_fk_len) + 0] = _pif_parrep[PIF_PARREP_CTLDATA_OFF_LW + 0] & 0x81209f00;
    _pif_parrep_fk_ptr[(*_pif_parrep_fk_len) + 1] = _pif_parrep[PIF_PARREP_CTLDATA_OFF_LW + 1] & 0x0;
    (*_pif_parrep_fk_len) += PIF_PARREP_CTLDATA_LEN_LW;
#endif /* !PIF_GLOBAL_FLOWCACHE_DISABLED */
    return 0;
_pif_parrep_label_error:
    pif_pkt_info_spec.pkt_pl_off = _pif_parrep_pktoff + _pif_read_xbuf_off;
    pif_global_set_stdmd_parser_error_location(_pif_parrep, _pif_parrep_state);
    return -_pif_parrep_error;
}

extern __forceinline int
pif_parrep_exceptions(__lmem uint32_t *_pif_parrep, int _pif_pe_error, __lmem uint32_t *_pif_parrep_fk_ptr, __gpr uint32_t *_pif_parrep_fk_len)
{
    return -1; /* no exceptions, always fail */
}
