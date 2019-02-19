/********************************************************************
 * This file contains all the functionalities associated with a UE. *
 ********************************************************************/

#include "ue.h"
#include <time.h>
#include<iomanip>
#include <vector>
#include "nettle/hmac.h"

typedef uint8_t  u8;
typedef uint32_t u32;

/* UE Authentication and tunnel setup codes */
string AUTHENTICATION_FAILURE = "-1";
string AUTHENTICATION_STEP_ONE = "1"; 	// Attach request
string AUTHENTICATION_STEP_TWO = "2";
string AUTHENTICATION_STEP_THREE = "3";
string NAS_STEP_ONE = "4";
string SEND_APN = "5";
string SEND_IP_SGW_TEID = "6";
string SEND_UE_TEID = "7";
string ATTACH_ACCEPT = "8";
string DETACH_REQUEST = "9";
string DETACH_ACCEPT = "10";
string REQUEST_STARTING_IP = "12";
string SEND_STARTING_IP = "13";
string UE_CONTEXT_RELEASE_REQUEST = "14";
string UE_CONTEXT_RELEASE_COMMAND = "15";
string UE_CONTEXT_RELEASE_COMPLETE = "16";
string UE_SERVICE_REQUEST = "17";
string INITIAL_CONTEXT_SETUP_REQUEST = "18";
string INITIAL_CONTEXT_SETUP_RESPONSE = "19";
string NAS_STEP_TWO = "20";
string PAGING_REQUEST = "21";
string INITIATE_NETWORK_SERVICE_REQUEST = "22";
string SINK_SERVICE_REQUEST = "23";
string APU_EXIT = "24";


char * SEPARATOR = "@:##:@";
char * INTSEPARATOR = "^";


int SN_ID = 1; // Serving Network Id of MME
int teid = 1;
static int count=0;

/*-------------------- Rijndael round subkeys ---------------------*/
//u8 roundKeys[11][4][4];
/*--------------------- Rijndael S box table ----------------------*/
u8 S[256] = {
  99,124,119,123,242,107,111,197, 48, 1,103, 43,254,215,171,118,
  202,130,201,125,250, 89, 71,240,173,212,162,175,156,164,114,192,
  183,253,147, 38, 54, 63,247,204, 52,165,229,241,113,216, 49, 21,
  4,199, 35,195, 24,150, 5,154, 7, 18,128,226,235, 39,178,117,
  9,131, 44, 26, 27,110, 90,160, 82, 59,214,179, 41,227, 47,132,
  83,209, 0,237, 32,252,177, 91,106,203,190, 57, 74, 76, 88,207,
  208,239,170,251, 67, 77, 51,133, 69,249, 2,127, 80, 60,159,168,
  81,163, 64,143,146,157, 56,245,188,182,218, 33, 16,255,243,210,
  205, 12, 19,236, 95,151, 68, 23,196,167,126, 61,100, 93, 25,115,
  96,129, 79,220, 34, 42,144,136, 70,238,184, 20,222, 94, 11,219,
  224, 50, 58, 10, 73, 6, 36, 92,194,211,172, 98,145,149,228,121,
  231,200, 55,109,141,213, 78,169,108, 86,244,234,101,122,174, 8,
  186,120, 37, 46, 28,166,180,198,232,221,116, 31, 75,189,139,138,
  112, 62,181,102, 72, 3,246, 14, 97, 53, 87,185,134,193, 29,158,
  225,248,152, 17,105,217,142,148,155, 30,135,233,206, 85, 40,223,
  140,161,137, 13,191,230, 66,104, 65,153, 45, 15,176, 84,187, 22,
};
/*------- This array does the multiplication by x in GF(2^8) ------*/
u8 Xtime[256] = {
  0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
  32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
  64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94,
  96, 98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,
  128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,
  160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,
  192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,
  224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,
  27, 25, 31, 29, 19, 17, 23, 21, 11, 9, 15, 13, 3, 1, 7, 5,
  59, 57, 63, 61, 51, 49, 55, 53, 43, 41, 47, 45, 35, 33, 39, 37,
  91, 89, 95, 93, 83, 81, 87, 85, 75, 73, 79, 77, 67, 65, 71, 69,
  123,121,127,125,115,113,119,117,107,105,111,109, 99, 97,103,101,
  155,153,159,157,147,145,151,149,139,137,143,141,131,129,135,133,
  187,185,191,189,179,177,183,181,171,169,175,173,163,161,167,165,
  219,217,223,221,211,209,215,213,203,201,207,205,195,193,199,197,
  251,249,255,253,243,241,247,245,235,233,239,237,227,225,231,229
};


/*
 * Constructor: Create a UE object.
 */
UserEquipment::UserEquipment(int ue_num){
	int f = key_generation(ue_num);
	//memcpy(key, &key_str, 16);
	//imsi = key[0]*1000;
	imsi = ue_num * 1000;
	//cout<<"imsi=" << imsi<<endl;
	//cout<<"key_str="<<std::hex<<key_str<<endl;
	ue_key = ue_num;
	msisdn = 9000000000 + key[0];
	apn = ue_num;
	tai = ue_num + 10; 	// Tracking area ID
	ue_nw_capability = random_ue_nw_capability(generator); 	// Random
	uint8_t roundKeys[11][4][4] = {0xff};
}

/*
 * This function generates UE key (same as UE ID in this case).
 */
int UserEquipment::key_generation(int ue_num){
	int i;
	for (i=0; i<16; i++){
		key[i] = ue_num;
		//cout<<std::hex << static_cast<int>(key[i])<<" ";
	}
	//cout<<endl;
	//return ue_num;
	return 1;
}

/*-------------------------------------------------------------------
 * Rijndael key schedule function. Takes 16-byte key and creates
 * all Rijndael's internal subkeys ready for encryption.
 *-----------------------------------------------------------------*/
void UserEquipment::RijndaelKeySchedule( const u8 key[16] )
{
  u8 roundConst;
  int i, j;

  /*printf("RijndaelKeySchedule: K %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
		  key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7],
		  key[8],key[9],key[10],key[11],key[12],key[13],key[14],key[15] );*/
  /* first round key equals key */
  for (i=0; i<16; i++)
    roundKeys[0][i & 0x03][i>>2] = key[i];

  roundConst = 1;

  /* now calculate round keys */
  for (i=1; i<11; i++) {
    roundKeys[i][0][0] = S[roundKeys[i-1][1][3]]
                         ^ roundKeys[i-1][0][0] ^ roundConst;
    roundKeys[i][1][0] = S[roundKeys[i-1][2][3]]
                         ^ roundKeys[i-1][1][0];
    roundKeys[i][2][0] = S[roundKeys[i-1][3][3]]
                         ^ roundKeys[i-1][2][0];
    roundKeys[i][3][0] = S[roundKeys[i-1][0][3]]
                         ^ roundKeys[i-1][3][0];

    for (j=0; j<4; j++) {
      roundKeys[i][j][1] = roundKeys[i-1][j][1] ^ roundKeys[i][j][0];
      roundKeys[i][j][2] = roundKeys[i-1][j][2] ^ roundKeys[i][j][1];
      roundKeys[i][j][3] = roundKeys[i-1][j][3] ^ roundKeys[i][j][2];
    }

    /* update round constant */
    roundConst = Xtime[roundConst];
  }

  return;
} /* end of function RijndaelKeySchedule */
/* Round key addition function */
void UserEquipment::KeyAdd(u8 state[4][4], u8 roundKeys[11][4][4], int round)
{
  int i, j;

  for (i=0; i<4; i++)
    for (j=0; j<4; j++)
      state[i][j] ^= roundKeys[round][i][j];

  return;
}
/* Byte substitution transformation */
int UserEquipment::ByteSub(u8 state[4][4])
{
  int i, j;

  for (i=0; i<4; i++)
    for (j=0; j<4; j++)
      state[i][j] = S[state[i][j]];

  return 0;
}
/* Row shift transformation */
void UserEquipment::ShiftRow(u8 state[4][4])
{
  u8 temp;
  /* left rotate row 1 by 1 */
  temp = state[1][0];
  state[1][0] = state[1][1];
  state[1][1] = state[1][2];
  state[1][2] = state[1][3];
  state[1][3] = temp;
  /* left rotate row 2 by 2 */
  temp = state[2][0];
  state[2][0] = state[2][2];
  state[2][2] = temp;
  temp = state[2][1];
  state[2][1] = state[2][3];
  state[2][3] = temp;
  /* left rotate row 3 by 3 */
  temp = state[3][0];
  state[3][0] = state[3][3];
  state[3][3] = state[3][2];
  state[3][2] = state[3][1];
  state[3][1] = temp;
  return;
}
/* MixColumn transformation*/
void UserEquipment::MixColumn(u8 state[4][4])
{
  u8 temp, tmp, tmp0;
  int i;

  /* do one column at a time */
  for (i=0; i<4; i++) {
    temp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
    tmp0 = state[0][i];
    /* Xtime array does multiply by x in GF2^8 */
    tmp = Xtime[state[0][i] ^ state[1][i]];
    state[0][i] ^= temp ^ tmp;
    tmp = Xtime[state[1][i] ^ state[2][i]];
    state[1][i] ^= temp ^ tmp;
    tmp = Xtime[state[2][i] ^ state[3][i]];
    state[2][i] ^= temp ^ tmp;
    tmp = Xtime[state[3][i] ^ tmp0];
    state[3][i] ^= temp ^ tmp;
  }

  return;
}
/*-------------------------------------------------------------------
 * Rijndael encryption function. Takes 16-byte input and creates
 * 16-byte output (using round keys already derived from 16-byte
 * key).
 *-----------------------------------------------------------------*/
void UserEquipment::RijndaelEncrypt( const u8 input[16], u8 output[16] )
{
  u8 state[4][4];
  int i, r;

  /*printf("Rijndael input:\t%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
		  input[0],input[1],input[2],input[3],input[4],input[5],input[6],input[7],
		  input[8],input[9],input[10],input[11],input[12],input[13],input[14],input[15]);*/

  /* initialise state array from input byte string */
  for (i=0; i<16; i++)
    state[i & 0x3][i>>2] = input[i];

  /* add first round_key */
  KeyAdd(state, roundKeys, 0);

  /* do lots of full rounds */
  for (r=1; r<=9; r++) {
    ByteSub(state);
    ShiftRow(state);
    MixColumn(state);
    KeyAdd(state, roundKeys, r);
  }

  /* final round */
  ByteSub(state);
  ShiftRow(state);
  KeyAdd(state, roundKeys, r);

  /* produce output byte string from state array */
  for (i=0; i<16; i++) {
    output[i] = state[i & 0x3][i>>2];
  }
  /*printf("Rijndael output:\t%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
		  output[0],output[1],output[2],output[3],output[4],output[5],output[6],output[7],
		  output[8],output[9],output[10],output[11],output[12],output[13],output[14],output[15]);*/
  return;
} /* end of function RijndaelEncrypt */

