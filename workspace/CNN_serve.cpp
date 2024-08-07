#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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
#include "opencv4/opencv2/opencv.hpp"
#include<nlohmann/json.hpp>
#include "DBforimg.hpp"
#define BUF_SZIE 4000
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
// void oneread_oneread(int mysock,string msg);
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
// void* QnAToFile_T(void* arg);
bool isValidJson (std::string jsonString);
void chatprotocol(string msg,int sock);
string selectcustomer(string mysaka,int socks);
// void chatprotocol(int clnt_sock,int* login,chatserver* my,King* king,string msg,string* aka,int* status);
int plzone_one(int* login,chatingparts my);
void* inviteFriend(void* arg);
string watingcs(string msg,int socks);
void* matching(void* arg);
void* showcustomer(void* args);
chatingparts sock_clnt;
randchat rc;
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];

unordered_map<int,int> clnt_fid;//고유번호->소켓
unordered_map<int,string> clnt_aka;//소켓->이름
unordered_map<string,int> waitqna;//고객이름->소켓
unordered_map<string,int> goqna;//cs이름->소켓
unordered_map<string,int> csonline;//cs들이 로그인하면 저장좀해야겠으
unordered_map<string,string(*)(string,int)> theyfun; // 프로토콜 요청 함수 모음 딕셔너리
unordered_multimap<string,string> fileDriver;//파일을 위한 대화내용 연결 딕셔너리
pthread_mutex_t mutx;

//CNN프로젝트시작
void snedVectorMsg(string msg,int sock);//크기만큼 할당해서 데이터 보내기
string saveimg(vector<uchar> img);
string getimg(string msg,int sock);
string ThePython(string msg,int sock);
string usemoneydata(string msg,int sock);
queue<int> modelQueue; //파이썬 클라이언트가 처리할 큐
vector<vector<uchar>> diaData; //파이썬 클라이언트에게 보낼 프로토콜을 담은 백터
unordered_map<int,string> User_name_sock;//소켓 번호로 유저 소켓번호 찾기
string Sign_UP(string msg,int sock); //로그인 함수 사용X
string sendimg(string msg,int sock); //이미지 전송함수
string history(string msg,int sock); //DB데이터 전송함수
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
    
    // int recvBufSize = 64000; // Example: 8KB
    // if (setsockopt(serv_sock, SOL_SOCKET, SO_RCVBUF, &recvBufSize, sizeof(recvBufSize)) < 0) {
    //     std::cerr << "setsockopt failed" << std::endl;
    //     close(serv_sock);
    //     return 1;
    // }
    
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi("10001"));

    theyfun.insert(pair<string,string(*)(string,int)>("이미지전송",getimg)); //이미지 전송을 위한 프로토콜
    theyfun.insert(pair<string,string(*)(string,int)>("life is short",ThePython));//파이썬 클라이언트가 접속했을때 요청대기 상태로만드는 프로토콜
    theyfun.insert(pair<string,string(*)(string,int)>("이미지로그",sendimg));//저장된 이미지를 다시 클라이언트로 보내주는 프로토콜
    theyfun.insert(pair<string,string(*)(string,int)>("데이터요청",history));//DB에 저장된 데이터를 클라이언트로 보내주는 프로토콜
    if(bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr)))
        error_handling("bind() error");
    if(listen(serv_sock,5)==-1)
        error_handling("listen() error");
   
    // pthread_detach(t_id);
    // pthread_create(&t_id,NULL,QnAToFile_T,(void*)&clnt_sock);
    // pthread_detach(t_id);
    // pthread_create(&t_id,NULL,showcustomer,(void*)&clnt_sock);
    // pthread_detach(t_id);


     
    while (1)
    {
        clnt_adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz);
        // int recv_buffer_size = 64000; // 수신 버퍼 크기 설정
        // if (setsockopt(clnt_sock, SOL_SOCKET, SO_RCVBUF, &recv_buffer_size, sizeof(recv_buffer_size)) < 0)
        //  {
        //     perror("Setsockopt for SO_RCVBUF failed");
        //     exit(EXIT_FAILURE);
        // }
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
    int * str_len=new int;
    int* login=new int;
    char* msg=new char[BUF_SZIE];
    string* aka=new string;
    int flag = 1;
    // int bufSize = 1024 * 10;
    // socklen_t len = sizeof(bufSize);
    // setsockopt(clnt_sock, SOL_SOCKET, SO_SNDBUF, &bufSize, sizeof(bufSize));
    // vector ,딕셔너리 
    // pthread_create(&t_id,NULL,matching,(void*)&clnt_sock);
    setsockopt(clnt_sock, IPPROTO_TCP, TCP_NODELAY, (void *)&flag, sizeof(int));
    unordered_map<string,int>::iterator iter;
    unordered_map<int,string>::iterator ater;
    string mymsg;
    memset(msg,0,BUF_SZIE);
    while ((*str_len=recv(clnt_sock,msg,BUF_SZIE,0))!=0)
    {                 
        msg[*str_len]=0;
        mymsg=msg;   
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
    //딕셔너리 키 벨류 iter->first 키 iter->second 벨류

    //모든 딕셔너리에 해당 클라이언트 제거
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

    pthread_mutex_unlock(&mutx);//모든 정리가 끝나고나서 unlock
    clnt_fid.erase(*login);
    delete str_len;
    delete login;
    delete msg; 
    close(clnt_sock);
    return NULL;
}



