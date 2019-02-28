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
	String contactPGW(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,String sgw_dpId, String pgw_dpId, String apn){
		String dgwId = Constants.getDgwDpid(sgw_dpId);
		String []tmpArray = null;
		int pgw_teid, sgw_teid;
		//code for reusing the used tunnel ids. Because we only have 4000 available
		int chainId = Constants.getChainIDFromSGW(sgw_dpId);
		/*************************** for now we dont need synchronisation as issue is fixed ****************************/
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


		if(Constants.DEBUG){
			log.warn("PGATEWAY="+pgw_dpId);
			log.warn("S GW TUNNEL ID of UE {}",apn);
			log.warn(" is {}",sgw_teid);
		}
		// contacting pgw to allocate an ip address for UE. PGW_C also provides its tunnel endpoint identifier to SGW_C.
		String ip_pgw = pg.allocateIPForUE(appId,flowRuleService,sgw_teid, sgw_dpId, pgw_dpId,  apn);
		//ip_pgw format is UE_IP_ADDRESS + SEPARATOR + PGW tunnel ID for this UE

		tmpArray = ip_pgw.split(Constants.SEPARATOR); // tmpArray[0] => IP for UE. tmpArray[1] => PGW tunnel ID for this UE

		//uplink rule (SGW to PGW)
		if(Constants.MYDEBUG1){

			log.warn("SGW installing uplink rule on S-GW dpid = {}",sgw_dpId);
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

		// tmpArray[0] => IP for UE
		return tmpArray[0] + Constants.SEPARATOR + sgw_teid;
	}

	/*
	 * This method installs the downlink flow rule between SGW-D and default switch after knowing the UE generated tunnel for default switch
	 */
	public void modifyBearerRequest(ApplicationId appId,FlowRuleService flowRuleService,DeviceId SGWswitchId,String sgw, String sgw_dpId, int sgw_teId, int ue_teId, String key){
		if(Constants.DEBUG){
			log.warn("teid = {}",ue_teId);
			//downlink rule (SGW to ENodeB)

			log.warn("---------------------------------------SGW installing downlink rule on S-GW dpid = {}",sgw_dpId);
			log.warn(" inport = {}",Constants.SGW_PORT_MAP.get(sgw_dpId)[1]);
			log.warn(" in teid = {}",sgw_teId);
			log.warn(" outPort = {}",Constants.SGW_PORT_MAP.get(sgw_dpId)[0]);
			log.warn(" out teid = {}",ue_teId);
			log.warn(" of UE key = {}",key);
		}

		/******************************** Downlink flow rules on SGW (SGW to DGW) **************************************/
			fr.insertDownlinkTunnelForwardRule(false,appId,flowRuleService,SGWswitchId,sgw_teId,Constants.SGW_PORT_MAP.get(sgw_dpId)[0],ue_teId);
			

	}

	/*
	 * This is a utility method requiring to know the starting IP address PGW-C will be using.
	 * This method is needed so that we can preallocate the IP addresses that will be used in this 
	 * experiment onto the interface of UE machine. This is to avoid wasting time and CPU on this later
	 * that is, during the main experiment.
	 */

	public String getStartingIPAddress(String sw){
		return pg.returnStartingIPAddress(sw);
	}

	/******This method detaches the tunnel between SGW-D and default switch, by deleting the uplink and downlink rules on SGW-D *****/
	public boolean detachUEFromSGW(ApplicationId appId,FlowRuleService flowRuleService,DeviceId SGWswitchId,String sgw_dpId, String pgw_dpId, int sgw_teid, String ue_ip) {

			int pgw_teid=0;
			String dgwId = Constants.getDgwDpid(sgw_dpId);
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
			if(Constants.MYDEBUG) {
					log.warn(" in detachUEFromSGW del");
			}
			FT.del(Integer.parseInt(Constants.DETACH_REQUEST),dgwId, "SGW_PGW_TEID_MAP", String.valueOf(sgw_teid));   // TODO

			//delete uplink rule
			/***********************************delete uplink flow rule on Transit SGW( SGW -> PGW) *********************************************/
			/*******************while deleting we only need match field confirm??????????????***************************************/

			fr.insertUplinkTunnelForwardRule(true,appId,flowRuleService,SGWswitchId,sgw_teid,Constants.SGW_PORT_MAP.get(sgw_dpId)[1],pgw_teid,false);

			if(Constants.DEBUG){
				log.warn(" SGW deleting uplink rule with PGW TEID = {}",pgw_teid);
				log.warn(" for UE with IP = {}",ue_ip);
			}

			/*****************************delete downlink flow rule on Transit SGW( SGW -> DGW)**************************************************/
			int ue_teId = 0; // we dont need action parameters while deleting flow rules
			fr.insertDownlinkTunnelForwardRule(true,appId,flowRuleService,SGWswitchId,sgw_teid,Constants.SGW_PORT_MAP.get(sgw_dpId)[0],ue_teId);

			if(Constants.DEBUG){
				log.warn(" SGW deleting downlink rule with SGW TEID = {}",sgw_teid);
				log.warn(" for UE with IP = {}",ue_ip);
			}
			int chainId = Constants.getChainIDFromSGW(sgw_dpId);
			reusable_teids[chainId].add(sgw_teid);

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

		if(Constants.DEBUG){
			log.info("SGW deleting downlink rule with SGW TEID = {} for UE with IP = {}",sgw_teid,ue_ip);
		}
	}
}

