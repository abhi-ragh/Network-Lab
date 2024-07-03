#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void main(){
    char buf[100];
    int SP1,SP2,k;
    struct sockaddr_in server,client;
    socklen_t len;
    
    int a[10][10],b[10][10],c[10][10],n=2,i,j;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;
    
    SP1 = socket(AF_INET,SOCK_STREAM,0);

    k = bind(SP1,(struct sockaddr*)&server,sizeof(server));
    k = listen(SP1,5);
    len = sizeof(client);    

    SP2 = accept(SP1,(struct sockaddr*)&client,&len);
    if (SP2 < 0)
        printf("Error");

    while(1){
        k = recv(SP2,a,sizeof(a),0);
        k = recv(SP2,b,sizeof(b),0);
        
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                c[i][j] = a[i][j] + b[i][j];            
            }

        k = send(SP2,c,sizeof(c),0);    
    }
}
