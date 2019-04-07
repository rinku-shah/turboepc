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

import org.onosproject.net.Device;
import org.onosproject.net.Port;
import org.onosproject.net.device.DeviceEvent;
import org.onosproject.net.device.DeviceListener;
import org.onosproject.net.device.DeviceService;
import org.onosproject.net.link.DefaultLinkDescription;
import org.onosproject.net.link.LinkDescription;
import org.onosproject.net.link.LinkEvent;
import org.onosproject.net.link.LinkListener;
import org.onosproject.net.link.LinkProvider;
import org.onosproject.net.link.LinkProviderRegistry;
import org.onosproject.net.link.LinkProviderService;
import org.onosproject.net.link.LinkService;
import org.onosproject.net.provider.AbstractProvider;
import org.onosproject.net.provider.ProviderId;

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
import java.util.Iterator;
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
//@Service(value = EpcApp.class)
public class EpcApp extends AbstractProvider implements LinkProvider{

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

    @Reference(cardinality = ReferenceCardinality.MANDATORY_UNARY)
	protected LinkProviderRegistry registry;

    @Reference(cardinality = ReferenceCardinality.MANDATORY_UNARY)
    protected DeviceService deviceService;

    @Reference(cardinality = ReferenceCardinality.MANDATORY_UNARY)
    protected LinkService linkService;

    private ReactivePacketProcessor processor = new ReactivePacketProcessor();

    private int counter = 0;

    private LinkProviderService providerService;
    private DeviceListener deviceListener = new InternalDeviceListener();
    private LinkListener linkListener = new InternalLinkListener();
    
    private int num_devices = 3;
	private boolean [] dev = new boolean[num_devices+1];
    DeviceId [] devIds = new DeviceId[num_devices+1];
    public EpcApp() {
        super(new ProviderId("epcapp", "org.onosproject.p4tutorial.epc"));
	}
    
    FR fr = new FR();
    FT ft = new FT();

    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------

    @Activate
    public void activate() {
        // Register app and event listeners.
        log.info("Starting EpcApp...");
        appId = coreService.registerApplication(APP_NAME);
        packetService.addProcessor(processor, PacketProcessor.director(2));
        deviceService.addListener(deviceListener);
	linkService.addListener(linkListener);
	providerService = registry.register(this);
        for (int i=1; i <=3; i++)
        {
        	devIds[i] = org.onosproject.net.DeviceId.deviceId("device:bmv2:s"+Integer.toString(i));
        	dev[i] = false;
        }
        requestIntercepts();
        log.info("STARTED EpcApp...", appId.id());
    }

    @Deactivate
    public void deactivate() {
        // Remove listeners and clean-up flow rules.
        log.info("Stopping...");
        deviceService.removeListener(deviceListener);
	linkService.removeListener(linkListener);
	registry.unregister(this);
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
        int epc_code = 12;
        int PORTMASK = 0xff;
        PiMatchFieldId epcCode = PiMatchFieldId.of("hdr.data.epc_traffic_code");
        PiCriterion match = PiCriterion.builder()
                .matchTernary(epcCode, epc_code,PORTMASK)
                .build();
        packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        epc_code = 1;
        match = PiCriterion.builder()
                .matchTernary(epcCode, epc_code,PORTMASK)
                .build();
        packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        epc_code = 3;
        match = PiCriterion.builder()
                .matchTernary(epcCode, epc_code,PORTMASK)
                .build();
        packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        epc_code = 20;
        match = PiCriterion.builder()
                .matchTernary(epcCode, epc_code,PORTMASK)
                .build();
        packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        epc_code = 5;
        match = PiCriterion.builder()
                .matchTernary(epcCode, epc_code,PORTMASK)
                .build();
        packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        epc_code = 7;
        match = PiCriterion.builder()
                .matchTernary(epcCode, epc_code,PORTMASK)
                .build();
        packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        epc_code = 9;
        match = PiCriterion.builder()
                .matchTernary(epcCode, epc_code,PORTMASK)
                .build();
        packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        // @FT_failover design : we will not request context release and service request packets as they will be handled at SGW and sent to local ONOS

        // epc_code = 14;
        // match = PiCriterion.builder()
        //         .matchTernary(epcCode, epc_code,PORTMASK)
        //         .build();
        // packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        // epc_code = 17;
        // match = PiCriterion.builder()
        //         .matchTernary(epcCode, epc_code,PORTMASK)
        //         .build();
        // packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);

        // epc_code = 19;
        // match = PiCriterion.builder()
        //         .matchTernary(epcCode, epc_code,PORTMASK)
        //         .build();
        // packetService.requestPackets(selector.matchPi(match).build(), PacketPriority.REACTIVE, appId);
        
        
    }
    /**
     * Cancel request for packet in via packet service.
     */
    private void withdrawIntercepts() {
        TrafficSelector.Builder selector = DefaultTrafficSelector.builder();
        selector.matchEthType(Ethernet.TYPE_IPV4);
        packetService.cancelPackets(selector.build(), PacketPriority.REACTIVE, appId);
    }

    // @FT_with_failover : code added 
    /***************************** FAILOVER CODE STARTS HERE **************************************************/

