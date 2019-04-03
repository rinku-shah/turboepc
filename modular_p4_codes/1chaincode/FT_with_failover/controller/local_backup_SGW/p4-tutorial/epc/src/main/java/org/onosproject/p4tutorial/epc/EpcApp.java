/*
 * Copyright 2017-present Open Networking Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.onosproject.p4tutorial.epc;

import org.onlab.packet.Ethernet;
import org.onlab.packet.IPacket;
import org.onlab.packet.UDP;
import org.onlab.packet.IPv4;
import org.onlab.packet.Ip4Prefix;
import org.onlab.packet.IpPrefix;

import org.onlab.packet.Ip4Address;
import org.onlab.packet.TCP;
import org.onlab.packet.TpPort;
import org.onlab.packet.UDP;
import org.onlab.packet.MacAddress;
import com.google.common.collect.Lists;
import org.apache.felix.scr.annotations.Activate;
import org.apache.felix.scr.annotations.Component;
import org.apache.felix.scr.annotations.Deactivate;
import org.apache.felix.scr.annotations.Reference;
import org.apache.felix.scr.annotations.ReferenceCardinality;
import org.apache.felix.scr.annotations.Service;
import org.onlab.packet.IpAddress;
import org.onosproject.core.ApplicationId;
import org.onosproject.core.CoreService;
import org.onosproject.net.DeviceId;
import org.onosproject.net.Host;
import org.onosproject.net.Link;
import org.onosproject.net.Path;
import org.onosproject.net.PortNumber;
import org.onosproject.net.flow.DefaultFlowRule;
import org.onosproject.net.flow.DefaultTrafficSelector;
import org.onosproject.net.flow.DefaultTrafficTreatment;
import org.onosproject.net.flow.FlowRule;
import org.onosproject.net.HostId;
import org.onosproject.net.flow.FlowRuleService;
import org.onosproject.net.flow.criteria.PiCriterion;
import org.onosproject.net.host.HostEvent;
import org.onosproject.net.host.HostListener;
import org.onosproject.net.host.HostService;
import org.onosproject.net.packet.InboundPacket;
import org.onosproject.net.packet.PacketContext;
import org.onosproject.net.packet.PacketPriority;
import org.onosproject.net.packet.PacketProcessor;
import org.onosproject.net.packet.PacketService;
import org.onosproject.net.pi.model.PiActionId;
import org.onosproject.net.pi.model.PiActionParamId;
import org.onosproject.net.pi.model.PiMatchFieldId;
import org.onosproject.net.pi.model.PiTableId;
import org.onosproject.net.pi.runtime.PiAction;
import org.onosproject.net.pi.runtime.PiActionParam;
import org.onosproject.net.topology.Topology;
import org.onosproject.net.topology.TopologyService;
import org.onosproject.net.flow.TrafficSelector;
import org.onosproject.net.ConnectPoint;
import org.onlab.packet.Data;
import org.onosproject.net.packet.DefaultOutboundPacket;
import org.onosproject.net.packet.OutboundPacket;
import org.onosproject.net.packet.PacketService;
import org.onosproject.net.flow.DefaultTrafficTreatment;
import org.onosproject.net.flow.TrafficTreatment;

import org.slf4j.Logger;

import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.Set;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.nio.charset.Charset;
import java.util.concurrent.atomic.AtomicInteger;

import java.nio.charset.StandardCharsets;



import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

import static org.slf4j.LoggerFactory.getLogger;

/**
 * MyTunnel application which provides forwarding between each pair of hosts vi
 * MyTunnel protocol as defined in mytunnel.p4.
 * <p>
 * The app works by listening for host events. Each time a new host is
 * discovered, it provisions a tunnel between that host and all the others.
 */
@Component(immediate = true)
@Service(value = EpcApp.class)
public class EpcApp {

    private static final String APP_NAME = "org.onosproject.p4tutorial.epc";

    // Default priority used for flow rules installed by this app.
    private static final int FLOW_RULE_PRIORITY = 100;

    private ApplicationId appId;

    private static final Logger log = getLogger(EpcApp.class);

    //--------------------------------------------------------------------------
    // ONOS services needed by this application.
    //--------------------------------------------------------------------------

    @Reference(cardinality = ReferenceCardinality.MANDATORY_UNARY)
    private FlowRuleService flowRuleService;

    @Reference(cardinality = ReferenceCardinality.MANDATORY_UNARY)
    private CoreService coreService;

    @Reference(cardinality = ReferenceCardinality.MANDATORY_UNARY)
    private TopologyService topologyService;

    @Reference(cardinality = ReferenceCardinality.MANDATORY_UNARY)
    protected PacketService packetService;

    private ReactivePacketProcessor processor = new ReactivePacketProcessor();

    private int counter = 0;

    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------

    @Activate
    public void activate() {
        // Register app and event listeners.
        log.info("Starting EpcApp...");
        appId = coreService.registerApplication(APP_NAME);
        packetService.addProcessor(processor, PacketProcessor.director(2));
        requestIntercepts();
        
        log.info("STARTED EpcApp...", appId.id());
    }

