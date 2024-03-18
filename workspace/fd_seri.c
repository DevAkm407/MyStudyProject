#include<stdio.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/socket.h>

int main(){
    int fd1, fd2 ,fd3;
    //PF_INET는 IPv4인터넷 프로토콜을 이용하겠다는 상수적 표현이다.
    //SOCK_STREAM은 데이터를 순서대로 보내주는대신 느리다. 이전의 데이터가 도착하지못하면
    //데이터가 쌓여버린다.
    //SOCK_STREAM은 일단 데이터를 보내고본다.그래서 데이터를받으면 순서가 엉망일 수 있다.\
    //하지만 받는 사람이 그데이터를 조립하는 순서를 안다면 데이터를 무사히 받아 사용 할 수 있을 것이다.
    //마지막 인자는 프로토콜을 좀더 세밀하게 사용하기 위해서 지정하는 부분이다. 
    //특별한 경우가 아니면 TCP는 TCP로 UDP는 UDP로 사용할것 같다.
    fd1=socket(PF_INET,SOCK_STREAM,0);// 즉 이문장은 fd1을 소켓으로 사용할 것이고 IPv4인터넷 프로토콜
    //을 이용할것이며 보내는 방식은 순차적으로 데이터를 보내지만 느린방식으로 보내겠다는 것이다.
    //socket함수는 함수를 성공적으로 실행하면 파일 디스크립터를 반환한다.
    fd2=open("text.dat",O_CREAT|O_WRONLY|O_TRUNC);
    //fd2는 파일을 제어하는 대 사용하겠다는 것이다. text.dat라는 파일을 만들것이며
    //오직 쓰기만 가능하고 기존에 데이터가 있다면 모두 제거할것이라는 말이다.
    //open함수는 함수를 성곡적으로 실행하면 파일 디스크립터를 반환한다.
    fd3=socket(PF_INET,SOCK_DGRAM,0);
    //fd3는 IPv4프로토콜을 사용할 것이고 빠르지만 데이터가 순서대로 가진않을것이다.
    //따라서 사용자는 받은데이터를 순서에 맞게 제조립해야한다.

    printf("file descriptor 1:%d\n", fd1);
    printf("file descriptor 2:%d\n",fd2);
    printf("file descriptor 3:%d\n",fd3);
    close(fd1);//socket도 파일이기때문에 닫아줘야함
    close(fd2);//파일을 닫아줘야함
    close(fd3);//위와동일
    return 0;

       
    
}