#ifndef UTILS_H
#define UTILS_H
#include <fcntl.h>
#include "utils.h"
#endif

// all the struct for messages from RAN -> Controller are defined here 
struct req_starting_ip {
    uint8_t msg_id;
    uint16_t sep1[3];
};

struct auth_step_one_t{
    uint8_t msg_id;
    uint16_t sep1[3];
    uint32_t imsi;
    uint16_t sep2[3];
    uint8_t ue_nw_capability;
    uint16_t sep3[3];
    uint8_t ksi_asme[32];  
    uint16_t sep4[3];
    uint32_t sqn;
    uint16_t sep5[3];
    uint8_t tai[8];
};


struct auth_step_three_t{
    uint8_t msg_id;
    uint16_t sep1[3];
    uint32_t imsi;
    uint16_t sep2[3];
    uint8_t res[8]; 
};

struct nas_step_two_t{
    uint8_t msg_id;
    uint16_t sep1[3];
    uint32_t encrypted_hash[5];
    uint16_t sep2[3];
    uint32_t imsi;
};

struct send_apn_t{
    uint8_t msg_id;
    uint16_t sep1[3];
    uint8_t apn[8];
    uint16_t sep2[3];
    uint32_t key;   
};

struct send_ue_teid_t{
    uint8_t msg_id;
    uint16_t sep1[3];
    uint32_t ue_teid;  
    uint16_t sep2[3];
    uint32_t key;   
};

//DETACH REQUEST
struct detach_req_t{
    uint8_t msg_id;
    uint16_t sep1[3];
    uint32_t ue_ip;
    uint16_t sep2[3];
    uint32_t ue_teid;
    uint16_t sep3[3];
    uint32_t sgw_teid;
    uint16_t sep4[3];
    uint32_t ue_num;
};

// CONTEXT RELEASE
struct ue_context_rel_req_t{
    uint8_t msg_id;
    uint16_t sep1[3];
    uint32_t ue_ip;
    uint16_t sep2[3];
    uint32_t ue_teid;
    uint16_t sep3[3];
    uint32_t sgw_teid;
    uint16_t sep4[3];
    uint32_t ue_num;
};


// SERVICE REQUEST
struct ue_service_req_t{
    uint8_t msg_id;
    uint16_t sep1[3];
    uint32_t ue_num;
    uint16_t sep2[3];
    int32_t ksi_asme;   
    uint16_t sep3[3];
    uint32_t ue_ip;
};

struct initial_ctxt_setup_resp_t{
    uint8_t msg_id;
    uint16_t sep1[3];
    uint32_t ue_teid;
    uint16_t sep2[3];
    uint32_t ue_key;
    uint16_t sep3[3];
    uint32_t ue_ip;
};

class Client{
public:
    int tID;
    int client_socket;
    char client_buffer[BUFFER_SIZE];
        unsigned char my_client_byte_buffer[BUFFER_SIZE];
    char write_client_buffer[BUFFER_SIZE];
    char write_client_byte_buffer[BUFFER_SIZE];
    int sock_raw; //To receive raw packets
    int saddr_size , data_size;
    struct sockaddr saddr;
    // Byte array in C++
    unsigned char client_byte_buffer[BUFFER_SIZE];  

    int server_port;
    const char *server_address;
    struct sockaddr_in server_sock_addr;
    struct sockaddr_in source,dest;
    //bool flag=false; //flag to test the right dest IP for rcv data 
    bool tflag=false; //flag to test dest UDP port for demux of packets
    time_t cT;
    time_t eT;

    clock_t begin, beginOff; //for timeout in us
    clock_t end, endOff;
    clock_t curr, currOff;
    double elapsed_secs, elapsed_secsOff; 

        double timeout = 12000; //timeout value in us
        bool timeoutFlag=false; // Flag =true if read timedout for non-offloadable messages
        double timeoutOff = 2000; //timeout value in us
        bool timeoutFlagOff=false; // Flag =true if read timedout for offloadable messages

    // Constructor
    Client(int);

    // Socket methods
    void input_server_details(int,const char*);
    void read_data();
    void read_data2();

    void write_data(string);
    // void write_data2(char *);
    void write_data2(int);

    void read_byte();
    void write_byte();

    int sendUEData(int, string, string, int, int, int, string, size_t);

    // Utility functions
    string GetStdoutFromCommand(string cmd);
    string runIperfCommand(string cmd,string srcIp);    

    //Raw packet functions

    int ProcessPacket(unsigned char* , int);
    int ProcessPacket2(unsigned char* , int);

    void print_ip_header(unsigned char* , int);
    void print_ip_header2(unsigned char* , int);

    //void print_tcp_packet(unsigned char * , int );
    void print_udp_packet(unsigned char * , int );
    void print_udp_packet2(unsigned char * , int );

    //void print_icmp_packet(unsigned char* , int );
    //void PrintData (unsigned char* , int);
    //void PrintDataPayload (unsigned char* , int);
    //void print_ethernet_header(unsigned char*, int);

    // Destructor
    ~Client();      
};
