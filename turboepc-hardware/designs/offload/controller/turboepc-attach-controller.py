from scapy.all import *
import argparse
import time
import threading
from threading import Event
from time import sleep

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
        #new_p_str = switch_port + str(packet)  #add switch_port

        #print "threading.active_count " + str(threading.active_count())
        s = conf.L2socket(iface=self.controller_port)
        # sendp(new_p_str, iface=self.controller_port, verbose=0)
        #s.send(new_p_str)
	s.send(str(packet))

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
                if data.epc_traffic_code == 1:  #1:Authentication Step One
		    #print "Authentication Step 1"
		    #ether = Ether(dst='00:11:11:11:11:11')
		    #ip = IP(src=self.host, dst='192.168.2.2')
		    #udp = UDP(sport=68, dport=self.port)
		    #payload = Raw(load=data)
		    #packet = str(ether / ip / udp / payload)
		    #self.logger.debug('Sending header+data to host: %s:%d' % (self.host, self.port))
		    #self.socket.send(packet)
		    #self.logger.debug('Header+data sent to host') 
		    p2['Data'].epc_traffic_code = 2  #AUTH_STEP_TWO
		    temp = p2['UDP'].sport
		    p2['UDP'].sport = p2['UDP'].dport
		    p2['UDP'].dport = temp
		    temp = p2['IP'].src
		    p2['IP'].src = p2['IP'].dst
		    p2['IP'].dst = temp
		    temp = p2['Ether'].src
		    p2['Ether'].src = p2['Ether'].dst
		    p2['Ether'].dst = temp    
		    #p3 = Ether(src=p2['Ether'].dst, dst=p2['Ether'].src) / IP(src=p2['IP'].dst, dst=p2['IP'].src) / UDP(sport=p2['UDP'].dport, dport=p2['UDP'].sport) / Raw('\x02@:##:@')  
		    #p3.show()
		    #time.sleep(0.05)
		    PacketProcessor.SendToSwitch(self, p2, switch_port)
		    #p2.show()
		else:
			if data.epc_traffic_code == 3:  #Authentication Step 3
			    #print "Authentication Step 3" 
			    p2['Data'].epc_traffic_code = 4 #NAS_STEP_ONE
			    temp = p2['UDP'].sport
			    p2['UDP'].sport = p2['UDP'].dport
			    p2['UDP'].dport = temp
			    temp = p2['IP'].src
			    p2['IP'].src = p2['IP'].dst
			    p2['IP'].dst = temp
			    temp = p2['Ether'].src
			    p2['Ether'].src = p2['Ether'].dst
			    p2['Ether'].dst = temp    
			    PacketProcessor.SendToSwitch(self, p2, switch_port)
			    #p2.show()
			else:
				if data.epc_traffic_code == 20:  #NAS_STEP_TWO
				    pass
				    #print "NAS_STEP_TWO" #send nothing
				else:
				        if data.epc_traffic_code == 5:  #Send APN
					    #print "Send APN" 
					    p2['Data'].epc_traffic_code = 6 #SEND_IP_SGW_TEID
					    temp = p2['UDP'].sport
					    p2['UDP'].sport = p2['UDP'].dport
					    p2['UDP'].dport = temp
					    temp = p2['IP'].src
					    p2['IP'].src = p2['IP'].dst
					    p2['IP'].dst = temp
					    temp = p2['Ether'].src
					    p2['Ether'].src = p2['Ether'].dst
					    p2['Ether'].dst = temp
					    #PacketProcessor.SendToSwitch(self, p2, switch_port)
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
					    PacketProcessor.SendToSwitch(self, p2, switch_port)  
					else:
				    	        if data.epc_traffic_code == 7:  #SEND_UE_TEID
						    #print "Attach accept" 
						    p2['Data'].epc_traffic_code = 25 #ACTUAL_ATTACH_ACCEPT
						    temp = p2['UDP'].sport
						    p2['UDP'].sport = p2['UDP'].dport
						    p2['UDP'].dport = temp
						    temp = p2['IP'].src
						    p2['IP'].src = p2['IP'].dst
						    p2['IP'].dst = temp
						    temp = p2['Ether'].src
						    p2['Ether'].src = p2['Ether'].dst
						    p2['Ether'].dst = temp
						    #PacketProcessor.SendToSwitch(self, p2, switch_port)    
						    #p2.show()
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
						    PacketProcessor.SendToSwitch(self, p2, switch_port)  

					        else:
				    	                if data.epc_traffic_code == 9:  #DETACH_REQ
					                    #print "Detach request" 
							    p2['Data'].epc_traffic_code = 10 #DETACH_ACCEPT
							    temp = p2['UDP'].sport
							    p2['UDP'].sport = p2['UDP'].dport
							    p2['UDP'].dport = temp
							    temp = p2['IP'].src
							    p2['IP'].src = p2['IP'].dst
							    p2['IP'].dst = temp
							    temp = p2['Ether'].src
							    p2['Ether'].src = p2['Ether'].dst
							    p2['Ether'].dst = temp 
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
							    PacketProcessor.SendToSwitch(self, p2, switch_port)
							    #p2.show()
  
def main():
    parser = argparse.ArgumentParser(description='P4 TurboEPC SGW config')
    parser.add_argument('-i','--ip', help='External IP address - "192.168.0.1"', required=False,default="192.168.0.1")
    # parser.add_argument('-p','--ext-port', help='External port for rules - "v0.2"', required=False,default="v0.2")
    parser.add_argument('-p','--ext-port', help='External port for rules - "p1"', required=False,default="p1")
    # parser.add_argument('-c','--controller-port', help='Controller port - "vf0_1"', required=False,default="vf0_1")
    parser.add_argument('-c','--controller-port', help='Controller port - "vf0_0"', required=False,default="vf0_0")
    parser.add_argument('-r','--controller-port-rules', help='Controller port for rules - "v0.0"', required=False,default="v0.0")
    #parser.add_argument('-d','--device-number', help='Device number in case of using VFs - "v0."', required=False,default="vf0.0") #How would this work for physical ports? - Default " "?
    parser.add_argument('-d','--port-prefix', help='Port prefix for internal port - "v0." for VF or "p" for physical (DEFAULT: p)"', required=False,default="p")
    parser.add_argument('-o', '--rpc-port',dest='rpc_port', default='20206',type=int,help="Thrift RPC port (DEFAULT: 20206)")
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
        #s.sniff(prn=pp ,filter='udp')
    	sniff(iface=args.controller_port, prn=pp)

if __name__ == '__main__':
	main()