/*-------------------------------------------------------------------
 * Function to compute OPc from OP and K.
 *-----------------------------------------------------------------*/
void UserEquipment::ComputeOPc( const uint8_t kP[16], const uint8_t opP[16], uint8_t opcP[16] )
{
  uint8_t i;
  int p,q,r;

  RijndaelKeySchedule( kP );
  /*printf("RoundKeys:\t");
  for(p=0; p<11; p++)
  	for(q=0; q<4; q++)
	  for(r=0; r<4; r++)
	  {
  		printf("%02X",roundKeys[p][q][r]);
	  }
  printf("\n");

  printf("Compute opc:\n\tK:\t%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
		  kP[0],kP[1],kP[2],kP[3],kP[4],kP[5],kP[6],kP[7],
		  kP[8],kP[9],kP[10],kP[11],kP[12],kP[13],kP[14],kP[15]);*/
  RijndaelEncrypt( opP, opcP );
/*  printf("\tIn:\t%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n\tRinj:\t%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
		  opP[0],opP[1],opP[2],opP[3],opP[4],opP[5],opP[6],opP[7],
		  opP[8],opP[9],opP[10],opP[11],opP[12],opP[13],opP[14],opP[15],
	      opcP[0],opcP[1],opcP[2],opcP[3],opcP[4],opcP[5],opcP[6],opcP[7],
	      opcP[8],opcP[9],opcP[10],opcP[11],opcP[12],opcP[13],opcP[14],opcP[15] );*/

  for (i=0; i<16; i++)
	  opcP[i] ^= opP[i];
/*  printf("\tOut:\t%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
	         opcP[0],opcP[1],opcP[2],opcP[3],opcP[4],opcP[5],opcP[6],opcP[7],
	         opcP[8],opcP[9],opcP[10],opcP[11],opcP[12],opcP[13],opcP[14],opcP[15] );*/

  return;
} /* end of function ComputeOPc */


void UserEquipment::derive_kasme(uint8_t ck[16], uint8_t ik[16], uint8_t plmn[3], uint8_t sqn[6],
                  uint8_t ak[6], uint8_t *kasme)
{
  uint8_t s[14];
  int i;
  uint8_t key[32];

  /* The input key is equal to the concatenation of CK and IK */
  memcpy(&key[0], ck, 16);
  memcpy(&key[16], ik, 16);

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
  memcpy(&s[1], plmn, 3);

  /* L0 */
  s[4] = 0x00;
  s[5] = 0x03;

  /* P1 */
  for (i = 0; i < 6; i++) {
    s[6 + i] = sqn[i] ^ ak[i];
  }

  /* L1 */
  s[12] = 0x00;
  s[13] = 0x06;

#if defined(DEBUG_AUC_KDF)

  for (i = 0; i < 32; i++)
    printf("0x%02x ", key[i]);

  printf("\n");

  for (i = 0; i < 14; i++)
    printf("0x%02x ", s[i]);

  printf("\n");
#endif

  //kdf(key, 32, s, 14, kasme, 32);
}

void UserEquipment::generate_autn(const uint8_t sqn[6], const uint8_t ak[6], const uint8_t amf[2], const uint8_t mac_a[8], uint8_t autn[16])
{
  int i;

  for (i = 0; i < 6; i++) {
    autn[i] = sqn[i] ^ ak[i];
  }

  memcpy(&autn[6], amf, 2);
  memcpy(&autn[8], mac_a, 8);
}

/*-------------------------------------------------------------------
 * Algorithm f1
 *-------------------------------------------------------------------
 *
 * Computes network authentication code MAC-A from key K, random
 * challenge RAND, sequence number SQN and authentication management
 * field AMF.
 *
 *-----------------------------------------------------------------*/
