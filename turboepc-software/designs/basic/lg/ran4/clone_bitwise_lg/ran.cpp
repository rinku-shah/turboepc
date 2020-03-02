#include "ran.h"
#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <signal.h>
#define BUFFER_SIZE 1024
using namespace std;

#define NO_EPOCH 8
#define INST_ARR_LEN 300
#define INST_PERIOD 10 // period in secs
// Boolean values corresponding to various LTE procedures
bool setUpTunnel = false;
bool doDetach = false;
bool sendData = true;			//keep either doDetach, or s1_release true for sending data
bool assignIpToInterface = true; //For data traffic only
bool s1_release = false;		// UE initiated S1 Release
bool doEncryption = false;
bool checkIntegrity = false;
bool ueServiceRequest = false;	// UE initiated service request (uplink traffic)
bool networkServiceRequest = false;	// Network initiated service request (downlink traffic)
//mix of traffic types
/* attach-detach, context-rel/service-req, att-data_all_the_time-det, att-data(default=1s)-det-loop, att-serv_req-data-loop2-det-loop1, att-serv-req-data-loop2-det*/
// vector<vector<int>> traffic_mix={{0,100,0,0,0},{499,99501,0,0,0},{1499,98501,0,0,0},{2999,97001,0,0,0},{6999,93001,0,0,0},{8999,91001,0,0,0},{10999,89001,0,0,0},{30999,69001,0,0,0},{40999,59001,0,0,0},{50999,49001,0,0,0},{60999,39001,0,0,0},{100,0,0,0,0}};
vector<vector<int>> traffic_mix={{0,0,0,9909,90991,0},{499,0,0,0,99501,0},{1499,98501,0,0,0,0},{2999,97001,0,0,0,0},{6999,93001,0,0,0,0},{8999,91001,0,0,0,0},{10999,89001,0,0,0,0},{30999,69001,0,0,0,0},{40999,59001,0,0,0,0},{0,0,0,0,100,0},{0,0,0,0,0,100},{0,0,0,100,0,0}};
int start_ue = 400;
int wait_latency = 48000; //28000 for <1ms; 58000 for 5ms, 108000 for 10ms //This is the delay between two messages ; For read retransmit on timeout set "double timeout =x" in client.h file

//2_98,0
//5_95,1
//6_94,2
//10_90,3
//25_75,4........15_85,4
//...............20_80,5
//................27_73,6
//50_50,7.........37_63,7
//................50_50,8
//70_30,9.........65_35,9
//80_20,10
//100_0,11

//vector<vector<int>> traffic_mix={{1499,98501,0,0,0},{3999,95001,0,0,0},{10999,89001,0,0,0},{30999,69001,0,0,0},{50999,49001,0,0,0},{70999,29001,0,0,0},{0,99999,0,0,0},{19000,80999,0,0,1},{0,0,0,100,0},{0,0,100,0,0},{0,100,0,0,0},{499,99501,0,0,0},{1499,98501,0,0,0},{2999,97001,0,0,0},{6999,93001,0,0,0},{8999,91001,0,0,0},{10999,89001,0,0,0},{20999,79001,0,0,0},{30999,69001,0,0,0},{40999,59001,0,0,0},{50999,49001,0,0,0},{60999,39001,0,0,0}/*,{750,200,0,50,0},{100,0,0,0,0}*/};
//{1999,98001,0,0,0}:ATTACH=10-15% mix=0
//{4999,95001,0,0,0}:ATTACH=      mix=1
//{11999,88001,0,0,0}:ATTACH=25-30% mix=2
//{31999,68001,0,0,0}:ATTACH=40-45% mix=3
//{51999,48001,0,0,0}:ATTACH=60-65% mix=4
//{71999,28001,0,0,0}:ATTACH=80-85% mix=5
//{0,99999,0,0,0}: ATTACH=2% mix=6
//mix0 -> 80-20 wrt time, mix2 -> 20-80 wrt time

/// DYNAMIC LOAD GENERATOR ///
std::mutex traffic_mtx;
std::mutex inst_mtx;
std::mutex lat_mtx;
int traffic_shape_size = NO_EPOCH;
//traffic_shape[5][2] = {{4,3},{4,0},{4,3},{4,1},{4,2}};
//traffic_shape[3][2] = {{4,0},{6,3},{4,0}};
//traffic_shape[5][2] = {{4,3},{6,0},{4,3},{7,0}};
//{{4,3},{4,0},{4,2},{4,1},{4,4}};
//{4,3},{6,0},{4,3},{6,0} //Normal load
//{{4,3},{1,0},{1,4},{4,0},{4,0}}; //bad load
//int traffic_shape[5][2] = {{5,1},{5,10},{5,1},{6,10}};
//int traffic_shape[10][2] = {{5,1},{5,0},{5,9},{5,7},{5,1},{5,3},{5,0},{6,10}};
//int traffic_shape[5][2] = {{3,1},{3,10},{3,1},{4,10}};
int traffic_shape[10][2] = {{5,1},{5,0},{5,9},{5,3},{5,1},{5,11},{5,10},{6,7}};
//int traffic_shape[10][2] = {{5,1},{5,9},{6,0}};
int curr_mix_index=0;
bool dynLoad = false;
bool instrumentTptLat = false; //Instrument num_ue and response_time every 10 sec
//vector<vector<int>> traffic_shape={{2,1},{3,3}}; //States for the first two minutes mix_num=1 & for next 3 minutes mix_num=3
/// DYNAMIC LOAD GENERATOR ///
// 1=> 1:99
int mix_num = 9; //9;	//choose the traffix mix from above traffic_options -> {0,1,2}  // 11 means only attach request will be sent
float a_prob = 0;
float s_prob = 0;
//0%  att/serv == att=0.01,serv=0.99 ==>0.7%
//25% att/serv == att=0.25,serv=0.75 ==>24.6%
//50% att/serv == att=0.5,serv=0.5
//75% att/serv == att=0.75,serv=0.25 ==>75%
//100% att/serv == att=1,serv=0

//bool serviceRequestLoopFlag = true; //set this true only for service requests, for long service-req traffic only
//int fracServ = 60; //fraction of time for Service requests before next attach
//int servno = 100;

//TRAFFIC MIX 1: attach-wait-servicereq-wait-detach..repeat
//TRAFFIC MIX 2: attach-wait-servreq-wait-servreq-wait..repeat-detach..repeat
//Only registration: setUpTunnel, doDetach== true, doEncryption,checkIntegrity could be anything
//Service request: s1_release=true, ueServiceRequest OR networkServiceRequest =true
//Data traffic: setUpTunnel, doDetach, sendData, assignIpToInterface =true, s1_release AND ueServiceRequest AND networkServiceRequest==false


