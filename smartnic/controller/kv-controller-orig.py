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
                    # #print(ruleList[i].rule_name)
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
	fields_desc = [	ByteEnumField("type_sync", None, { 2 : "WRITE", 3 : "WRITE_REPLY"}),
							IntField("key1", None),
							IntField("value", None),
							ByteField("version", None)]



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
        t1.daemon = True
        t1.start()

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
        # hexdump(p)
        # print '.',
	p_str = str(p)
        try:
		switch_port = p_str[0]
		p2  = Ether(p_str[1:])	
		data = p2['Data']		
        except:
		print "welcome"
		return

	
	print p2.show()
	print "Switch Port : " + switch_port

        try:
            tbl_id = 'kv_store'
            rule_name = 'kv_store_add_' + str(data.key1)
            default_rule = False
            actions = '{  "type" : "reply_to_read",  "data" : { "value" : { "value" : "%s" } } }' % \
                      (data.value)
            match = '{ "data.key1" : {  "value" : "%s"} }' % \
                    (data.key1)

            with THRIFT_API_LOCK:
                if data.key1 != 0:
                	RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1)
                # RTEInterface.Tables.AddRule(tbl_id, rule_name, default_rule, match, actions, 1, 3)
                  
        except Exception, err:
            print("Exception")
            print(err)

        
	print data.key1
	print data.value
	p2['Data'].type_sync = 3
	#p2['IP'].src = ip_hdr.dst
	#p2['IP'].dst = ip_hdr.src
	#p2['Ether'].src = eth_hdr.dst
	#p2['Ether'].dst = eth_hdr.src         
	PacketProcessor.SendToSwitch(self, p2, switch_port)
        self.ruleNum += 1
        print "Done Adding Rule: " + str(self.ruleNum)

def main():
    parser = argparse.ArgumentParser(description='P4 Key-Value Store config')
    parser.add_argument('-i','--ip', help='External IP address - "192.168.0.1"', required=False,default="192.168.0.1")
    # parser.add_argument('-p','--ext-port', help='External port for rules - "v0.2"', required=False,default="v0.2")
    parser.add_argument('-p','--ext-port', help='External port for rules - "p1"', required=False,default="p1")
    # parser.add_argument('-c','--controller-port', help='Controller port - "vf0_1"', required=False,default="vf0_1")
    parser.add_argument('-c','--controller-port', help='Controller port - "vf0_1"', required=False,default="vf0_1")
    parser.add_argument('-r','--controller-port-rules', help='Controller port for rules - "v0.1"', required=False,default="v0.1")
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

    RTEInterface.Connect(args.rpc_server,"192.168.200.2", args.rpc_port)
    ruleNum = 0
    pp = PacketProcessor(args.ip, 1025, args.ext_port, args.controller_port, 
        args.controller_port_rules, args.port_prefix,ruleNum)

    while(1):
        s = conf.L2socket(iface=args.controller_port)
        s.sniff(prn=pp)
    # sniff(iface=args.controller_port, prn=pp)

if __name__ == '__main__':
	main()
