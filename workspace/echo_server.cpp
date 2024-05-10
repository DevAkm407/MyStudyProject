#include<iostream>
#include<string.h>
#include<string>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
using namespace std;
void error_handling(string message);

int main(int argc, char *argv[])
{
    int serv_sock,clnt_sock;
    char message[BUF_SIZE];
    int str_len,i;
    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc !=2)
    {
        cout<<"USage: " <<argv[0] <<" <port>"<<endl;
        exit(1);
    }

    serv_sock=socket(PF_INET,SOCK_STREAM,0);//IPV4 사용 ,TCP통신사용,기본 TCP프로토콜사용
    if(serv_sock ==-1)
        error_handling("socket() error");
    memset(&serv_adr,0,sizeof(serv_adr));//소켓구조체 안쪽을 0으로 초기화 해야함(구조체길이를 맞추기위한 변수의 0을 무조건 넣어주기위해서)
    serv_adr.sin_family=AF_INET;//IPV4사용
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);//자동으로 이 컴퓨터에 존재하는 랜카드 중 사용가능한 랜카드의 ip주소를 사용하라는 의미이다.일반 PC경우의 랜카드 1개임
    serv_adr.sin_port=htons(atoi(argv[1]));//포트번호를 프로토콜의 맞게 빅엔디안 방식으로 바꿔줌

    if(bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr))==-1)//IP,포트번호를 소켓에 연결해줌
        error_handling("bind() error");
    if(listen(serv_sock,5)==-1)//대기
        error_handling("listen() error");
    
    clnt_adr_sz=sizeof(clnt_adr);//소켓길이를 알기위해서 SIZEOF사용

    for ( i = 0; i < 5; i++)
    {
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz);//연결
        if(clnt_sock==-1)
            error_handling("accept() error");
        else
            cout<<"Connected client "<<i+1<<endl;
        while ((str_len=read(clnt_sock,message,BUF_SIZE))!=0)
        {//버퍼(MESSAGE)에 데이터 읽어오기
            write(clnt_sock,message,str_len);//데이터 쓰기
            cout<<"받은 메세지: " <<message;
        }
        close(clnt_sock);        
    }
    close(serv_sock);
    return 0;
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}