void chatprotocol(string msg,int sock) //프로토콜 핸들러
{
  
   try{
   json j=json::parse(msg);
   string k;
   unordered_map<string,string(*)(string,int)>::iterator iter;
   iter=theyfun.find(j["protocol"]);
   puts(j["protocol"].dump().c_str());
   if(iter!=theyfun.end()){
        k=iter->second(msg,sock);   
   if(k.compare("X")!=0) //함수 반환 값이 X가아니면 반환된 스트링 전송
        snedVectorMsg(k,sock);
   }
   else if(k.compare("X")==0) // X 면 잘 실행은 되었는지 확인
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
    // snedVectorMsg((string)"json타입이 아닙니다.",sock);
   }

}

// json j=json::parse(msg);
// reciveimdata.emplace_back(j["data"].dump());

string getimg(string msg,int sock) // 이미지를 OPencv를 이용하여 decoding
{
    //ostringstream oss;
    json j;
    uchar* buffer = new uchar[BUF_SZIE];
    int len;
    vector<uchar> imgvec;
    while (true)
    {
    try
    {
    
        while ((len=recv(sock,buffer,BUF_SZIE,0))!=0)
        {
            cout<< strlen((char*)buffer)<<endl;
            buffer[len]=0;
            json j=json::parse((string)(char*)buffer);
            
            if(((string)j["protocol"]).compare("이미지전송완료")==0)
            {
                string k = saveimg(imgvec);
                modelQueue.push(sock);
                diaData.push_back(imgvec);
                return k;
            }

        }
    
    }
    catch(const json::exception& e)
    {
         for (int i = 0; i <len; i++) //이미지 데이터 수집
        {
            imgvec.push_back(buffer[i]); 
        }
        if(strlen((char*)buffer) == 4000)
            return "길이가 4000바이트 이상입니다.";
    }
    }
    
    return (string)"X";
}

