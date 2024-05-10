#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;
void timeout(int sig)
{
    if(sig==SIGALRM)
        cout<<"Time out!"<<endl;
        alarm(2);
}

void keycontrol(int sig)
{
    if(sig==SIGINT)
        cout<<"CTRL+C pressed"<<endl;
}

int main(int argc,char *argv[])
{
    int i;
    signal(SIGALRM,timeout);
    signal(SIGINT,keycontrol);
    alarm(2);

    for(i=0;i<3;i++)
    {
        cout<<"wait...";
        sleep(100);
    }
    return 0;
}