#include <iostream>
#include "rectangle.h"
using namespace std;

bool rectangle::InitMembers(const point &ul, const point &lr)
{
    if(ul.GetX()>lr.GetX() || ul.GetY()>lr.GetY())
    {
        cout << "잘못된 위치정보 전달" << endl;
        return false;
    }
    upLeft=ul;
    lowRight=lr;
    return true;
}

void rectangle::ShowRecInfo() const
{
    cout << "좌 상단: " <<'[' << upLeft.GetX()<<", ";
    cout<<upLeft.GetY()<<']'<<endl;
    cout <<"우 하단: "<< '[' << lowRight.GetX()<<", ";
    cout <<lowRight.GetY() << ']' <<endl <<endl;
}
