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


	static final int FLOW_RULE_PRIORITY = 100;

	static byte[] dstSinkIpAddr =  IPv4.toIPv4AddressBytes("192.168.4.5");

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
			final static String RAN_IP_2 = "192.168.5.1";
			final static String RAN_IP_3 = "192.168.7.1";
			final static String RAN_IP_4 = "192.168.11.1";
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
			static boolean DO_ENCRYPTION = true;
			static boolean CHECK_INTEGRITY = true;
			//=====================================
			// DPID or unique ID of default switch 
			final static int DEFAULT_SWITCH_ID_1 = 1;
			final static int DEFAULT_SWITCH_ID_2 = 4;
			final static int DEFAULT_SWITCH_ID_3 = 6;
			final static int DEFAULT_SWITCH_ID_4 = 8;
			final static int DEFAULT_SWITCH_ID_5 = 10;
			final static int DEFAULT_SWITCH_ID_6 = 12;

			final static DeviceId DGW_Switch_Name = DeviceId.deviceId("device:bmv2:s1");
			final static int DGW_to_primary_SGW_port = 2;
			final static int DGW_to_backup_SGW_port = 3;
			
			// DPID of Primary SGW
			final static int SGW_ID_1 = 2;
			final static int SGW_ID_2 = 5;
			final static int SGW_ID_3 = 7;
			final static int SGW_ID_4 = 9;
			final static int SGW_ID_5 = 11;
			final static int SGW_ID_6 = 13;

			// @ft : DPID of Secondary (Backup) SGW
			final static int BSGW_ID_1 = 3;
			final static int BSGW_ID_2 = 5;
			final static int BSGW_ID_3 = 7;
			final static int BSGW_ID_4 = 9;
			final static int BSGW_ID_5 = 11;
			final static int BSGW_ID_6 = 13;

			final static DeviceId SGW_NAME_1 = DeviceId.deviceId("device:bmv2:s2");
			final static DeviceId SGW_NAME_2 = DeviceId.deviceId("device:bmv2:s5");
			final static DeviceId SGW_NAME_3 = DeviceId.deviceId("device:bmv2:s7");
			final static DeviceId SGW_NAME_4 = DeviceId.deviceId("device:bmv2:s9");
			final static DeviceId SGW_NAME_5 = DeviceId.deviceId("device:bmv2:s11");
			final static DeviceId SGW_NAME_6 = DeviceId.deviceId("device:bmv2:s13");

			//@ft : backup sgw names
			final static DeviceId BSGW_NAME_1 = DeviceId.deviceId("device:bmv2:s3");
			final static DeviceId BSGW_NAME_2 = DeviceId.deviceId("device:bmv2:s5");
			final static DeviceId BSGW_NAME_3 = DeviceId.deviceId("device:bmv2:s7");
			final static DeviceId BSGW_NAME_4 = DeviceId.deviceId("device:bmv2:s9");
			final static DeviceId BSGW_NAME_5 = DeviceId.deviceId("device:bmv2:s11");
			final static DeviceId BSGW_NAME_6 = DeviceId.deviceId("device:bmv2:s13");


			final static DeviceId PGW_Switch_Name = DeviceId.deviceId("device:bmv2:s13");

			// DPID of PGW
			final static int PGW_ID = 13;
			
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
				put(PGW_ID + SEPARATOR + SGW_ID_1, 1); // for switch S1(SGW-1) connected to S4(PGW) via port 1 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_2, 2); // for switch S2(SGW-2) connected to S4(PGW) via port 1 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_3, 3); // for switch S3(SGW-3) connected to S4(PGW) via port 1 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_4, 4); // for switch S3(SGW-4) connected to S4(PGW) via port 1 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_5, 5); // for switch S3(SGW-4) connected to S4(PGW) via port 1 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_6, 6); // for switch S3(SGW-4) connected to S4(PGW) via port 1 of PGW
			}};
//
			@SuppressWarnings("serial")