    private class InternalDeviceListener implements DeviceListener {
        @Override
        public void event(DeviceEvent event) {
            //log.warn("*********************************** ALERT we are in event fn of DeviceListner in EpcApp");
            DeviceId DGW_deviceId = Constants.DGW_Switch_Name;
            DeviceEvent.Type type = event.type();
	    //log.warn("**************************** event Type = {}",type.toString());
            Device device = event.subject();
            DeviceId devId = device.id();
            // log.warn("=========== Type : " + type.toString() + " " + device.toString() + " ============");
            if (type == DeviceEvent.Type.DEVICE_AVAILABILITY_CHANGED || type == DeviceEvent.Type.DEVICE_REMOVED) {
                // processDeviceLinks(device);
                log.warn("--------- Device removed -----------");
                for (int i=1;i<=3; i++) {
                	if (devId.equals(devIds[i])) {
                		if (dev[i] == true) {
                			log.info("***************** Device Removed : " + devId.toString() + " ******************");
                			dev[i] = false;
                			if (i==Constants.SGW_ID_1) {
                                // if the primary SGW goes down then we forward all packets(Context Release and Service Request) to backup SGW from DGW
                                // ue_context_rel_req
                                fr.populate_dgw_failover_table(appId,flowRuleService,DGW_deviceId,14,Constants.DGW_to_backup_SGW_port);
                                // ue_service_req
                                fr.populate_dgw_failover_table(appId,flowRuleService,DGW_deviceId,17,Constants.DGW_to_backup_SGW_port);
                                // initial_ctxt_setup_resp
                                fr.populate_dgw_failover_table(appId,flowRuleService,DGW_deviceId,19,Constants.DGW_to_backup_SGW_port);
                                
                                // @FT_with_failover : We need to change the Uplink GTP tunnel table on DGW as well 
                                // Match key : (UE_IPAddr, Constants.dstSinkIpAddr)
                                // Action fields : (sgw_teid, outPort)
                                // once primary goes down the outPort has to be changed to DGW_to_backup_SGW_port.
                                // For this we need to iterate over hashmaps "uekey_sgw_teid_map", "uekey_ueip_map"
                                Iterator<String> uekey_sgwteid_it = ft.uekey_sgw_teid_map.keySet().iterator();
                                // Iterator<String> uekey_ueip_it = ft.uekey_sgw_teid_map.keySet().iterator();
                                int outPort = Constants.DGW_to_backup_SGW_port;

                                while(uekey_sgwteid_it.hasNext()){
                                    String uekey = uekey_sgwteid_it.next();
				    log.warn("Moving uekey = {} to backup egress port",uekey);
                                    String sgwteid_value = ft.uekey_sgw_teid_map.get(uekey);
                                    String tmpArray2[] = sgwteid_value.split(Constants.SEPARATOR);
				    // tmpArray2[0] = sgw_dpId and tmpArray2[1] = sgw_teid
			            sgwteid_value =  tmpArray2[1]; // sgw_teid	
                                    String ueip = ft.uekey_ueip_map.get(uekey);
                                    byte[] UE_IPAddr = IPv4.toIPv4AddressBytes(ueip);
                                    /**************************** Uplink flow rules here (DGW to SGW) on DGW switch ***************************/
                                    fr.insertUplinkTunnelIngressRule(false, appId, flowRuleService, DGW_deviceId, UE_IPAddr, Constants.dstSinkIpAddr, Integer.parseInt(sgwteid_value), outPort);

                                }

			                    log.info("============== Switching over to secondary (backup SGW) ===============================");
                			}
                		}
                	}
                }

            }
            else if (type == DeviceEvent.Type.DEVICE_ADDED) {
                // processPortLinks(device, event.port());
                log.warn("------------- Device added -------------");
                for (int i=1;i<=3; i++) {
                	if (devId.equals(devIds[i])) {
                		dev[i] = true;
                		log.warn("***************** Device Added : " + devId.toString() + " **********************");
                		if (i==Constants.DEFAULT_SWITCH_ID_1) {
                                // populating DGW to forward all packets(Context Release and Service Request) to primary SGW
                                // ue_context_rel_req
                                fr.populate_dgw_failover_table(appId,flowRuleService,DGW_deviceId,14,Constants.DGW_to_primary_SGW_port);
                                // ue_service_req
                                fr.populate_dgw_failover_table(appId,flowRuleService,DGW_deviceId,17,Constants.DGW_to_primary_SGW_port);
                                // initial_ctxt_setup_resp
                		fr.populate_dgw_failover_table(appId,flowRuleService,DGW_deviceId,19,Constants.DGW_to_primary_SGW_port);
                            
			        log.warn("=============== Primary table entries pushed at DGW ======================");
                		}
                	}
                }

            }
        }
 	}

 	//Listens to link events and processes the link additions.
    private class InternalLinkListener implements LinkListener {
        @Override
        public void event(LinkEvent event) {
            if (event.type() == LinkEvent.Type.LINK_ADDED) {
                Link link = event.subject();
                if (link.providerId().scheme().equals("cfg")) {
                    // processLink(event.subject());
                }
            }
        }
    }
    
    /***************************** FAILOVER CODE ENDS HERE **************************************************/
    /**
     * Packet processor responsible for forwarding packets along their paths.
     */
    private class ReactivePacketProcessor implements PacketProcessor {

        private ConcurrentHashMap<String, String> imsi_xres_mapping = new ConcurrentHashMap<String, String>();
        private ConcurrentHashMap<String, String> uekey_guti_map = new ConcurrentHashMap<String, String>(); // Key: UE_Key, Value: GUTI
        private ConcurrentHashMap<String, String[]> uekey_nas_keys_map = new ConcurrentHashMap<String, String[]>();		// Key = IMSI, Value = [0]: K_ASME, [1]: NAS Integrity key, NAS Encryption key
        HSS hss = new HSS();
        SGW sgw = new SGW();

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
            int ue_state = 0;

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
                //log.warn("payload direct = {}",((Data)final_payload).getData());
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
                switch(Integer.toString(type)){
                    
                    case Constants.REQUEST_STARTING_IP:
                        if(Constants.DEBUG){
                            log.warn("Inside case REQUEST_STARTING_IP");
                            log.warn("Request Starting IP address from PGW via SGW");
                            step = 6;
                            d1 = d2 = null;
                            d1 = new Date();
                        }
                        String deviceID = (String)connectPoint.deviceId().toString();  //hardcoding
                        String sw[]= deviceID.split(":");
                        String swName = sw[2];

                        /***************get starting UE IP  **************************************/

                        String ip = sgw.getStartingIPAddress(swName);

                        response = new StringBuilder();
                        response.append(Constants.SEND_STARTING_IP).append(Constants.SEPARATOR).append(ip);

                        if(Constants.DEBUG){
                            log.warn("Starting IP= {}",ip);
                            log.warn("Response to send = {}",response);
                        }

                        build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());

