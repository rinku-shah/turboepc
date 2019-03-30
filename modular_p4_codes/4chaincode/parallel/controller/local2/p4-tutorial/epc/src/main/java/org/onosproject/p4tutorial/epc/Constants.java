
/***********************************************************************
 * This file contains all the constants used in the controller's code  *
 ***********************************************************************/
package org.onosproject.p4tutorial.epc;


import java.util.HashMap;
import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;
import org.onosproject.net.DeviceId;
import org.onlab.packet.IPv4;


//import org.projectfloodlight.openflow.types.DatapathId;

public class Constants {
	private static final Logger log = getLogger(EpcApp.class);
	// Boolean flag to do the logging of events
	static boolean DEBUG = false;
	static boolean DEBUG3 = false;
	static boolean MYDEBUG = false;
	static boolean MYDEBUG1 = false;
	static boolean FRDEBUG = false;
	static boolean BITWISE_DEBUG = false;
	


	static boolean offload_with_clone = true;

	static final int FLOW_RULE_PRIORITY = 100;

	static byte[] dstSinkIpAddr =  IPv4.toIPv4AddressBytes("192.168.4.5");

        // final static int LB1 = 100; //Select SGW1 when UE KEY is between LB1 & UB1
        // final static int UB1 = 103; //101;

        // final static int LB2 = 104; //Select SGW2 when UE KEY is between LB2 & UB2
        // final static int UB2 = 107;


	/***************************Configurable parameters**********************************/
	//40:8d:5c:76:d2:67 UE MAC 00:16:3e:1f:c0:12 
	//final static String UE_MAC = "00:16:3e:c6:a2:aa"; // MAC Address of UE/eNodeB Node  *
	//final static String DEFAULT_GW_MAC = "00:16:3e:f7:4d:43"; //"12:b4:6f:db:03:28";//"00:16:3e:03:9d:5a"; // MAC Address of DGW int2 //1e:12:62:1d:67:a5     *
	final static boolean OFFLOAD_ATTACH = true; //false; //True=> We wish to offload attach components to local controller
	final static String SINK_MAC = "00:16:3e:de:0a:60"; //"00:16:3e:42:b9:ea"; // MAC Address of SINK Node //40:8d:5c:76:d2:fa    *
	final static int NUM_CHAINS = 6;
	final static String CONTROLLER_IP = "192.168.100.100";  // static controller IP
	final static int NUM_MSG = 11; //Number of messages arriving at the controller
	static int NUM_OFF_MSG =0; // Number of offloadable messages
	static int NUM_NONOFF_MSG = 0; // Number of offloadable messages
	static boolean MIGRATE_HALT = false;
	static boolean CENTRALIZED = true;
	static boolean MIGRATING = false;
	static Double SYNC_THRESHOLD = 4.0;
	static Double ROOT_CPU_THRESHOLD = 75.0;
	static Double LOCAL_CPU_THRESHOLD = 50.0;
	static Double FLOW_RATE_UPBOUND = (1.0/NUM_MSG)*2.2; //(1.0/(NUM_MSG-2));
	static float ThrREMOTEtoCENT = (float) 2400; //2300; //2700
	static float ThrCENTtoREMOTE = (float) 2200; //2200; //2400
	
	final static String ROOT_PORT ="4000"; //external socket.. port number at which root listens to
	final static String LOCAL_1_PORT ="4001"; //external socket.. port number at which root listens to
	final static String LOCAL_2_PORT ="4001"; //external socket.. port number at which root listens to
	final static String LOCAL_3_PORT ="4001"; //external socket.. port number at which root listens to
	final static String LOCAL_4_PORT ="4001"; //external socket.. port number at which root listens to
	final static String LOCAL_5_PORT ="4001"; //external socket.. port number at which root listens to
	final static String LOCAL_6_PORT ="4001"; //external socket.. port number at which root listens to
	
	final static String DGW_1_PORT ="4002"; //external socket.. port number at which root listens to
	final static String DGW_2_PORT ="4002"; //external socket.. port number at which root listens to
	final static String DGW_3_PORT ="4002"; //external socket.. port number at which root listens to
	final static String DGW_4_PORT ="4002"; //external socket.. port number at which root listens to
	final static String DGW_5_PORT ="4002"; //external socket.. port number at which root listens to
	final static String DGW_6_PORT ="4002"; //external socket.. port number at which root listens to
	
