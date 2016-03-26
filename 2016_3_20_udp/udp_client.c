#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main()
{
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		perror("sock");
		exit(1);
	}
	struct sockaddr_in remote;
	remote.sin_family=AF_INET;
	remote.sin_port=htons(8080);
	remote.sin_addr.s_addr=inet_addr("127.0.0.1");
	socklen_t len=sizeof(remote);
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	while(1){
		ssize_t _size=read(0,buf,sizeof(buf)-1);
		buf[_size]='\0';
		_size=sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&remote,len);
		_size=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
		if(_size>0){
			printf("server echo:%s");
		}
	}
	close(sock);
	return 0;
}