string ThePython(string msg,int sock) // 큐에 대기중인 클라이언트소켓파일디스크립터를 하나씩처리함
{
    vector<string>::iterator iter;
    Dbim dibp;
    unordered_map<int,string>::iterator ater;
    puts("파이썬 연결 완료");
    int procesSocket;
    int len;
    int modulo;
    char* buf=new char[BUF_SZIE];
    vector<uchar> hand;
    vector<uchar>::iterator zter;
    string price;
    json j;
    memset(buf,0,BUF_SZIE);
    
    while (true)
    {   usleep(10000);
        if(modelQueue.empty()) //큐가 비었는지 풀링으로 확인
            continue;
        puts("되나?");
        procesSocket= modelQueue.front();
        modelQueue.pop();
        hand=*diaData.begin();        
        uchar* imgbuf=new uchar[hand.size()];
        string msg=R"(
        {"protocol":"imgsend"}
        )";
        msg.copy(buf,msg.length());
        write(sock,buf,msg.length());
        usleep(30000);
        for ( int i =0; i<hand.size(); i++)
        {
            imgbuf[i]=hand[i];       
        }
        write(sock,imgbuf,hand.size());
       
        diaData.erase(diaData.begin());
        memset(buf,0,BUF_SZIE);
        usleep(10000);
        msg=R"(
        {"protocol":"imgdone"}
        )";
        msg.copy(buf,msg.length());
        write(sock,buf,msg.length());                        
        memset(buf,0,BUF_SZIE);
        len=read(sock,buf,BUF_SZIE);
        buf[len]=0;
        string fdata=buf;
        dibp.SetData(fdata);
        //이미지 테이블이랑 분리되어있는 테이블 만들어서 그 테이블에서 찾아서 보내야할듯
        write(procesSocket,buf,len);                
        puts("전송완료");
        memset(buf,0,BUF_SZIE);
        delete imgbuf;
        }
    delete buf;
    puts("파이썬 서버 종료");
    return (string)"X";
}

string history(string msg,int sock)
{
    
    Dbim dbim;
    string k;
    k=dbim.Getvalue(msg);
    return k;
}

string sendimg(string msg,int sock)
{
    Dbim dbim;
    string path;
    path =dbim.Getimg(msg);
    cv::Mat img =cv::imread(path,cv::IMREAD_COLOR);
    vector<uchar> decoingdata;
    cv::imencode(".png",img,decoingdata);
    uchar* imgbuf= new uchar[decoingdata.size()];
    for (int i = 0; i < decoingdata.size(); i++) // 이미지 전송을 위해서 vector data를 버퍼에 담기
    {
        imgbuf[i]=decoingdata[i];
    }
    write(sock,imgbuf,decoingdata.size());
    // string done = R"({
    // protocol : "이미지전송완료"
    // })";
    // char* buf = new char[BUF_SZIE];
    // done.copy(buf,done.length());
    // write(sock,buf,done.length());
    delete imgbuf; //사용후 제거
    return "X";
}

string sendData(string msg,int sock)
{
    Dbim dbim;
    string flowerdata;
    flowerdata= dbim.Getvalue(msg);

    return flowerdata;
}

string saveimg(vector<uchar> imgdata) //받은 이미지를 로컬에 저장
{
    try{
    Dbim dbim;  
    
    cv::Mat img =cv::imdecode(cv::Mat(imgdata),-1);
    ostringstream oss2;
    time_t curTime =time(NULL);
    tm* PLocal =NULL;
    PLocal=localtime(&curTime);
    localtime_r(&curTime,PLocal);
    oss2<<PLocal->tm_year+1900<<PLocal->tm_mon +1<<PLocal->tm_mday<<PLocal->tm_hour
    <<PLocal->tm_min<<PLocal->tm_sec;  
    string filename="/home/lms/test/myc-1/ImageFolder/"+oss2.str()+".png"; //시간을 이름으로 사용
    if(cv::imwrite(filename,img)) //imwrite는 반환값으로 성공여부를 반환함
    {

        puts(dbim.savepath(filename).c_str());
        
    }    
    
    
    return (string)"이미지수신성공!";
    }catch(cv:: Exception &e)
    {
        puts(e.what());
    }
    return (string)"X";
}


void snedVectorMsg(string msg,int sock) //크기만큼만 전송
{
    int k=msg.length();
    char* vchar= new char[k+1];
    msg.copy(vchar,k);
    write(sock,vchar,k);
    delete vchar;
}




void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}