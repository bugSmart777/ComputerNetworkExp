#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include <arpa/inet.h>
#include <string.h>
#include "global.h"

#define SERV_PORT 6666
#define SERV_IP "127.0.0.1"

using namespace std;
int main(int argc ,char *argv[]){
	
	int lfd,cfd;
	
	struct sockaddr_in serv_addr,clie_addr;
	socklen_t clie_addr_len;

	char buf[BUFSIZ],clie_IP[BUFSIZ];
	int n;

	lfd=Socket(AF_INET,SOCK_STREAM,0);
	bzero(&serv_addr,sizeof(serv_addr));
	//lfd=socket(AF_INET,SOCK_DGRAM,0);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERV_PORT);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	Bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	Listen(lfd,128);
	clie_addr_len=sizeof(clie_addr);
	cfd=Accept(lfd,(struct sockaddr *)&clie_addr,&clie_addr_len);
	printf("client IP:%s, client port:%d\n",
					inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_IP,sizeof(clie_IP)),
					ntohs(clie_addr.sin_port));
	while(1){
		n=Read(cfd,buf,sizeof(buf));
		for(int i=0;i<n;i++){
			buf[i]=toupper(buf[i]);
		}
		Write(cfd,buf,n);
	}
	Close(lfd);
	Close(cfd);
	return 0;
}
