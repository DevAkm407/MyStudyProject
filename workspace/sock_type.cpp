// #include<iostream>
// #include<string.h>
// #include<string>
// #include<unistd.h>
// #include<arpa/inet.h>
// #include<sys/socket.h>

// using namespace std;
// void error_handling(string message);

// int main(int argc, char *argv[])
// {
//     int tcp_sock,udp_sock;
//     int sock_type;
//     socklen_t optlen;
//     int state;
//     optlen=sizeof(sock_type);
//     tcp_sock=socket(PF_INET,SOCK_STREAM,0);
//     udp_sock=socket(PF_INET,SOCK_DGRAM,0);
//     cout<<"SOCK_STREAM: "<<SOCK_STREAM<<endl;
//     cout<<"SOCK_DGRAM: "<<SOCK_DGRAM<<endl;

//     state=getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
//     if(state)
//         error_handling("getsockopt() error!");
//     cout<<"Socket type one:" <<sock_type<<endl;

//     state=getsockopt(udp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
//     if(state)
//         error_handling("getsockopt() error!");
//     cout<<"Socket type one:" <<sock_type<<endl;

//     return 0;
// }

// void error_handling(string message)
// {
//     cerr<<message<<endl;
//     exit(1);
// }

#include<iostream>
#include<string.h>
#include<string>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

using namespace std;
void error_handling(string message);

int main(int argc, char *argv[])
{
    int sock;
    int snd_buf,rcv_buf;
    socklen_t len;
    int state;
    len=sizeof(snd_buf);
    sock=socket(PF_INET,SOCK_STREAM,0);
    
    state=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,&len);
    if(state)
        error_handling("getsockopt() error!");
    cout<<"Socket type one:" <<endl;
    len=(rcv_buf);
    state=getsockopt(sock,SOL_SOCKET,SO_TYPE,(void*)&rcv_buf,&len);
    if(state)
        error_handling("getsockopt() error!");
    cout<<"Input buffer size: " <<rcv_buf <<endl;
    cout<<"Output buffer size: " <<snd_buf <<endl;

    return 0;
}

void error_handling(string message)
{
    cerr<<message<<endl;
    exit(1);
}
