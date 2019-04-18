/*************************************************************
 * This class contains the control plane code of SGW.        *
 * It is used to install/delete uplink and downlink          *
 * flow rules on  dataplane switch of SGW (SGW-D). It also   *
 * contacts PGW-C on behalf of MME for allocating IP address *
 * and for install/deleting rules on PGW-D                   *
 *************************************************************/
package org.onosproject.p4tutorial.epc;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;


import com.google.common.collect.ImmutableSet;
import org.onlab.packet.MacAddress;
import org.onlab.packet.VlanId;
import org.onlab.util.ImmutableByteSequence;
import org.onosproject.net.DeviceId;
import org.onosproject.net.flow.DefaultFlowRule;
import org.onosproject.net.flow.DefaultTrafficSelector;
import org.onosproject.net.flow.DefaultTrafficTreatment;
import org.onosproject.net.flow.FlowRule;
import org.onosproject.net.flow.TrafficSelector;
import org.onosproject.net.flow.TrafficTreatment;
import org.onosproject.net.flow.criteria.Criterion;
import org.onosproject.net.flow.criteria.EthCriterion;
import org.onosproject.net.flow.criteria.IPCriterion;
import org.onosproject.net.flow.criteria.MplsCriterion;
import org.onosproject.net.flow.criteria.VlanIdCriterion;
import org.onosproject.net.flowobjective.ForwardingObjective;
import org.onosproject.net.flowobjective.ObjectiveError;
import org.onosproject.net.pi.model.PiActionId;
import org.onosproject.net.pi.runtime.PiAction;
import org.onosproject.net.pi.runtime.PiActionParam;


import com.google.common.collect.Lists;
import org.apache.felix.scr.annotations.Activate;
import org.apache.felix.scr.annotations.Component;
import org.apache.felix.scr.annotations.Deactivate;
import org.apache.felix.scr.annotations.Reference;
import org.apache.felix.scr.annotations.ReferenceCardinality;
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
import org.onosproject.net.flow.FlowRuleService;
import org.onosproject.net.flow.criteria.PiCriterion;
import org.onosproject.net.host.HostEvent;
import org.onosproject.net.host.HostListener;
import org.onosproject.net.host.HostService;
import org.onosproject.net.pi.model.PiActionId;
import org.onosproject.net.pi.model.PiActionParamId;
import org.onosproject.net.pi.model.PiMatchFieldId;
import org.onosproject.net.pi.model.PiTableId;
import org.onosproject.net.pi.runtime.PiAction;
import org.onosproject.net.pi.runtime.PiActionParam;

import org.slf4j.LoggerFactory;

import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;


public class SGW  {

	PGW pg = new PGW();
	FT ft = new FT();
	FR fr = new FR();
	private static final Logger log = getLogger(EpcApp.class);

	int tunnelId[] = {1,683,1365,2047,2729,3411};
	static int maxTeid[] = {682,1364,2046,2728,3410,4095};
	static int minTeid[] = {1,683,1365,2047,2729,3411};
	//ConcurrentHashMap<Integer, Integer> SGW_PGW_TEID_MAP = new ConcurrentHashMap<Integer, Integer>();
	//ConcurrentLinkedQueue<Integer> reuseable_teids = new ConcurrentLinkedQueue<Integer>();
	
	ConcurrentLinkedQueue<Integer>[] reusable_teids = makeClqArray(Constants.NUM_CHAINS);
	 
	@SuppressWarnings({"unchecked"})
	private static ConcurrentLinkedQueue<Integer>[] makeClqArray(int size) {
	    return (ConcurrentLinkedQueue<Integer>[]) new ConcurrentLinkedQueue[size];
	}
	public SGW(){
		for(int i=0;i<Constants.NUM_CHAINS;i++){
			reusable_teids[i] = new ConcurrentLinkedQueue<Integer>();

		}
	}
	
	
	