    @Deactivate
    public void deactivate() {
        // Remove listeners and clean-up flow rules.
        log.info("Stopping...");
        withdrawIntercepts();
        flowRuleService.removeFlowRulesById(appId);
        packetService.removeProcessor(processor);
        processor = null;
        log.info("STOPPED");
    }
    /**
     * Request packet in via packet service.
     */
    private void requestIntercepts() {
        TrafficSelector.Builder selector = DefaultTrafficSelector.builder();
        // packetService.requestPackets(selector.build(), PacketPriority.REACTIVE, appId);

        /* PacketPriority.REACTIVE = packets are only sent to the
        controller if they fail to match any of the rules installed in the switch.  */
        /* PacketPriority.CONTROL = High priority for control traffic this will result in all 
        traffic matching the selector to be sent to controller */
        // int epc_code = 50;
        // int PORTMASK = 0xff;
        // PiMatchFieldId epcCode = PiMatchFieldId.of("hdr.data.epc_traffic_code");
        // PiCriterion match = PiCriterion.builder()
        //         .matchTernary(epcCode, epc_code,PORTMASK)
        //         .build();
        // packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        // epc_code = 51;
        // match = PiCriterion.builder()
        //         .matchTernary(epcCode, epc_code,PORTMASK)
        //         .build();
        // packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        // @offload design : since the root onos has already requested for packets we will not request again and the SGW will forward to local onos the service request and ctxt release request.
    }
    /**
     * Cancel request for packet in via packet service.
     */
    private void withdrawIntercepts() {
        TrafficSelector.Builder selector = DefaultTrafficSelector.builder();
        selector.matchEthType(Ethernet.TYPE_IPV4);
        packetService.cancelPackets(selector.build(), PacketPriority.REACTIVE, appId);
    }
    /**
     * Packet processor responsible for forwarding packets along their paths.
     */
    private class ReactivePacketProcessor implements PacketProcessor {

        private ConcurrentHashMap<String, String> imsi_xres_mapping = new ConcurrentHashMap<String, String>();
        private ConcurrentHashMap<String, String> uekey_guti_map = new ConcurrentHashMap<String, String>(); // Key: UE_Key, Value: GUTI
        private ConcurrentHashMap<String, String[]> uekey_nas_keys_map = new ConcurrentHashMap<String, String[]>();		// Key = IMSI, Value = [0]: K_ASME, [1]: NAS Integrity key, NAS Encryption key
        // @offload design :  we do not need HSS at local onos
        SGW sgw = new SGW();
        FT ft = new FT();
        FR fr = new FR();

        int uePort = Constants.DEFAULT_SWITCH_UE_PORT;


