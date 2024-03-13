#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void main(){
	char buf[100];
	struct sockaddr_in server,client;
	int SP1,K;
	socklen_t len;
	
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = 3003;
	
	SP1 = socket(AF_INET,SOCK_STREAM,0);
	K=connect(SP1, (struct sockaddr*)&client,sizeof(client));
	while(1){
		printf("Enter The Message: ");
		fgets(buf,100,stdin);
		K = send(SP1,buf,100,0);
		
		K = recv(SP1 , buf , 100 ,0);
		printf("\nMessage from Server:  %s\n",buf);
	}
}
