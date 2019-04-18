/*
    Raw UDP sockets
*/

#include <arpa/inet.h>
#include<stdio.h> //for printf
#include<string.h> //memset
#include<sys/socket.h>    //for socket ofcourse
#include<stdlib.h> //for exit(0);
#include<errno.h> //For errno - the error number
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/ip.h>    //Provides declarations for ip header
//#include<iostream>
#include<bits/stdc++.h> 
#include<iomanip>
#include <iostream>
#include <string>
#include<vector>
using namespace std;

/* 
    96 bit (12 bytes) pseudo header needed for udp header checksum calculation 
*/
struct pseudo_header
{
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t udp_length;
};
 
struct send_apn {
    uint8_t pcode;
    //int8_t pcode2;
    uint8_t sep1[6];
    //uint8_t apnt;
    //uint8_t sep2[6];
    //uint8_t key;
};

struct auth_step_one_t{
	uint8_t msg_id;
    uint8_t sep1[6];
    // uint8_t imsi[4];
    uint32_t imsi;
    uint8_t sep2[6];
    uint8_t ue_nw_capability;
    uint8_t sep3[6];
    // bit<256> ksi_asme;
    uint64_t ksi_asme[4];
    uint8_t sep4[6];
    uint8_t sqn[6];
    uint8_t sep5[6];
    uint16_t tai;
};

/*
    Generic checksum calculation function
*/
unsigned short csum(unsigned short *ptr,int nbytes) 
{
    register long sum;
    unsigned short oddbyte;
    register short answer;
 
    sum=0;
    while(nbytes>1) {
        sum+=*ptr++;
        nbytes-=2;
    }
    if(nbytes==1) {
        oddbyte=0;
        *((u_char*)&oddbyte)=*(u_char*)ptr;
        sum+=oddbyte;
    }
 
    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;
     
    return(answer);
}


 
int main (void)
{
    //Create a raw socket of type IPPROTO
    int s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
     
    if(s == -1)
    {
        //socket creation failed, may be because of non-root privileges
        perror("Failed to create raw socket");
        exit(1);
    }
     
    //Datagram to represent the packet
    char datagram[8096] , source_ip[32] , *data , *pseudogram;
     
    //zero out the packet buffer
    memset (datagram, 0, 4096);
     
    //IP header
    struct iphdr *iph = (struct iphdr *) datagram;
     
    //UDP header
    struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));
     
    struct sockaddr_in sin;
    struct pseudo_header psh;
     
    //struct send_apn *apn = (struct send_apn *)malloc(sizeof(struct send_apn));
    // Copy it all to message
    struct send_apn apn ;
    apn.pcode = 0;
    //apn.pcode2 = 0x32;
    //Data part
    apn.sep1[0] = 0x40;
    apn.sep1[1] = 0x3a;
    apn.sep1[2] = 0x23;
    apn.sep1[3] = 0x23;
    apn.sep1[4] = 0x3a;
    apn.sep1[5] = 0x40;

    // std::string message;
    // message.append( (const char*) &apn.pcode, sizeof(uint16_t));
    // message.append( (const char*) & apn.sep1[0],  sizeof(uint8_t));
    // message.append( (const char*) & apn.sep1[1], sizeof(uint8_t));
    // message.append( (const char*) & apn.sep1[2],  sizeof(uint8_t));
    // message.append( (const char*) & apn.sep1[3],  sizeof(uint8_t));
    // message.append( (const char*) & apn.sep1[4],  sizeof(uint8_t));
    // message.append( (const char*) & apn.sep1[5],  sizeof(uint8_t));