        @Override
        public void process(PacketContext context) {
            // Stop processing if the packet has been handled, since we
            // can't do any more to it.

            if (context.isHandled()) {
//                log.info("context is already handled");
                return;
            }

            InboundPacket pkt = context.inPacket();
            ConnectPoint connectPoint = pkt.receivedFrom();
            /******************************************************************************************************************************/
            
            // ingress port will help us identify whether primary is active or not.
            // if primary sgw is active then we get the packet at SGW1_2 from port 2 of SGW1_2
            //  if primary is down, then we recive ingress port as 1, as all the packets are directly forwarded from DGW to SGW1_2 
            long ingressPort = connectPoint.port().toLong();
            // @FT_with_failover: if primary is active then we send the PACKET OUT via the same port from which Packet IN came  
            boolean primary_active;
            if(ingressPort == Constants.primary_to_backup_SGW_Port){
                primary_active = true;
            }
            // @FT_with_failover: if primary is not active then we have to send the packet directly to DGW port
            else if(ingressPort == Constants.DGW_to_backup_SGW_Port){
                primary_active = false;
                log.warn("************* PRIMARY Switch is DEAD. Failover successful!!!!");
            }

            // @TODO : this might not be needed, need to check.
            if(primary_active==false){
                //@FT_with_failover:  since primary is DEAD so we send the PACKET OUT messages directly to DGW.
                ElementId eid = connectPoint.elementId();
                PortNumber portNumber(Constants.DGW_to_backup_SGW_Port);
                deviceId = ConnectPoint(eid,portNumber);
            }

            /******************************************************************************************************************************/
            DeviceId deviceId = pkt.receivedFrom().deviceId();
            if(Constants.DEBUG) {
                log.warn("Packet received from {}", connectPoint);
                log.warn("Device ID {}", deviceId);
            }


            // parse the incoming packet as Ethernet frame
            Ethernet ethPkt = pkt.parsed();

            // Bail if this is deemed to be a control packet.
            if (isControlPacket(ethPkt)) {
                return;
            }

            HostId id = HostId.hostId(ethPkt.getDestinationMAC());

            // Do not process LLDP MAC address in any way.
            if (id.mac().isLldp()) {
                return;
            }

            // Do not process IPv4 multicast packets, let mfwd handle them
            if (ethPkt.getEtherType() == Ethernet.TYPE_IPV4) {
                if (id.mac().isMulticast()) {
                    return;
                }
            }

            /****************   PARSE Ethernet srcMAC and dstMAC ***************************/
            MacAddress srcMac = ethPkt.getSourceMAC();
            MacAddress dstMac = ethPkt.getDestinationMAC();
            //            log.warn("srcMACAddrestype = {}",ethPkt.getSourceMAC().getClass().getName());
            if(Constants.DEBUG) {
                log.warn("srcMACAddres = {}", srcMac);
                log.warn("dstMACAddres = {}", dstMac);
            }

            //parse the incoming packet as IP packet
            IPacket ipPkt = pkt.parsed();
            // ipheader will have IPv4 header
            IPacket ipheader = ipPkt.getPayload();
            // tcp_udp_header will have tcp/udp header
            IPacket tcp_udp_header = ipheader.getPayload();
            // final_payload will have actual payload of the packet
            IPacket final_payload = tcp_udp_header.getPayload();

            byte ipv4Protocol=IPv4.PROTOCOL_UDP;
            int ipv4SourceAddress = 0;
            int ipv4DstAddress = 0;
            int udp_srcport=0;
            int udp_dstport=0;
            int tcp_srcport=0;
            int tcp_dstport=0;
            String DGW_IPAddr = "";
            int sgw_teid = 0;
            int outPort = 0;

            /****************   PARSE Ipv4 SrcIP and DstIP ***************************/

            if (ethPkt.getEtherType() == Ethernet.TYPE_IPV4) {
                IPv4 ipv4Packet = (IPv4) ipPkt.getPayload();
                ipv4Protocol = ipv4Packet.getProtocol();
                ipv4SourceAddress = ipv4Packet.getSourceAddress();
                ipv4DstAddress = ipv4Packet.getDestinationAddress();
                Ip4Prefix matchIp4SrcPrefix =
                        Ip4Prefix.valueOf(ipv4Packet.getSourceAddress(),
                                          Ip4Prefix.MAX_MASK_LENGTH);
                Ip4Prefix matchIp4DstPrefix =
                        Ip4Prefix.valueOf(ipv4Packet.getDestinationAddress(),
                                          Ip4Prefix.MAX_MASK_LENGTH);

                 DGW_IPAddr = ipv4Packet.fromIPv4Address(ipv4SourceAddress);  // returns string IP of DGW_IPAddr
                if(Constants.DEBUG) {
                   log.warn("ipv4srcAddres = {}", matchIp4SrcPrefix);
                   log.warn("ipv4dstAddres = {}", matchIp4DstPrefix);
                }


                /****************   PARSE TCP SrcPort and DstPort ***************************/

                if (ipv4Protocol == IPv4.PROTOCOL_TCP) {
                    TCP tcpPacket = (TCP) ipv4Packet.getPayload();
                    tcp_srcport = tcpPacket.getSourcePort();
                    tcp_dstport = tcpPacket.getDestinationPort();
                    if (Constants.DEBUG) {
                        log.warn("TCP srcPort = {}", tcp_srcport);
                        log.warn("TCP dstPort = {}", tcp_dstport);
                    }
                }
                /****************   PARSE UDP SrcPort and DstPort ***************************/

                if (ipv4Protocol == IPv4.PROTOCOL_UDP) {
                    UDP udpPacket = (UDP) ipv4Packet.getPayload();
                    udp_srcport = udpPacket.getSourcePort();
                    udp_dstport = udpPacket.getDestinationPort();
                    if(Constants.DEBUG) {
                        log.warn("UDP srcPort = {}", udp_srcport);
                        log.warn("UDP dstPort = {}", udp_dstport);
                    }
                }
                if (ipv4Protocol == IPv4.PROTOCOL_ICMP) {
                    if(Constants.DEBUG){
                        log.info("received ICMP packet returning ");
                        }
                        return;
                }
            }

            String payload;
            if(Constants.BITWISE_DEBUG){
                log.warn("payload direct = {}",((Data)final_payload).getData());
            }
            byte[] p =((Data)final_payload).getData();
            byte [] b1 = Arrays.copyOfRange(p, 0, 1); //code
            byte [] b2 = Arrays.copyOfRange(p, 1, 7); //sep1

            byte code = ByteBuffer.wrap(b1).get();
            int type = code;
			String sep1 = new String(b2, StandardCharsets.UTF_8); //6 byte
                

            ByteBuffer bb = ByteBuffer.wrap(((Data)final_payload).getData());
           
            payload = new String((((Data)final_payload).getData()),  Charset.forName("UTF-8"));
            if (ethPkt == null) {
                return;
            }
            else{
                if(Constants.DEBUG) {
                    log.warn(" {}", ipheader);
                    log.warn(" {}", tcp_udp_header);
                    log.warn("Packet payload = {}",payload);

                }
            }


            @SuppressWarnings("unused")
            String tmpArray[], tmpArray2[], decArray[], NAS_Keys[];
            String NAS_MAC = null;
            // String res, xres, autn, rand, K_ASME, imsi, ue_nw_capability, KSI_ASME, SQN, tai;
            String res, xres, autn, rand, K_ASME,imsi, KSI_ASME, SQN,tai;
            byte ue_nw_capability;
            StringBuilder response;
            byte[] arr =((Data)final_payload).getData();

            /************************************************************************************/

            if(payload.contains(Constants.SEPARATOR)){
                tmpArray = payload.split(Constants.SEPARATOR);
                Date d1 = null, d2 = null;
                int step = 0;

                if(Constants.DEBUG) {
                    log.warn("tmpArray[0] = {}", tmpArray[0]);
                }
                // switch(tmpArray[0]){
                switch(Integer.toString(type)){
                    
                    case Constants.REQUEST_STARTING_IP:
                        break;

                    case Constants.AUTHENTICATION_STEP_ONE:
                        // @offload will only handle service request and context release messgaes
                        break;

                    case Constants.AUTHENTICATION_STEP_THREE:
                        // @offload will only handle service request and context release messgaes
                        break;

                    case Constants.SEND_APN:
                        // @offload will only handle service request and context release messgaes
                        break;

                    case Constants.SEND_UE_TEID:
                        // @offload will only handle service request and context release messgaes
                        break;

                    case Constants.DETACH_REQUEST:
                        // @offload will only handle service request and context release messgaes
                        break;

                    /************************************************* CONTEXT RELEASE ****************************************************/

                    case Constants.UE_CONTEXT_RELEASE_REQUEST:

                                byte [] b143 =Arrays.copyOfRange(p, 7, 11); //ue ip
                                byte [] b144 =Arrays.copyOfRange(p, 11, 17); //sep
                                byte [] b145 =Arrays.copyOfRange(p, 17, 21); //ue teid
                                byte [] b146 =Arrays.copyOfRange(p, 21, 27); //sep
                                byte [] b147 =Arrays.copyOfRange(p, 27, 31); //sgw teid
                                byte [] b148 =Arrays.copyOfRange(p, 31, 37); //sep
                                byte [] b149 =Arrays.copyOfRange(p, 37, 41); //ue num
                                
                                int ipv4add1 = IPv4.toIPv4Address(b143);
                                String ue_ipaddr1 = IPv4.fromIPv4Address(ipv4add1);
                                tmpArray[1]=ue_ipaddr1;

                                String sep142 = new String(b144, StandardCharsets.UTF_8); //6 byte
                                
                                int ue_teid14 = ByteBuffer.wrap(b145).getInt();
                                tmpArray[2] = Integer.toString(ue_teid14);
                                
                                String sep146 = new String(b146, StandardCharsets.UTF_8); //6 byte
                                
                                int sgw_teid14 = ByteBuffer.wrap(b147).getInt();
                                tmpArray[3] = Integer.toString(sgw_teid14);
                                
                                String sep148 = new String(b148, StandardCharsets.UTF_8); //6 byte
                                
                                int ue_num14 = ByteBuffer.wrap(b149).getInt();
                                tmpArray[4] = Integer.toString(ue_num14);

                                if(Constants.BITWISE_DEBUG){
                                    log.info("UE_CONTEXT_RELEASE_REQUEST");
                                    log.warn("ue_ipaddr ={}",ue_ipaddr1);
                                    log.warn("sep2 = {}" , sep142);
                                    log.warn("ue_teid = {}" , ue_teid14);
                                    log.warn("sep3 = {}" , sep146);
                                    log.warn("sgw_teid = {}" , sgw_teid14);
                                    log.warn("sep4 = {}" , sep148);
                                    log.warn("ue_num = {}" , ue_num14);
                                }

                        // @offload design : since the PACKET IN comes from SGW switch we call getSgwDpidFromIp
                        String dw_cr = Constants.getSgwDpidFromIp(DGW_IPAddr);  // dw_cr contains switches ID like "1", "2" etc
                        if(Constants.DEBUG){
                            log.info("Inside case UE_CONTEXT_RELEASE_REQUEST");
                            //tmpArray[1]==> UE IP  &  tmpArray[2] ==> UE TEID  &  tmpArray[3] ==> SGW TEID &  tmpArray[4] ==> UE_KEY
                            log.info("RECEIVED UE CONTEXT RELEASE REQUEST from UE with ip = {}, TEID= {}, corresponding SGW TEID = {}, UE KEY = {}" , tmpArray[1] ,tmpArray[2], tmpArray[3] , tmpArray[4]);
                            step = 7;
                            d1 = d2 = null;
                            d1 = new Date();
                        }

                        byte [] UE_IP1 = IPv4.toIPv4AddressBytes(tmpArray[1]);
                        // @offload design: since the request is received from SGW switch we need the DGW switch deviceID
                        DeviceId DGWswitchName3 = Constants.getDgwswitchName(dw_cr);

                        if(Constants.DEBUG){
                            log.info("UE IP as received from RAN = {}",tmpArray[1]);
                            log.info("Deleting ingress rule with deiveId = {}, UE_IPAddr = {}, sgw_teid = {},outPort = {}",deviceId,UE_IP1, Integer.parseInt(tmpArray[3]),outPort);
                            log.warn("DGWswitchName3 Device ID {}", DGWswitchName3);
                        }

                        /* UPLINK   => ipv4srcAddr = UE IP and ipv4dstAddr = Sink IP   */

                        /******************************** delete uplink flow rule on Ingress DGW( DGW -> SGW)********************************/
                        fr.insertUplinkTunnelIngressRule(true,appId,flowRuleService,DGWswitchName3,UE_IP1,Constants.dstSinkIpAddr,Integer.parseInt(tmpArray[3]),outPort);
                        if(Constants.DEBUG){
                            log.info("DEFAULT SWITCH deleting uplink rule with for UE with IP = {}",tmpArray[1]);
                        }

                        /***********************************delete downlink flow rule on Egress DGW( DGW -> RAN)*************************/
                        fr.insertUplinkTunnelForwardRule(true,appId, flowRuleService, DGWswitchName3,Integer.parseInt(tmpArray[2]), uePort,0,true);
                        if(Constants.DEBUG){
                            log.info("DEFAULT SWITCH deleting downlink rule with for UE with IP = {} and UE TEID = {}",tmpArray[1],tmpArray[2]);
                        }

                        // dpids[0] ==> SGW DPID   & dpids[1]==> PGW DPID

                        /*****************************delete downlink flow rule on Transit SGW( SGW -> PGW)**************************************************/
                        sgw.releaseAccessBearersRequest(appId,flowRuleService,deviceId, dw_cr, Integer.parseInt(tmpArray[3]), tmpArray[1]);

                        // FT.put(Integer.parseInt(Constants.UE_CONTEXT_RELEASE_REQUEST),dw_cr, "ue_state", tmpArray[4], "0");
                        // @offload design : populate the uekey_uestate map on SGW with 0 instead of map.

                        // @ft : since it is backup switch we only populate ue state tables
                        fr.populate_uekey_uestate_map(appId,flowRuleService,deviceId,Integer.parseInt(tmpArray[4]),0);

                        if(Constants.offload_with_clone){
                            // @offload design : since SGW has already replied to RAN by cloning packet no need to reply to RAN from local ONOS
                        }
                        else{
                                response = new StringBuilder();
                                response.append(Constants.UE_CONTEXT_RELEASE_COMMAND).append(Constants.SEPARATOR).append("");
                                build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
                                response = null;
                        } 
                        
                        if(Constants.DEBUG)
                            d2 = new Date();
                        break;

                    /**********************************  UE_INITIATED SERVICE REQUEST ***************************************/

                    case Constants.UE_SERVICE_REQUEST:

                                        byte [] b173 =Arrays.copyOfRange(p, 7, 11); //ue num
                                        byte [] b174 =Arrays.copyOfRange(p, 11, 17); //sep
                                        byte [] b175 =Arrays.copyOfRange(p, 17, 21); //ksi asme
                                        byte [] b176 =Arrays.copyOfRange(p, 21, 27); //sep
                                        byte [] b177 =Arrays.copyOfRange(p, 27, 31); //ue ip
                                        byte [] b178 =Arrays.copyOfRange(p, 31, 37); //sep
                                        byte [] b179 =Arrays.copyOfRange(p, 37, 41); //sgw teid
                                        
                                        int ue_num17 = ByteBuffer.wrap(b173).getInt();
                                        tmpArray[1] = Integer.toString(ue_num17);
                                        
                                        String sep172 = new String(b174, StandardCharsets.UTF_8); //6 byte
                                        
                                        int ksi_asme17 = ByteBuffer.wrap(b175).getInt();
                                        tmpArray[2] = Integer.toString(ksi_asme17);
                                        
                                        String sep176 = new String(b176, StandardCharsets.UTF_8); //6 byte
                                        
                                        int ipv4add2 = IPv4.toIPv4Address(b177);
                                        String ue_ipaddr2 = IPv4.fromIPv4Address(ipv4add2);
                                        tmpArray[3]=ue_ipaddr2;

                                        String sep178 = new String(b178, StandardCharsets.UTF_8); //6 byte

                                        int sgw_teid17 = ByteBuffer.wrap(b179).getInt();
                                        tmpArray[4] = Integer.toString(sgw_teid17);

                                        if(Constants.BITWISE_DEBUG){
                                            log.info("UE_SERVICE_REQUEST");
                                            log.warn("UE_KEY ={}",tmpArray[1]);
                                            log.warn("sep1 = {}" , sep172);
                                            log.warn("KSI_ASME = {}",tmpArray[2]);
                                            log.warn("sep2 = {}" , sep176);
                                            log.warn("UE_IP = {}" , ue_ipaddr2);
                                            log.warn("sep3 = {}" , sep178);
                                            log.warn("SGW_TEID = {}" , tmpArray[4]);

                                        }

                        String dw_ue_ser = Constants.getSgwDpidFromIp(DGW_IPAddr);  // dw_ue_ser contains switches ID like "1", "2" etc

                        if(Constants.DEBUG){
                            log.info("Inside case UE_SERVICE_REQUEST");
                            step = 9;
                            d1 = d2 = null;
                            d1 = new Date();
                        }
                        //tmpArray[1]==> UE_KEY  &  tmpArray[2] ==> KSI_ASME & tmpArray[3] ==> UE_IP
                        if(Constants.DEBUG){
                            log.info("RECEIVED UE_SERVICE_REQUEST from UE with key = {} KSI_ASME = {}", tmpArray[1], tmpArray[2]);
                        }
                        if(Constants.DO_ENCRYPTION){
                            decArray = receiveDecryptedArray(tmpArray);
                        }
                        String sgw_dpId = Constants.getSgwDpid(dw_ue_ser);
                        String ue_ip = tmpArray[3];

                        // @offload design :  we will get sgw_teid from switch uekey_sgwteid table which is the last param of the received equest as appended by SGW switch

                        sgw_teid = Integer.parseInt(tmpArray[4]);

                        //install uplink rule on default switch
                        DeviceId DGWswitchName4 = Constants.getDgwswitchName(dw_ue_ser);

                        if(Constants.DEBUG){
                                log.warn("DGWswitchName4 Device ID {}", DGWswitchName4);
                        }
                        // @offload design : hardcoding here value as 2 as all switches are conncected linearly
                        int outPort1 = Constants.SGW_to_PGW_Port;

                        byte[] UE_IPAddr1 = IPv4.toIPv4AddressBytes(tmpArray[3]);

                        // deviceId is SGW switch name
                        // install flow rules by matching on UE_IP

                        /**************************** Uplink flow rules here (DGW to SGW) on DGW switch ***************************/

                        /* UPLINK   => ipv4srcAddr = UE IP and ipv4dstAddr = Sink IP   */
                        fr.insertUplinkTunnelIngressRule(false,appId,flowRuleService,DGWswitchName4,UE_IPAddr1,Constants.dstSinkIpAddr, sgw_teid,outPort1);

                        if(Constants.DO_ENCRYPTION){
                            decArray = receiveDecryptedArray(tmpArray);
                        }

                        if(Constants.offload_with_clone){
                            // @offload design : since SFW has already replied to RAN by cloning packet no need to reply to RAN from local ONOS 
                        }
                        else{
                            response = new StringBuilder();
                            response.append(Constants.INITIAL_CONTEXT_SETUP_REQUEST).append(Constants.SEPARATOR).append(sgw_teid);
                            build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
                            response = null;
                        }

                        if(Constants.DEBUG)
                            d2 = new Date();
                        break;

                    case Constants.INITIAL_CONTEXT_SETUP_RESPONSE:

                                    byte [] b193 =Arrays.copyOfRange(p, 7, 11); //ue teid
                                    byte [] b194 =Arrays.copyOfRange(p, 11, 17); //sep
                                    byte [] b195 =Arrays.copyOfRange(p, 17, 21); //ue key
                                    byte [] b196 =Arrays.copyOfRange(p, 21, 27); //sep
                                    byte [] b197 =Arrays.copyOfRange(p, 27, 31); //ue ip
                                    byte [] b198 =Arrays.copyOfRange(p, 31, 37); //sep
                                    byte [] b199 =Arrays.copyOfRange(p, 37, 41); //sgw teid
                                    
                                    int ue_teid19 = ByteBuffer.wrap(b193).getInt();
                                    tmpArray[1]=Integer.toString(ue_teid19);
                                    
                                    String sep192 = new String(b194, StandardCharsets.UTF_8); //6 byte
                                    
                                    int ue_key19 = ByteBuffer.wrap(b195).getInt();
                                    tmpArray[2]=Integer.toString(ue_key19);
                                    
                                    String sep193 = new String(b196, StandardCharsets.UTF_8); //6 byte
                                    
                                    int ipv4add3 = IPv4.toIPv4Address(b197);
                                    String ue_ipaddr3 = IPv4.fromIPv4Address(ipv4add3);
                                    tmpArray[3]=ue_ipaddr3;

                                    String sep198 = new String(b198, StandardCharsets.UTF_8); //6 byte

                                    int sgw_teid171 = ByteBuffer.wrap(b199).getInt();
                                    tmpArray[4] = Integer.toString(sgw_teid171);

                                    if(Constants.BITWISE_DEBUG){
                                        log.info("INITIAL_CONTEXT_SETUP_RESPONSE");
                                        log.warn("ue_teId ={}",tmpArray[1]);
                                        log.warn("sep1 = {}" , sep192);
                                        log.warn("key = {}" ,tmpArray[2]);
                                        log.warn("sep2 = {}" , sep193);
                                        log.warn("UE_IP = {}" , tmpArray[3]);
                                        log.warn("sep3 = {}" , sep198);
                                        log.warn("SGW_TEID = {}" , tmpArray[4]);
                                    }

                        String dw_c_resp = Constants.getSgwDpidFromIp(DGW_IPAddr);
                        if(Constants.DEBUG){
                            log.info("Inside case INITIAL_CONTEXT_SETUP_RESPONSE");
                            step = 10;
                            d1 = d2 = null;
                            d1 = new Date();
                        }
                        if(Constants.DO_ENCRYPTION){
                            decArray = receiveDecryptedArray(tmpArray);
                        }

                        //tmpArray[1] => ue_teId, tmpArray[2] => ue key & tmpArray[3] => ue ip
                        if(Constants.DEBUG){
                            log.info("received teid = {}",tmpArray[1]);
                        }

                        // @offload design :  we will get sgw_teid from switch uekey_sgwteid table 
                        sgw_teid = Integer.parseInt(tmpArray[4]);

                        /******************************** Downlink flow rules on SGW (SGW to DGW) **************************************/
                        sgw.modifyBearerRequest(appId,flowRuleService, deviceId,dw_c_resp, dw_c_resp, sgw_teid, Integer.parseInt(tmpArray[1]), tmpArray[2]);

                        ue_ip = tmpArray[3];


                        /**************************** Downlink flow rules on DGW (DGW -> RAN) ***************************/
                        DeviceId DGWswitchName5 = Constants.getDgwswitchName(dw_c_resp);

                        fr.insertUplinkTunnelForwardRule(false,appId, flowRuleService,DGWswitchName5,Integer.parseInt(tmpArray[1]), uePort,0,true);

                        //NOT USED uekey_guti_map, not considered

                        // @offload design : no need to store as we are not using it

                        // uekey_guti_map.put(tmpArray[2], (Integer.parseInt(tmpArray[2])+1000)+"");


                        // @offload design : populate the uekey_uestate table on SGW with 1 instead of map.
                        // FT.put(Integer.parseInt(Constants.INITIAL_CONTEXT_SETUP_RESPONSE),dw_c_resp, "ue_state", tmpArray[2], "1");
                        
                        // @ft : we populate both GTP forwaring tables and offload state tables on SGWs
                        fr.populate_uekey_uestate_map(appId,flowRuleService,deviceId,Integer.parseInt(tmpArray[2]),1);

                        if(Constants.DO_ENCRYPTION){
                            decArray = receiveDecryptedArray(tmpArray);
                        }

                        if(Constants.offload_with_clone){
                                // @offload design : since SFW has already replied to RAN by cloning packet no need to reply to RAN from local ONOS 
                        }
                        else{
                            response = new StringBuilder();
                            response.append(Constants.ATTACH_ACCEPT).append(Constants.SEPARATOR).append(tmpArray[2]);
                            build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
                            response = null;
                        }

                        if(Constants.DEBUG)
                            d2 = new Date();
                        break;


                    default:
                        if(Constants.DEBUG){
                           log.info("Inside case default");
                            step = 11;
                            d1 = d2 = null;
                            d1 = new Date();
                        }

                        if(tmpArray.length == 3){
                                        byte [] b203 =Arrays.copyOfRange(p, 7, 27); //enc hash
                                        byte [] b204 = Arrays.copyOfRange(p, 27, 33); //sep2
                                        byte [] b205 =Arrays.copyOfRange(p, 33, 37); //imsi
                                        
                                        String enc_hash = new String(b203, StandardCharsets.UTF_8); //6 byte
                                        
                                        String sep202 = new String(b204, StandardCharsets.UTF_8); //6 byte
                                        
                                        int imsi205 = ByteBuffer.wrap(b205).getInt();

                                        if(Constants.BITWISE_DEBUG){
                                            log.info("NAS STEP TWO");
                                            log.warn("enc_hash = {}" , enc_hash);
                                            log.warn("sep2 = {}" , sep202);
                                            log.warn("imsi = {}" , imsi205);
                                        }
                    
                            if(Constants.DEBUG){
                                log.warn("NAS STEP TWO: arr length = {}", arr.length);
                                log.warn(" Received encrypted text = {}", enc_hash);
                                // log.warn(" NAS-MAC = {}", tmpArray[1] );
                                log.warn( " IMSI = {}", imsi205);
                                log.warn("Encrypted length={}",  enc_hash.length());
                                // log.warn(" NAS-MAC length{}=" , tmpArray[1].length());
                                log.warn( " IMSI length={}",Integer.toString(imsi205).length());
                            }
                            if(!Constants.CHECK_INTEGRITY){
                                d2 = new Date();
                                break;
                            }

                            NAS_Keys = uekey_nas_keys_map.get(Integer.toString(imsi205));
                            NAS_MAC = Utils.hmacDigest(enc_hash, NAS_Keys[1]);
                            if(Constants.DEBUG){
                               log.warn("NAS_STEP_TWO: Generated NAS MAC= {}" , NAS_MAC);
                            }
                        }
                        else{
                            log.warn("ERROR: NAS STEP TWO: unknown command. Array length = {}" , tmpArray.length);
                            log.warn(" Received: {}" , payload);
                            //System.exit(1);
                        }
                        d2 = new Date();
                }
                if(Constants.DEBUG)
                    timeDiff(d1, d2, step);
            }


        }