struct _threadArgs {
	int threadId;
	int serverPort;
	int port_gap;
	int starting_ue_id;
	int ue_id_gap;		// Number of ids of UE initially allocated to each thread
	int num_threads;
        //long delay[1000][10000]; //For storing index ofserviceRequestLoopFlag UE delays
        //int j; //secondary index for delay matrix
};

struct _ipArgs {
	string startingIp;
 	// char *startingIp;
	long numIps;
};

// To store the statistics for the simulation
float tpt[NO_EPOCH] = {0};
float lat[NO_EPOCH] = {0};
unsigned long long num_ue_per_epoch[NO_EPOCH] = {0};
unsigned long long ue_response_time_per_epoch[NO_EPOCH] = {0};
double num_ue_inst[INST_ARR_LEN] = {0};  // Enough to store 50 min data if captured after every 10 sec
double resp_time_inst[INST_ARR_LEN] = {0};  // Enough to store 50 min data if captured after every 10 sec
int instIndex = 0; // Index to remember number of entries in instr arrays
unsigned long long prev_tpt = 0; //To remember tpt till previous period
unsigned long long prev_lat = 0; //To remember lat till previous period
vector<unsigned long long> num_ue_per_thread;
vector<unsigned long long> ue_registration_response_time;
vector<unsigned long long> sr_registration_response_time;
vector<unsigned long long> stored_ue_registration_response_time;//For delay distribution
//long delay[1000][10000]; //For storing index of UE delays

//struct timeval start[500];

string rate;		// Rate at which each UE sends data
time_t endTime;		// Simulation end time
time_t mix_endTime; //End time of current traffic mix
time_t inst_endTime; //End time of instrumenting current period (10sec)
//time_t servReqTime; //Service Request time for traffic mix containing multiple service requests
int cnt = 0;
int attNo, detNo, sreqNo = 0;//Counts number of requests served
float traffic_percent=0.0; // For Attach%:ServiceReq%, "traffic_percent" provides attach%
//int servTime; //Delta service time, to increment curTime, used for long serv-req traffic
int j = 0; //For storing index of UE delays
//int tID=0; //Thread ID
vector<int> distr_check(6,0);
// Thread function for each simulated UE

void error(const char *msg){
  perror(msg);
  
}

int read_stream(int conn_fd, uint8_t *buf, int len) {
	int ptr;
	int retval;
	int read_bytes;
	int remaining_bytes;

	ptr = 0;
	remaining_bytes = len;
	if (conn_fd < 0 || len <= 0) {
		return -1;
	}
	while (1) {
		read_bytes = read(conn_fd, buf + ptr, remaining_bytes);
		if (read_bytes <= 0) {
			retval = read_bytes;
			break;
		}
		ptr += read_bytes;
		remaining_bytes -= read_bytes;
		if (remaining_bytes == 0) {
			retval = len;
			break;
		}
	}
	return retval;
}

int send_socket_data(const char *ip)
{
    int portno,nbytes;
    struct sockaddr_in server_addr;
    struct hostent *server;
    portno = atoi("13001");
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
      perror("Error opening socket");
    }
    else
    //   printf("\n");

    server = gethostbyname("192.168.4.5");
    if(server == NULL){
      fprintf(stderr, "ERROR no such host\n" );
      exit(0);
    }
    bzero((char *)&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr,server->h_length);
    server_addr.sin_port = htons(portno);

    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = inet_addr(ip);
    localaddr.sin_port = 0;  // Any local port will do
    if(bind(sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr))==0){
        // printf("Binded Correctly\n"); 
    }
    else{
         
        printf("Unable to bind\n"); 
    }

    if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
    //   perror("ERROR connecting");
	  cout<<"error connecting";
    	close(sockfd);

	  return 0;

    }
	
    char buff[BUFFER_SIZE];
    memset(buff,0,BUFFER_SIZE);

    sprintf(buff,"%s","tffXE5CT0fn8qnN9QwEDStJhNTU0TtqtiSk9JYJRDWGPp2ETwHXSNmkaT5jnBRptoPx0xvtDdWPa9lsoWDWVtu3UJIkYYTY6qnfLdzp9mSkSe7R1wsjoldi8YKulcFn1lh3bh4SERWNsUlIshNZPE281SIBC3dmcMS7cu0ajnZM5GCF0oONCsJjQmkZ7xUNZkUeCsGQMiqXe0BM8wlE019fP8hXkAmMwmeLKYkPtVLhKIDLI4lH4QxZQDXNKEB9Q2a9rvdv14bZTzG5PKAZ8z46wr7g9Vp60GwFXiJcBJxOhFbRcvCYUadVGoBabk4fo4gdWrNQAEAYIxm6S7J0dXlCZHud0fyGzzzkrQ0TuNgDFxxEQoWKtiL7KEJPQeeV8Ege2fbM4UC9p4Ks1rJsigIsV2vAcYKGTHlfBcRNXLDk5homW1RQJcB7NXGvV5Efjf5XJ4hyf5kYJWfs5UgW6iGmhDDBfr9jGFXWAB5xSo7BptH4s4DIZbjQ8f79irZrK291dM58zWQfJPD8AIyjWbvn73tYRnUhyn3UPIno7tTqVkkCxC4nBZ44GY7Lg3zIvcbKvetTdofCB3EfVWdbyIMSIGRjxvwdLHgieZY7DZyX3ZJHjpQ3pbyE1boGp7dKQGgA86lgMaKbzUqgNv9OpGaIVusVGOgYy9v29USGv5rO504dOTlH8RPjWuHMKBUiNGXbNLGMHCQGvV6LOreSBEUFpZOOuCIqPxEGZzCqQBQ7ZwLxfT7khfWjE9GvXYK4KSo59yLGeq4D1CTDoe7IJQj9kiL3Jnjfis0zaI3i13wMfmuZMXCanW6FQzTp9RmInV8LzGoX7rSdsdilsVwO8aI3DT62qztvCzV64swaYy1AjSAz70RMNs9sMoSKnqEV3ACi8nUAenQn1txmBWz6h4yYZiZ4hs3TArykHvwVAEt2VXpeJH47I2owZxHBmT4g9aCRtWslY9jjP7oOJDEUvwiyY9mKj4mTDs5RuxUrNbN2xc1UEtJgw03qNeRvqdUsq"); 
    //cout<<"buufer is"<<buff<<endl;

    int n = send(sockfd,buff,sizeof(buff),0);
    if (n < 0) error("ERROR writing to socket");
    memset(buff,0,BUFFER_SIZE);

 	int retval = read_stream(sockfd,(uint8_t *)buff, 8);
	 if (retval == 0) {
				cout<<"zero bytes read"<<endl;
	 }
    // if ((nbytes = recv(sockfd, buff, sizeof buff, 0)) <= 0)
    //     {                
    //         if (nbytes == 0) {
    //         	printf("connection %d closed\n", socket);
    //             close(sockfd);
    //             pthread_exit(NULL);
	// 		}
    //         else {
    //             perror("recv");
    //         }
    //     }
    // cout << "buffer received in client = " << buff <<endl;
    close(sockfd);
}