void UserEquipment::f1 ( const uint8_t opc[16], const uint8_t k[16], const uint8_t _rand[16], const uint8_t sqn[6], const uint8_t amf[2],
          uint8_t mac_a[8] )
{
  uint8_t temp[16];
  uint8_t in1[16];
  uint8_t out1[16];
  uint8_t rijndaelInput[16];
  uint8_t i;
  int p,q,r;
  RijndaelKeySchedule( k );
  /*printf("RoundKeys:\t");
  for(p=0; p<11; p++)
  	for(q=0; q<4; q++)
	  for(r=0; r<4; r++)
	  {
  		printf("%02X",roundKeys[p][q][r]);
	  }
  printf("\n");*/
  for (i=0; i<16; i++){
    rijndaelInput[i] = _rand[i] ^ opc[i];
    /*printf("RAND_i: %02X  OPC_i: %02X", _rand[i], opc[i]);
    cout<<endl;*/
  }

  RijndaelEncrypt( rijndaelInput, temp );

  for (i=0; i<6; i++) {
    in1[i] = sqn[i];
    in1[i+8] = sqn[i];
  }

  for (i=0; i<2; i++) {
    in1[i+6] = amf[i];
    in1[i+14] = amf[i];
  }

  /* XOR op_c and in1, rotate by r1=64, and XOR *
   * on the constant c1 (which is all zeroes) */
  for (i=0; i<16; i++)
    rijndaelInput[(i+8) % 16] = in1[i] ^ opc[i];

  /* XOR on the value temp computed before */
  for (i=0; i<16; i++)
    rijndaelInput[i] ^= temp[i];

  RijndaelEncrypt( rijndaelInput, out1 );

  for (i=0; i<16; i++)
    out1[i] ^= opc[i];

  for (i=0; i<8; i++)
    mac_a[i] = out1[i];

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
void UserEquipment::f2345 ( const uint8_t opc[16], const uint8_t k[16], const uint8_t _rand[16],
             uint8_t res[8], uint8_t ck[16], uint8_t ik[16], uint8_t ak[6] )
{
  uint8_t temp[16];
  uint8_t out[16];
  uint8_t rijndaelInput[16];
  uint8_t i;
  int p,q,r;
  RijndaelKeySchedule( k );
  /*printf("RoundKeys:\t");
  for(p=0; p<11; p++)
  	for(q=0; q<4; q++)
	  for(r=0; r<4; r++)
	  {
  		printf("%02X",roundKeys[p][q][r]);
	  }
  printf("\n");*/
  for (i=0; i<16; i++)
    rijndaelInput[i] = _rand[i] ^ opc[i];

  RijndaelEncrypt( rijndaelInput, temp );

  /* To obtain output block OUT2: XOR OPc and TEMP, *
   * rotate by r2=0, and XOR on the constant c2 (which *
   * is all zeroes except that the last bit is 1). */
  for (i=0; i<16; i++)
    rijndaelInput[i] = temp[i] ^ opc[i];

  rijndaelInput[15] ^= 1;
  RijndaelEncrypt( rijndaelInput, out );

  for (i=0; i<16; i++)
    out[i] ^= opc[i];

  for (i=0; i<8; i++)
    res[i] = out[i+8];

  for (i=0; i<6; i++)
    ak[i] = out[i];

  /* To obtain output block OUT3: XOR OPc and TEMP, *
   * rotate by r3=32, and XOR on the constant c3 (which *
   * is all zeroes except that the next to last bit is 1). */

  for (i=0; i<16; i++)
    rijndaelInput[(i+12) % 16] = temp[i] ^ opc[i];

  rijndaelInput[15] ^= 2;
  RijndaelEncrypt( rijndaelInput, out );

  for (i=0; i<16; i++)
    out[i] ^= opc[i];

  for (i=0; i<16; i++)
    ck[i] = out[i];

  /* To obtain output block OUT4: XOR OPc and TEMP, *
   * rotate by r4=64, and XOR on the constant c4 (which *
   * is all zeroes except that the 2nd from last bit is 1). */
  for (i=0; i<16; i++)
    rijndaelInput[(i+8) % 16] = temp[i] ^ opc[i];

  rijndaelInput[15] ^= 4;
  RijndaelEncrypt( rijndaelInput, out );

  for (i=0; i<16; i++)
    out[i] ^= opc[i];

  for (i=0; i<16; i++)
    ik[i] = out[i];

  return;
} /* end of function f2345 */

static inline void print_buffer(const char *prefix, const uint8_t *buffer, int length)
{
  int i;

  fprintf(stdout, "%s", prefix);

  for (i = 0; i < length; i++) {
    fprintf(stdout, "%02x.", buffer[i]);
  }

  fprintf(stdout, "\n");
}


int UserEquipment::generate_vector(uint8_t opc[16], uint64_t imsi, uint8_t key[16], uint8_t plmn[3],
                    uint8_t sqn[6], auc_vector_t *vector)
{
  /* in E-UTRAN an authentication vector is composed of:
   * - RAND
   * - XRES
   * - AUTN
   * - KASME
   */

  uint8_t amf[] = { 0x80, 0x00 };
  /*uint8_t mac_a[8];
  uint8_t ck[16];
  uint8_t ik[16];
  uint8_t ak[6];*/

  if (vector == NULL) {
    return EINVAL;
  }

  /* Compute MAC */
  f1(opc, key, vector->rand, sqn, amf, vector->mac_a);
  //f1(opc, key, rand, sqn, amf, mac_a);

  /*print_buffer("MAC_A   : ", mac_a, 8);
  print_buffer("SQN     : ", sqn, 6);
  print_buffer("RAND    : ", vector->rand, 16);*/

  /* Compute XRES, CK, IK, AK */
  f2345(opc, key, vector->rand, vector->xres, vector->ck, vector->ik, vector->ak);
  /*print_buffer("AK      : ", ak, 6);
  print_buffer("CK      : ", ck, 16);
  print_buffer("IK      : ", ik, 16);
  print_buffer("XRES    : ", vector->xres, 8);*/

  /* AUTN = SQN ^ AK || AMF || MAC */
  generate_autn(sqn, vector->ak, amf, vector->mac_a, vector->autn);

  //print_buffer("AUTN    : ", vector->autn, 16);

  derive_kasme(vector->ck, vector->ik, plmn, sqn, vector->ak, vector->kasme);
  //print_buffer("KASME   : ", vector->kasme, 32);

  return 0;
}

template< typename T >
	std::string int_to_hex( T i )
	{
	std::stringstream stream;
	stream << "0x" 
			<< std::setfill ('0') << std::setw(sizeof(T)) 
			<< std::hex << i;
	return stream.str();
	}

vector<unsigned char> intToBytes(int paramInt)
{
     vector<unsigned char> arrayOfByte(4);
     for (int i = 0; i < 4; i++)
         arrayOfByte[3 - i] = (paramInt >> (i * 8));
     return arrayOfByte;
}

bool UserEquipment::apu_exit(Client &user){
	string send;
	send = APU_EXIT + SEPARATOR ;
	if(DO_DEBUG){
		cout<<"SENT"<<send.c_str()<<endl;
	}
	bzero(user.client_buffer, BUFFER_SIZE);
	sprintf(user.client_buffer, send.c_str());
	user.write_data(APU_EXIT);
	return true;
}

/*
 * This function contains all the steps that take place during the authentication procedure.
 * A mutual authentication takes place between the UE and the MME (i.e. the network).
 */

bool UserEquipment::authenticate(Client &user, bool checkIntegrity){
		string send, receive;
	/*unsigned long long autn;
	unsigned long long rand;
	unsigned long long res;*/
	uint8_t rand[16];
	uint8_t xres[8];
  	uint8_t autn[16];
  	uint8_t kasme[32] = {1};

	//// SQN comes from UE (unint8_t sqn[6]) /////
	uint8_t sqn[6] = {99,124,119,123,107,111};
	//// SQN init done ////
	
	uint8_t plmn[3];
	plmn[0] = 0x9 | 0x0;
	plmn[1] = 0x9 | 0x1;
	plmn[2] = 0x8 | 0x9;

	auc_vector_t av;
	//Initialize opP to all 1's
	uint8_t in = 0xFF;
	uint8_t opP[16], opC[16]={0};
	for (int i=0; i<16; i++){
		opP[i] = in;
	}
	vector<string> tmpArray;
	vector<unsigned long long> authenticationVector;
	time_t curTime;
	time(&curTime);
	//string KSI_ASME = "7";
	int SQN = 1;
	ComputeOPc( key, opP, opC );


	// KSI: Key Selection Identifier, ASME: Access Security Management Entity (MME in this case), SQN: Sequence number
//	cout<<"Befor Send"<<endl;


	// rewriting Authentication Step 1
    struct auth_step_one_t one;

	one.msg_id = 1;     
	
	one.sep1[0] = htons(0x403A);
    one.sep1[1] = htons(0x2323);
    one.sep1[2] = htons(0x3A40);

    one.imsi = htonl(imsi);

	// unsigned char x;
	// x=(imsi >> 24) & 0xFF;
	// cout<<"x = "<<x<<endl;
	// if(x == NULL){
	// 	cout<<"some null###############";
	// 	one.imsi[0]=0x30;
	// }
	// else{
	// 	cout<<"some ###############";
	// }

	// one.imsi[0] =  (imsi >> 24) & 0xFF;
	// one.imsi[1] =  (imsi >> 16) & 0xFF;
	// one.imsi[2] =  (imsi >> 8) & 0xFF;
	// one.imsi[3] =  (imsi) & 0xFF;

	one.sep2[0] = htons(0x403A);
    one.sep2[1] = htons(0x2323);
    one.sep2[2] = htons(0x3A40);


	one.ue_nw_capability = htons(ue_nw_capability);

	one.sep3[0] = htons(0x403A);
    one.sep3[1] = htons(0x2323);
    one.sep3[2] = htons(0x3A40);

	
	// one.ksi_asme = htonl(stoi(KSI_ASME));
	memcpy(one.ksi_asme,&kasme,sizeof(kasme));
	// cout<<"one.ksi_asme = "<<one.ksi_asme<<endl;
	// one.ksi_asme = kasme;

	one.sep4[0] = htons(0x403A);
    one.sep4[1] = htons(0x2323);
    one.sep4[2] = htons(0x3A40);

	one.sqn = htonl(SQN);

	one.sep5[0] = htons(0x403A);
    one.sep5[1] = htons(0x2323);
    one.sep5[2] = htons(0x3A40);

	// one.tai = htonl(tai); 

	one.tai[0] =  (tai >> 56) & 0xFF;
	one.tai[1] =  (tai >> 48) & 0xFF;
	one.tai[2] =  (tai >> 40) & 0xFF;
	one.tai[3] =  (tai >> 32) & 0xFF;
	one.tai[4] =  (tai >> 24) & 0xFF;
	one.tai[5] =  (tai >> 16) & 0xFF;
	one.tai[6] =  (tai >> 8) & 0xFF;
	one.tai[7] =  (tai) & 0xFF;

    bzero(user.client_buffer, BUFFER_SIZE);

	int len=0;

    memcpy(user.client_buffer, &(one.msg_id), sizeof(one.msg_id));
	len+=sizeof(one.msg_id);

    memcpy(user.client_buffer+len, &(one.sep1), sizeof(one.sep1));
	len+=sizeof(one.sep1);

    memcpy(user.client_buffer+len, &(one.imsi), sizeof(one.imsi));
	len+=sizeof(one.imsi);

    memcpy(user.client_buffer+len, &(one.sep2), sizeof(one.sep2));
	len+=sizeof(one.sep2);

    memcpy(user.client_buffer+len, &(one.ue_nw_capability), sizeof(one.ue_nw_capability));
	len+=sizeof(one.ue_nw_capability);

    memcpy(user.client_buffer+len, &(one.sep3), sizeof(one.sep3));
	len+=sizeof(one.sep3);

    memcpy(user.client_buffer+len, &(one.ksi_asme), sizeof(one.ksi_asme));
	len+=sizeof(one.ksi_asme);

    memcpy(user.client_buffer+ len, &(one.sep4), sizeof(one.sep4));
	len+=sizeof(one.sep4);

    memcpy(user.client_buffer+ len, &(one.sqn), sizeof(one.sqn));
	len+=sizeof(one.sqn);

    memcpy(user.client_buffer+ len, &(one.sep5), sizeof(one.sep5));
	len+=sizeof(one.sep5);

    memcpy(user.client_buffer+ len, &(one.tai), sizeof(one.tai));
	len+=sizeof(one.tai);


	// printf("sizeof one.imsi = %ld\n",sizeof(one.imsi));
	// printf("sizeof one = %ld\n",sizeof(one));
	// printf("sizeof struct = %ld\n",sizeof(struct auth_step_one_t ));  
	// printf("data = %s\n",user.client_buffer);     

	user.write_data2(len);

	// ORIGINAL code: uncomment if required 
	// send = AUTHENTICATION_STEP_ONE + SEPARATOR + longToString(imsi) + SEPARATOR + longToString(ue_nw_capability) + SEPARATOR + std::string ( reinterpret_cast< char const* >(kasme) ) + SEPARATOR + std::string ( reinterpret_cast< char const* >(sqn)) + SEPARATOR + longToString(tai);
	// send = AUTHENTICATION_STEP_ONE + SEPARATOR + longToString(imsi) + SEPARATOR + longToString(ue_nw_capability) + SEPARATOR + KSI_ASME + SEPARATOR + to_string(SQN) + SEPARATOR + longToString(tai);
	// bzero(user.client_buffer, BUFFER_SIZE);
	// sprintf(user.client_buffer, send.c_str());
	// user.write_data(AUTHENTICATION_STEP_ONE);


//	cout<<"After write"<<endl;
	time(&curTime);
	// Receive reply from MME: Authentication Step 2
	user.read_data();
//	cout<<"After read"<<endl;
	time(&curTime);
	receive = (string) (user.client_buffer);
	//receive = (string) (user.trim_buffer);
	if(MY_DEBUG){
	cout<<"My Print -- received"<<receive<<endl;
	}
	if (receive.find(SEPARATOR) != std::string::npos) {
		tmpArray.clear();
		tmpArray = split(user.client_buffer, SEPARATOR);
		if(tmpArray[0] == AUTHENTICATION_STEP_TWO){
			if(DO_DEBUG){
				cout <<"AUTHENTICATION_STEP_TWO: RAND = "<<tmpArray[1]<<" autn = "<<tmpArray[2]<<" KSI_ASME = "<<tmpArray[3]<< " for UE with key = "<<ue_key<<endl;
								print_buffer("", key , 16);
												cout<<endl;


			}
			//cout <<"AUTHENTICATION_STEP_TWO: RAND = "<<tmpArray[1]<<" autn = "<<tmpArray[2]<<" KSI_ASME = "<<tmpArray[3]<< " for UE with key = "<<key<<endl;
			/*rand = stoull(tmpArray[1]);
			autn = stoull(tmpArray[2]);
			KSI_ASME = tmpArray[3];*/
			
			//memcpy(rand, &tmpArray[1], 16);
			//memcpy(autn, &tmpArray[2], 16);
			memcpy(kasme, &tmpArray[3], 32);
		   //MAP RAND string to uint8_t

		   	// std::vector<uint8_t> myVector(tmpArray[1].begin(), tmpArray[1].end());
			// uint8_t *rand1 = &myVector[0];

					vector<string> randArray; 
					char rand_char_array[200]; 
					int int_array[64]; //Store integer values of RAND[i]
					// copying the contents of the 
					// string to char array
					strcpy(rand_char_array, tmpArray[1].c_str()); //Convert RAND to char[]
					// cout<<"f3"<<endl;
					//cout<<"rand_char_array = "<<rand_char_array<<endl;
					randArray.clear();
					randArray = split(rand_char_array,INTSEPARATOR);//Pass RAND char[] to split the rand num int[] digits 
					//cout<<"randS= ";
					// cout<<"f4"<<endl;

					for(int i=0; i<16; i++){
					//cout<<tmpArray[i]<<endl; 
					int_array[i]=stoi(randArray[i]); //copy RAND[i] to int array
					// cout<<"f5"<<endl;

					//cout<<tmpArray[i]<<endl; // Print the int digits(byte) 
					rand[i]=(uint8_t)int_array[i];
					//cout<<rand[i]<<endl;
					//printf("%02x ",rand[i]);
					}

		    //cout<<endl;
			/*int_array[0]=stoi(randArray[0]);
			rand[0]=(uint8_t)int_array[0];*/

		    //MAP AUTN string to uint8_t

			// std::vector<uint8_t> myVector1(tmpArray[1].begin(), tmpArray[1].end());
			// uint8_t *autn = &myVector1[0];
			
			
					vector<string> autnArray; 
					char autn_char_array[200]; 
					int int_array1[64]; //Store integer values of RAND[i]
					// copying the contents of the 
					// string to char array
					strcpy(autn_char_array, tmpArray[2].c_str()); //Convert RAND to char[]
					autnArray.clear();
					autnArray = split(autn_char_array,INTSEPARATOR);//Pass RAND char[] to split the rand num int[] digits 
					//cout<<"autnS= ";

					for(int i=0; i<16; i++){
					//cout<<tmpArray[i]<<endl; 
					int_array1[i]=stoi(autnArray[i]); //copy RAND[i] to int array
					//cout<<tmpArray[i]<<endl; // Print the int digits(byte) 
					autn[i]=(uint8_t)int_array1[i];
					//cout<<rand[i]<<endl;
					//printf("%02x ",autn[i]);
					}
		 
		 /*cout<<endl;
			cout<<"Received values:"<<endl;
			print_buffer("RAND:", rand, 16);
			print_buffer("AUTN:", autn, 16);
                        print_buffer("KASME:", kasme, 32);*/
			//authenticationVector = EPS_AKA_algorithm(key, rand, SQN, SN_ID);
			//authenticationVector = EPS_AKA_algorithm(123456, 1234, SQN, SN_ID);
		        /*typedef struct {
			  uint8_t rand[16];
			  uint8_t rand_new;
			  uint8_t xres[8];
			  uint8_t autn[16];
			  uint8_t kasme[32];
			} auc_vector_t;*/
			//memcpy(av->rand, &rand, 16);
			//memcpy(av->autn, &autn, 16);
			//memcpy(av->kasme, &kasme, 16);
			// cout<<"raned  recieved =";
			for(int y=0; y<16; y++){
				// cout<<rand1[y]<<" ";
				// av.rand[y] = rand1[y];
				av.rand[y] = rand[y];

				av.autn[y] = autn[y];
			}
			// cout<<endl;

			generate_vector(opC, imsi, key, plmn, sqn, &av);
			/*print_buffer("RAND:", av.rand, 16);
			print_buffer("AUTN:", av.autn, 16);*/
                        //print_buffer("KASME:", av.kasme, 16);
			// authenticationVector: [0] = autn, [1] = res, [2] = K_ASME

			/*if(DO_DEBUG){
				cout<<"EPS_AKA_algorithm autn = "<<authenticationVector[0]<<" res ="<<authenticationVector[1]<<" K_ASME = "<<authenticationVector[2]<<endl;
			}*/
			if(DO_DEBUG){
				cout<<"EPS_AKA_algorithm autn = "<<autn<<" res ="<<xres<<" K_ASME = "<<kasme<<endl;
			}
			tmpArray.clear();
			time(&curTime);

			// rewriting Authentication Step 3


			//send = AUTHENTICATION_STEP_THREE + SEPARATOR + longToString(imsi) + SEPARATOR + longToString(authenticationVector[1]);
			//send = AUTHENTICATION_STEP_THREE + SEPARATOR + longToString(imsi) + SEPARATOR + xres;

			//string xresS = itoa(av.xres[0]) + itoa(av.xres[1]) + itoa(av.xres[2]) + itoa(av.xres[3]) + itoa(av.xres[4]) + itoa(av.xres[5]) + itoa(av.xres[6]) + itoa(av.xres[7]);
			char s0[4],s1[4],s2[4],s3[4],s4[4],s5[4],s6[4],s7[4];
			//string xresS = 
			//for(int k=0; k<8; k++){
			//	sprintf(s+k,"%d",av.xres[k]);
			//}
            sprintf(s0,"%d",av.xres[0]);
			sprintf(s1,"%d",av.xres[1]);
			sprintf(s2,"%d",av.xres[2]);
			sprintf(s3,"%d",av.xres[3]);
			sprintf(s4,"%d",av.xres[4]);
			sprintf(s5,"%d",av.xres[5]);
			sprintf(s6,"%d",av.xres[6]);
			sprintf(s7,"%d",av.xres[7]);
			string xresS =(string)s0+(string)s1+(string)s2+(string)s3+(string)s4+(string)s5+(string)s6+(string)s7;

			//cout<<"Concatenated RES="<<xresS<<endl;

			if(DO_DEBUG){
				string PxresS =(string)s0+"+"+(string)s1+"+"+(string)s2+"+"+(string)s3+"+"+(string)s4+"+"+(string)s5+"+"+(string)s6+"+"+(string)s7;
				cout<<"XRES= " << PxresS <<endl;
			}


			struct auth_step_three_t three;
			three.msg_id = 3;

			three.sep1[0] = htons(0x403A);
    		three.sep1[1] = htons(0x2323);
    		three.sep1[2] = htons(0x3A40);
			
			three.imsi = htonl(imsi);

			three.sep2[0] = htons(0x403A);
   			three.sep2[1] = htons(0x2323);
    		three.sep2[2] = htons(0x3A40);
			
			// this is already in network byte order so need to apply hton() fn
			// three.res[0] =  (authenticationVector[1] >> 56) & 0xFF;
			// three.res[1] =  (authenticationVector[1] >> 48) & 0xFF;
			// three.res[2] =  (authenticationVector[1] >> 40) & 0xFF;
			// three.res[3] =  (authenticationVector[1] >> 32) & 0xFF;
			// three.res[4] =  (authenticationVector[1] >> 24) & 0xFF;
			// three.res[5] =  (authenticationVector[1] >> 16) & 0xFF;
			// three.res[6] =  (authenticationVector[1] >> 8) & 0xFF;
			// three.res[7] =  (authenticationVector[1]) & 0xFF;
			// cout<<"size of av.xres = "<<sizeof(av.xres)<<endl;
			memcpy(three.res,av.xres,sizeof(av.xres));

			// now write struct elemets to buffer one by one
			bzero(user.client_buffer, BUFFER_SIZE);
			len=0;  // reset length which holds no of bytes written in buffer

			memcpy(user.client_buffer, &(three.msg_id), sizeof(three.msg_id));
			len+=sizeof(three.msg_id);

			memcpy(user.client_buffer+len, &(three.sep1), sizeof(three.sep1));
			len+=sizeof(three.sep1);

			memcpy(user.client_buffer+len, &(one.imsi), sizeof(one.imsi));
			len+=sizeof(three.imsi);

			memcpy(user.client_buffer+len, &(three.sep2), sizeof(three.sep2));
			len+=sizeof(three.sep2);

			memcpy(user.client_buffer+len, &(three.res), sizeof(three.res));
			len+=sizeof(three.res);

			user.write_data2(len);

			// ORIGINAL code: uncomment if required 
				// send = AUTHENTICATION_STEP_THREE + SEPARATOR + longToString(imsi) + SEPARATOR + xresS;
				if(DO_DEBUG){
					cout<<"NOTICE: autn= "<<av.autn<<" rand= "<<av.rand<<endl;
					cout<<"SENT"<<send.c_str()<<endl;
				}
				
				// bzero(user.client_buffer, BUFFER_SIZE);
				// sprintf(user.client_buffer, send.c_str());
				// /////
				// //usleep(my_rand());
				// ////
				// user.write_data(AUTHENTICATION_STEP_THREE);
				time(&curTime);

			
			// Receive reply from MME: Authentication Step 4
			user.read_data();
			time(&curTime);
			receive = (string) (user.client_buffer);
			//receive = (string) (user.trim_buffer);
			if(MY_DEBUG){
			cout<<"My Print -- received"<<receive<<endl;
			}
			if (receive.find(SEPARATOR) != std::string::npos) {
				tmpArray.clear();
				tmpArray = split(user.client_buffer, SEPARATOR);
				if(tmpArray[0] == NAS_STEP_ONE){
					if(DO_DEBUG){
						cout<<"SUCCESS: UE with key = "<<ue_key<<" imsi= "<<imsi<<" AUTHENTICATED"<<endl;
						cout<<"NAS Parameters: KSI_ASME = "<<tmpArray[1]<<" UE Network Capability "<<tmpArray[2]<<
						" Cipher algorithm ID = "<<tmpArray[3]<<" Integrity Algorithm ID = "<<tmpArray[4]<<" NAS MAC = "<<tmpArray[5]<<
						" UE with key = "<<ue_key<<endl;
					}
					/*NAS_KEYS = KDF_NAS(authenticationVector[2], stoi(tmpArray[4]), stoi(tmpArray[3]));
					// NAS_KEYS[0] = Integrity key and NAS_KEYS[1] = Cipher Key
					if(DO_DEBUG){
						cout<<" Integrity Key = "<<NAS_KEYS[0]<<" Cipher key ="<<NAS_KEYS[1]<<endl;
					}*/
					string integrity_text = tmpArray[0] + SEPARATOR + tmpArray[1] + SEPARATOR + tmpArray[2] + SEPARATOR + tmpArray[3] + SEPARATOR + tmpArray[4];

					// not handling if condition of NAS STEP 2 as of now as checkIntegrity is set to false in RAN.cpp everywhere
					if(checkIntegrity){
						string NAS_MAC_UE = hmacDigest(integrity_text, NAS_KEYS[0]);
						if(DO_DEBUG){
							cout<<"NAS_MAC_UE ="<<NAS_MAC_UE<<" Controller NAS MAC ="<<tmpArray[5]<<endl;
						}
						if (NAS_MAC_UE == tmpArray[5]){ // Check if generated NAS MAC = received NAS MAC
							string plain_text = NAS_STEP_TWO;
							//unsigned char *key = (unsigned char *)NAS_KEYS[1].c_str();//"01234567890123456789012345678901";
							unsigned char *plaintext = (unsigned char *)plain_text.c_str();
							unsigned char ciphertext[BUFFER_SIZE];

							/* Buffer for the decrypted text */
							unsigned char decryptedtext[128];
							int decryptedtext_len, ciphertext_len;

	 						// Encrypt the plaintext
							ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, ciphertext);

							char tmpCiphertext[ciphertext_len];
							for (int i = 0; i < ciphertext_len; i++){
								tmpCiphertext[i] = (char) ciphertext[i];
							}
							string encrypted_hash = hmacDigest2(tmpCiphertext, NAS_KEYS[0]);
							if(DO_DEBUG){
								cout<<"NAS STEP ONE: Generated NAS MAC= " << encrypted_hash <<endl;
							}
							send = SEPARATOR + encrypted_hash + SEPARATOR + longToString(imsi);

							for (int i = ciphertext_len; i < ciphertext_len+send.size(); i++){
								ciphertext[i] = (unsigned char)send[i-ciphertext_len];
							}
							ciphertext[ciphertext_len+send.size()] = '\0';

							//bzero(user.client_byte_buffer, BUFFER_SIZE);
							bzero(user.client_buffer, BUFFER_SIZE);
							//memcpy (user.client_byte_buffer, ciphertext , sizeof(ciphertext));
							sprintf(user.client_buffer, (const char*)ciphertext);
							//memcpy (user.client_buffer, ciphertext , sizeof(ciphertext));
							//user.write_byte();
							/////
                        				//usleep(my_rand());
                        				////
							user.write_data(NAS_STEP_TWO);
						} else{

							cout<<"ERROR:: Sending NAS Security Mode NOT Complete for UE with imsi = "<<longToString(imsi)<<endl;
							//exit(1);
							return false;
						}
					} else{
						
						// rewriting NAS STEP TWO

						// struct nas_step_two_t{
						// uint8_t msg_id;
						// uint16_t sep1[3];
						// uint32_t encrypted_hash[5];
						// uint16_t sep2[3];
						// uint32_t imsi;
						// };

						struct nas_step_two_t n2;

						n2.msg_id = 20;

						n2.sep1[0] = htons(0x403A);
    					n2.sep1[1] = htons(0x2323);
    					n2.sep1[2] = htons(0x3A40);

						// handling encrypted text as just random string 
						// encrypted hash = "abcd wxyz mnop stuv ghij"; 

						n2.encrypted_hash[0] = htonl(0x61626364);
    					n2.encrypted_hash[1] = htonl(0x777879);
    					n2.encrypted_hash[2] = htonl(0x6d6e6f70);
    					n2.encrypted_hash[3] = htonl(0x73747576);
    					n2.encrypted_hash[4] = htonl(0x6768696a);

						
						n2.sep2[0] = htons(0x403A);
    					n2.sep2[1] = htons(0x2323);
    					n2.sep2[2] = htons(0x3A40);

    					n2.imsi = htonl(imsi);

						// now write struct elemets to buffer one by one
						bzero(user.client_buffer, BUFFER_SIZE);
						len=0;  // reset length which holds no of bytes written in buffer

						memcpy(user.client_buffer, &(n2.msg_id), sizeof(n2.msg_id));
						len+=sizeof(n2.msg_id);

						memcpy(user.client_buffer+len, &(n2.sep1), sizeof(n2.sep1));
						len+=sizeof(n2.sep1);

						memcpy(user.client_buffer+len, &(n2.encrypted_hash), sizeof(n2.encrypted_hash));
						len+=sizeof(n2.encrypted_hash);

						memcpy(user.client_buffer+len, &(n2.sep2), sizeof(n2.sep2));
						len+=sizeof(n2.sep2);	

						memcpy(user.client_buffer+len, &(n2.imsi), sizeof(n2.imsi));
						len+=sizeof(n2.imsi);	

						user.write_data2(len);

						// ORIGINAL code: uncomment if required 
							// send = NAS_STEP_TWO + SEPARATOR + "encrypted_hash" + SEPARATOR + longToString(imsi);
							// bzero(user.client_buffer, BUFFER_SIZE);
							// sprintf(user.client_buffer, send.c_str());
							//                                 /////
							//                                 //usleep(my_rand());
							//                                 ////
							// user.write_data(NAS_STEP_TWO);
					}
					return true;
				}else{
					cout<<"**ERROR: Step FOUR authentication failure for UE with key = " <<key<<endl;
					//exit(1);
					return false;
				}
			}else{
				cout<<"ERROR: Step FOUR authentication failure for UE with key = " <<key<<endl;
				//exit(1);
				return false;
			}
		}else{
			cout<<"ERROR: Step ONE authentication failure for UE with key = "<<key<<endl;
			//exit(1);
			return false;
		}
	}else{
		cout<<"*ERROR: Step ONE authentication failure for UE with key = "<<key<<endl;
		//exit(1);
		return false;
	}
}

