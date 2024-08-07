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
#include <netinet/tcp.h>
#include"cs_info2.hpp"
#include"appap.hpp"
#include<nlohmann/json.hpp>
#include<unordered_map>
#define BUF_SZIE 8000
#define MAX_CLNT 100
using namespace std;
using json = nlohmann::json;
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
bool isValidJson (std::string jsonString);
void aptfriend(int& login,string msg,chatserver* my);
string selectcustomer(string mysaka,int socks);
// void chatprotocol(int clnt_sock,int* login,chatserver* my,King* king,string msg,string* aka,int* status);
int plzone_one(int* login,chatingparts my);
void* inviteFriend(void* arg);
string watingcs(string msg,int socks);
void* matching(void* arg);
void* showcustomer(void* args);
void rejectfriend(int& login,string msg,chatserver* my);
//api프로젝트시작
void snedVectorMsg(string msg,int sock);//크기만큼 할당해서 데이터 보내기
std::string employeelogin(string copy,int clnt);//직원 로그인함수
std::string cuslogin(string copy,int clnt);//고객 로그인 함수
string plzanimal(string msg,int clnt);//동물정보 요청함수(api)
void chatprotocol(string msg,int sock);//프로토콜 실행함수
string SignUp(string copy,int a = 0);//고객 회원가입 함수
string emSignUP(string copy,int a);// 직원 회원가입 함수
string survays(string msg,int clnt);//설문조사 저장 하기
string surGets(string msg,int clnt);//설문조사 데이터 받기(특정 고객데이터만)
string GPT(string msg, int clnt);//gpt에게 qna요청함수
string ImageBeginToss(string msg,int clnt);//c#과 c#이 이미지전송을 한다면 받는쪽에 크기를 알려주는 함수
string yesur(string msg,int clnt);
string mydatata(string msg,int clnt);
chatingparts sock_clnt;
randchat rc;
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
unordered_map<int,int> clnt_fid;//고유번호->소켓
unordered_map<int,string> clnt_aka;//소켓->이름
unordered_map<string,int> waitqna;//고객이름->소켓
unordered_map<string,int> goqna;//cs이름->소켓
unordered_map<string,int> csonline;//cs들이 로그인하면 저장좀해야겠으
unordered_map<string,string(*)(string,int)> theyfun;
unordered_multimap<string,string> fileDriver;//파일을 위한 대화내용 연결 딕셔너리

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

    // pthread_create(&t_id,NULL,matching,(void*)&clnt_sock);
    // pthread_detach(t_id);
    pthread_create(&t_id,NULL,QnAToFile_T,(void*)&clnt_sock);
    pthread_detach(t_id);
    pthread_create(&t_id,NULL,showcustomer,(void*)&clnt_sock);
    pthread_detach(t_id);


    theyfun.insert(pair<string,string(*)(string,int)>("고객회원가입",SignUp));
    theyfun.insert(pair<string,string(*)(string,int)>("직원회원가입",emSignUP));
    theyfun.insert(pair<string,string(*)(string,int)>("직원로그인",employeelogin));
    theyfun.insert(pair<string,string(*)(string,int)>("고객로그인",cuslogin));
    theyfun.insert(pair<string,string(*)(string,int)>("상담수락",selectcustomer));
    theyfun.insert(pair<string,string(*)(string,int)>("상담요청",watingcs));
    theyfun.insert(pair<string,string(*)(string,int)>("동물정보",plzanimal));
    theyfun.insert(pair<string,string(*)(string,int)>("설문저장",survays));
    theyfun.insert(pair<string,string(*)(string,int)>("GPT",GPT));
    theyfun.insert(pair<string,string(*)(string,int)>("설문정보",yesur));
    theyfun.insert(pair<string,string(*)(string,int)>("고객설문정보",mydatata));          
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
    string* aka=new string;
    unordered_map<string,int>::iterator iter;
    unordered_map<int,string>::iterator ater;
    string mymsg;
    while ((*str_len=read(clnt_sock,msg,BUF_SZIE))!=0)
    {                 
        msg[*str_len]=0;
        mymsg=msg;
        if(*status==1){
            continue;
        }        
        chatprotocol(mymsg,clnt_sock);
        memset(msg,0,BUF_SZIE);
        // puts(msg);
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


// 고객회원가입
string SignUp(string copy,int a)
{
    chatserver k;
    return k.GetAccount2(copy);        
}

string emSignUP(string copy,int a)
{
    chatserver k;
    return k.GetAccount(copy);
}

// 직원 로그인
std::string employeelogin(string copy,int clnt)
{
    chatserver my;
    json j=json::parse(copy);
    if(my.getlogin(copy) !=0)
    {
        string aka=my.aka;
        int k=my.login;
        clnt_fid.insert(pair<int,int>(k,clnt));
        clnt_aka.insert(pair<int,string>(clnt,aka));
        csonline.insert(pair<string,int>(aka,clnt));        
        return aka;
    }
    else
    {
        return (string)"로그인 실패";
    }    

   
}
//고객 로그인
std::string cuslogin(string copy,int clnt)
{
    chatserver my;
    json j=json::parse(copy);
    if(my.getlogin2(copy) !=0)
    {
        string aka=my.aka;
        int k=my.login;
        clnt_fid.insert(pair<int,int>(k,clnt));
        clnt_aka.insert(pair<int,string>(clnt,aka));               
        return aka;
    }
    else
    {
        return (string)"로그인 실패";
    }    
}

string surGets(string msg,int clnt)
{
    chatserver k;
    return k.Getsurvey(msg);
}

//앞에 숫자 때어버리기
string splitchatmsg(string msg)
{
    
    string buffer=msg;
    string k;
    stringstream ss(buffer);
    ss>>k;
    return ss.str();
    // buffer=buffer.substr(buffer.find(" "));
    // return buffer;
}

string mydatata(string msg,int clnt)
{
    chatserver k;
    return k.Getsurvey(msg);    
}

//설문저장
string survays(string msg,int clnt)
{
    chatserver k;
    return k.surveySave(msg);
}

//동물데이터 요청
string plzanimal(string msg,int clnt)
{
    ShowYourData myanimal;
    
    return myanimal.AnimalData(msg,clnt);
}
//gptqna
string GPT(string msg, int clnt)
{
    ShowYourData mygpt;
    return mygpt.GPTMAN(msg,1); 
}


void chatprotocol(string msg,int sock)
{
  
   try{
   json j=json::parse(msg);
   string k;
   unordered_map<string,string(*)(string,int)>::iterator iter;
   iter=theyfun.find(j["protocol"]);
   puts(j.dump().c_str());
   if(iter!=theyfun.end()){
        k=iter->second(msg,sock);   
   if(k.compare("X")!=0)
        snedVectorMsg(k,sock);
   }
   else if(k.compare("X")==0)
   {
    
   }
   else
   {
    k="프로토콜 오류" + msg;
    snedVectorMsg(k,sock);
   }
   }catch( json::exception& e)
   {    
    snedVectorMsg((string)"json타입이 아닙니다.",sock);
   }
}




void snedVectorMsg(string msg,int sock)
{
    int k=msg.length();
    char* vchar= new char[k+1];
    msg.copy(vchar,k);
    write(sock,vchar,k);
    delete vchar;
}



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
     int flag = 1;
    setsockopt(mysock, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));
    string plzimg;  
    int str_ren,i;
    string qnakey=csaka+" "+cusaka;
    usleep(10000);
    // r.copy(buffer,r.length());
    // write(yoursock,buffer,r.length());
    memset(buffer,0,BUF_SZIE);
 try{  
 while ((str_ren=read(mysock,buffer,BUF_SZIE))!= 0)
    {
        time_t curTime =time(NULL);
        tm* PLocal =NULL;
        PLocal=localtime(&curTime);
        localtime_r(&curTime,PLocal);
        oss<<PLocal->tm_year+1900<<"년 "<<PLocal->tm_mon +1<<"월 "<<PLocal->tm_mday<<"일 "<<PLocal->tm_hour<<"시 "
        <<PLocal->tm_min<<"분 "<<PLocal->tm_sec<<"초 ";
        plzimg=buffer;    
    
        try{
        json js=json::parse(plzimg);
        if(((string)js["protocol"]).compare("이미지전송알림")==0){
            snedVectorMsg(plzimg,yoursock);
            memset(buffer,0,BUF_SZIE);
            continue;
        }
        else if(((string)js["protocol"]).compare("이미지전송")==0){
            snedVectorMsg(plzimg,yoursock);
            memset(buffer,0,BUF_SZIE);
            continue;   
        }
        else if(((string)js["protocol"]).compare("이미지전송완료")==0){
            snedVectorMsg(plzimg,yoursock);
            memset(buffer,0,BUF_SZIE);
            continue;
        }        
        }catch (const json::exception& e) {
        // Catch-all for other nlohmann::json exceptions        
            puts(buffer);            
        }         
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

bool isValidJson ( std::string jsonString) 
{
        try {
          json j= json::parse(jsonString);
            
            return true;  // 파싱에 성공하면 유효한 JSON
        }catch ( json::parse_error& e) {
            return false; // 파싱에 실패하면 유효하지 않은 JSON
        }
return false;
}

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
string selectcustomer(string data,int socks)
{
    try{
    json j=json::parse(data);
    unordered_map<string,int>::iterator iter;       
    // char* messge=new char[100];
    // int len;    
    // messge[len]=0;    
    iter=waitqna.find((string)j["cusname"]);   
    int clssock=iter->second;
    waitqna.erase((string)j["cusname"]);
    goqna.insert(pair<string,int>((string)j["cusname"],socks));        
    // delete messge;
    chatqna((string)j["myname"],(string)j["cusname"] ,socks , clssock);   
}catch (const json::exception& e) {
        // Catch-all for other nlohmann::json exceptions
            return(string)"메시지에러: "+data;
    } 
return (string)"X";
}

string yesur(string msg,int clnt)
{
    chatserver k;
    return k.GetsurveyAVG(msg);
}

//고객이 QnA를 신청하면 딕셔너리에 저장되고 대기되는 부분
string watingcs(string msg,int socks)
{

try{    
json j=json::parse(msg);

char* control=new char[BUF_SZIE];
char* sending=new char[BUF_SZIE];
string k="3";
string m="1";
int* len = new int;
string z;
unordered_map<string,int>::iterator iter;  
unordered_map<int,string>::iterator ater;
waitqna.insert(pair<string,int>((string)j["myname"],socks));
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
            
   else if(waitqna.find((string)j["myname"])==waitqna.end())
    {                                
        memset(sending,0,BUF_SZIE);
        iter=goqna.find(j["myname"]);
        ater=clnt_aka.find(iter->second);
        k.copy(sending,k.length());
        write(socks,sending,k.length());            
        usleep(1000);
        chatqna(ater->second,(string)j["myname"],socks,iter->second);
        goqna.erase((string)j["myname"]);                 
        delete len;
        delete control;
        return "X";    
    }
    
    else
    {
    memset(sending,0,BUF_SZIE);
 
    memset(control,0,BUF_SZIE);
    }
}

        delete sending;
        delete len;
        delete control;
        if(waitqna.find((string)j["myname"])!=waitqna.end())
            waitqna.erase((string)j["myname"]);
return (string)"X";  
}
catch (const json::exception& e) {
        // Catch-all for other nlohmann::json exceptions
            return(string)"메시지에러: "+msg;
    } 
return (string)("알수없는 에러");    
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