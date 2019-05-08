/*************************************************************************

* * This file contains all the socket level functions that is used by UE.  *************************************************************************/

#include "client.h"
//#include "utils.h"
//Below are the files included for raw packets
#include<stdio.h> //for printf
#include<string.h> //memset
#include<sys/socket.h>    //for socket ofcourse
#include<stdlib.h> //for exit(0);
#include<errno.h> //For errno - the error number
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include <unistd.h> //Used to get PID of current process
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
//#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
//#include<netinet/ip.h>    //Provides declarations for ip header
#include<netinet/if_ether.h>  //For ETH_P_ALL
#include<net/ethernet.h>  //For ether_header
//#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include <ctime>

//#include<unistd.h>

/*void ProcessPacket(unsigned char* , int);
void print_ip_header(unsigned char* , int);
void print_tcp_packet(unsigned char * , int );
void print_udp_packet(unsigned char * , int );
void print_icmp_packet(unsigned char* , int );
void PrintData (unsigned char* , int);
void PrintDataPayload (unsigned char* , int);*/
//FILE *logfile; 

/*
 *Constructor: Create a UDP socket.
 */
//int tID;

/*
AUTHENTICATION_STEP_ONE..1
AUTHENTICATION_STEP_THREE..3
NAS_STEP_TWO..20
SEND_APN..5
SEND_UE_TEID..7
DETACH_REQUEST..9
UE_CONTEXT_RELEASE_REQUEST..14
UE_SERVICE_REQUEST..17
INITIAL_CONTEXT_SETUP_RESPONSE..19
REQUEST_STARTING_IP..12
*/

/*float timeout = 5;
time_t curT;
time_t endT;*/

 Client::Client(int ID){
    
    tID=2000+ID; //use global tID to distinguish between threads

        //Create a raw socket of type IPPROTO
        client_socket = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
    if(MY_DEBUG){
        cout << "Raw Send Socket created"<<endl;
    }
        //client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
     if(client_socket < 0){
        cout << "ERROR opening UDP socket" << endl;
    exit(1);
  }

    sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
    if(MY_DEBUG){
    cout << "Raw Receive Socket created"<<endl;
    }
        //int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
        //setsockopt(sock_raw , SOL_SOCKET , SO_BINDTODEVICE , "eth1" , strlen("eth1")+ 1 );
     
       if(sock_raw < 0)
       {
        //Print the error with proper message
        perror("Socket Error");
        //return 1;
       }
 }


struct pseudo_header
{
    u_int32_t source_address;
    u_int32_t dest_address;
    u_int8_t placeholder;
    u_int8_t protocol;
    u_int16_t udp_length;
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

/*
 * This function configures the port number and IP address of the created socket.
 */
 void Client::input_server_details(int server_port, const char *server_address){
        int status;
        this->server_port = server_port;
        this->server_address = server_address;
        bzero((char*)&server_sock_addr, sizeof(server_sock_addr));
        server_sock_addr.sin_family = AF_INET;
        server_sock_addr.sin_port = htons(server_port);
        // Store this IP address in server_sock_addr; pton supports IPv6 while aton does not
        status = inet_pton(AF_INET, server_address, &(server_sock_addr.sin_addr));
        if(status == 0){
                cout<<"ERROR: Invalid IP address"<<endl;
                exit(EXIT_FAILURE);
        }
 }

void Client::read_data2(){
        int status=0;
        unsigned char* my_buffer;
        
        timeoutFlag = false;
        //time(&cT);
        //eT = cT + (int) timeout;
        begin = clock();
        end = begin + timeout; //timeout in usec
        while(status!=17 || !tflag){    
            bzero(my_client_byte_buffer, BUFFER_SIZE);
            data_size = recvfrom(sock_raw, my_client_byte_buffer , BUFFER_SIZE-1 , 0 , &saddr , (socklen_t*)&saddr_size);
            //Now process the packet        
            status=ProcessPacket2((unsigned char*)my_client_byte_buffer , data_size);
            //time(&cT);
            curr = clock();
            //if (cT > eT) {
            elapsed_secs =  double(curr - begin); // / CLOCKS_PER_SEC;
            if (elapsed_secs > end) {
                cout<<"Read Timed out"<<endl;
                timeoutFlag = true;
                break;
            }
        }
}

int Client::ProcessPacket2(unsigned char* buffer, int size)
{   
    int tcp=0,udp=0,icmp=0,others=0,igmp=0,total=0,i,j; 
    ++total;
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    switch (iph->protocol) //Check the Protocol and do accordingly...
    {   //cout<<"Inside process packet:inside switch"<<endl;
         
        case 17: //UDP Protocol
            print_udp_packet2(buffer , size);
            return(17);
            break;
         
        default: //Some Other Protocol like ARP etc.
            //cout<<"Inside process packet:others";
            //++others;
        return(0);
            break;
    }
}
 

 
void Client::print_ip_header2(unsigned char* Buffer, int Size)
{
    unsigned short iphdrlen;
    struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
    iphdrlen =iph->ihl*4;
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
}


void Client::print_udp_packet2(unsigned char *Buffer , int Size)
{
    unsigned short iphdrlen;
    struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
    iphdrlen = iph->ihl*4;
    struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));
    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
    print_ip_header2(Buffer,Size);           
     
    if ((int)ntohs(udph->dest) == tID) {
        tflag=true;
    }
    else 
    tflag=false;