/*
 * This function initiates the tunnel setup procedure.
 */
vector<string> UserEquipment::setupTunnel(Client &user, bool doEncryption){
	string send, receive, initial;
	vector<string> tmpArray;
	vector<string> clearToSend;
        //vector<string> tmpArray1;
	int ue_teid;
	bool done=false;

	//mtx.lock();
	while(!done){
		mtx.lock();
		if(!reusable_ue_teid.empty()){
			ue_teid = reusable_ue_teid.front();
			reusable_ue_teid.pop();
			mtx.unlock();
			count++;
			done=true;
		}

		else{
			mtx.unlock();
			cout<<"UE TEID CROSSOVER!!!!"<<count<<endl;
			usleep(1000);
			//goto check;

		}
	}
	/*if(!reusable_ue_teid.empty()){
		ue_teid = reusable_ue_teid.front();
		reusable_ue_teid.pop();
	}
	else{
		ue_teid = ue_teid_curr.load();
		ue_teid_curr++;
		if(ue_teid_curr.load()>4095){
			ue_teid_curr = 1;
		}
	}*/
	//mtx.unlock();
	//ue_teid = uniform_distribution(generator);
	if(DO_DEBUG){
		cout<<" GENERATED teid="<<ue_teid<<endl;
	}

	// key_str="123";  


	// rewriting Send APN to the MME
	// struct send_apn_t{
	// uint8_t msg_id;
    // uint16_t sep1[3];
    // uint8_t apn[8];
    // uint16_t sep2[3];
    // uint8_t key[8];   // modify it later
	// };

	struct send_apn_t apnt;
	apnt.msg_id = 5;

	apnt.sep1[0] = htons(0x403A);
    apnt.sep1[1] = htons(0x2323);
    apnt.sep1[2] = htons(0x3A40);

	apnt.apn[0] =  (apn >> 56) & 0xFF;
	apnt.apn[1] =  (apn >> 48) & 0xFF;
	apnt.apn[2] =  (apn >> 40) & 0xFF;
	apnt.apn[3] =  (apn >> 32) & 0xFF;
	apnt.apn[4] =  (apn >> 24) & 0xFF;
	apnt.apn[5] =  (apn >> 16) & 0xFF;
	apnt.apn[6] =  (apn >> 8) & 0xFF;
	apnt.apn[7] =  (apn) & 0xFF;

	apnt.sep2[0] = htons(0x403A);
    apnt.sep2[1] = htons(0x2323);
    apnt.sep2[2] = htons(0x3A40);

	// apnt.key[0] =  (ue_key >> 56) & 0xFF;
	// apnt.key[1] =  (ue_key >> 48) & 0xFF;
	// apnt.key[2] =  (ue_key >> 40) & 0xFF;
	// apnt.key[3] =  (ue_key >> 32) & 0xFF;
	// apnt.key[4] =  (ue_key >> 24) & 0xFF;
	// apnt.key[5] =  (ue_key >> 16) & 0xFF;
	// apnt.key[6] =  (ue_key >> 8) & 0xFF;
	// apnt.key[7] =  (ue_key) & 0xFF;

	apnt.key = htonl(ue_key);

	// now write struct elemets to buffer one by one
	bzero(user.client_buffer, BUFFER_SIZE);
	int len=0;  // reset length which holds no of bytes written in buffer

	memcpy(user.client_buffer, &(apnt.msg_id), sizeof(apnt.msg_id));
	len+=sizeof(apnt.msg_id);

	memcpy(user.client_buffer+len, &(apnt.sep1), sizeof(apnt.sep1));
	len+=sizeof(apnt.sep1);

	memcpy(user.client_buffer+len, &(apnt.apn), sizeof(apnt.apn));
	len+=sizeof(apnt.apn);

	memcpy(user.client_buffer+len, &(apnt.sep2), sizeof(apnt.sep2));
	len+=sizeof(apnt.sep2);

	memcpy(user.client_buffer+len, &(apnt.key), sizeof(apnt.key));
	len+=sizeof(apnt.key);
	
	user.write_data2(len);

	// ORIGINAL code: uncomment if required 
		// send = SEND_APN + SEPARATOR + longToString(apn) + SEPARATOR + longToString(key);
		// bzero(user.client_buffer, BUFFER_SIZE);
		// sprintf(user.client_buffer, send.c_str());
		//                                                             /////
		//                                                     //usleep(my_rand());
		//                                                     ////
		// user.write_data(SEND_APN);
	if(doEncryption) {
		sendEncryptedData(user, SEND_APN + SEPARATOR,  longToString(apn) + SEPARATOR + longToString(ue_key),"SEND_APN");
	}
	// Receive UE IP address and SGW TEID from MME
	user.read_data();
	receive = (string) (user.client_buffer);
	//receive = (string) (user.trim_buffer);
        
	if(MY_DEBUG){
        cout<<"My Print -- received"<<receive<<endl;
        }

        tmpArray.clear();
	tmpArray = split(user.client_buffer, SEPARATOR);
	if(doEncryption) {
		receiveEncryptedData(user, tmpArray[0], "string method");
	}
	if(tmpArray[0] == SEND_IP_SGW_TEID){
		if(DO_DEBUG){
			cout<<" IP Address of UE="<<tmpArray[1]<<" and SGW TEID="<<tmpArray[2]<<" ue TEID="<<ue_teid<<endl;
		}
		//tmpArray.push_back(to_string(ue_teid));
		tmpArray[3] = to_string(ue_teid);
                
		/*tmpArray1.push_back(tmpArray[0]);
		tmpArray1.push_back(SEPARATOR);
		tmpArray1.push_back(tmpArray[1]);
                tmpArray1.push_back(SEPARATOR);
		tmpArray1.push_back(tmpArray[2]);
                tmpArray1.push_back(SEPARATOR);
                tmpArray1.push_back(to_string(ue_teid));*/

		// rewriting Send UE TEID and key for identifying UE at MME (for SGW)
		// struct send_ue_teid_t{
		// uint8_t msg_id;
		// uint16_t sep1[3];
		// uint32_t ue_teid;  
		// uint16_t sep2[3];
		// uint8_t key[8];   // modify it later
		// };

		struct send_ue_teid_t st;
		st.msg_id = 7;

		st.sep1[0] = htons(0x403A);
    	st.sep1[1] = htons(0x2323);
   		st.sep1[2] = htons(0x3A40);

		st.ue_teid = htonl(ue_teid);

		st.sep2[0] = htons(0x403A);
    	st.sep2[1] = htons(0x2323);
   		st.sep2[2] = htons(0x3A40);

		// st.key[0] =  (ue_key >> 56) & 0xFF;
		// st.key[1] =  (ue_key >> 48) & 0xFF;
		// st.key[2] =  (ue_key >> 40) & 0xFF;
		// st.key[3] =  (ue_key >> 32) & 0xFF;
		// st.key[4] =  (ue_key >> 24) & 0xFF;
		// st.key[5] =  (ue_key >> 16) & 0xFF;
		// st.key[6] =  (ue_key >> 8) & 0xFF;
		// st.key[7] =  (ue_key) & 0xFF;

		st.key = htonl(ue_key);

		// now write struct elemets to buffer one by one
		bzero(user.client_buffer, BUFFER_SIZE);
		len=0;  // reset length which holds no of bytes written in buffer

		memcpy(user.client_buffer, &(st.msg_id), sizeof(st.msg_id));
		len+=sizeof(st.msg_id);

		memcpy(user.client_buffer+len, &(st.sep1), sizeof(st.sep1));
		len+=sizeof(st.sep1);

		memcpy(user.client_buffer+len, &(st.ue_teid ), sizeof(st.ue_teid ));
		len+=sizeof(st.ue_teid );

		memcpy(user.client_buffer+len, &(st.sep2), sizeof(st.sep2));
		len+=sizeof(st.sep2);

		memcpy(user.client_buffer+len, &(st.key), sizeof(st.key));   
		len+=sizeof(st.key);
		
		user.write_data2(len);

		// ORIGINAL code: uncomment if required 
			// send = SEND_UE_TEID + SEPARATOR + longToString(ue_teid) + SEPARATOR + longToString(key);
			// bzero(user.client_buffer, BUFFER_SIZE);
			// sprintf(user.client_buffer, send.c_str());
			// 												/////
			// 												//usleep(1500);
			// 												////
			// user.write_data(SEND_UE_TEID);
		if(doEncryption) {
			sendEncryptedData(user, SEND_UE_TEID + SEPARATOR, longToString(ue_teid) + SEPARATOR + longToString(ue_key), "SEND_UE_TEID");
		}

		user.read_data();
		receive = (string) (user.client_buffer);
		//receive = (string) (user.trim_buffer);
                if(MY_DEBUG){
                    cout<<"My Print -- received"<<receive<<endl;
                }
		clearToSend.clear();
		clearToSend = split(user.client_buffer, SEPARATOR);
		if(doEncryption) {
			receiveEncryptedData(user, clearToSend[0], "string method");
		}
		if(clearToSend[0] == ATTACH_ACCEPT){
			tmpArray.push_back(clearToSend[1]); // clearToSend[1] => GUTI

			/*tmpArray1.push_back(clearToSend[0]);
	                tmpArray1.push_back(SEPARATOR);
			tmpArray1.push_back(clearToSend[1]); */

			if(DO_DEBUG){
				cout<<"CLEAR TO SEND DATA"<<endl;
			}
		}else{
			cout<<"ERROR: NOT CLEAR TO SEND DATA"<<endl;
			exit(1);
		}
		time_t seconds;
		seconds = time (NULL);
		if(DO_DEBUG){
		//	printf ("%ld seconds since January 1, 1970 kk=%d\n", seconds, stoi(tmpArray[2]));
		}
	}
	return tmpArray;
}

