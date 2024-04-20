#include<iostream>
#include "point.h"
#include"rectangle.h"
#include "point.cpp"
#include "rectangle.cpp"
using namespace std;

int main()
{
    point pos1;
    if(!pos1.InitMembrs(-2,4))
        cout<<"초기화 실패"<<endl;
    if(!pos1.InitMembrs(2,4))
        cout<<"초기화 실패"<<endl;
    point pos2;
    if(!pos2.InitMembrs(5,9))
        cout<< "초기화 실패" <<endl;
    rectangle rec;
    if(!rec.InitMembers(pos2,pos1))
        cout << "직사각형 초기화 실패" <<endl;
    if(!rec.InitMembers(pos1,pos2))
        cout << "직사각형 초기화 실패" <<endl;
    rec.ShowRecInfo();
    return 0;    
} 
