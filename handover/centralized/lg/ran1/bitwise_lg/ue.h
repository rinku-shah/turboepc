#include "client.h"

typedef struct {
  uint8_t rand[16];
  uint8_t rand_new;
  uint8_t xres[8];
  uint8_t autn[16];
  uint8_t kasme[32];
  uint8_t mac_a[8];
  uint8_t ck[16];
  uint8_t ik[16];
  uint8_t ak[6];
} auc_vector_t;

class UserEquipment{
	public:
		uint8_t key[16];		// UE key
		/*-------------------- Rijndael round subkeys ---------------------*/
		uint8_t roundKeys[11][4][4];
		// string key_str;
		unsigned long long ue_key;
		unsigned long long imsi;	// International Mobile Subscriber Identity
		unsigned long long msisdn;	// Mobile Station International Subscriber Directory Number
		unsigned long long apn;		// Access Point Name
		unsigned long long ue_nw_capability; 	// Varies between 0 and 10; 0-> BAD connectivity, 10-> EXCELLENT connectivity
		vector<string> NAS_KEYS;	// Contains the keys generated at the time of NAS setup

		unsigned long long tai; 	// Tracking area ID
		int type;
		
		// Constructor
		UserEquipment(int);

		/* Functions for various LTE procedures */
		bool authenticate(Client&, bool);
		vector<string> setupTunnel(Client&, bool);
		vector<string> setupTunnel_ho(Client&, bool);
		int sendUserData(Client&, int, string, int, int, int, vector<string>&, int);
		void initiate_detach(Client&, int, string, string, string);
		void initiate_ue_context_release(Client&, int, string, string, string, int, bool);
		string send_ue_service_request(Client&, int, string);
		string receive_paging_request(Client&, int, string);
		
		/* High-level functions for encryption/decryption */
		void sendEncryptedData(Client&, string, string, string);
		void receiveEncryptedData(Client&, string, string);

		/* Functions for NAS security setup */
		int key_generation(int);
		vector<unsigned long long> EPS_AKA_algorithm(unsigned long long, unsigned long long, int, int);
		unsigned long long KDF(int, int, unsigned long long, unsigned long long);
		vector<string> KDF_NAS(int, int, int);

		// Function to retrieve starting UE IP address from the controller
		string getStartingIPAddress(Client&);

		//Authentication functions
		void RijndaelKeySchedule( const uint8_t*);
		void KeyAdd(uint8_t[4][4], uint8_t[11][4][4], int);
		int ByteSub(uint8_t[4][4]);
		void ShiftRow(uint8_t[4][4]);
		void MixColumn(uint8_t[4][4]);
		void RijndaelEncrypt( const uint8_t[16], uint8_t[16] );
		void ComputeOPc( const uint8_t[16], const uint8_t[16], uint8_t[16]);
		void derive_kasme(uint8_t[16], uint8_t[16], uint8_t[3], uint8_t[6],uint8_t[6], uint8_t*);
		void generate_autn(const uint8_t[6], const uint8_t[6], const uint8_t[2], const uint8_t[8], uint8_t[16]);
		void f1 (const uint8_t[16], const uint8_t[16], const uint8_t[16], const uint8_t[6], const uint8_t[2],uint8_t[8]);
		void f2345 ( const uint8_t[16], const uint8_t[16], const uint8_t[16],uint8_t[8] , uint8_t[16], uint8_t[16] , uint8_t[6] );
		//static inline void print_buffer(const char*, const uint8_t *buffer, int length);
		int generate_vector(uint8_t[16] , uint64_t, uint8_t[16], uint8_t[3], uint8_t[6], auc_vector_t*);
		bool apu_exit(Client&);
		// Destructor
		~UserEquipment();		
};