        // Used for measuring execution time of procedures; uncomment it if needed for debugging purpose
        private void timeDiff(Date d1, Date d2, int step){
	
        }
        @SuppressWarnings("unused")
        private String getStepName(int step){
            switch(step){
                case 1: return "AUTHENTICATION_STEP_ONE: ";
                case 2: return "AUTHENTICATION_STEP_THREE: ";
                case 3: return "SEND_APN: ";
                case 4: return "SEND_UE_TEID: ";
                case 5: return "DETACH_REQUEST: ";
                case 6: return "REQUEST_STARTING_IP: ";
                case 7: return "UE_CONTEXT_RELEASE_REQUEST: ";
                case 8: return "UE_CONTEXT_RELEASE_COMPLETE";
                case 9: return "UE_SERVICE_REQUEST: ";
                case 10: return "TUNNEL_SETUP_ACCEPT: ";
                case 11: return "DEFAULT: ";
                case 12: return "HSS call: ";
                default: return "Invalid";
            }
        }

        private String[] receiveDecryptedArray(String tmpArray[]){
            //tmpArray[1] => Encrypted text, tmpArray[2] => HMAC, tmpArray[3] => IMSI
            Utils.hmacDigest(tmpArray[1], Constants.SAMPLE_ENC_KEY);
            String decText = "";
            Utils.aesEncrypt(tmpArray[1], Constants.SAMPLE_ENC_KEY);
            return decText.split(Constants.SEPARATOR);
        }