	final static String ROOT_IP ="192.168.100.100"; //Inter-controller commn... Root's IP for external commn
	//UE_MAC
	final static String UE_MAC_1 = "00:16:3e:c6:a2:aa"; // MAC Address of UE/eNodeB Node  *
	final static String UE_MAC_2 = "00:16:3e:e7:56:4b"; // MAC Address of UE/eNodeB Node  *
	final static String UE_MAC_3 = "00:16:3e:1c:8f:e1"; // MAC Address of UE/eNodeB Node  *
	final static String UE_MAC_4 = "00:16:3e:e4:62:8a"; // MAC Address of UE/eNodeB Node  *
	final static String UE_MAC_5 = "00:16:3f:7e:8e:b3"; // MAC Address of UE/eNodeB Node  *
	final static String UE_MAC_6 = "00:16:3e:c8:9a:44"; // MAC Address of UE/eNodeB Node  *
	//final static String UE_MAC_7 = "00:16:3f:7e:8e:b3"; // MAC Address of UE/eNodeB Node  *
	// IP address of various component interfaces										*
			final static String RAN_IP_1 = "192.168.1.1";			// RAN							*
			final static String RAN_IP_2 = "192.168.6.1";
			final static String RAN_IP_3 = "192.168.11.1";
			final static String RAN_IP_4 = "192.168.16.1";
			final static String RAN_IP_5 = "192.168.14.1";
			final static String RAN_IP_6 = "192.168.16.1";
			
			final static String DGW_IP_1_UPLINK = "192.168.1.2";	// DGW
			final static String DGW_IP_1_DOWNLINK = "192.168.2.2";	// DGW
			final static String DGW_IP_2_UPLINK = "192.168.5.2";	// DGW
			final static String DGW_IP_2_DOWNLINK = "192.168.6.2";
			final static String DGW_IP_3_UPLINK = "192.168.7.2";	// DGW
			final static String DGW_IP_3_DOWNLINK = "192.168.8.2";
			final static String DGW_IP_4_UPLINK = "192.168.11.2";	// DGW
			final static String DGW_IP_4_DOWNLINK = "192.168.12.2";
			final static String DGW_IP_5_UPLINK = "192.168.14.2";	// DGW
			final static String DGW_IP_5_DOWNLINK = "192.168.15.2";
			final static String DGW_IP_6_UPLINK = "192.168.16.2";	// DGW
			final static String DGW_IP_6_DOWNLINK = "192.168.17.2";
			
			//final static String DSWITCH_IP_UPLINK = "10.127.41.4";	// DGW						*
			//final static String DSWITCH_IP_DOWNLINK =final static String SGW_IP_2_DOWNLINK = "10.129.2.219"; "10.127.41.4";	// DGW
			final static String SGW_IP_1_UPLINK = "192.168.2.3";	// SGW	*
			final static String SGW_IP_1_DOWNLINK = "192.168.3.3";	
			final static String SGW_IP_2_UPLINK = "192.168.6.3";	// SGW	*
			final static String SGW_IP_2_DOWNLINK = "192.168.9.3";
			final static String SGW_IP_3_UPLINK = "192.168.8.3";	// SGW	*
			final static String SGW_IP_3_DOWNLINK = "192.168.10.3";
			final static String SGW_IP_4_UPLINK = "192.168.12.3";	// SGW	*
			final static String SGW_IP_4_DOWNLINK = "192.168.13.3";
			final static String SGW_IP_5_UPLINK = "192.168.15.3";	// SGW	*
			final static String SGW_IP_5_DOWNLINK = "192.168.100.3";
			final static String SGW_IP_6_UPLINK = "192.168.17.3";	// SGW	*
			final static String SGW_IP_6_DOWNLINK = "192.168.100.5";
			
			/// SGW IPs connected to Root Controller
			final static String SGW_IP_1 = "192.168.100.12";	// SGW	*
			final static String SGW_IP_2 = "192.168.100.14";	// SGW	*
			final static String SGW_IP_3 = "192.168.100.16";	// SGW	*
			final static String SGW_IP_4 = "192.168.100.19";	// SGW	*
			final static String SGW_IP_5 = "192.168.100.21";	// SGW	*
			final static String SGW_IP_6 = "192.168.100.23";	// SGW	*
			