// TODO : only 8 bytes are copied in my_client_byte_buffer in print_udp_packet_2 why?? 
    // memcpy(my_client_byte_buffer,(const char*) Buffer + header_size,sizeof(Buffer + header_size));
    // cout<<"sizeof(Buffer + header_size) = "<<sizeof(Buffer + header_size)<<endl;
    memcpy(my_client_byte_buffer,(const char*) Buffer + header_size,11);

    // strcpy(my_client_byte_buffer, (const char*) Buffer + header_size);
}


/*
 * This function reads from the UDP socket.
 */
 void Client::read_data(){
        int status=0;
        unsigned char* my_buffer;
    timeoutFlag = false;
        //time(&cT);
        //eT = cT + (int) timeout;
        begin = clock();
        end = begin + timeout; //timeout in usec
    while(status!=17 || !tflag){    
     bzero(client_buffer, BUFFER_SIZE);
         data_size = recvfrom(sock_raw, client_buffer , BUFFER_SIZE-1 , 0 , &saddr , (socklen_t*)&saddr_size);
        //Now process the packet        
        status=ProcessPacket((unsigned char*)client_buffer , data_size); 
        //time(&cT);
        curr = clock();
        //if (cT > eT) {
        elapsed_secs =  double(curr - begin); // / CLOCKS_PER_SEC;
        if (elapsed_secs > end) {
          cout<<"Read Timed out"<<endl;
          timeoutFlag = true;
          break;
          }
    }

 }


int Client::ProcessPacket(unsigned char* buffer, int size)
{   
    
    int tcp=0,udp=0,icmp=0,others=0,igmp=0,total=0,i,j; 
   
    //cout<<"Inside process packet"<<endl;
    ++total;
    //struct ethhdr *eth = (struct ethhdr *)buffer;
    //Get the IP Header part of this packet , excluding the ethernet header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    //cout<<"Inside process packet:before switch"<<endl;

    switch (iph->protocol) //Check the Protocol and do accordingly...
    {   //cout<<"Inside process packet:inside switch"<<endl;
       /* case 1:  //ICMP Protocol
        //cout<<"Inside process packet:ICMP";
            ++icmp;
            //print_icmp_packet( buffer , size);
            break;
         
        case 2:  //IGMP Protocol
            //cout<<"Inside process packet:IGMP";
            ++igmp;
            break;
         
        case 6:  //TCP Protocol
            //cout<<"Inside process packet:TCP";
            ++tcp;
            //print_tcp_packet(buffer , size);
            break; */
         
        case 17: //UDP Protocol
        //cout<<"Inside process packet:UDP"<<endl;
            //++udp;
            print_udp_packet(buffer , size);
        return(17);
            break;
         
        default: //Some Other Protocol like ARP etc.
            //cout<<"Inside process packet:others";
            //++others;
        return(0);
            break;
    }
    //printf("TCP : %d   UDP : %d   ICMP : %d   IGMP : %d   Others : %d   Total : %d\r", tcp , udp , icmp , igmp , others , total);
}
 
/*void Client::print_ethernet_header(unsigned char* Buffer, int Size)
{
    struct ethhdr *eth = (struct ethhdr *)Buffer;
     
    fprintf(logfile , "\n");
    fprintf(logfile , "Ethernet Header\n");
    fprintf(logfile , "   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );
    fprintf(logfile , "   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );
    fprintf(logfile , "   |-Protocol            : %u \n",(unsigned short)eth->h_proto);
}*/
 
