#include<iostream>
#include<unistd.h>
using namespace std;
int gval=10;
int main(int argc, char *argv[])
{
    pid_t pid;
    int lval=20;
    
    lval+=5;
    gval++;
    pid=fork();

    if(pid==0)
        gval+=2,lval+=2;
    else
        gval-=2,lval-=2;
    
    if(pid==0)
        cout<<"child proc:"<<gval<<", "<<lval<<endl;
    else
        cout<<"parent proc: "<<gval<<", "<<lval<<endl;
    return 0;
}