void* multithreading_func(void *arg){
	bool setUpTunnel_t = false;
	bool doDetach_t = false;
	bool sendData_t = false;			//keep either doDetach, or s1_release true for sending data
	bool assignIpToInterface_t = false; //For data traffic only
	bool s1_release_t = false;		// UE initiated S1 Release
	bool doEncryption_t = false;
	bool checkIntegrity_t = false;
	bool ueServiceRequest_t = false;	// UE initiated service request (uplink traffic)
	bool networkServiceRequest_t = false;	// Network initiated service request (downlink traffic)
	struct _threadArgs *args = (struct _threadArgs *)arg;
	int threadId = args->threadId;
	int startingPort = args->serverPort;
	int ue_num = args->starting_ue_id;
	int port_gap =  args->port_gap;
	int gap = args->ue_id_gap;
	int maxThreads = args->num_threads;
	//int j = args->j;
	//long delay[1000][10000] = args->delay;
	time_t curTime;
	time(&curTime);
	int currentPort = startingPort;
	int endPort = startingPort + port_gap;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	//struct timeval start, end;
	//struct timeval start, start1, start2, start3, end, end1, end2, end3;
	//struct timeval end, end1, end2, end3;
	//long useconds, seconds;
	long mtime;
	size_t idleSleepTime, serviceRequestSleepTime;

	// Client user(threadId+1), sink_user(threadId+1);
	Client user(threadId+start_ue), sink_user(threadId+start_ue);
	vector<string> tmpArray;
	vector<string> service_response;
	bool att_done=false;
	int loop1,loop2;
	int dataTime;
	UserEquipment ue_end(10000);
	Client user_end(10000);
	while(curTime < endTime){
		int traffic_type = get_mix(traffic_mix[mix_num]); 	//weighted random selection for the traffic type for particular ue
		distr_check[traffic_type]++;
		if(DO_DEBUG){
			cout<<"\n selected traffic type = "<<traffic_type<<endl;
		}
		switch(traffic_type){

			/* attach-detach only, */
			case 0: setUpTunnel_t = true;
					doDetach_t = true;
					sendData_t = false;
					assignIpToInterface_t = false;
					s1_release_t = false;
					doEncryption_t = false;
					checkIntegrity_t = false;
					ueServiceRequest_t = false;
					loop1 = 100;
					loop2 = 0;
					break;

			/* context-rel/service-req, only*/ 
			case 1: setUpTunnel_t = true;
					doDetach_t = true;
					sendData_t = false;
					assignIpToInterface_t = false;
					s1_release_t = true;
					doEncryption_t = false;
					checkIntegrity_t = false;
					ueServiceRequest_t = true;
					loop1 = 1;
					loop2 = 100;
					break;

			/*att-data_all_the_time-det, */
			case 2: setUpTunnel_t = true;			//long data
					doDetach_t = true;
					sendData_t = true;
					assignIpToInterface_t = true;
					s1_release_t = false;
					doEncryption_t = false;
					checkIntegrity_t = false;
					ueServiceRequest_t = false;
					dataTime = 60;	//seconds
					loop1 = 1;
					loop2 = 1;
					break;

			/* att-data(default=1s)-det-loop, */ 
			case 3: setUpTunnel_t = true;
					doDetach_t = true;
					sendData_t = true;
					assignIpToInterface_t = true;
					s1_release_t = false;
					doEncryption_t = false;
					checkIntegrity_t = false;
					ueServiceRequest_t = false;
					dataTime = 1;				//short data
					//loop1 = 1;    // sttach loop
					//loop2 = 1;    // sttach loop
					loop1 = 100;   // data loop
					loop2 = 0;   // data loop
					break;

			/* att-serv_req-data-loop2-det-loop1, */ 
			case 4: setUpTunnel_t = true;
					doDetach_t = true;
					sendData_t = true;
					assignIpToInterface_t = true;
					s1_release_t = true;
					doEncryption_t = false;
					checkIntegrity_t = false;
					ueServiceRequest_t = true;
					dataTime = 1;
					loop1 = 1;    //outer loop---attach
					loop2 = 99;   //inner loop---service-req
					break;

			/* att-serv-req-data-loop2-det*/
			case 5: setUpTunnel_t = true;
					doDetach_t = true;
					sendData_t = true;
					assignIpToInterface_t = true;
					s1_release_t = true;
					doEncryption_t = false;
					checkIntegrity_t = false;
					ueServiceRequest_t = true;
					dataTime = 1;
					// max time is service request only 
					//loop1 = 1;  //outer loop---attach
					//loop2 = 100;   //inner loop---service-req
					loop1 = 1; //1;  //outer loop---attach
					loop2 = 99; //100;   //inner loop---service-req
					break;
		}
		do {
			// UserEquipment ue(threadId+1);
			UserEquipment ue(threadId+start_ue);
			//user.input_server_details(g_mme_port, g_mme_address);
			if(DO_DEBUG){
				cout<<"Attaching with MME"<<endl;
			}
			//gettimeofday(&ue.start, NULL);
			//gettimeofday(&start, NULL);
			//usleep(my_rand()+2000);
			// usleep(200000);
			usleep(my_rand()+wait_latency);
			mtime=0;
			if(attach_with_mme(ue, user, checkIntegrity_t, mtime)){ 	// Authentication
				//if(setUpTunnel_t || serviceRequestLoopFlag){
					// Setup tunnel
				if(setUpTunnel_t) {
						//att=1;
						/*if(attNo>6)
							setUpTunnel_t=false;*/
					//att_done=true
					// lat_mtx.lock();
					// attNo++;
					// lat_mtx.unlock();
					//usleep(my_rand()+200);
					//gettimeofday(&ue.start1, NULL);
					//gettimeofday(&start1, NULL);
					tmpArray = setup_tunnel(ue, user, doEncryption_t, mtime);
					//cout<<"IP Address of UE="<<tmpArray[1]<<" and SGW TEID="<<tmpArray[2]<<endl;
					// string UE_IP = tmpArray[1];
					//lat_mtx.lock();
					//attNo++;
					//num_ue_per_thread[threadId] += 1; //Increment completion num for att req
					//lat_mtx.unlock();
					//////PRINT REG TIME TO ARRAY////
					/*gettimeofday(&end1, NULL);
					seconds  = end1.tv_sec  - ue.start1.tv_sec;
					useconds = end1.tv_usec - ue.start1.tv_usec;
					//seconds  = end1.tv_sec  - start1.tv_sec;
                                        //useconds = end1.tv_usec - start1.tv_usec;
					mtime = ((seconds) * 1000000 + useconds);*/
					//lat_mtx.lock();
					ue_registration_response_time[threadId] += mtime;
					//lat_mtx.unlock();
					//cout<<"a:"<<mtime<<endl;
					lat_mtx.lock();
                        attNo++;
                    lat_mtx.unlock();
					num_ue_per_thread[threadId] += 1; //Increment completion num for att req

					/*stored_ue_registration_response_time[j] = mtime;
					j = j + 1;*/
						////////////////////////////////////
					sleep(9);
				}
					//tmpArray: [0] = SEND_IP_SGW_TEID, [1] = IP Address of UE, [2] = SGW TEID, [3] = ue_teid, [4] = GUTI

				// usleep(200000);
				if(tmpArray.size()>=5){
					do{
						if(sendData_t){
								// Send data
							if(DO_DEBUG){
								cout<<"traffic_type = "<<traffic_type<<" DATA TIME = "<<dataTime<<endl;

							}
							/*if(ue_num == 100){
								sleep(1000);
							}*/
							//usleep(20000);
							//sleep(500);
							//cout<<"IP address of UE = "<<tmpArray[1].c_str()<<endl;
							//send_socket_data(tmpArray[1].c_str());
							//currentPort = send_ue_data(ue, ue_num, rate, currentPort, startingPort, endPort, user, tmpArray, dataTime);
							// usleep(100000);
						}
						if(s1_release_t){
							//cout<<"SLEEPING BEFORE s1 release"<<endl;
							//usleep(my_rand()+2000);		//200-700 usec
							usleep(my_rand()+wait_latency);
							//sreqNo++;
							//gettimeofday(&ue.start2, NULL);
							//gettimeofday(&start2, NULL);
							mtime=0;
							ue_context_release(ue, user, ue_num, tmpArray[1], tmpArray[2], tmpArray[3], currentPort, networkServiceRequest, mtime);
							//lat_mtx.lock();
							//num_ue_per_thread[threadId] += 1;//Increment completion num for serv req
							//sreqNo++;
							//lat_mtx.unlock();
							/*gettimeofday(&end2, NULL);
							seconds  = end2.tv_sec  - ue.start2.tv_sec;
							useconds = end2.tv_usec - ue.start2.tv_usec;
							//seconds  = end2.tv_sec  - start2.tv_sec;
                                                        //useconds = end2.tv_usec - start2.tv_usec;
							mtime = ((seconds) * 1000000 + useconds);*/
							//lat_mtx.lock();
							ue_registration_response_time[threadId] += mtime;
							sr_registration_response_time[threadId] += mtime;
							//lat_mtx.unlock();
							//cout<<"c:"<<mtime<<endl;	
                            num_ue_per_thread[threadId] += 1;//Increment completion num for serv req
                            lat_mtx.lock();
							sreqNo++;
                            lat_mtx.unlock();

							if(DO_DEBUG){
								cout<<"UE CONTEXT RELEASE DONE with UE NUM="<<ue_num<<endl;
							}

							if(ueServiceRequest_t){

									/*do{
										serviceRequestSleepTime = (size_t) dist_service_request_time(generator);
									}while(serviceRequestSleepTime == 0);*/
								//usleep(5000);
									//sleep(serviceRequestSleepTime);

									// tmpArray[1] = UE IP   tmpArray[2]= SGW TEID  tmpArray[4]=GUTI
								if(DO_DEBUG){
									cout<<"UE SERVICE REQUEST INITIATED with UE NUM="<<ue_num<<" after "<<serviceRequestSleepTime<<" seconds"<<endl;
								}
								num_ue_per_thread[threadId] += 1;//Increment completion num for serv req
								lat_mtx.lock();
								sreqNo++;
								lat_mtx.unlock();
								//cout<<"SLEEPING BEFORE service request"<<endl;
								//usleep(my_rand());
								//usleep(my_rand()+2000);
								usleep(my_rand()+wait_latency);
								//usleep(my_rand()+2000);
								//gettimeofday(&ue.start2, NULL);
								//gettimeofday(&start2, NULL);
								mtime=0;
								tmpArray[3] = ue_service_request(ue, user, ue_num, tmpArray[1], mtime); //returns newly generated ue_teid
									//////PRINT REG TIME TO ARRAY////
								/*gettimeofday(&end2, NULL);
								seconds  = end2.tv_sec  - ue.start2.tv_sec;
								useconds = end2.tv_usec - ue.start2.tv_usec;
								//seconds  = end2.tv_sec  - start2.tv_sec;
                                                                //useconds = end2.tv_usec - start2.tv_usec;
								mtime = ((seconds) * 1000000 + useconds);*/
								//lat_mtx.lock();
								ue_registration_response_time[threadId] += mtime;
								sr_registration_response_time[threadId] += mtime;
								//lat_mtx.unlock();

								//cout<<"s:"<<mtime<<endl;
								/*stored_ue_registration_response_time[j] = mtime;
								j = j + 1;*/
								////////////////////////////////////
								if(DO_DEBUG){
									cout<<"UE SERVICE REQUEST DONE with UE NUM="<<ue_num<<endl;
								}
							} else if(networkServiceRequest){
								tmpArray[3] = network_service_request(ue, user, ue_num, tmpArray[1]); //returns newly generated ue_teid
								if(DO_DEBUG){
									cout<<"NETWORK SERVICE REQUEST DONE with UE NUM="<<ue_num<<endl;
								}
							}
							// if(sendData_t){
							// 	// Send data
							// if(DO_DEBUG){
							// 	cout<<"traffic_type = "<<traffic_type<<" DATA TIME = "<<dataTime<<endl;

							// }
							// currentPort = send_ue_data(ue, ue_num, rate, currentPort, startingPort, endPort, user, tmpArray, dataTime);
							// // usleep(100000);
							// }

						} //endif s1 release
						if(sendData_t){
							currentPort++;
							if(currentPort >= endPort){
								currentPort = startingPort;
							}
						}
						//cout<<"IN LOOP 2"<<endl;
						loop2--;
					}while(loop2>0);
					// sleep(300); // sleep after sending data
					if(doDetach_t){
						// Initiate detach
						//cout<<"SLEEPING BEFORE detach"<<endl;
						//usleep(my_rand()+200);			//sleep for 200-700 usec
						if(!s1_release_t && !sendData_t)
							usleep(my_rand()+wait_latency);
						att_done=false;
						usleep(my_rand()+wait_latency);
						//gettimeofday(&ue.start3, NULL);
						//gettimeofday(&start3, NULL);
						mtime=0;
						detach_ue(ue, user, ue_num, tmpArray[1], tmpArray[2], tmpArray[3], mtime);
						// sleep(300);

						//gettimeofday(&end3, NULL);
						lat_mtx.lock();
						detNo++;
						lat_mtx.unlock();
                                                num_ue_per_thread[threadId] += 1;//Increment completion num for delreq

						//////PRINT REG TIME TO ARRAY////
						/*seconds  = end3.tv_sec  - ue.start3.tv_sec;
						useconds = end3.tv_usec - ue.start3.tv_usec;
						//seconds  = end3.tv_sec  - start3.tv_sec;
                                                //useconds = end3.tv_usec - start3.tv_usec;
						mtime = ((seconds) * 1000000 + useconds);*/
						//lat_mtx.lock();
						ue_registration_response_time[threadId] += mtime;
						//lat_mtx.unlock();
						/*stored_ue_registration_response_time[j] = mtime;
						j = j + 1;*/
						////////////////////////////////////
						//cout<<"SLEEPING AFTER detach"<<endl;
						//usleep(my_rand()+200);
					}

				}//endif tmpArray.size()>=5

			}//end if attach_with_mme
			else{
				cout<<"Authentication Error"<<endl;
				//exit(1);
			} //endif else attach_with_mme
		/*	gettimeofday(&end, NULL);
			seconds  = end.tv_sec  - start.tv_sec;
			useconds = end.tv_usec - start.tv_usec;
			mtime = ((seconds) * 1000000 + useconds);
			ue_registration_response_time[threadId] += mtime;
			//if (WANT_DELAY_CDF){
			stored_ue_registration_response_time[j] = mtime;
			//delay[threadId][j] = mtime;
			j = j + 1;*/
			//}*/
			time(&curTime);
			loop1--;

			if(dynLoad){
				traffic_mtx.lock();
				if(curTime >= mix_endTime) {
					//cout<<"start time="<<curTime<<endl;
					lat_mtx.lock();
					//num_ue_per_epoch[curr_mix_index] = attNo + detNo + sreqNo;
					for(int i=0; i<maxThreads; i++){
						num_ue_per_epoch[curr_mix_index] = num_ue_per_epoch[curr_mix_index] + num_ue_per_thread[i];
						ue_response_time_per_epoch[curr_mix_index] = ue_response_time_per_epoch[curr_mix_index] + ue_registration_response_time[i];
					}
					lat_mtx.unlock();
					//cout<<"Total Num previous epoch is "<<num_ue_per_epoch[curr_mix_index]<<endl;
					if ( curr_mix_index > 0){
						int i = curr_mix_index;
						while (i > 0) {
							num_ue_per_epoch[curr_mix_index] = num_ue_per_epoch[curr_mix_index] - num_ue_per_epoch[i-1];
							ue_response_time_per_epoch[curr_mix_index] =  ue_response_time_per_epoch[curr_mix_index] - ue_response_time_per_epoch[i-1];
							i--;
						}
					}
					float tmp_tpt = (num_ue_per_epoch[curr_mix_index]*1.0)/(traffic_shape[curr_mix_index][0] * 60);
					float tmp_lat = (ue_response_time_per_epoch[curr_mix_index]*0.001)/num_ue_per_epoch[curr_mix_index];
					cout<<"Throughput= "<<tmp_tpt<<endl;
					cout<<"Latency(ms)= "<<tmp_lat<<endl;
					tpt[curr_mix_index] = tmp_tpt;
					lat[curr_mix_index] = tmp_lat;
//					cout<<"Num this epoch is "<<(num_ue_per_epoch[curr_mix_index]*1.0)/(traffic_shape[curr_mix_index][0] * 60.0)<<endl;
//					cout<<"Delay this epoch is "<< (ue_response_time_per_epoch[curr_mix_index]*1.0)/num_ue_per_epoch[curr_mix_index] <<endl;

					if(curr_mix_index < traffic_shape_size){
						curr_mix_index++;
					}
					mix_num = traffic_shape[curr_mix_index][1];
					int tmp1 = traffic_shape[curr_mix_index][0] * 60;
					mix_endTime = curTime + (int) tmp1;
					//cout<<"mix end time="<<mix_endTime<<endl;
					cout<<"mix="<<mix_num<<endl;
					//usleep(500000);
					//sleep(1);
				}
				traffic_mtx.unlock();
			}
//////  INSTRUMENTATION CODE STARTS HERE /////////////////////////////////////////////////////////

			if(instrumentTptLat){
				inst_mtx.lock();
				time(&curTime);
				if(curTime >= inst_endTime) {
					//cout<<"start time="<<curTime<<endl;
					lat_mtx.lock();
					//num_ue_inst[instIndex] = attNo + detNo + sreqNo;
					for(int i=0; i<maxThreads; i++){
						num_ue_inst[instIndex] =  num_ue_inst[instIndex] + num_ue_per_thread[i];
						resp_time_inst[instIndex] = resp_time_inst[instIndex] + ue_registration_response_time[i];
					}
					lat_mtx.unlock();
					//cout<<"Total Num previous epoch is "<<num_ue_per_epoch[curr_mix_index]<<endl;
					/*if ( instIndex > 0){
						int i = instIndex;
						while (i > 0) {
							num_ue_inst[instIndex] = num_ue_inst[instIndex] - num_ue_inst[i-1];
							resp_time_inst[instIndex] =  resp_time_inst[instIndex] - resp_time_inst[i-1];
							i--;
						}
					}*/
					float prev_t = num_ue_inst[instIndex];
					float prev_l = resp_time_inst[instIndex];
					num_ue_inst[instIndex] = num_ue_inst[instIndex] - prev_tpt; //Get current period val
					resp_time_inst[instIndex] = resp_time_inst[instIndex] - prev_lat;
					resp_time_inst[instIndex] = (resp_time_inst[instIndex]*0.001)/num_ue_inst[instIndex]; //Keep it bfor num_ue_inst update coz we need total number and not throughtput
					num_ue_inst[instIndex] = (num_ue_inst[instIndex]*1.0)/INST_PERIOD;
					prev_tpt = prev_t;
					prev_lat = prev_l;
					//cout<<"Throughput= "<<num_ue_inst[instIndex]<<endl;
					//cout<<"Latency(ms)= "<<resp_time_inst[instIndex]<<endl;

					instIndex++;

					inst_endTime = curTime + (int) INST_PERIOD;
					//cout<<"mix end time="<<mix_endTime<<endl;
					//sleep(1);
				}
				inst_mtx.unlock();
			}


//////  INSTRUMENTATION CODE ENDS HERE /////////////////////////////////////////////////////////

		}while(curTime < endTime && loop1>0);
	} //end while

        //apu_exit(ue_end, user_end);
	free(args);
	pthread_exit(NULL);
}

