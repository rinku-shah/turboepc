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
    int8_t pcode;
    int8_t sep1[6];
    //uint8_t apnt;
    //uint8_t sep2[6];
    //uint8_t key;
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
    struct send_apn apn;
    apn.pcode = 12;
    //Data part
    apn.sep1[0] = 0x40;
    apn.sep1[1] = 0x3a;
    apn.sep1[2] = 0x23;
    apn.sep1[3] = 0x23;
    apn.sep1[4] = 0x3a;
    apn.sep1[5] = 0x40;
    /*apn.apnt = 0x5;
    apn.sep2[0] = 0x40;
    apn.sep2[1] = 0x3a;
    apn.sep2[2] = 0x23;
    apn.sep2[3] = 0x23;
    apn.sep2[4] = 0x3a;
    apn.sep2[5] = 0x40;
    apn.key = 32;
*/
    data =  datagram+sizeof(struct iphdr) + sizeof(struct udphdr);
    //strcpy(data , apn);
    //strcpy(data , "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0");
    //memcpy ( data, a, sizeof(a) );
    memcpy (data, &apn, sizeof(apn) );
	
printf("data = %s\n",data);     
printf("sizeof send_apn = %ld\n",sizeof(struct send_apn));     
printf("sizeof apn = %ld\n",sizeof(apn));     
//cout<<"sizeof apn = "<<sizeof(apn);     
    //some address resolution
    strcpy(source_ip , "192.168.1.1");
     
    sin.sin_family = AF_INET;
    sin.sin_port = htons(80);
    sin.sin_addr.s_addr = inet_addr ("192.168.1.2");
     
    //Fill in the IP Header
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data) ;
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
    udph->len = htons(8 + strlen(data)); //tcp header size
    udph->check = 0; //leave checksum 0 now, filled later by pseudo header
     
    //Now the UDP checksum using the pseudo header
    psh.source_address = inet_addr( source_ip );
    psh.dest_address = sin.sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_UDP;
    psh.udp_length = htons(sizeof(struct udphdr) + strlen(data) );
     
    int psize = sizeof(struct pseudo_header) + sizeof(struct udphdr) + strlen(data);
    pseudogram =(char *) malloc(psize);
     
    memcpy(pseudogram , (char*) &psh , sizeof (struct pseudo_header));
    memcpy(pseudogram + sizeof(struct pseudo_header) , udph , sizeof(struct udphdr) + strlen(data));
     
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
