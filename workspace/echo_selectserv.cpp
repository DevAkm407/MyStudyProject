#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 100

using namespace std;

void error_handling(string message);

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_adr;
    timeval timeout;
    fd_set reads, cpy_reads;
    socklen_t adr_sz;
    int fd_max,str_len,fd_num,i;
    char buf[BUF_SIZE];
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

    FD_ZERO(&reads);//기본세팅은 0
    FD_SET(serv_sock,&reads);//reads에 servo_sock을 등록합
    fd_max=serv_sock;//fd_max serv_Sock에 파일디스크립터를 받음
    while (1)
    {
        cpy_reads=reads; //cpy_reads가 reads의 정보를 복사
        timeout.tv_sec=5;
        timeout.tv_usec=5000;

        //파일 검사를 정확하게 몇개할지 생각하는게 귀찮아서 serv_sock에 파일 디스크립터 번호를 사용하는 듯 하다
        if((fd_num=select(fd_max+1,&cpy_reads,0,0,&timeout))==-1)
            break;
        if(fd_num==0)
            continue;
        for ( i = 0; i <fd_max+1; i++)
        {
           if(FD_ISSET(i,&cpy_reads))//i번째 파일 디스크립터를 검사
           {
                if(i==serv_sock)//검사한 파일 디스크립터가 serv_sock이면 클라이언트와 연결
                {
                    adr_sz=sizeof(clnt_adr);
                    clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&adr_sz);
                    cout<<"C ip: "<<inet_ntoa(clnt_adr.sin_addr)<<" ";//연결한 클라이언트 IP정보를 눈으로 보기
                    FD_SET(clnt_sock,&reads);//read에 클라이언트 소켓을 등록한다.
                    if(fd_max<clnt_sock)    //클라이언트 소켓에 번호가 fd_max보다 크면 clnt_sock값으로 바꾸어줌
                        fd_max=clnt_sock;
                    cout<<"connected client: "<<clnt_sock<<endl;
                }
                else//검사한 파일 디스크립터가 serv_sock이 아닐경우 클라이언트 소켓이 요청한 내용이니까....
                {
                    str_len=read(i,buf,BUF_SIZE);//i는 특정 클라이언트의 파일디스크립터이다. 그 클라이언트가 보낸 데이터를 buf가 BUF_SIZEA만큼 읽어온다.
                    if(str_len==0)//연결이 종료를 요청했으면
                    {
                        FD_CLR(i,&reads);//그 클라이언트 소켓을 검사항목에서 제거
                        close(i);//소켓 close
                        cout<<"closed client: "<<i<<endl;
                    }
                    else//읽었을때 보낸 데이터가 있으면 write buf가 읽어온 데이터를 가지고 있기때문에 읽은것 그대로 보낸다.
                        write(i,buf,str_len);
                }
           }
        }
    }
    close(serv_sock);
    return 0;   
}    

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}