void Client::print_ip_header(unsigned char* Buffer, int Size)
{
    //print_ethernet_header(Buffer , Size);
   
    unsigned short iphdrlen;
         
    struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
    iphdrlen =iph->ihl*4;
     
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
     
    /*fprintf(logfile , "\n");
    fprintf(logfile , "IP Header\n");
    fprintf(logfile , "   |-IP Version        : %d\n",(unsigned int)iph->version);
    fprintf(logfile , "   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    fprintf(logfile , "   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
    fprintf(logfile , "   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    fprintf(logfile , "   |-Identification    : %d\n",ntohs(iph->id));
    //fprintf(logfile , "   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
    //fprintf(logfile , "   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
    //fprintf(logfile , "   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
    fprintf(logfile , "   |-TTL      : %d\n",(unsigned int)iph->ttl);
    fprintf(logfile , "   |-Protocol : %d\n",(unsigned int)iph->protocol);
    fprintf(logfile , "   |-Checksum : %d\n",ntohs(iph->check));
    fprintf(logfile , "   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
    fprintf(logfile , "   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));*/
   /* if ((string)inet_ntoa(dest.sin_addr) == "10.127.41.2") {
    //cout<<"Dest IP= "<<inet_ntoa(dest.sin_addr)<<endl;
    flag=true;
    }
    else 
    flag=false; */
}
 
/*void Client::print_tcp_packet(unsigned char* Buffer, int Size)
{
    unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)( Buffer  + sizeof(struct ethhdr) );
    iphdrlen = iph->ihl*4;
     
    struct tcphdr *tcph=(struct tcphdr*)(Buffer + iphdrlen + sizeof(struct ethhdr));
             
    int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;
     
    fprintf(logfile , "\n\n***********************TCP Packet*************************\n");  
         
    print_ip_header(Buffer,Size);
         
    fprintf(logfile , "\n");
    fprintf(logfile , "TCP Header\n");
    fprintf(logfile , "   |-Source Port      : %u\n",ntohs(tcph->source));
    fprintf(logfile , "   |-Destination Port : %u\n",ntohs(tcph->dest));
    fprintf(logfile , "   |-Sequence Number    : %u\n",ntohl(tcph->seq));
    fprintf(logfile , "   |-Acknowledge Number : %u\n",ntohl(tcph->ack_seq));
    fprintf(logfile , "   |-Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
    //fprintf(logfile , "   |-CWR Flag : %d\n",(unsigned int)tcph->cwr);
    //fprintf(logfile , "   |-ECN Flag : %d\n",(unsigned int)tcph->ece);
    fprintf(logfile , "   |-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
    fprintf(logfile , "   |-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
    fprintf(logfile , "   |-Push Flag            : %d\n",(unsigned int)tcph->psh);
    fprintf(logfile , "   |-Reset Flag           : %d\n",(unsigned int)tcph->rst);
    fprintf(logfile , "   |-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
    fprintf(logfile , "   |-Finish Flag          : %d\n",(unsigned int)tcph->fin);
    fprintf(logfile , "   |-Window         : %d\n",ntohs(tcph->window));
    fprintf(logfile , "   |-Checksum       : %d\n",ntohs(tcph->check));
    fprintf(logfile , "   |-Urgent Pointer : %d\n",tcph->urg_ptr);
    fprintf(logfile , "\n");
    fprintf(logfile , "                        DATA Dump                         ");
    fprintf(logfile , "\n");
         
    fprintf(logfile , "IP Header\n");
    PrintData(Buffer,iphdrlen);
         
    fprintf(logfile , "TCP Header\n");
    PrintData(Buffer+iphdrlen,tcph->doff*4);
         
    fprintf(logfile , "Data Payload\n");    
    PrintData(Buffer + header_size , Size - header_size );
                         
    fprintf(logfile , "\n###########################################################");
}*/
 
