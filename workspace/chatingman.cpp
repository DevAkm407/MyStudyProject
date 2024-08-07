#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <pthread.h>
#include <sys/epoll.h>
#include"chatserver.hpp"
#include "clntclass.hpp"
#include<unordered_map>
#define BUF_SZIE 1024
#define MAX_CLNT 256
using namespace std;
struct chatingparts
{
    int socks[30];
    
    int len;
};

struct randchat
{
    int randsocks[30];
    int mathedman[2];
    bool mathedstatus;
    int len;
};

void * handle_clnt(void* arg);
void oneread_oneread(int mysock,string msg);
void okchatingroom(int socks);
void chat_msg(string clnts,char * msg, int len);
void error_handling(string message);
void send_clnt(string msg,int sock);
int ranyou(int mysock);
void renchatchober(int sock);
string findonlinefriend(string msg);
string splitchatmsg(string msg);
void rnchatingroom(int socks,int you);
string shootFriend(int& login,string msg,chatserver* my);
void aptfriend(int& login,string msg,chatserver* my);
void chatprotocol(char checkf,int clnt_sock,int* login,chatserver* my,char msg[BUF_SZIE],string* aka,int* status,CHAT*);
int plzone_one(int* login,chatingparts my);
void* inviteFriend(void* arg);
void watingcs(string aka,int socks);
void* matching(void* arg);
void rejectfriend(int& login,string msg,chatserver* my);
chatingparts sock_clnt;
randchat rc;
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
unordered_map<int,int> clnt_fid;
unordered_map<int,string> clnt_aka;
unordered_map<string,int> waitqna;
unordered_map<string,int> goqna;
pthread_mutex_t mutx;


