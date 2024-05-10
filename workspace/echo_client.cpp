#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SZIE 1024
using namespace std;
void error_handling(string message);

int main(int argc, char *argv[])
{
    int sock;
    sockaddr_in serv_addr;
    char message[BUF_SZIE];
    int str_len=0;
    
    if(argc !=3)
    {
        cout << "Usage : " << argv[0] << " <IP> <port>\n";
        exit(1);
    }

   sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock ==-1)
        error_handling("socket() error");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sock,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("connect() error!");
    else
        cout<<"connected......";

    while (1)
    {
        cout<<"Input message(Q to quit): ";
        fgets(message,BUF_SZIE,stdin);
        
        if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
            break;
        write(sock,message,strlen(message));
        str_len=read(sock,message,BUF_SZIE-1);
        message[str_len]=0;
        cout<<"Message from server: "<<message;
    }
    close(sock);
    return 0;
    
    
    
    }
void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}