	/*
	 * This method is invoked by MME to establish the data tunnel between SGW-D and PGW-D
	 * by installing flow rules specific to the UE on SGW-D (for Uplink Data traffic)
	 * Here PGW_C also allocated an IP address for the UE. This IP address will be passed on to UE via SGW-C,
	 * MME and default switch in sequence.
	 */
//	String contactPGW(IOFSwitch sgw, IOFSwitch pgw, DatapathId sgw_dpId, DatapathId pgw_dpId, String apn){
	String contactPGW(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,String sgw_dpId, String pgw_dpId, String apn){
		String dgwId = Constants.getDgwDpid(sgw_dpId);
		String []tmpArray = null;
		int pgw_teid, sgw_teid;
		//code for reusing the used tunnel ids. Because we only have 4000 available
		int chainId = Constants.getChainIDFromSGW(sgw_dpId);
		/*************************** for now we dont need synchronisation as issue is fixed ****************************/
//		synchronized( this ) {
			if(reusable_teids[chainId].isEmpty()){
				if(tunnelId[chainId] > maxTeid[chainId]){
					tunnelId[chainId] = minTeid[chainId];
				}
				sgw_teid = tunnelId[chainId];
				tunnelId[chainId]++;

			}else{
				sgw_teid = reusable_teids[chainId].remove();
				if(Constants.MYDEBUG){
					log.warn("SGW reusing TEID = {}",sgw_teid);
				}
			}
//		}


		if(Constants.DEBUG){
			log.warn("PGATEWAY="+pgw_dpId);
			log.warn("S GW TUNNEL ID of UE {}",apn);
			log.warn(" is {}",sgw_teid);
		}
		// contacting pgw to allocate an ip address for UE. PGW_C also provides its tunnel endpoint identifier to SGW_C.
//		String ip_pgw = pg.allocateIPForUE(pgw, sgw_teid, sgw_dpId, pgw_dpId,  apn);
		String ip_pgw = pg.allocateIPForUE(appId,flowRuleService,sgw_teid, sgw_dpId, pgw_dpId,  apn);
		//ip_pgw format is UE_IP_ADDRESS + SEPARATOR + PGW tunnel ID for this UE

		tmpArray = ip_pgw.split(Constants.SEPARATOR); // tmpArray[0] => IP for UE. tmpArray[1] => PGW tunnel ID for this UE

		//uplink rule (SGW to PGW)
		if(Constants.MYDEBUG1){
//			System.out.println("SGW installing uplink rule on S-GW dpid = "+sgw_dpId+" inport="+Constants.SGW_PORT_MAP.get(sgw_dpId)[0]+" in teid = "+sgw_teid+
			//					" outPort = "+Constants.SGW_PORT_MAP.get(sgw_dpId)[1]+" out teid= "+tmpArray[1]+" of UE apn = "+apn);

			log.warn("SGW installing uplink rule on S-GW dpid = {}",sgw_dpId);
//			log.warn(" inport={}",Constants.SGW_PORT_MAP.get(sgw_dpId)[0]);
			log.warn(" in teid = {}",sgw_teid);
			log.warn(" outPort = {}",Constants.SGW_PORT_MAP.get(sgw_dpId)[1]);
			log.warn(" out teid= {}",tmpArray[1]);
		}
		pgw_teid = Integer.parseInt(tmpArray[1]);
		//SGW_PGW_TEID_MAP.put(sgw_teid, pgw_teid);
		if(Constants.MYDEBUG) {
			log.info(" in contactPGW put");
			log.warn(" of UE apn = {}",apn);

		}

		FT.put(Integer.parseInt(Constants.SEND_APN), dgwId, "SGW_PGW_TEID_MAP", String.valueOf(sgw_teid), String.valueOf(pgw_teid));

		/****************************uplink rule on SGW (SGW to PGW) ************************************/
		//delete y/n, application id, const, switch to install rule on, 
		fr.insertUplinkTunnelForwardRule(false,appId,flowRuleService,switchId,sgw_teid,Constants.SGW_PORT_MAP.get(sgw_dpId)[1],pgw_teid,false);
		// done
//		installFlowRule(sgw, sgw_dpId, Constants.SGW_PORT_MAP.get(sgw_dpId)[0], sgw_teid, Constants.SGW_PORT_MAP.get(sgw_dpId)[1], pgw_teid, tmpArray[0], Constants.getPgwIpUplink(sgw_dpId));

		// tmpArray[0] => IP for UE
		return tmpArray[0] + Constants.SEPARATOR + sgw_teid;
	}


