#include<iostream>
#include <string>
#include <iostream>
#include<random>
#include<unistd.h>
#include "jinwoo.h"
#include "jinwoo.cpp"
int main()
{
    jinwoo* boki=new jinwoo;
    while(1)
    {
       if(boki->easycountreturn()==0)
            boki->fight();
       
       if(boki->easycountreturn()==0) 
            boki->query();
       else
       {
       jinwoo boki2=*boki;
       delete boki;
       while (1)
        {
            boki2.fight();
            boki2.query();
        }
       }    
    }    
    
    return 0;
}