                        response = null;
                        if(Constants.DEBUG)
                            d2 = new Date();
                        break;

                    case Constants.AUTHENTICATION_STEP_ONE:
                        if(Constants.DEBUG){
                            log.info("Inside case AUTHENTICATION_STEP_ONE");
                            step = 1;
                            d1 = d2 = null;
                            d1 = new Date();
                        }

                        /************************* Validating user in HSS*********************************/
                            byte [] b3 =Arrays.copyOfRange(p, 7, 11); //imsi
                            byte [] b4 = Arrays.copyOfRange(p, 11, 17); //sep2
                            byte [] b5 = Arrays.copyOfRange(p, 17, 18); //ue_nw_cap
                            byte [] b6 =Arrays.copyOfRange(p, 18, 24); //sep3
                            byte [] b7 = Arrays.copyOfRange(p, 24, 56); //ksi_asme //32 byte
                            byte [] b8 = Arrays.copyOfRange(p, 56, 62); //sep4
                            byte [] b9 = Arrays.copyOfRange(p, 62, 66); //sqn
                            byte [] b10 = Arrays.copyOfRange(p, 66, 72); //sep5
                            byte [] b11 = Arrays.copyOfRange(p, 72, 80); //tai
        
                            /*byte code = ByteBuffer.wrap(b1).get();
                            System.out.println("code = " + code);*/

        
                            int imsi1 = ByteBuffer.wrap(b3).getInt();
                            imsi = Integer.toString(imsi1);
        
                            String sep2 = new String(b4, StandardCharsets.UTF_8); //6 byte
        
                            ue_nw_capability = ByteBuffer.wrap(b5).get();
        
                            String sep3 = new String(b6, StandardCharsets.UTF_8); //6 byte
        
                            int ksi_asme = ByteBuffer.wrap(b7).getInt();
                            KSI_ASME = Integer.toString(ksi_asme);
        
                            String sep4 = new String(b8, StandardCharsets.UTF_8); //6 byte
        
                            int sqn = ByteBuffer.wrap(b9).getInt();
                            SQN = Integer.toString(sqn);
        
                            String sep5 = new String(b10, StandardCharsets.UTF_8); //6 byte
        
                            Long tai1 = ByteBuffer.wrap(b11).getLong();
                            tai = Long.toString(tai1);

                            if(Constants.BITWISE_DEBUG){
                            log.info("Inside case AUTHENTICATION_STEP_ONE");
                                log.warn("imsi = {}" , imsi1);
                                log.warn("sep2 = {}" , sep2);
                                log.warn("ue_nw_cap = {}" , ue_nw_capability);
                                log.warn("sep3 = {}" , sep3);
                                log.warn("ksi_asme = {}", ksi_asme);
                                log.warn("sep4 = {}" ,sep4);
                                log.warn("sqn = {}" , sqn);
                                log.warn("sep5 = {}", sep5);
                                log.warn("tai = {}" , tai1);
                            }
        
                        // imsi = tmpArray[1];
                        // ue_nw_capability = tmpArray[2];
                        // KSI_ASME = tmpArray[3];
                        // SQN = tmpArray[4];	// UE sequence number
                        // tai = tmpArray[5];	// Tracking area ID
                        Date d3 = new Date();

                        int[][][] roundKeys= new int[11][4][4];
                        auc_vector_t av = hss.validateUser(imsi, Constants.SN_ID, Constants.NW_TYPE, SQN, tai, roundKeys);
                        if(Constants.DEBUG){
                            Date d4 = new Date();
                            timeDiff(d3, d4, 11);
                        }
                       
                            if(Constants.DEBUG){
                                log.warn("INITIAL imsi= {} and  msisdn= {}",imsi,ue_nw_capability);
                            }
                            //////////////////////////////////////EDIT//////////////////
                            StringBuilder xresS = new StringBuilder();
                            StringBuilder K_ASMES = new StringBuilder();
                            for(int k=0; k<8; k++){
                                if(k!=7)
                                    xresS.append(av.xres[k]);//.append(Constants.INTSEPARATOR);
                                else 
                                    xresS.append(av.xres[k]);
                            }
                            for(int k=0; k<32; k++){
                                if(k!=31)
                                    K_ASMES.append(av.kasme[k]);//.append(Constants.INTSEPARATOR);
                                else 
                                    K_ASMES.append(av.kasme[k]);
                            }
                            imsi_xres_mapping.put(imsi, xresS.toString());
                            uekey_nas_keys_map.put(imsi, new String[]{K_ASMES.toString(), "", ""});
                            //////////////////////////////////////EDIT//////////////////
                            KSI_ASME = "1";
                            response = new StringBuilder();
                          
                            StringBuilder randS = new StringBuilder();
                            for(int j=0; j<16;j++){
                                if(j !=15){
                                    randS.append(av.rand[j]).append(Constants.INTSEPARATOR);
                                }else{
                                    randS.append(av.rand[j]);
                                }
                            }
                            //System.out.println("randS= "+ randS);
                            StringBuilder autnS = new StringBuilder();
                            for(int j=0; j<16;j++){
                                if(j !=15){
                                    autnS.append(av.autn[j]).append(Constants.INTSEPARATOR);
                                }else{
                                    autnS.append(av.autn[j]);
                                }
                            }
                           
