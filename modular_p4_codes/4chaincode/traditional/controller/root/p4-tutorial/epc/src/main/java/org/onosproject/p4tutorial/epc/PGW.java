/*************************************************************
 * This class contains the control plane code of PGW.        *
 * It is used to install/delete uplink and downlink          *
 * flow rules on  dataplane switch of PGW (PGW-D). It also   *
 * allocates IP address for the UE.                          *
 *************************************************************/
package org.onosproject.p4tutorial.epc;

import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Random;
import java.util.concurrent.ConcurrentLinkedQueue;

import org.onosproject.core.ApplicationId;
import org.onosproject.net.flow.FlowRuleService;
import org.onosproject.net.DeviceId;
import org.onlab.packet.IPv4;



import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;

public class PGW  {

	FR fr = new FR();

	private static final Logger log = getLogger(EpcApp.class);
	volatile String ip[]={Constants.STARTING_UE_IP_1, Constants.STARTING_UE_IP_2, Constants.STARTING_UE_IP_3, Constants.STARTING_UE_IP_4, Constants.STARTING_UE_IP_5, Constants.STARTING_UE_IP_6};
	int tunnelId = 4000;
	
	int numIps = 0;
	int pgw_sink_port;
//	protected static IOFSwitchService switchService;
	ConcurrentLinkedQueue reuseable_teids = new ConcurrentLinkedQueue<Integer>();
	/*ConcurrentLinkedQueue<String> reuseable_ips_0 = new ConcurrentLinkedQueue<String>();
	ConcurrentLinkedQueue<String> reuseable_ips_1 = new ConcurrentLinkedQueue<String>();
	ConcurrentLinkedQueue<String> reuseable_ips_2 = new ConcurrentLinkedQueue<String>();
	ConcurrentLinkedQueue<String> reuseable_ips_3 = new ConcurrentLinkedQueue<String>();
	ConcurrentLinkedQueue<String> reuseable_ips_4 = new ConcurrentLinkedQueue<String>();
	*/
	
	ConcurrentLinkedQueue<String>[] reusable_ips = makeClqArray(Constants.NUM_CHAINS);
	 
	@SuppressWarnings({"unchecked"})
	private static ConcurrentLinkedQueue<String>[] makeClqArray(int size) {
	    return (ConcurrentLinkedQueue<String>[]) new ConcurrentLinkedQueue[size];
	}
	

	
	public PGW() {
		// port of pgw which is connected to sink
		pgw_sink_port = Constants.PGW_SINK_PORT; 
		for(int i=0;i<Constants.NUM_CHAINS;i++){
			reusable_ips[i] = new ConcurrentLinkedQueue<String>();

		}		
	}

	public String[] getPartsOfIpAddress(String ipAddress) {
		String[] elements = ipAddress.split("\\.");
		return elements;
	}
	
//	public String returnStartingIPAddress(IOFSwitch sw){   // changes here
	public String returnStartingIPAddress(String sw){
//		DatapathId dp = sw.getId();
		
		return ip[Constants.getChainIDFromDGW(sw)];
	}
	
	public static int randInt(int min, int max) {
	    // Usually this can be a field rather than a method variable
	    Random rand = new Random();
	    // nextInt is normally exclusive of the top value,
	    // so add 1 to make it inclusive
	    int randomNum = rand.nextInt((max - min) + 1) + min;

	    return randomNum;
	}

	/*
	 * This method generates the next IP address in sequence given the current IP address. 
	 */
	public synchronized String getNextIPAddress(String ipAddress) throws Exception {
		String[] elements = getPartsOfIpAddress(ipAddress);
		if (elements != null && elements.length == 4) {
			Integer part1 = Integer.parseInt(elements[0]);
			Integer part2 = Integer.parseInt(elements[1]);
			Integer part3 = Integer.parseInt(elements[2]);
			Integer part4 = Integer.parseInt(elements[3]);
			if (part4 < 255) {
				String ip = part1 + "." + part2 + "." + part3 + "." + (++part4);
				return ip;
			} else if (part4 == 255) {
				if (part3 < 255) {
					String ip = part1 + "." + part2 + "." + (++part3) + "."
							+ (0);
					return ip;
				} else if (part3 == 255) {
					if (part2 < 255) {
						String ip = part1 + "." + (++part2) + "." + (0) + "."
								+ (0);
						return ip;
					} else if (part2 == 255) {
						if (part1 < 255) {
							String ip = (++part1) + "." + (0) + "." + (0) + "."
									+ (0);
							return ip;
						} else if (part1 == 255) {
							throw new Exception("IP Range Exceeded -> "+ipAddress);
						}
					}
				}
			}
		}

		return null;
	}

