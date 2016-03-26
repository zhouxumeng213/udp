#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define _PORT_ 8080
int main()
{
	//create a socket
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		perror("socket");
		return 1;
	}
	//tian chong ben di xin xi
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(_PORT_);
	local.sin_addr.s_addr=htonl(INADDR_ANY);
	//bang ding
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0){
		perror("bind");
		return 2;
	}
	char buf[1024];
	memset(buf,'\0',sizeof(buf)-1);
	struct sockaddr_in client;
	socklen_t len=sizeof(client);
	while(1){
		ssize_t _size=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
		if(_size<0){
			perror("recvfrom");
			continue;
		}else{
			buf[_size]='\0';
			printf("client:%s");
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&client,len);
		}
	}
	close(sock);
}
