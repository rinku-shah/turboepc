/*****************************************************************
 * This class contains the code of Home Subscriber Server (HSS). *
 * This class connects to the MySql database containing UE      *
 * specific data for verifying the UE details and establish a    *
 * secure communication thereafter                               *
 *****************************************************************/

package org.onosproject.p4tutorial.epc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import com.mysql.jdbc.Driver;
import java.util.Vector;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import org.onosproject.p4tutorial.epc.Rijndael;

import org.slf4j.Logger;
import static org.slf4j.LoggerFactory.getLogger;

class auc_vector_t{
	int[] rand;
	int rand_new;
	int[] xres;
	int[] autn;
	int[] kasme;
	int[] mac_a ;
	int[] ck ;
	int[] ik ;
	int[] ak ;
	int[] key;
	//public auc_vector_t(byte[] rand, byte rand_new, byte[] xres, byte[] autn, byte[] kasme){
	public auc_vector_t(){
		  rand = new int[16]; //uint8_t rand[16];
		  rand_new = 0x0;
		  //uint8_t rand_new;
		  xres = new int[8]; //uint8_t xres[8];
		  autn = new int[16]; //uint8_t autn[16];
		  kasme = new int[32]; //uint8_t kasme[32];
		  mac_a = new int[8];
		  ck = new int[16];
		  ik = new int[16];
		  ak = new int[6];
		  key = new int[16];
		/// Initialize RAND ///
			for(int i=0; i<16; i++){
				rand[i] = Utils.randInt(6, 255); // Any range of numbers
			}
			/// RAND init done
			
		/*this.rand = rand;
		this.rand_new = rand_new;
		this.xres = xres;
		this.autn = autn;
		this.kasme = kasme;*/
	}
}

public class HSS {
    private static final Logger log = getLogger(EpcApp.class);

    private static final String DB_DRIVER = "com.mysql.jdbc.Driver";
	private static final String DB_CONNECTION = "jdbc:mysql://localhost:3306/HSS";
	private static final String DB_USER = "root";
	private static final String DB_PASSWORD = "root";
	private Connection dbConnection;

		/////PLMN initialization
		//int[] key = new int[16];
		//plmn=SNID=fixed [0] MCC digit2|MCC digit1
		//				  [1] MNC digit3|MCC digit3
		//		          [2] MNC digit2|MNC digit1
		// example MCC=091  MNC=989
		int[] plmn = new int[3];
		/*		plmn[0] = 0x9 | 0x0;
				plmn[1] = 0x9 | 0x1;
				plmn[2] = 0x8 | 0x9;*/
		/////PLMN initialization done
		
		//// SQN comes from UE (unint8_t sqn[6]) /////
		int[] sqn = {99,124,119,123,
					107,111};
		//// SQN init done ////
		
		
		//int[][][] roundKeys= new int[11][4][4];
		
		/// RAND (uint8_t rand[16])
		//byte[] rand = new byte[16];
		//long rand;
		/// RAND declaration done
		
		/// Initialize AMF 
		int[] amf = { 0x80,  0x00};//new byte[16];
		/// AMF init done

	public HSS() {
		dbConnection = getDBConnection();
		if(dbConnection==null){
			log.info("null dbconnection");
        }
		else{
		log.info("created db connection in HSS....");
		}
		plmn[0] = 0x9 | 0x0;
		plmn[1] = 0x9 | 0x1;
		plmn[2] = 0x8 | 0x9;
		
	}
	public void display(String msg, int dst[], int len){
		System.out.print( msg + "=");
		for(int j=0; j<len; j++)
			System.out.print(String.format("0x%02X",dst[j])+ " ");
		System.out.println();
	}
	
	public void displayRoundKeys(int[][][] roundKeys){
		System.out.println("RoundKeys:= ");
			for(int p=0; p<11; p++)
				for(int q=0; q<4; q++)
					for(int r=0; r<4; r++)
					{
						System.out.print(String.format("0x%02X",roundKeys[p][q][r])+ " ");
					}
			System.out.println();
	}
  
	@SuppressWarnings("resource")
	/*
	 * This method validates the UE on the various parameters like IMSI.
	 */
	