	/*
	 * This method generates and allocates the UE IP address and PGW Tunnel ID (for this specific UE session)
	 */
//	public synchronized String allocateIPForUE(IOFSwitch pgw, int sgw_tunnelId, DatapathId sgw_dpId, DatapathId pgw_dpId, String apn){
	public synchronized String allocateIPForUE(ApplicationId appId,FlowRuleService flowRuleService, int sgw_tunnelId, String sgw_dpId, String pgw_dpId, String apn){
		Integer pgw_teid;
		// resuing old tunnel ids
		int chainId = Constants.getChainIDFromSGW(sgw_dpId);
		if(Constants.DEBUG) {
			log.warn("ALLOCATE IP for chain = {}", chainId);
			log.warn("sgw teid = {}", sgw_tunnelId);
			log.warn(" sgwdpid = {}", sgw_dpId);
		}
		if(reuseable_teids.isEmpty()){
			if(tunnelId < 0 || tunnelId > 4000){
				tunnelId = 4000;
			}
			pgw_teid = tunnelId;
			tunnelId--;
		}else{
			pgw_teid = (int) reuseable_teids.remove();
			if(Constants.DEBUG){
				log.warn("PGW reusing TEID = {}",pgw_teid);
			}
		}
		try {


			if(reusable_ips[chainId].isEmpty()){
				numIps++;
				this.ip[chainId] = getNextIPAddress(ip[chainId]);
			}else{
				this.ip[chainId] = reusable_ips[chainId].remove();
				if(Constants.DEBUG){
					log.warn("PGW reusing IP = {}",this.ip[chainId]);
					log.warn(" numips = ",numIps);
				}
			}
		} catch (Exception e) {
			log.info("some stacktrace");
//			System.out.println(e.printStackTrace());
		}

		if(Constants.DEBUG){
			log.warn("P GW TUNNEL ID of UE = {}",apn);
            log.warn(" is = {}",pgw_teid);
		}
		String dgw_dp_id_temp = Constants.getDgwDpid(sgw_dpId);
		String sgw_ip = Constants.getSgwIpDownlink(dgw_dp_id_temp);
		//install uplink and downlink rules
		//System.out.println("PGW DPID " + pgw_dpId.getLong() + "SGW DPID " + sgw_dpId.getLong());
        /********************  Uplink rule is installed on PGW (PGW to sink) *************************/
		DeviceId pgwSwitchName = Constants.PGW_Switch_Name;
//		sgw.insertTunnelForwardRule(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int intunId,int outPort,int outtunId,true);
		fr.insertUplinkTunnelForwardRule(false,appId, flowRuleService,pgwSwitchName,pgw_teid, pgw_sink_port,0,true);

		/********************  Downlink rule is installed on PGW (sink to PGW) *************************/


		byte[] UE_IPAddr = IPv4.toIPv4AddressBytes(ip[chainId]);
		if(Constants.DEBUG) {
			log.warn("PGW reusing IP = {}", this.ip[chainId]);
			log.warn("IP rule ############## {}", UE_IPAddr);
			log.info("pgw_dpId + Constants.SEPARATOR + sgw_dpId = {}",pgw_dpId + Constants.SEPARATOR+ sgw_dpId);
			log.info("pgw_dpId + Constants.SEPARATOR + sgw_dpId value ### {}",Constants.PGW_SGW_PORT_MAP.get(pgw_dpId + Constants.SEPARATOR+ sgw_dpId));
		}


        /* DOWNLINK => ipv4srcAddr = Sink IP and ipv4dstAddr = UE IP   */
		fr.insertUplinkTunnelIngressRule(false,appId,flowRuleService,pgwSwitchName,Constants.dstSinkIpAddr,UE_IPAddr,sgw_tunnelId,Constants.PGW_SGW_PORT_MAP.get(pgw_dpId + Constants.SEPARATOR + sgw_dpId));

		//	private void installPGWRules(IOFSwitch pgw, DatapathId pgw_dpId, int inPort, int pgw_tunnelId, int sgw_tunnelId, int outPort, String apn, String UE_IP, String sgw_ip){

//		installPGWRules(pgw, pgw_dpId, Constants.PGW_SGW_PORT_MAP.get(pgw_dpId.getLong() + Constants.SEPARATOR + sgw_dpId.getLong()), pgw_teid, sgw_tunnelId, pgw_sink_port, apn, ip[chainId], sgw_ip);

		return ip[chainId] + Constants.SEPARATOR + pgw_teid.toString();
	}

