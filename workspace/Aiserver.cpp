#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<queue>
#include<unistd.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include<chrono>
#include <ctime>
#include <pthread.h>
#include <netinet/tcp.h>
#include<unordered_map>
#include<nlohmann/json.hpp>
#include "aidb.hpp"
#define BUF_SZIE 4000
#define MAX_CLNT 100
using namespace std;
using json = nlohmann::json;
void* handle_clnt(void* arg);
void error_handling(string message);
void chatqna(string aka,int mysock,int yoursock);
void chatqna(string csaka,string cusaka,int mysock,int yoursock);
void chatprotocol(string msg,int sock);
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
unordered_map<int,int> clnt_fid;//고유번호->소켓
unordered_map<int,string> clnt_aka;//소켓->이름

unordered_map<string,int> goqna;//cs이름->소켓
unordered_map<string,int> csonline;//cs들이 로그인하면 저장좀해야겠으
unordered_map<string,string(*)(string,int)> theyfun;
unordered_multimap<string,string> fileDriver;//파일을 위한 대화내용 연결 딕셔너리
pthread_mutex_t mutx;

//opencv프로젝트시작
void snedVectorMsg(string msg,int sock);//크기만큼 할당해서 데이터 보내기
string Login(string msg,int sock);
string GetDiaPrice(string msg,int sock);
unordered_map<int,string> User_name_sock;//소켓 번호로 유저 소켓번호 찾기
string ThePython(string msg,int sock); // 파이썬 클라이언트 등록
queue<int> modelQueue; //파이썬 클라이언트가 처리할 큐
vector<string> diaData; // 파이썬 클라이언트에게 보낼 프로토콜을 담은 백터
string Sign_UP(string msg,int sock); //회원가입
string Getdata(string msg,int sock);
int main(int argc,char *argv[])
{
    signal(SIGPIPE,SIG_IGN);
    int serv_sock,clnt_sock;
    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    pthread_t t_id;
    srand(time(NULL));

    memset(clnt_socks,0,MAX_CLNT*2);
    
    pthread_mutex_init(&mutx,NULL);
    
    serv_sock=socket(PF_INET,SOCK_STREAM,0);    
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi("10001"));
    theyfun.insert(pair<string,string(*)(string,int)>("로그인",Login));
    theyfun.insert(pair<string,string(*)(string,int)>("회원가입",Sign_UP));
    theyfun.insert(pair<string,string(*)(string,int)>("life is short",ThePython));
    theyfun.insert(pair<string,string(*)(string,int)>("Request price",GetDiaPrice));
    theyfun.insert(pair<string,string(*)(string,int)>("데이터요청",Getdata));
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
    string* aka=new string;
    int flag = 1;
    setsockopt(clnt_sock, IPPROTO_TCP, TCP_NODELAY, (void *)&flag, sizeof(int));
    unordered_map<string,int>::iterator iter;
    unordered_map<int,string>::iterator ater;
    string mymsg;
    memset(msg,0,BUF_SZIE);
    while ((*str_len=read(clnt_sock,msg,BUF_SZIE))!=0)
    {                 
        msg[*str_len]=0;
        mymsg=msg;
        if(*status==1){
            continue;
        }        
        chatprotocol(mymsg,clnt_sock);
        memset(msg,0,BUF_SZIE);
    }
    pthread_mutex_lock(&mutx);//만약 다른 클라이언트가 비슷한 시기에 접속을 종료했다면 밑에 for문이 돌기전에 진입하게된다.그렇게되면 소켓번호를
    for ( i = 0; i <clnt_cnt ; i++)//재정렬하는 과정에서 하나가 또 지워지거나 정렬하고. 있는거 또 정렬해서 순번이 꼬이는 사건이 발생할 수 있다. 그 사건을 막기위한 lock
    {
        if(clnt_sock==clnt_socks[i])
        {
            while (i++< clnt_cnt-1)
                clnt_socks[i]=clnt_socks[i+1]; //i번째를 탈락시켰기 때문에 i번째 소켓을 i+1번째로 한칸 씩 덮어쒸운다.
            break;
        }
    }
    clnt_cnt--;
    ater=User_name_sock.find(clnt_cnt);
    //딕셔너리 키 벨류 iter->first 키 iter->second 벨류
    
    if(ater!=User_name_sock.end())
    {
        User_name_sock.erase(clnt_cnt);
    }
    iter=csonline.find(*aka);
    
    if(iter!=csonline.end())
    {
        csonline.erase(*aka);
    }
    ater=clnt_aka.find(clnt_sock);
    
    if(ater!=clnt_aka.end())
    {
        clnt_aka.erase(clnt_sock);
    }

    pthread_mutex_unlock(&mutx);//모든 정렬이 끝나고나서 unlock
    clnt_fid.erase(*login);
    delete str_len;
    delete login;
    delete msg; 
    close(clnt_sock);
    return NULL;
}


