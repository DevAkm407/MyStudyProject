#include<iostream>
#include<string.h>
#include<string>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
using namespace std;
void error_handling(string message);

int main(int argc, char *argv[])
{
    int serv_sd,clnt_sd;
    FILE * fp;
    char buf[BUF_SIZE];
    int read_cnt;
    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    if(argc !=2)
    {
        cout<<"USage: " <<argv[0] <<" <port>"<<endl;
        exit(1);
    }

    fp=fopen("file_server.cpp","rb");//파일 open 읽기모드 현재 이 파일을 읽음
    serv_sd=socket(PF_INET,SOCK_STREAM,0);//IPV4 사용 ,TCP통신사용,기본 TCP프로토콜사용
    if(serv_sd ==-1)
        error_handling("socket() error");
    memset(&serv_adr,0,sizeof(serv_adr));//소켓구조체 안쪽을 0으로 초기화 해야함(구조체길이를 맞추기위한 변수의 0을 무조건 넣어주기위해서)
    serv_adr.sin_family=AF_INET;//IPV4사용
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);//자동으로 이 컴퓨터에 존재하는 랜카드 중 사용가능한 랜카드의 ip주소를 사용하라는 의미이다.일반 PC경우의 랜카드 1개임
    serv_adr.sin_port=htons(atoi(argv[1]));//포트번호를 프로토콜의 맞게 빅엔디안 방식으로 바꿔줌

    if(bind(serv_sd,(sockaddr*)&serv_adr,sizeof(serv_adr))==-1)//IP,포트번호를 소켓에 연결해줌
        error_handling("bind() error");
    if(listen(serv_sd,5)==-1)//대기
        error_handling("listen() error");
    clnt_adr_sz=sizeof(clnt_adr);//소켓길이를 알기위해서 SIZEOF사용
    clnt_sd=accept(serv_sd,(sockaddr*)&clnt_adr,&clnt_adr_sz );
    while (1)
    {
        //fread => 버퍼,버퍼에 저장할 배열의 원소 하나의 크기,버퍼 크기,FILE* 타입 변수
        //반환값  fread를 통해 실제로 읽은 배열의 원소 개수를 반환.
        read_cnt=fread((void*)buf,1,BUF_SIZE,fp);
        if(read_cnt<BUF_SIZE)//읽어온 개수보다 버퍼 사이즈가 크면
        {
            //클라이언트 소켓에,버퍼를 써라,읽어온 길이만큼 즉 읽어온 데이터를 클라이언트 소켓에 보내라
            write(clnt_sd,buf,read_cnt);
            break;
        }
        //평소엔 BUF_SIZE만큼 읽으니까 그냥 클라이언트에 그만큼 보내라     
        write(clnt_sd,buf,BUF_SIZE);

    }
    shutdown(clnt_sd,SHUT_WR);//입력스트림 제거
    read(clnt_sd,buf,BUF_SIZE);//클라이언트 소켓에서 버퍼 싸이즈만큼 읽기,상대가 뭔가 보냄
    cout<< "Message from client: "<<buf<<endl;//보낸 메시지 출력
    fclose(fp);//파일닫기
    close(clnt_sd);//클라이언트와 연결 해제
    close(serv_sd);//서버도 헤제
    return 0;
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}
