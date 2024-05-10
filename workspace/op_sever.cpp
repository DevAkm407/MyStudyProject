#include<iostream>
#include<string.h>
#include<string>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4
using namespace std;
void error_handling(string message);
int calculate(int opnum,int opnds[], char oprator);
int main(int argc, char *argv[])
{
    int serv_sock,clnt_sock;
    char opinfo[BUF_SIZE];
    int str_len,i,recv_cnt,recv_len,result,opnd_cnt;
    sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    if(argc !=2)
    {
        cout<<"USage: " <<argv[0] <<" <port>"<<endl;
        exit(1);
    }

    serv_sock=socket(PF_INET,SOCK_STREAM,0);//IPV4 사용 ,TCP통신사용,기본 TCP프로토콜사용
    if(serv_sock ==-1)
        error_handling("socket() error");
    memset(&serv_adr,0,sizeof(serv_adr));//소켓구조체 안쪽을 0으로 초기화 해야함(구조체길이를 맞추기위한 변수의 0을 무조건 넣어주기위해서)
    serv_adr.sin_family=AF_INET;//IPV4사용
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);//자동으로 이 컴퓨터에 존재하는 랜카드 중 사용가능한 랜카드의 ip주소를 사용하라는 의미이다.일반 PC경우의 랜카드 1개임
    serv_adr.sin_port=htons(atoi(argv[1]));//포트번호를 프로토콜의 맞게 빅엔디안 방식으로 바꿔줌

    if(bind(serv_sock,(sockaddr*)&serv_adr,sizeof(serv_adr))==-1)//IP,포트번호를 소켓에 연결해줌
        error_handling("bind() error");
    if(listen(serv_sock,5)==-1)//대기
        error_handling("listen() error");
    
    clnt_adr_sz=sizeof(clnt_adr);//소켓길이를 알기위해서 SIZEOF사용

    for ( i = 0; i < 5; i++)
    {
        opnd_cnt=0;
        clnt_sock=accept(serv_sock,(sockaddr*)&clnt_adr,&clnt_adr_sz);
        read(clnt_sock,&opnd_cnt,1);//클라이언트 소켓에서 opnd_cnt를 버퍼로 1바이트만큼만 읽겠다.

        recv_len=0;
        while ((opnd_cnt*OPSZ+1)>recv_len)//소켓에서 읽어온데이터가 cnt*4+1보다 크면 탈출한다.  
        {
            recv_cnt=read(clnt_sock,&opinfo[recv_len],BUF_SIZE-1);//시작은 클라이언트 소켓에서opinfo[0]번지주소를 주고,
                                                                  //BUF_SIZE-1 만큼 읽겠다. 반환값은 읽어온 데이터size
            recv_len+=recv_cnt;//처음 recv_len=recv_len+recv_cnt(소켓에서 읽어온 데이터 size) 
        }
        //위에서 opinfo에 저장한 데이터를 int*로 읽고 opinfo[받은길이-1]번째 데이터(아마 연산자를입력함)를 매개변수로함
        result=calculate(opnd_cnt,(int*)opinfo,opinfo[recv_len-1]);
        write(clnt_sock,(char*)&result,sizeof(result));//다시 클라이언트로 보낼땐 문자열로 보내야해서 문자열로 바꿔줌
        close(clnt_sock);//소켓닫기
    }
    close(serv_sock);
    return 0;
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}
int calculate(int opnum,int opnds[],char op)//opnum은 몇개의 숫자를 입력받았는지,opnds[]는 버퍼로읽어온 데이터,op는 마지막에 입력받은 연산자
{
    int result = opnds[0];
    int i;
    //opnds[0] 번째에서는 몇개의 데이터를 받을지 물어보는 oprand count 데이터가 들어있다.
    //따라서 opnds[1] 번째 부터 더하기 시작한다
    //opnum = oprand count에 입력한 숫자
    switch (op)
    {
    case '+' /* constant-expression */:
        /* code */for ( i = 1; i < opnum; i++) result+=opnds[i];
        break;
    case '-' /* constant-expression */:
        /* code */for ( i = 1; i < opnum; i++) result-=opnds[i];
        break;
    case '*' /* constant-expression */:
    /* code */for ( i = 1; i < opnum; i++) result*=opnds[i];
        break;
    default:
        break;
    }
    return result;
}