                            response.append(Constants.AUTHENTICATION_STEP_TWO).append(Constants.SEPARATOR).append(randS).append(Constants.SEPARATOR);
                            response.append(autnS);
                            response.append(Constants.SEPARATOR).append(KSI_ASME); //K_ASME
                            
                            if(Constants.DEBUG){
                                System.out.println(response.toString());
                            }
                           
                            build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
                            response = null;
                       
                        if(Constants.DEBUG)
                            d2 = new Date();
                        break;


                    case Constants.AUTHENTICATION_STEP_THREE:
                        if(Constants.DEBUG){
                            log.info("Inside case AUTHENTICATION_STEP_THREE");
                            step = 2;
                            d1 = d2 = null;
                            d1 = new Date();
                        }
                                byte [] b33 =Arrays.copyOfRange(p, 7, 11); //imsi
                                byte [] b34 = Arrays.copyOfRange(p, 11, 17); //sep2
                                byte [] b35 = Arrays.copyOfRange(p, 17, 25); //res
                                
                                int imsi3 = ByteBuffer.wrap(b33).getInt();
                                imsi = Integer.toString(imsi3);
                                
                                String sep32 = new String(b34, StandardCharsets.UTF_8); //6 byte
                                
                                int[] res1 = new int[8];
                                for(int i=0; i<8; i++){
                                    res1[i] = b35[i] & 0xFF;
                                }
                                
                                StringBuilder resS = new StringBuilder();
                                for(int k=0; k<8; k++){
                                    if(k!=7)
                                        resS.append(res1[k]);
                                    else 
                                        resS.append(res1[k]);
                                }
                                res = resS.toString();
                                if(Constants.BITWISE_DEBUG){
                                    log.info("Inside case AUTHENTICATION_STEP_THREE");
                                    log.warn("imsi = {}" , imsi3);
                                    log.warn("sep2 = {}" , sep32);
                                    log.warn("RES string: {}" , resS);
                                }

                        // imsi = tmpArray[1];
                        // res = tmpArray[2];	// RES from UE
                        if(Constants.DEBUG){
                            log.warn("imsi = {}",imsi);
                            log.warn(" res = {}",res);
                        }
                        if(imsi_xres_mapping.containsKey(imsi)){
							String k;
                            if(imsi_xres_mapping.get(imsi).equals(res)){ // UE Authentication (RES == XRES)    
                                imsi_xres_mapping.remove(imsi);
                                /*****************UE is authenticated ****************/
                                KSI_ASME = "1";
                                int replayed_nw_capability = Utils.randInt(0, 10);		// Replayed UE Network Capability decided by MME
                                int NAS_integrity_algo_id = Constants.CIPHER_ALGO_MAP.get("HmacSHA1");
                                int NAS_cipher_algo_id = Constants.CIPHER_ALGO_MAP.get("AES");
                                if(uekey_nas_keys_map.containsKey(imsi)){
                                    K_ASME = uekey_nas_keys_map.get(imsi)[0];
                                }
                                else{
                                    log.info("AUTHENTICATION_STEP_THREE: imsi not found");
                                    System.exit(1);
                                }
                                // K_ASME = uekey_nas_keys_map.get(imsi)[0];
								k = uekey_nas_keys_map.get(imsi)[0];

                                String NAS_keys[] = KDF_NAS(k, NAS_integrity_algo_id, NAS_cipher_algo_id);		// NAS_keys[0]: Integrity key K_NAS_int, NAS_keys[1]: Encryption key K_NAS_enc

                                if(Constants.DEBUG){
                                    log.warn("AUTHENTICATION_STEP_THREE: INT_KEY= {}", NAS_keys[0]);
                                    log.warn(" ENC_KEY = {}", NAS_keys[1]);
                                }
								uekey_nas_keys_map.put(imsi, new String[]{k, NAS_keys[0], NAS_keys[1]});

                                response = new StringBuilder();
                                response.append(Constants.NAS_STEP_ONE).append(Constants.SEPARATOR).append(KSI_ASME).append(Constants.SEPARATOR).append(replayed_nw_capability).append(Constants.SEPARATOR).append(NAS_cipher_algo_id).append(Constants.SEPARATOR).append(NAS_integrity_algo_id);

                                NAS_MAC = Utils.hmacDigest(response.toString(), NAS_keys[0] + "");	// Generate Message Authentication Code using the hash function
                                if(Constants.DEBUG){
                                    log.warn("AUTHENTICATION_STEP_THREE: Generated NAS MAC= {}", NAS_MAC);
                                }
                                response.append(Constants.SEPARATOR).append(NAS_MAC);
                                build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
                                response = null;
                            }else{
                                log.info(imsi_xres_mapping.get(imsi).equals(res) +" ### "+ imsi_xres_mapping.get(imsi) +" ue_res= "+ res+" ****imsi "+ imsi);
                                response = new StringBuilder();
                                response.append(Constants.NAS_STEP_ONE).append(Constants.SEPARATOR).append("1").append(Constants.SEPARATOR).append("1").append(Constants.SEPARATOR).append("1").append(Constants.SEPARATOR).append("1");

                                NAS_MAC = Utils.hmacDigest(response.toString(), "1234" + "");	// Generate Message Authentication Code using the hash function
                                if(Constants.DEBUG){
                                    log.warn("AUTHENTICATION_STEP_THREE: Generated NAS MAC= {}", NAS_MAC);
                                }
                                response.append(Constants.SEPARATOR).append(NAS_MAC);
                                if(Constants.DEBUG){
                                    log.warn(response.toString());
                                }
                                build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,Constants.AUTHENTICATION_FAILURE);
								response = null;
                                System.exit(1);
                            }
                        }else{
                            log.info("AUTHENTICATION_STEP_THREE failure");
                            build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,Constants.AUTHENTICATION_FAILURE);

