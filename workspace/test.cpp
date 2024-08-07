#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<sstream>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<fcntl.h>
#define BUF_SZIE 1024
using namespace std;
// struct chatingparts
// {
//     int socks[30];
//     int len;
// };
struct threadControl
{
    int sock;
    int* state;
    int* chat;
};

void error_handling(string message);
void* seread(void*args);
void choice(const int& sock);
void menu(threadControl* tc,int choice1);
int login(int sock);
void checkFriendRequest(int sock);
void registFriend(int sock);
void signup(int sock);
void rejectFriend(int sock);
void shootFriend(int sock);
void ranchat(int sock);
int loginfali(int sock);
// void* chatreadmsg(void* arg);
// void* chatwritemsg(void* arg);
// chatingparts my;
pthread_mutex_t mutx;
int logincount=0;
int main(int argc, char *argv[])
{
    int sock;
    pthread_mutex_t mutx;
    sockaddr_in serv_addr;
    int loginstat=0;
    char* message=new char[BUF_SZIE];

    pthread_t t_id;
    int str_len=0;
    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock ==-1)
        error_handling("socket() error");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_addr.sin_port=htons(atoi("10001"));
    if(connect(sock,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("connect() error!");
    else
        cout<<"connected......\n";
    int chatcase=0;
    
    threadControl tc{
        tc.sock=sock,
        tc.state=&loginstat,
        tc.chat=&chatcase
    };
    pthread_create(&t_id,NULL,seread,(void*)&tc);//쓰레드 id하나로 클라이언트 수만큼 쓰래드를 생성해주는 부분 클라이언트는 1개의 전용 쓰래드를 할당받음 
    pthread_detach(t_id);//할당한 쓰래드를 프로세스 종료와 함께 종료시키거나 클라이언트가 종료하면 자동으로 쓰레드가 종료되게 때어냄
    // if(argc !=3)
    // {
    //     cout << "Usage : " << argv[0] << " <IP> <port>\n";
    //     exit(1);
    // }
   string kk; 
   while (1)
   {
    
    
    // if(loginstat==0)
    //     choice(sock);
    // else
    // {
    //     if(chatcase!=1)
    //     {
        // menu(&tc,atoi(&message[0]));
        // }
        // else
        // {

        // }
        memset(message,0,BUF_SZIE);
        getline(cin,kk);
        kk.copy(message,kk.length());     
        write(sock,message,kk.length());
    //     if(message[0]=='`')
    //     {
    //         chatcase=0;
    //     }   
    // }        
   }
    close(sock);
    return 0;
}

/*A 회원가입  B 로그인 C 친구 목록 조회 D 채팅 요청 함수 E 채팅방 참여함수 F 친구추가 G 친구 신청 목록 확인  H 친구 수락  I 친구 거절 */

int login(int sock)
{
    ostringstream oss;
    string k;
    string a;
    int len;
    char msg[BUF_SZIE];
    oss<<"B ";
    cout<<"ID를 입력해주세요."<<endl;
    getline(cin,k);
    oss<<k<<" ";
    cout<<"PW(비밀번호)를 입력해주세요."<<endl;
    getline(cin,k);
    oss<<k<<" ";
    a=oss.str();
    a.copy(msg,a.length());
    write(sock,msg,a.length());
    memset(msg,0,BUF_SZIE);    
    usleep(10000);
    return 0;
    
}


void signup(int sock)
{
    ostringstream oss;
    string k;
    string a;
    int len;
    char msg[BUF_SZIE];
    oss<<"A ";
    cout<<"이름을 입력해주세요."<<endl;
    getline(cin,k);
    oss<<k<<" ";
    cout<<"낙네임를 입력해주세요."<<endl;
    getline(cin,k);
    oss<<k<<" ";
    cout<<"ID를 입력해주세요."<<endl;
    getline(cin,k);
    oss<<k<<" ";
    cout<<"비밀번호를 입력해주세요."<<endl;
    getline(cin,k);
    oss<<k<<" ";
    a=oss.str();
    a.copy(msg,a.length());
    write(sock,msg,a.length());
    memset(msg,0,BUF_SZIE);    
    usleep(10000);
    return ;
}

int loginfali(int sock)
{
    ostringstream oss;
    string k;
    string a;
    int len;
    char msg[BUF_SZIE];
    oss<<"B ";
    puts("ID를 입력해주세요.");
    getline(cin,k);
    oss<<k<<" ";
    puts("PW(비밀번호)를 입력해주세요.");
    getline(cin,k);
    oss<<k<<" ";
    puts("고유번호를 입력해주세요.");
    getline(cin,k);
    oss<<k<<" ";
    a=oss.str();
    a.copy(msg,a.length());
    write(sock,msg,a.length());
    memset(msg,0,BUF_SZIE);    
    usleep(10000);
    return 0;
}


void findMyFriend(int sock)
{
    char msg[BUF_SZIE]="C\0";
    int len;
    puts("현재 접속한 나의 친구입니다.");
    write(sock,msg,3);
    memset(msg,0,BUF_SZIE);
}

void startChat(int sock)
{
    ostringstream oss;
    string k,a;
    oss<<"D ";
    findMyFriend(sock);
    puts("접속한 친구(고유) 번호를 입력해주세요.");
    getline(cin,k);
    oss<<k<<" ";
    while (1)
    {
        puts("다른 친구도 초대할까요? y or n");
        getline(cin,k);
        if(k.compare("y")==0||k.compare("Y")==0||k.compare("yes")==0||k.compare("YES")==0||k.compare("ok")==0||k.compare("o")==0||k.compare("O")==0||k.compare("OK")==0)
        {
            puts("고유 번호를 입력해주세요.");
            getline(cin,k);
            oss<<k<<" ";
        }
        else if(k.compare("n")==0||k.compare("N")==0||k.compare("no")==0||k.compare("NO")==0||k.compare("nop")==0||k.compare("x")==0||k.compare("X")==0)
        {
            puts("친구를 초대합니다.");
            break;
        }
        else
        {
            puts("다시 입력해 주세요");
        }
    }
    a=oss.str();
    char msg[BUF_SZIE];
    a.copy(msg,a.length());
    write(sock,msg,a.length());
}

void choice(const int& sock)
{
    int choice1=0;
    puts("옵션을선택해주세요 1.회원가입 2.로그인");
    cin>>choice1;
    getchar();
    switch (choice1)
    {
    case 1:
        signup(sock);
        break;
    case 2:    
        if(logincount<5)
        { 
        login(sock);
        logincount++;
        }
        else
        {
        loginfali(sock);
        }
    break;
    
    default:
        break;
    }
    
}
 
/*1번 접속한 친구목록 2번 채팅시작 3번 친구 추가 4번 친구요청란확인 5번 친구등록 6번 친구요청삭제*/
void menu(threadControl* tc,int choice1)
{   
    int sock=tc->sock;
    if(*tc->chat==0||*tc->chat==2){    
        switch (choice1)
        {
        case 1:
            findMyFriend(sock);
            
            break;
        case 2:
            startChat(sock);
            
            break;
        case 3:
            shootFriend(sock);
            *tc->chat=1;
            break;
        case 4:
            checkFriendRequest(sock);

            break;
        case 5:
            registFriend(sock);
            break;    
        case 6:
            rejectFriend(sock);
            break;
        case 7:
            ranchat(sock);
            *tc->chat=1;
            break;
        default:
            break;
        }
    puts("1번 접속한 친구목록 2번 채팅시작 3번 친구 추가 4번 친구요청란확인 5번 친구등록 6번 친구요청삭제 7번 랜덤채팅");
    }
}

void ranchat(int sock)
{
    char c[3]="J\0";
    write(sock,c,sizeof(char)*3);
}


void checkFriendRequest(int sock)
{
    char msg[3]="G\0";
    int len;
    write(sock,msg,sizeof(char)*3);
    memset(msg,0,3);
}

//친구 수락
void registFriend(int sock)
{
    ostringstream oss;
    string k,a;
    int len;
    oss<<"H ";
    // checkFriendRequest(sock);
    puts("수락할 친구(고유) 번호를 입력해주세요.");
    getline(cin,k);
    oss<<k<<" ";
    while (1)
    {
        puts("다른 사람도 수락할까요? y or n");
        getline(cin,k);
        if(k.compare("y")==0||k.compare("Y")==0||k.compare("yes")==0||k.compare("YES")==0||k.compare("ok")==0||k.compare("o")==0||k.compare("O")==0||k.compare("OK")==0)
        {
            puts("고유 번호를 입력해주세요.");
            getline(cin,k);
            oss<<k<<" ";
        }
        else if(k.compare("n")==0||k.compare("N")==0||k.compare("no")==0||k.compare("NO")==0||k.compare("nop")==0||k.compare("x")==0||k.compare("X")==0)
        {
            break;
        }
        else
        {
            puts("다시 입력해 주세요");
        }
    }
    a=oss.str();
    char msg[BUF_SZIE];
    a.copy(msg,a.length());
    write(sock,msg,a.length());
    memset(msg,0,BUF_SZIE);
    puts("수락되었습니다");
}


//친구 거절
void rejectFriend(int sock)
{
    ostringstream oss;
    string k,a;
    int len;
    // checkFriendRequest(sock);
    oss<<"I ";
    puts("거절할 친구(고유) 번호를 입력해주세요.");
    getline(cin,k);
    oss<<k<<" ";
    while (1)
    {
        puts("다른 사람도 거절할까요? y or n");
        getline(cin,k);    
        if(k.compare("y")==0||k.compare("Y")==0||k.compare("yes")==0||k.compare("YES")==0||k.compare("ok")==0||k.compare("o")==0||k.compare("O")==0||k.compare("OK")==0)
        {
            puts("고유 번호를 입력해주세요.");
            getline(cin,k);
            oss<<k<<" ";
        }
        else if(k.compare("n")==0||k.compare("N")==0||k.compare("no")==0||k.compare("NO")==0||k.compare("nop")==0||k.compare("x")==0||k.compare("X")==0)
        {
            break;;
        }
        else
        {
            puts("다시 입력해 주세요");
        }
    }
    a=oss.str();
    char msg[BUF_SZIE];
    a.copy(msg,a.length());
    write(sock,msg,a.length());
    memset(msg,0,BUF_SZIE);
    puts("거절이완료되었습니다");
}

//친구추가
void shootFriend(int sock)
{
    ostringstream oss;
    string k,a;
    int len;
    // checkFriendRequest(sock);
    oss<<"F ";
    puts("친구추가할 친구(고유) 번호를 입력해주세요.");
    getline(cin,k);
    oss<<k<<" ";
    while (1)
    {
        puts("다른 사람도 추가할까요? y or n");
        getline(cin,k);    
        if(k.compare("y")==0||k.compare("Y")==0||k.compare("yes")==0||k.compare("YES")==0||k.compare("ok")==0||k.compare("o")==0||k.compare("O")==0||k.compare("OK")==0)
        {
            puts("고유 번호를 입력해주세요.");
            getline(cin,k);
            oss<<k<<" ";
        }
        else if(k.compare("n")==0||k.compare("N")==0||k.compare("no")==0||k.compare("NO")==0||k.compare("nop")==0||k.compare("x")==0||k.compare("X")==0)
        {
            break;;
        }
        else
        {
            puts("다시 입력해 주세요");
        }
    }
    a=oss.str();
    char msg[BUF_SZIE];
    a.copy(msg,a.length());
    write(sock,msg,a.length());
    memset(msg,0,BUF_SZIE);
}

void* seread(void*arg)
{

threadControl *tc=(threadControl*)arg;
int clnt_sock=tc->sock;
char* msg=new char[BUF_SZIE];
int* ren=new int;
string k; 
while(1)
{

*ren=read(clnt_sock,msg,BUF_SZIE);
msg[*ren]=0;
puts(msg);
if(atoi(&msg[0])==1)
    *tc->state=1;

if(atoi(&msg[0])==5)
{
  
    memset(msg,0,BUF_SZIE);
    msg[0]='E';
    msg[2]=' ';
    msg[3]='\0';    
    write(clnt_sock,msg,BUF_SZIE);
    *tc->chat=1;
}
if(msg[0]==':')
{
    memset(msg,0,BUF_SZIE);
    msg[0]='J';
    msg[2]=' ';
    msg[3]='\0';    
    write(clnt_sock,msg,BUF_SZIE);
    usleep(200);
    *tc->chat=1;
}    
}
delete msg;
delete ren;
memset(msg,0,BUF_SZIE);
return NULL;
}

// void* chatreadmsg(void* arg)
// {
//     threadControl my=*(threadControl*)arg;
//     int clnt_sock=my.sock;
//     char* msg=new char[BUF_SZIE];
//     int ren; 
//     while (1)
//     {
//         ren=read(clnt_sock,msg,BUF_SZIE);
//         msg[ren]=0;
//         if(*my.state==0)
//             break;
//         puts(msg);
//         memset(msg,0,BUF_SZIE);    
//     }
// delete msg;    
// return NULL;
// }

// void* chatwritemsg(void* arg)
// {
//     threadControl* my=(threadControl*)arg;
//     char message[BUF_SZIE];
//     int sock=my->sock;

//     if(loginstat==0)
//         choice(sock);
//     else
//     {
//         if(*tc.chat!=1)
//         {
//             menu(&tc,atoi(&message[0]));
//         }
//         else
//         {

//         }
//         memset(message,0,BUF_SZIE);
//         getline(cin,kk);
//         kk.copy(message,kk.length());
//         if(kk.compare("채팅 수락")==0)
//         {
//             *tc.chat=1;
//         }
//         else
//         {
//             *tc.chat=2;
//         }        
//         write(sock,message,kk.length());   
//     }    
// return NULL;
// }





void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}