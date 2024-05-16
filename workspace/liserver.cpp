#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <sstream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "lsclass.hpp"
#define BUF_SZIE 100
#define MAX_CLNT 256
using namespace std;
void * handle_clnt(void* arg);
void send_msg(char * msg, int len,int clntsock);
void error_handling(string message);
int Rhandle(int checkf,char msg[BUF_SZIE],lsclass* clnt);
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
void* chekingclnt(void* arg);
pthread_mutex_t mutx;

int main(int argc,char *argv[])
{
    int serv_sock,clnt_sock;
    int xxs;
    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    pthread_t t_id,ban_id;
    if(argc!=2)
    {
        cout<<"Usage : "<<argv[0] <<" <prot>\n";
        exit(1);
    }
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
    
    // pthread_create(&ban_id,NULL,chekingclnt,(void*)&xxs);
    // pthread_detach(ban_id);
    while (1)
    {
        clnt_adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz);
        puts("Connected client IP: " );
        puts(inet_ntoa(clnt_adr.sin_addr));
        // cout<<"Connected client IP: ";//inet_ntoa(clnt_adr.sin_addr);
        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt++]=clnt_sock;
        pthread_mutex_unlock(&mutx);

        pthread_create(&t_id,NULL,handle_clnt,(void*)&clnt_sock);
        pthread_detach(t_id);
       
    }
    
    close(serv_sock);
    return 0;
}



void* handle_clnt(void* arg)
{
    
    int clnt_sock=*((int*)arg);
    int str_len=0,i;
    int login=0;
    char msg[BUF_SZIE];
    lsclass clnt;
    
    while ((str_len=read(clnt_sock,msg,sizeof(msg)))!=0)
    {  
        cout<<clnt_sock<<": "<<msg<<endl;
        login=Rhandle(atoi(&msg[0]),msg,&clnt);
        send_msg(msg,BUF_SZIE,clnt_sock);
        memset(msg,0,BUF_SZIE);
    }
            
    // send_msg(msg,str_len);
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
    close(clnt_sock);
    return NULL;
}



void send_msg(char * msg, int len,int clntsock)
{

    int i;
    
    // pthread_mutex_lock(&mutx);//모든 클라이언트들에게 메시지를 뿌리기전에  다시 for문을 돈다고 가정하면 다른 스레드가 i에 접근하게 되면서 i를
    //다시 0으로 만들어버리는 사태가 발생할 수 있고 메시지는 모든 클라이언트들에게 전달되지 못하고 후자로 들어온 메시지만 모두에게 전달될 가능성이 있다. 
    // for(i=0; i<clnt_cnt; i++)
    // {

        write(clntsock,msg,len);

    // }
    // pthread_mutex_unlock(&mutx);//모든 메시지를 사용자에게 보내고 나서 언락을 풀어준다.

}



void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}


int Rhandle(int checkf,char msg[BUF_SZIE],lsclass* clnt)
{
    // pthread_mutex_lock(&mutx);
    string copymsg=msg;
    string mail; 
    switch (checkf)
    {
    
    case 1:
        
        
        /*함수(atoi(&hand1),a[2])*/    
        break;
    
    case 2: //회원가입
       mail = clnt->sign_up(copymsg);
    
       memset(msg,0,BUF_SZIE);
    
       mail.copy(msg,mail.length()); 
        //    send_msg(msg,mail.length());      
        /*함수(parameter[1],parameter[2])*/
        break;
    
    case 3: //로그인
    
        mail=clnt->loginService(msg);

        memset(msg,0,BUF_SZIE);

        mail.copy(msg,mail.length());

        /*함수(parameter[1],parameter[2])*/
        break;
    
    case 4: //대여서비스
        mail = clnt->rental(copymsg);

        memset(msg,0,BUF_SZIE);

        mail.copy(msg,mail.length());

        /*함수(parameter[1])*/
        break;
    
    case 5: //반납
        mail = clnt->giveBack(copymsg);

        memset(msg,0,BUF_SZIE);
            
        mail.copy(msg,mail.length());
        /*함수(parameter[1])*/
        break;
    
    case 6: //회원탈퇴
        
        /*함수(parameter[1])*/
        break;                
    
    default:
        memset(msg,0,BUF_SZIE);
        string  ph="프로토콜 위반" ;
        ph.copy(msg,ph.length());
        break;
    }

    // pthread_mutex_unlock(&mutx);
    return 0; 
}

 
// void* chekingclnt(void* arg)
// {
//     lsclass* c=new lsclass;
//     c->dateCheck();
// }
