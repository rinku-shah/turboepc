#ifndef __CHECKSUMS__
#define __CHECKSUMS__
#include "headers.p4"

/*************************************************************************
************   C H E C K S U M    V E R I F I C A T I O N   *************
*************************************************************************/

control update_gtpu_checksum(
        inout ipv4_t gtpu_ipv4,
        inout udp_t  gtpu_udp,
        in    gtpu_t gtpu,
        in    ipv4_t ipv4,
        in    udp_t  udp
    ) {
    apply {
        // Compute outer IPv4 checksum.
        update_checksum(gtpu_ipv4.isValid(),
            {
                gtpu_ipv4.version,
                gtpu_ipv4.ihl,
                gtpu_ipv4.diffserv,
                gtpu_ipv4.totalLen,
                gtpu_ipv4.identification,
                gtpu_ipv4.flags,
                gtpu_ipv4.fragOffset,
                gtpu_ipv4.ttl,
                gtpu_ipv4.protocol,
                gtpu_ipv4.srcAddr,
                gtpu_ipv4.dstAddr
            },
            gtpu_ipv4.hdrChecksum,
            HashAlgorithm.csum16
        );


        // Compute outer UDP checksum.
        update_checksum_with_payload(gtpu_udp.isValid(),
            {
                gtpu_ipv4.srcAddr,
                gtpu_ipv4.dstAddr,
                8w0,
                gtpu_ipv4.protocol,
                gtpu_udp.length_,
                gtpu_udp.srcPort,
                gtpu_udp.dstPort,
                gtpu_udp.length_,
                gtpu,
                ipv4,
                // we are assuming only UDP for uplink/downlink packets
                udp
            },
            gtpu_udp.checksum,
            HashAlgorithm.csum16
        );

    }
}

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
    }
}

/*************************************************************************
*************   C H E C K S U M    C O M P U T A T I O N   **************
*************************************************************************/

control c_compute_checksum(inout headers  hdr, inout metadata meta) {
     apply {
	update_checksum(
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
        
         update_gtpu_checksum.apply(hdr.gtpu_ipv4, hdr.gtpu_udp, hdr.gtpu,
                                   hdr.ipv4, hdr.udp);
    }
}

#endif
