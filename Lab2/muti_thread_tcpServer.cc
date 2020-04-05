#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
#include <ctype.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include "global.h"

#define SERV_PORT 8888
#define MAXLINE 8192

using namespace std;
FILE *fp;

struct s_info{
	struct sockaddr_in clie_addr;
	int cfd;
//	int num;
};

void * do_work(void *arg){
	int n,i;
	struct s_info *ts=(struct s_info*)arg;
	char buf[BUFSIZ];
//	char str[INET_ADDRSTRLEN];
	while(1){
		n=Read(ts->cfd,buf,BUFSIZ);
		if(n==0){
			printf("the client %d closed...\n",ts->cfd);
			break;
		}
		for(i=0;i<n;i++){
			buf[i]=toupper(buf[i]);
		}
		Write(ts->cfd,buf,n);
	}
	Close(ts->cfd);
	return (void*)0;
}


int main(int argc,char * argv[]){
	int lfd,cfd;
	pthread_t tid;
	struct s_info ts[256];
	//char buf[BUFSIZ],clie_IP[BUFSIZ],to_clie[BUFSIZ];
	struct sockaddr_in serv_addr , clie_addr;
	socklen_t clie_addr_len;
	int n,i=0;

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
		ts[i].clie_addr=clie_addr;
		ts[i].cfd=cfd;
	//	ts[i].num=i+1;
		pthread_create(&tid,NULL,do_work,(void*)&ts[i]);
		pthread_detach(tid);
		i++;
	}
	return 0;
}