bool apu_exit(UserEquipment &ue, Client &user){
	return ue.apu_exit(user);
}

bool attach_with_mme(UserEquipment &ue, Client &user, bool checkIntegrity, long& mtime){
	return ue.authenticate(user, checkIntegrity, mtime);
}

string get_starting_IP_Address(UserEquipment &ue, Client &user){
	return ue.getStartingIPAddress(user);
}

vector<string> setup_tunnel(UserEquipment &ue, Client &user, bool doEncryption, long& mtime){
	return ue.setupTunnel(user, doEncryption, mtime);
}

int send_ue_data(UserEquipment &ue, int ue_num, string rate, int serverPort, int startingPort, int endPort, Client &user, vector<string>& tmpArray, int dataTime){
	return ue.sendUserData(user, ue_num, rate, serverPort, startingPort, endPort, tmpArray, dataTime);
}

void ue_context_release(UserEquipment &ue, Client &user, int ue_num, string ue_ip, string sgw_teid, string ue_teid, int currentPort, bool networkServiceRequest, long &mtime){
	ue.initiate_ue_context_release(user, ue_num, ue_ip, sgw_teid, ue_teid, currentPort, networkServiceRequest, mtime);
}

string ue_service_request(UserEquipment &ue, Client &user, int ue_num, string ue_ip, long& mtime){
	return ue.send_ue_service_request(user, ue_num, ue_ip, mtime);
}