//			final static HashMap<DatapathId, int[]> SGW_PORT_MAP = new HashMap<DatapathId, int[]>()
			final static HashMap<String, int[]> SGW_PORT_MAP = new HashMap<String, int[]>()
			{{
//				put(DatapathId.of(SGW_ID_1), new int[]{3,4}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_1), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_2), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_3), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_4), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_5), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_6), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
			}};

			//final static int UE_PORT = 3; //port with which default switch is connected to UE
			@SuppressWarnings("serial")
			final static HashMap<String, Integer> ENODEB_SGW_PORT_MAP = new HashMap<String, Integer>()
			{{
				put(DEFAULT_SWITCH_ID_1 + SEPARATOR + SGW_ID_1, 2);// , 3// for switch S2(SGW-1) connected to S1(ENODEB) via port 3 of Default Switch
				put(DEFAULT_SWITCH_ID_2 + SEPARATOR + SGW_ID_2, 2);// , 4// for switch S3(SGW-2) connected to S1(ENODEB) via port 4 of Default Switch
				put(DEFAULT_SWITCH_ID_3 + SEPARATOR + SGW_ID_3, 2);// , 4// for switch S3(SGW-2) connected to S1(ENODEB) via port 4 of Default Switch
				put(DEFAULT_SWITCH_ID_4 + SEPARATOR + SGW_ID_4, 2);// , 4// for switch S3(SGW-2) connected to S1(ENODEB) via port 4 of Default Switch
				put(DEFAULT_SWITCH_ID_5 + SEPARATOR + SGW_ID_5, 2);// , 4// for switch S3(SGW-2) connected to S1(ENODEB) via port 4 of Default Switch
				put(DEFAULT_SWITCH_ID_6 + SEPARATOR + SGW_ID_6, 2);// , 4// for switch S3(SGW-2) connected to S1(ENODEB) via port 4 of Default Switch
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
                    sgw = Constants.SGW_ID_1;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_2))
					sgw =  Constants.SGW_ID_2;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_3))
					sgw =  Constants.SGW_ID_3;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_4))
					sgw =  Constants.SGW_ID_4;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_5))
					sgw =  Constants.SGW_ID_5;
                else if (swid==(Constants.DEFAULT_SWITCH_ID_6))
					sgw =  Constants.SGW_ID_6;
				return Integer.toString(sgw);
			}

			public static DeviceId getSgwswitchName(String dgw){
				if(Constants.DEBUG) {
					log.warn("in Constants.getSgwswitchName sgw = {}", dgw);
				}
				// int length = dgw.length();
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
				if (swid==(Constants.DEFAULT_SWITCH_ID_1))
					sgwName = Constants.SGW_NAME_1;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_2))
					sgwName = Constants.SGW_NAME_2;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_3))
					sgwName = Constants.SGW_NAME_3;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_4))
					sgwName = Constants.SGW_NAME_4;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_5))
					sgwName = Constants.SGW_NAME_5;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_6))
					sgwName = Constants.SGW_NAME_6;
				return 	sgwName;
			}

			public static DeviceId getBackupSgwswitchName(String dgw){
				if(Constants.DEBUG) {
					log.warn("in Constants.getSgwswitchName sgw = {}", dgw);
				}
				// int length = dgw.length();
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
				if (swid==(Constants.DEFAULT_SWITCH_ID_1))
					sgwName = Constants.BSGW_NAME_1;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_2))
					sgwName = Constants.BSGW_NAME_2;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_3))
					sgwName = Constants.BSGW_NAME_3;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_4))
					sgwName = Constants.BSGW_NAME_4;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_5))
					sgwName = Constants.BSGW_NAME_5;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_6))
					sgwName = Constants.BSGW_NAME_6;
				return 	sgwName;
			}

			public static String getDgwDpid(String sgw){
//				log.info("received sgw = {}",sgw);
//				String swid1 = Character.toString(sgw.charAt(1));  // assuming that switches will be from s1---s9 so char at position1 will give switchid which is an int
				String swid1 = sgw;  // assuming that switches will be from s1---s9 so char at position1 will give switchid which is an int
				int swid = Integer.parseInt(swid1);
				String dgw="";
				if (swid==(Constants.SGW_ID_1))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_1);
				else if (swid==(Constants.SGW_ID_2))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_2);
				else if (swid==(Constants.SGW_ID_3))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_3);
				else if (swid==(Constants.SGW_ID_4))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_4);
				else if (swid==(Constants.SGW_ID_5))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_5);
				else if (swid==(Constants.SGW_ID_6))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_6);
				return dgw;
			}

