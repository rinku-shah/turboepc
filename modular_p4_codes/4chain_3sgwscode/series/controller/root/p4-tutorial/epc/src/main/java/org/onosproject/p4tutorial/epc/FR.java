/***********************************************************************
 * This file contains methods to install flow rules on simple_switch_grpc  *
 ***********************************************************************/

package org.onosproject.p4tutorial.epc;

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

import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;

public class FR{
    private static final Logger log = getLogger(EpcApp.class);

    /*********************************************** INSERT FLOW RULES ****************************************************/
    /**
     * Generates and insert a flow rule to perform the tunnel INGRESS function
     * for the given switch, destination IP address and tunnel ID.
     *
     * @param switchId  switch ID
     * @param dstIpAddr IP address to forward inside the tunnel
     * @param tunId     tunnel ID
     */

     /**************************** @offload ***********************/

     public void populate_uekey_sgwteid_map(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int ue_key, int sgw_teid){

        PiTableId tunnelIngressTableId = PiTableId.of("c_ingress.service_req_uekey_sgwteid_map");
        PiMatchFieldId ueKeyFieldId = PiMatchFieldId.of("hdr.ue_service_req.ue_key");
        PiCriterion match = PiCriterion.builder()
                .matchExact(ueKeyFieldId, ue_key)
                .build();

        PiActionId ingressActionId = PiActionId.of("c_ingress.populate_service_req_uekey_sgwteid_map");
        PiActionParam sgwTeidParam = new PiActionParam(PiActionParamId.of("sgwteid"), sgw_teid);

        PiAction action = PiAction.builder()
                .withId(ingressActionId)
                .withParameter(sgwTeidParam)
                .build();

        if(Constants.FRDEBUG){
            log.info("populate_service_req_uekey_sgwteid_map rule on switch {}: table={}, match={}, action={}",
                    switchId, tunnelIngressTableId, match, action);
            }
       
        if (removeRule) {
            removePiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
        }
        else{
            insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
        }

        tunnelIngressTableId = PiTableId.of("c_ingress.ctxt_setup_uekey_sgwteid_map");
        ueKeyFieldId = PiMatchFieldId.of("hdr.initial_ctxt_setup_resp.ue_key");
        match = PiCriterion.builder()
                .matchExact(ueKeyFieldId, ue_key)
                .build();

        ingressActionId = PiActionId.of("c_ingress.populate_ctxt_setup_uekey_sgwteid_map");
        sgwTeidParam = new PiActionParam(PiActionParamId.of("sgwteid"), sgw_teid);

        action = PiAction.builder()
                .withId(ingressActionId)
                .withParameter(sgwTeidParam)
                .build();

        if(Constants.FRDEBUG){
            log.info("populate_uekey_uestate_map rule on switch {}: table={}, match={}, action={}",
                    switchId, tunnelIngressTableId, match, action);
            }
        if (removeRule) {
            removePiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
        }
        else{
            insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
        }

         tunnelIngressTableId = PiTableId.of("c_egress.ctxt_release_uekey_sgwteid_map");
         ueKeyFieldId = PiMatchFieldId.of("hdr.ue_service_req.ue_key");
         match = PiCriterion.builder()
                 .matchExact(ueKeyFieldId, ue_key)
                 .build();

         ingressActionId = PiActionId.of("c_egress.populate_ctxt_release_uekey_sgwteid_map");
         sgwTeidParam = new PiActionParam(PiActionParamId.of("sgwteid"), sgw_teid);
         action = PiAction.builder()
                 .withId(ingressActionId)
                 .withParameter(sgwTeidParam)
                 .build();
         if(Constants.FRDEBUG){
             log.info("populate_ctxt_release_uekey_sgwteid_map rule on switch {}: table={}, match={}, action={}",
                     switchId, tunnelIngressTableId, match, action);
         }
         if (removeRule) {
             removePiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
         }
         else{
             insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
         }

        }
     public void populate_lookup_if_tables(boolean removeRule,int lookup_flag,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int ue_key){

    // ******************************************************   LOOKUP TBALES for if statements **************************************************

         //lookup_flag tells which tables to be populated either lb1_ub1 tables or lb2_ub2 tables
        if(lookup_flag==1){

            PiTableId tunnelIngressTableId = PiTableId.of("c_ingress.uekey_lookup_lb1_ub1");
            PiMatchFieldId ueKeyFieldId = PiMatchFieldId.of("meta.metakey");
            PiCriterion match = PiCriterion.builder()
                    .matchExact(ueKeyFieldId, ue_key)
                    .build();
            
            // invoking default action which is NoAction()

            PiActionId ingressActionId = PiActionId.of("NoAction");

            PiAction action = PiAction.builder()
                    .withId(ingressActionId)
                    .build();

            if (removeRule) {
                removePiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
            }
            else{
                insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
            }
        }


        else if(lookup_flag==2){

            PiTableId tunnelIngressTableId = PiTableId.of("c_ingress.uekey_lookup_lb2_ub2");
            PiMatchFieldId ueKeyFieldId = PiMatchFieldId.of("meta.metakey");
            PiCriterion match = PiCriterion.builder()
                    .matchExact(ueKeyFieldId, ue_key)
                    .build();

            //invoking default action which is NoAction()
            PiActionId ingressActionId = PiActionId.of("NoAction");

            PiAction action = PiAction.builder()
                    .withId(ingressActionId)
                    .build();

            if (removeRule) {
                removePiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
            }
            else{
                insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
            }
        }
 
        else if(lookup_flag==3){

            PiTableId tunnelIngressTableId = PiTableId.of("c_ingress.uekey_lookup_lb3_ub3");
            PiMatchFieldId ueKeyFieldId = PiMatchFieldId.of("meta.metakey");
            PiCriterion match = PiCriterion.builder()
                    .matchExact(ueKeyFieldId, ue_key)
                    .build();

            //invoking default action which is NoAction()
            PiActionId ingressActionId = PiActionId.of("NoAction");

            PiAction action = PiAction.builder()
                    .withId(ingressActionId)
                    .build();

            if (removeRule) {
                removePiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
            }
            else{
                insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
            }
        }

                  
     }


