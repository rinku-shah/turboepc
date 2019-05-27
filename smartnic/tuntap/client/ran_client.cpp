// sudo ifconfig tun1 up
// sudo route add -host 10.129.131.171 tun1

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

using namespace std;

#define PORT     		8080	// both DN and UPF listens at the same port
#define MAXLINE 		1024
#define SINK_SERVER_IP	"10.129.131.158"
#define MIDDLE_SERVER_IP	"192.168.2.3"

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

 


int tun_alloc(char *dev, int flags) {
	struct ifreq ifr;
	int fd, err;
	const char *clonedev = "/dev/net/tun";
	if( (fd = open(clonedev, O_RDWR)) < 0 ) {
		cout << "something wrong !" << endl;
		return fd;
	}
	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags = flags;
	if (*dev) {
		strncpy(ifr.ifr_name, dev, IFNAMSIZ);
	}
	if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
		perror("ioctl");
		close(fd);
		return err;
	}
	strcpy(dev, ifr.ifr_name);
	return fd;
}
int receive_data(int tunfd, char *packet, int bufsize) {
    int len;
    len = read(tunfd, packet, bufsize);
    if (len < 0) {
        perror("read");
    }
    return len;
}
void printArray(char * buf, int bufsize) {
    for(int i=0; i<bufsize; i++)
        printf("0x%02X ", buf[i]);

    printf("\n");
}

int main() {
    
    
    char tun_name[IFNAMSIZ];
    strcpy(tun_name, "tun2");
    int tunfd = tun_alloc(tun_name, IFF_TUN | IFF_NO_PI);
    getchar();

	cout<<"tunfd = "<<tunfd<<endl;
    int sockfd;
    // printf("Enter the tcpdatasocket:");
    // scanf("%d", &sockfd);

	/******************************************* @vikas : open TCP stream to server   **********************************************/
	char buffer[MAXLINE];
	struct sockaddr_in     servaddr;

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(MIDDLE_SERVER_IP);    

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    }else {
        printf("connected to the server..\n"); 
				cout<<"sockfd = "<<sockfd<<endl;
    }
	/******************************************************************************************************************************/

    // getchar();

	long long int cnt = 0;
	while(1) {
		char buf[1024];
		cout <<"reading..." << endl;
		int len = receive_data(tunfd,buf,1024);
		if(len>=0)
		cout << YELLOW <<"Number of bytes captured by RAN = " << len << RESET <<endl;
		// printArray(buf, len);
                write(sockfd, buf, len); // write to tcp socket  
		// sendto(sockfd, buf, len,
		// 	MSG_CONFIRM, (const struct sockaddr *) &servaddr,
		// 	sizeof(servaddr));
		cout << YELLOW << "Packet sent by RAN to UPF" << RESET << endl;
		cnt++;
	}	

	return 0;
}