void Client::print_udp_packet(unsigned char *Buffer , int Size)
{
     
    unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
    iphdrlen = iph->ihl*4;
     
    struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));
     
    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
     
    //fprintf(logfile , "\n\n***********************UDP Packet*************************\n");
     
    print_ip_header(Buffer,Size);           
     
    /*fprintf(logfile , "\nUDP Header\n");
    fprintf(logfile , "   |-Source Port      : %d\n" , ntohs(udph->source));
    fprintf(logfile , "   |-Destination Port : %d\n" , ntohs(udph->dest));
    fprintf(logfile , "   |-UDP Length       : %d\n" , ntohs(udph->len));
    fprintf(logfile , "   |-UDP Checksum     : %d\n" , ntohs(udph->check));
     
    fprintf(logfile , "\n");
    fprintf(logfile , "IP Header\n");
    PrintData(Buffer , iphdrlen);
         
    fprintf(logfile , "UDP Header\n");
    PrintData(Buffer+iphdrlen , sizeof udph);
         
    fprintf(logfile , "Data Payload\n");    
     
    //Move the pointer ahead and reduce the size of string
    PrintData(Buffer + header_size , Size - header_size);
     
    PrintDataPayload(Buffer + header_size , Size - header_size);
    unsigned char *temp_buffer;
    temp_buffer = Buffer + header_size;*/

        if ((int)ntohs(udph->dest) == tID) {
        tflag=true;
    }
    else 
    tflag=false;

    strcpy(client_buffer, (const char*) Buffer + header_size);
    /*int c = 0;
    while (temp_buffer[c] != '\0') {
         client_buffer[c] = temp_buffer[c];
          c++;
    }
   client_buffer[c] = '\0';*/
    
//    fprintf(logfile , "\n###########################################################");
}

/*void Client::PrintDataPayload (unsigned char* data , int Size)
{
    int i , j;
    fprintf(logfile , "%s\n",(unsigned char*)data);
    for(i=0 ; i < Size ; i++)
    {
        fprintf(logfile , "%c",(unsigned char)data[i]);
        /*if( i!=0 && i%16==0)   //if one line of hex printing is complete...
        {
            fprintf(logfile , "         ");
            for(j=i-16 ; j<i ; j++)
            {
                if(data[j]>=32 && data[j]<=128)
                    fprintf(logfile , "%c",(unsigned char)data[j]); //if its a number or alphabet
                 
                else fprintf(logfile , "."); //otherwise print a dot
            }
            fprintf(logfile , "\n");
        } 
         
        if(i%16==0) fprintf(logfile , "   ");
            fprintf(logfile , " %02X",(unsigned int)data[i]);
                 
        if( i==Size-1)  //print the last spaces
        {
            for(j=0;j<15-i%16;j++) 
            {
              fprintf(logfile , "   "); //extra spaces
            }
             
            fprintf(logfile , "         ");
             
            for(j=i-i%16 ; j<=i ; j++)
            {
                if(data[j]>=32 && data[j]<=128) 
                {
                  fprintf(logfile , "%c",(unsigned char)data[j]);
                }
                else
                {
                  fprintf(logfile , ".");
                }
            }
             
            fprintf(logfile ,  "\n" );
        }*/
//    }
//}
 
/*void Client::print_icmp_packet(unsigned char* Buffer , int Size)
{
    unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr));
    iphdrlen = iph->ihl * 4;
     
    struct icmphdr *icmph = (struct icmphdr *)(Buffer + iphdrlen  + sizeof(struct ethhdr));
     
    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof icmph;
     
    fprintf(logfile , "\n\n***********************ICMP Packet*************************\n"); 
     
    print_ip_header(Buffer , Size);
             
    fprintf(logfile , "\n");
         
    fprintf(logfile , "ICMP Header\n");
    fprintf(logfile , "   |-Type : %d",(unsigned int)(icmph->type));
             
    if((unsigned int)(icmph->type) == 11)
    {
        fprintf(logfile , "  (TTL Expired)\n");
    }
    else if((unsigned int)(icmph->type) == ICMP_ECHOREPLY)
    {
        fprintf(logfile , "  (ICMP Echo Reply)\n");
    }
     
    fprintf(logfile , "   |-Code : %d\n",(unsigned int)(icmph->code));
    fprintf(logfile , "   |-Checksum : %d\n",ntohs(icmph->checksum));
    //fprintf(logfile , "   |-ID       : %d\n",ntohs(icmph->id));
    //fprintf(logfile , "   |-Sequence : %d\n",ntohs(icmph->sequence));
    fprintf(logfile , "\n");
 
    fprintf(logfile , "IP Header\n");
    PrintData(Buffer,iphdrlen);
         
    fprintf(logfile , "UDP Header\n");
    PrintData(Buffer + iphdrlen , sizeof icmph);
         
    fprintf(logfile , "Data Payload\n");    
     
    //Move the pointer ahead and reduce the size of string
    PrintData(Buffer + header_size , (Size - header_size) );
     
    fprintf(logfile , "\n###########################################################");
}*/
 
