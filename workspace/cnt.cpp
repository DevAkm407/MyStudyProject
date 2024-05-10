// #include<iostream>
// #include<stdlib.h>
// #include<string>
// #include<string.h>
// #include<unistd.h>
// #include<arpa/inet.h>
// #include<sys/socket.h>
// using namespace std;
// void error_handling(string message);

// int main(int argc, char *argv[])
// {
//     int sock;
//     int clnt_sock;
//     sockaddr_in serv_addr;
//     char message[30];
//     int str_len;
    
//     if(argc !=3)
//     {
//         cout << "Usage : " << argv[0] << " <IP> <port>\n";
//         exit(1);
//     }

//    sock=socket(PF_INET,SOCK_STREAM,0);
//     if(sock ==-1)
//         error_handling("socket() error");
    
//     memset(&serv_addr,0,sizeof(serv_addr));
//     serv_addr.sin_family=AF_INET;
//     serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
//     serv_addr.sin_port=htons(atoi(argv[2]));
    
//     if(connect(sock,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
//         error_handling("connect() error!");
    
//     str_len=read(sock,message,sizeof(message)-1);

//     if(str_len==-1)
//         error_handling("read() error!");
    
//     cout<<"Message from server: "<<message<<endl;
//     close(sock);
//     return 0;
    
    
    
//     }
// void error_handling(string message)
// {
//     cerr<<message<<endl;
//     exit(1);
// }
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
    int sock;
    int clnt_sock;
    sockaddr_in serv_addr;
    char message[30];
    int str_len=0;
    int read_len=0,idx =0;
    
    if(argc !=3)
    {
        cout << "Usage : " << argv[0] << " <IP> <port>\n";
        exit(1);
    }

   sock=socket(PF_INET,SOCK_STREAM,0); //ipv4 통신,tcp통신,기본 tcp
    if(sock ==-1)
        error_handling("socket() error");
    
    memset(&serv_addr,0,sizeof(serv_addr));//socket_in 안쪽 char 형태의 0을 무조건적으로 넣어주어야하기 때문에 사용(구조체 길이를 맞추기위해서)
    serv_addr.sin_family=AF_INET;   //ipv4사용
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);// 메인에서 입력한 서버 ip문자열을 net프로토콜에 맞게 설정
    serv_addr.sin_port=htons(atoi(argv[2]));//메인에서 입력한 port 번호를 프로토콜에 맞게 변환  
    
    if(connect(sock,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)//클라이언트 소켓에 서버를 연결
        error_handling("connect() error!");
    
    while (read_len=read(sock,&message[idx++],1))//소켓에서 읽어온 데이터의 길이 측정,message에는 해당 데이터를 읽음(반복한번에 1개의 char을 읽어옴)
    {
        if(read_len==-1)
            error_handling("read() error!");

        str_len+=read_len;
    }
    

    if(str_len==-1)
        error_handling("read() error!");
    
    cout<<"Message from server: "<<message<<endl; //읽어온 문자열 출력
    cout<<"Function read call count "<<str_len<<endl;//읽어온 문자열 길이 출력
    close(sock); //소켓 제거
    return 0;
    
    
    
    }
void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}