     public void populate_uekey_uestate_map(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int ue_key, int ue_state){

        PiTableId tunnelIngressTableId = PiTableId.of("c_ingress.uekey_uestate_map");
        PiMatchFieldId ueKeyFieldId = PiMatchFieldId.of("hdr.uekey_uestate.ue_key");
        PiCriterion match = PiCriterion.builder()
                .matchExact(ueKeyFieldId, ue_key)
                .build();

        PiActionId ingressActionId = PiActionId.of("c_ingress.populate_uekey_uestate_map");
        PiActionParam ueStateParam = new PiActionParam(PiActionParamId.of("uestate"), ue_state);

        PiAction action = PiAction.builder()
                .withId(ingressActionId)
                .withParameter(ueStateParam)
                .build();

        if(Constants.FRDEBUG){
            log.info("populate_uekey_uestate_map rule on switch {}: table={}, match={}, action={}",
                    switchId, tunnelIngressTableId, match, action);
            }
       
        insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
     }

     public void populate_uekey_guti_map(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int ue_key, int guti){

        PiTableId tunnelIngressTableId = PiTableId.of("c_ingress.uekey_guti_map");
        PiMatchFieldId ueKeyFieldId = PiMatchFieldId.of("hdr.uekey_guti.ue_key");
        PiCriterion match = PiCriterion.builder()
                .matchExact(ueKeyFieldId, ue_key)
                .build();

        PiActionId ingressActionId = PiActionId.of("c_ingress.populate_uekey_guti_map");
        PiActionParam gutiParam = new PiActionParam(PiActionParamId.of("guti"), guti);

        PiAction action = PiAction.builder()
                .withId(ingressActionId)
                .withParameter(gutiParam)
                .build();

        if(Constants.FRDEBUG){
            log.info("populate_uekey_uestate_map rule on switch {}: table={}, match={}, action={}",
                    switchId, tunnelIngressTableId, match, action);
            }
       
        insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
     }

