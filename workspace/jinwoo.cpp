#include <string>
#include <iostream>
#include<random>
#include<unistd.h>
#include "jinwoo.h"
jinwoo::jinwoo()
{
std::cout << "이름을 입력해주세요: ";
getline(std::cin,name);
level=1;
expBar=30000;
exp=0;  
}
jinwoo::jinwoo(const std::string myname,int mylevel,int myexpBar)
{
    name=myname;
    level=mylevel;
    this->expBar=myexpBar;
}
jinwoo::~jinwoo()
{
}

int jinwoo::callrandom(int count)
{
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rexp(-3500,3500); //정수 균등분포 -3500에서 3500이 뽑힐 확률이 균등하다
    if (count ==0)
    {
        int rep=rexp(gen);
        return rep;
    }
    
    return -1; 
}
double jinwoo::callrandom(double count)
{
    using namespace std;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> mulexp(1.0,5.0);//실수 균등 분포 1.0~5.0이 뽑힐확률이 균등하다
    uniform_real_distribution<double> ebmul(1.8,2.5);//실수 균등 분포 1.8~2.5이 뽑힐확률이 균등하다
    if (count ==1.0)
    {
        int mul=mulexp(gen);
        return mul;
    }
     if (count ==2.0)
    {
        int ebb=ebmul(gen);
        return ebb;
    }
    return -1; 
}
void jinwoo::fight()
{
    double bonus=jinwoo::callrandom(1.0);
    if(bonus ==-1)
    {
        std::cout << "랜덤 뽑기 매개변수 지정오류"<<std::endl;
        exit(-1);
    }
    for(int i=0; i <5; i++)
    {
    double getExp=jinwoo::callrandom(0);
     if(getExp ==-1)
    {
        std::cout << "랜덤 뽑기 매개변수 지정오류"<<std::endl;
        exit(-1);
    }
    std::cout <<"한턴의 "<<i<<"번째 입니다."<<std::endl;
    std::cout << "경험치를 획득하셨습니다: " <<getExp<<std::endl;
    std::cout << "경험치 배율은: "<<bonus<<" 입니다.\n";
    this->exp+=getExp*bonus;
    jinwoo::levelUp();
    jinwoo::levleDown();
    }

}


void jinwoo::levelUp()
{
if(this->exp > this->expBar)
{
    this->level++;
    this->expBar*=jinwoo::callrandom(2.0);
    std::cout <<"레벨업!!: "<< this->level<<std::endl;
    std::cout<<"경험치통: "<<this->expBar << std::endl;
}
if(this->level==99)
{
    std::cout <<"축하합니다 99레벨입니다."<<std::endl;
    exit(0);
}
}

void jinwoo::levleDown()
{
    if(this->exp < 0 )
    {
        this->level--;
        if(level<=0){
            std::cout<<"사망 하셨습니다.\n";
            exit(0);
        }
        std::cout <<"레벨이 낮아졌습니다... 현재 레벨: "<<this->level<<std::endl;
    }
}

void jinwoo::query()
{
    using namespace std;
    string answer;
    while(true)
    {
        cout <<"턴을 진행하시겠습니까? yes or no: ";
        getline(cin,answer);
        if(answer.compare("yes")== 0||answer.compare("y")==0||answer.compare("Y")==0)
            {
                cout <<"턴을 진행합니다.\n";
                break;
            }
        else if(answer.compare("no")== 0||answer.compare("n")==0||answer.compare("N")==0)
        {
            cout<<"현재 레벨: "<< this->level <<"현재 경험치: "<< this->exp <<"현재 경험치통: "<<this->expBar<<endl;
            cout<<"게임 종료\n";
            exit(0);
        }
        else
            cout << "긍정은 yes, y , Y 부정은 no, n, n 를 입력해주세요"<<endl;
    }

}