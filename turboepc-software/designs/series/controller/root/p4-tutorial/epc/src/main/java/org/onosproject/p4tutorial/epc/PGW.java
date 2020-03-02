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
	ConcurrentLinkedQueue reuseable_teids = new ConcurrentLinkedQueue<Integer>();

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
	
	public String returnStartingIPAddress(String sw){
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
	public synchronized String allocateIPForUE(ApplicationId appId,FlowRuleService flowRuleService, int sgw_tunnelId, String sgw_dpId, String pgw_dpId, String apn){
		int pgw_teid;
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
					log.warn("PGW reusing IP = {}",ip);
					log.warn(" numips = ",numIps);
				}
			}
		} catch (Exception e) {
			log.info("some stacktrace");
		}

		if(Constants.DEBUG){
			log.warn("P GW TUNNEL ID of UE = {}",apn);
            log.warn(" is = {}",pgw_teid);
		}
		String dgw_dp_id_temp = Constants.getDgwDpid(sgw_dpId);
		//@not needed
		//install uplink and downlink rules
        /********************  Uplink rule is installed on PGW (PGW to sink) *************************/
		DeviceId pgwSwitchName = Constants.PGW_NAME;

		fr.insertUplinkTunnelForwardRule(false,appId, flowRuleService,pgwSwitchName,pgw_teid, pgw_sink_port,0,true);

		/********************  Downlink rule is installed on PGW (sink to PGW) *************************/


		byte[] UE_IPAddr = IPv4.toIPv4AddressBytes(ip[chainId]);
		if(Constants.DEBUG) {
			log.warn("PGW reusing IP = {}", ip[chainId]);
			log.warn("IP rule ############## {}", UE_IPAddr);
		}

        /* DOWNLINK => ipv4srcAddr = Sink IP and ipv4dstAddr = UE IP   */
		fr.insertUplinkTunnelIngressRule(false,appId,flowRuleService,pgwSwitchName,Constants.dstSinkIpAddr,UE_IPAddr,sgw_tunnelId,Constants.PGW_SGW_PORT_MAP.get(pgw_dpId + Constants.SEPARATOR + sgw_dpId));

		return ip[chainId] + Constants.SEPARATOR + pgw_teid;
	}

	/************* this method deletes uplink and downlink flow rules from PGW-D *******************/
	public boolean detachUEFromPGW(ApplicationId appId,FlowRuleService flowRuleService,String sgw_dpId, String pgw_dpId, int pgw_teid, String ue_ip){
		int S_P_inPort = Constants.PGW_SGW_PORT_MAP.get(pgw_dpId + Constants.SEPARATOR + sgw_dpId);
		//delete uplink rule
		int chainId = Constants.getChainIDFromSGW(sgw_dpId);
		/******************** Remove  Uplink rule is installed on PGW (PGW to sink) *************************/
		DeviceId pgwSwitchName = Constants.PGW_NAME;

		int pgw_sink_port = 0 ; // dont need outPort while deleting flow rule
		fr.insertUplinkTunnelForwardRule(true,appId, flowRuleService,pgwSwitchName,pgw_teid, pgw_sink_port,0,true);

		if(Constants.DEBUG){
			log.warn(" TBD : PGW deleting uplink rule with PGW TEID = {}",pgw_teid);
			log.warn(" inPort = {}",S_P_inPort);
			log.warn(" for UE with IP = {}",ue_ip);
		}

		//delete downlink rule
		/********************  Remove Downlink rule is installed on PGW (sink to PGW) *************************/
		byte[] UE_IPAddr = IPv4.toIPv4AddressBytes(ue_ip);
		int sgw_tunnelId = 0; // dont need sgw_tunnelId while deleting flow rule

        /* DOWNLINK => ipv4srcAddr = Sink IP and ipv4dstAddr = UE IP   */
		fr.insertUplinkTunnelIngressRule(true,appId,flowRuleService,pgwSwitchName,Constants.dstSinkIpAddr,UE_IPAddr,sgw_tunnelId,Constants.PGW_SGW_PORT_MAP.get(pgw_dpId + Constants.SEPARATOR + sgw_dpId));

		if(Constants.DEBUG){
			log.warn(" TBD : PGW deleting downlink rule with PGW TEID = {}",pgw_teid);
			log.warn(" inPort = {}",pgw_sink_port);
			log.warn(" for UE with IP = {}",ue_ip);
		}

		reusable_ips[chainId].add(ue_ip);
		reuseable_teids.add(pgw_teid);

		return true;
	}

}
