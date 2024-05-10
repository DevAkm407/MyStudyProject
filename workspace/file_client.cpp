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

int main(int argc, char *argv[])
{
    int sd;
    FILE *fp;
    sockaddr_in serv_addr;
    char buf[BUF_SZIE];
    int read_cnt;
    
    if(argc !=3)
    {
        cout << "Usage : " << argv[0] << " <IP> <port>\n";
        exit(1);
    }
    fp=fopen("recive.dat","wb");//파일 오픈 쓰기모드
    sd=socket(PF_INET,SOCK_STREAM,0);
    if(sd ==-1)
        error_handling("socket() error");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sd,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("connect() error!");
    else
        cout<<"connected......";
    while((read_cnt=read(sd,buf,BUF_SZIE))!=0)//read가 실패할때까지 계속 BUF_SIZE만큼 읽어온다
    {
        //버퍼,한번에가져올 데이터크기,반복횟수(당연히 읽어온데이터 크기만큼),FILE* 변수
        //버퍼에 담긴 내용을 1바이트씩 read_cnt번만큼 fp 에 작성한다.
        fwrite((void*)buf,1,read_cnt,fp);
    }
    cout<<"Received file data"<<endl;//작성완료 메시지 보내기
    write(sd,"Thank you",10);//서버에 Thank you 보내기
    fclose(fp);//파일닫기
    close(sd);//소켓닫기
    return 0;    
    
    }
void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}