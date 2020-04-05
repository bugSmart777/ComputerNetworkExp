#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
#include <ctype.h>
#include <sys/wait.h>
#include "global.h"

#define SERV_PORT 8888


using namespace std;
FILE *fp;
void wait_child(int signo){
	while(waitpid(0,NULL,WNOHANG)>0);
	return;
}



int main(int argc,char * argv[]){
	pid_t pid;
	int lfd,cfd;
	char buf[BUFSIZ],clie_IP[BUFSIZ],to_clie[BUFSIZ];
	struct sockaddr_in serv_addr , clie_addr;
	socklen_t clie_addr_len;
	int n,i;

	lfd=Socket(AF_INET,SOCK_STREAM,0);

	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERV_PORT);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	Bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	
	Listen(lfd,128);
	while(1){
			clie_addr_len=sizeof(clie_addr);
			cfd=Accept(lfd,(struct sockaddr*)&clie_addr,&clie_addr_len);
	//		printf("client IP:%s, port:%d\n",
	//						inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_IP,sizeof(clie_IP)),
	//						ntohs(clie_addr.sin_port));
			pid=fork();
			if(pid<0){
				perror("fork error");
				exit(1);
			}
			else if(pid==0){
				Close(lfd);
				while(1){
					n=Read(cfd,buf,sizeof(buf));
					if(n==0){
						Close(cfd);
						return 0;
					}
					else if(n==-1){
						perror("read error");
						exit(1);
					}
					else{
						Write(STDOUT_FILENO,buf,n);
						char File[100];
					    cin>>File;
						fp=fopen(File,"r");
						while(fgets(to_clie,sizeof(to_clie),fp)!=NULL){
							Write(cfd,to_clie,strlen(to_clie));
						}
					}	
				}
			}
			else{
				Close(cfd);
				signal(SIGCHLD,wait_child);
			}
	}
	return 0;
}

