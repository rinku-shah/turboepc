/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_PLUGIN_H__
#define __PIF_PLUGIN_H__

/* This file is generate, edit at your peril */

#include <stdint.h>
#include <nfp.h>
#include "pif_common.h"

#define EXTRACTED_HEADERS_T __lmem uint32_t
#define MATCH_DATA_T __xread uint32_t
#define ACTION_DATA_T __xread uint32_t

#define PIF_PLUGIN_RETURN_DROP PIF_RETURN_DROP
#define PIF_PLUGIN_RETURN_EXIT PIF_RETURN_EXIT
#define PIF_PLUGIN_RETURN_FORWARD PIF_RETURN_FORWARD

#include "pif_plugin_metadata.h"
#ifdef PIF_PLUGIN_INIT
void pif_plugin_init(); /* called once per worker thread */
void pif_plugin_init_master(); /* called once system wide */
#endif /* PIF_PLUGIN_INIT */
#include "pif_plugin_ue_context_rel_req.h"
#include "pif_plugin_initial_ctxt_setup_resp.h"
#include "pif_plugin_tcp.h"
#include "pif_plugin_packet_in.h"
#include "pif_plugin_offload_initial_ctxt_setup_resp.h"
#include "pif_plugin_initial_ctxt_setup_req.h"
#include "pif_plugin_auth_step_three.h"
#include "pif_plugin_ue_context_rel_command.h"
#include "pif_plugin_attach_accept.h"
#include "pif_plugin_detach_req.h"
#include "pif_plugin_ipv4.h"
#include "pif_plugin_udp.h"
#include "pif_plugin_send_apn.h"
#include "pif_plugin_data.h"
#include "pif_plugin_send_ue_teid.h"
#include "pif_plugin_offload_ue_service_req.h"
#include "pif_plugin_ue_service_req.h"
#include "pif_plugin_nas_step_two.h"
#include "pif_plugin_packet_out.h"
#include "pif_plugin_ethernet.h"
#include "pif_plugin_auth_step_one.h"

#endif /* __PIF_PLUGIN_H__ */