/*void Client::PrintData (unsigned char* data , int Size)
{
    int i , j;
    for(i=0 ; i < Size ; i++)
    {
        if( i!=0 && i%16==0)   //if one line of hex printing is complete...
        {
            fprintf(logfile , "         ");
            for(j=i-16 ; j<i ; j++)
            {
                if(data[j]>=32 && data[j]<=128)
                    fprintf(logfile , "%c",(unsigned char)data[j]); //if its a number or alphabet
                 
                else fprintf(logfile , "."); //otherwise print a dot
            }
            fprintf(logfile , "\n");
        } 
         
        if(i%16==0) fprintf(logfile , "   ");
            fprintf(logfile , " %02X",(unsigned int)data[i]);
                 
        if( i==Size-1)  //print the last spaces
        {
            for(j=0;j<15-i%16;j++) 
            {
              fprintf(logfile , "   "); //extra spaces
            }
             
            fprintf(logfile , "         ");
             
            for(j=i-i%16 ; j<=i ; j++)
            {
                if(data[j]>=32 && data[j]<=128) 
                {
                  fprintf(logfile , "%c",(unsigned char)data[j]);
                }
                else
                {
                  fprintf(logfile , ".");
                }
            }
             
            fprintf(logfile ,  "\n" );
        }
    }
}*/