    /* UPLINK   => ipv4srcAddr = UE IP and ipv4dstAddr = Sink IP   */
    /* DOWNLINK => ipv4srcAddr = Sink IP and ipv4dstAddr = UE IP   */
    public void insertUplinkTunnelIngressRule(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,byte[] srcIpAddr,byte[] dstIpAddr, int tunId, int outPort) {

        PiTableId tunnelIngressTableId = PiTableId.of("c_ingress.ip_op_tun_s1_uplink");
        // Longest prefix match on IPv4 dest address.
        PiMatchFieldId ipSrcMatchFieldId = PiMatchFieldId.of("hdr.ipv4.srcAddr");
        PiMatchFieldId ipDestMatchFieldId = PiMatchFieldId.of("hdr.ipv4.dstAddr");
        PiCriterion match = PiCriterion.builder()
//				.matchLpm(ipDestMatchFieldId, dstIpAddr.toOctets(), 32)
                .matchExact(ipSrcMatchFieldId, srcIpAddr)
                // .matchLpm(ipDestMatchFieldId, dstIpAddr, 32)
                .matchExact(ipDestMatchFieldId, dstIpAddr)
                .build();

        PiActionParam tunIdParam = new PiActionParam(PiActionParamId.of("op_tunnel_s1"), tunId);
        PiActionParam portIdParam = new PiActionParam(PiActionParamId.of("egress_port_s1"), outPort);


        PiActionId ingressActionId = PiActionId.of("c_ingress.populate_ip_op_tun_s1_uplink");
        PiAction action = PiAction.builder()
                .withId(ingressActionId)
                .withParameter(tunIdParam)
                .withParameter(portIdParam)
                .build();
        if(Constants.FRDEBUG){
            log.info("{} INGRESS rule on switch {}: table={}, match={}, action={}",
                     removeRule ? "REMOVING" : "INSERTING" ,switchId, tunnelIngressTableId, match, action);
            }
        if(removeRule){
            removePiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
        }
        else{
            insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
        }
    }

    /**
     * Generates and insert a flow rule to perform the tunnel FORWARD/EGRESS
     * function for the given switch, output port address and tunnel ID.
     *
     * @param switchId switch ID
     * @param outPort  output port where to forward tunneled packets
     * @param tunId    tunnel ID
     * @param isEgress if true, perform tunnel egress action, otherwise forward
     *                 packet as is to port
     */
    public void insertUplinkTunnelForwardRule(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int intunId,int outPort,int outtunId,boolean isEgress) {

        PiTableId tunnelForwardTableId = PiTableId.of("c_ingress.ip_op_tun_s2_uplink");

        // Exact match on tun_id
        // PiMatchFieldId tunIdMatchFieldId = PiMatchFieldId.of("hdr.vlan.vid");
        PiMatchFieldId tunIdMatchFieldId = PiMatchFieldId.of("hdr.gtpu.teid");
        PiCriterion match = PiCriterion.builder()
                .matchExact(tunIdMatchFieldId, intunId)
                .build();

        // Action depend on isEgress parameter.
        // if true, perform tunnel egress action on the given outPort, otherwise
        // simply forward packet as is (set_out_port action).
        PiActionParamId portParamId = PiActionParamId.of("egress_port_s2");
        PiActionParam portParam = new PiActionParam(portParamId,  outPort);

        PiActionParamId outtunParamId = PiActionParamId.of("op_tunnel_s2");
        PiActionParam outtunParam = new PiActionParam(outtunParamId, outtunId);

        final PiAction action;
        if (isEgress) {

            PiTableId egresstunnelForwardTableId = PiTableId.of("c_ingress.tun_egress_s3_uplink");

            PiActionParamId egressportParamId = PiActionParamId.of("egress_port_s3");
            PiActionParam egressportParam = new PiActionParam(egressportParamId,  outPort);
            // Tunnel egress action.
            // Remove MyTunnel header and forward to outPort.
            PiActionId egressActionId = PiActionId.of("c_ingress.populate_tun_egress_s3_uplink");
            action = PiAction.builder()
                    .withId(egressActionId)
                    .withParameter(egressportParam)
                    .build();
            if(Constants.FRDEBUG) {
                log.info("{} {} rule on switch {}: table={}, match={}, action={}",
                         removeRule ? "REMOVING" : "INSERTING", isEgress ? "EGRESS" : "TRANSIT",
                         switchId, egresstunnelForwardTableId, match, action);
            }
            if(removeRule){
                removePiFlowRule(appId,flowRuleService,switchId, egresstunnelForwardTableId, match, action);
            }
            else{
                insertPiFlowRule(appId,flowRuleService,switchId, egresstunnelForwardTableId, match, action);
            }

        } else {
            // Tunnel transit action.
            // Forward the packet as is to outPort.
            PiActionId egressActionId = PiActionId.of("c_ingress.populate_ip_op_tun_s2_uplink");
            action = PiAction.builder()
                    .withId(egressActionId)
                    .withParameter(outtunParam)
                    .withParameter(portParam)
                    .build();
            if(Constants.FRDEBUG) {
                log.info("{} {} rule on switch {}: table={}, match={}, action={}",
                         removeRule ? "REMOVING" : "INSERTING", isEgress ? "EGRESS" : "TRANSIT",
                         switchId, tunnelForwardTableId, match, action);
            }

            if (removeRule) {
                removePiFlowRule(appId, flowRuleService, switchId, tunnelForwardTableId, match, action);
            } else {
                insertPiFlowRule(appId, flowRuleService, switchId, tunnelForwardTableId, match, action);
            }
        }


    }

