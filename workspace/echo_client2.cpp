#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>
#define BUF_SZIE 8000
using namespace std;
void error_handling(string message);
void* rrrr(void* args);
pthread_t t_id;
int main(int argc, char *argv[])
{
    int sock;
    sockaddr_in serv_addr;
    
    string j=R"(
  
  {
    "protocol":"고객로그인",
    "id" : "sh",
    "pw" : "1234"
  })";

// string j=R"(
  
//   {
//     "protocol":"직원로그인",
//     "id" : "sh",
//     "pw" : "1234"
//   })";


string k=R"({
"protocol" : "상담요청",
"myname" :  "임석현" 
})";


//     string k=R"(  
//   {
//      "protocol": "상담수락",
     
//      "myname" :  "박선후",
     
//      "cusname" : "임석현" 
  
//   }
//   )";

    char message[BUF_SZIE];
    int str_len=0;
    int recv_len,recv_cnt;
    int zz=0;
    int lenm=0;
    // if(argc !=3)
    // {
    //     cout << "Usage : " << argv[0] << " <IP> <port>\n";
    //     exit(1);
    // }

   sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock ==-1)
        error_handling("socket() error");
    
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("10.10.21.106");
    serv_addr.sin_port=htons(atoi("10001"));
    
    if(connect(sock,(sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("connect() error!");
    else{
        cout<<"connected......";
        pthread_create(&t_id,NULL,rrrr,(void*)&sock);
        pthread_detach(t_id);
    
        // cout<<"Input message(Q to quit): ";
        while (true)
        {
        memset(message,0,BUF_SZIE);
        cin>>zz;
        if(zz==1){
        j.copy(message,j.length());
        lenm=j.length();
        message[lenm]=0;
        }

        if(zz==2)
        {
            k.copy(message,k.length());
            lenm=k.length();
            message[lenm];
        }
        
        write(sock,message,lenm);
        memset(&message,0,BUF_SZIE);                    
        }
                               
    }
    close(sock);
    return 0;
    }
void* rrrr(void* args){
    int recv_cnt;
    int sock = (*(int*)args);
    char message[BUF_SZIE];
    while((recv_cnt=read(sock,message,BUF_SZIE))!=0){
        message[recv_cnt]=0;            
        puts(message);
    }
return NULL;
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}