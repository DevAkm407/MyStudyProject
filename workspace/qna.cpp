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
#include<chrono>
#include <ctime>
#include <pthread.h>
#include <sys/epoll.h>
#include"csinfo.hpp"
#include"customer_info.hpp"
#include<unordered_map>
#define BUF_SZIE 1024
#define MAX_CLNT 100
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

void* handle_clnt(void* arg);
void oneread_oneread(int mysock,string msg);
void okchatingroom(int socks);
void chat_msg(string clnts,char * msg, int len);
void error_handling(string message);
void send_clnt(string msg,int sock);
int ranyou(int mysock);
void renchatchober(int sock);
string findonlinefriend(string msg);
void chatqna(string aka,int mysock,int yoursock);
void chatqna(string csaka,string cusaka,int mysock,int yoursock);
string splitchatmsg(string msg);
void rnchatingroom(int socks,int you);
string shootFriend(int& login,string msg,chatserver* my);
void* QnAToFile_T(void* arg);
void aptfriend(int& login,string msg,chatserver* my);
void selectcustomer(string mysaka,string csaka,int socks);
void chatprotocol(char checkf,int clnt_sock,int* login,chatserver* my,King* king,char msg[BUF_SZIE],string* aka,int* status);
int plzone_one(int* login,chatingparts my);
void* inviteFriend(void* arg);
void watingcs(string aka,int socks);
void* matching(void* arg);
void* showcustomer(void* args);
void rejectfriend(int& login,string msg,chatserver* my);
chatingparts sock_clnt;
randchat rc;
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
unordered_map<int,int> clnt_fid;//고유번호->소켓
unordered_map<int,string> clnt_aka;//소켓->이름
unordered_map<string,int> waitqna;//고객이름->소켓
unordered_map<string,int> goqna;//cs이름->소켓
unordered_map<string,int> csonline;//cs들이 로그인하면 저장좀해야겠으

unordered_multimap<string,string> fileDriver;//파일을 위한 대화내용 연결 딕셔너리

pthread_mutex_t mutx;