	/*
	 * This method installs the downlink flow rule between SGW-D and default switch after knowing the UE generated tunnel for default switch
	 */
	public void modifyBearerRequest(ApplicationId appId,FlowRuleService flowRuleService,DeviceId SGWswitchId,String sgw, String sgw_dpId, int sgw_teId, int ue_teId, String key){
		if(Constants.DEBUG){
//			System.out.println("teid="+ue_teId);
			log.warn("teid = {}",ue_teId);
			//downlink rule (SGW to ENodeB)
//			System.out.println("SGW installing downlink rule on S-GW dpid = "+sgw_dpId.getLong()+" inport="+Constants.SGW_PORT_MAP.get(sgw_dpId)[1]+" in teid = "+sgw_teId+
//									   " outPort = "+Constants.SGW_PORT_MAP.get(sgw_dpId)[0]+" out teid= "+ue_teId+" of UE key = "+key);

			log.warn("SGW installing downlink rule on S-GW dpid = {}",sgw_dpId);
			log.warn(" inport = {}",Constants.SGW_PORT_MAP.get(sgw_dpId)[1]);
			log.warn(" in teid = {}",sgw_teId);
			log.warn(" outPort = {}",Constants.SGW_PORT_MAP.get(sgw_dpId)[0]);
			log.warn(" out teid = {}",ue_teId);
			log.warn(" of UE key = {}",key);
		}

		/******************************** Downlink flow rules on SGW (SGW to DGW) **************************************/
//          insertUplinkTunnelForwardRule(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int intunId,int outPort,int outtunId,boolean isEgress) {
			fr.insertDownlinkTunnelForwardRule(false,appId,flowRuleService,SGWswitchId,sgw_teId,Constants.SGW_PORT_MAP.get(sgw_dpId)[0],ue_teId);
            // fr.insertUplinkTunnelForwardRule(false,appId,flowRuleService,SGWswitchId,sgw_teId,Constants.SGW_PORT_MAP.get(sgw_dpId)[0],ue_teId,false);
			
//		installFlowRule(sgw, sgw_dpId, Constants.SGW_PORT_MAP.get(sgw_dpId)[1], sgw_teId, Constants.SGW_PORT_MAP.get(sgw_dpId)[0], ue_teId, Constants.SINK_IP, Constants.getDgwIpDownlink(sgw_dpId));

	}


	/*
	 * This is a utility method requiring to know the starting IP address PGW-C will be using.
	 * This method is needed so that we can preallocate the IP addresses that will be used in this 
	 * experiment onto the interface of UE machine. This is to avoid wasting time and CPU on this later
	 * that is, during the main experiment.
	 */
//	public String getStartingIPAddress(IOFSwitch sw){
	public String getStartingIPAddress(String sw){
		return pg.returnStartingIPAddress(sw);
	}

	/******This method detaches the tunnel between SGW-D and default switch, by deleting the uplink and downlink rules on SGW-D *****/
//	public boolean detachUEFromSGW(IOFSwitch sgw, IOFSwitch pgw, DatapathId sgw_dpId, DatapathId pgw_dpId, int sgw_teid, String ue_ip) throws NumberFormatException, InterruptedException{
	public boolean detachUEFromSGW(ApplicationId appId,FlowRuleService flowRuleService,DeviceId SGWswitchId,String sgw_dpId, String pgw_dpId, int sgw_teid, String ue_ip) {

			int pgw_teid=0;
	//		DatapathId dgwId = DatapathId.of(Constants.getDgwDpid(sgw_dpId));
			String dgwId = Constants.getDgwDpid(sgw_dpId);
			//pgw_teid = SGW_PGW_TEID_MAP.get(sgw_teid);
//			pgw_teid = Integer.parseInt(FT.get(dgwId, "SGW_PGW_TEID_MAP", String.valueOf(sgw_teid)));
		if(Constants.MYDEBUG){
			log.warn(" in detachUEFromSGW get");
			log.warn("before get dgwId  = {}",dgwId);
			log.warn("before get in SGW sgw_teid = {}",String.valueOf(sgw_teid));
		}
		    String pgw_teid1 = FT.get(dgwId, "SGW_PGW_TEID_MAP", String.valueOf(sgw_teid));
		    if(pgw_teid1==null){
		    	log.warn("recevied null value in line 248 in SGW");
			}
			else{
				pgw_teid = Integer.parseInt(pgw_teid1);
			}
			//if (pgw_teid != 0)
				//SGW_PGW_TEID_MAP.remove(sgw_teid);
			if(Constants.MYDEBUG) {
					log.warn(" in detachUEFromSGW del");
			}
			FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dgwId, "SGW_PGW_TEID_MAP", String.valueOf(sgw_teid));   // TODO