			/// DGW IPs connected to Root Controller
			final static String DGW_IP_1 = "192.168.100.11";	
			final static String DGW_IP_2 = "192.168.100.13";	
			final static String DGW_IP_3 = "192.168.100.15";	
			final static String DGW_IP_4 = "192.168.100.18";	
			final static String DGW_IP_5 = "192.168.100.20";	
			final static String DGW_IP_6 = "192.168.100.22";	
			
			//final static String SGW_IP_UPLINK = "10.129.41.99";	// SGW							*
			//final static String SGW_IP_DOWNLINK = "10.129.41.99";	// SGW						*
			final static String PGW_IP_1_UPLINK= "192.168.3.4";	// PGW
			final static String PGW_IP_2_UPLINK= "192.168.9.4";	// PGW
			final static String PGW_IP_3_UPLINK= "192.168.10.4";	// PGW
			final static String PGW_IP_4_UPLINK= "192.168.13.4";	// PGW
			final static String PGW_IP_5_UPLINK= "192.168.100.4";	// PGW
			final static String PGW_IP_6_UPLINK= "192.168.100.6";	// PGW	
			final static String PGW_IP_DOWNLINK = "192.168.4.4";
			//final static String PGW_IP_UPLINK = "10.129.41.95";	// PGW							*
			//final static String PGW_IP_DOWNLINK = "10.129.41.95";	// PGW						*
			final static String SINK_IP = "192.168.4.5";	// SINK								*

			// The starting IP address which is allocated to the first UE connecting to our		*
			// network. After this addresses are assigned in monotonically increasing order.	*
			final static String STARTING_UE_IP_1 = "10.127.1.1"; //"10.129.41.103";
//			final static String STARTING_UE_IP_1 = "10.0.0.1"; //"10.129.41.103";
			final static String STARTING_UE_IP_2 = "10.127.2.1"; //"10.129.41.103";
			final static String STARTING_UE_IP_3 = "10.127.3.1"; //"10.129.41.103";  
			final static String STARTING_UE_IP_4 = "10.127.4.1"; //"10.129.41.103";  
			final static String STARTING_UE_IP_5 = "10.127.5.1"; //"10.129.41.103";  
			final static String STARTING_UE_IP_6 = "10.127.6.1"; //"10.129.41.103"; 
			/************************************************************************************/

			/*********************************************
			 * Authentication and UE Tunnel Setup Codes  *
			 *********************************************/
			final static String AUTHENTICATION_FAILURE = "-1";
			final static String AUTHENTICATION_STEP_ONE = "1";
			final static String AUTHENTICATION_STEP_TWO = "2";
			final static String AUTHENTICATION_STEP_THREE = "3";
			final static String NAS_STEP_ONE = "4";
			final static String SEND_APN = "5";
			final static String SEND_IP_SGW_TEID = "6";
			final static String SEND_UE_TEID = "7";
			final static String ATTACH_ACCEPT = "8";
			final static String SEPARATOR = "@:##:@";
			final static String INTSEPARATOR = "^";
			final static String DETACH_REQUEST = "9";
			final static String DETACH_ACCEPT = "10";
			final static String DETACH_FAILURE = "11";
			final static String REQUEST_STARTING_IP = "12";
			final static String SEND_STARTING_IP = "13";
			final static String UE_CONTEXT_RELEASE_REQUEST = "14";
			final static String UE_CONTEXT_RELEASE_COMMAND = "15";
			final static String UE_CONTEXT_RELEASE_COMPLETE = "16";
			final static String UE_SERVICE_REQUEST = "17";
			final static String INITIAL_CONTEXT_SETUP_REQUEST = "18";
			final static String INITIAL_CONTEXT_SETUP_RESPONSE = "19";
			final static String NAS_STEP_TWO = "20";
			final static String PAGING_REQUEST = "21";
			final static String INITIATE_NETWORK_SERVICE_REQUEST = "22";
			final static String SINK_SERVICE_REQUEST = "23";
			
                        final static String UE_CONTEXT_RELEASE_REQUEST_MISS = "24";
                        final static String UE_SERVICE_REQUEST_MISS = "27";
                        final static String INITIAL_CONTEXT_SETUP_RESPONSE_MISS = "29";

