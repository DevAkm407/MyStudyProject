#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/epoll.h>
#include"chatserver.hpp"
#include<unordered_map>
#define BUF_SZIE 1024
#define MAX_CLNT 256
#define EPOLL_SIZE 50
using namespace std;
struct chatingparts
{
    int socks[30];
    
    int len;
};
void * handle_clnt(void* arg);
chatingparts oneread_oneread(string msg);
void chat_msg(string clnts,char * msg, int len);
void gosock(chatingparts my);
void send_msg(char * msg, int len);
void error_handling(string message);
void send_clnt(string msg,int sock);
void* chatingroom(void* socks);
string findonlinefriend(string msg);
string splitchatmsg(string msg);
void chatprotocol(int checkf,int clnt_sock,int* login,chatserver* my,char msg[BUF_SZIE],string* aka,int* status);
int plzone_one(int* login,chatingparts my);
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
unordered_map<int,int> clnt_fid;
pthread_mutex_t mutx;

int main(int argc,char *argv[])
{
    int serv_sock,clnt_sock;
    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    pthread_t t_id;
    if(argc!=2)
    {
        cout<<"Usage : "<<argv[0] <<" <prot>\n";
        exit(1);
    }
    memset(clnt_socks,0,MAX_CLNT*2);
    pthread_mutex_init(&mutx,NULL);
    serv_sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr)))
        error_handling("bind() error");
    if(listen(serv_sock,5)==-1)
        error_handling("listen() error");
    while (1)
    {
        clnt_adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz);

        pthread_mutex_lock(&mutx);//handle_cnt에서 순서를 정렬할때 새로들어오는것을 막아주기위해 lock 함
        clnt_socks[clnt_cnt++]=clnt_sock;
        pthread_mutex_unlock(&mutx);
        pthread_create(&t_id,NULL,handle_clnt,(void*)&clnt_sock);//쓰레드 id하나로 클라이언트 수만큼 쓰래드를 생성해주는 부분 클라이언트는 1개의 전용 쓰래드를 할당받음 
        pthread_detach(t_id);//할당한 쓰래드를 프로세스 종료와 함께 종료시키거나 클라이언트가 종료하면 자동으로 쓰레드가 종료되게 때어냄
        puts("Connected client IP: ");
        puts(inet_ntoa(clnt_adr.sin_addr));
    }
    close(serv_sock);
    return 0;
}



