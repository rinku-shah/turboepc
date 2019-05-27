#ifndef __CHECKSUMS__
#define __CHECKSUMS__
#include "headers.p4"

/*************************************************************************
************   C H E C K S U M    V E R I F I C A T I O N   *************
*************************************************************************/

control c_verify_checksum(inout headers hdr, inout metadata meta) {
    apply {
        verify_checksum(
	    hdr.ipv4.isValid(),
            { hdr.ipv4.version,
	          hdr.ipv4.ihl,
              hdr.ipv4.diffserv,
              hdr.ipv4.totalLen,
              hdr.ipv4.identification,
              hdr.ipv4.flags,
              hdr.ipv4.fragOffset,
              hdr.ipv4.ttl,
              hdr.ipv4.protocol,
              hdr.ipv4.srcAddr,
              hdr.ipv4.dstAddr },
            hdr.ipv4.hdrChecksum,
            HashAlgorithm.csum16);

        verify_checksum(
        hdr.control_ipv4.isValid(),
            { hdr.control_ipv4.version,
	          hdr.control_ipv4.ihl,
              hdr.control_ipv4.diffserv,
              hdr.control_ipv4.totalLen,
              hdr.control_ipv4.identification,
              hdr.control_ipv4.flags,
              hdr.control_ipv4.fragOffset,
              hdr.control_ipv4.ttl,
              hdr.control_ipv4.protocol,
              hdr.control_ipv4.srcAddr,
              hdr.control_ipv4.dstAddr },
            hdr.control_ipv4.hdrChecksum,
            HashAlgorithm.csum16);
    }
}

/*************************************************************************
*************   C H E C K S U M    C O M P U T A T I O N   **************
*************************************************************************/

control c_compute_checksum(inout headers  hdr, inout metadata meta) {
     apply {
	update_checksum(
         true,
	    //hdr.ipv4.isValid(),
            { hdr.ipv4.version,
	          hdr.ipv4.ihl,
              hdr.ipv4.diffserv,
              hdr.ipv4.totalLen,
              hdr.ipv4.identification,
              hdr.ipv4.flags,
              hdr.ipv4.fragOffset,
              hdr.ipv4.ttl,
              hdr.ipv4.protocol,
              hdr.ipv4.srcAddr,
              hdr.ipv4.dstAddr },
            hdr.ipv4.hdrChecksum,
            HashAlgorithm.csum16);

    // @vikas: @udp in tcp : we need to update checksum of update ipv4 header as well

    update_checksum(
	    hdr.control_ipv4.isValid(),
            { hdr.control_ipv4.version,
	          hdr.control_ipv4.ihl,
              hdr.control_ipv4.diffserv,
              hdr.control_ipv4.totalLen,
              hdr.control_ipv4.identification,
              hdr.control_ipv4.flags,
              hdr.control_ipv4.fragOffset,
              hdr.control_ipv4.ttl,
              hdr.control_ipv4.protocol,
              hdr.control_ipv4.srcAddr,
              hdr.control_ipv4.dstAddr },
            hdr.control_ipv4.hdrChecksum,
            HashAlgorithm.csum16);
    
    update_checksum(
	    //hdr.ipv4.isValid(),
        true,
            { 
            hdr.ipv4.srcAddr,
            hdr.ipv4.dstAddr,
            // 8'0';
            8w0,
            //00000000,
            hdr.ipv4.protocol,
            //16w1066, // hardcoding as all packets have 1024 Bytes long payload + 12 Bytes TCP options + 20 Bytes TCP header + 10Bytes (sep+sgwteid)
            16w101,
            //(bit<16>)hdr.ipv4.totalLen - (bit<16>)(hdr.ipv4.ihl << 2), 
            hdr.tcp.src_port,
            hdr.tcp.dst_port,
            hdr.tcp.seq_no,
            hdr.tcp.ack_no,
            hdr.tcp.data_offset,
            hdr.tcp.res,
            hdr.tcp.ecn,
            hdr.tcp.ctrl,
            hdr.tcp.window,
            hdr.tcp.urgent_ptr,
            hdr.tcp.options,
            hdr.control_ipv4.version,
            hdr.control_ipv4.ihl,
            hdr.control_ipv4.diffserv,
            hdr.control_ipv4.totalLen,
            hdr.control_ipv4.identification,
            hdr.control_ipv4.flags,
            hdr.control_ipv4.fragOffset,
            hdr.control_ipv4.ttl,
            hdr.control_ipv4.protocol,
            hdr.control_ipv4.hdrChecksum,
            hdr.control_ipv4.srcAddr,
            hdr.control_ipv4.dstAddr,
            hdr.control_udp.srcPort,
            hdr.control_udp.dstPort,
            hdr.control_udp.length_,
            hdr.control_udp.checksum,
            hdr.data.epc_traffic_code,
            hdr.data.sep,
            hdr.offload_ue_service_req.ue_key,
            hdr.offload_ue_service_req.sep1,
            hdr.offload_ue_service_req.ksi_asme,
            hdr.offload_ue_service_req.sep2,
            hdr.offload_ue_service_req.ue_ip,
            hdr.offload_ue_service_req.sep3,
            hdr.offload_ue_service_req.sgw_teid
             },
            hdr.tcp.checksum,
            HashAlgorithm.csum16); 
    }
}

#endif