	public auc_vector_t validateUser(String imsi, int SN_ID, String nw_type, String SQN,
		String tai, int[][][] roundKeys) {
		// imsi: International mobile subscriber identity, SN_ID: Serving network
		// Id, nw_type: Network type identifier, SQN: UE Sequence number, tai:
		// Tracking area identifier
		// Long key;
		// long rand;
		auc_vector_t av = new auc_vector_t();
		PreparedStatement preparedStatement = null;
		ResultSet rs = null;
		String selectSQL = "SELECT key_id from ue_data where imsi = ?";
		try {
			// selectSQL = "SELECT * from ue_data";
			selectSQL = "SELECT key_id from ue_data where imsi = ?";
			preparedStatement = dbConnection.prepareStatement(selectSQL);
			preparedStatement.setLong(1, Long.parseLong(imsi));
			for (int i = 0; i < 1; i++) {
				rs = preparedStatement.executeQuery();
			}
			if (rs.next()) {
				Long temp = rs.getLong("key_id");
				av.key[0] =  (int) (temp & 0xFF);
				for(int i=1; i<16; i++){
					av.key[i] = av.key[0];
				}
				if(Constants.DEBUG)
					log.warn("got key in HSS= {}",av.key);
			} else {
				log.info("Error in selecting UE tracking area...");
				return null;
			}

			// key = Long.parseLong(imsi)/1000;   // for now hardcoiding it because of onos jdbc issue.

							// 			rand = Utils.randInt(25, 84); // Any range of numbers
							// 		    if(Constants.DEBUG){
							// 		    	log.warn(" in HSS key = {}",key);
							// 		    	log.warn(" in HSS rand = {}",rand);
							// 		    	log.warn(" in HSS SQN = {}",SQN);
							// 		    	log.warn(" in HSS SN_ID = {}",SN_ID);
							// 			}
							// //			long tempArray[] = new long[4];
							// 		    long tempArray[] = EPS_AKA_algorithm(key, rand, SQN, SN_ID);

							// 			// tempArray[0]: autn, tempArray[1]: xres, tempArray[2]: K_ASME
										
							// 			return tempArray[1] + Constants.SEPARATOR + tempArray[0]
							// 					+ Constants.SEPARATOR + rand + Constants.SEPARATOR
							// 					+ tempArray[2];
		} catch (SQLException e) {
			log.warn("got SQL Exception : {}",e.getMessage());
			return null;
		} finally {
			try {
				if (preparedStatement != null) {
					preparedStatement.close();
				}
				if (rs != null) {
					rs.close();
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		//Initialize opP to all 1's
		int in =  0xFF; // whatever goes here
		int[] opP = new int[16];
		int[] opC = new int[16];
		for (int i=0; i<16; i++){
			opP[i] = in;
		}
		//Generate opC using key, opP
		ComputeOPc(av.key, opP, opC, roundKeys);
		//Generate AV
		
		generate_vector(opC, Long.parseLong(imsi) , av.key, plmn,sqn, roundKeys, av);
		/*display("KEY:", key, 16);
		display("RAND:", av.rand, 16);
		display("XRES", av.xres, 8);*/
		///// Done till here //////
		//long tempArray[] = EPS_AKA_algorithm(key, rand, SQN, SN_ID); 
		// tempArray[0]: autn, tempArray[1]: xres, tempArray[2]: K_ASME
		//returns xres, autn, rand, K_ASME 
		/*return tempArray[1] + Constants.SEPARATOR + tempArray[0]
				+ Constants.SEPARATOR + rand + Constants.SEPARATOR
				+ tempArray[2];*/
		/*display("XRES:", av.xres, 8);
		display("AUTN:", av.autn, 16);
		display("RAND:", av.rand, 16);
		display("KASME:", av.kasme, 32);*/
		/*System.out.println(av.xres.toString() + Constants.SEPARATOR + av.autn.toString() + Constants.SEPARATOR + 
				av.rand.toString() + Constants.SEPARATOR + av.kasme.toString());*/
		/*return av.xres.toString() + Constants.SEPARATOR + av.autn.toString() + Constants.SEPARATOR + 
				av.rand.toString() + Constants.SEPARATOR + av.kasme.toString();*/
		return av;
	
	}

	/*-------------------------------------------------------------------
	 * Function to compute OPc from OP and K.
	 *-----------------------------------------------------------------*/
	void ComputeOPc( int[] kP, int[] opP, int[] opcP, int[][][] roundKeys)
	{
	  int i;

	  Rijndael.RijndaelKeySchedule( kP, roundKeys );
      //displayRoundKeys(roundKeys);
	  
	  /*System.out.print("Compute kP: ");
	  for(int j=0; j<16; j++)
		  System.out.print(kP[j]+ " ");
	  System.out.println();*/
	  
	  //display("Compute OPc:k:", kP,16);
	  
	  Rijndael.RijndaelEncrypt( opP, opcP, roundKeys );
	  /*printf("\tIn:\t%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n\tRinj:\t%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
			  opP[0],opP[1],opP[2],opP[3],opP[4],opP[5],opP[6],opP[7],
			  opP[8],opP[9],opP[10],opP[11],opP[12],opP[13],opP[14],opP[15],
		      opcP[0],opcP[1],opcP[2],opcP[3],opcP[4],opcP[5],opcP[6],opcP[7],
		      opcP[8],opcP[9],opcP[10],opcP[11],opcP[12],opcP[13],opcP[14],opcP[15] );
*/
	  /*System.out.print("Compute opcP: ");
	  for(int j=0; j<16; j++)
		  System.out.print(opcP[j]+ " ");
	  System.out.println();*/
	 /* display("In:", opP,16);
	  display("In:", opcP,16);*/
	  
	  for (i=0; i<16; i++)
		  opcP[i] ^= opP[i];
	 /* printf("\tOut:\t%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
		         opcP[0],opcP[1],opcP[2],opcP[3],opcP[4],opcP[5],opcP[6],opcP[7],
		         opcP[8],opcP[9],opcP[10],opcP[11],opcP[12],opcP[13],opcP[14],opcP[15] );
*/
	 /* System.out.print("Compute opcP new: ");
	  for(int j=0; j<16; j++)
		  System.out.print(opcP[j]+ " ");
	  System.out.println();*/
	  //display("Out:", opcP,16);
	  
	  return;
	} /* end of function ComputeOPc */
		
	/*-------------------------------------------------------------------
	* Function to compute AuthenticationVector from OPC, imsi, key, plmn, and sqn.
	*-----------------------------------------------------------------*/	
	void generate_vector(int[] opc, long imsi, int[] key, int[] plmn, int[] sqn, int[][][] roundK , auc_vector_t vector)
	{
	/* in E-UTRAN an authentication vector is composed of:
	* - RAND
	* - XRES
	* - AUTN
	* - KASME
	*/
		//public auc_vector_t(byte[] rand, byte rand_new, byte[] xres, byte[] autn, byte[] kasme)
		
	//auc_vector_t vector = new auc_vector_t();
	//uint8_t amf[] = { 0x80, 0x00 };
		
	/*int[] mac_a = new int[8];
	int[] ck = new int[16];
	int[] ik = new int[16];
	int[] ak = new int[6];*/

	/*if (vector == NULL) {
	return EINVAL;
	}
	*/
	/* Compute MAC */

	f1(opc, key, vector.rand, sqn, amf, vector.mac_a, roundK);

	/*print_buffer("MAC_A   : ", mac_a, 8);
	print_buffer("SQN     : ", sqn, 6);
	print_buffer("RAND    : ", vector->rand, 16);*/

	/*display("MAC_A", mac_a, 8);
	display("SQN", sqn, 6);
	display("RAND",vector.rand,16);*/
	/*System.out.println("MAC_A= " + mac_a.toString() + " SQN= " 
			+ sqn.toString() + " RAND= " + vector.rand.toString());*/

	/* Compute XRES, CK, IK, AK */
	f2345(opc, key, vector.rand, vector.xres, vector.ck, vector.ik, vector.ak, roundK);
	/*print_buffer("AK      : ", ak, 6);
	print_buffer("CK      : ", ck, 16);
	print_buffer("IK      : ", ik, 16);
	print_buffer("XRES    : ", vector->xres, 8);*/
	/*display("AK", ak, 6);
	display("CK", ck, 16);
	display("IK", ik, 16);
	display("XRES", vector.xres, 8);*/
	/*System.out.println("AK= " + ak.toString() + " CK= " 
			+ ck.toString() + " IK= " + ik.toString() + 
			" XRES= " + vector.xres.toString());
	*/
	/* AUTN = SQN ^ AK || AMF || MAC */
	generate_autn(sqn, vector.ak, amf, vector.mac_a, vector.autn);

	//print_buffer("AUTN    : ", vector->autn, 16);
	//display("AUTN", vector.autn, 16);
	//System.out.println("AUTN= " + vector.autn.toString());

	derive_kasme(vector.ck, vector.ik, plmn, sqn, vector.ak, vector.kasme);
	//print_buffer("KASME   : ", vector->kasme, 32);
	//display("KASME", vector.kasme, 32);
	//System.out.println("KASME= " + vector.kasme.toString());

	//return vector;
	}/* end of function generate_vector */
	/****
	 * Function f1
	 * @param opc
	 * @param k
	 * @param _rand
	 * @param sqn
	 * @param amf
	 * @param mac_a
	 */
	void f1 ( int[] opc, int[] k, int[] _rand, int[] sqn, int[] amf, int[] mac_a, int[][][] roundKeys)
	{
	int[] temp = new int[16];
	int[] in1 = new int[16];
	int[] out1 = new int[16];
	int[] rijndaelInput = new int[16];
	int i;
	/*display("RAND in f1", _rand, 16);
	displayRoundKeys(roundKeys);*/

	Rijndael.RijndaelKeySchedule( k, roundKeys );
	//displayRoundKeys(roundKeys);
	for (i=0; i<16; i++){
	//System.out.println("RANDi: "+ String.format("0x%02X",_rand[i]) +" OPCi: "+String.format("0x%02X",opc[i]));
	rijndaelInput[i] =  (_rand[i] ^ opc[i]);// & 0xff;
	}

	Rijndael.RijndaelEncrypt( rijndaelInput, temp, roundKeys );

	for (i=0; i<6; i++) {
	in1[i] = sqn[i]; // & 0xff;
	in1[i+8] = sqn[i]; // & 0xff;
	}

	for (i=0; i<2; i++) {
	in1[i+6] = amf[i]; //& 0xff;
	in1[i+14] = amf[i]; //& 0xff;
	}

	/* XOR op_c and in1, rotate by r1=64, and XOR *
	* on the constant c1 (which is all zeroes) */
	for (i=0; i<16; i++)
	rijndaelInput[(i+8) % 16] =  (in1[i] ^ opc[i]); //& 0xff;

	/* XOR on the value temp computed before */
	for (i=0; i<16; i++)
	rijndaelInput[i] = (rijndaelInput[i] ^ temp[i]); // & 0xff;

	Rijndael.RijndaelEncrypt( rijndaelInput, out1, roundKeys );

	for (i=0; i<16; i++)
	out1[i] = (out1[i] ^ opc[i]); // & 0xff;

	for (i=0; i<8; i++)
	mac_a[i] = out1[i]; // & 0xff;

	return;
	} /* end of function f1 */

	/*-------------------------------------------------------------------
	* Algorithms f2-f5
	*-------------------------------------------------------------------
	*
	* Takes key K and random challenge RAND, and returns response RES,
	* confidentiality key CK, integrity key IK and anonymity key AK.
	*
	*-----------------------------------------------------------------*/
	void f2345 ( int[] opc, int[] k, int[] _rand, int[] res, int[] ck, int[] ik, int[] ak, int[][][] roundKeys)
	{
	int[] temp = new int[16];
	int[] out = new int[16];
	int[] rijndaelInput = new int[16];
	int i;
	Rijndael.RijndaelKeySchedule( k, roundKeys );
	//displayRoundKeys(roundKeys);
	for (i=0; i<16; i++)
		rijndaelInput[i] =  (_rand[i] ^ opc[i]) & 0xff;

	Rijndael.RijndaelEncrypt( rijndaelInput, temp, roundKeys );

	/* To obtain output block OUT2: XOR OPc and TEMP, *
	* rotate by r2=0, and XOR on the constant c2 (which *
	* is all zeroes except that the last bit is 1). */
	for (i=0; i<16; i++)
		rijndaelInput[i] =  (temp[i] ^ opc[i]) & 0xff ;

	rijndaelInput[15] = (rijndaelInput[15] ^ 1) & 0xff;
	Rijndael.RijndaelEncrypt( rijndaelInput, out, roundKeys );

	for (i=0; i<16; i++)
		out[i] = (out[i] ^ opc[i]) & 0xff;

	for (i=0; i<8; i++)
		res[i] = out[i+8] & 0xff;

	for (i=0; i<6; i++)
		ak[i] = out[i] & 0xff;

	/* To obtain output block OUT3: XOR OPc and TEMP, *
	* rotate by r3=32, and XOR on the constant c3 (which *
	* is all zeroes except that the next to last bit is 1). */

	for (i=0; i<16; i++)
		rijndaelInput[(i+12) % 16] =  (temp[i] ^ opc[i])& 0xff;

	rijndaelInput[15] ^= 2;
	Rijndael.RijndaelEncrypt( rijndaelInput, out, roundKeys );

	for (i=0; i<16; i++)
		out[i] = (out[i] ^ opc[i]) & 0xff;

	for (i=0; i<16; i++)
		ck[i] = out[i] & 0xff;

	/* To obtain output block OUT4: XOR OPc and TEMP, *
	* rotate by r4=64, and XOR on the constant c4 (which *
	* is all zeroes except that the 2nd from last bit is 1). */
	for (i=0; i<16; i++)
		rijndaelInput[(i+8) % 16] =  (temp[i] ^ opc[i])& 0xff;

	rijndaelInput[15] = (rijndaelInput[15] ^ 4) & 0xff;
	Rijndael.RijndaelEncrypt( rijndaelInput, out, roundKeys );

	for (i=0; i<16; i++)
		out[i] = (out[i] ^ opc[i]) & 0xff;

	for (i=0; i<16; i++)
		ik[i] = out[i] & 0xff;

	return;
	} /* end of function f2345 */

	/****
	 * Generate AUTN-16B
	 * autn[0..5]=sqn^ak
	 * autn[6]=amf
	 * autn[8..15]=mac_a //8B
	 * @param sqn
	 * @param ak
	 * @param amf
	 * @param mac_a
	 * @param autn
	 */
	void generate_autn(int[] sqn, int[] ak, int[] amf, int[] mac_a, int[] autn)
	{
	int i;

	for (i = 0; i < 6; i++) {
		autn[i] =  (sqn[i] ^ ak[i]) & 0xff;
	}
	autn[6] = amf[0] & 0xff;
	autn[7] = amf[1] & 0xff;
	
	for(i=8; i<16; i++)
		autn[i] = mac_a[i-8] & 0xff;
	/*memcpy(&autn[6], amf, 2);
	memcpy(&autn[8], mac_a, 8);*/
	}
	/**
	 * Function derive_kasme
	 * @param ck
	 * @param ik
	 * @param plmn
	 * @param sqn
	 * @param ak
	 * @param kasme
	 */
	void derive_kasme(int[] ck, int[] ik, int[] plmn, int[] sqn, int[] ak, int[] kasme)
	{
		int[] s = new int[14];
		int i;
		int[] key = new int[32];
		
		/* The input key is equal to the concatenation of CK and IK */
		for(i=0; i<16; i++)
			key[i] = ck[i] & 0xff;
		for(i=16; i<32; i++)
			key[i] = ik[i-16]& 0xff;
		/*memcpy(&key[0], ck, 16);
		memcpy(&key[16], ik, 16);*/
		
		/*if (hss_config.valid_opc == 0) {
		SetOP(hss_config.operator_key);
		}*/
		
		/* FC */
		s[0] = 0x10;
		
		/* SN id is composed of MCC and MNC
		* Octets:
		*   1      MCC digit 2 | MCC digit 1
		*   2      MNC digit 3 | MCC digit 3
		*   3      MNC digit 2 | MNC digit 1
		*/
		//memcpy(&s[1], plmn, 3);
		s[1] = plmn[0] & 0xff;
		s[2] = plmn[1] & 0xff;
		s[3] = plmn[2] & 0xff;
		/* L0 */
		s[4] = 0x00 & 0xff;
		s[5] = 0x03 & 0xff;
		
		/* P1 */
		for (i = 0; i < 6; i++) {
		s[6 + i] =  (sqn[i] ^ ak[i]) & 0xff;
		}
		
		/* L1 */
		s[12] = 0x00;
		s[13] = 0x06;
		
	/*	#if defined(DEBUG_AUC_KDF)
		
		for (i = 0; i < 32; i++)
		printf("0x%02x ", key[i]);
		
		printf("\n");
		
		for (i = 0; i < 14; i++)
		printf("0x%02x ", s[i]);
		
		printf("\n");
		#endif*/
		
	kasme = kdf(key, 32, s, 14, kasme, 32);
	} /*end of function derive_kasme */

	/***
	 * Function kdf
	 * @param key
	 * @param key_len
	 * @param s
	 * @param s_len
	 * @param out
	 * @param out_len
	 */
	int[] kdf(int[] key, int key_len, int[] s, int s_len, int[] out, int out_len)
	{
	/*struct hmac_sha256_ctx ctx;

	memset(&ctx, 0, sizeof(ctx));

	hmac_sha256_set_key(&ctx, key_len, key);
	hmac_sha256_update(&ctx, s_len, s);
	hmac_sha256_digest(&ctx, out_len, out);*/
	return hmacSha(key, s);
	} /*End of function kdf */

	/**
	 * function hmacSHA256
	 * @param key
	 * @param val //s
	 * @param out
	 * @return
	 */
	private static int[] hmacSha(int[] key, int[] val) {
		String SHA_TYPE="HmacSHA256";
		try {
			SecretKeySpec signingKey = new SecretKeySpec(key.toString().getBytes("UTF-8"), SHA_TYPE);
			Mac mac = Mac.getInstance(SHA_TYPE);
			mac.init(signingKey);
			byte[] rawHmac = mac.doFinal(val.toString().getBytes("UTF-8"));

			int[] hexArray = {
					'0', '1', '2', '3',
					'4', '5', '6', '7',
					'8', '9', 'a', 'b',
					'c', 'd', 'e', 'f'
			};
			int[] hexChars = new int[rawHmac.length * 2];
			for ( int j = 0; j < rawHmac.length; j++ ) {
				int v = rawHmac[j] & 0xFF;
				hexChars[j * 2] = hexArray[v >>> 4] & 0xff;
				hexChars[j * 2 + 1] = hexArray[v & 0x0F] & 0xff;
			}
			return hexChars;
		}
		catch (Exception ex) {
			throw new RuntimeException(ex);
		}
	}/*end of function hmacSha */

	/*
	 * This method featches the ID of PGW based on the APN (Access Point Name) specified by the UE
	 */
	@SuppressWarnings("resource")
	public String getPGateway(String apn) {

			// return Integer.toString(Constants.PGW_ID); // hardcoding PGW dpid as 4 for all apns as configured in Constants.java
		/***************TBD : after database issue gets resolved*****************/

		PreparedStatement preparedStatement = null;
		// DatapathId dpid = null;
		String dpid="";
		ResultSet rs = null;
		String selectSQL = "SELECT pgw_dpid from apn_to_pgw where apn = ?";
		try {
			preparedStatement = dbConnection.prepareStatement(selectSQL);
			preparedStatement.setLong(1, Long.parseLong(apn));
			rs = preparedStatement.executeQuery();
			if (rs.next()) {
				dpid = String.valueOf(rs.getLong("pgw_dpid"));
			} else {
				return null;
			}
			//log.info("pgw_dpid from db = {}",dpid);
			return dpid;
		} catch (SQLException e) {
			log.warn(e.getMessage());
			return null;
		} finally {
			try {
				if (preparedStatement != null) {
					preparedStatement.close();
				}
				if (rs != null) {
					rs.close();
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	/*
	 * Authentication & Key Agreement algorithm
	 */
	private long[] EPS_AKA_algorithm(long key, long rand, int SQN, int SN_ID) { 
		long xres, autn, CK, IK, K_ASME; 
		// CK: Cipher key, IK: Integrity key,
		// ASME: Access Security Management
		// Entity (in this case MME)
		xres = rand * key + SQN;
		autn = (rand - 1) * (key + 1) - SQN;
		CK = (rand + 1) * (key - 1) - (SQN + 1);
		IK = (rand + 1) * (key + 1) - (SQN - 1);
		K_ASME = KDF(SQN, SN_ID, CK, IK);
		long temp[] = {autn,xres,K_ASME};
		return temp;
//		return new long[] { autn, xres, K_ASME };
	}

	/*
	 * Key derivation function
	 */
	private long KDF(int SQN, int SN_ID, long CK, long IK) { 
		long K_ASME; // ASME: Access Security Management Entity (in this case MME)
		K_ASME = SQN * CK + SN_ID * IK;
		return K_ASME;
	}

	/*
	 * Method to get a database connection to the mysql database holding HSS data
	 */
	private Connection getDBConnection() {
        String driverName = Driver.class.getName();
		Connection dbConnection = null;
		try {
			//Class.forName(DB_DRIVER);
			Class.forName(driverName);
//			ClassLoader.forName(DB_DRIVER);

		} catch (ClassNotFoundException e) {
			log.warn("classnotfound {}",e.getMessage());
		}

		try {
			dbConnection = DriverManager.getConnection(DB_CONNECTION, DB_USER,
					DB_PASSWORD);
			return dbConnection;
		} catch (SQLException e) {
			log.warn("some sql exception = {}",e.getMessage());
		}
		return dbConnection;
	}
}