                            System.exit(1);
                        }
                        if(Constants.DEBUG)
                            d2 = new Date();
                        break;

                    case Constants.SEND_APN:

                                    byte [] b53 =Arrays.copyOfRange(p, 7, 15); //apn
                                    byte [] b54 = Arrays.copyOfRange(p, 15, 21); //sep2
                                    byte [] b55 =Arrays.copyOfRange(p, 21, 25); //ue_key

                                    Long apn = ByteBuffer.wrap(b53).getLong();
                                    
                                    String sep52 = new String(b54, StandardCharsets.UTF_8); //6 byte
                                    
                                    int ue_key = ByteBuffer.wrap(b55).getInt();
                                    if(Constants.BITWISE_DEBUG){
                                        log.info("insisde SEND_APN");
                                        log.warn("imsi = {}" , apn);
                                        log.warn("sep2 = {}" , sep52);
                                        log.warn("ue_key = {}" , ue_key);
                                    }
                                    tmpArray[1] = Long.toString(apn);
                                    tmpArray[2] = Integer.toString(ue_key);
					
                        String dgw_dpId = (String)connectPoint.deviceId().toString();  //hardcoding  Device ID format = device:bmv2:s1
                        String array1[]= dgw_dpId.split(":");  //parsing the connectpoint to get switch ID

                        dgw_dpId = array1[2];  // contains switch names like "s10","s1" 

                        if(Constants.DEBUG){
                            log.info("Inside case SEND_APN");
                            log.warn("array1[2] = {}",array1[2]); //hardcoding  array1[2] contains switches  like "s1", "s2" etc
                            log.warn("dgw_dpId = {}",dgw_dpId); //hardcoding  array1[2] contains switches  like "s1", "s2" etc
                            step = 3;
                            d1 = d2 = null;
                            d1 = new Date();
                        }
                        if(Constants.DO_ENCRYPTION){
                            decArray = receiveDecryptedArray(tmpArray);
                        }

                        //tmpArray[1] => ue apn and tmpArray[2] => ue key
                        if(Constants.DEBUG){
                            log.warn("received apn={}",tmpArray[1]);
                        }
                        // storing src port of udp packet to identify the specific UE, when MME wants to initiate connection with this UE.
                        // @Offload design map not needed

                        // FT.put(Integer.parseInt(Constants.SEND_APN),dgw_dpId, "uekey_udp_src_port_map", tmpArray[2], Integer.toString(udp_srcport));

                        String pgw_dpId = hss.getPGateway(tmpArray[1]);  // returns 4 for all apn
                        /********************* defaultSwitch is DGW ******************************/
                        String sgw_dpId = Constants.getSgwDpid(dgw_dpId);
                        DeviceId sgwswitchName = Constants.getSgwswitchName(dgw_dpId);
                        /*******************install uplink rules on SGW and PGW in this method********************/
                        String ip_sgw;
                        ip_sgw = sgw.contactPGW(appId,flowRuleService,sgwswitchName,sgw_dpId, pgw_dpId, tmpArray[1]); //tmpArray[1] => apn of UE
                       
                        response = new StringBuilder();
                        response.append(Constants.SEND_IP_SGW_TEID).append(Constants.SEPARATOR).append(ip_sgw).append(Constants.SEPARATOR).append("1").append(Constants.SEPARATOR);

                        if(Constants.DO_ENCRYPTION){
                            Utils.aesEncrypt(response.toString(), Constants.SAMPLE_ENC_KEY);
                            Utils.hmacDigest(response.toString(), Constants.SAMPLE_ENC_KEY);
                        }

                        tmpArray2 = ip_sgw.split(Constants.SEPARATOR);
                        sgw_teid = Integer.parseInt(tmpArray2[1]);

                        /**************************** Uplink flow rules here (DGW to SGW) on DGW switch ***************************/
                        int SGW_ID =  Integer.parseInt(Constants.getSgwDpid(dgw_dpId));
                        String getval = dgw_dpId.split("s")[1] + Constants.SEPARATOR + SGW_ID;
                        outPort =  Constants.ENODEB_SGW_PORT_MAP.get(getval);
                        byte[] UE_IPAddr = IPv4.toIPv4AddressBytes(tmpArray2[0]);
                        if(Constants.DEBUG){
                            log.info("#####################################");
                            log.warn("dgw_dpid = {}",dgw_dpId);
                            log.warn("SGW_ID = {}",SGW_ID);
                            log.warn("getval = {}",getval);
                            log.info("outPort  ############=  {}",outPort);
                            log.info("UE_IPAddr = {}",UE_IPAddr);
                        }
                        // deviceId is DGW switch name
                        // install flow rules by matching on UE_IP
                        
                        /* UPLINK   => ipv4srcAddr = UE IP and ipv4dstAddr = Sink IP  */
                        fr.insertUplinkTunnelIngressRule(false, appId, flowRuleService, deviceId, UE_IPAddr, Constants.dstSinkIpAddr, sgw_teid, outPort);

                         // key: tmpArray[2] => UE Key, Value: tmpArray2[0] => UE IP
                        FT.put(Integer.parseInt(Constants.SEND_APN),dgw_dpId, "uekey_ueip_map", tmpArray[2], tmpArray2[0]); // key: tmpArray[2] => UE Key, Value: tmpArray2[0] => UE IP

                        //MAP key = UE KEY,  MAP value = SGW_DPID + SEPARATOR + SGW_TEID
                        // @Offload design push sgw_teid to switch table so no need to update in map
                        FT.put(Integer.parseInt(Constants.SEND_APN),dgw_dpId, "uekey_sgw_teid_map", tmpArray[2], Constants.getSgwDpid(dgw_dpId) + Constants.SEPARATOR + tmpArray2[1]);
                        

                        FT.put(Integer.parseInt(Constants.SEND_APN),dgw_dpId, "sgw_teid_uekey_map", tmpArray2[1], tmpArray[2]);

                        // @Offload design push sgw_teid to switch table
                        // populates this map on SGW switch
                        DeviceId offload_SGWswitchName1 = Constants.getSgwswitchName(dgw_dpId);
                        // populate rules on primary sgw switch 
                        fr.populate_uekey_sgwteid_map(false,appId,flowRuleService,offload_SGWswitchName1,Integer.parseInt(tmpArray[2]),sgw_teid);

                        //@ft : get secondary SGW id
                        DeviceId offload_BackupSGWswitchName1 = Constants.getBackupSgwswitchName(dgw_dpId);
                        // populate rules on backup sgw switch 
                        fr.populate_uekey_sgwteid_map(false,appId,flowRuleService,offload_BackupSGWswitchName1,Integer.parseInt(tmpArray[2]),sgw_teid);

                        build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
                        response = null;
                        if(Constants.DEBUG){
                            log.info("Send APN done");
                            d2 = new Date();
                        }
                        break;

                    case Constants.SEND_UE_TEID:

                                    byte [] b73 =Arrays.copyOfRange(p, 7, 11); //ue_teid
                                    byte [] b74 = Arrays.copyOfRange(p, 11, 17); //sep2
                                    byte [] b75 =Arrays.copyOfRange(p, 17, 21); //ue_key
                                    
                                    int ue_teid = ByteBuffer.wrap(b73).getInt();
                                    
                                    String sep72 = new String(b74, StandardCharsets.UTF_8); //6 byte
                                    
                                    int ue_key7 = ByteBuffer.wrap(b75).getInt();
                                    if(Constants.BITWISE_DEBUG){
                                        log.info("SEND_UE_TEID");
                                        log.warn("ue_teid = {}" ,ue_teid);
                                        log.warn("sep2 = {}" , sep72);
                                        log.warn("imsi = {}" , ue_key7);
                                    }

                                    tmpArray[1] = Integer.toString(ue_teid);
                                    tmpArray[2] = Integer.toString(ue_key7);
					
                        String dgw_dpId1 = (String)connectPoint.deviceId().toString();  //hardcoding  Device ID format = device:bmv2:s1
                        String array5[]= dgw_dpId1.split(":");  //parsing the connectpoint to get switch ID
                        dgw_dpId1 = array5[2];

                        String send_ue_teid_dgw = Constants.getDgwDpidFromIp(DGW_IPAddr);  // send_ue_teid_dgw contains switches ID like "1", "2" etc

                        if(Constants.DEBUG){
                            log.info("Inside case SEND_UE_TEID");
                            log.warn("send_ue_teid_dgw = {}",send_ue_teid_dgw); // send_ue_teid_dgw contains switches ID like "1", "2" etc
                            step = 4;
                            d1 = d2 = null;
                            d1 = new Date();
                        }
                        if(Constants.DO_ENCRYPTION){
                            decArray = receiveDecryptedArray(tmpArray);
                        }

                        //MAP key = UE KEY,  MAP value = SGW_DPID + SEPARATOR + SGW_TEID
                        String tmp = FT.get(send_ue_teid_dgw, "uekey_sgw_teid_map", tmpArray[2]); // tmpArray[2] => ue key
                        //log.warn("tmp uekey_sgw_teid_map = {}",tmp);
                        tmpArray2 = tmp.split(Constants.SEPARATOR);

                        //tmpArray[1] => ue_teId and tmpArray[2] => ue key
                        //tmpArray2[0] => sgw_dpId  and tmpArray2[1] => sgw_teID
                        if(Constants.DEBUG){
                            log.info("inside SEND_UE_TEID");
                            log.warn("received ue_teid from RAN = {}",tmpArray[1]);
                            log.warn("sgw_dpId = {}",tmpArray2[0]);
                            log.warn("sgw_teId = {}",tmpArray2[1]);
                        }

                        DeviceId SGWswitchName1 = Constants.getSgwswitchName(dgw_dpId1);
                        sgw.modifyBearerRequest(appId, flowRuleService, SGWswitchName1, tmpArray2[0], tmpArray2[0], Integer.parseInt(tmpArray2[1]), Integer.parseInt(tmpArray[1]), tmpArray[2]);

                        String ue_ip = FT.get(send_ue_teid_dgw, "uekey_ueip_map", tmpArray[2]); // tmpArray[2] => ue key
                      
                        /**************************** Downlinkl flow rules on DGW (DGW -> RAN) ***************************/
                        fr.insertUplinkTunnelForwardRule(false,appId, flowRuleService, deviceId,Integer.parseInt(tmpArray[1]), uePort,0,true);

                        response = new StringBuilder();
                        //NOT USED LATER uekey_guti_map, so not considered in state calc
                        //@offload design  : commenting as not needed

                            // uekey_guti_map.put(tmpArray[2], (Integer.parseInt(tmpArray[2])+1000)+"");
                            // FT.put(Integer.parseInt(Constants.SEND_UE_TEID),send_ue_teid_dgw, "ue_state", tmpArray[2], "1");

                            //@offload design 
                        // populate all these rules on SGW switch only
                        DeviceId offload_SGWswitchName2 = Constants.getSgwswitchName(dgw_dpId1);
                        ue_state = 1;
                        fr.populate_uekey_uestate_map(false,appId,flowRuleService,offload_SGWswitchName2,Integer.parseInt(tmpArray[2]),ue_state);
                        fr.populate_uekey_guti_map(false,appId,flowRuleService,offload_SGWswitchName2,Integer.parseInt(tmpArray[2]),(Integer.parseInt(tmpArray[2])+1000));

                        // @ft : populate tables on backup SGW switch as well
                        DeviceId offload_BackupSGWswitchName2 = Constants.getBackupSgwswitchName(dgw_dpId1);
                        fr.populate_uekey_uestate_map(false,appId,flowRuleService,offload_BackupSGWswitchName2,Integer.parseInt(tmpArray[2]),ue_state);
                        fr.populate_uekey_guti_map(false,appId,flowRuleService,offload_BackupSGWswitchName2,Integer.parseInt(tmpArray[2]),(Integer.parseInt(tmpArray[2])+1000));

                        response.append(Constants.ATTACH_ACCEPT).append(Constants.SEPARATOR).append(Integer.parseInt(tmpArray[2])+1000);	// Sending GUTI

                        if(Constants.DO_ENCRYPTION){
                            decArray = receiveDecryptedArray(tmpArray);
                        }

                        build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());
                        response = null;
                        if(Constants.DEBUG)
                            d2 = new Date();

                        break;

                    case Constants.DETACH_REQUEST:
                                        byte [] b93 =Arrays.copyOfRange(p, 7, 11); //ue ip
                                        byte [] b94 =Arrays.copyOfRange(p, 11, 17); //sep
                                        byte [] b95 =Arrays.copyOfRange(p, 17, 21); //ue teid
                                        byte [] b96 =Arrays.copyOfRange(p, 21, 27); //sep
                                        byte [] b97 =Arrays.copyOfRange(p, 27, 31); //sgw teid
                                        byte [] b98 =Arrays.copyOfRange(p, 31, 37); //sep
                                        byte [] b99 =Arrays.copyOfRange(p, 37, 41); //ue num
                                        
                                        int ipv4add = IPv4.toIPv4Address(b93);
                                        String ue_ipaddr = IPv4.fromIPv4Address(ipv4add);
                                        
                                        String sep92 = new String(b94, StandardCharsets.UTF_8); //6 byte
                                        
                                        int ue_teid9 = ByteBuffer.wrap(b95).getInt();
                                        
                                        String sep96 = new String(b96, StandardCharsets.UTF_8); //6 byte
                                        
                                        int sgw_teid9 = ByteBuffer.wrap(b97).getInt();
                                        
                                        String sep98 = new String(b98, StandardCharsets.UTF_8); //6 byte
                                        
                                        int ue_key9 = ByteBuffer.wrap(b99).getInt();
                                        if(Constants.BITWISE_DEBUG){
                                            log.info("DETACH_REQUEST");
                                            log.warn("sep2 = {}" , sep92);
                                            log.warn("ue_teid = {}" , ue_teid9);
                                            log.warn("sep3 = {}" , sep96);
                                            log.warn("sgw_teid = {}" , sgw_teid9);
                                            log.warn("sep4 = {}" , sep98);
                                            log.warn("ue_key = {}" , ue_key9);
                                        }

                        //tmpArray[1] => UE IP, tmpArray[2] => UE TEID, tmpArray[3] => SGW TEID, tmpArray[4] => UE_KEY
                        tmpArray[1] = ue_ipaddr;
                        tmpArray[2] = Integer.toString(ue_teid9);
                        tmpArray[3] = Integer.toString(sgw_teid9);
                        tmpArray[4] = Integer.toString(ue_key9);

                        String dw = (String)connectPoint.deviceId().toString();  //hardcoding
                        String array3[]= dw.split(":");  //hardcoding
                        dw = array3[2];
                        if(Constants.DEBUG){
                            log.info("Inside case DETACH_REQUEST");
                            log.warn("array3[2] = {}",array3[2]); //hardcoding  array3[2] contains switches  like "s1", "s2" etc
                            log.warn(" in DETACH_REQUEST dw = {}",dw); //hardcoding  dw contains switches  like "s1", "s2" etc
                            step = 5;
                            d1 = d2 = null;
                            d1 = new Date();
                        }

                        if(Constants.DO_ENCRYPTION){
                            decArray = receiveDecryptedArray(tmpArray);
                        }

                        //tmpArray[1] => UE IP, tmpArray[2] => UE TEID, tmpArray[3] => SGW TEID, tmpArray[4] => UE_KEY
                        if(Constants.DEBUG){
                            log.warn("RECEIVED DETACH REQUEST from UE with ip = {} ",tmpArray[1]);
                                     log.warn("TEID = {}", tmpArray[2]);
                                              log.warn("corresponding SGW TEID = {}", tmpArray[3]);
                                                       log.warn("UE_KEY = {}", tmpArray[4]);
                        }
                        //removing the port mapping between UE key and its source port (UDP) used for control traffic
                        // tmpArray[4] => UE KEY
                        // @Offload design map not needed

                        // FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dw, "uekey_udp_src_port_map", tmpArray[4]); // tmpArray[4] => UE KEY

                        String pgw_dpid = Integer.toString(Constants.PGW_ID);

                        // newly added.. because can't remove in SEND_UE_TEID step.. due to re-establishment of tunnel
                            //@offload design  : commenting as not needed

                        FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dw, "uekey_sgw_teid_map", tmpArray[4]);// newly added.. because can't remove in SEND_UE_TEID step.. due to re-establishment of tunnel

                        // key is sgw teid and value is ue key
                        FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dw, "sgw_teid_uekey_map", tmpArray[3]); // key is sgw teid and value is ue key

                        //
                        FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dw,"uekey_ueip_map", tmpArray[4]);		// key is UE Key and value is UE IP

                        //delete uplink rule
                        /******************************** delete uplink flow rule on Ingress DGW( DGW -> SGW)********************************/
                        // tmpArray[2] contains UE IP as string convert it to byte array
                        //tmpArray[1] => UE IP, tmpArray[2] => UE TEID, tmpArray[3] => SGW TEID, tmpArray[4] => UE_KEY
                        int SGW_ID2 =  Integer.parseInt(Constants.getSgwDpid(dw));
                        String getval2 = dw.split("s")[1] + Constants.SEPARATOR + SGW_ID2;
                        outPort =  Constants.ENODEB_SGW_PORT_MAP.get(getval2);
                        byte [] UE_IP = IPv4.toIPv4AddressBytes(tmpArray[1]);
                        if(Constants.DEBUG){
                            log.info("UE IP as received from RAN = {}",tmpArray[1]);
                            log.info("Deleting ingress rule with deiveId = {}, UE_IPAddr = {}, sgw_teid = {},outPort = {}",deviceId,UE_IP, Integer.parseInt(tmpArray[3]),outPort);
                        }

                        /* UPLINK   => ipv4srcAddr = UE IP and ipv4dstAddr = Sink IP   */
                        fr.insertUplinkTunnelIngressRule(true, appId, flowRuleService, deviceId, UE_IP,Constants.dstSinkIpAddr, Integer.parseInt(tmpArray[3]), outPort);

                        if(Constants.DEBUG){
                            log.warn("DEFAULT SWITCH deleting uplink rule with for UE with IP = {}",tmpArray[1]);
                        }
                        int DEFAULT_S_SGW_PORT = Constants.ENODEB_SGW_PORT_MAP.get(dw.split("s")[1] + Constants.SEPARATOR + Constants.getSgwDpid(dw)); //dpids[0] ==> SGW DPID
                        //delete downlink rule
                        /***********************************delete downlink flow rule on Egress DGW( DGW -> RAN)*************************/
                        fr.insertUplinkTunnelForwardRule(true, appId, flowRuleService, deviceId, Integer.parseInt(tmpArray[2]), uePort, 0, true);

                        if(Constants.DEBUG){
                            log.warn("DEFAULT SWITCH deleting downlink rule with for UE with IP = {}",tmpArray[1]);
                            log.warn(" and UE TEID = {}",tmpArray[2]);
                        }

                        // dpids[0] ==> SGW DPID   & dpids[1]==> PGW DPID
                        DeviceId SGWswitchName2 = Constants.getSgwswitchName(dw);
                        boolean status = sgw.detachUEFromSGW(appId,flowRuleService,SGWswitchName2,Constants.getSgwDpid(dw), pgw_dpid, Integer.parseInt(tmpArray[3]), tmpArray[1]);
                        response = new StringBuilder();
                        
                        if(status){
                            response.append(Constants.DETACH_ACCEPT).append(Constants.SEPARATOR).append("");
                            if(Constants.DO_ENCRYPTION){
                                Utils.aesEncrypt(response.toString(), Constants.SAMPLE_ENC_KEY);
                                Utils.hmacDigest(response.toString(), Constants.SAMPLE_ENC_KEY);
                            }
                            if(Constants.DEBUG){
                                log.info(" sending response in DETACH_REQUEST");
                            }
                            DeviceId offload_SGWswitchName3 = Constants.getSgwswitchName(dw);

                            // @offload design : remove populated auxilary tables from SGW switch in detach case
                            // while deleting rules we dont need match values so sendong match parameters as 0 in all cases
                            fr.populate_uekey_uestate_map(true,appId,flowRuleService,offload_SGWswitchName3,Integer.parseInt(tmpArray[4]),0);
                            fr.populate_uekey_guti_map(true,appId,flowRuleService,offload_SGWswitchName3,Integer.parseInt(tmpArray[4]),0);
                            fr.populate_uekey_sgwteid_map(true,appId,flowRuleService,offload_SGWswitchName3,Integer.parseInt(tmpArray[4]),0);

                            DeviceId offload_BackupSGWswitchName3 = Constants.getBackupSgwswitchName(dw);

                            //@ft : remove rules from backup SGW as well
                            fr.populate_uekey_uestate_map(true,appId,flowRuleService,offload_BackupSGWswitchName3,Integer.parseInt(tmpArray[4]),0);
                            fr.populate_uekey_guti_map(true,appId,flowRuleService,offload_BackupSGWswitchName3,Integer.parseInt(tmpArray[4]),0);
                            fr.populate_uekey_sgwteid_map(true,appId,flowRuleService,offload_BackupSGWswitchName3,Integer.parseInt(tmpArray[4]),0);


                            build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());

                        }else{
                            response.append(Constants.DETACH_FAILURE).append(Constants.SEPARATOR).append("");
                            if(Constants.DO_ENCRYPTION){
                                Utils.aesEncrypt(response.toString(), Constants.SAMPLE_ENC_KEY);
                                Utils.hmacDigest(response.toString(), Constants.SAMPLE_ENC_KEY);
                            }
                            build_response_pkt(connectPoint,srcMac,dstMac,ipv4Protocol,ipv4SourceAddress,udp_dstport,udp_srcport,response.toString());

                            log.info("ERROR: DETACH_FAILURE");
                            //System.exit(1);
                        }
                        response = null;
                        if(Constants.DEBUG)
                            d2 = new Date();
                        break;

                    /************************************************* CONTEXT RELEASE ****************************************************/

                    case Constants.UE_CONTEXT_RELEASE_REQUEST:
                        // @offload design it will be handled by local onos controller
                        break;

                    /**********************************  UE_INITIATED SERVICE REQUEST ***************************************/

                    case Constants.UE_SERVICE_REQUEST:
                        // @offload design it will be handled by local onos controller
                        break;

                    case Constants.INITIAL_CONTEXT_SETUP_RESPONSE:
                        // @offload design it will be handled by local onos controller
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

                            // NAS_Keys = uekey_nas_keys_map.get(tmpArray[2]);
                            NAS_Keys = uekey_nas_keys_map.get(Integer.toString(imsi205));

                            // NAS_MAC = Utils.hmacDigest(tmpArray[0], NAS_Keys[1]);
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
