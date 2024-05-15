#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include<sstream>
#define BUF_SIZE 100
#define NAME_SIZE 20
using namespace std;
void* send_msg(void * arg); //쓰레드로 사용하는  함수는 void* 함수이름(void* 매개변수) 형식을 반드시 맞춰주어야한다
void* recv_msg(void * arg);
void * rent_msg(void * arg);
void error_handling(string message);
void * back_msg(void * arg);
// char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];
// char name[NAME_SIZE]="[DEFAULT]";

int main(int argc,char* argv[])
{
    int sock;
    sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void * thread_return;
    
    if(argc!=3)// ip port번호 닉네임을 실행과정에서 입력해주어야함
    {
        cout<<"Usage: "<<argv[0] <<" <IP> <port> <name>\n";
        exit(1);
    }
    // name=argv[3];
    // sprintf(name,"[%s]",argv[3]);//name에 실행과정에서 입력한 닉네임을 저장함 [닉네임]형식으로
    sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("connect() error");
    
    send_msg((void*)&sock);
    // pthread_create(&snd_thread,NULL,send_msg,(void*)&sock); //메세지보내는 함수를 쓰레드로 전환 쓰레드에게 매개변수로 보낼 데이터로 소켓의 파일디스크립터를 보냄
    
    pthread_create(&rcv_thread,NULL,recv_msg,(void*)&sock); //메세지 받는 함수를 쓰레드로 전환 쓰레드에게 매개변수로 보낼 데이터로 소켓의 파일디스크립터를 보냄
    
    rent_msg((void*)&sock);

    
    
    back_msg((void*)&sock);
    // pthread_join(snd_thread,&thread_return); //join으로 thread_return이라는 변수로 thread의 반환값을 가져옴 현재 프로세스에선 사용되지 않음
    
    pthread_join(rcv_thread,&thread_return); //join으로 thread_return이라는 변수로 thread의 반환값을 가져옴 현재 프로세스에선 사용되지 않음
    sleep(2);
    close(sock);    
    return 0;
}



void * send_msg(void * arg)
{
    
    int sock=*((int*)arg);
    char name_msg[BUF_SIZE+NAME_SIZE]="3,";
    string c;
    ostringstream oss;
    oss<<name_msg;
    // cout<<"이름을 입력해주세요";
    // getline(cin,c);
    // oss<<c<<",";
    // cout<<"주소을 입력해주세요";
    // getline(cin,c);
    // oss<<c<<",";
    cout<<"id을 입력해주세요";
    getline(cin,c);
    oss<<c<<",";
    cout<<"pw을 입력해주세요";
    getline(cin,c);
    oss<<c<<",";
    // cout<<"pnum을 입력해주세요";
    // getline(cin,c);
    // oss<<c;
    c=oss.str();
    c.copy(name_msg,c.length( ));
    
    // sprintf(name_msg,"%s %s",name,msg);//printf 에서 화면에 출력하는 대신에 화면에 출력할 문자열을 인자로 지정한 문자열에 쓰는 함수 이 부분에선 name + msg를 name_msg로 넣는다.
    
    write(sock,name_msg,strlen(name_msg));
    
    // write(sock,name_msg,strlen(name_msg));//" [닉네임] 메시지 " 형식으로 데이터쓰기
    
    return NULL;

}



void * rent_msg(void * arg)
{
    
    int sock=*((int*)arg);
    char name_msg[BUF_SIZE+NAME_SIZE]="4,";
    string c;
    ostringstream oss;
    oss<<name_msg;
    // cout<<"이름을 입력해주세요";
    // getline(cin,c);
    // oss<<c<<",";
    // cout<<"주소을 입력해주세요";
    // getline(cin,c);
    // oss<<c<<",";할
    cout<<"책코드를 입력해주세요";
    getline(cin,c);
    oss<<c<<",";
    // cout<<"pw을 입력해주세요";
    // getline(cin,c);
    // oss<<c<<",";
    // cout<<"pnum을 입력해주세요";
    // getline(cin,c);
    // oss<<c;
    
    c=oss.str();
    
    c.copy(name_msg,c.length( ));    
    
    // sprintf(name_msg,"%s %s",name,msg);//printf 에서 화면에 출력하는 대신에 화면에 출력할 문자열을 인자로 지정한 문자열에 쓰는 함수 이 부분에선 name + msg를 name_msg로 넣는다.
    
    write(sock,name_msg,strlen(name_msg));
    
    // write(sock,name_msg,strlen(name_msg));//" [닉네임] 메시지 " 형식으로 데이터쓰기
    
    return NULL;
}

void * back_msg(void * arg)
{
    
    int sock=*((int*)arg);
    char name_msg[BUF_SIZE+NAME_SIZE]="5,";
    string c;
    ostringstream oss;
    oss<<name_msg;
    // cout<<"이름을 입력해주세요";
    // getline(cin,c);
    // oss<<c<<",";
    // cout<<"주소을 입력해주세요";
    // getline(cin,c);
    // oss<<c<<",";할
    cout<<"반납할 책코드를 입력해주세요";
    getline(cin,c);
    oss<<c<<",";
    // cout<<"pw을 입력해주세요";
    // getline(cin,c);
    // oss<<c<<",";
    // cout<<"pnum을 입력해주세요";
    // getline(cin,c);
    // oss<<c;
    
    c=oss.str();
    
    c.copy(name_msg,c.length( ));    
    
    // sprintf(name_msg,"%s %s",name,msg);//printf 에서 화면에 출력하는 대신에 화면에 출력할 문자열을 인자로 지정한 문자열에 쓰는 함수 이 부분에선 name + msg를 name_msg로 넣는다.
    
    write(sock,name_msg,strlen(name_msg));
    
    // write(sock,name_msg,strlen(name_msg));//" [닉네임] 메시지 " 형식으로 데이터쓰기
    
    return NULL;
}


void * recv_msg(void * arg)
{
    
    int sock=*((int*)arg);
    char name_msg[NAME_SIZE+BUF_SIZE];
    int str_len;
    while (1)
    {
        str_len=read(sock,name_msg,(NAME_SIZE+BUF_SIZE-1));//서버에서 오는 데이터크기 버퍼만큼 맞춰주는 부분
        
        if(str_len==-1)
            return (void *)-1; //실패시 EOF 반환
        
        name_msg[str_len]='\0'; //name_msg보다 짧은 부분은 \0처리로 문자열의 끝을 알리기
        
        cout<<name_msg<<endl;
    }    
    return NULL;
}


void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}