// this is my function that send it
//   broadcastMessage(&message[0], message.size());

    
    /*apn.apnt = 0x5;
    apn.sep2[0] = 0x40;
    apn.sep2[1] = 0x3a;
    apn.sep2[2] = 0x23;
    apn.sep2[3] = 0x23;
    apn.sep2[4] = 0x3a;
    apn.sep2[5] = 0x40;
    apn.key = 32;
*/
   


    // char buffer[1000];
    // data = buffer;

    struct auth_step_one_t one;

    // // struct auth_step_one_t *one = (struct auth_step_one_t *)data;

    one.msg_id = 1;
    // // one->msg_id = 1;

	
	one.sep1[0] = 0x40;
    one.sep1[1] = 0x3A;
    one.sep1[2] = 0x23;
    one.sep1[3] = 0x23;
    one.sep1[4] = 0x3A;
    one.sep1[5] = 0x40;




    unsigned long long imsi = 100001;
	// unsigned char x;
	// x=(imsi >> 24) & 0xFF;
	// // cout<<"x = "<<x<<endl;
	// if(x == NULL){
	// 	// cout<<"some null###############";
	// 	one.imsi[0]=0x30;
	// }
	// else{
	// 	// cout<<"some ###############";
	// }
	// one.imsi[0] =  (imsi >> 24) & 0xFF;
	// one.imsi[1] =  (imsi >> 16) & 0xFF;
	// one.imsi[2] =  (imsi >> 8) & 0xFF;
	// one.imsi[3] =  (imsi) & 0xFF;

    // one->imsi[0] =  (imsi >> 24) & 0xFF;
	// one->imsi[1] =  (imsi >> 16) & 0xFF;
	// one->imsi[2] =  (imsi >> 8) & 0xFF;
	// one->imsi[3] =  (imsi) & 0xFF;

    one.imsi = htonl(imsi);
    // one->imsi = htonl(one->imsi);


    one.sep2[0] = 0x40;
    one.sep2[1] = 0x3a;
    one.sep2[2] = 0x23;
    one.sep2[3] = 0x23;
    one.sep2[4] = 0x3a;
    one.sep2[5] = 0x40;
	one.ue_nw_capability = 1;
	one.sep3[0] = 0x40;
    one.sep3[1] = 0x3a;
    one.sep3[2] = 0x23;
    one.sep3[3] = 0x23;
    one.sep3[4] = 0x3a;
    one.sep3[5] = 0x40;
	one.ksi_asme[0] = 0;
	one.ksi_asme[1] = 0;
	one.ksi_asme[2] = 0;
	one.ksi_asme[3] = 20;
	one.sep4[0] = 0x40;
    one.sep4[1] = 0x3a;
    one.sep4[2] = 0x23;
    one.sep4[3] = 0x23;
    one.sep4[4] = 0x3a;
    one.sep4[5] = 0x40;
	one.sqn[0] = 0;
	one.sqn[1] = 0;
	one.sqn[2] = 0;
	one.sqn[3] = 0;
	one.sqn[4] = 0;
	one.sqn[5] = 1;
	one.sep5[0] = 0x40;
    one.sep5[1] = 0x3a;
    one.sep5[2] = 0x23;
    one.sep5[3] = 0x23;
    one.sep5[4] = 0x3a;
    one.sep5[5] = 0x40;
	one.tai = 20; 

    data =  datagram+sizeof(struct iphdr) + sizeof(struct udphdr);
    // memcpy (data, &one, struct_size );

	int len=0;

    

    memcpy(data, &(one.msg_id), sizeof(one.msg_id));
	len+=sizeof(one.msg_id);

    memcpy(data+len, &(one.sep1), sizeof(one.sep1));
	len+=sizeof(one.sep1);

    memcpy(data+len, &(one.imsi), sizeof(one.imsi));
	len+=sizeof(one.imsi);

    memcpy(data+len, &(one.sep2), sizeof(one.sep2));
	len+=sizeof(one.sep2);

    memcpy(data+len, &(one.ue_nw_capability), sizeof(one.ue_nw_capability));
	len+=sizeof(one.ue_nw_capability);

    memcpy(data+len, &(one.sep3), sizeof(one.sep3));
	len+=sizeof(one.sep3);

    memcpy(data+len, &(one.ksi_asme), sizeof(one.ksi_asme));
	len+=sizeof(one.ksi_asme);

    memcpy(data+ len, &(one.sep4), sizeof(one.sep4));
	len+=sizeof(one.sep4);

    memcpy(data+ len, &(one.sqn), sizeof(one.sqn));
	len+=sizeof(one.sqn);

    memcpy(data+ len, &(one.sep5), sizeof(one.sep5));
	len+=sizeof(one.sep5);

    memcpy(data+ len, &(one.tai), sizeof(one.tai));
	len+=sizeof(one.tai);



    cout<<"len = "<<len<<endl;

    int struct_size = len;


    

    
    




    //strcpy(data , apn);
    // strcpy(data , "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0");
    // strcpy(data , "01@:##:@100000\0");
    
    //memcpy ( data, a, sizeof(a) );
    // memcpy(buffer,&one, sizeof(one) );
    // printf("buffer = %u",buffer);
    // strcpy(data,(char *)buffer);
    // memcpy (data, &one, sizeof(one) );
