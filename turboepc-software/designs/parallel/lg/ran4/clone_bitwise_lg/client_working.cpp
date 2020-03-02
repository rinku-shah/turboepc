/*************************************************************************

* * This file contains all the socket level functions that is used by UE.  *************************************************************************/

#include "client.h"
#include "utils.h"
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
//#include<unistd.h>

void ProcessPacket(unsigned char* , int);
void print_ip_header(unsigned char* , int);
void print_tcp_packet(unsigned char * , int );
void print_udp_packet(unsigned char * , int );
void print_icmp_packet(unsigned char* , int );
void PrintData (unsigned char* , int);
void PrintDataPayload (unsigned char* , int);
FILE *logfile; 
struct sockaddr_in source,dest;
/*
 *Constructor: Create a UDP socket.
 */
 Client::Client(){
	

        //Create a raw socket of type IPPROTO
        client_socket = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
        cout << "Raw Socket created"<<endl;
        //client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(client_socket < 0){
    cout << "ERROR opening UDP socket" << endl;
    exit(1);
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


/*
 * This function reads from the UDP socket.
 */
 void Client::read_data(){
       // int status;
        unsigned char* my_buffer;
	bzero(client_buffer, BUFFER_SIZE);

	int saddr_size , data_size;
        struct sockaddr saddr;
	
    logfile=fopen("log.txt","w");
    if(logfile==NULL) 
    {
        printf("Unable to create log.txt file.");
    }
        //struct ethhdr *eth = (struct ethhdr *)client_buffer;
        //struct iphdr *iph = (struct iphdr *)(client_buffer  + sizeof(struct ethhdr) );
        //struct udphdr *udph = (struct udphdr*)(client_buffer + sizeof(struct iphdr) + sizeof(struct ethhdr));

        int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
        //setsockopt(sock_raw , SOL_SOCKET , SO_BINDTODEVICE , "eth0" , strlen("eth0")+ 1 );
     
       if(sock_raw < 0)
       {
        //Print the error with proper message
        perror("Socket Error");
        //return 1;
       }
	
	saddr_size = sizeof saddr;
        //Receive a packet
         data_size = recvfrom(sock_raw, client_buffer , BUFFER_SIZE-1 , 0 , &saddr , (socklen_t*)&saddr_size);
       //cout<<&client_buffer<<endl;
       //cout<<status;
        //Now process the packet
     
        ProcessPacket((unsigned char*)client_buffer , data_size); 
			
        //status = recvfrom(client_socket, client_buffer, BUFFER_SIZE-1, 0, NULL, NULL);
        cout<<data_size<<endl;
        fclose(logfile);
        report_error(data_size);
 }


void ProcessPacket(unsigned char* buffer, int size)
{   
    
    int tcp=0,udp=0,icmp=0,others=0,igmp=0,total=0,i,j; 
   
    cout<<"Inside process packet"<<endl;
    ++total;
    //struct ethhdr *eth = (struct ethhdr *)buffer;
    //Get the IP Header part of this packet , excluding the ethernet header
    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    cout<<"Inside process packet:before switch"<<endl;

    switch (iph->protocol) //Check the Protocol and do accordingly...
    {   cout<<"Inside process packet:inside switch"<<endl;
        case 1:  //ICMP Protocol
	    cout<<"Inside process packet:ICMP";
            ++icmp;
            print_icmp_packet( buffer , size);
            break;
         
        case 2:  //IGMP Protocol
            cout<<"Inside process packet:IGMP";
            ++igmp;
            break;
         
        case 6:  //TCP Protocol
            cout<<"Inside process packet:TCP";
            ++tcp;
            print_tcp_packet(buffer , size);
            break;
         
        case 17: //UDP Protocol
	    cout<<"Inside process packet:UDP"<<endl;
            ++udp;
            print_udp_packet(buffer , size);
            break;
         
        default: //Some Other Protocol like ARP etc.
            cout<<"Inside process packet:others";
            ++others;
            break;
    }
    printf("TCP : %d   UDP : %d   ICMP : %d   IGMP : %d   Others : %d   Total : %d\r", tcp , udp , icmp , igmp , others , total);
}
 
void print_ethernet_header(unsigned char* Buffer, int Size)
{
    struct ethhdr *eth = (struct ethhdr *)Buffer;
     
    fprintf(logfile , "\n");
    fprintf(logfile , "Ethernet Header\n");
    fprintf(logfile , "   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );
    fprintf(logfile , "   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );
    fprintf(logfile , "   |-Protocol            : %u \n",(unsigned short)eth->h_proto);
}
 
void print_ip_header(unsigned char* Buffer, int Size)
{
    print_ethernet_header(Buffer , Size);
   
    unsigned short iphdrlen;
         
    struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
    iphdrlen =iph->ihl*4;
     
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
     
    fprintf(logfile , "\n");
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
    fprintf(logfile , "   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
}
 
void print_tcp_packet(unsigned char* Buffer, int Size)
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
}
 
void print_udp_packet(unsigned char *Buffer , int Size)
{
     
    unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
    iphdrlen = iph->ihl*4;
     
    struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));
     
    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
     
    fprintf(logfile , "\n\n***********************UDP Packet*************************\n");
     
    print_ip_header(Buffer,Size);           
     
    fprintf(logfile , "\nUDP Header\n");
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

    fprintf(logfile , "\n###########################################################");
}

void PrintDataPayload (unsigned char* data , int Size)
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
    }
}
 