			final static String MAPKEYSEPARATOR = "@#";
			final static String STOREKEYSEPARATOR = "@@";
			// Serving Network ID of the MME
			final static int SN_ID = 1;

			// Network type identifier
			final static String NW_TYPE = "UMTS";

			// Key length for AES encryption/decryption algorithm
			final static int ENC_KEY_LENGTH = 32;

			// Sample AES encryption/decryption key
			final static String SAMPLE_ENC_KEY = "ABCD1234EFGH5678IJKL9012MNOP3456";

			// Range of Tunnel IDs from 1 to 4095 depending upon the length of VLAN field of ethernet header
			final static int MIN_TEID = 1;
			final static int MAX_TEID = 4095;
			
			// DPID or unique ID of SGW switch (assuming only one sgw in the network)
			//final static int SGW_DPID = 2;
			/*final static int SGW_DPID_1 = 2;
			final static int SGW_DPID_2 = 6;
			final static int SGW_DPID_3 = 8;
			final static int SGW_DPID_4 = 3;*/
			
			// boolean flags which control whether encryption and integrity checks needs to be performed or not.
			static boolean DO_ENCRYPTION = false;
			static boolean CHECK_INTEGRITY = false;
		//=====================================
			// DPID or unique ID of default switch 
			final static int DEFAULT_SWITCH_ID_1 = 1;
//			final static String DEFAULT_SWITCH_ID_1 = "s1";
			final static int DEFAULT_SWITCH_ID_2 = 4;
			final static int DEFAULT_SWITCH_ID_3 = 7;
			final static int DEFAULT_SWITCH_ID_4 = 10;
			final static int DEFAULT_SWITCH_ID_5 = 13;
			final static int DEFAULT_SWITCH_ID_6 = 16;

			final static DeviceId DGW_NAME_1 = DeviceId.deviceId("device:bmv2:s1");
			final static DeviceId DGW_NAME_2 = DeviceId.deviceId("device:bmv2:s4");
			final static DeviceId DGW_NAME_3 = DeviceId.deviceId("device:bmv2:s7");
			final static DeviceId DGW_NAME_4 = DeviceId.deviceId("device:bmv2:s10");
			final static DeviceId DGW_NAME_5 = DeviceId.deviceId("device:bmv2:s13");
			final static DeviceId DGW_NAME_6 = DeviceId.deviceId("device:bmv2:s16");
			
			// DPID of SGW
			// final static int SGW_ID_1 = 2;
			// final static int SGW_ID_2 = 5;
			// final static int SGW_ID_3 = 7;
			// final static int SGW_ID_4 = 9;
			// final static int SGW_ID_5 = 11;
			// final static int SGW_ID_6 = 13;

			final static int SGW_ID_11 = 2;
			final static int SGW_ID_12 = 3;
			final static int SGW_ID_21 = 5;
			final static int SGW_ID_22 = 6;
			final static int SGW_ID_31 = 8;
			final static int SGW_ID_32 = 9;
			final static int SGW_ID_41 = 11;
			final static int SGW_ID_42 = 12;

			// final static DeviceId SGW_NAME_1 = DeviceId.deviceId("device:bmv2:s2");
			// final static DeviceId SGW_NAME_2 = DeviceId.deviceId("device:bmv2:s5");
			// final static DeviceId SGW_NAME_3 = DeviceId.deviceId("device:bmv2:s7");
			// final static DeviceId SGW_NAME_4 = DeviceId.deviceId("device:bmv2:s9");
			// final static DeviceId SGW_NAME_5 = DeviceId.deviceId("device:bmv2:s11");
			// final static DeviceId SGW_NAME_6 = DeviceId.deviceId("device:bmv2:s13");
			