//일단 딕셔너리를 이용하면 충분히 데이터를 취합할 수 있음 그러나 문제는 취합한 데이터의 순서가 맞지않을 가능성이 높음
//딕셔너리에 넣는다고해도 어떻게 처리할 것인지 고민해야함 일단 상담사의 이름으로 데이터를 저장하고 나중엔 어케 찾을거?
//일단 이중for문으로 데이터를 찾아서 합치는 과정을 하고 어떻게 데이터를 정렬할지 고민해야함 정렬한 다음 하... 고객이름이 소실되네 그러면
//cs이름 cus이름으로 키를 정하고 같은 키가 있는지 멀티맵에서 찾은다음 데이터를 합쳐주고 그 키들을 모두 제거 이걸 스레드로 처리하자
//채팅방이 한개도 아니고 여러개일탠대 그걸 어떻게 처리하고 관리해야하나


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

    // pthread_create(&t_id,NULL,matching,(void*)&clnt_sock);
    // pthread_detach(t_id);
    pthread_create(&t_id,NULL,QnAToFile_T,(void*)&clnt_sock);
    pthread_detach(t_id);
    pthread_create(&t_id,NULL,showcustomer,(void*)&clnt_sock);
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
    King* king =new King;
    string* aka=new string;
    unordered_map<string,int>::iterator iter;
    
    while ((*str_len=read(clnt_sock,msg,BUF_SZIE))!=0)
    {                 
        if(*status==1){
            continue;
        }
        msg[*str_len]=0;
        // puts(msg);
        chatprotocol(msg[0],clnt_sock,login,my,king,msg,aka,status);
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
    iter=waitqna.find(*aka);
    
    if(iter!=waitqna.end())
    {
        waitqna.erase(iter->first);
    }
    iter=csonline.find(*aka);
    if(iter!=csonline.end())
    {
        csonline.erase(*aka);
    }
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


// int ChatThat(int* x,int len)
// {
//     unordered_map<int,int>::iterator iter;    
//     int count=0;
//     int socks[len];
//     int users[len];
//     //해당유저가 접속한 유저끼리만 연결될 수 있게 1차적으로 정렬해주기
//     for (int i = 0; i < len; i++)
//     {
//         iter=clnt_fid.find(x[i]);
//         if(iter!=clnt_fid.end())
//         {
//             socks[count]=iter->second;
//             users[count]=iter->first;
//             count++;
//         }
//     }
        
//     /*이부분은 채팅의 참여할건지 안할건지 물어봐야하는 부분*/

//     //길이를 보내는부분
//     for (int j = 0; j < len; j++)
//     {
//         write(x[j],(void*)&len,sizeof(int));
//     }


//     //고유번호를 보내는 부분
//     for (int i = 0; i < len; i++)
//     {
//         write(x[i],(void*)x,sizeof(int)*len);
//     }


// }
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


// void rnchatingroom(int socks,int you)
// {
//     pthread_mutex_lock(&mutx);
//     int mysock=socks;
//     pthread_mutex_unlock(&mutx);
//     string k,j,c;
//     unordered_map<int,string>::iterator iter;
//     iter=clnt_aka.find(mysock); //클라이언트 번호로 내 별명찾기
//     k=iter->second; 
//     int str_ren,i;
//     int matchcount=0; 
//     char* buffer = new char[BUF_SZIE];
//     memset(buffer,0,BUF_SZIE);
//     c="["+k+ "]" ; //내 별명 등록
    
//     for (int i = 0; i < 2; i++)
//     {
    
//       j=c+"님이 입장했습니다.\n";
//       j.copy(buffer,j.length());
//       write(mysock,buffer,j.length());      
//       write(you,buffer,j.length());      
//       memset(buffer,0,BUF_SZIE);  
    
//     }
//     rc.len--;    

//     while ((str_ren=read(mysock,buffer,BUF_SZIE))!= -1)
//     {
//       if(buffer[0]=='`')
//       {
      
//       j=c+"님이 퇴장했습니다.\n";
//       j.copy(buffer,j.length());
//       write(mysock,buffer,j.length());
//       write(you,buffer,j.length());
//       memset(buffer,0,BUF_SZIE);
//       break;
//       }
      
//       j=c+" "+buffer;
//       j.copy(buffer,j.length());
//       buffer[j.length()]=0;
//       write(mysock,buffer,j.length());
//       write(you,buffer,j.length());
//       memset(buffer,0,BUF_SZIE); 
//     }

//     k="다음대화상대를 찾으시겠습니까? y or n";
//     k.copy(buffer,k.length());
//     write(mysock,buffer,k.length());
//     memset(buffer,0,BUF_SZIE);
//     str_ren=read(mysock,buffer,BUF_SZIE);
//     if(buffer[0]=='y')
//     {
//         memset(buffer,0,BUF_SZIE);
//         buffer[0]=':';
//         buffer[1]='\0';
//         write(mysock,buffer,3);
//     }

//     delete buffer;
// }


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
        usleep(100000);
        mmsg=mmsg+"\n";
        mmsg.copy(booksmsg,mmsg.length());
        write(sock,booksmsg,mmsg.length());
        memset(booksmsg,0,BUF_SZIE);
    }  
    
    delete c;   
}