			//delete uplink rule
			/***********************************delete uplink flow rule on Transit SGW( SGW -> PGW) *********************************************/
			/*******************while deleting we only need match field confirm??????????????***************************************/

//		public void insertUplinkTunnelForwardRule(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int intunId,int outPort,int outtunId,boolean isEgress) {
			fr.insertUplinkTunnelForwardRule(true,appId,flowRuleService,SGWswitchId,sgw_teid,Constants.SGW_PORT_MAP.get(sgw_dpId)[1],pgw_teid,false);

		//		deleteFlowRuleWithTEID(sgw, Constants.SGW_PORT_MAP.get(sgw_dpId)[0], sgw_teid, ue_ip);

			if(Constants.DEBUG){
				log.warn(" SGW deleting uplink rule with PGW TEID = {}",pgw_teid);
				log.warn(" for UE with IP = {}",ue_ip);
			}

			/*****************************delete downlink flow rule on Transit SGW( SGW -> DGW)**************************************************/
			int ue_teId = 0; // we dont need action parameters while deleting flow rules
			fr.insertDownlinkTunnelForwardRule(true,appId,flowRuleService,SGWswitchId,sgw_teid,Constants.SGW_PORT_MAP.get(sgw_dpId)[0],ue_teId);
			// fr.insertUplinkTunnelForwardRule(true,appId,flowRuleService,SGWswitchId,sgw_teid,Constants.SGW_PORT_MAP.get(sgw_dpId)[0],ue_teId,false);

		//		deleteFlowRuleWithTEID(sgw, Constants.SGW_PORT_MAP.get(sgw_dpId)[1], sgw_teid, Constants.SINK_IP);

			if(Constants.DEBUG){
				log.warn(" SGW deleting downlink rule with SGW TEID = {}",sgw_teid);
				log.warn(" for UE with IP = {}",ue_ip);
			}
			int chainId = Constants.getChainIDFromSGW(sgw_dpId);
			reusable_teids[chainId].add(sgw_teid);

//			return pg.detachUEFromPGW(pgw, sgw_dpId, pgw_dpId, pgw_teid, ue_ip);
			return pg.detachUEFromPGW(appId,flowRuleService,sgw_dpId, pgw_dpId, pgw_teid, ue_ip);


	}

	/**
	 * This method is used to simulate UE idle timeout. When UE remains idle for specified amount of time, we delete the downlink rule between SDG-D
	 * and default switch.
	 **/
	public void releaseAccessBearersRequest(ApplicationId appId,FlowRuleService flowRuleService,DeviceId SGWswitchId, String sgw_dpId, int sgw_teid, String ue_ip){

		//delete downlink rule
		/*****************************delete downlink flow rule on Transit SGW( SGW -> DGW)**************************************************/
		int ue_teId = 0; // we dont need action parameters while deleting flow rules
		fr.insertDownlinkTunnelForwardRule(true,appId,flowRuleService,SGWswitchId,sgw_teid,Constants.SGW_PORT_MAP.get(sgw_dpId)[0],ue_teId);
		// fr.insertUplinkTunnelForwardRule(true,appId,flowRuleService,SGWswitchId,sgw_teid,Constants.SGW_PORT_MAP.get(sgw_dpId)[0],ue_teId,false);


//		deleteFlowRuleWithTEID(sgw, Constants.SGW_PORT_MAP.get(sgw_dpId)[1], sgw_teid, Constants.SINK_IP);
		if(Constants.DEBUG){
			log.info("SGW deleting downlink rule with SGW TEID = {} for UE with IP = {}",sgw_teid,ue_ip);
		}
	}
}


//	/*
//	 * This method helps to delete the flow rule on SGW-D using TEID as the matching criteria
//	 */
//	private void deleteFlowRuleWithTEID(IOFSwitch sw, int inPort, int ue_teid, String srcIP){
//		OFFlowMod.Builder fmb = sw.getOFFactory().buildFlowDelete();
//		Match.Builder mb = sw.getOFFactory().buildMatch();
//
//		mb.setExact(MatchField.ETH_TYPE, EthType.IPv4)
//		.setExact(MatchField.IN_PORT, OFPort.of(inPort))
//		.setExact(MatchField.IPV4_SRC, IPv4Address.of(srcIP))
//		.setExact(MatchField.VLAN_VID, OFVlanVidMatch.ofVlanVid(VlanVid.ofVlan(ue_teid)));
//
//		fmb.setMatch(mb.build());
//
//		//delete the rule from the switch
//		sw.write(fmb.build());
//	}

	/********* This method helps to install the flow rule on SGW-D using TEID as the matching criteria ***********************/

	//		     installFlowRule(sgw, sgw_dpId, Constants.SGW_PORT_MAP.get(sgw_dpId)[0], sgw_teid, Constants.SGW_PORT_MAP.get(sgw_dpId)[1], pgw_teid, tmpArray[0], Constants.getPgwIpUplink(sgw_dpId));