			// @vikas : in 4chain setup we have 2 SGWs in 1 chain 
			final static DeviceId SGW_NAME_11 = DeviceId.deviceId("device:bmv2:s2");
			final static DeviceId SGW_NAME_12 = DeviceId.deviceId("device:bmv2:s3");
			final static DeviceId SGW_NAME_21 = DeviceId.deviceId("device:bmv2:s5");
			final static DeviceId SGW_NAME_22 = DeviceId.deviceId("device:bmv2:s6");
			final static DeviceId SGW_NAME_31 = DeviceId.deviceId("device:bmv2:s8");
			final static DeviceId SGW_NAME_32 = DeviceId.deviceId("device:bmv2:s9");
			final static DeviceId SGW_NAME_41 = DeviceId.deviceId("device:bmv2:s11");
			final static DeviceId SGW_NAME_42 = DeviceId.deviceId("device:bmv2:s12");


			//final static int SGW_ID = 0;
			
			// DPID of PGW
			final static int PGW_ID = 4;
			
			// its the source port to be used by MME while sending UDP packets to UE
			final static int DEFAULT_CONTROL_TRAFFIC_UDP_PORT = 9876;

			// Port of Default switch with which UE is connected
			final static int DEFAULT_SWITCH_UE_PORT = 1;
			
			// Port of pgw with which sink is connected
			final static int PGW_SINK_PORT = 7;  // SINK s3 connected on eth2 of PGW in container setup

			//Controller IDs
			final static int CONTROLLER_ID_ROOT = 1;
			final static int CONTROLLER_ID_LOCAL_1 = 2;
			final static int CONTROLLER_ID_LOCAL_2 = 3;
			final static int CONTROLLER_ID_LOCAL_3 = 4;
			final static int CONTROLLER_ID_LOCAL_4 = 5;
			final static int CONTROLLER_ID_LOCAL_5 = 6;
			final static int CONTROLLER_ID_LOCAL_6 = 7;
			
			
			// We have assumed there are two SGWs viz. SGW-1 and SGW-2 between our default switch and PGW.
			// Note: One one SGW would also work, just the port number with with it is connected to default
			// switch and PGW should be correct.
			@SuppressWarnings("serial")
			final static HashMap<String, Integer> PGW_SGW_PORT_MAP = new HashMap<String, Integer>()
			{{
				

				put(PGW_ID + SEPARATOR + SGW_ID_11, 1); // for switch S2(SGW-11) connected to S13(PGW) via port 1 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_12, 2); // for switch S3(SGW-12) connected to S13(PGW) via port 2 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_21, 3); // for switch S5(SGW-21) connected to S13(PGW) via port 3 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_22, 4); // for switch S6(SGW-22) connected to S13(PGW) via port 4 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_31, 5); // for switch S8(SGW-31) connected to S13(PGW) via port 5 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_32, 6); // for switch S9(SGW-32) connected to S13(PGW) via port 6 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_41, 7); // for switch S11(SGW-41) connected to S13(PGW) via port 7 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_42, 8); // for switch S12(SGW-42) connected to S13(PGW) via port 8 of PGW
			}};
//
			@SuppressWarnings("serial")
			final static HashMap<String, int[]> SGW_PORT_MAP = new HashMap<String, int[]>()
			{{
//				put(DatapathId.of(SGW_ID_1), new int[]{3,4}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_11), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_12), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_21), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_22), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_31), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_32), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_41), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_42), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
			}};

