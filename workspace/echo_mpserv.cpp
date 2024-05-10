#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 30
using namespace std;

void error_handling(string message);
void read_childproc(int sig );

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_adr;
    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len,state;
    char buf[BUF_SIZE];
    if(argc!=2)
    {
        cout<<"Usage : "<<argv[0] <<" <prot>\n";
        exit(1);
    }

    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    state=sigaction(SIGCHLD,&act,0);
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("bind() error");
    if(listen(serv_sock,5)==-1)
        error_handling("listen() error");
    while (1)
    {
        adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&adr_sz);
        if(clnt_sock==-1)
            continue;
        else{    
            printf("new Client connected\n Client ip: %s ",inet_ntoa(clnt_adr.sin_addr));

        }
        
        pid = fork();    
        
        if(pid==-1)
        {
            close(clnt_sock);
            continue;
        }     
        
        if(pid==0)
        {
            close(serv_sock);
            while ((str_len=read(clnt_sock,buf,BUF_SIZE))!=0)
                write(clnt_sock,buf,str_len);
            close(clnt_sock);
            cout<<"client disconnected...\n";
            return 0;
        }
        else
            close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid=waitpid(-1,&status,WNOHANG);
    cout<<"removed proc id: "<< pid << endl;
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}