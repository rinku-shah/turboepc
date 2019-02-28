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

	static byte[] dstSinkIpAddr =  IPv4.toIPv4AddressBytes("192.168.21.2");


	/***************************Configurable parameters**********************************/
	final static boolean OFFLOAD_ATTACH = true; //false; //True=> We wish to offload attach components to local controller
	final static String SINK_MAC = "00:16:3e:de:0a:60"; //"00:16:3e:42:b9:ea"; // MAC Address of SINK Node //40:8d:5c:76:d2:fa    *
	final static int NUM_CHAINS = 6;
	final static String CONTROLLER_IP = "192.168.100.12";  // static controller IP
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
	
	// IP address of various component interfaces										*
			final static String RAN_IP_1 = "192.168.1.1";			// RAN							*
			final static String RAN_IP_2 = "192.168.5.1";
			final static String RAN_IP_3 = "192.168.9.1";
			final static String RAN_IP_4 = "192.168.13.1";
			final static String RAN_IP_5 = "192.168.17.1";
			final static String RAN_IP_6 = "192.168.21.1";
			

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
			
			// boolean flags which control whether encryption and integrity checks needs to be performed or not.
			static boolean DO_ENCRYPTION = false;
			static boolean CHECK_INTEGRITY = false;
			//=====================================
			// DPID or unique ID of default switch 
			final static int DEFAULT_SWITCH_ID_1 = 1;
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
			
			// DPID of SGWs

			final static int SGW_ID_11 = 2;
			final static int SGW_ID_12 = 3;
			final static int SGW_ID_21 = 5;
			final static int SGW_ID_22 = 6;
			final static int SGW_ID_31 = 8;
			final static int SGW_ID_32 = 9;
			final static int SGW_ID_41 = 11;
			final static int SGW_ID_42 = 12;


			// @vikas : in 4chain setup we have 2 SGWs in 1 chain 
			final static DeviceId SGW_NAME_11 = DeviceId.deviceId("device:bmv2:s2");
			final static DeviceId SGW_NAME_12 = DeviceId.deviceId("device:bmv2:s3");
			final static DeviceId SGW_NAME_21 = DeviceId.deviceId("device:bmv2:s5");
			final static DeviceId SGW_NAME_22 = DeviceId.deviceId("device:bmv2:s6");
			final static DeviceId SGW_NAME_31 = DeviceId.deviceId("device:bmv2:s8");
			final static DeviceId SGW_NAME_32 = DeviceId.deviceId("device:bmv2:s9");
			final static DeviceId SGW_NAME_41 = DeviceId.deviceId("device:bmv2:s11");
			final static DeviceId SGW_NAME_42 = DeviceId.deviceId("device:bmv2:s12");

			// Port of Default switch with which UE is connected
			final static int DEFAULT_SWITCH_UE_PORT = 1;
			
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
                    sgw = Constants.SGW_ID_11;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_2))
					sgw =  Constants.SGW_ID_21;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_3))
					sgw =  Constants.SGW_ID_31;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_4))
					sgw =  Constants.SGW_ID_41;
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
					String sgw = "";
					if (ip.equals(Constants.RAN_IP_1))
						sgw = Integer.toString(Constants.SGW_ID_11);
					else if (ip.equals(Constants.RAN_IP_2))
						sgw = Integer.toString(Constants.SGW_ID_21);
					else if (ip.equals(Constants.RAN_IP_3))
						sgw = Integer.toString(Constants.SGW_ID_31);
					else if (ip.equals(Constants.RAN_IP_4))
						sgw = Integer.toString(Constants.SGW_ID_41);
					// else if (ip.equals(Constants.RAN_IP_5))
					// 	sgw = Integer.toString(Constants.SGW_ID_5);
					// else if (ip.equals(Constants.RAN_IP_6))
					// 	sgw = Integer.toString(Constants.SGW_ID_6);
					return sgw;
				}

			@SuppressWarnings("serial")
			final static HashMap<String, Integer> CIPHER_ALGO_MAP = new HashMap<String, Integer>()	
			{{
				put("AES", 1);
				put("HmacSHA1", 2);
			}};

		}