//   memcpy(data,&message[0], message.size());
// printf("message= %s",message);
// strcpy(data,message.c_str());

    // const auto ndr = to_ndr(d) ;
    // auto ptr = reinterpret_cast< const unsigned char* >( std::addressof( ndr.front() ) ) ;

    //memcpy (data, &apn.pcode, sizeof(apn.pcode) );
    //memcpy (data, &apn.pcode, sizeof(apn.pcode) );
    //memcpy (data+sizeof(apn.pcode), &apn.sep1, sizeof(apn.sep1) );


	
    printf("pcode = %d\n",apn.pcode);     
    printf("data = %s\n",data);     
    printf("sizeof send_apn = %ld\n",sizeof(struct auth_step_one_t));     
    printf("sizeof apn = %ld\n",struct_size);     
//cout<<"sizeof apn = "<<struct_size;     
    //some address resolution
    strcpy(source_ip , "192.168.1.1");
     
    sin.sin_family = AF_INET;
    sin.sin_port = htons(80);
    sin.sin_addr.s_addr = inet_addr ("192.168.4.5");
     
    //Fill in the IP Header
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + struct_size ;
    iph->id = htonl (54321); //Id of this packet
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;      //Set to 0 before calculating checksum
    iph->saddr = inet_addr ( source_ip );    //Spoof the source ip address
    iph->daddr = sin.sin_addr.s_addr;
     
    //Ip checksum
    iph->check = csum ((unsigned short *) datagram, iph->tot_len);
     
    //UDP header
    udph->source = htons (6666);
    udph->dest = htons (8622);
    udph->len = htons(8 + struct_size); //tcp header size
    udph->check = 0; //leave checksum 0 now, filled later by pseudo header
     
    //Now the UDP checksum using the pseudo header
    psh.source_address = inet_addr( source_ip );
    psh.dest_address = sin.sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_UDP;
    psh.udp_length = htons(sizeof(struct udphdr) + struct_size );
     
    int psize = sizeof(struct pseudo_header) + sizeof(struct udphdr) + struct_size;
    pseudogram =(char *) malloc(psize);
     
    memcpy(pseudogram , (char*) &psh , sizeof (struct pseudo_header));
    memcpy(pseudogram + sizeof(struct pseudo_header) , udph , sizeof(struct udphdr) + struct_size);
     
    udph->check = csum( (unsigned short*) pseudogram , psize);
     
    //loop if you want to flood :)
    //while (1)
    {
        //Send the packet
        if (sendto (s, datagram, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin)) < 0)
        {
            perror("sendto failed");
        }
        //Data send successfully
        else
        {
            printf ("Packet Send. Length : %d \n" , iph->tot_len);
        }
    }
     
    return 0;
}
 
//Complete 
