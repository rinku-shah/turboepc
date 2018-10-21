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

void error(const char *msg){
  perror(msg);
  
}
int main(int argc, char *argv[])
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
      printf("\n");

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
    localaddr.sin_addr.s_addr = inet_addr("10.127.1.2");
    localaddr.sin_port = 0;  // Any local port will do
    if(bind(sockfd, (struct sockaddr *)&localaddr, sizeof(localaddr))==0){
        printf("Binded Correctly\n"); 
    }
    else{
         
        printf("Unable to bind\n"); 
    }

    if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
      perror("ERROR connecting");
    }
    char buff[BUFFER_SIZE];
    memset(buff,0,BUFFER_SIZE);

    sprintf(buff,"%s","tffXE5CT0fn8qnN9QwEDStJhNTU0TtqtiSk9JYJRDWGPp2ETwHXSNmkaT5jnBRptoPx0xvtDdWPa9lsoWDWVtu3UJIkYYTY6qnfLdzp9mSkSe7R1wsjoldi8YKulcFn1lh3bh4SERWNsUlIshNZPE281SIBC3dmcMS7cu0ajnZM5GCF0oONCsJjQmkZ7xUNZkUeCsGQMiqXe0BM8wlE019fP8hXkAmMwmeLKYkPtVLhKIDLI4lH4QxZQDXNKEB9Q2a9rvdv14bZTzG5PKAZ8z46wr7g9Vp60GwFXiJcBJxOhFbRcvCYUadVGoBabk4fo4gdWrNQAEAYIxm6S7J0dXlCZHud0fyGzzzkrQ0TuNgDFxxEQoWKtiL7KEJPQeeV8Ege2fbM4UC9p4Ks1rJsigIsV2vAcYKGTHlfBcRNXLDk5homW1RQJcB7NXGvV5Efjf5XJ4hyf5kYJWfs5UgW6iGmhDDBfr9jGFXWAB5xSo7BptH4s4DIZbjQ8f79irZrK291dM58zWQfJPD8AIyjWbvn73tYRnUhyn3UPIno7tTqVkkCxC4nBZ44GY7Lg3zIvcbKvetTdofCB3EfVWdbyIMSIGRjxvwdLHgieZY7DZyX3ZJHjpQ3pbyE1boGp7dKQGgA86lgMaKbzUqgNv9OpGaIVusVGOgYy9v29USGv5rO504dOTlH8RPjWuHMKBUiNGXbNLGMHCQGvV6LOreSBEUFpZOOuCIqPxEGZzCqQBQ7ZwLxfT7khfWjE9GvXYK4KSo59yLGeq4D1CTDoe7IJQj9kiL3Jnjfis0zaI3i13wMfmuZMXCanW6FQzTp9RmInV8LzGoX7rSdsdilsVwO8aI3DT62qztvCzV64swaYy1AjSAz70RMNs9sMoSKnqEV3ACi8nUAenQn1txmBWz6h4yYZiZ4hs3TArykHvwVAEt2VXpeJH47I2owZxHBmT4g9aCRtWslY9jjP7oOJDEUvwiyY9mKj4mTDs5RuxUrNbN2xc1UEtJgw03qNeRvqdUsq"); 
    //cout<<"buufer is"<<buff<<endl;

    int n = send(sockfd,buff,sizeof(buff),0);
    if (n < 0) error("get_filesystem_from_server:ERROR writing to socket");
    memset(buff,0,BUFFER_SIZE);

    if ((nbytes = recv(sockfd, buff, sizeof buff, 0)) <= 0)
        {                
            if (nbytes == 0) {
            	printf("connection %d closed\n", socket);
                close(sockfd);
                pthread_exit(NULL);
			}
            else {
                perror("recv");
            }
        }
    // cout << "buffer received in client = " << buff <<endl;
    close(sockfd);
}