/*
 * This function writes to the UDP socket.
 */

 void Client::write_data2(int data_len){
      //Datagram to represent the packet
    char datagram[4096] , source_ip[32] , *data , *pseudogram;
     
    //zero out the packet buffer
    memset (datagram, 0, 4096);
     
    //IP header
    struct iphdr *iph = (struct iphdr *) datagram;
     
    //UDP header
    struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));
     
    struct sockaddr_in server_sock_addr;
    struct pseudo_header psh;
     
    //Data part
    
    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    if(MY_DEBUG){   
        cout<<"data len = "<<data_len<<endl;
    }

    memcpy (data, client_buffer, data_len);
    
    bzero(client_buffer, BUFFER_SIZE);
    if(MY_DEBUG){   
    cout<<"SENDING - "<<data<<endl;
    }
    //cout<<"Thread ID- "<<tID<<endl;
    /*int c = 0;
    while (client_buffer[c] != '\0') {
      data[c] = client_buffer[c];
      c++;
    }
    data[c] = '\0';*/

    //some address resolution
    strcpy(source_ip , RAN_IP); //Source IP
   
    server_sock_addr.sin_family = AF_INET;
    server_sock_addr.sin_port = htons(g_mme_port);
    server_sock_addr.sin_addr.s_addr = inet_addr(DGW_IP); //Dest IP
     
    //Bind the client socket to UDP port 
    //bind(client_socket, (struct sockaddr *)& server_sock_addr, sizeof(server_sock_addr)); 

   //Tell the kernel that we build our own packets
   /*int one = 1;
   const int *val = &one;
    if(setsockopt(client_socket, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0){
        perror("setsockopt() error");
        exit(-1);
    }*/

    //Fill in the IP Header
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = stoi("1")*4; //16;
    iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + data_len;
    iph->id = htonl(0); //htonl (12345); //Id of this packet
    iph->frag_off = 0;
    // iph->ttl = 255;
    iph->ttl = 64;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;      //Set to 0 before calculating checksum
    iph->saddr = inet_addr(source_ip);    //Spoof the source ip address
    iph->daddr = server_sock_addr.sin_addr.s_addr;
     
    //Ip checksum
    iph->check = csum ((unsigned short *) datagram, iph->tot_len);
    
    //int pid = getpid();
    //int parentsPID = getppid();     

    //UDP header
    //udph->source = htons (RAN_UDP_PORT);
    udph->source = htons (tID);
    udph->dest = htons (g_mme_port);// htons(stoi(msg_id)+2000);
    udph->len = htons(8 + data_len); //tcp header size
    udph->check = 0; //leave checksum 0 now, filled later by pseudo header
     
    //Now the UDP checksum using the pseudo header
    psh.source_address = inet_addr( source_ip );
    psh.dest_address = server_sock_addr.sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_UDP;
    psh.udp_length = htons(sizeof(struct udphdr) + data_len );
     
    int psize = sizeof(struct pseudo_header) + sizeof(struct udphdr) + data_len;
    pseudogram =(char*) malloc(psize);
     
    memcpy(pseudogram , (char*) &psh , sizeof (struct pseudo_header));
    memcpy(pseudogram + sizeof(struct pseudo_header) , udph , sizeof(struct udphdr) + data_len);
     
    udph->check = csum( (unsigned short*) pseudogram , psize);

    int status;
    status = sendto(client_socket, datagram, iph->tot_len, 0 , (struct sockaddr*) &server_sock_addr, sizeof(server_sock_addr));
    
    report_error(status);


 }

 void Client::write_data(string msg_id){
   
    //Datagram to represent the packet
    char datagram[4096] , source_ip[32] , *data , *pseudogram;
     
    //zero out the packet buffer
    memset (datagram, 0, 4096);
     
    //IP header
    struct iphdr *iph = (struct iphdr *) datagram;
     
    //UDP header
    struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));
     
    struct sockaddr_in server_sock_addr;
    struct pseudo_header psh;
     
    //Data part
    //char client_data[BUFFER_SIZE];
    //strcpy(client_data, client_buffer);
    //bzero(client_buffer, BUFFER_SIZE);
    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    //strcpy(data , client_data);

    strcpy(data , client_buffer);
    bzero(client_buffer, BUFFER_SIZE);
    if(MY_DEBUG){   
    cout<<"SENDING - "<<data<<endl;
    }
    //cout<<"Thread ID- "<<tID<<endl;
    /*int c = 0;
    while (client_buffer[c] != '\0') {
      data[c] = client_buffer[c];
      c++;
    }
    data[c] = '\0';*/

    //some address resolution
    strcpy(source_ip , RAN_IP); //Source IP
   
    server_sock_addr.sin_family = AF_INET;
    server_sock_addr.sin_port = htons(g_mme_port);
    server_sock_addr.sin_addr.s_addr = inet_addr(DGW_IP); //Dest IP
     
    //Bind the client socket to UDP port 
    //bind(client_socket, (struct sockaddr *)& server_sock_addr, sizeof(server_sock_addr)); 

   //Tell the kernel that we build our own packets
   /*int one = 1;
   const int *val = &one;
    if(setsockopt(client_socket, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0){
        perror("setsockopt() error");
        exit(-1);
    }*/

    //Fill in the IP Header
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = stoi(msg_id)*4; //16;
    iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data);
    iph->id = htonl(0); //htonl (12345); //Id of this packet
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;      //Set to 0 before calculating checksum
    iph->saddr = inet_addr(source_ip);    //Spoof the source ip address
    iph->daddr = server_sock_addr.sin_addr.s_addr;
     
    //Ip checksum
    iph->check = csum ((unsigned short *) datagram, iph->tot_len);
    
    //int pid = getpid();
    //int parentsPID = getppid();     

    //UDP header
    //udph->source = htons (RAN_UDP_PORT);
    udph->source = htons (tID);
    udph->dest = htons (g_mme_port);// htons(stoi(msg_id)+2000);
    udph->len = htons(8 + strlen(data)); //tcp header size
    udph->check = 0; //leave checksum 0 now, filled later by pseudo header
     
    //Now the UDP checksum using the pseudo header
    psh.source_address = inet_addr( source_ip );
    psh.dest_address = server_sock_addr.sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_UDP;
    psh.udp_length = htons(sizeof(struct udphdr) + strlen(data) );
     
    int psize = sizeof(struct pseudo_header) + sizeof(struct udphdr) + strlen(data);
    pseudogram =(char*) malloc(psize);
     
    memcpy(pseudogram , (char*) &psh , sizeof (struct pseudo_header));
    memcpy(pseudogram + sizeof(struct pseudo_header) , udph , sizeof(struct udphdr) + strlen(data));
     
    udph->check = csum( (unsigned short*) pseudogram , psize);

    int status;
    status = sendto(client_socket, datagram, iph->tot_len, 0 , (struct sockaddr*) &server_sock_addr, sizeof(server_sock_addr));
    
    report_error(status);

 }