			@SuppressWarnings("serial")
			final static HashMap<String, Integer> ENODEB_SGW_PORT_MAP = new HashMap<String, Integer>()
			{{
				//@vikas : 4chainsetup
				// chain1 
				put(DEFAULT_SWITCH_ID_1 + SEPARATOR + SGW_ID_11, 2);// for switch S2(SGW-1)  connected to S1(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_1 + SEPARATOR + SGW_ID_12, 3);// for switch S3(SGW-12) connected to S1(ENODEB) via port 3 of Default Switch
				// chain2
				put(DEFAULT_SWITCH_ID_2 + SEPARATOR + SGW_ID_21, 2);// for switch S5(SGW-21) connected to S2(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_2 + SEPARATOR + SGW_ID_22, 3);// for switch S6(SGW-22) connected to S2(ENODEB) via port 3 of Default Switch
				// chain3
				put(DEFAULT_SWITCH_ID_3 + SEPARATOR + SGW_ID_31, 2);// for switch S8(SGW-31) connected to S3(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_3 + SEPARATOR + SGW_ID_32, 3);// for switch S9(SGW-32) connected to S3(ENODEB) via port 3 of Default Switch
				// chain4
				put(DEFAULT_SWITCH_ID_4 + SEPARATOR + SGW_ID_41, 2);// for switch S11(SGW-41) connected to S4(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_4 + SEPARATOR + SGW_ID_42, 3);// for switch S12(SGW-42) connected to S4(ENODEB) via port 3 of Default Switch
			}};


//            getSgwDpid() fn can get "1", "s1", "s2", "s10", "12"
			public static String getSgwDpid(String dgw){
				if(Constants.DEBUG) {
					log.warn("in Constants.getSgwDpid dgw = {}", dgw);
				}
				String swid1 = "";
				if(dgw.charAt(0)=='s'){
					// means we get "s1", "s11" like switch numbers
					// log.warn("got switch name ={}",dgw);
					swid1=dgw.split("s")[1];

				}
				else{
					// we got switch ID like "1", "2", "12"
					// log.warn("got switch id ={}",dgw);
					swid1 = dgw;
				}
                int swid = Integer.parseInt(swid1);
                int sgw = 0 ;
                if (swid==(Constants.DEFAULT_SWITCH_ID_1))
                    sgw = Constants.SGW_ID_12;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_2))
					sgw =  Constants.SGW_ID_22;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_3))
					sgw =  Constants.SGW_ID_32;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_4))
					sgw =  Constants.SGW_ID_42;
                // else if (swid==(Constants.DEFAULT_SWITCH_ID_5))
				// 	sgw =  Constants.SGW_ID_5;
                // else if (swid==(Constants.DEFAULT_SWITCH_ID_6))
				// 	sgw =  Constants.SGW_ID_6;
				return Integer.toString(sgw);
			}

			// Given a SGW switch ID this function returns DGW switch name
			public static DeviceId getDgwswitchName(String dgw){
				if(Constants.DEBUG) {
					log.warn("in Constants.getDgwswitchName sgw = {}", dgw);
				}
				String swid1 = "";
				if(dgw.charAt(0)=='s'){
					// means we get "s1", "s11" like switch numbers
					//log.warn("got switch name ={}",dgw);
					swid1=dgw.split("s")[1];
				}
				else{
					// we got switch ID like "1", "2", "12"
					//log.warn("got switch id ={}",dgw);
					swid1 = dgw;
				}
				int swid = Integer.parseInt(swid1);
				DeviceId sgwName = DeviceId.deviceId("") ;
				if ( (swid==(Constants.SGW_ID_11)) || (swid==(Constants.SGW_ID_12) )){
					sgwName = Constants.DGW_NAME_1;
				}
				else if ( (swid==(Constants.SGW_ID_21)) || (swid==(Constants.SGW_ID_22) )){
					sgwName = Constants.DGW_NAME_2;
				}
				else if ( (swid==(Constants.SGW_ID_31)) || (swid==(Constants.SGW_ID_32) )){
					sgwName = Constants.DGW_NAME_3;
				}
				else if ( (swid==(Constants.SGW_ID_41)) || (swid==(Constants.SGW_ID_42) )){
					sgwName = Constants.DGW_NAME_4;
				}
							// log.warn("in Constants.getDgwswitchName returning = {}", sgwName);
				return 	sgwName;
			}


			public static String getSgwDpidFromIp(String ip){
					String dgw = "";
					if (ip.equals(Constants.RAN_IP_1))
						dgw = Integer.toString(Constants.SGW_ID_12);
					else if (ip.equals(Constants.RAN_IP_2))
						dgw = Integer.toString(Constants.SGW_ID_22);
					else if (ip.equals(Constants.RAN_IP_3))
						dgw = Integer.toString(Constants.SGW_ID_32);
					else if (ip.equals(Constants.RAN_IP_4))
						dgw = Integer.toString(Constants.SGW_ID_42);
					// else if (ip.equals(Constants.RAN_IP_5))
					// 	dgw = Integer.toString(Constants.SGW_ID_5);
					// else if (ip.equals(Constants.RAN_IP_6))
					// 	dgw = Integer.toString(Constants.SGW_ID_6);
					return dgw;
				}

			@SuppressWarnings("serial")
			final static HashMap<String, Integer> CIPHER_ALGO_MAP = new HashMap<String, Integer>()	
			{{
				put("AES", 1);
				put("HmacSHA1", 2);
			}};

		}
