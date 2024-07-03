#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void main(){
    char buf[100];
    int SP1,k;
    struct sockaddr_in server,client;

    int a[10][10],b[10][10],c[10][10],n=2,i,j;
    
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = 3003;

    SP1 = socket(AF_INET,SOCK_STREAM,0);
    
    k = connect(SP1,(struct sockaddr*)&client,sizeof(client));

    while(1){
        printf("Enter Matrix A Elements\n");
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                printf("Enter A[%d][%d]: ",i,j);
                scanf("%d",&a[i][j]);                
             }

        printf("Enter Matrix B Elements\n");
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                printf("Enter B[%d][%d]: ",i,j);
                scanf("%d",&b[i][j]);                
             }


        k = send(SP1,a,sizeof(a),0);
        k = send(SP1,b,sizeof(b),0);
    
        k = recv(SP1,c,sizeof(c),0);

        printf("Matrix A + Matrix B = \n");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                printf("%d ",c[i][j]);                
             }
            printf("\n");
        }       
    }

}
