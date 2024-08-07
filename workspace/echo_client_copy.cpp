#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<vector>
#include<sys/socket.h>
#include<nlohmann/json.hpp>
#include"opencv4/opencv2/opencv.hpp"
#define BUF_SZIE 1024
using namespace cv;
using json = nlohmann::json;
using namespace std;
void error_handling(string message);
vector<uchar> reciveimdata; 


string saveimg(string msg,int sock)
{
    try{
    // Dbim dbim;
    // vector<string>::iterator iter;
    // ostringstream oss;
    // for (iter=reciveimdata.begin(); iter!=reciveimdata.end(); ++iter)
    // {
    //     oss << *iter;
    // }
    vector<uchar> imgdata;

    // vector<uchar> imgdata;
    // int len = msg.length();
    // uchar* us = new uchar[len];
    // msg.copy((char*)(uchar*)us,msg.length());
    // for (int i = 0; i < strlen((char*)us); i++)
    // {
    //     imgdata.emplace_back(us[i]);
    // }
    
    cv::Mat img =cv::imdecode(cv::Mat(reciveimdata),-1);
    cv::imshow("img",img);
    cv::waitKey(0);
    cv::destroyAllWindows();
    ostringstream oss2;
    time_t curTime =time(NULL);
    tm* PLocal =NULL;
    PLocal=localtime(&curTime);
    localtime_r(&curTime,PLocal);
    oss2<<PLocal->tm_year+1900<<PLocal->tm_mon +1<<PLocal->tm_mday<<PLocal->tm_hour
    <<PLocal->tm_min<<PLocal->tm_sec;  
    // string filename="/home/lms/test/myc-1/ImageFolder/"+oss2.str()+".png";
    // if(cv::imwrite(filename,img))
    // {

    //     puts(dbim.savepath(filename).c_str());
        
    //     puts(dbim.savetext(msg).c_str());
    // }    
    
    reciveimdata.erase( reciveimdata.begin(),reciveimdata.end() );
    
    return (string)"이미지수신성공!";
    }catch(cv:: Exception &e)
    {
        puts(e.what());
        reciveimdata.erase( reciveimdata.begin(),reciveimdata.end() );
    }
    return (string)"X";
}


string getimg(string msg,int sock)
{
    ostringstream oss;
    json j;
    uchar* buffer = new uchar[BUF_SZIE];
    int len;
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
               string k = saveimg(j.dump(),sock);
               return k;
            }

        }
    
    }
    catch(const json::exception& e)
    {
         for (int i = 0; i <len; i++)
        {
            reciveimdata.push_back(buffer[i]); 
        }
        if(strlen((char*)buffer) == 4000)
            return "길이가 4000바이트 이상입니다.";
    }
    }
    
    

    return (string)"X";
}

int main(int argc, char *argv[])
{
    int sock;
    sockaddr_in serv_addr;
    char message[BUF_SZIE];
    int str_len=0;
    
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
        
    string msg=R"({
        "key" : "데이터전송",
        "3" : "클로버"
        })";
    puts(msg.c_str());
    json j=json::parse(msg);
    char* sbuf =new char[BUF_SZIE];
    // str_len=read(sock,sbuf,BUF_SZIE);
    // sbuf[str_len]=0;
    // puts(sbuf);
    // for(int i=0;i<6;i++)
    // {
    //     memset(message,0,BUF_SZIE);
    //     cout<<"Input message(Q to quit): ";
    //     fgets(message,BUF_SZIE,stdin);
    //     string k =message;
    //     k.replace(k.find('\n'),k.length(),"");
    //     puts(k.c_str());
    //     j["type"] = k;
    //     memset(message,0,BUF_SZIE);
    //     fgets(message,BUF_SZIE,stdin);
    //     k =message;
    //     memset(message,0,BUF_SZIE);
    //     puts(k.c_str());
    //     j["num"] =atoi(k.c_str());
    //     j.dump().copy(message,j.dump().length());
    //     write(sock,message,strlen(message));
    //     memset(message,0,BUF_SZIE);
    //     str_len=read(sock,message,BUF_SZIE);
    //     message[str_len]=0;
    //     cout<<"Message from server: "<<message;
    // }
    
    // while (1)
    // {
        // cout<<"Input message(Q to quit): ";
        memset(message,0,BUF_SZIE);
        // fgets(message,BUF_SZIE,stdin);
        // string k =message;
        // k.replace(k.find('\n'),k.length(),"");
        // j["type"] =k;
        // if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
        //     break;

        j.dump().copy(message,j.dump().length());
        write(sock,message,strlen(message));
        memset(message,0,BUF_SZIE);
        // getimg("a",sock);
        str_len=read(sock,message,BUF_SZIE);
        message[str_len]=0;
        cout<<"Message from server: "<<message;
   
    // }
    close(sock);
    return 0;
    
    
    
    }
void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}