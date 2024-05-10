#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
using namespace std;
void error_handling(string message);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;
    sockaddr_in serv_addr; //서버소켓 객체
    sockaddr_in clnt_addr;//클라이언트 소켓 객체
    socklen_t clnt_addr_size;

    char message[]="hello world!";

    if(argc !=2)
    {
        cout << "Usage : " << argv[0] << "<port>\n";
        exit(1);
    }

    serv_sock=socket(PF_INET,SOCK_STREAM,0);//소켓할당 ipv4사용,tcp프로토콜사용,디폴트 프로토콜
    if(serv_sock ==-1)
        error_handling("socket() error");
    
    memset(&serv_addr,0,sizeof(serv_addr)); //서버소켓 초기화
    serv_addr.sin_family=AF_INET;   //TCP프로토콜을 사용하겠다.
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);//자동으로 이 컴퓨터에 존재하는 랜카드 중 사용가능한 랜카드의 ip주소를 사용하라는 의미이다.
    serv_addr.sin_port=htons(atoi(argv[1]));//포트번호를 네트워크 방식의맞게 변환 (빅엔디안으로)

    if(bind(serv_sock,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)//서버소켓의 파일번호,서버소켓 객체포인터 타입주소,서버소켓크기를주면
        error_handling("bind() error");//이러한 정보들을 받아서 소켓에 ip와 포트 번호를 할당해주는 작업을bind함수가 자동으로해준다.
    if(listen(serv_sock,5)==-1)//소켓의 파일번호,몇명의 사용자의 연결을 대기할것인가, 해당 함수는 5번의 연결이 오기까지를 기다린다.
        error_handling("listen() error");
    
    clnt_addr_size=sizeof(clnt_addr);  //클라이언트 소켓 객체의 사이즈 측정
    clnt_sock=accept(serv_sock,(sockaddr*)&clnt_addr,&clnt_addr_size);//서버소켓 파일번호,sockaddr*타입clnt_addr 주소,
    //소켓길이를 가지고 있는 객체의 주소를 넣어준다. accpet함수가 실패하면 -1을 반환한다.

    if(clnt_sock==-1)
        error_handling("accept() error");
    write(clnt_sock,message,sizeof(message));//리눅스는 파일단위이기때문에 write를 사용할 수 있다
    close(clnt_sock);//클라이언트 소켓과 연결 해제
    close(serv_sock);//서버 닫기
    return 0;
    
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}