/*
 * This function is used to send data from a UE in the form of TCP traffic generated using iperf3.
 */
int UserEquipment::sendUserData(Client &user, int ue_num, string rate, int serverPort, int startingPort, int endPort, vector<string>& tmpArray, int dataTime){
	/*size_t meanTime;
	// Generate a random non-zero time duration with the specified mean
	do{
		meanTime = (size_t) distribution(generator);
	}while(meanTime == 0);
*/
	size_t meanTime = dataTime;
	struct timeb start;
	ftime(&start);
	string dstIp(SINK_IP);
	int returnedPort = 0;
	if(DO_DEBUG){
		cout<<"****DATA TIME = "<<dataTime<<endl;
	}
	returnedPort = user.sendUEData(ue_num, tmpArray[1], dstIp, serverPort, startingPort, endPort, rate, meanTime);

	struct timeb end;
	ftime(&end);
	double diff= (end.time - start.time) + (end.millitm - start.millitm)/1000.0;

	if(DO_DEBUG){
		cout<<"UE ID="<<ue_num<<" meanTime= "<<meanTime<<" Time for Data Transfer = "<<diff<<"sec"<<endl;
	}
	return returnedPort;
}

/*
 * This function initiates the detach procedure which is invoked by UE.
 */
void UserEquipment::initiate_detach(Client &user, int ue_num, string ue_ip, string sgw_teid, string ue_teid){
	string send, receive;
	vector<string> tmpArray;

	//rewriting Initiate detach procedure

	// struct detach_req_t{
    // uint8_t msg_id;
    // uint16_t sep1[3];
	// uint32_t ue_ip;
    // uint16_t sep2[3];
    // uint32_t ue_teid;
    // uint16_t sep3[3];
    // uint32_t sgw_teid;
    // uint16_t sep4[3];
    // uint32_t ue_num;
	// };

	struct detach_req_t detach;

	detach.msg_id = 9;

	detach.sep1[0] = htons(0x403A);
    detach.sep1[1] = htons(0x2323);
   	detach.sep1[2] = htons(0x3A40);

	detach.ue_ip = inet_addr(ue_ip.c_str());

	detach.sep2[0] = htons(0x403A);
    detach.sep2[1] = htons(0x2323);
   	detach.sep2[2] = htons(0x3A40);

	detach.ue_teid =  htonl(stoul(ue_teid));
	
	detach.sep3[0] = htons(0x403A);
    detach.sep3[1] = htons(0x2323);
   	detach.sep3[2] = htons(0x3A40);

	detach.sgw_teid = htonl(stoul(sgw_teid));

	detach.sep4[0] = htons(0x403A);
    detach.sep4[1] = htons(0x2323);
   	detach.sep4[2] = htons(0x3A40);

	detach.ue_num = htonl(ue_num);


	// now write struct elemets to buffer one by one
	bzero(user.client_buffer, BUFFER_SIZE);
	int len=0;  // reset length which holds no of bytes written in buffer

	memcpy(user.client_buffer, &(detach.msg_id), sizeof(detach.msg_id));
	len+=sizeof(detach.msg_id);

	memcpy(user.client_buffer+len, &(detach.sep1), sizeof(detach.sep1));
	len+=sizeof(detach.sep1);

	memcpy(user.client_buffer+len, &(detach.ue_ip ), sizeof(detach.ue_ip ));
	len+=sizeof(detach.ue_ip );

	memcpy(user.client_buffer+len, &(detach.sep2), sizeof(detach.sep2));
	len+=sizeof(detach.sep2);

	memcpy(user.client_buffer+len, &(detach.ue_teid), sizeof(detach.ue_teid));
	len+=sizeof(detach.ue_teid);

	memcpy(user.client_buffer+len, &(detach.sep4), sizeof(detach.sep4));
	len+=sizeof(detach.sep4);

	memcpy(user.client_buffer+len, &(detach.sgw_teid), sizeof(detach.sgw_teid));
	len+=sizeof(detach.sgw_teid);

	memcpy(user.client_buffer+len, &(detach.sep3), sizeof(detach.sep3));
	len+=sizeof(detach.sep3);

	memcpy(user.client_buffer+len, &(detach.ue_num), sizeof(detach.ue_num));
	len+=sizeof(detach.ue_num);
	
	user.write_data2(len);

	// ORIGINAL code: uncomment if required 
		// send = DETACH_REQUEST + SEPARATOR + ue_ip + SEPARATOR + ue_teid + SEPARATOR + sgw_teid + SEPARATOR + to_string(ue_num);
		// bzero(user.client_buffer, BUFFER_SIZE);
		// sprintf(user.client_buffer, send.c_str());
		// //cout<<"SEND deatch: "<<sgw_teid<<endl;
		// ////
		// //usleep(1500);
		// ////
		// user.write_data(DETACH_REQUEST);
	//sendEncryptedData(user, DETACH_REQUEST + SEPARATOR,  ue_ip + SEPARATOR + ue_teid + SEPARATOR + sgw_teid + SEPARATOR + to_string(ue_num),"DETACH_REQUEST");
	if(DO_DEBUG){
		cout<<"UE INITIATED DETACH:  IP Address of UE="<<ue_ip<<" and UE TEID="<<ue_teid<<" SGW TEID"<<sgw_teid<<endl;
	}

	// Receive UE IP address and SGW TEID
	user.read_data();
	tmpArray.clear();
	receive = (string) (user.client_buffer);
	//receive = (string) (user.trim_buffer);
        if(MY_DEBUG){
	        cout<<"My Print -- received"<<receive<<endl;
        }

	tmpArray = split(user.client_buffer, SEPARATOR);
	if(DO_DEBUG){
		//cout<<"UE INITIATED DETACH: tmpArray[0] = "<<tmpArray[0]<<"        "<<"tmpArray[1] = "<<tmpArray[1]<<endl;
	}
	// receiveEncryptedData(user, tmpArray[0], "string method");
	if(tmpArray[0] == DETACH_ACCEPT){
		// TODO: delete the ip from the network interface
		string dstNetwork(SINK_SERVER_NETMASK);
		if(DO_DEBUG){
			cout<<"UE DETACH ACCEPTED:  IP Address of UE="<<ue_ip<<" and UE TEID="<<ue_teid<<" SGW TEID"<<sgw_teid<<endl;
		}
//		int ue_teid;
		mtx.lock();
		reusable_ue_teid.push(stoi(ue_teid));
		mtx.unlock();
		count--;
	}else{
		cout<<"ERROR: UE DETACH ACCEPT ERROR:  IP Address of UE="<<ue_ip<<" and UE TEID="<<ue_teid<<" SGW TEID"<<sgw_teid<<endl;
		exit(1);
	}
}

