#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SZIE 30
using namespace std;
void error_handling(string message);
void read_routine(int sock,char *buf);
void write_routine(int sock,char *buf);
int main(int argc, char *argv[])
{
    int sock;
    pid_t pid;
    sockaddr_in serv_addr;
    char buf[BUF_SZIE];
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
    
    pid=fork();
    if(pid==0)
        write_routine(sock,buf);
    else
        read_routine(sock,buf);

    
    return 0;
    }
void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}

void read_routine(int sock, char *buf)
{
    while (1)
    {
        int str_len=read(sock,buf,BUF_SZIE);
        if(str_len==0)
            return;
        
        buf[str_len]=0;
        cout<<"Message from server: "<<buf<<endl;
    }
    
}

void write_routine(int sock,char *buf)
{
    while (1)
    {
        fgets(buf,BUF_SZIE,stdin);
        if(!strcmp(buf,"q\n")||!strcmp(buf,"Q\n"))
        {
            shutdown(sock,SHUT_WR);
            return;
        }
        write(sock,buf,strlen(buf));
    }   
}