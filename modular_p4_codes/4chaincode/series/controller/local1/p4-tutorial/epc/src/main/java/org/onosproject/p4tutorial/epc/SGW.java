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
	FR fr = new FR();
	private static final Logger log = getLogger(EpcApp.class);

	int tunnelId[] = {1,683,1365,2047,2729,3411};
	static int maxTeid[] = {682,1364,2046,2728,3410,4095};
	static int minTeid[] = {1,683,1365,2047,2729,3411};
	
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
	 * This method installs the downlink flow rule between SGW-D and default switch after knowing the UE generated tunnel for default switch
	 */
	public void modifyBearerRequest(ApplicationId appId,FlowRuleService flowRuleService,DeviceId SGWswitchId,String sgw, String sgw_dpId, int sgw_teId, int ue_teId, String key){
		if(Constants.DEBUG){
			log.warn("teid = {}",ue_teId);
			//downlink rule (SGW to ENodeB)
			log.warn("SGW installing downlink rule on S-GW dpid = {}",sgw_dpId);
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