void print_icmp_packet(unsigned char* Buffer , int Size)
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
}
 
void PrintData (unsigned char* data , int Size)
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
}

/*
 * This function writes to the UDP socket.
 */
 void Client::write_data(){
   
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
    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    //strcpy(data , client_data);
    strcpy(data , client_buffer);
     
    //some address resolution
    strcpy(source_ip , RAN_IP); //Source IP
   
    server_sock_addr.sin_family = AF_INET;
    server_sock_addr.sin_port = htons(g_mme_port);
    server_sock_addr.sin_addr.s_addr = inet_addr(DGW_IP); //Dest IP
     
    //Bind the client socket to UDP port 
    bind(client_socket, (struct sockaddr *)& server_sock_addr, sizeof(server_sock_addr)); 

   //Tell the kernel that we build our own packets
   int one = 1;
   const int *val = &one;
    if(setsockopt(client_socket, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0){
		perror("setsockopt() error");
		exit(-1);
    }

    //Fill in the IP Header
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 16;
    iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data);
    iph->id = htonl (12345); //Id of this packet
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
    udph->source = htons (RAN_UDP_PORT);
    //udph->source = htons (68);
    udph->dest = htons (g_mme_port);
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
        meanTime = 120; //10;
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
                cout<<f<<endl;
        }

        bool done = false, loopedOnce = false;
        int count = 0, tmp_port, ret, realCounter = 0;
        int port_gap = endPort - startingPort;
        int numGlobaltriedPorts = 0;

        do{
        //cout<<"BEFORE SENDING"<<endl;

        string g = GetStdoutFromCommand("iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -t "+to_string(meanTime)+" -B "+srcIp);
//      cout<<"BEFORE SENDING"<<endl;
//      string g = GetStdoutFromCommand("iperf3 -c "+dstIp+" -p "+to_string(portnum)+" -b "+rate+" -M "+to_string(LINK_MTU)+" -f "+format+" -t 60"+" -B "+srcIp);
//      cout<<"AFTER SENDING"<<endl;

                size_t f = g.find("Connecting to host");
                size_t found = g.find("iperf3: error - the server is busy running a test");
                size_t timeout = g.find("iperf3: error - unable to connect to server:");

                if(f == std::string::npos && found == std::string::npos && timeout != std::string::npos){
                        cout<<"iperf3 output: "<<g<<endl;
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

        if(loopedOnce){
                portnum = tmp_port;
        }

        return portnum;
 }

/*
 * This function executes the specified command and returns its output.
 */
 string Client::GetStdoutFromCommand(string cmd) {
        string data;
        FILE * stream;
        const int max_buffer = 256;
        char buffer[max_buffer];
        //cout<<"Entered getstdout"<<endl;

        cmd.append(" 2>&1");

        stream = popen(cmd.c_str(), "r");

        //cout<<"After popen"<<endl;

        if (stream) {
                //cout<<"inside if stream"<<endl;
                while (!feof(stream))
                        //cout<<"inside !feof stream"<<endl;

                        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
                pclose(stream);
        }
//      cout<<"before return"<<endl;

        return data;
 }

// Destructor: Close the UDP client socket
Client::~Client(){
        close(client_socket);
}
                                                                                                                                                                                                                         