string network_service_request(UserEquipment &ue, Client &user, int ue_num, string ue_ip){
	return ue.receive_paging_request(user, ue_num, ue_ip);
}

void detach_ue(UserEquipment &ue, Client &user, int ue_num, string ue_ip, string sgw_teid, string ue_teid, long& mtime){
	ue.initiate_detach(user, ue_num, ue_ip, sgw_teid, ue_teid, mtime);
}

// Generate UE IP addresses and assign to the network interface
void* multithreading_add_ip(void *arg){
	cout<<"inside multithreading_add_ip"<<endl;
	string c = "";
	struct _ipArgs *args = (struct _ipArgs *)arg;
	string ip = args->startingIp;
	long numIp = args->numIps;
	system(("sudo chmod +x ipgen.sh"+c+"").c_str());
	string s = "bash ./ipgen.sh "+ip+" "+SINK_SERVER_NETMASK+" "+ to_string(numIp) +" "+DEFAULT_IF;
	if(DO_DEBUG){
		cout<<"Generating IPs: "<<s<<endl;
	}
	system(s.c_str());
}

int main(int argc, char *args[]){
	long maxThreads = 0;
	int status;
	stringstream ss;
	string data = "";
	std::ofstream outfile;
	std::ofstream delayfile;
	std::ofstream instfile;

	if(argc != 4 && argc != 5){
		fprintf(stderr,"Usage: %s <max-threads> <program-run-time(in mins)> <rate[e.g. 20M (i.e. 20 Mbits/sec)  or 20K (i.e. 20 Kbits/sec)]> [<SINK_SERVER_STARTING_PORT (default:13001)>]\n", args[0]);
		exit(0);
	}

	maxThreads = atoi(args[1]);
	if(maxThreads <= 0){
		printf("Number of threads should be greater than 0\n");
		exit(0);
	}
	double tmp;
	ss << args[2];
	ss >> tmp;
	if(tmp <= 0.0){
		printf("Run time of each threads should be greater than 0.0\n");
		exit(0);
	}

	rate = args[3];
	if(rate.size() <= 1){
		printf("Rate should be of format XM or XK e.g. 20M (i.e. 20 Mbits/sec)  or 20K (i.e. 20 Kbits/sec)\n");
		exit(0);
	}

	if(argc == 5){
		int tmp_port = atoi(args[4]);
		if (tmp_port >= 65536 || tmp_port <= 1023){
			printf("Server port number should lie in [1024, 65535] only \n");
			exit(0);
		}
		SINK_SERVER_STARTING_PORT = tmp_port;
	}

	string c = "";
	system(("ifconfig"+c+" "+DEFAULT_IF+" mtu "+to_string(LINK_MTU)).c_str());

	for(int i=1; i<4096; i++){
		reusable_ue_teid.push(i);
	}

	if(sendData || networkServiceRequest){
		// Get the starting UE IP address from controller
		// UserEquipment ue(1);
		UserEquipment ue(start_ue);
		Client user(2001);
		// Client user(1);
		//user.input_server_details(g_mme_port, g_mme_address);
		string startingIp1 = get_starting_IP_Address(ue, user);

		if(assignIpToInterface){
			// Generate and assign UE IP addresses in advance
			cout<<"Allocating IPs. Please wait..."<<endl;
			time_t start;
			time(&start);
			pthread_t ipAddThread;
			struct _ipArgs *argss =   (struct _ipArgs *)malloc(sizeof(struct _ipArgs));
			memset(argss, 0, sizeof(struct _ipArgs));
			argss->startingIp = startingIp1;
			argss->numIps = 2 * maxThreads + 10;
			status = pthread_create(&ipAddThread,NULL, multithreading_add_ip, argss);
			report_error(status);
			pthread_join(ipAddThread, NULL);
			time_t end;
			time(&end);
			cout<<"time="<<(end-start)<<"sec"<<endl;
			sleep(5);
			if(DO_DEBUG){
				cout<<"Starting IP="<<startingIp1<<endl;
			}
		}
	}

	num_ue_per_thread.resize(maxThreads, 0);
	ue_registration_response_time.resize(maxThreads, 0);
	sr_registration_response_time.resize(maxThreads, 0);
        //int ue_per_thr = 50000;
	stored_ue_registration_response_time.resize(UE_PER_THREAD, 0);

	cout<<"***************STARTING NOW***************"<<endl;
	tmp = tmp * 60;
	time_t curTime;
	time(&curTime);
	if(DO_DEBUG){
		cout<<"start time="<<curTime<<endl;
	}

	///////// DYNAMIC LOAD GEN in MAIN STARTS ///////////////
	if (dynLoad){
		cout<<"start time="<<curTime<<endl;
		int tmp1 = traffic_shape[curr_mix_index][0] * 60;
		mix_endTime = curTime + (int) tmp1;
		mix_num = traffic_shape[curr_mix_index][1];
		/*if(curr_mix_index < traffic_shape_size){
			curr_mix_index++;
		}*/
		cout<<"mix end time="<<mix_endTime<<endl;
		cout<<"mix="<<mix_num<<endl;
	}
	///////// DYNAMIC LOAD GEN in MAIN ENDS ///////////////

	///// INSTRUMENTATION CODE STARTS /////////

	if (instrumentTptLat){
		cout<<"start time="<<curTime<<endl;
		int tmp2 = INST_PERIOD;
		inst_endTime = curTime + (int) tmp2;
		//cout<<"instrumentation end time="<<inst_endTime<<endl;
	}
	///// INSTRUMENTATION CODE ENDS /////////

	endTime = curTime + (int) tmp;
	if(DO_DEBUG){
		cout<<"end time="<<endTime<<endl;
	}
	int simulationTime = (int) tmp;


	//servTime = (int) (tmp/fracServ);
        //servReqTime = curTime + (int) servTime;

	pthread_t tid[maxThreads];
	int gap = 1;
	int port_gap = PER_THREAD_PORT_WINDOW;
	int total_non_global_ports = maxThreads * port_gap;
	int global_starting_port = SINK_SERVER_STARTING_PORT + total_non_global_ports;
	// Filling global ports
	for(int i = 0; i < NUM_GLOBAL_PORTS; i++){
		global_ports[i] = global_starting_port + i;
	}

	// Create UE threads
	for(int i = 0;i<maxThreads;i++){
		struct _threadArgs * args = (struct _threadArgs *)malloc(sizeof(struct _threadArgs));
		args->threadId = i;
		args->serverPort = SINK_SERVER_STARTING_PORT + i * port_gap;
		args->port_gap = port_gap;
		args->starting_ue_id = start_ue + i * gap;
		args->ue_id_gap = gap;
		args->num_threads = maxThreads;

		status = pthread_create(&tid[i], NULL, multithreading_func, args);
		report_error(status);
	}

	string s = "";
	int total_ue = 0;
	unsigned long long total_reistration_time = 0;
	double average_registration_time = 0.0;
	unsigned long long total_sr_reistration_time = 0;
        double average_sr_registration_time = 0.0;
	double registrationThroughput = 0.0;

	// Sleep for the specified simulation time
	usleep(simulationTime * 1000000); // 1sec

	/* Wake up and cancel/join all the UE threads to end simulation */
	for(int i=0;i<maxThreads;i++){
		if(DO_DEBUG){
			cout<<"******* ENDING THREAD - "<<i<<endl;
		}
		pthread_cancel(tid[i]);
		pthread_join(tid[i],NULL);
	}
	if(DO_DEBUG){
		cout<<"************ENDED!!!************"<<endl;
	}
	/* Calculations for last epoch */
	if (dynLoad == true){
		//num_ue_per_epoch[curr_mix_index] = attNo + detNo + sreqNo;
		for(int i=0; i<maxThreads; i++){
						num_ue_per_epoch[curr_mix_index] = num_ue_per_epoch[curr_mix_index] + num_ue_per_thread[i];
						ue_response_time_per_epoch[curr_mix_index] = ue_response_time_per_epoch[curr_mix_index] + ue_registration_response_time[i];
					}
		//cout<<"Total Num previous epoch is "<<num_ue_per_epoch[curr_mix_index]<<endl;
		if ( curr_mix_index > 0){
			int i = curr_mix_index;
			while (i > 0) {
				num_ue_per_epoch[curr_mix_index] = num_ue_per_epoch[curr_mix_index] - num_ue_per_epoch[i-1];
				ue_response_time_per_epoch[curr_mix_index] = ue_response_time_per_epoch[curr_mix_index] - ue_response_time_per_epoch[i-1];
				i--;
			}
		}
		float tmp_tpt = (num_ue_per_epoch[curr_mix_index]*1.0)/(traffic_shape[curr_mix_index-1][0] * 60);
		float tmp_lat = (ue_response_time_per_epoch[curr_mix_index]*0.001)/num_ue_per_epoch[curr_mix_index];
		cout<<"Throughput= "<<tmp_tpt<<endl;
		cout<<"Latency(ms)= "<<tmp_lat<<endl;
		tpt[curr_mix_index] = tmp_tpt;
		lat[curr_mix_index] = tmp_lat;
	}


	/////////////////////////////////

	/* Calculate and display various metrics */
	time_t actual_endTime;
	time(&actual_endTime);
	for(int i=0;i<maxThreads;i++){
		total_ue += num_ue_per_thread[i];
		total_reistration_time += ue_registration_response_time[i];
		total_sr_reistration_time += sr_registration_response_time[i];
		cout<<"num_ue_per_thread["<<i<<"] "<<num_ue_per_thread[i]<<endl;
		cout<<"ue_registration_response_time["<<i<<"] "<<((ue_registration_response_time[i]*1.0)/num_ue_per_thread[i])<<" us"<<endl;
	}
	average_sr_registration_time = (total_sr_reistration_time*1.0)/(sreqNo*1.0);
	average_registration_time = (total_reistration_time*1.0)/(total_ue*1.0);
	registrationThroughput = (total_ue*1.0)/(actual_endTime - curTime);

	cout<<"***************************************STATISTICS***************************************"<<endl;
	execution_done = true;
	double averageUEperThread = ((total_ue*1.0)/maxThreads);
	averageUEperThread = roundf(averageUEperThread * 100) / 100;
	ostringstream strs;
	strs << averageUEperThread;
	string avUE = strs.str();
	printf("Total Number of Threads=%d\n", maxThreads);
	printf("Total Number of UE=%d\n", total_ue);
	cout<<"Average Number of UE per Thread="<<averageUEperThread<<endl;
	printf("Total Execution Time=%d sec\n", (actual_endTime - curTime));

	average_registration_time = average_registration_time/1000000.0;
	cout<<"Latency = "<<average_registration_time<<" secs"<<endl;
	cout<<"Service Request Latency = "<<average_sr_registration_time<<" secs"<<endl;
	cout<<"Registration Throughput="<<registrationThroughput<<" registrations/sec"<<endl;
	cout<<"Attach-Request= "<<attNo<<"  Detach-Request= "<< detNo<<"  Service-Request= "<<sreqNo<<endl;
	cout << fixed;
	cout.precision(2);
	traffic_percent = ((attNo+detNo)*1.0/(attNo+detNo+sreqNo))*100; //Attach Percentage served
        cout<<"Attach Percentage= "<<traffic_percent<<endl;
	/*verify traffic distribution */
	cout<<"\n ******* verify traffic distribution "<<endl;
	for(int i=0;i<6;i++){
		cout<<i<<"--->"<<distr_check[i]<<endl;
	}
	/* end verification*/

	/***** EPOCH STATISTICS *******/
	for (int i=0; i<=curr_mix_index; i++){
		cout<< "EPOCH "<<i<<"Tpt= "<<tpt[i]<<" LAT(ms)= "<<lat[i]<<endl;
	}

	/******************************/



	/* Write the metrics to the statistics file */
	if(!fileExists(STATISTIC_FILE)){
		data.append("#MaxThreads").append(COMMA).append("#UE").append(COMMA).append("AvUE/Thread").append(COMMA);
		data.append("ExecutionTime").append(COMMA);
		data.append("RegistrationThroughput(registrations/sec)").append(COMMA);
		data.append("RegistrationLatency(sec)").append(COMMA);
		data.append("SetupTunnel(Yes/No)").append(COMMA);
		data.append("DO Detach (Yes/No)").append(COMMA);
		data.append("SendingData?(Yes/No)").append(COMMA).append("MeanDataSendingTime").append(COMMA).append("SendingRate").append(COMMA);
		data.append("#Attach").append(COMMA).append("#Detach").append(COMMA);
		data.append("#Service_Requests").append(COMMA);
		data.append("ATTACH_PERCENT").append(COMMA);
		data.append("EPOCH_TPT").append(COMMA).append("EPOCH_DELAY_ms").append(COMMA).append("ServiceRequestLatency");
		data.append("\n");
	}
	/*if(!fileExists(INST_FILE)){
		data = "";
		data.append("ThroughputPerPeriod").append(COMMA).append("RespTimePerPeriod");
		data.append("\n");
	}*/

	outfile.open(STATISTIC_FILE, std::ios_base::app);
	if (outfile.is_open()){
		data.append(to_string(maxThreads)).append(COMMA).append(to_string(total_ue)).append(COMMA).append(avUE).append(COMMA);
		data.append(to_string((actual_endTime - curTime))).append(COMMA);
		data.append(to_string(registrationThroughput)).append(COMMA);
		data.append(to_string(average_registration_time)).append(COMMA);
		data.append(setUpTunnel?"Yes":"No").append(COMMA);
		data.append(doDetach?"Yes":"No").append(COMMA);
		data.append(sendData?"Yes":"No").append(COMMA);
		data.append(to_string(UE_MEAN_DATA_SENDING_TIME)).append(COMMA).append(rate).append(COMMA);
		data.append(to_string(attNo)).append(COMMA);
		data.append(to_string(detNo)).append(COMMA).append(to_string(sreqNo)).append(COMMA);
		data.append(to_string(traffic_percent)).append(COMMA).append(to_string(average_sr_registration_time));
		if (dynLoad==true){
			for (int i=0; i<=curr_mix_index; i++){
				data.append(COMMA).append(to_string(tpt[i])).append(COMMA).append(to_string(lat[i]));
			}
		}
		data.append("\n");
		outfile << data;
		outfile.close();
		//data="";
	}

	if (instrumentTptLat) {
		instfile.open(INST_FILE, std::ios_base::app);
		data = "";
		if (instfile.is_open()){
			for(int i = 0; i < instIndex; i++){
				float t = num_ue_inst[i];
				float l = resp_time_inst[i];
				data.append(to_string(t)).append(COMMA).append(to_string(l)).append("\n");

			}
			instfile << data;
			instfile.close();
		}
	}

	if (WANT_DELAY_CDF){
	/*Captured Delays of each thread for Delay Distribution*/
		delayfile.open(DELAY_FILE, std::ios_base::app);
		data = "";
		if (delayfile.is_open()){
		/*for(int i = 0; i < maxThreads; i++){
			float delay = (ue_registration_response_time[i]*1.0)/(num_ue_per_thread[i]*1000);
			cout<<"Delay for UE thread "<<i<<" = "<<delay<<" ms\n";
			data.append(to_string(delay)).append("\n");

		}*/
			for(int i = 0; i < total_ue; i++){
				long delay = stored_ue_registration_response_time[i];
			//cout<<"Delay for UE thread "<<i<<" = "<<delay<<" ms\n";
				data.append(to_string(maxThreads)).append(COMMA).append(to_string(delay)).append("\n");

			}
			delayfile << data;
			delayfile.close();

		}
	}

	/* Kill all the iperf3 client processes after the simulation ends */
	//if(sendData){
		system(("sudo killall iperf3 "+c+"").c_str());
	//}

	exit(0);
	return 0;
}

inline bool fileExists (const std::string& name) {
	struct stat buffer;
	return (stat (name.c_str(), &buffer) == 0);
}

string GetStdoutFromCommand(string cmd) {
        string data;
        FILE * stream;
        const int max_buffer = 256;
        char buffer[max_buffer];
        cout<<"Entered getstdout"<<endl;
        // if you want to see error uncomment the below line

        cmd.append(" 2>&1");

        stream = popen(cmd.c_str(), "r");

        cout<<"After popen"<<endl;

        if (stream) {
                //cout<<"inside if stream"<<endl;
                while (!feof(stream)){
                        cout<<"inside !feof stream "<<cmd<<endl;

                        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
                }

		pclose(stream);
        }
//      cout<<"before return"<<endl;

        return data;
 }
