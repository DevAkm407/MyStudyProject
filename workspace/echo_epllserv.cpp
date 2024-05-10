#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 4
#define EPOLL_SIZE 50 
using namespace std;
void error_handling(string message);

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_adr;
    socklen_t adr_sz;
    int str_len,i;
    char buf[BUF_SIZE];
    epoll_event *ep_events;
    epoll_event event;
    int epfd,event_cnt;
    if(argc!=2)
    {
        cout<<"Usage : "<<argv[0] <<" <prot>\n";
        exit(1);
    }
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("bind() error");
    if(listen(serv_sock,5)==-1)
        error_handling("listen() error");
    
    epfd=epoll_create(EPOLL_SIZE);//운영체제의 epoll을 콜하고 파일디스크립터를 받음
    ep_events=new epoll_event[EPOLL_SIZE];//동적할당으로 epoll_event만들어줌

    event.events=EPOLLIN;//수신할 데이터가 존재하는 상황을 이벤트로 등록
    event.data.fd=serv_sock;//serv_sock을 감시대상으로 등록
    epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event);//만들어진 epoll구조체변수와 실질적인 역활을하고있는 운영체제에 epoll과 바인드해주는 느낌

    while (1)
    {
        event_cnt=epoll_wait(epfd,ep_events,EPOLL_SIZE,-1);//epoll이 얼마만큼 이벤트가 발생할때 까지 대기할 것인지
        if(event_cnt==-1)
        {
            cout<<"epoll_wait() error";
            break;
        }
        cout<<"return epoll_wait\n";
        for ( i = 0; i <event_cnt ; i++)
        {
            if(ep_events[i].data.fd==serv_sock)//운영체제에서 데이터변화를 감지했는대 그게 serv_sock이면
            {
                adr_sz=sizeof(clnt_adr);
                clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&adr_sz);
                string a=inet_ntoa(clnt_adr.sin_addr);
                cout<<"C ip: "<<a<<" ";
                event.events=EPOLLIN;// 수시할 데이터가 존재하는 상황을 이벤트로 정하겠다.
                event.data.fd=clnt_sock;//clnt_sock에 파일디스크립터를 검사항목으로 등록
                epoll_ctl(epfd,EPOLL_CTL_ADD,clnt_sock,&event);//진짜 epoll에 등록
            }
            else
            {
                    str_len=read(ep_events[i].data.fd,buf,BUF_SIZE);
                    if(str_len==0)
                    {
                        epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);//진짜epoll에서 ep_events[i]번째 clnt_sock을 제거
                        close(ep_events[i].data.fd);//해당 소켓 close
                        cout<<"closed client: "<<ep_events[i].data.fd<<endl;
                    }
                    else
                    {
                        write(ep_events[i].data.fd,buf,str_len);
                    }
            }
        }   
    }
    close(serv_sock);
    close(epfd);
    return 0;
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}