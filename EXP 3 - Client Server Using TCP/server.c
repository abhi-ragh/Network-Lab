#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void main(){
	char buf[100];
	struct sockaddr_in server,client;
	int SP1 , SP2, SP3,SP4,K;
	socklen_t len;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=3003;
	
	SP1 = socket(AF_INET,SOCK_STREAM,0);
	K = bind(SP1, (struct sockaddr*)&server,sizeof(server));
	K = listen(SP1,5);
	len = sizeof(client);
	SP2 = accept(SP1 , (struct sockaddr*)&client,&len);
	if(SP2<0)
		printf("ERROR");
	while(1){
		K=recv(SP2,buf,100,0);
		printf("\nMessage From Client : %s\n",buf);
		printf("Enter Message to Send:");
		fgets(buf,100,stdin);
		K = send(SP2,buf,100,0);		
		}
}
