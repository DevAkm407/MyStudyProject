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
#define BUF_SZIE 1024
#define MAX_CLNT 256
using namespace std;
void * handle_clnt(void* arg);
void send_msg(char * msg, int len);
void error_handling(string message);
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int main(int argc,char *argv[])
{
    signal(SIGPIPE,SIG_IGN);
    int serv_sock,clnt_sock;
    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    pthread_t t_id;
    // if(argc!=2)
    // {
    //     cout<<"Usage : "<<argv[0] <<" <prot>\n";
    //     exit(1);
    // }
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
    while (1)
    {
        clnt_adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz);

        pthread_mutex_lock(&mutx);//handle_cnt에서 순서를 정렬할때 새로들어오는것을 막아주기위해 lock 함
        clnt_socks[clnt_cnt++]=clnt_sock;
        pthread_mutex_unlock(&mutx);

        pthread_create(&t_id,NULL,handle_clnt,(void*)&clnt_sock);//쓰레드 id하나로 클라이언트 수만큼 쓰래드를 생성해주는 부분 클라이언트는 1개의 전용 쓰래드를 할당받음 
        pthread_detach(t_id);//할당한 쓰래드를 프로세스 종료와 함께 종료시키거나 클라이언트가 종료하면 자동으로 쓰레드가 종료되게 때어냄
        puts(inet_ntoa(clnt_adr.sin_addr));
    }
    close(serv_sock);
    return 0;
}

void* handle_clnt(void* arg)
{
    int clnt_sock=*((int*)arg);
    int str_len=0,i;    
    string j=R"(
    {
        "protocol" : "동물이름",
        "animal" : "Quokka"
    })";
    char msg[BUF_SZIE];
    char asg[BUF_SZIE];
    j.copy(asg,j.length());
    int test[10]={1,2,3,4,5,6,7,8,9,10};
    while ((str_len=read(clnt_sock,msg,10))!=0){
        msg[str_len]=0;
        puts(msg);
        send_msg(asg,BUF_SZIE);
        memset(msg,0,BUF_SZIE);
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
    close(clnt_sock);
    return NULL;
}

void send_msg(char* msg, int len)
{

    int i;
    pthread_mutex_lock(&mutx);//모든 클라이언트들에게 메시지를 뿌리기전에  다시 for문을 돈다고 가정하면 다른 스레드가 i에 접근하게 되면서 i를
    //다시 0으로 만들어버리는 사태가 발생할 수 있고 메시지는 모든 클라이언트들에게 전달되지 못하고 후자로 들어온 메시지만 모두에게 전달될 가능성이 있다.
    
    for(i=0; i<clnt_cnt; i++)
    {

        write(clnt_socks[i],msg,BUF_SZIE);
        sleep(10);
    }
    pthread_mutex_unlock(&mutx);//모든 메시지를 사용자에게 보내고 나서 언락을 풀어준다.
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}