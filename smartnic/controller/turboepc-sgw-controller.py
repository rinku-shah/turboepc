from scapy.all import *
import argparse
import time
import threading
from threading import Event

from RTEInterface import RTEInterface

THRIFT_API_LOCK = threading.Lock()

class TimerThread(threading.Thread):
    def __init__(self, event, rule_timeout, internal_ports):
        threading.Thread.__init__(self)
        self.stopped = event
        self.rule_timeout = rule_timeout
        self.internal_ports = internal_ports

    def run(self):
        while not self.stopped.wait(self.rule_timeout):
            #print("Timeout poll")

            with THRIFT_API_LOCK:
                counterList = RTEInterface.Counters.ListP4Counters()
                tableId = counterList[0].tableid # Only have 1 table with counters in this example (Hardcoded 0)
                ruleList = RTEInterface.Tables.ListRules(tableId)
                counterValueList = []

                for i in range(self.internal_ports + 2,len(ruleList)):
                     #print(ruleList[i].rule_name)
                    try:
                        counterValueList.append(RTEInterface.Counters.GetP4Counter(counterList[0])[i])
                        if RTEInterface.Counters.GetP4Counter(counterList[0])[i] == 0:
                            #print("Deleting rule: " + ruleList[i].rule_name)
                            RTEInterface.Tables.DeleteRule(tableId, ruleList[i].rule_name, False, "{}", "{}")
                            # time.sleep(0.01)
                    except:
                        print("Error trying to append counter value")

                #print(counterValueList)
                RTEInterface.Counters.ClearAllP4Counters()

class FuncThread(threading.Thread):
    def __init__(self, target, *args):
        self._target = target
        self._args = args
        threading.Thread.__init__(self)

    def run(self):
        self._target(*self._args)


class Data(Packet):
	name = "Data"
	#ShortFeild('ingress_port', None), #controller-header ..CPU-port ... Followed by ETH/IP/UDP/DATA
	fields_desc = [	ByteField("epc_traffic_code", None), #14:UE_Context_Release_Req, 17:UE_Service_Req, 19:Initial_Ctxt_Setup_Resp
							IntField("sep1", None),
							ShortField('sep2', None),
							IntField("param1", None), #ue_ip/ue_key/ue_teid
							IntField("sep11", None),
							ShortField('sep12', None), #2bytes
							IntField("param2", None), #ue_teid/ksi_asme/ue_key
							IntField("sep21", None),
							ShortField('sep22', None), #2bytes
							IntField("param3", None), #sgw_teid/ue_ip/ue_ip
							IntField("sep31", None),
							ShortField('sep32', None), #2bytes
							IntField("param4", None)] #ue_num/sgw_teid/sgw_teid

class UE_Context_Release_Req(Packet):
	name = "UE_Context_Release_Req"
	fields_desc = [	IntField("ue_ip", None),
							IntField("sep11", None),
							ShortField('sep12', None), #2bytes
							IntField("ue_teid", None),
							IntField("sep21", None),
							ShortField('sep22', None), #2bytes
							IntField("sgw_teid", None),
							IntField("sep31", None),
							ShortField('sep32', None), #2bytes
							IntField("ue_num", None)]

class UE_Service_Req(Packet):
	name = "UE_Service_Req"
	fields_desc = [	IntField("ue_key", None),
							IntField("sep11", None),
							ShortField('sep12', None), #2bytes
							IntField("ksi_asme", None),
							IntField("sep21", None),
							ShortField('sep22', None), #2bytes
							IntField("ue_ip", None),
							IntField("sep31", None),
							ShortField('sep32', None), #2bytes
							IntField("sgw_teid", None)]

