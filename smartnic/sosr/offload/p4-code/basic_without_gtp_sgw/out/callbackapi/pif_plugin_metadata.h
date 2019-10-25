/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_metadata_H__
#define __PIF_PLUGIN_metadata_H__
/*
 * Access function prototypes
 */

/* get uekey_sgwteid.ue_key */
uint32_t pif_plugin_meta_get__uekey_sgwteid__ue_key(EXTRACTED_HEADERS_T *extracted_headers);

/* set uekey_sgwteid.ue_key */
void pif_plugin_meta_set__uekey_sgwteid__ue_key(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get uekey_sgwteid.sgw_teid */
uint32_t pif_plugin_meta_get__uekey_sgwteid__sgw_teid(EXTRACTED_HEADERS_T *extracted_headers);

/* set uekey_sgwteid.sgw_teid */
void pif_plugin_meta_set__uekey_sgwteid__sgw_teid(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get vlan.pcp */
uint32_t pif_plugin_meta_get__vlan__pcp(EXTRACTED_HEADERS_T *extracted_headers);

/* set vlan.pcp */
void pif_plugin_meta_set__vlan__pcp(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get vlan.dei */
uint32_t pif_plugin_meta_get__vlan__dei(EXTRACTED_HEADERS_T *extracted_headers);

/* set vlan.dei */
void pif_plugin_meta_set__vlan__dei(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get vlan.vid */
uint32_t pif_plugin_meta_get__vlan__vid(EXTRACTED_HEADERS_T *extracted_headers);

/* set vlan.vid */
void pif_plugin_meta_set__vlan__vid(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get vlan.vlan_type */
uint32_t pif_plugin_meta_get__vlan__vlan_type(EXTRACTED_HEADERS_T *extracted_headers);

/* set vlan.vlan_type */
void pif_plugin_meta_set__vlan__vlan_type(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get kv.key1 [32;0] */
uint32_t pif_plugin_meta_get__kv__key1__0(EXTRACTED_HEADERS_T *extracted_headers);

/* get kv.key1 [32;32] */
uint32_t pif_plugin_meta_get__kv__key1__1(EXTRACTED_HEADERS_T *extracted_headers);

/* get kv.key1 [32;64] */
uint32_t pif_plugin_meta_get__kv__key1__2(EXTRACTED_HEADERS_T *extracted_headers);

/* get kv.key1 [32;96] */
uint32_t pif_plugin_meta_get__kv__key1__3(EXTRACTED_HEADERS_T *extracted_headers);

/* set kv.key1 [32;0] */
void pif_plugin_meta_set__kv__key1__0(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* set kv.key1 [32;32] */
void pif_plugin_meta_set__kv__key1__1(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* set kv.key1 [32;64] */
void pif_plugin_meta_set__kv__key1__2(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* set kv.key1 [32;96] */
void pif_plugin_meta_set__kv__key1__3(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get kv.value [32;0] */
uint32_t pif_plugin_meta_get__kv__value__0(EXTRACTED_HEADERS_T *extracted_headers);

/* get kv.value [32;32] */
uint32_t pif_plugin_meta_get__kv__value__1(EXTRACTED_HEADERS_T *extracted_headers);

/* get kv.value [32;64] */
uint32_t pif_plugin_meta_get__kv__value__2(EXTRACTED_HEADERS_T *extracted_headers);

/* get kv.value [32;96] */
uint32_t pif_plugin_meta_get__kv__value__3(EXTRACTED_HEADERS_T *extracted_headers);

/* set kv.value [32;0] */
void pif_plugin_meta_set__kv__value__0(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* set kv.value [32;32] */
void pif_plugin_meta_set__kv__value__1(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* set kv.value [32;64] */
void pif_plugin_meta_set__kv__value__2(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* set kv.value [32;96] */
void pif_plugin_meta_set__kv__value__3(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.clone_spec */
uint32_t pif_plugin_meta_get__standard_metadata__clone_spec(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.clone_spec */
void pif_plugin_meta_set__standard_metadata__clone_spec(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.egress_spec */
uint32_t pif_plugin_meta_get__standard_metadata__egress_spec(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.egress_spec */
void pif_plugin_meta_set__standard_metadata__egress_spec(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.egress_port */
uint32_t pif_plugin_meta_get__standard_metadata__egress_port(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.egress_port */
void pif_plugin_meta_set__standard_metadata__egress_port(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.ingress_port */
uint32_t pif_plugin_meta_get__standard_metadata__ingress_port(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.ingress_port */
void pif_plugin_meta_set__standard_metadata__ingress_port(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.packet_length */
uint32_t pif_plugin_meta_get__standard_metadata__packet_length(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.packet_length */
void pif_plugin_meta_set__standard_metadata__packet_length(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.checksum_error */
uint32_t pif_plugin_meta_get__standard_metadata__checksum_error(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.checksum_error */
void pif_plugin_meta_set__standard_metadata__checksum_error(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.egress_instance */
uint32_t pif_plugin_meta_get__standard_metadata__egress_instance(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.egress_instance */
void pif_plugin_meta_set__standard_metadata__egress_instance(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.parser_error_location */
uint32_t pif_plugin_meta_get__standard_metadata__parser_error_location(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.parser_error_location */
void pif_plugin_meta_set__standard_metadata__parser_error_location(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.instance_type */
uint32_t pif_plugin_meta_get__standard_metadata__instance_type(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.instance_type */
void pif_plugin_meta_set__standard_metadata__instance_type(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get standard_metadata.parser_status */
uint32_t pif_plugin_meta_get__standard_metadata__parser_status(EXTRACTED_HEADERS_T *extracted_headers);

/* set standard_metadata.parser_status */
void pif_plugin_meta_set__standard_metadata__parser_status(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get scalars.hasReturned_0 */
uint32_t pif_plugin_meta_get__scalars__hasReturned_0(EXTRACTED_HEADERS_T *extracted_headers);

/* set scalars.hasReturned_0 */
void pif_plugin_meta_set__scalars__hasReturned_0(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);

/* get scalars.pred */
uint32_t pif_plugin_meta_get__scalars__pred(EXTRACTED_HEADERS_T *extracted_headers);

/* set scalars.pred */
void pif_plugin_meta_set__scalars__pred(EXTRACTED_HEADERS_T *extracted_headers, uint32_t val);






/*
 * Access function implementations
 */

#include "pif_parrep.h"
#include "pif_headers.h"

__forceinline uint32_t pif_plugin_meta_get__uekey_sgwteid__ue_key(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_uekey_sgwteid *md = (__lmem struct pif_header_uekey_sgwteid *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_uekey_sgwteid_OFF_LW);
    return PIF_HEADER_GET_uekey_sgwteid___ue_key(md);
}

__forceinline void pif_plugin_meta_set__uekey_sgwteid__ue_key(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_uekey_sgwteid *md = (__lmem struct pif_header_uekey_sgwteid *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_uekey_sgwteid_OFF_LW);
    PIF_HEADER_SET_uekey_sgwteid___ue_key(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__uekey_sgwteid__sgw_teid(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_uekey_sgwteid *md = (__lmem struct pif_header_uekey_sgwteid *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_uekey_sgwteid_OFF_LW);
    return PIF_HEADER_GET_uekey_sgwteid___sgw_teid(md);
}

__forceinline void pif_plugin_meta_set__uekey_sgwteid__sgw_teid(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_uekey_sgwteid *md = (__lmem struct pif_header_uekey_sgwteid *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_uekey_sgwteid_OFF_LW);
    PIF_HEADER_SET_uekey_sgwteid___sgw_teid(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__vlan__pcp(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_vlan *md = (__lmem struct pif_header_vlan *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_vlan_OFF_LW);
    return PIF_HEADER_GET_vlan___pcp(md);
}

__forceinline void pif_plugin_meta_set__vlan__pcp(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_vlan *md = (__lmem struct pif_header_vlan *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_vlan_OFF_LW);
    PIF_HEADER_SET_vlan___pcp(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__vlan__dei(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_vlan *md = (__lmem struct pif_header_vlan *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_vlan_OFF_LW);
    return PIF_HEADER_GET_vlan___dei(md);
}

__forceinline void pif_plugin_meta_set__vlan__dei(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_vlan *md = (__lmem struct pif_header_vlan *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_vlan_OFF_LW);
    PIF_HEADER_SET_vlan___dei(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__vlan__vid(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_vlan *md = (__lmem struct pif_header_vlan *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_vlan_OFF_LW);
    return PIF_HEADER_GET_vlan___vid(md);
}

__forceinline void pif_plugin_meta_set__vlan__vid(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_vlan *md = (__lmem struct pif_header_vlan *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_vlan_OFF_LW);
    PIF_HEADER_SET_vlan___vid(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__vlan__vlan_type(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_vlan *md = (__lmem struct pif_header_vlan *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_vlan_OFF_LW);
    return PIF_HEADER_GET_vlan___vlan_type(md);
}

__forceinline void pif_plugin_meta_set__vlan__vlan_type(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_vlan *md = (__lmem struct pif_header_vlan *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_vlan_OFF_LW);
    PIF_HEADER_SET_vlan___vlan_type(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__kv__key1__0(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    return PIF_HEADER_GET_kv___key1___0(md);
}

__forceinline uint32_t pif_plugin_meta_get__kv__key1__1(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    return PIF_HEADER_GET_kv___key1___1(md);
}

__forceinline uint32_t pif_plugin_meta_get__kv__key1__2(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    return PIF_HEADER_GET_kv___key1___2(md);
}

__forceinline uint32_t pif_plugin_meta_get__kv__key1__3(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    return PIF_HEADER_GET_kv___key1___3(md);
}

__forceinline void pif_plugin_meta_set__kv__key1__0(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    PIF_HEADER_SET_kv___key1___0(md, val);
}

__forceinline void pif_plugin_meta_set__kv__key1__1(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    PIF_HEADER_SET_kv___key1___1(md, val);
}

__forceinline void pif_plugin_meta_set__kv__key1__2(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    PIF_HEADER_SET_kv___key1___2(md, val);
}

__forceinline void pif_plugin_meta_set__kv__key1__3(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    PIF_HEADER_SET_kv___key1___3(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__kv__value__0(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    return PIF_HEADER_GET_kv___value___0(md);
}

__forceinline uint32_t pif_plugin_meta_get__kv__value__1(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    return PIF_HEADER_GET_kv___value___1(md);
}

__forceinline uint32_t pif_plugin_meta_get__kv__value__2(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    return PIF_HEADER_GET_kv___value___2(md);
}

__forceinline uint32_t pif_plugin_meta_get__kv__value__3(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    return PIF_HEADER_GET_kv___value___3(md);
}

__forceinline void pif_plugin_meta_set__kv__value__0(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    PIF_HEADER_SET_kv___value___0(md, val);
}

__forceinline void pif_plugin_meta_set__kv__value__1(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    PIF_HEADER_SET_kv___value___1(md, val);
}

__forceinline void pif_plugin_meta_set__kv__value__2(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    PIF_HEADER_SET_kv___value___2(md, val);
}

__forceinline void pif_plugin_meta_set__kv__value__3(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_kv *md = (__lmem struct pif_header_kv *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_kv_OFF_LW);
    PIF_HEADER_SET_kv___value___3(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__clone_spec(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___clone_spec(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__clone_spec(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___clone_spec(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__egress_spec(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___egress_spec(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__egress_spec(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___egress_spec(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__egress_port(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___egress_port(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__egress_port(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___egress_port(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__ingress_port(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___ingress_port(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__ingress_port(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___ingress_port(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__packet_length(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___packet_length(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__packet_length(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___packet_length(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__checksum_error(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___checksum_error(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__checksum_error(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___checksum_error(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__egress_instance(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___egress_instance(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__egress_instance(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___egress_instance(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__parser_error_location(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___parser_error_location(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__parser_error_location(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___parser_error_location(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__instance_type(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___instance_type(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__instance_type(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___instance_type(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__standard_metadata__parser_status(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    return PIF_HEADER_GET_standard_metadata___parser_status(md);
}

__forceinline void pif_plugin_meta_set__standard_metadata__parser_status(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_standard_metadata *md = (__lmem struct pif_header_standard_metadata *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_standard_metadata_OFF_LW);
    PIF_HEADER_SET_standard_metadata___parser_status(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__scalars__hasReturned_0(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_scalars *md = (__lmem struct pif_header_scalars *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_scalars_OFF_LW);
    return PIF_HEADER_GET_scalars___hasReturned_0(md);
}

__forceinline void pif_plugin_meta_set__scalars__hasReturned_0(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_scalars *md = (__lmem struct pif_header_scalars *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_scalars_OFF_LW);
    PIF_HEADER_SET_scalars___hasReturned_0(md, val);
}

__forceinline uint32_t pif_plugin_meta_get__scalars__pred(EXTRACTED_HEADERS_T *extracted_headers)
{
    __lmem struct pif_header_scalars *md = (__lmem struct pif_header_scalars *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_scalars_OFF_LW);
    return PIF_HEADER_GET_scalars___pred(md);
}

__forceinline void pif_plugin_meta_set__scalars__pred(EXTRACTED_HEADERS_T *extracted_headers,uint32_t val)
{
    __lmem struct pif_header_scalars *md = (__lmem struct pif_header_scalars *)(((__lmem uint32_t *)extracted_headers) + PIF_PARREP_scalars_OFF_LW);
    PIF_HEADER_SET_scalars___pred(md, val);
}

#endif /* __PIF_PLUGIN_metadata_H__ */