//	private void installFlowRule(IOFSwitch sw, DatapathId dpId, int inPort, int inTunnelId, int outPort, int outTunnelId, String srcIP, String dstIP){
//		OFFlowMod.Builder fmb = sw.getOFFactory().buildFlowAdd();
//		Match.Builder mb = sw.getOFFactory().buildMatch();
//
//		mb.setExact(MatchField.ETH_TYPE, EthType.IPv4)
//		.setExact(MatchField.IN_PORT, OFPort.of(inPort))
//		.setExact(MatchField.IPV4_SRC, IPv4Address.of(srcIP))
//		.setExact(MatchField.VLAN_VID, OFVlanVidMatch.ofVlanVid(VlanVid.ofVlan(inTunnelId)));
//
//		List<OFAction> actions = new ArrayList<OFAction>();
//
//		actions.add(sw.getOFFactory().actions().setVlanVid(VlanVid.ofVlan(outTunnelId)));
//		if(dstIP != "")
//			actions.add(sw.getOFFactory().actions().setNwDst(IPv4Address.of(dstIP)));
//		actions.add(sw.getOFFactory().actions().output(OFPort.of(outPort), Integer.MAX_VALUE)); // FLOOD is a more selective/efficient version of ALL
//
//		fmb.setActions(actions);
//
//		fmb.setHardTimeout(0)
//		.setIdleTimeout(0)
//		.setPriority(1)
//		.setBufferId(OFBufferId.NO_BUFFER)
//		.setMatch(mb.build());
//
//		sw.write(fmb.build());
//	}

//	public void installFlowRule(ForwardingObjective fwd){
//		TrafficTreatment treatment;
//
//		treatment = fwd.treatment();
//		if (fwd.nextId() != null) {
//			PiActionParam nextIdParam = new PiActionParam(FabricConstants.NEXT_ID,
//														  ImmutableByteSequence.copyFrom(fwd.nextId().byteValue()));
//			PiAction nextIdAction = PiAction.builder()
//					.withId(FabricConstants.FABRIC_INGRESS_FORWARDING_POP_MPLS_AND_NEXT)
//					.withParameter(nextIdParam)
//					.build();
//			treatment = DefaultTrafficTreatment.builder()
//					.piTableAction(nextIdAction)
//					.build();
//		}
//
//		TrafficSelector selector = DefaultTrafficSelector.builder()
//				.add(mplsCriterion)
//				.build();
//
//		FlowRule flowRule = DefaultFlowRule.builder()
//				.withSelector(selector)
//				.withTreatment(treatment)
//				.fromApp(fwd.appId())
//				.withPriority(fwd.priority())
//				.makePermanent()
//				.forDevice(deviceId)
//				.forTable(FabricConstants.FABRIC_INGRESS_FORWARDING_MPLS)
//				.build();
//
//		resultBuilder.addFlowRule(flowRule);
//	}