	/************* this method deletes uplink and downlink flow rules from PGW-D *******************/
//	public boolean detachUEFromPGW(IOFSwitch pgw, DatapathId sgw_dpId, DatapathId pgw_dpId, int pgw_teid, String ue_ip){
	public synchronized boolean detachUEFromPGW(ApplicationId appId,FlowRuleService flowRuleService,String sgw_dpId, String pgw_dpId, int pgw_teid, String ue_ip){
//		int S_P_inPort = Constants.PGW_SGW_PORT_MAP.get(pgw_dpId.getLong() + Constants.SEPARATOR + sgw_dpId.getLong());
		int S_P_inPort = Constants.PGW_SGW_PORT_MAP.get(pgw_dpId + Constants.SEPARATOR + sgw_dpId);
		//delete uplink rule
		int chainId = Constants.getChainIDFromSGW(sgw_dpId);
		/******************** Remove  Uplink rule is installed on PGW (PGW to sink) *************************/
		DeviceId pgwSwitchName = DeviceId.deviceId("device:bmv2:s3");
		int pgw_sink_port = 0 ; // dont need outPort while deleting flow rule
		fr.insertUplinkTunnelForwardRule(true,appId, flowRuleService,pgwSwitchName,pgw_teid, pgw_sink_port,0,true);

//		deleteFlowRuleWithTEID(pgw, S_P_inPort, pgw_teid, ue_ip);

		if(Constants.DEBUG){
//			System.out.println("PGW deleting uplink rule with PGW TEID="+pgw_teid+" inPort="+S_P_inPort+" for UE with IP="+ue_ip);
			log.warn(" TBD : PGW deleting uplink rule with PGW TEID = {}",pgw_teid);
			log.warn(" inPort = {}",S_P_inPort);
			log.warn(" for UE with IP = {}",ue_ip);
		}

		//delete downlink rule
		/********************  Remove Downlink rule is installed on PGW (sink to PGW) *************************/
		byte[] UE_IPAddr = IPv4.toIPv4AddressBytes(ue_ip);
		int sgw_tunnelId = 0; // dont need sgw_tunnelId while deleting flow rule
		// fr.insertDownlinkTunnelIngressRule(true,appId,flowRuleService,pgwSwitchName,UE_IPAddr,sgw_tunnelId,Constants.PGW_SGW_PORT_MAP.get(pgw_dpId + Constants.SEPARATOR + sgw_dpId));

        /* DOWNLINK => ipv4srcAddr = Sink IP and ipv4dstAddr = UE IP   */
		fr.insertUplinkTunnelIngressRule(true,appId,flowRuleService,pgwSwitchName,Constants.dstSinkIpAddr,UE_IPAddr,sgw_tunnelId,Constants.PGW_SGW_PORT_MAP.get(pgw_dpId + Constants.SEPARATOR + sgw_dpId));

//		deleteFlowRuleWithIP(pgw, pgw_sink_port, ue_ip);
		if(Constants.DEBUG){
//			System.out.println("PGW deleting downlink rule with PGW TEID="+pgw_teid+" inPort="+pgw_sink_port+" for UE with IP="+ue_ip);
			log.warn(" TBD : PGW deleting downlink rule with PGW TEID = {}",pgw_teid);
			log.warn(" inPort = {}",pgw_sink_port);
			log.warn(" for UE with IP = {}",ue_ip);
		}

		reusable_ips[chainId].add(ue_ip);
		reuseable_teids.add(pgw_teid);

		return true;
	}
//
//	// Method for deleting downlink rule
//	private synchronized void deleteFlowRuleWithIP(IOFSwitch sw, int inPort, String ue_ip){
//		OFFlowMod.Builder fmb = sw.getOFFactory().buildFlowDelete();
//		Match.Builder mb = sw.getOFFactory().buildMatch();
//
//		mb.setExact(MatchField.ETH_TYPE, EthType.IPv4)
//		.setExact(MatchField.IN_PORT, OFPort.of(inPort))
//		.setExact(MatchField.IPV4_DST, IPv4Address.of(ue_ip));
//
//		fmb.setMatch(mb.build());
//		boolean x = sw.write(fmb.build());
//		if(!x){
//			System.out.println("********************LO JI HO GAYI GADBAD!!!!!! pgw delete ip mein**********************");
//			System.exit(0);
//		}
//		/*try {
//			Thread.sleep(1);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}*/
//	}
//
//	// Method for deleting uplink rule
//	private synchronized void deleteFlowRuleWithTEID(IOFSwitch sw, int inPort, int pgw_teid, String srcIP){
//		OFFlowMod.Builder fmb = sw.getOFFactory().buildFlowDelete();
//		Match.Builder mb = sw.getOFFactory().buildMatch();
//
//		mb.setExact(MatchField.ETH_TYPE, EthType.IPv4)
//		.setExact(MatchField.IN_PORT, OFPort.of(inPort))
//		.setExact(MatchField.IPV4_SRC, IPv4Address.of(srcIP))
//		.setExact(MatchField.VLAN_VID, OFVlanVidMatch.ofVlanVid(VlanVid.ofVlan(pgw_teid)));
//
//		fmb.setMatch(mb.build());
//		sw.write(fmb.build());
//		boolean x = sw.write(fmb.build());
//		if(!x){
//			System.out.println("********************LO JI HO GAYI GADBAD!!!!!! pgw delete teid mein**********************");
//			System.exit(0);
//		}
//		/*try {
//			Thread.sleep(1);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}*/
//	}
//
//	/*
//	 * this method installs uplink and downlink flow rules on PGW-D
//	 */
//	private void installPGWRules(IOFSwitch pgw, DatapathId pgw_dpId, int inPort, int pgw_tunnelId, int sgw_tunnelId, int outPort, String apn, String UE_IP, String sgw_ip){
//		//uplink rule (PGW to SINK)
//		if(Constants.DEBUG){
//			System.out.println("PGW installing uplink rule on P-GW dpid = "+pgw_dpId.getLong()+" inport="+inPort+" in teid = "+pgw_tunnelId+
//					" outPort = "+outPort+" out teid= "+pgw_tunnelId+" of UE apn = "+apn);
//		}
//
//		installFlowRule(pgw, pgw_dpId, inPort, pgw_tunnelId, outPort, pgw_tunnelId, UE_IP, Constants.SINK_IP);
//
//		//downlink rule (SINK to PGW)
//		if(Constants.DEBUG){
//			System.out.println("PGW installing downlink rule on P-GW dpid = "+pgw_dpId.getLong()+" inport="+outPort+" in SRC IP = "+UE_IP+
//					" outPort = "+inPort+" out teid= "+sgw_tunnelId+" and SRC IP = "+ Constants.SINK_IP +" of UE apn = "+apn);
//		}
//		installFlowRuleWithIP(pgw, pgw_dpId, outPort, inPort, sgw_tunnelId, UE_IP, Constants.SINK_IP, sgw_ip);
//	}
//
//	// Method for installing uplink rule
//	private synchronized void installFlowRule(IOFSwitch sw, DatapathId dpId, int inPort, int inTunnelId, int outPort, int outTunnelId, String srcIP, String dstIP){
//		if(Constants.DEBUG){
//			System.out.println("switchService "+ switchService + " dpId "+ dpId);
//		}
//		OFFlowMod.Builder fmb = sw.getOFFactory().buildFlowAdd();
//		Match.Builder mb = sw.getOFFactory().buildMatch();
//
//		mb.setExact(MatchField.ETH_TYPE, EthType.IPv4)
//		.setExact(MatchField.IN_PORT, OFPort.of(inPort))
//		.setExact(MatchField.IPV4_SRC, IPv4Address.of(srcIP))
//		.setExact(MatchField.VLAN_VID, OFVlanVidMatch.ofVlanVid(VlanVid.ofVlan(inTunnelId)));
//
//		List<OFAction> actions = new ArrayList<OFAction>();
//		actions.add(sw.getOFFactory().actions().stripVlan());//outTunnelId
//		if(dstIP != "")
//			actions.add(sw.getOFFactory().actions().setNwDst(IPv4Address.of(dstIP)));
//
//		actions.add(sw.getOFFactory().actions().output(OFPort.of(outPort), Integer.MAX_VALUE)); // FLOOD is a more selective/efficient version of ALL
//		fmb.setActions(actions);
//
//		fmb.setHardTimeout(0)
//		.setIdleTimeout(0)
//		.setPriority(1)
//		.setBufferId(OFBufferId.NO_BUFFER)
//		.setMatch(mb.build());
//
//		boolean x = sw.write(fmb.build());
//		if(!x){
//			System.out.println("********************LO JI HO GAYI GADBAD!!!!!! pgw install mein**********************");
//			System.exit(0);
//		}
//		/*try {
//			Thread.sleep(1);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}*/
//	}
//
//	// Method for installing downlink rule
//	private synchronized void installFlowRuleWithIP(IOFSwitch sw, DatapathId dpId, int inPort, int outPort, int outTunnelId, String UE_IP, String sink_ip, String sgw_ip){
//		if(Constants.DEBUG){
//			System.out.println("switchService "+ switchService + " dpId "+ dpId);
//		}
//
//		OFFlowMod.Builder fmb = sw.getOFFactory().buildFlowAdd();
//		Match.Builder mb = sw.getOFFactory().buildMatch();
//
//		mb.setExact(MatchField.ETH_TYPE, EthType.IPv4)
//		.setExact(MatchField.IN_PORT, OFPort.of(inPort))
//		.setExact(MatchField.IPV4_DST, IPv4Address.of(UE_IP));
//
//		List<OFAction> actions = new ArrayList<OFAction>();
//		actions.add(sw.getOFFactory().actions().setVlanVid(VlanVid.ofVlan(outTunnelId)));
//		actions.add(sw.getOFFactory().actions().setNwDst(IPv4Address.of(sgw_ip)));
//		actions.add(sw.getOFFactory().actions().output(OFPort.of(outPort), Integer.MAX_VALUE)); // FLOOD is a more selective/efficient version of ALL
//		fmb.setActions(actions);
//
//		fmb.setHardTimeout(0)
//		.setIdleTimeout(0)
//		.setPriority(1)
//		.setBufferId(OFBufferId.NO_BUFFER)
//		.setMatch(mb.build());
//
//		boolean x = sw.write(fmb.build());
//		if(!x){
//			System.out.println("********************LO JI HO GAYI GADBAD!!!!!! pgw install ip mein**********************");
//			System.exit(0);
//		}
//		/*try {
//			Thread.sleep(1);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}*/
//	}

//	@Override
//	public Collection<Class<? extends IFloodlightService>> getModuleServices() {
//		// TODO Auto-generated method stub
//		return null;
//	}
//
//	@Override
//	public Map<Class<? extends IFloodlightService>, IFloodlightService> getServiceImpls() {
//		// TODO Auto-generated method stub
//		return null;
//	}
//
//	@Override
//	public Collection<Class<? extends IFloodlightService>> getModuleDependencies() {
//		// TODO Auto-generated method stub
//		return null;
//	}
//
//	@Override
//	public void init(FloodlightModuleContext context)
//			throws FloodlightModuleException {
//		switchService = context.getServiceImpl(IOFSwitchService.class);
//
//	}
//
//	@Override
//	public void startUp(FloodlightModuleContext context)
//			throws FloodlightModuleException {
//		// TODO Auto-generated method stub
//	}
}
