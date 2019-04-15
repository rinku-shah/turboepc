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

	static byte[] dstSinkIpAddr =  IPv4.toIPv4AddressBytes("192.168.21.2");

	/***************************Configurable parameters**********************************/
	
	//global chain
	final static int UE_LB = 100; //push UE state to switches when UE KEY is between UE_LB & UE_UB
	final static int UE_UB = 174;
	
	//chain1
	final static int LB11 = 100; //Select SGW11 when UE KEY is between LB11 & UB11
    final static int UB11 = 124; 

    final static int LB12 = 125; //Select SGW12 when UE KEY is between LB12 & UB12
	final static int UB12 = 149;

	final static int LB13 = 150; //Select SGW21 when UE KEY is between LB13 & UB13
    final static int UB13 = 174; 

	//chain2	
    final static int LB21 = 250; //Select SGW22 when UE KEY is between LB21 & UB21
	final static int UB21 = 299;

	final static int LB22 = 300; //Select SGW31 when UE KEY is between LB22 & UB22
    final static int UB22 = 349; 

    final static int LB23 = 350; //Select SGW32 when UE KEY is between LB23 & UB23
	final static int UB23 = 399;

	//chain3
	final static int LB31 = 400; //Select SGW41 when UE KEY is between LB31 & UB31
    final static int UB31 = 449; 

    final static int LB32 = 450; //Select SGW42 when UE KEY is between LB32 & UB32
	final static int UB32 = 499;

	final static int LB33 = 450; //Select SGW42 when UE KEY is between LB32 & UB32
    final static int UB33 = 499;

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
			
			final static String PGW_IP_1_UPLINK= "192.168.3.4";	// PGW
			final static String PGW_IP_2_UPLINK= "192.168.9.4";	// PGW
			final static String PGW_IP_3_UPLINK= "192.168.10.4";	// PGW
			final static String PGW_IP_4_UPLINK= "192.168.13.4";	// PGW
			final static String PGW_IP_5_UPLINK= "192.168.100.4";	// PGW
			final static String PGW_IP_6_UPLINK= "192.168.100.6";	// PGW	
			final static String PGW_IP_DOWNLINK = "192.168.4.4";
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

			final static int DGW_ID_1 = 1;
			final static int DGW_ID_2 = 4;
			final static int DGW_ID_3 = 7;
			final static int DGW_ID_4 = 10;
			final static int DGW_ID_5 = 13;
			final static int DGW_ID_6 = 16;
			
			final static DeviceId DGW_NAME_1 = DeviceId.deviceId("device:bmv2:s1");
			final static DeviceId DGW_NAME_2 = DeviceId.deviceId("device:bmv2:s4");
			final static DeviceId DGW_NAME_3 = DeviceId.deviceId("device:bmv2:s7");
			final static DeviceId DGW_NAME_4 = DeviceId.deviceId("device:bmv2:s10");
			final static DeviceId DGW_NAME_5 = DeviceId.deviceId("device:bmv2:s13");
			final static DeviceId DGW_NAME_6 = DeviceId.deviceId("device:bmv2:s16");	
			

			// DPID of SGW
			final static int SGW_ID_11 = 2;
			final static int SGW_ID_12 = 3;
			final static int SGW_ID_13 = 6;
			//final static int SGW_ID_13 = 5;

			final static int SGW_ID_21 = 5;
			final static int SGW_ID_22 = 6;
			final static int SGW_ID_23 = 6;

			final static int SGW_ID_31 = 8;
			final static int SGW_ID_32 = 9;
			final static int SGW_ID_33 = 9;

			final static int SGW_ID_41 = 11;
			final static int SGW_ID_42 = 12;
			final static int SGW_ID_43 = 12;

			

			// @vikas : in 4chain series setup we have 3 SGWs in 1 chain 
			final static DeviceId SGW_NAME_11 = DeviceId.deviceId("device:bmv2:s2");
			final static DeviceId SGW_NAME_12 = DeviceId.deviceId("device:bmv2:s3");
			final static DeviceId SGW_NAME_13 = DeviceId.deviceId("device:bmv2:s6");

			final static DeviceId SGW_NAME_21 = DeviceId.deviceId("device:bmv2:s5");
			final static DeviceId SGW_NAME_22 = DeviceId.deviceId("device:bmv2:s6");
			final static DeviceId SGW_NAME_23 = DeviceId.deviceId("device:bmv2:s6");

			final static DeviceId SGW_NAME_31 = DeviceId.deviceId("device:bmv2:s8");
			final static DeviceId SGW_NAME_32 = DeviceId.deviceId("device:bmv2:s9");
			final static DeviceId SGW_NAME_33 = DeviceId.deviceId("device:bmv2:s9");

			final static DeviceId SGW_NAME_41 = DeviceId.deviceId("device:bmv2:s11");
			final static DeviceId SGW_NAME_42 = DeviceId.deviceId("device:bmv2:s12");
			final static DeviceId SGW_NAME_43 = DeviceId.deviceId("device:bmv2:s12");

			final static DeviceId PGW_NAME = DeviceId.deviceId("device:bmv2:s13");

			// DPID of PGW : since PGW switch is device:bmv2:s13
			final static int PGW_ID = 13;


			// Port of Default switch with which UE is connected
			final static int DEFAULT_SWITCH_UE_PORT = 1;
			
			// Port of pgw with which sink is connected
			final static int PGW_SINK_PORT = 5;  // SINK s3 connected on eth5 of PGW in container setup
			
			// We have assumed there are two SGWs viz. SGW-1 and SGW-2 between our default switch and PGW.
			// Note: One one SGW would also work, just the port number with with it is connected to default
			// switch and PGW should be correct.
			@SuppressWarnings("serial")
			final static HashMap<String, Integer> PGW_SGW_PORT_MAP = new HashMap<String, Integer>()
			{{
				// put(PGW_ID + SEPARATOR + SGW_ID_1, 1); // for switch S1(SGW-1) connected to S4(PGW) via port 1 of PGW

				put(PGW_ID + SEPARATOR + SGW_ID_11, 1); // for switch S2(SGW-11) connected to S13(PGW) via port 1 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_12, 1); // for switch S3(SGW-12) connected to S13(PGW) via port 1 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_13, 1); // for switch S3(SGW-12) connected to S13(PGW) via port 1 of PGW

				put(PGW_ID + SEPARATOR + SGW_ID_21, 2); // for switch S5(SGW-21) connected to S13(PGW) via port 2 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_22, 2); // for switch S6(SGW-22) connected to S13(PGW) via port 2 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_23, 2); // for switch S6(SGW-22) connected to S13(PGW) via port 2 of PGW

				put(PGW_ID + SEPARATOR + SGW_ID_31, 3); // for switch S8(SGW-31) connected to S13(PGW) via port 3 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_32, 3); // for switch S9(SGW-32) connected to S13(PGW) via port 3 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_33, 3); // for switch S9(SGW-32) connected to S13(PGW) via port 3 of PGW

				put(PGW_ID + SEPARATOR + SGW_ID_41, 4); // for switch S11(SGW-41) connected to S13(PGW) via port 4 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_42, 4); // for switch S12(SGW-42) connected to S13(PGW) via port 4 of PGW
				put(PGW_ID + SEPARATOR + SGW_ID_43, 4); // for switch S12(SGW-42) connected to S13(PGW) via port 4 of PGW
			}};
			@SuppressWarnings("serial")
			final static HashMap<String, int[]> SGW_PORT_MAP = new HashMap<String, int[]>()
			{{
				put(Integer.toString(SGW_ID_11), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_12), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_13), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}

				put(Integer.toString(SGW_ID_21), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_22), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_23), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}

				put(Integer.toString(SGW_ID_31), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_32), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_33), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}

				put(Integer.toString(SGW_ID_41), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_42), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
				put(Integer.toString(SGW_ID_43), new int[]{1,2}); // new int[]{SGW-INPORT, SGW-OUTPORT}
			}};

			@SuppressWarnings("serial")
			final static HashMap<String, Integer> ENODEB_SGW_PORT_MAP = new HashMap<String, Integer>()
			{{
				//@vikas : 4chainsetup
				// chain1 
				put(DEFAULT_SWITCH_ID_1 + SEPARATOR + SGW_ID_11, 2);// for switch S2(SGW-11)  connected to S1(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_1 + SEPARATOR + SGW_ID_12, 2);// for switch S3(SGW-12) connected to S1(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_1 + SEPARATOR + SGW_ID_13, 2);// for switch S3(SGW-12) connected to S1(ENODEB) via port 2 of Default Switch

				// chain2
				put(DEFAULT_SWITCH_ID_2 + SEPARATOR + SGW_ID_21, 2);// for switch S5(SGW-21) connected to S2(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_2 + SEPARATOR + SGW_ID_22, 2);// for switch S6(SGW-22) connected to S2(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_2 + SEPARATOR + SGW_ID_23, 2);// for switch S6(SGW-22) connected to S2(ENODEB) via port 2 of Default Switch
				// chain3
				put(DEFAULT_SWITCH_ID_3 + SEPARATOR + SGW_ID_31, 2);// for switch S8(SGW-31) connected to S3(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_3 + SEPARATOR + SGW_ID_32, 2);// for switch S9(SGW-32) connected to S3(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_3 + SEPARATOR + SGW_ID_33, 2);// for switch S9(SGW-32) connected to S3(ENODEB) via port 2 of Default Switch
				// chain4
				put(DEFAULT_SWITCH_ID_4 + SEPARATOR + SGW_ID_41, 2);// for switch S11(SGW-41) connected to S4(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_4 + SEPARATOR + SGW_ID_42, 2);// for switch S12(SGW-42) connected to S4(ENODEB) via port 2 of Default Switch
				put(DEFAULT_SWITCH_ID_4 + SEPARATOR + SGW_ID_43, 2);// for switch S12(SGW-42) connected to S4(ENODEB) via port 2 of Default Switch
			}};