/*
 * This function reads from the UDP socket in the form of unsigned char.
 */
 void Client::read_byte(){
        int status;
        bzero(client_byte_buffer, BUFFER_SIZE);
        status = recvfrom(client_socket, client_byte_buffer, BUFFER_SIZE-1, 0, NULL, NULL);
        report_error(status);
 }

/*
 * This function writes to the UDP socket in the form of unsigned char.
 */
 void Client::write_byte(){
        int status;
        status = sendto(client_socket, client_byte_buffer, strlen((char*)client_byte_buffer), 0,(struct sockaddr*)&server_sock_addr, sizeof(server_sock_addr));
        report_error(status);
 }

/*
 * This function generates TCP traffic at given rate using iperf3 for the specified duration of time.
 */
 int Client::sendUEData(int ue_num, string srcIp, string dstIp, int portnum, int startingPort, int endPort, string rate, size_t meanTime){
        //meanTime = 300; //10;
        //cout<<"MEAN DATA TIME="<<meanTime<<endl;

        const char *srcIpptr = srcIp.c_str();
        char c = tolower(rate[rate.size()-1]);
        string dstNetwork(SINK_SERVER_NETMASK);
        string format(1,c);

        //string f = "iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -B "+srcIp;
                                                                                                                                                                                                                         
        string f = "iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -t "+to_string(meanTime)+" -B "+srcIp;

//      string f = "iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -t 120"+" -B "+srcIp;

        if(DO_DEBUG){
                cout<<"SOURCE IP="<<srcIp<<endl;
                cout<<"DESTINATION IP="<<dstIp<<endl;
                cout<<"*** client.cpp DATA TIME _--- "<<meanTime<<endl;
                cout<<f<<endl;
        }

        bool done = false, loopedOnce = false;
        int count = 0, tmp_port, ret, realCounter = 0;
        int port_gap = endPort - startingPort;
        int numGlobaltriedPorts = 0;

        do{
        
    // string g = runIperfCommand("iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -t "+to_string(meanTime)+" -B "+srcIp, srcIp);
    string No_of_bytes="1K";
    string g = runIperfCommand("iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -n "+No_of_bytes+" -B "+srcIp+" -l "+to_string(1424), srcIp );


//      string g = GetStdoutFromCommand("iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -t 60"+" -B "+srcIp);
        string cmd1 = "iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -n "+No_of_bytes+" -B "+srcIp+" -l "+to_string(1424);
        // string cmd1 = "iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -t "+to_string(meanTime)+" -B "+srcIp;

        size_t f = g.find("Connecting to host");
                size_t found = g.find("iperf3: error - the server is busy running a test");
                size_t timeout = g.find("iperf3: error - unable to connect to server:");

                if(f == std::string::npos && found == std::string::npos && timeout != std::string::npos){
                        cout<<"FAILURE FOR "<<cmd1<<endl;
                        cout<<"iperf3 output: "<<g<<"\n for cmd "<<cmd1<<endl;
                        //return portnum;
            exit(1);
                }
                if(found != std::string::npos){
                        cout<<"iperf3 output: "<<g<<endl;
                        cout<< "Using local port " << portnum<<" "<<" count="<<count<<" real counter="<<realCounter<<endl;
                        portnum++;
                        if(portnum >= endPort){
                                if(count < port_gap){
                                        portnum = startingPort;
                                }else{
                                        loopedOnce = true;
                                        tmp_port = startingPort;
                                }
                        }
                        if(count >= port_gap && numGlobaltriedPorts <= NUM_GLOBAL_PORTS){
                                numGlobaltriedPorts++;
                                // Use global ports
                                ret = pthread_mutex_lock(&request_mutex);
                                if(ret < 0)
                                {
                                        perror("ERROR: mutex lock failed");
                                        exit(1);
                                }
                                portnum = global_ports[globalPortsIndex];
                                if(globalPortsIndex < NUM_GLOBAL_PORTS-1){
                                        globalPortsIndex++;
                                }else{
                                        globalPortsIndex = 0;
                                }

                                // Releasing lock
                                ret = pthread_mutex_unlock(&request_mutex);
                                if(ret < 0)
                                {
                                        perror("ERROR: mutex unlock failed");
                                        exit(1);
                                }
                                cout<<"Global port ="<<portnum<<" used approx index="<<(globalPortsIndex-1)<<endl;
                        }else if(count >= port_gap && numGlobaltriedPorts > NUM_GLOBAL_PORTS){
                                numGlobaltriedPorts = 0;
                                count = 0;
                                portnum = tmp_port;
                        }
            count++;
                        realCounter++;
                }else{
                        if(realCounter != 0){
                                cout<< "Using global port " << portnum<<" "<<realCounter<<" DONE"<<endl;
                        }
                        done = true;
                }
        }while(!done);
    if(DO_DEBUG)
        cout<<"SENT DATA with SRC IP "<<srcIp<<endl;
        if(loopedOnce){
                portnum = tmp_port;
        }
    /*string get_pid = "ps -aux | grep -E 'iperf3.*"+srcIp+"'|grep -v 'grep'| tr -s \" \"| cut -d \" \" -f 2";
    cout<<"GET PID COMMAND --- "<<get_pid<<endl;
    string pid = GetStdoutFromCommand(get_pid);
    cout<<"\nPROCESS TO KILL - "<<pid<<endl;    
    if(!pid.empty()){
        cout<<"\ninside PROCESS TO KILL - "<<pid<<endl;         
        string kill_out = GetStdoutFromCommand("sudo kill -9 "+pid);
        cout<<"KILL OUTPUT ---- "<<kill_out<<endl;
    }*/
//  const char* kill_cmd = ("sudo kill $(ps -aux | grep -E 'iperf3.*"+srcIp+"'|grep -v 'grep'| tr -s \" \"| cut -d \" \" -f 2)").c_str();
//  system(kill_cmd);

        return portnum;
 }