        private String[] KDF_NAS(String K_ASME, int NAS_integrity_algo_id, int NAS_cipher_algo_id){
            String NAS_keys[] = new String[2];	// NAS_keys[0]: Integrity key K_NAS_int, NAS_keys[1]: Encryption key K_NAS_enc
            /*long K_NAS_int = K_ASME * 2 + NAS_integrity_algo_id;
            long K_NAS_enc = K_ASME * 4 + NAS_cipher_algo_id;*/
            long K_NAS_int = 2 * 2 + NAS_integrity_algo_id;
            long K_NAS_enc = 2 * 4 + NAS_cipher_algo_id;
            NAS_keys[0] = K_NAS_int + "";
            NAS_keys[1] = K_NAS_enc + "";

            if(NAS_keys[1].length() > Constants.ENC_KEY_LENGTH){
                NAS_keys[1].substring(0, Constants.ENC_KEY_LENGTH);
            }
            else if(NAS_keys[1].length() < Constants.ENC_KEY_LENGTH){
                NAS_keys[1] += Constants.SAMPLE_ENC_KEY.substring(0, Constants.ENC_KEY_LENGTH - NAS_keys[1].length());
            }
            return NAS_keys;
        }

        private void build_response_pkt(ConnectPoint connectPoint,MacAddress srcMac,MacAddress dstMac,byte ipv4Protocol,int ipv4SourceAddress,int udp_dstport,int udp_srcport,String response){
            Data payload_data = new Data();
            payload_data.setData(response.toString().getBytes());
            UDP udp = new UDP();
            udp.setSourcePort(udp_dstport);
            udp.setDestinationPort(udp_srcport);
            udp.setPayload(payload_data);

            IPv4 ip_pkt = new IPv4();
            byte ttl = 64;
            ip_pkt.setDestinationAddress(ipv4SourceAddress);
            ip_pkt.setSourceAddress(Constants.CONTROLLER_IP);   // controller IP is hardcoded in Constants.java file
            ip_pkt.setProtocol(ipv4Protocol);   //assuming that pacet will always be UDP
            ip_pkt.setTtl(ttl);
            ip_pkt.setPayload(udp);


            if(Constants.DEBUG){
                log.warn("sending payload as = {}",response);
                log.warn("Sending IP header as  : {}",ip_pkt);
            }

            Ethernet ethernet = new Ethernet();
            ethernet.setEtherType(Ethernet.TYPE_IPV4)
                    .setDestinationMACAddress(srcMac)
                    .setSourceMACAddress(dstMac)
                    .setPayload(ip_pkt);


            TrafficTreatment treatment = DefaultTrafficTreatment.builder()
                    .setOutput(connectPoint.port())
                    .build();

            OutboundPacket outboundPacket =
                    new DefaultOutboundPacket(connectPoint.deviceId(), treatment,
                                              ByteBuffer.wrap(ethernet.serialize()));
            if(Constants.DEBUG) {
                log.debug("Processing outbound packet: {}", outboundPacket);
            }

            packetService.emit(outboundPacket);
        }

    }

    // Indicates whether this is a control packet, e.g. LLDP, BDDP
    private boolean isControlPacket(Ethernet eth) {
        short type = eth.getEtherType();
        return type == Ethernet.TYPE_LLDP || type == Ethernet.TYPE_BSN;
    }

       
}