void chatprotocol(string msg,int sock)
{
try{
   json j=json::parse(msg);
   string k;
   unordered_map<string,string(*)(string,int)>::iterator iter;
   iter=theyfun.find(j["protocol"]);
   puts(j["protocol"].dump().c_str());
   if(iter!=theyfun.end()){
        k=iter->second(msg,sock);   
   if(k.compare("X")!=0)
        snedVectorMsg(k,sock);
   }
   else if(k.compare("X")==0)
   {
     puts("문제없음");
   }
   else
   {
    k="프로토콜 오류" + msg;
    puts(k.c_str());
    snedVectorMsg(k,sock);
   }
   }catch( json::exception& e)
   {    
    puts(msg.c_str());
 
   }

}

string ThePython(string msg,int sock) // 큐에 대기중인 클라이언트소켓파일디스크립터를 하나씩처리함
{
    vector<string>::iterator iter;
    DBConnect dibp;
    unordered_map<int,string>::iterator ater;
    puts("파이썬 연결 완료");
    int procesSocket;
    int len;
    char* buf=new char[BUF_SZIE];
    string hand;
    string price;
    json j;
    memset(buf,0,BUF_SZIE);
    while (true)
    {   usleep(10000);
        if(modelQueue.empty())
            continue;
        procesSocket= modelQueue.front();
        modelQueue.pop();
        hand=diaData.front();
        iter=diaData.begin();
        diaData.erase(iter);
        hand.copy(buf,hand.length());
        write(sock,buf,hand.length());    
        memset(buf,0,BUF_SZIE);
        len=read(sock,buf,BUF_SZIE);
        buf[len]=0;
        write(procesSocket,buf,len);        
        price=buf;
        ater =User_name_sock.find(procesSocket);
        j=json::parse(hand);
        j["price"]=atof(price.c_str());
        j["username"]=ater->second;
        dibp.SetUser_Search_Data(j.dump());
        memset(buf,0,BUF_SZIE);
        
    }
    delete buf;
    puts("파이썬 서버 종료");
    return (string)"X";
}
string Getdata(string msg,int sock)
{
    DBConnect db;
    string a;
    a=db.GetSearchData(msg);
    return a;
}

string GetDiaPrice(string msg,int sock) // 가격을 얻기위한 큐와 벡터에 데이터를 저장하는 함수
{
    pthread_mutex_lock(&mutx);
    modelQueue.push(sock);
    diaData.push_back(msg);
    pthread_mutex_unlock(&mutx);
    puts("가격얻기완료");
    return (string)"X";   
}

string Login(string msg,int sock) // 로그인함수 보완 필요
{
    DBConnect db;
    string result=db.UserLogin(msg);
    User_name_sock.insert(pair<int,string>(sock,result));
    return result;
}

string Sign_UP(string msg,int sock)
{
    DBConnect db;
    db.SetAccount(msg);
    return (string)"회원가입 완료";
}


void snedVectorMsg(string msg,int sock)
{
    int k=msg.length();
    char* vchar= new char[k];
    msg.copy(vchar,k);
    write(sock,vchar,k);
    delete vchar;
}


void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}