//	@Override
//	public String getName() {
//		return SGW.class.getPackage().getName();
//	}
//
//	public Command receive(IOFSwitch sw, OFMessage msg, FloodlightContext cntx) {
//		switch (msg.getType()) {
//		case PACKET_IN:
//			/*if(DatapathId.of(getSgwDpid()).equals(sw.getId())) {
//				//System.out.println("SGW: Received PACKET_IN request");
//				//+return this.processPacketInMessage(sw, (OFPacketIn) msg, cntx);
//			}*/
//			if(DatapathId.of(Constants.DEFAULT_SWITCH_ID_1).equals(sw.getId()) || DatapathId.of(Constants.DEFAULT_SWITCH_ID_2).equals(sw.getId())) {
//				defaultSwitch = sw.getId();
//			}
//			return Command.CONTINUE;
//		case ERROR:
//			log.info("received an error {} from switch {}", msg, sw);
//			return Command.CONTINUE;
//		default:
//			log.error("received an unexpected message {} from switch {}", msg, sw);
//			return Command.CONTINUE;
//		}
//
//	}
//
//	@SuppressWarnings("unused")
//	private Command processPacketInMessage(IOFSwitch sw, OFPacketIn pi, FloodlightContext cntx) {
//		OFPort inPort = (pi.getVersion().compareTo(OFVersion.OF_12) < 0 ? pi.getInPort() : pi.getMatch().get(MatchField.IN_PORT));
//
//		/* Read packet header attributes into Match */
//		Match m = createMatchFromPacket(sw, inPort, cntx);
//		MacAddress sourceMac = m.get(MatchField.ETH_SRC);
//		MacAddress destMac = m.get(MatchField.ETH_DST);
//		VlanVid vlan = m.get(MatchField.VLAN_VID) == null ? VlanVid.ZERO : m.get(MatchField.VLAN_VID).getVlanVid();
//		IPv4Address srcIp, dstIp;
//
//		if (sourceMac == null) {
//			sourceMac = MacAddress.NONE;
//		}
//
//		if (destMac == null) {
//			destMac = MacAddress.NONE;
//		}
//		if (vlan == null) {
//			vlan = VlanVid.ZERO;
//		}
//
//
//		Ethernet eth = IFloodlightProviderService.bcStore.get(cntx, IFloodlightProviderService.CONTEXT_PI_PAYLOAD);
//		if(eth.getEtherType() == EthType.IPv4){
//
//			IPv4 ipPkt = (IPv4)eth.getPayload();
//			srcIp = ipPkt.getSourceAddress();
//			dstIp = ipPkt.getDestinationAddress();
//
//			System.out.println("Src IP = "+ srcIp+" Dst Ip = "+ dstIp);
//
//			//mme.downlinkDataNotification(srcIp.toString());
//		}
//		return Command.CONTINUE;
//	}
//
//	protected Match createMatchFromPacket(IOFSwitch sw, OFPort inPort, FloodlightContext cntx) {
//		// The packet in match will only contain the port number.
//		// We need to add in specifics for the hosts we're routing between.
//		Ethernet eth = IFloodlightProviderService.bcStore.get(cntx, IFloodlightProviderService.CONTEXT_PI_PAYLOAD);
//		VlanVid vlan = VlanVid.ofVlan(eth.getVlanID());
//		MacAddress srcMac = eth.getSourceMACAddress();
//		MacAddress dstMac = eth.getDestinationMACAddress();
//
//		Match.Builder mb = sw.getOFFactory().buildMatch();
//		mb.setExact(MatchField.IN_PORT, inPort)
//		.setExact(MatchField.ETH_SRC, srcMac)
//		.setExact(MatchField.ETH_DST, dstMac);
//
//		if (!vlan.equals(VlanVid.ZERO)) {
//			mb.setExact(MatchField.VLAN_VID, OFVlanVidMatch.ofVlanVid(vlan));
//		}
//
//		return mb.build();
//	}
//
//	@Override
//	public boolean isCallbackOrderingPrereq(OFType type, String name) {
//		return false;
//	}
//
//	@Override
//	public boolean isCallbackOrderingPostreq(OFType type, String name) {
//		return false;
//	}
//
//	// IFloodlightModule
//
//	@Override
//	public Collection<Class<? extends IFloodlightService>> getModuleServices() {
//		// We don't provide any services, return null
//		return null;
//	}
//
//	@Override
//	public Map<Class<? extends IFloodlightService>, IFloodlightService>
//	getServiceImpls() {
//		// We don't provide any services, return null
//		return null;
//	}
//
//	@Override
//	public Collection<Class<? extends IFloodlightService>>
//	getModuleDependencies() {
//		Collection<Class<? extends IFloodlightService>> l =
//				new ArrayList<Class<? extends IFloodlightService>>();
//		l.add(IFloodlightProviderService.class);
//		return l;
//	}
//
//	@Override
//	public void init(FloodlightModuleContext context)
//			throws FloodlightModuleException {
//		floodlightProvider = context.getServiceImpl(IFloodlightProviderService.class);
//	}
//
//	@Override
//	public void startUp(FloodlightModuleContext context) {
//		floodlightProvider.addOFMessageListener(OFType.PACKET_IN, this);
//	}