    public void insertDownlinkTunnelForwardRule(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int intunId,int outPort,int outtunId) {

        PiTableId tunnelForwardTableId = PiTableId.of("c_ingress.ip_op_tun_s2_downlink");
    
        // Exact match on tun_id
        // PiMatchFieldId tunIdMatchFieldId = PiMatchFieldId.of("hdr.vlan.vid");
        PiMatchFieldId tunIdMatchFieldId = PiMatchFieldId.of("hdr.gtpu.teid");
    
        PiCriterion match = PiCriterion.builder()
                .matchExact(tunIdMatchFieldId, intunId)
                .build();
    
        // Action depend on isEgress parameter.
        // if true, perform tunnel egress action on the given outPort, otherwise
        // simply forward packet as is (set_out_port action).
        PiActionParamId portParamId = PiActionParamId.of("egress_port_s2");
        PiActionParam portParam = new PiActionParam(portParamId,  outPort);
    
        PiActionParamId outtunParamId = PiActionParamId.of("op_tunnel_s2");
        PiActionParam outtunParam = new PiActionParam(outtunParamId, outtunId);
        final PiAction action;
      
        // Tunnel transit action.
        // Forward the packet as is to outPort.
        PiActionId egressActionId = PiActionId.of("c_ingress.populate_ip_op_tun_s2_downlink");
        action = PiAction.builder()
                .withId(egressActionId)
                .withParameter(outtunParam)
                .withParameter(portParam)
                .build();
        if(Constants.FRDEBUG) {
            log.info("{} {} rule on switch {}: table={}, match={}, action={}",
                    removeRule ? "REMOVING" : "INSERTING",  "TRANSIT",
                    switchId, tunnelForwardTableId, match, action);
        }
        if (removeRule) {
            removePiFlowRule(appId, flowRuleService, switchId, tunnelForwardTableId, match, action);
        } else {
            insertPiFlowRule(appId, flowRuleService, switchId, tunnelForwardTableId, match, action);
        }
    }
    /**
     * Inserts a flow rule in the system that using a PI criterion and action.
     *
     * @param switchId    switch ID
     * @param tableId     table ID
     * @param piCriterion PI criterion
     * @param piAction    PI action
     */
    private void insertPiFlowRule(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId, PiTableId tableId,
                                  PiCriterion piCriterion, PiAction piAction) {
        FlowRule rule = DefaultFlowRule.builder()
                .forDevice(switchId)
                .forTable(tableId)
                .fromApp(appId)
                .withPriority(Constants.FLOW_RULE_PRIORITY)
                .makePermanent()
                .withSelector(DefaultTrafficSelector.builder()
                                      .matchPi(piCriterion).build())
                .withTreatment(DefaultTrafficTreatment.builder()
                                       .piTableAction(piAction).build())
                .build();
        flowRuleService.applyFlowRules(rule);
    }

    /*********************************************** REMOVE FLOW RULES ****************************************************/


    /**
     * Removes a flow rule in the system that using a PI criterion and action.
     *
     * @param switchId    switch ID
     * @param tableId     table ID
     * @param piCriterion PI criterion
     * @param piAction    PI action
     */

    private void removePiFlowRule(ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId, PiTableId tableId,
                                  PiCriterion piCriterion, PiAction piAction) {

        FlowRule rule = DefaultFlowRule.builder()
                .forDevice(switchId)
                .forTable(tableId)
                .fromApp(appId)
                .withPriority(Constants.FLOW_RULE_PRIORITY)
                .makePermanent()
                .withSelector(DefaultTrafficSelector.builder()
                                      .matchPi(piCriterion).build())
                .withTreatment(DefaultTrafficTreatment.builder()
                                       .piTableAction(piAction).build())
                .build();
        flowRuleService.removeFlowRules(rule);
    }

}

/******************************************************************** EXTRA ****************************************************************/
// public void insertDownlinkTunnelIngressRule(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,byte[] dstIpAddr, int tunId, int outPort) {

//     PiTableId tunnelIngressTableId = PiTableId.of("c_ingress.ip_op_tun_s3_downlink");

//     // Longest prefix match on IPv4 dest address.
//     PiMatchFieldId ipDestMatchFieldId = PiMatchFieldId.of("hdr.ipv4.dstAddr");
//     PiCriterion match = PiCriterion.builder()
// //				.matchLpm(ipDestMatchFieldId, dstIpAddr.toOctets(), 32)
//             .matchLpm(ipDestMatchFieldId, dstIpAddr, 32)
//             .build();