/*
 * This function initiates the context release procedure. It is invoked by a UE (eNodeB in real life) after it
 * remains idle for a particular duration of time. The tunnel is then ruptured with the help of RAN and controller.
 */
void UserEquipment::initiate_ue_context_release(Client &user, int ue_num, string ue_ip, string sgw_teid, string ue_teid, int sinkUDPServerPort, bool networkServiceRequest){
	string send, receive;
	vector<string> tmpArray;

	// Initiate ue context release procedure

	// struct ue_context_rel_req_t{
    // uint8_t msg_id;
    // uint16_t sep1[3];
	// uint32_t ue_ip;
    // uint16_t sep2[3];
    // uint32_t ue_teid;
    // uint16_t sep3[3];
    // uint32_t sgw_teid;
    // uint16_t sep4[3];
	// uint32_t ue_num;
	// };
	struct ue_context_rel_req_t ctxtrel;

	ctxtrel.msg_id=14;

	ctxtrel.sep1[0] = htons(0x403A);
    ctxtrel.sep1[1] = htons(0x2323);
   	ctxtrel.sep1[2] = htons(0x3A40);

	ctxtrel.ue_ip = inet_addr(ue_ip.c_str());

	ctxtrel.sep2[0] = htons(0x403A);
    ctxtrel.sep2[1] = htons(0x2323);
   	ctxtrel.sep2[2] = htons(0x3A40);

	ctxtrel.ue_teid =  htonl(stoul(ue_teid));

	ctxtrel.sep3[0] = htons(0x403A);
    ctxtrel.sep3[1] = htons(0x2323);
   	ctxtrel.sep3[2] = htons(0x3A40);

	ctxtrel.sgw_teid =  htonl(stoul(sgw_teid));

	ctxtrel.sep4[0] = htons(0x403A);
    ctxtrel.sep4[1] = htons(0x2323);
   	ctxtrel.sep4[2] = htons(0x3A40);

	ctxtrel.ue_num = htonl(ue_num);
	
	// now write struct elemets to buffer one by one
	bzero(user.client_buffer, BUFFER_SIZE);
	int len=0;  // reset length which holds no of bytes written in buffer

	memcpy(user.client_buffer, &(ctxtrel.msg_id), sizeof(ctxtrel.msg_id));
	len+=sizeof(ctxtrel.msg_id);

	memcpy(user.client_buffer+len, &(ctxtrel.sep1), sizeof(ctxtrel.sep1));
	len+=sizeof(ctxtrel.sep1);

	memcpy(user.client_buffer+len, &(ctxtrel.ue_ip ), sizeof(ctxtrel.ue_ip ));
	len+=sizeof(ctxtrel.ue_ip );

	memcpy(user.client_buffer+len, &(ctxtrel.sep2), sizeof(ctxtrel.sep2));
	len+=sizeof(ctxtrel.sep2);

	memcpy(user.client_buffer+len, &(ctxtrel.ue_teid), sizeof(ctxtrel.ue_teid));
	len+=sizeof(ctxtrel.ue_teid);

	memcpy(user.client_buffer+len, &(ctxtrel.sep3), sizeof(ctxtrel.sep3));
	len+=sizeof(ctxtrel.sep3);

	memcpy(user.client_buffer+len, &(ctxtrel.sgw_teid), sizeof(ctxtrel.sgw_teid));
	len+=sizeof(ctxtrel.sgw_teid);

	memcpy(user.client_buffer+len, &(ctxtrel.sep4), sizeof(ctxtrel.sep4));
	len+=sizeof(ctxtrel.sep4);

	memcpy(user.client_buffer+len, &(ctxtrel.ue_num), sizeof(ctxtrel.ue_num));
	len+=sizeof(ctxtrel.ue_num);
	
	user.write_data2(len);

	// ORIGINAL code: uncomment if required 
		// send = UE_CONTEXT_RELEASE_REQUEST + SEPARATOR + ue_ip + SEPARATOR + ue_teid + SEPARATOR + sgw_teid + SEPARATOR + to_string(ue_num);
		// bzero(user.client_buffer, BUFFER_SIZE);
		// sprintf(user.client_buffer, send.c_str());
		// user.write_data(UE_CONTEXT_RELEASE_REQUEST);
	if(DO_DEBUG){
		cout<<"UE INITIATED CONTEXT RELEASE REQUEST:  IP Address of UE="<<ue_ip<<" and UE TEID="<<ue_teid<<" SGW TEID"<<sgw_teid<<endl;
	}

	// Receive UE_CONTEXT_RELEASE_COMMAND from MME
	user.read_data();
	tmpArray.clear();
	receive = (string) (user.client_buffer);
	//receive = (string) (user.trim_buffer);
	if(MY_DEBUG){
                cout<<"My Print -- received"<<receive<<endl;
        }

	tmpArray = split(user.client_buffer, SEPARATOR);
	if(tmpArray[0] == UE_CONTEXT_RELEASE_COMMAND){

		if(DO_DEBUG){
			cout<<"UE CONTEXT RELEASE COMMAND:  IP Address of UE="<<ue_ip<<" and UE TEID="<<ue_teid<<" SGW TEID"<<sgw_teid<<endl;
		}

	}else{
		cout<<"ERROR: UE CONTEXT RELEASE ACCEPT ERROR: UE Key="<<key<<" IP Address of UE="<<ue_ip<<" and UE TEID="<<ue_teid<<" SGW TEID"<<sgw_teid<<endl;
		exit(1);
	}
	mtx.lock();
		reusable_ue_teid.push(stoi(ue_teid));
		mtx.unlock();
		count--;

	// Context relase complete
/*	if(networkServiceRequest) {
		send = UE_CONTEXT_RELEASE_COMPLETE + SEPARATOR + to_string(ue_num) + SEPARATOR + ue_ip + SEPARATOR + "1" + SEPARATOR + to_string(sinkUDPServerPort);
	}else{
		send = UE_CONTEXT_RELEASE_COMPLETE + SEPARATOR + to_string(ue_num) + SEPARATOR + ue_ip + SEPARATOR + "0";
	}

	bzero(user.client_buffer, BUFFER_SIZE);
	sprintf(user.client_buffer, send.c_str());
	user.write_data(UE_CONTEXT_RELEASE_COMPLETE);*/
	if(DO_DEBUG){
		cout<<"UE INITIATED CONTEXT RELEASE COMPLETE: UE Key="<<ue_num<<endl;
	}
}