//            getSgwDpidScale() fn can get "1", "s1", "s2", "s10", "12"
			public static String getSgwDpidScale(String dgw, int key){
					if(Constants.DEBUG) {
							log.warn("in Constants.getSgwDpidScale dgw = {}", dgw);
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
					// chain1 with 3 SGWs
					if (swid==(Constants.DEFAULT_SWITCH_ID_1) && ((key >= Constants.LB11 && key <= Constants.UB11)))
						sgw = Constants.SGW_ID_11;
					else if (swid==(Constants.DEFAULT_SWITCH_ID_1) && ((key >= Constants.LB12 && key <= Constants.UB12)))
						sgw = Constants.SGW_ID_12;
					else if (swid==(Constants.DEFAULT_SWITCH_ID_1) && ((key >= Constants.LB13 && key <= Constants.UB13)))
						sgw = Constants.SGW_ID_13;
					
					// chain 2 with 3 SGWs
					else if (swid==(Constants.DEFAULT_SWITCH_ID_2) && ((key >= Constants.LB21 && key <= Constants.UB21)))
						sgw = Constants.SGW_ID_21;
					else if (swid==(Constants.DEFAULT_SWITCH_ID_2) && ((key >= Constants.LB22 && key <= Constants.UB22)))
						sgw = Constants.SGW_ID_22;
					else if (swid==(Constants.DEFAULT_SWITCH_ID_2) && ((key >= Constants.LB23 && key <= Constants.UB23)))
						sgw = Constants.SGW_ID_23;

					else if (swid==(Constants.DEFAULT_SWITCH_ID_3) && ((key >= Constants.LB31 && key <= Constants.UB31)))
						sgw = Constants.SGW_ID_31;
					else if (swid==(Constants.DEFAULT_SWITCH_ID_3) && ((key >= Constants.LB32 && key <= Constants.UB32)))
						sgw = Constants.SGW_ID_32;
					else if (swid==(Constants.DEFAULT_SWITCH_ID_3) && ((key >= Constants.LB33 && key <= Constants.UB33)))
						sgw = Constants.SGW_ID_33;
			
				return Integer.toString(sgw);
            }


			public static DeviceId getSgwswitchNameScale(String dgw, int key){
					if(Constants.DEBUG) {
							log.warn("in Constants.getSgwswitchNameScale dgw = {}", dgw);
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
					if ((swid==(Constants.DEFAULT_SWITCH_ID_1)) && ((key >= Constants.LB11 && key <= Constants.UB11)) )
							sgwName = Constants.SGW_NAME_11;
					else if ((swid==(Constants.DEFAULT_SWITCH_ID_1)) && ((key >= Constants.LB12 && key <= Constants.UB12)) )
							sgwName = Constants.SGW_NAME_12;
					else if ((swid==(Constants.DEFAULT_SWITCH_ID_1)) && ((key >= Constants.LB13 && key <= Constants.UB13)) )
							sgwName = Constants.SGW_NAME_13;

					else if ((swid==(Constants.DEFAULT_SWITCH_ID_2)) && ((key >= Constants.LB21 && key <= Constants.UB21)) )
							sgwName = Constants.SGW_NAME_21;
					else if ((swid==(Constants.DEFAULT_SWITCH_ID_2)) && ((key >= Constants.LB22 && key <= Constants.UB22)) )
							sgwName = Constants.SGW_NAME_22;
					else if ((swid==(Constants.DEFAULT_SWITCH_ID_2)) && ((key >= Constants.LB23 && key <= Constants.UB23)) )
							sgwName = Constants.SGW_NAME_23;

					else if ((swid==(Constants.DEFAULT_SWITCH_ID_3)) && ((key >= Constants.LB31 && key <= Constants.UB31)) )
							sgwName = Constants.SGW_NAME_31;
					else if ((swid==(Constants.DEFAULT_SWITCH_ID_3)) && ((key >= Constants.LB32 && key <= Constants.UB32)) )
							sgwName = Constants.SGW_NAME_32;
					else if ((swid==(Constants.DEFAULT_SWITCH_ID_3)) && ((key >= Constants.LB33 && key <= Constants.UB33)) )
							sgwName = Constants.SGW_NAME_33;

					return  sgwName;
			}
			
			// @vikas: if statement rewriting
			public static int getSgwswitchNameSeries_forlookup(String dgw, int key){
				if(Constants.DEBUG) {
						log.warn("in Constants.getSgwswitchNameSeries_forlookup dgw = {}", dgw);
				}
				int lookup_flag=0;  // lookup_flag will tell whether to populate entries on SGW1_1 switch or SGW1_2 switch after matching ue_key range
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
				//chain1
				if ((swid==(Constants.DEFAULT_SWITCH_ID_1)) && ((key >= Constants.LB11 && key <= Constants.UB11)) ){
						lookup_flag = 1;
				}
				else if ((swid==(Constants.DEFAULT_SWITCH_ID_1)) && ((key >= Constants.LB12 && key <= Constants.UB12)) ){
					lookup_flag = 2;
				}
				else if (swid==(Constants.DEFAULT_SWITCH_ID_1)  && ((key >= Constants.LB13 && key <= Constants.UB13)) ){
					lookup_flag = 3;
				}
				//chain2
				else if ((swid==(Constants.DEFAULT_SWITCH_ID_2)) && ((key >= Constants.LB21 && key <= Constants.UB21)) ){
					lookup_flag = 1;
				}
				else if (swid==(Constants.DEFAULT_SWITCH_ID_2)  && ((key >= Constants.LB22 && key <= Constants.UB22)) ){
					lookup_flag = 2;
				}
				else if ((swid==(Constants.DEFAULT_SWITCH_ID_2)) && ((key >= Constants.LB23 && key <= Constants.UB23)) ){
					lookup_flag = 3;
				}
				//chain3
				else if (swid==(Constants.DEFAULT_SWITCH_ID_3)  && ((key >= Constants.LB31 && key <= Constants.UB31)) ){
					lookup_flag = 1;
				}
				else if ((swid==(Constants.DEFAULT_SWITCH_ID_3)) && ((key >= Constants.LB32 && key <= Constants.UB32)) ){
					lookup_flag = 2;
				}
				else if ((swid==(Constants.DEFAULT_SWITCH_ID_3)) && ((key >= Constants.LB33 && key <= Constants.UB33)) ){
					lookup_flag = 3;
				}

				return  lookup_flag;
			}

			public static String getDgwDpid(String sgw){
//				log.info("received sgw = {}",sgw);
//				String swid1 = Character.toString(sgw.charAt(1));  // assuming that switches will be from s1---s9 so char at position1 will give switchid which is an int
				String swid1 = sgw;  // assuming that switches will be from s1---s9 so char at position1 will give switchid which is an int
				int swid = Integer.parseInt(swid1);
				String dgw="";
				// chain1
				if ( (swid==(Constants.SGW_ID_11)) || (swid==(Constants.SGW_ID_12)) || (swid==(Constants.SGW_ID_13)) ) 
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_1);
				// chain2
				else if ( (swid==(Constants.SGW_ID_21)) || (swid==(Constants.SGW_ID_22)) || (swid==(Constants.SGW_ID_23)) ) 
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_2);
				// chain3
				else if ( (swid==(Constants.SGW_ID_31)) || (swid==(Constants.SGW_ID_32)) || (swid==(Constants.SGW_ID_33))) 
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_3);
				// chain 4
				else if ( (swid==(Constants.SGW_ID_41)) || (swid==(Constants.SGW_ID_42)) || (swid==(Constants.SGW_ID_43))) 
					dgw = Integer.toString(Constants.DEFAULT_SWITCH_ID_4);

				return dgw;
			}

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
				if (swid==(Constants.DGW_ID_1))
					sgwName = Constants.DGW_NAME_1;
				else if (swid==(Constants.DGW_ID_2)){
					sgwName =Constants.DGW_NAME_2;
					// sgwName =Constants.DGW_NAME_1;
					}
				else if (swid==(Constants.DGW_ID_3))
					sgwName = Constants.DGW_NAME_3;
				else if (swid==(Constants.DGW_ID_4))
					sgwName = Constants.DGW_NAME_4;
				else if (swid==(Constants.DGW_ID_5))
					sgwName = Constants.DGW_NAME_5;
				else if (swid==(Constants.DGW_ID_6))
					sgwName = Constants.DGW_NAME_6;
			// log.warn("in Constants.getDgwswitchName returning = {}", sgwName);
				return 	sgwName;
			}

			public static String getDgwDpidFromIp(String ip){
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
				//log.warn("in Constants.getChainIDFromSGW sgw recieved = {}",sgw);
//				String swid1 = Character.toString(sgw.charAt(1));  // assuming that switches will be from s1---s9 so char at position1 will give switchid which is an int
				String swid1 = sgw;  // assuming that switches will be from s1---s9 so char at position1 will give switchid which is an int
				int swid = Integer.parseInt(swid1);
				// @vikas : @modular 4chain : in case of series code both SGW1_1 and SGW1_2 are part of chain 1 so returning 0 in case of SGW_ID_2 as well.
				if ( (swid==(Constants.SGW_ID_11)) ||  (swid==(Constants.SGW_ID_12)) ||  (swid==(Constants.SGW_ID_13)) )
					return 0;
				else if ( (swid==(Constants.SGW_ID_21)) ||  (swid==(Constants.SGW_ID_22)) ||  (swid==(Constants.SGW_ID_23)) )
					return 1;
				else if ( (swid==(Constants.SGW_ID_31)) ||  (swid==(Constants.SGW_ID_32)) ||  (swid==(Constants.SGW_ID_33)) )
					return 2;
				else if ( (swid==(Constants.SGW_ID_41)) ||  (swid==(Constants.SGW_ID_42)) ||  (swid==(Constants.SGW_ID_43)) )
					return 3;
				else
					// if(DEBUG)
						log.warn("GOT INVALID SGW DPID!!!");
					return 10;
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
				else
					// if(DEBUG)
						log.info("GOT INVALID DGW DPID!!!");
					return 10;
			}


			@SuppressWarnings("serial")
			final static HashMap<String, Integer> CIPHER_ALGO_MAP = new HashMap<String, Integer>()	
			{{
				put("AES", 1);
				put("HmacSHA1", 2);
			}};

		}