/*
 * This function executes the specified command and returns its output.
 */
 string Client::runIperfCommand(string cmd, string srcIp) {
        string data;
        FILE * stream;
        const int max_buffer = 256;
        char buffer[max_buffer];
        // cout<<"cmd = "<<cmd<<endl;
        //cout<<"Entered getstdout"<<endl;

        // cmd.append(" 2>&1");

        stream = popen(cmd.c_str(), "r");
    /*int fd = fileno(stream);
    int flags;
    flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);*/



        //cout<<"After popen"<<endl;


        if (stream) {
                //cout<<"inside if stream"<<endl;
                while (!feof(stream)){
                        //cout<<"inside !feof stream "<<cmd<<endl;

                        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
                }
                string get_pid = "ps -aux | grep -E 'iperf3.*"+srcIp+"'|grep -v 'grep'| tr -s \" \"| cut -d \" \" -f 2";
                //cout<<"client --- GET PID COMMAND --- "<<get_pid<<endl;
                string pid = GetStdoutFromCommand(get_pid);
                //cout<<"\nclient --- PROCESS TO KILL - "<<pid<<endl;   
                if(!pid.empty()){
                    //cout<<"\ninside PROCESS TO KILL - "<<pid<<endl;       
                    string kill_out = GetStdoutFromCommand("sudo kill -9 "+pid);
                    
                    //cout<<"KILL OUTPUT ---- "<<kill_out<<endl;
                }
        


            int status = pclose(stream);
            if(status!=-1){

            }
            else{
            cout<<"status some error= "<<endl;

            }
        }
        else{
            cout<<"some eroor in stream in runiperfcommand"<<endl;
        }

        
//      cout<<"before return"<<endl;
        return data;
 }

string Client::GetStdoutFromCommand(string cmd) {
        string data;
        FILE * stream;
        const int max_buffer = 256;
        char buffer[max_buffer];
        //cout<<"Entered getstdout"<<endl;
        // if you want to see error uncomment the below line
        // cmd.append(" 2>&1");

        stream = popen(cmd.c_str(), "r");

        //cout<<"After popen"<<endl;

        if (stream) {
                //cout<<"inside if stream"<<endl;
                while (!feof(stream)){
                        //cout<<"inside !feof stream "<<cmd<<endl;

                        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
                }
        
        // pclose(stream);
        int status = pclose(stream);
            if(status!=-1){

            }
            else{
            cout<<"status ###################= "<<endl;

            }
        }
        else{
            cout<<"some error in stream"<<endl;
        }
//      cout<<"before return"<<endl;

        return data;
 }

// Destructor: Close the UDP client socket
Client::~Client(){
        close(client_socket);
    close(sock_raw);
}
                                                                                                                                                                                                                         
