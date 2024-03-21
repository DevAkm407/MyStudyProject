#include<stdio.h>
#include<arpa/inet.h>

//intet_addr은 문자로된 ip를 숫자로 바꾸어준다.

int main(int argc,char *argv[]){
   const char* addr1="1.2.3.4";
   const char* addr2="1.2.3.256";

    unsigned long conv_addr=inet_addr(addr1);
    conv_addr=htonl(conv_addr);
    if(conv_addr == INADDR_NONE)
        printf("Error Occured!\n");
    else
        printf("NETwork ordered integer addr: %#lx \n",conv_addr);
    
    conv_addr=inet_addr(addr2);
    if(conv_addr==INADDR_NONE)
        printf("Error Occured!\n");
    else
        printf("NETwork ordered integer addr: %#lx \n",conv_addr);
    return 0;
}