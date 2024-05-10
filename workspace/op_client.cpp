#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SZIE 1024
#define RLT_SIZE 4
#define OPSZ 4
using namespace std;
void error_handling(string message);

int main(int argc, char *argv[])
{
    int sock;
    sockaddr_in serv_addr;
    char opmsg[BUF_SZIE];
    int result,open_cnt,i;
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
    else
        cout<<"connected......";
    cout<<"Operand count: ";
    cin >>open_cnt;
    opmsg[0]=(char)open_cnt;

    for ( i = 0; i < open_cnt; i++)
    {
        cout<<"Operand "<<i+1<<" :";
        scanf("%d",(int*)&opmsg[i*OPSZ+1]);
    }
    fgetc(stdin);
    cout <<"operator: ";
    cin>>&opmsg[open_cnt*OPSZ+1];
    //입력받은 opmsg를 서버로 보냄 그때 값은 입력받은 cnt를 이용해서 cnt*4+2 size로 데이터를 보내줌
    write(sock,opmsg,open_cnt*OPSZ+2); 
    //서버에서 데이터를 읽어옴 RLT_SIZE만큼 읽어옴 4바이트(int와 같은)
    read(sock,&result,RLT_SIZE);
    //읽어온 계산결과를 출력
    cout<<"Operation result: "<<result<<endl;
    close(sock);
    return 0;
    }

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}