//     PiActionParam tunIdParam = new PiActionParam(PiActionParamId.of("op_tunnel_s3"), tunId);
//     PiActionParam portIdParam = new PiActionParam(PiActionParamId.of("egress_port_s3"), outPort);


//     PiActionId ingressActionId = PiActionId.of("c_ingress.populate_ip_op_tun_s3_downlink");
//     PiAction action = PiAction.builder()
//             .withId(ingressActionId)
//             .withParameter(tunIdParam)
//             .withParameter(portIdParam)
//             .build();
//     if(Constants.FRDEBUG) {
//         log.info("{} INGRESS rule on switch {}: table={}, match={}, action={}",
//                  removeRule ? "REMOVING" : "INSERTING", switchId, tunnelIngressTableId, match, action);
//     }

//     if(removeRule){
//         removePiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
//     }
//     else{
//         insertPiFlowRule(appId,flowRuleService,switchId, tunnelIngressTableId, match, action);
//     }
// }



// public void insertDownlinkTunnelForwardRule(boolean removeRule,ApplicationId appId,FlowRuleService flowRuleService,DeviceId switchId,int intunId,int outPort,int outtunId,boolean isEgress) {

//     PiTableId tunnelForwardTableId = PiTableId.of("c_ingress.ip_op_tun_s2_downlink");

//     // Exact match on tun_id
//     // PiMatchFieldId tunIdMatchFieldId = PiMatchFieldId.of("hdr.vlan.vid");
//     PiMatchFieldId tunIdMatchFieldId = PiMatchFieldId.of("hdr.gtpu.teid");

//     PiCriterion match = PiCriterion.builder()
//             .matchExact(tunIdMatchFieldId, intunId)
//             .build();

//     // Action depend on isEgress parameter.
//     // if true, perform tunnel egress action on the given outPort, otherwise
//     // simply forward packet as is (set_out_port action).
//     PiActionParamId portParamId = PiActionParamId.of("egress_port_s2");
//     PiActionParam portParam = new PiActionParam(portParamId,  outPort);

//     PiActionParamId outtunParamId = PiActionParamId.of("op_tunnel_s2");
//     PiActionParam outtunParam = new PiActionParam(outtunParamId, outtunId);




//     final PiAction action;
//     if (isEgress) {

//         PiTableId egresstunnelForwardTableId = PiTableId.of("c_ingress.tun_egress_s1_downlink");

//         PiActionParamId egressportParamId = PiActionParamId.of("egress_port_s1");
//         PiActionParam egressportParam = new PiActionParam(egressportParamId,  outPort);
//         // Tunnel egress action.
//         // Remove MyTunnel header and forward to outPort.
//         PiActionId egressActionId = PiActionId.of("c_ingress.populate_tun_egress_s1_downlink");
//         action = PiAction.builder()
//                 .withId(egressActionId)
//                 .withParameter(egressportParam)
//                 .build();
//         if(Constants.FRDEBUG) {
//             log.info("{} {} rule on switch {}: table={}, match={}, action={}",
//                      removeRule ? "REMOVING" : "INSERTING", isEgress ? "EGRESS" : "TRANSIT",
//                      switchId, egresstunnelForwardTableId, match, action);
//         }
//         if (removeRule) {
//             removePiFlowRule(appId, flowRuleService, switchId, egresstunnelForwardTableId, match, action);
//         } else {
//             insertPiFlowRule(appId, flowRuleService, switchId, egresstunnelForwardTableId, match, action);
//         }

//     } else {
//         // Tunnel transit action.
//         // Forward the packet as is to outPort.
//         PiActionId egressActionId = PiActionId.of("c_ingress.populate_ip_op_tun_s2_downlink");
//         action = PiAction.builder()
//                 .withId(egressActionId)
//                 .withParameter(portParam)
//                 .withParameter(outtunParam)
//                 .build();
//         if(Constants.FRDEBUG) {
//             log.info("{} {} rule on switch {}: table={}, match={}, action={}",
//                      removeRule ? "REMOVING" : "INSERTING", isEgress ? "EGRESS" : "TRANSIT",
//                      switchId, tunnelForwardTableId, match, action);
//         }

//         if (removeRule) {
//             removePiFlowRule(appId, flowRuleService, switchId, tunnelForwardTableId, match, action);
//         } else {
//             insertPiFlowRule(appId, flowRuleService, switchId, tunnelForwardTableId, match, action);
//         }
//     }

// }

