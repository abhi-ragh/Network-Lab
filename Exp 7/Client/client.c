#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argr,char *argv[]){
	int socket_desc;
	char message[2000],filename[2000];
	struct sockaddr_in server;
	FILE *fp;
	
	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if (socket_desc==-1){
		printf("Could not create socket");
	}
	
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_family=AF_INET;
	server.sin_port=htons(8888);
	
	if(connect(socket_desc,(struct sockaddr*)&server,sizeof(server))<0){
		puts("connect error");
		return 1;
	}
	
	puts("Connected");
	
	do{
		puts("Filename: ");
		scanf("%s",filename);
		if(send(socket_desc,filename,strlen(filename),0)<0){
			puts("Send failed");
			return 1;
		}
		fp = fopen("backup","w");
		while(recv(socket_desc,message,2000,0)){
			if(strcmp(message,"EOF")){
				fputs(message,fp);
				puts(message);
			}
			else{
				fclose(fp);
				break;
			}
		}
	}while(1);
return 0;
}