/*
 * This function initiates for the tunnel resetup when a UE wishes to send data after remaining idle for a long time.
 * Ideally, no re-authentication needs to be done in this case. We just need to re-establish the tunnel for traffic flow.
 */
string UserEquipment::send_ue_service_request(Client& user, int ue_num, string ue_ip){
	vector<string> clearToSend;
	int ue_teid;
	string send, receive, response= "";
	vector<string> tmpArray;
	string KSI_ASME = "7";

	// Send UE Service request
	// struct ue_service_req_t{
    // uint8_t msg_id;
    // uint16_t sep1[3];
	// uint32_t ue_num[4];
    // uint16_t sep2[3];
    // int32_t ksi_asme;   // for now making it 64 bit
    // uint16_t sep3[3];
    // uint32_t ue_ip;
	// };

	struct ue_service_req_t serreq;

	serreq.msg_id = 17;

	serreq.sep1[0] = htons(0x403A);
    serreq.sep1[1] = htons(0x2323);
   	serreq.sep1[2] = htons(0x3A40);

	serreq.ue_num = htonl(ue_num);

	serreq.sep2[0] = htons(0x403A);
    serreq.sep2[1] = htons(0x2323);
   	serreq.sep2[2] = htons(0x3A40);

	serreq.ksi_asme = htonl(stoi(KSI_ASME));

	serreq.sep3[0] = htons(0x403A);
    serreq.sep3[1] = htons(0x2323);
   	serreq.sep3[2] = htons(0x3A40);

	serreq.ue_ip = inet_addr(ue_ip.c_str());


	// now write struct elemets to buffer one by one
	bzero(user.client_buffer, BUFFER_SIZE);
	int len=0;  // reset length which holds no of bytes written in buffer

	memcpy(user.client_buffer, &(serreq.msg_id), sizeof(serreq.msg_id));
	len+=sizeof(serreq.msg_id);

	memcpy(user.client_buffer+len, &(serreq.sep1), sizeof(serreq.sep1));
	len+=sizeof(serreq.sep1);

	memcpy(user.client_buffer+len, &(serreq.ue_num), sizeof(serreq.ue_num));
	len+=sizeof(serreq.ue_num);

	memcpy(user.client_buffer+len, &(serreq.sep2), sizeof(serreq.sep2));
	len+=sizeof(serreq.sep2);

	memcpy(user.client_buffer+len, &(serreq.ksi_asme), sizeof(serreq.ksi_asme));
	len+=sizeof(serreq.ksi_asme);

	memcpy(user.client_buffer+len, &(serreq.sep3), sizeof(serreq.sep3));
	len+=sizeof(serreq.sep3);

	memcpy(user.client_buffer+len, &(serreq.ue_ip ), sizeof(serreq.ue_ip ));
	len+=sizeof(serreq.ue_ip );
	
	user.write_data2(len);

	// ORIGINAL code: uncomment if required 
		// send = UE_SERVICE_REQUEST + SEPARATOR + longToString(ue_num) + SEPARATOR + KSI_ASME + SEPARATOR + ue_ip;
		// bzero(user.client_buffer, BUFFER_SIZE);
		// sprintf(user.client_buffer, send.c_str());
		// // sendEncryptedData(user, UE_SERVICE_REQUEST + SEPARATOR, longToString(ue_num) + SEPARATOR + KSI_ASME + SEPARATOR + ue_ip, "UE_SERVICE_REQUEST");
		// user.write_data(UE_SERVICE_REQUEST);

	// Receive reply from MME
	user.read_data();
	receive = (string) (user.client_buffer);
	//receive = (string) (user.trim_buffer);
	if(MY_DEBUG){
                cout<<"My Print -- received"<<receive<<endl;
        }

	// receiveEncryptedData(user, receive, "string method");
	if(MY_DEBUG){
	cout<<"My Print -- received"<<receive<<endl;
	}
	if (receive.find(SEPARATOR) != std::string::npos) {
		tmpArray.clear();
		tmpArray = split(user.client_buffer, SEPARATOR);

		if(tmpArray[0] == INITIAL_CONTEXT_SETUP_REQUEST){
			if(DO_DEBUG){
				cout<<"Received INITIAL_CONTEXT_SETUP_REQUEST for UE with key="<<ue_num<<" SGW TEID="<<tmpArray[1]<<endl;
			}

//			int ue_teid;
		//mtx.lock();

		bool done=false;
	//mtx.lock();
	while(!done){
		mtx.lock();
		if(!reusable_ue_teid.empty()){
			ue_teid = reusable_ue_teid.front();
			reusable_ue_teid.pop();
			mtx.unlock();
			count++;
			done=true;
		}

		else{
			mtx.unlock();
			cout<<"UE TEID CROSSOVER!!!!"<<count<<endl;
			usleep(1000);
			//goto check;

		}
	}
		/*if(!reusable_ue_teid.empty()){
			ue_teid = reusable_ue_teid.front();
			reusable_ue_teid.pop();
		}
		else{
			ue_teid = ue_teid_curr.load();
			ue_teid_curr++;
			if(ue_teid_curr.load()>4095){
				ue_teid_curr = 1;
			}
		}*/
		//mtx.unlock();

			//ue_teid = uniform_distribution(generator);
			if(DO_DEBUG){
				cout<<" GENERATED teid="<<ue_teid<<endl;
			}
			// Send INITIAL_CONTEXT_SETUP_RESPONSE


			// struct initial_ctxt_setup_resp_t{
			// 	uint8_t msg_id;
			// 	uint16_t sep1[3];
			// 	uint32_t ue_teid;
			// 	uint16_t sep2[3];
			// 	int64_t ue_key;
			// 	uint16_t sep3[3];
			// 	uint32_t ue_ip;
			// };

			struct initial_ctxt_setup_resp_t ctxtresp;

			ctxtresp.msg_id = 19;

			ctxtresp.sep1[0] = htons(0x403A);
			ctxtresp.sep1[1] = htons(0x2323);
			ctxtresp.sep1[2] = htons(0x3A40);

			ctxtresp.ue_teid =  htonl(ue_teid);

			ctxtresp.sep2[0] = htons(0x403A);
			ctxtresp.sep2[1] = htons(0x2323);
			ctxtresp.sep2[2] = htons(0x3A40);

			// ctxtresp.ue_key[0] =  (ue_key >> 56) & 0xFF;
			// ctxtresp.ue_key[1] =  (ue_key >> 48) & 0xFF;
			// ctxtresp.ue_key[2] =  (ue_key >> 40) & 0xFF;
			// ctxtresp.ue_key[3] =  (ue_key >> 32) & 0xFF;
			// ctxtresp.ue_key[4] =  (ue_key >> 24) & 0xFF;
			// ctxtresp.ue_key[5] =  (ue_key >> 16) & 0xFF;
			// ctxtresp.ue_key[6] =  (ue_key >> 8) & 0xFF;
			// ctxtresp.ue_key[7] =  (ue_key) & 0xFF;
			ctxtresp.ue_key = htonl(ue_key);

			ctxtresp.sep3[0] = htons(0x403A);
			ctxtresp.sep3[1] = htons(0x2323);
			ctxtresp.sep3[2] = htons(0x3A40);

			ctxtresp.ue_ip = inet_addr(ue_ip.c_str());

			// now write struct elemets to buffer one by one
			bzero(user.client_buffer, BUFFER_SIZE);
			int len=0;  // reset length which holds no of bytes written in buffer

			memcpy(user.client_buffer, &(ctxtresp.msg_id), sizeof(ctxtresp.msg_id));
			len+=sizeof(ctxtresp.msg_id);

			memcpy(user.client_buffer+len, &(ctxtresp.sep1), sizeof(ctxtresp.sep1));
			len+=sizeof(ctxtresp.sep1);

			memcpy(user.client_buffer+len, &(ctxtresp.ue_teid), sizeof(ctxtresp.ue_teid));
			len+=sizeof(ctxtresp.ue_teid);

			memcpy(user.client_buffer+len, &(ctxtresp.sep2), sizeof(ctxtresp.sep2));
			len+=sizeof(ctxtresp.sep2);

			memcpy(user.client_buffer+len, &(ctxtresp.ue_key), sizeof(ctxtresp.ue_key));
			len+=sizeof(ctxtresp.ue_key);

			memcpy(user.client_buffer+len, &(ctxtresp.sep3), sizeof(ctxtresp.sep3));
			len+=sizeof(ctxtresp.sep3);

			memcpy(user.client_buffer+len, &(ctxtresp.ue_ip ), sizeof(ctxtresp.ue_ip ));
			len+=sizeof(ctxtresp.ue_ip );
			
			user.write_data2(len);

			// ORIGINAL code: uncomment if required 
				// send = INITIAL_CONTEXT_SETUP_RESPONSE + SEPARATOR + longToString(ue_teid) + SEPARATOR + longToString(key) + SEPARATOR + ue_ip;
				// bzero(user.client_buffer, BUFFER_SIZE);
				// sprintf(user.client_buffer, send.c_str());
				// //sendEncryptedData(user, UE_SERVICE_REQUEST + SEPARATOR, longToString(ue_num), "INITIAL_CONTEXT_SETUP_RESPONSE");
				// user.write_data(INITIAL_CONTEXT_SETUP_RESPONSE);

			user.read_data();
			receive = (string) (user.client_buffer);
			//receive = (string) (user.trim_buffer);
			if(MY_DEBUG){
        			cout<<"My Print -- received"<<receive<<endl;
		        }
			// receiveEncryptedData(user, receive, "string method");
			tmpArray.clear();
			tmpArray = split(user.client_buffer, SEPARATOR);
			if(tmpArray[0] == ATTACH_ACCEPT){
				// tmpArray[1] => ue key
				if(DO_DEBUG){
					cout<<"CLEAR TO SEND DATA for ue with key ="<<tmpArray[1]<<endl;
				}
			}
		}
	}

	return to_string(ue_teid);
}

