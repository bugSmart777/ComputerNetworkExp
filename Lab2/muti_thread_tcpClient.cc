#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "global.h"
using namespace std;
#define SERV_PORT 8888
#define SERV_IP "127.0.0.1"
FILE *fp;
int main(int argc,char *argv[]){
	int cfd;
	struct sockaddr_in serv_addr;
	char buf[BUFSIZ];
	int n;
	
	cfd =Socket(AF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERV_PORT);
	inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);
	Connect(cfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

	while(1){
//		char File[100];
//		cin>>File;
//		fp=fopen(File,"r");
//		while(fgets(buf,sizeof(buf),fp)!=NULL){
			fgets(buf,sizeof(buf),stdin);
			Write(cfd,buf,strlen(buf));
//		}
			n=Read(cfd,buf,sizeof(buf));
			Write(STDOUT_FILENO,buf,n);
	}
	Close(cfd);
	return 0;

}