//			public static DatapathId getDgwDpidFromIp(String ip){
			public static String getDgwDpidFromIp(String ip){
//				DatapathId dgw = DatapathId.of(0);
				String dgw = "";
				if (ip.equals(Constants.RAN_IP_1))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_1);
				else if (ip.equals(Constants.RAN_IP_2))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_2);
				else if (ip.equals(Constants.RAN_IP_3))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_3);
				else if (ip.equals(Constants.RAN_IP_4))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_4);
				else if (ip.equals(Constants.RAN_IP_5))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_5);
				else if (ip.equals(Constants.RAN_IP_6))
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_6);
					// log.warn("getDgwDpidFromIp dgw returning  = {}",dgw);
				return dgw;
			}


			public static int getChainIDFromSGW(String sgw){
//				String swid1 = Character.toString(sgw.charAt(1));  // assuming that switches will be from s1---s9 so char at position1 will give switchid which is an int
				String swid1 = sgw;  // assuming that switches will be from s1---s9 so char at position1 will give switchid which is an int
				int swid = Integer.parseInt(swid1);
				if (swid==(Constants.SGW_ID_1))
					return 0;
				else if (swid==(Constants.SGW_ID_2))
					return 1;
				else if (swid==(Constants.SGW_ID_3))
					return 2;
				else if (swid==(Constants.SGW_ID_4))
					return 3;
				else if (swid==(Constants.SGW_ID_5))
					return 4;
				else if (swid==(Constants.SGW_ID_6))
					return 5;
				else
					if(DEBUG)
						System.out.println("GOT INVALID SGW DPID!!!");
					return 0;
			}

			public static int getChainIDFromDGW(String dgw){

				String swid1 =dgw.split("s")[1];  // assuming that switches will be from s1---s9 so char at position1 will give switchid which is an int
				
				int swid = Integer.parseInt(swid1);
				if (swid==(Constants.DEFAULT_SWITCH_ID_1))
					return 0;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_2))
					return 1;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_3))
					return 2;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_4))
					return 3;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_5))
					return 4;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_6))
					return 5;
				else
					if(DEBUG)
						log.info("GOT INVALID DGW DPID!!!");
					return 0;
			}


//			public static String getSgwIpDownlink(DatapathId dgw){
			public static String getSgwIpDownlink(String dgw){
				String ip = "";
				String swid1 = ""; 
				if(dgw.charAt(0)=='s'){
					// means we get "s1", "s11" like switch numbers
					// log.warn("getSgwIpDownlink got switch name ={}",dgw);
					swid1=dgw.split("s")[1];

				}
				else{
					// we got switch ID like "1", "2", "12"
					// log.warn("getSgwIpDownlink got switch id ={}",dgw);
					swid1 = dgw;
				}
				int swid = Integer.parseInt(swid1);
				if (swid==(Constants.DEFAULT_SWITCH_ID_1))
					ip = Constants.SGW_IP_1_DOWNLINK;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_2))
					ip = Constants.SGW_IP_2_DOWNLINK;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_3))
					ip = Constants.SGW_IP_3_DOWNLINK;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_4))
					ip = Constants.SGW_IP_4_DOWNLINK;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_5))
					ip = Constants.SGW_IP_6_DOWNLINK;
				else if (swid==(Constants.DEFAULT_SWITCH_ID_6))
					ip = Constants.SGW_IP_6_DOWNLINK;
				return ip;
			}

			public static String getPgwIpUplink(String sgw){
				String swid1 = "";
				if(sgw.charAt(0)=='s'){
					// means we get "s1", "s11" like switch numbers
					//log.warn("got switch name ={}",sgw);
					swid1=sgw.split("s")[1];

				}
				else{
					// we got switch ID like "1", "2", "12"
					//log.warn("got switch id ={}",sgw);
					swid1 = sgw;
				}
                int swid = Integer.parseInt(swid1);

				String ip = "";
				if (swid == SGW_ID_1)
					ip = Constants.PGW_IP_1_UPLINK;
				else if (swid == SGW_ID_2)
                    ip = Constants.PGW_IP_2_UPLINK;
                else if (swid == SGW_ID_3)
                    ip = Constants.PGW_IP_3_UPLINK;
                else if (swid == SGW_ID_4)
                    ip = Constants.PGW_IP_4_UPLINK;
                else if (swid == SGW_ID_5)
                    ip = Constants.PGW_IP_5_UPLINK;
                else if (swid == SGW_ID_6)
                    ip = Constants.PGW_IP_6_UPLINK;
				return ip;
			}

			@SuppressWarnings("serial")
			final static HashMap<String, Integer> CIPHER_ALGO_MAP = new HashMap<String, Integer>()	
			{{
				put("AES", 1);
				put("HmacSHA1", 2);
			}};

		}