/*
 * This function blocks on UDP read socket call and waits for paging request from MME.
 */
string UserEquipment::receive_paging_request(Client& user, int ue_num, string ue_ip){
	string receive, ue_teid= "";
	vector<string> tmpArray;
	// Receive paging request from MME
	user.read_data();
	receive = (string) (user.client_buffer);
	//receive = (string) (user.trim_buffer);
	if(MY_DEBUG){
	cout<<"My Print -- received"<<receive<<endl;
	}
	if (receive.find(SEPARATOR) != std::string::npos) {
		tmpArray.clear();
		tmpArray = split(user.client_buffer, SEPARATOR);
		if(tmpArray[0] == PAGING_REQUEST){
			if(DO_DEBUG){
				cout<<"Received PAGING_REQUEST for UE with key="<<ue_num<<" SGW TEID = "<<tmpArray[1]<<endl;
			}
			ue_teid = send_ue_service_request(user, ue_num, ue_ip);
		}
	}
	return ue_teid;
}

/*
 * This function is used to contact the controller (MME) to fetch the starting UE IP address.
 */
string UserEquipment::getStartingIPAddress(Client& user){
	string send, receive, ip= "";
	vector<string> tmpArray;
	// write structure instead of string and pass that as argument 
	
    struct req_starting_ip rip;
	int len=0;
	bzero(user.client_buffer, BUFFER_SIZE);

	rip.msg_id = 12;

	rip.sep1[0] = htons(0x403A);
    rip.sep1[1] = htons(0x2323);
    rip.sep1[2] = htons(0x3A40);

	memcpy(user.client_buffer,&rip.msg_id,sizeof(rip.msg_id));
	len+=sizeof(rip.msg_id);
	memcpy(user.client_buffer+len,&rip.sep1,sizeof(rip.sep1));
	len+=sizeof(rip.sep1);

	user.write_data2(len);


	// ORIGINAL code : uncomment it later if req to roll back
	// send = REQUEST_STARTING_IP + SEPARATOR + "";
	// bzero(user.client_buffer, BUFFER_SIZE);
	// sprintf(user.client_buffer, send.c_str());
	// user.write_data(REQUEST_STARTING_IP);


	//cout<<"sent data in getStartingIPAddress = "<<send<<endl;
	user.read_data();
	receive = (string) (user.client_buffer);
	//receive = (string) (user.trim_buffer);

	if(MY_DEBUG){
	cout<<"My Print -- received"<<receive<<endl;
	}

	if (receive.find(SEPARATOR) != std::string::npos) {
		tmpArray.clear();
		tmpArray = split(user.client_buffer, SEPARATOR);
		if(tmpArray[0] == SEND_STARTING_IP && tmpArray.size()==2){
			ip = tmpArray[1];
			if(DO_DEBUG){
				cout<<"Received starting ip="<<ip<<endl;
			}
		}else{
			cout<<"ERROR:: error occured in fetching starting ip address";
			exit(1);
		}
	}else{
		cout<<"*ERROR:: error occured in fetching starting ip address";
		exit(1);
	}
	return ip;
}

/*
 * Authentication and Key Agreement Algorithm
 */
vector<unsigned long long> UserEquipment::EPS_AKA_algorithm(unsigned long long key, unsigned long long rand1, int SQN, int SN_ID){
	unsigned long long res, autn, CK, IK, K_ASME; // CK: Cipher Key, IK : Integrity Key, ASME: Access Security Management Entity (in this case MME)
	vector<unsigned long long> authenticationVector(3);
	res = rand1 * key + SQN;
	// cout<<" key="<<key<<" rand="<<rand<<" SQN ="<<SQN<<" SN_ID= "<<SN_ID<<endl;
	autn = (rand1 - 1) * (key + 1) - SQN;
	// cout<<"AUTN="<<autn<<endl;
	CK = (rand1 + 1) * (key - 1) - (SQN + 1);
	IK = (rand1 + 1) * (key + 1) - (SQN - 1);
	K_ASME = KDF(SQN, SN_ID, CK, IK);
	authenticationVector[0] = autn;
	authenticationVector[1] = res;
	authenticationVector[2] = K_ASME;
	return authenticationVector;
}

/*
 * KDF: Key Derivation Function
 */
unsigned long long UserEquipment::KDF(int SQN, int SN_ID, unsigned long long CK, unsigned long long IK) {
	unsigned long long K_ASME; //ASME: Access Security Management Entity (in this case MME)
	K_ASME = SQN * CK + SN_ID * IK;
	return K_ASME;
}

/*
 * KDF used in NAS setup
 */
vector<string> UserEquipment::KDF_NAS(int K_ASME, int NAS_integrity_algo_id, int NAS_cipher_algo_id){
	vector<string> NAS_keys(2);
	// NAS_keys[0]: Integrity key K_NAS_int, NAS_keys[1]: Encryption key K_NAS_enc
	long K_NAS_int = K_ASME * 2 + NAS_integrity_algo_id;
	long K_NAS_enc = K_ASME * 4 + NAS_cipher_algo_id;
	NAS_keys[0] = to_string(K_NAS_int); 	// Integrity key
	NAS_keys[1] = to_string(K_NAS_enc); 	// Cipher key
	if (NAS_keys[1].size() >= ENC_KEY_LENGTH){
		NAS_keys[1] = NAS_keys[1].substr(0, ENC_KEY_LENGTH);
	} else{
		NAS_keys[1] = NAS_keys[1] + SAMPLE_ENC_KEY.substr(0, (ENC_KEY_LENGTH-NAS_keys[1].size()));
	}
	return NAS_keys;
}


/*
 * This function is used to simulate decryption of received data.
 */
void UserEquipment::receiveEncryptedData(Client& user, string text, string method){
	unsigned char *cipherkey = (unsigned char *)NAS_KEYS[1].c_str();
	unsigned char *encrypted_text;
	unsigned char deryptedtext[BUFFER_SIZE];
	int plaintext_len;
	string send;
	text = "dddddddd";

	encrypted_text = (unsigned char *)(text).c_str();
	// Decrypt the encrypted_text
	plaintext_len = encrypt (encrypted_text, strlen ((char *)encrypted_text), cipherkey, deryptedtext);

	char tmpPlaintext[plaintext_len];
	for (int i = 0; i < plaintext_len; i++){
		tmpPlaintext[i] = (char) deryptedtext[i];
	}
	hmacDigest2(tmpPlaintext, NAS_KEYS[0]);
}

/*
 * This function is used to simulate encryption of the data to be sent.
 */
void UserEquipment::sendEncryptedData(Client& user, string initial, string text, string method){
	unsigned char *cipherkey = (unsigned char *)NAS_KEYS[1].c_str();
	unsigned char *plaintext;
	unsigned char ciphertext[BUFFER_SIZE];
	int ciphertext_len;
	string send;
	plaintext = (unsigned char *)(text).c_str();

	// Encrypt the plaintext
	ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), cipherkey, ciphertext);

	char tmpCiphertext[ciphertext_len];
	for (int i = 0; i < ciphertext_len; i++){
		tmpCiphertext[i] = (char) ciphertext[i];
	}
	hmacDigest2(tmpCiphertext, NAS_KEYS[0]);
}


UserEquipment::~UserEquipment(){
	// Dummy destructor
}
