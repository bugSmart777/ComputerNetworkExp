#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "global.h"
using namespace std;
#define SERV_PORT 6666
#define SERV_IP "127.0.0.1"
FILE *fp;
int main(int argc,char *argv[]){
	int cfd;
	struct sockaddr_in serv_addr;
	char buf[BUFSIZ];
	int n;
	
	cfd =Socket(AF_INET,SOCK_DGRAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERV_PORT);
	inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);
	Connect(cfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

	while(1){
			fgets(buf,sizeof(buf),stdin);
			n=sendto(cfd,buf,strlen(buf),0,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
			if(n==-1){
				perror("sendto error");
				exit(1);
			}
			n=recvfrom(cfd,buf,BUFSIZ,0,NULL,0);
			if(n==-1){
				perror("recvfrom error");
			}
			Write(STDOUT_FILENO,buf,n);
	}
	Close(cfd);
	return 0;

}