int main(int argc,char *argv[])
{
    signal(SIGPIPE,SIG_IGN);
    rc.len=0;
    int serv_sock,clnt_sock;
    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    pthread_t t_id;
    srand(time(NULL));
    // if(argc!=2)
    // {
    //     cout<<"Usage : "<<argv[0] <<" <prot>\n";
    //     exit(1);
    // }
    memset(clnt_socks,0,MAX_CLNT*2);
    pthread_mutex_init(&mutx,NULL);
    serv_sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi("10001"));

    if(bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr)))
        error_handling("bind() error");
    if(listen(serv_sock,5)==-1)
        error_handling("listen() error");
    
    pthread_create(&t_id,NULL,matching,(void*)&clnt_sock);
    pthread_detach(t_id);
    while (1)
    {
        clnt_adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz);// 채팅을하는 소켓은 3번 db를 보는 소켓은 4번
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
    CHAT* hb=new CHAT;
    string* aka=new string;
    while ((*str_len=read(clnt_sock,msg,BUF_SZIE))!=0)
    {                 
        if(*status==1){
            continue;
        }
        msg[*str_len]=0;
        // puts(msg);
        chatprotocol(msg[0],clnt_sock,login,my,msg,aka,status,hb);
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

//사용자가 채팅을 원하는 사람을 보내면 그만큼을 구조체에 할당 그리고 그길이도 할당
void oneread_oneread(int login,string msg)
{
    string mssg;
    mssg=splitchatmsg(msg);
    stringstream ssg(mssg);
    string buffer;
    unordered_map<int,int>::iterator ater;
    int socks[30];
    int count =1;
    socks[0]=login;
    pthread_mutex_lock(&mutx);
    // ssg>> socks[0]>>socks[1];
    while (ssg >> socks[count])
    {
        count++;
    }
    
    for (int i = 0; i < count; i++)
    {
        ater=clnt_fid.find(socks[i]);
        sock_clnt.socks[i]=ater->second;    
    }
     sock_clnt.len=count; 
    pthread_mutex_unlock(&mutx);
}

void renchatchober(int sock)
{
    rc.randsocks[rc.len]=sock;
    rc.len++;
}

void* matching(void* arg)
{
    int* ranum=new int;
    int* rranum=new int;
    while (1)
    {
    if(rc.len>=2)
    {
       *ranum=rand()%rc.len;
       *rranum=rand()%rc.len;
       if(*ranum!=*rranum)
       {
        rc.mathedman[0]=rc.randsocks[*ranum];
        rc.mathedman[1]=rc.randsocks[*rranum];
        rc.mathedstatus=true;
        sleep(3);
       }
    }
    else{
        rc.mathedstatus=false;
    }
    }
    return NULL;

}



//요청한 상대에게 대화 요청 보내기 수락하면 1 아니면 0
int plzone_one(int* login,chatingparts my)
{   
    ostringstream oss;
    string alk;
    pthread_t t_id;
    int ren;
    unordered_map<int,string>::iterator iter;
    iter=clnt_aka.find(sock_clnt.socks[0]);

    // oss<<iter->second<<"님이 "<<"대화를 요청했습니다.\n수락하시려면 '채팅 수락'을 입력해주세요.";
    // alk=oss.str();
    // int* c = new int;
    // char booksmsg[BUF_SZIE];
    // alk.copy(booksmsg,alk.length());
    // booksmsg[alk.length()]=0;

    // for (int i = 1; i < sock_clnt.len; i++)
    // {
    //     write(sock_clnt.socks[i],booksmsg,alk.length());
    //     memset(booksmsg,0,BUF_SZIE);
    // }      
    char ch[10]="5\0";
    for (int j = 0; j < sock_clnt.len; j++)
    {
        write(sock_clnt.socks[j],ch,sizeof(char)*3);
    }   
               
    // delete c;   
    return 0;
}

int ChatThat(int* x,int len)
{
    unordered_map<int,int>::iterator iter;    
    int count=0;
    int socks[len];
    int users[len];
    //해당유저가 접속한 유저끼리만 연결될 수 있게 1차적으로 정렬해주기
    for (int i = 0; i < len; i++)
    {
        iter=clnt_fid.find(x[i]);
        if(iter!=clnt_fid.end())
        {
            socks[count]=iter->second;
            users[count]=iter->first;
            count++;
        }
    }
    

    /*이부분은 채팅의 참여할건지 안할건지 물어봐야하는 부분*/


    //길이를 보내는부분
    for (int j = 0; j < len; j++)
    {
        write(x[j],(void*)&len,sizeof(int));
    }


    //고유번호를 보내는 부분
    for (int i = 0; i < len; i++)
    {
        write(x[i],(void*)x,sizeof(int)*len);
    }


}


int ranyou(int mysock)
{
    int matchcount=0;
    int you;
    while (rc.mathedstatus==false)
    {
        
    }
    
    for (int i = 0; i < 2; i++)
    {
        if(mysock==rc.mathedman[i])
            matchcount++;
        else
            you=rc.mathedman[i];
    }
    if(matchcount==0)
        return -1;
    return you;
}


void rnchatingroom(int socks,int you)
{
    pthread_mutex_lock(&mutx);
    int mysock=socks;
    pthread_mutex_unlock(&mutx);
    string k,j,c;
    unordered_map<int,string>::iterator iter;
    iter=clnt_aka.find(mysock); //클라이언트 번호로 내 별명찾기
    k=iter->second; 
    int str_ren,i;
    int matchcount=0; 
    char* buffer = new char[BUF_SZIE];
    memset(buffer,0,BUF_SZIE);
    c="["+k+ "]" ; //내 별명 등록
    
    for (int i = 0; i < 2; i++)
    {
    
      j=c+"님이 입장했습니다.\n";
      j.copy(buffer,j.length());
      write(mysock,buffer,j.length());      
      write(you,buffer,j.length());      
      memset(buffer,0,BUF_SZIE);  
    
    }
    rc.len--;    

    while ((str_ren=read(mysock,buffer,BUF_SZIE))!= -1)
    {
      if(buffer[0]=='`')
      {
      
      j=c+"님이 퇴장했습니다.\n";
      j.copy(buffer,j.length());
      write(mysock,buffer,j.length());
      write(you,buffer,j.length());
      memset(buffer,0,BUF_SZIE);
      break;
      }
      
      j=c+" "+buffer;
      j.copy(buffer,j.length());
      buffer[j.length()]=0;
      write(mysock,buffer,j.length());
      write(you,buffer,j.length());
      memset(buffer,0,BUF_SZIE); 
    }

    k="다음대화상대를 찾으시겠습니까? y or n";
    k.copy(buffer,k.length());
    write(mysock,buffer,k.length());
    memset(buffer,0,BUF_SZIE);
    str_ren=read(mysock,buffer,BUF_SZIE);
    if(buffer[0]=='y')
    {
        memset(buffer,0,BUF_SZIE);
        buffer[0]=':';
        buffer[1]='\0';
        write(mysock,buffer,3);
    }

    delete buffer;
}


//클라이언트들에게 데이터 모두보내기 
void okchatingroom(int socks)
{
    pthread_mutex_lock(&mutx);
    int mysock=socks;
    chatingparts* real=new chatingparts;
    *real=sock_clnt;
    pthread_mutex_unlock(&mutx);
    string k,j,c;
    unordered_map<int,string>::iterator iter;
    iter=clnt_aka.find(mysock); //클라이언트 번호로 내 별명찾기
    k=iter->second; 
    int str_ren,i; 
    char* buffer = new char[BUF_SZIE];
    memset(buffer,0,BUF_SZIE);
    c="["+k+ "]" ; //내 별명 등록
    for (int i = 0; i < real->len; i++)
    {
      j=c+"님이 입장했습니다.\n";
      j.copy(buffer,j.length());
      write(real->socks[i],buffer,j.length());
      memset(buffer,0,BUF_SZIE);  
    }
    
    while ((str_ren=read(mysock,buffer,BUF_SZIE))!= -1)
    {
      if(buffer[0]=='`')
      {
      for ( i = 0; i < real->len; i++)
      {
      j=c+"님이 퇴장했습니다.\n";
      j.copy(buffer,j.length());
      write(real->socks[i],buffer,j.length());
      memset(buffer,0,BUF_SZIE);
      }
      break;
      }
      
      
      j=c+" "+buffer;
      j.copy(buffer,j.length());
      buffer[j.length()]=0;
      for ( i = 0; i < real->len; i++)
      {
        write(real->socks[i],buffer,j.length());
      }
       memset(buffer,0,BUF_SZIE);
    }
    delete buffer;
    delete real;
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

void chatprotocol(char checkf,int clnt_sock,int* login,chatserver* my,char msg[BUF_SZIE],string* aka,int* status,CHAT* hb)
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
    case 'A':
        /*회원가입*/
        copy=splitchatmsg(copy);
        k=hb->signUp(copy);
        k.copy(msg,k.length());
        write(clnt_sock,msg,k.length());
        memset(msg,0,BUF_SZIE);
        break;
    case 'B'://로그인하면 해쉬맵에 key:고유번호 , value: 소켓번호 , key:소켓번호,value:별명
        /*로그인*/
        copy=splitchatmsg(copy);
        if(hb->gettn()>5)
        {
            *login=hb->LoginFail(copy);
            if(*login=-1)
            {
                close(clnt_sock);
                break;
            }
        }
        else
        {
        cout<<copy<<endl;
        *login=hb->LoginSuccess(copy);
        }
        
        usleep(100);
        if(*login !=0)
        {
            *aka=hb->aka;
            my->login=*login;
            clnt_fid.insert(pair<int,int>(*login,clnt_sock));
            clnt_aka.insert(pair<int,string>(clnt_sock,*aka));
            k="1";
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
    case 'C':
        /*친구목록조회*/
        puts("들어옴");
        k=my->showMyFriend();
        z=findonlinefriend(k);
        cout<<k;
        send_clnt(z,clnt_sock);
        memset(msg,0,BUF_SZIE);
        break;
    case 'D':
        /*채팅요청함수*/
        *status=1;           
        oneread_oneread(*login,copy);//구조체에 클라이언트 소켓번호들 할당   
        uyt=plzone_one(login,sock);//클라이언트들에게 채팅요청보내기
        okchatingroom(clnt_sock);
        memset(msg,0,BUF_SZIE);
        *status=0;
        break;
    
    case 'E'://채팅요청한 친구의 수락을받으면 자동으로 5를 보내서 이쪽으로 할당됌
        /*채팅확인*/      
        *status=1;           
        okchatingroom(clnt_sock);//채팅방 참여
        memset(msg,0,BUF_SZIE);
        *status=0;
        break;
    case 'F':/*친구신청*/
        copy=splitchatmsg(copy);
        k=shootFriend(*login,copy,my);
        k.copy(msg,k.length());
        msg[k.length()]=0;
        write(clnt_sock,msg,k.length());
        memset(msg,0,BUF_SZIE);
        break;            
    case 'G':
         /*친구신청목록확인*/
        k=my->checkFriendRequest(*login);
        send_clnt(k,clnt_sock);
        memset(msg,0,BUF_SZIE);
        break;            
    case 'H':
        /*친수 수락*/
        copy=splitchatmsg(copy);
        aptfriend(*login,copy,my);       
        memset(msg,0,BUF_SZIE);
        break;
    case 'I':
        /*친구 거절*/
        copy=splitchatmsg(copy);
        rejectfriend(*login,copy,my);
        memset(msg,0,BUF_SZIE);
        break;
    case 'J':
        *status=1;
        renchatchober(clnt_sock);
        uyt=ranyou(clnt_sock);
        if(uyt==-1)
            break;
        rnchatingroom(clnt_sock,uyt);
        *status=0;
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

//친구를 한번에 여러명 수락할 수 있는기능
void aptfriend(int& login,string msg,chatserver* my)
{
    stringstream sss(msg);
    
    vector<int> myvec;
    
    int k;
    
    while (sss >>k)
    {
        myvec.emplace_back(k);
    }

    vector<int>::iterator iter;
    for ( iter =myvec.begin(); iter !=myvec.end(); ++iter)
    {
        my->registFriend(login,*iter);
    }
}


//친구 신청
string shootFriend(int& login,string msg,chatserver* my)
{
    stringstream sss(msg);
    ostringstream oss;
    vector<int> myvec;
    
    int k;
    
    while (sss >>k)
    {
        myvec.emplace_back(k);
    }

    vector<int>::iterator iter;
    for ( iter =myvec.begin(); iter !=myvec.end(); ++iter)
    {
       oss<<my->shoot(login,*iter);
    }
    return oss.str();
}

void rejectfriend(int& login,string msg,chatserver* my)
{
    stringstream sss(msg);
    
    vector<int> myvec;
    
    int k;
    
    while (sss >>k)
    {
        myvec.emplace_back(k);
    }

    vector<int>::iterator iter;
    for ( iter =myvec.begin(); iter !=myvec.end(); ++iter)
    {
        my->rejectFriend(login,*iter);
    }
}


//현재 접속한 친구를 출력해주는 함수 해쉬맵에서 검색함
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
    }
    return oss.str();
}

//qna시작
void chatqna(string aka,int mysock,int yoursock)
{
    char* buffer =new char[1024];
    string c="["+aka+ "]" ; //내 별명 등록
    string j=c+"님이 입장했습니다.\n";
      j.copy(buffer,j.length());
      write(yoursock,buffer,j.length());
      memset(buffer,0,BUF_SZIE);  
    int str_ren,i; 
    
    while ((str_ren=read(mysock,buffer,BUF_SZIE))!= -1)
    {
      if(buffer[0]=='`')
      {      
      j=c+"님이 퇴장했습니다.\n";
      j.copy(buffer,j.length());
      write(yoursock,buffer,j.length());
      memset(buffer,0,BUF_SZIE);
      break;
      }
      j=c+buffer;
      j.copy(buffer,j.length());
      write(yoursock,buffer,j.length());  
      write(mysock,buffer,j.length());    
    }
}

void selectcustomer(string csaka,string cusaka,int socks)
{
    unordered_map<string,int>::iterator iter;
    iter=waitqna.find(cusaka);
    int clssock=iter->second;
    goqna.insert(pair<string,int>(csaka,socks));
    waitqna.erase(cusaka);

}

void watingcs(string aka,int socks)
{
 char control[100];
 int len;
 waitqna.insert(pair<string,int>(aka,socks));
 while (len=read(socks,control,100))
 {
    if(control[0]=='#')
    {
        break;
    }    
    
    if(waitqna.find(aka)==waitqna.end())
    {
      //1:1채팅함수로 보내버려야함   
    
    return;
    }
    
 }
if(waitqna.find(aka)!=waitqna.end())
    waitqna.erase(aka);
}



void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}