class Initial_Ctxt_Setup_Resp(Packet):
	name = "Initial_Ctxt_Setup_Resp"
	fields_desc = [	IntField("ue_teid", None),
							IntField("sep11", None),
							ShortField('sep12', None), #2bytes
							IntField("ue_key", None),
							IntField("sep21", None),
							ShortField('sep22', None), #2bytes
							IntField("ue_ip", None),
							IntField("sep31", None),
							ShortField('sep32', None), #2bytes
							IntField("sgw_teid", None)]


class PacketProcessor(object):
    def __init__(self, router_ext_ip, cur_udp_port, ext_port, controller_port, 
                 controller_port_rules, device_number,ruleNum):
        self.router_ext_ip = router_ext_ip
        self.cur_tcp_port = cur_udp_port
        self.ext_port = ext_port
        self.controller_port = controller_port
        self.controller_port_rules = controller_port_rules
        self.device_number = device_number
        self.ruleNum = ruleNum

    def __call__(self, x):
        t1 = FuncThread(self.processPacket, x)
        #t1.daemon = True
        t1.daemon = False
        t1.start()
	t1.join()

    def SendToSwitch(self, packet, switch_port):
        del packet[IP].chksum
        del packet[UDP].chksum
        packet = packet.__class__(str(packet))

        # packet already processed so don't process again - resubmit so reason won't be valid anymore
        new_p_str = switch_port + str(packet)  #add switch_port

        #print "threading.active_count " + str(threading.active_count())
        s = conf.L2socket(iface=self.controller_port)
        # sendp(new_p_str, iface=self.controller_port, verbose=0)
        s.send(new_p_str)

    def processPacket(self, p):
                #src_ip = p[IP].src
		#dst_ip = p[IP].dst
		p_str = str(p)
		try:
	                #print threading.active_count()
			switch_port = p_str[0:2]
			p2  = Ether(p_str[2:])	
			data = p2['Data']		
		except:
			print "welcome"
			return

		#print p2.show()
		#print "Switch Port : " + switch_port
		sink_ip=str("192.168.3.4")
		if data.epc_traffic_code == 14: #UE_Context_Release_Req
			# try:
			#     tbl_id = 'ip_op_tun_s1_uplink' #del on DGW
			#     rule_name = 'del-s1-uplink_' + str(data.param4)
			#     default_rule = False
			#     actions = '{  "type" : "populate_ip_op_tun_s1_uplink",  "data" : { "egress_port_s1" : { "value" : "p0" } } }' 
			#     match = '{ "ipv4.srcAddr" : {  "value" : "%s"} , "ipv4.dstAddr" : { "value" : "192.168.3.4"} } }' % \ (data.param1)  

			#     with THRIFT_API_LOCK:
			#         if src_ip != 0:
			#         	RTEInterface.Tables.RemoveRule(tbl_id, rule_name, default_rule, match, actions, 1)
			#         	#RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
			#         	# RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1, 3)
			# except Exception, err:
			# 	print("Exception")
			# 	print(err)

			# try:
			#     tbl_id = 'tun_egress_s3_uplink' #del on DGW
			#     rule_name = 'del-s3-uplink_' + str(data.param4)
			#     default_rule = False
			#     actions = '{  "type" : "populate_tun_egress_s3_uplink",  "data" : { "egress_port_s3" : { "value" : "v0.0" } } }' 
			#     match = '{ "ue_service_req.ue_key" : {  "value" : "%s"} }' % \ (data.param4) 

			#     with THRIFT_API_LOCK:
			#         if ue_service_req.ue_key != 0:
			#         	RTEInterface.Tables.RemoveRule(tbl_id, rule_name, default_rule, match, actions, 1)
			#         	#RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
			#         	# RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1, 3)
			# except Exception, err:
			# 	print("Exception")
			# 	print(err)

			try:
				tbl_id = 'ingress::ip_op_tun_s2_downlink' #del on SGW
				#rule_name = 'del-s2-downlink_' + str(data.param4)
				rule_name = str(data.param4-99)
				default_rule = False
				actions = '{  "type" : "ingress::populate_ip_op_tun_s2_downlink",  "data" : { "egress_port_s2" : { "value" : "0" } } }' 
				match = '{ "ue_service_req.ue_key" : {  "value" : "%s"} }' % (data.param4) 
				with THRIFT_API_LOCK:
					if data.param4 != 0:
						RTEInterface.Tables.DeleteRule(tbl_id, rule_name, default_rule, match, actions) #, 1)
						#RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
						# RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1, 3)
			except Exception, err:
				#print("Exception: ip_op_tun_s2_downlink:delete")
			        #print "param4 = ", data.param4
				#print(err)
				pass

			try:
				tbl_id = 'ingress::uekey_uestate_map' #update on SGW
				#rule_name = 'update_ue_state_0_' + str(data.param4)
				rule_name =  str(data.param4-99)
				default_rule = False
				actions = '{  "type" : "ingress::populate_uekey_uestate_map",  "data" : { "uestate" : { "value" : "0" } } }' 
				match = '{ "ingress::uekey_uestate.ue_key" : {  "value" : "%s"} }' % (data.param4) 

				with THRIFT_API_LOCK:
					if data.param4 != 0:
						RTEInterface.Tables.EditRule(tbl_id, rule_name, default_rule, match, actions, 1)
						#RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
						# RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1, 3)
			except Exception, err:
				#print("Exception:uekey_uestate_map:add")
				#print(err)
				pass
			self.ruleNum += 4

		else:
			if data.epc_traffic_code == 17:  #17:UE_Service_Req,
				# try:
				#     tbl_id = 'ip_op_tun_s1_uplink' #del on DGW
				#     rule_name = 'add-s1-uplink_' + str(data.param1)
				#     default_rule = False
				#     actions = '{  "type" : "populate_ip_op_tun_s1_uplink",  "data" : { "egress_port_s1" : { "value" : "p1" } } }'
				#     match = '{ "ipv4.srcAddr" : {  "value" : "%s"} , "ipv4.dstAddr" : { "value" : "192.168.3.4"} } }' % \ (data.param3)  

				#     with THRIFT_API_LOCK:
				#         if src_ip != 0:
				#         	RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
				#         	#RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
				#         	# RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1, 3)
				# except Exception, err:
				# 	print("Exception")
				# 	print(err) 
				# self.ruleNum += 1
				pass   
		
			else:
				if data.epc_traffic_code == 19:  #19:Initial_Ctxt_Setup_Resp
					try:
						tbl_id = 'ingress::ip_op_tun_s2_downlink' #add on SGW
						#rule_name = 'add-s2-downlink_' + str(data.param2)
						rule_name = str(data.param2-99)
						default_rule = False
						actions = '{  "type" : "ingress::populate_ip_op_tun_s2_downlink",  "data" : { "egress_port_s2" : { "value" : "p0" } } }' 
						match = '{ "ue_service_req.ue_key" :{  "value" : "%s"} }' % (data.param2)  

						with THRIFT_API_LOCK:
							if data.param2 != 0:
								RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
								#RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
								# RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1, 3)
					except Exception, err:
						#print("Exception:ip_op_tun_s2_downlink:add")
						#print(err)
						pass

					# try:
					#     tbl_id = 'tun_egress_s3_uplink' #add on DGW
					#     rule_name = 'add-s3-uplink_' + str(data.param2)
					#     default_rule = False
					#     actions = '{  "type" : "populate_tun_egress_s3_uplink",  "data" : { "egress_port_s3" : { "value" : "v0.0" } } }' 
					#     match = '{ "ue_service_req.ue_key" :{  "value" : "%s"} }' % \ (data.param2)  

					#     with THRIFT_API_LOCK:
					#         if ue_service_req.ue_key != 0:
					#         	RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
					#         	#RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
					#         	# RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1, 3)
					# except Exception, err:
					# 	print("Exception")
					# 	print(err)

					try:
						tbl_id = 'ingress::uekey_uestate_map' #update on SGW
						#rule_name = 'update_ue_state_1_' + str(data.param2)
						rule_name = str(data.param2-99)
						default_rule = False
						actions = '{  "type" : "ingress::populate_uekey_uestate_map",  "data" : { "uestate" : { "value" : "1" } } }' 
						match = '{ "ingress::uekey_uestate.ue_key"  :{  "value" : "%s"} }' % (data.param2)   

						with THRIFT_API_LOCK:
							if data.param2 != 0:
								RTEInterface.Tables.EditRule(tbl_id, rule_name, default_rule, match, actions, 1)
					except Exception, err:
						#print("Exceptioni:uekey_uestate_map:add")
						#print(err)
						pass
					self.ruleNum += 3
			# print data.key1
			# print data.value
			# p2['Data'].type_sync = 3
			# #p2['IP'].src = ip_hdr.dst
			# #p2['IP'].dst = ip_hdr.src
			# #p2['Ether'].src = eth_hdr.dst
			# #p2['Ether'].dst = eth_hdr.src         
			# PacketProcessor.SendToSwitch(self, p2, switch_port)
				#self.ruleNum += 1
			#print "Done Adding " + str(self.ruleNum) + "rules"
  