void chatprotocol(char checkf,int clnt_sock,int* login,chatserver* my,King* king,char msg[BUF_SZIE],string* aka,int* status)
{
    string copy=msg;
    pthread_t t_id;
    cout<<copy<<endl;
    stringstream ss;
    string k,z;
    int uyt;
    bool st=true;
    void* ga;
    chatingparts sock;
   
    
    switch (checkf)
    {
    case 'A':
        /*회원가입 customer*/
        copy=splitchatmsg(copy);
        k=king->GetAccount(copy);
        k.copy(msg,k.length());
        write(clnt_sock,msg,k.length());
        memset(msg,0,BUF_SZIE);
        break;
    case 'B'://로그인하면 해쉬맵에 key:고유번호 , value: 소켓번호 , key:소켓번호,value:별명
        /*CS로그인*/
        copy=splitchatmsg(copy);
        *login=my->getlogin(copy);
        usleep(100);
        if(*login !=0)
        {
            *aka=my->aka;
            my->login=*login;
            clnt_fid.insert(pair<int,int>(*login,clnt_sock));
            clnt_aka.insert(pair<int,string>(clnt_sock,*aka));
            csonline.insert(pair<string,int>(*aka,clnt_sock));
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
        // puts("들어옴");
        // k=my->showMyFriend();
        // z=findonlinefriend(k);
        // cout<<k;
        // send_clnt(z,clnt_sock);
        copy=splitchatmsg(copy);
        *login=king->getlogin(copy);        
        
        usleep(100);
        if(*login !=0)
        {
            *aka=king->aka;
            king->login=*login;
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
    case 'D':
        /*채팅요청함수*/
        watingcs(*aka,clnt_sock);
        // *status=1;           
        // oneread_oneread(*login,copy);//구조체에 클라이언트 소켓번호들 할당   
        // uyt=plzone_one(login,sock);//클라이언트들에게 채팅요청보내기
        // okchatingroom(clnt_sock);
        memset(msg,0,BUF_SZIE);
        // *status=0;
        break;
    
    case 'E':
        /*Q&A Start*/      
        csonline.erase(*aka);
        selectcustomer(*aka,copy,clnt_sock);
        csonline.insert(pair<string,int>(*aka,clnt_sock));
        // *status=1;           
        // okchatingroom(clnt_sock);//채팅방 참여
        memset(msg,0,BUF_SZIE);
        // *status=0;
        break;
    case 'F':/*클라이언트데이터요청*/
        ss.str(copy);
        ss>>z>>copy;
        k=my->customer_info(copy);
        send_clnt(k,clnt_sock);
        // copy=splitchatmsg(copy);
        // k=shootFriend(*login,copy,my);
        // k.copy(msg,k.length());
        // msg[k.length()]=0;
        // write(clnt_sock,msg,k.length());
        memset(msg,0,BUF_SZIE);
        break;            
    case 'G':
        /*올림픽 데이터 요청*/
        ss.str(copy);
        ss>>z>>copy;
        k=my->Get_SummerOlyp(copy);
        send_clnt(k,clnt_sock);
        // k=my->checkFriendRequest(*login);        
        // send_clnt(k,clnt_sock);
        memset(msg,0,BUF_SZIE);
        break;            
    case 'H':
        /*친수 수락*/
        // copy=splitchatmsg(copy);
        // aptfriend(*login,copy,my);       
        // memset(msg,0,BUF_SZIE);
        break;
    case 'I':
        /*친구 거절*/
        // copy=splitchatmsg(copy);
        // rejectfriend(*login,copy,my);
        // memset(msg,0,BUF_SZIE);
        break;
    case 'J':
        // *status=1;
        // renchatchober(clnt_sock);
        // uyt=ranyou(clnt_sock);
        // if(uyt==-1)
        //     break;
        // rnchatingroom(clnt_sock,uyt);
        // *status=0;
        // break;
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
// void aptfriend(int& login,string msg,chatserver* my)
// {
//     stringstream sss(msg);
    
//     vector<int> myvec;
    
//     int k;
    
//     while (sss >>k)
//     {
//         myvec.emplace_back(k);
//     }

//     vector<int>::iterator iter;
//     for ( iter =myvec.begin(); iter !=myvec.end(); ++iter)
//     {
//         my->registFriend(login,*iter);
//     }
// }


//친구 신청
// string shootFriend(int& login,string msg,chatserver* my)
// {
//     stringstream sss(msg);
//     ostringstream oss;
//     vector<int> myvec;
    
//     int k;
    
//     while (sss >>k)
//     {
//         myvec.emplace_back(k);
//     }

//     vector<int>::iterator iter;
//     for ( iter =myvec.begin(); iter !=myvec.end(); ++iter)
//     {
//        oss<<my->shoot(login,*iter);
//     }
//     return oss.str();
// }

// void rejectfriend(int& login,string msg,chatserver* my)
// {
//     stringstream sss(msg);
    
//     vector<int> myvec;
    
//     int k;
    
//     while (sss >>k)
//     {
//         myvec.emplace_back(k);
//     }

//     vector<int>::iterator iter;
//     for ( iter =myvec.begin(); iter !=myvec.end(); ++iter)
//     {
//         my->rejectFriend(login,*iter);
//     }
// }


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

// void chatqna(string aka,int mysock,int yoursock)
// {
//     char* buffer =new char[BUF_SZIE];
//     string j;
//     string c=aka ; //내 별명 등록
//     c.copy(buffer,c.length());
//     write(yoursock,buffer,j.length());
//     memset(buffer,0,BUF_SZIE);  
//     int str_ren,i;
    
//  while ((str_ren=read(mysock,buffer,BUF_SZIE))!= -1)
//     {
//       if(buffer[0]=='`')
//       {      
//       j=c+"님이 퇴장했습니다.\n";
//       j.copy(buffer,j.length());
//       write(yoursock,buffer,j.length());
//       memset(buffer,0,BUF_SZIE);
//       break;
//       }
//       j=c+" "+buffer;
//       j.copy(buffer,j.length());
//       write(yoursock,buffer,j.length());  
//       write(mysock,buffer,j.length());    
//       memset(buffer,0,BUF_SZIE);
//     }

// }
void chatqna(string csaka,string cusaka,int mysock,int yoursock)
{
    ostringstream oss("");
    char* buffer =new char[BUF_SZIE];
    string j,r;
    unordered_map<int,string>::iterator zter;
    zter=clnt_aka.find(mysock);
    string c=zter->second; //내 이름 넣기
    // r=c+"님이입장했습니다.";
    // c.copy(buffer,c.length());
    puts(buffer);
    // write(yoursock,buffer,j.length());
      
    int str_ren,i;
    string qnakey=csaka+" "+cusaka;
    usleep(10000);
    // r.copy(buffer,r.length());
    // write(yoursock,buffer,r.length());
    memset(buffer,0,BUF_SZIE);
 try{  
 while ((str_ren=read(mysock,buffer,BUF_SZIE))!= -1)
    {
        time_t curTime =time(NULL);
        tm* PLocal =NULL;
        PLocal=localtime(&curTime);
        localtime_r(&curTime,PLocal);
        oss<<PLocal->tm_year+1900<<"년 "<<PLocal->tm_mon +1<<"월 "<<PLocal->tm_mday<<"일 "<<PLocal->tm_hour<<"시 "
        <<PLocal->tm_min<<"분 "<<PLocal->tm_sec<<"초 ";
        if(buffer[0]=='`')
        {      
        oss<<c<<"퇴장\n";
        j=c+"님이 퇴장했습니다.\n";
        j.copy(buffer,j.length());
        write(yoursock,buffer,j.length());
        memset(buffer,0,BUF_SZIE);
        break;        
        }
        if(buffer[0]==0)
            continue;
        j=c+" "+buffer;
        oss<<j<<"\n";
        j.copy(buffer,j.length());
        write(yoursock,buffer,j.length());  
        write(mysock,buffer,j.length());    
        memset(buffer,0,BUF_SZIE);
    }
}catch(exception &e){}
    delete buffer;
    fileDriver.insert(pair<string,string>(qnakey,oss.str()));
    // chatserver k;
    // k.Counseling(csaka,cusaka,oss.str());
}

//cs클라이언트들에게 qna를 요청한 사람들을 보여주는 스레드 함수
//이거 안돼겠다 cs가 작업할때마다(채팅,조회,등등)딕셔너리에 넣다뺏다해야할듯
//일단 채팅이 cs의  이름과 관계성을 맺고 있어서 따로 분리하긴 힘들듯..
//그럼 채팅을 제외한 나머지 기능들을 다중접속으로 해결해보자...

void* showcustomer(void* args)
{
    unordered_map<string,int>::iterator iter;
    unordered_map<string,int>::iterator ater;
    int socks =0;
    string cusaka;
    string pastcus;
    ostringstream oss;
    char* messge=new char[1024];
    int* len = new int;
    int* count= new int;
    int* pastcount= new int;
    int* cscount= new int;
    *cscount=0;
    *count=0;
    *pastcount=0;
    while (true)
    {   
        try{
            sleep(3);
            count=0;
            cscount=0;
            socks=0;
            oss.str("");
            for ( iter=waitqna.begin(); iter !=waitqna.end(); ++iter)
            {
                oss<<iter->first<<"\n";
                
                count++;        
            }                                   
            if(count==0)
                continue;                
                                                
            cusaka=oss.str();            
            cusaka.copy(messge,cusaka.length());
            
            for ( ater = csonline.begin(); ater != csonline.end(); ++ater)
            {
                socks=ater->second;
                write(socks,messge,cusaka.length());

            }
            memset(messge,0,BUF_SZIE);
            
        }
        catch(exception &e)
        {
            
        }                
    }
    delete messge;
}


//cs가채팅할고객을 지목해서 보내면 채팅 스타트
void selectcustomer(string mysaka,string csaka,int socks)
{
    try{
    unordered_map<string,int>::iterator iter;
    string aa,cusaka;        
    char* messge=new char[100];
    int len;    
    messge[len]=0;    
    stringstream ss(csaka);
    ss>>aa>>cusaka;
    iter=waitqna.find(cusaka);   
    int clssock=iter->second;
    waitqna.erase(cusaka);
    goqna.insert(pair<string,int>(cusaka,socks));        
    delete messge;
    chatqna(mysaka,cusaka,socks,clssock);
   
}catch(exception &e){
    
}
}


//고객이 QnA를 신청하면 딕셔너리에 저장되고 대기되는 부분
void watingcs(string aka,int socks)
{
char* control=new char[BUF_SZIE];
char* sending=new char[BUF_SZIE];
string k="3";
string m="1";
int* len = new int;
string z;
unordered_map<string,int>::iterator iter;  
unordered_map<int,string>::iterator ater;
waitqna.insert(pair<string,int>(aka,socks));
//read가 while문을 블록킹함
//클라이언트에서 대기중에 주기적으로 #을제외한 아무거나 데이터를 보내면 좋을같음
while ((*len=read(socks,control,100))!=-1)
 {
    control[*len]=0;
    puts(control);
    z=control;
    if(z.compare("b")==0)
    {
        break;
    }
            
   else if(waitqna.find(aka)==waitqna.end())
    {                                
        memset(sending,0,BUF_SZIE);
        iter=goqna.find(aka);
        ater=clnt_aka.find(iter->second);
        k.copy(sending,k.length());
        write(socks,sending,k.length());            
        usleep(1000);
        chatqna(ater->second,aka,socks,iter->second);
        goqna.erase(aka);                 
        delete len;
        delete control;
        return;    
    }
    
    else
    {
    memset(sending,0,BUF_SZIE);
    m.copy(sending,m.length());
    write(socks,sending,m.length());
    memset(control,0,BUF_SZIE);
    }
}

        delete sending;
        delete len;
        delete control;
        if(waitqna.find(aka)!=waitqna.end())
            waitqna.erase(aka);
}

/*이터레이터 2개로 멀티딕셔너리에서 데이터를찾은후 해당데이터에서 상담낵을 뽑아서 합치고 저장한후 대기목록에서 제거해버는 로직*/
void* QnAToFile_T(void* arg)
{
 unordered_multimap<string,string>::iterator iter;
 unordered_multimap<string,string>::iterator ater;
 ostringstream oss;
 stringstream ss;
 string csname,cusname;
 chatserver k;
 bool satement=false; 
 
 try
{
    while (true)
    {
        for (iter = fileDriver.begin(); iter !=fileDriver.end(); ++iter)
        {
            for ( ater = fileDriver.begin(); ater != fileDriver.end(); ++ater)
            {
                if(iter!=ater)
                {
                    if(iter->first==ater->first)
                    {
                        oss<<iter->second<<ater->second;
                        ss.str(iter->first);   
                        ss>>csname>>cusname;
                        k.Counseling(csname,cusname,oss.str());
                        fileDriver.erase(iter->first);                                           
                        oss.str("");
                        ss.str("");
                        satement=true;
                        break;                                        
                    }                
                }
            }        
            if(satement==true)
            {
                satement=false;
                break;
            }
        }
        sleep(1);
    }
 }catch(const std::exception& e)
 {
    puts(e.what());
 }    
return NULL;
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}