void* handle_clnt(void* arg)
{
    int clnt_sock=*((int*)arg);
    int i;
    int* status=new int;
    int * str_len=new int;
    int* login=new int;
    char* msg=new char[BUF_SZIE];
    chatserver* my =new chatserver;
    string* aka=new string;
    while ((*str_len=read(clnt_sock,msg,BUF_SZIE))!=0)
    {              
    
        if(*status==1)
                continue;
            msg[*str_len]=0;
            // puts(msg);
            chatprotocol(atoi(&msg[0]),clnt_sock,login,my,msg,aka,status);
    }
    pthread_mutex_lock(&mutx);//만약 다른 클라이언트가 비슷한 시기에 접속을 종료했다면 밑에 for문이 돌기전에 진입하게된다.그렇게되면 소켓번호를
    for ( i = 0; i <clnt_cnt ; i++)//재정렬하는 과정에서 하나가 또 지워지거나 정렬하고 있는거 또 정렬해서 순번이 꼬이는 사건이 발생할 수 있다. 그 사건을 막기위한 lock
    {
        if(clnt_sock==clnt_socks[i])
        {
            while (i++< clnt_cnt-1)
                clnt_socks[i]=clnt_socks[i+1]; //i번째를 탈락시켰기 때문에 i번째 소켓을 i+1번째로 한칸 씩 덮어쒸운다.
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutx);//모든 정렬이 끝나고나서 unlock
    clnt_fid.erase(*login);
    delete str_len;
    delete login;
    delete msg; 
    close(clnt_sock);
    return NULL;
}

//사용자가 채팅을 요청했을때 socket을 묶어주는 함수 sock을 반드시 delete할것 실패시 NULL 반환 성공시 클라이언트 소켓배열 반환 크기는 int*2 
chatingparts oneread_oneread(string msg)
{
    string mssg;
    mssg=splitchatmsg(msg);
    stringstream ssg(mssg);
    string buffer;
    chatingparts my;
    unordered_map<int,int>::iterator ater;
    int* sock=new int[2];
    memset(sock,0,sizeof(int)*2);
    ssg>>sock[0]>>sock[1];
    
    ater=clnt_fid.find(sock[0]);
    sock[0]=ater->second;
    ater=clnt_fid.find(sock[1]);
    sock[1]=ater->second;
    my.socks[0]=sock[0];
    my.socks[1]=sock[1];
    my.len=2;
    return my;
}



//요청한 상대에게 대화 요청 보내기 수락하면 1 아니면 0
int plzone_one(int* login,chatingparts my)
{   
    ostringstream oss;
    string alk;
    int socks[2];
    socks[0]=my.socks[0];
    socks[1]=my.socks[1];
    int ren;
    oss<<"2, "<<*login<<"이 "<<"대화를 요청했습니다. 수락하려면 y 거절하려면 n";
    alk=oss.str();
    int* c = new int;
    char booksmsg[BUF_SZIE];
    alk.copy(booksmsg,alk.length());
    booksmsg[alk.length()+1]=0;

    write(socks[1],booksmsg,alk.length()+1);
    memset(booksmsg,0,BUF_SZIE);
    ren=read(socks[1],booksmsg,BUF_SZIE);
    booksmsg[ren]=0;
    alk=booksmsg;
    if(alk.compare("y"))
        return 1;
    delete c;   
    return 0;
}

void* okchatingroom(void* socks)
{
    int mysock=*(int*)socks;
    chatingparts* real=new chatingparts;
    int str_ren,i;
    string k;
    
    char* buffer = new char[BUF_SZIE];
    read(mysock,(void*)real,sizeof(chatingparts));    
    
       
    while ((str_ren=read(mysock,buffer,BUF_SZIE))!= -1)
    {
        buffer[str_ren]=0;
        for ( i = 0; i < real->len; i++)
        {
            write(real->socks[i],buffer,BUF_SZIE);
        }     
    }
    delete buffer;
    delete real;
    return NULL;
}
//채팅방 함수 msg를 통해 데이터가 들어오고 2명에게 모두 읽어온 데이터를 보냄
void* chatingroom(void* socks)
{
    chatingparts myparts=*(chatingparts*)socks;
    chatingparts* real=new chatingparts;
    epoll_event *epoll_events;
    epoll_event event;
    *real=myparts;
    int str_ren,i;
    int epfd,event_cnt;
    string k;
    char* buffer = new char[BUF_SZIE];
    for ( i = 0; i < real->len; i++)
    {
        event.events=EPOLLIN;
        event.data.fd=real->socks[i];
        epoll_ctl(epfd,EPOLL_CTL_ADD,real->socks[i],&event);
    }
    

    while (1)
    {
        for ( i = 0; i < event_cnt; i++)
        {
            str_ren=read(event[i])
        }
        

    }
    delete buffer;
    delete real;
    return NULL;
} 

void send_clnt(string msg,int sock)
{   
    istringstream iss(msg);
    string mmsg;
    int* c = new int;
    char booksmsg[BUF_SZIE];
    memset(booksmsg,0,BUF_SZIE);
    while (getline(iss,mmsg))
    {
        mmsg=mmsg+"\n";
        mmsg.copy(booksmsg,mmsg.length());
        write(sock,booksmsg,mmsg.length());
        memset(booksmsg,0,BUF_SZIE);
    }  
    
    delete c;   
}


void chatprotocol(int checkf,int clnt_sock,int* login,chatserver* my,char msg[BUF_SZIE],string* aka,int* status)
{
    string copy=msg;
    pthread_t t_id;
    cout<<copy<<endl;
    string k,z;
    int uyt;
    void* ga;
    chatingparts sock;
    switch (checkf)
    {
    case 1:
        /*회원가입*/
        memset(msg,0,BUF_SZIE);
        break;
    case 2:
        /*로그인*/
        *login=my->getlogin(copy);
        usleep(100);
        if(*login !=0)
        {
            *aka=my->aka;
            k="로그인 성공";
            clnt_fid.insert(pair<int,int>(*login,clnt_sock));
            send_clnt(k,clnt_sock);
            puts("로그인성공!");
            memset(msg,0,BUF_SZIE);
            break;        
        }
        puts("로그인 실패");
        k="로그인 실패";
        send_clnt(k,clnt_sock);
        cout<<*login<<endl;
        memset(msg,0,BUF_SZIE);
        break;
    case 3:
        /*친구목록조회*/
        puts("들어옴");
        k=my->showMyFriend();
        z=findonlinefriend(k);
        cout<<k;
        send_clnt(z,clnt_sock);
        memset(msg,0,BUF_SZIE);
        break;
    case 4:
        /*1:1채팅요청함수*/
        sock=oneread_oneread(copy);
        uyt=plzone_one(login,sock);
        cout<<uyt<<endl;
        
        if(uyt==1)
        {
           gosock(sock);
           *status=1;
           pthread_create(&t_id,NULL,chatingroom,(void*)&sock);
           pthread_detach(t_id);
        }
            
        memset(msg,0,BUF_SZIE);
        break;
    
    case 5:

        pthread_create(&t_id,NULL,okchatingroom,(void*)&clnt_sock);
        pthread_detach(t_id);
        memset(msg,0,BUF_SZIE);
        break;
    
    case 6:
         
        memset(msg,0,BUF_SZIE);
        break;            
    
    default:
        memset(msg,0,BUF_SZIE);
        break;
    }
}

//앞에 숫자 때어버리기
string splitchatmsg(string msg)
{
    string buffer=msg;
    buffer=buffer.substr(buffer.find(" "));
    return buffer;
}

void gosock(chatingparts my)
{    
    for (int i = 0; i < my.len; i++)
    {
        write(my.socks[i],(void*)&my,sizeof(chatingparts));
    }   
}

void chat_msg(string clnts,char * msg, int len)
{
    istringstream iss(msg);
    string buffer;
    vector<string> myfriendfid;
    while (getline(iss,buffer,','))
    {
        myfriendfid.emplace_back(buffer);
    }
    vector<string>::iterator iter;
    int i;
    
    pthread_mutex_lock(&mutx);//모든 클라이언트들에게 메시지를 뿌리기전에  다시 for문을 돈다고 가정하면 다른 스레드가 i에 접근하게 되면서 i를
    //다시 0으로 만들어버리는 사태가 발생할 수 있고 메시지는 모든 클라이언트들에게 전달되지 못하고 후자로 들어온 메시지만 모두에게 전달될 가능성이 있다.
    
    for ( iter=myfriendfid.begin(); iter!=myfriendfid.end(); ++iter)
    {
        write(stoi(*iter),msg,len);
    }
    
    pthread_mutex_unlock(&mutx);//모든 메시지를 사용자에게 보내고 나서 언락을 풀어준다.

}

// void send_flist(string msg,int sock)
// {
    
//         char* mssg=new char[BUF_SZIE];
//         msg.copy(mssg,BUF_SZIE);
        
//         while(write(sock,mssg,BUF_SZIE)){}
//         delete mssg;
    
// }


//현재 접속한 친구를 출력해주는 함수 


string findonlinefriend(string msg)
{
    stringstream iss(msg);
    ostringstream oss;
    string buffer;
    string fid[2];
    unordered_map<int,int>::iterator iter;
    oss<<"현재 접속한 친구는:\n";
    while(iss>>fid[0]>>fid[1])
    {
        iter=clnt_fid.find(stoi(fid[0]));
        if(iter!=clnt_fid.end())
            oss<<"고유번호: "<<fid[0]<<" 닉네임: "<<fid[1]<<"\n";
        iter=clnt_fid.end();
    }
    return oss.str();
}


void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}