def main():
    parser = argparse.ArgumentParser(description='P4 TurboEPC config')
    parser.add_argument('-i','--ip', help='External IP address - "192.168.0.1"', required=False,default="192.168.0.1")
    # parser.add_argument('-p','--ext-port', help='External port for rules - "v0.2"', required=False,default="v0.2")
    parser.add_argument('-p','--ext-port', help='External port for rules - "p1"', required=False,default="p1")
    # parser.add_argument('-c','--controller-port', help='Controller port - "vf0_1"', required=False,default="vf0_1")
    parser.add_argument('-c','--controller-port', help='Controller port - "vf0_0"', required=False,default="vf0_0")
    parser.add_argument('-r','--controller-port-rules', help='Controller port for rules - "v0.1"', required=False,default="v0.1")
    #parser.add_argument('-d','--device-number', help='Device number in case of using VFs - "v0."', required=False,default="vf0.0") #How would this work for physical ports? - Default " "?
    parser.add_argument('-d','--port-prefix', help='Port prefix for internal port - "v0." for VF or "p" for physical (DEFAULT: p)"', required=False,default="p")
    parser.add_argument('-o', '--rpc-port',dest='rpc_port', default='20207',type=int,help="Thrift RPC port (DEFAULT: 20207)")
    parser.add_argument('-s', '--rpc-server', dest='rpc_server', default='thrift', type=str, help="Thrift RPC host (DEFAULT: localhost)")
    parser.add_argument('-t', '--rule-timeout', dest='rule_timeout', default=1000, type=float, help="Rule Timeout - Rules will delete if not hit within t seconds (DEFAULT: 10 seconds)")
    parser.add_argument('-n', '--internal-ports', dest='internal_ports', default=1, type=float, help="Number of internal ports (DEFAULT: 1)")

    args = parser.parse_args()

    bind_layers(UDP, Data, dport=5001)
    stopFlag = Event()
    thread = TimerThread(stopFlag, args.rule_timeout, args.internal_ports)
    thread.daemon = True
    thread.start()
    
    #@rinku: check for switch CLI IP,port
    RTEInterface.Connect(args.rpc_server,"127.0.0.1", args.rpc_port)
    ruleNum = 0
    pp = PacketProcessor(args.ip, 1025, args.ext_port, args.controller_port, 
        args.controller_port_rules, args.port_prefix,ruleNum)

    while(1):
	#print "inside while 1"
        s = conf.L2socket(iface=args.controller_port)
        s.sniff(prn=pp ,filter='udp')
    # sniff(iface=args.controller_port, prn=pp)

if __name__ == '__main__':
	main()
