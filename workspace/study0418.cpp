// #include <iostream>
// #include <cstring>
// using namespace std;

// class First
// {
// private:
//     char * strOne;
// public:
//     First(char * str)
//     {
//         strOne=new char[strlen(str)+1];
//     }
//   virtual ~First()
//     {
//         cout<<"~First()"<<endl;
//         delete[]strOne;
//     }
// };

// class Second:public First
// {
// private:
//     char * strTwo;
// public:
//     Second(char * str1,char *str2):First(str1)
//     {
//         strTwo=new char[strlen(str2)+1];
//     }
//     ~Second()
//     {
//         cout<<"~Second()"<<endl;
//         delete []strTwo;
//     }
// };

// int main()
// {
//     First * ptr=new Second("simple","complex");
//     delete ptr;
//     return 0;
// }

// #include <iostream>
// using namespace std;

// class Point
// {
// private:
//     int xpos,ypos;
//     /* data */
// public:
//     Point(int x=0,int y=0):xpos(x),ypos(y)
//     {}
//     void ShowPosition() const
//     {
//         cout <<'[' <<xpos <<", "<<ypos<<']'<<endl;
//     }
//     Point operator+(const Point&ref)
//     {
//         Point pos(xpos+ref.xpos,ypos+ref.ypos);
//         return pos;
//     }
// };

// int main()
// {
//     Point pos1(3,4);
//     Point pos2(10,20);
//     Point pos3=pos1+pos2;
//     pos1.ShowPosition();
//     pos2.ShowPosition();
//     pos3.ShowPosition();
//     return 0;
// }

// #include<iostream>
// using namespace std;

// class Point
// {
// private:
//     int xpos,ypos;
//     /* data */
    
// public:
//     Point(int x=0,int y=0):xpos(x),ypos(y)
//     {}
//     void ShowPosition() const
//     {
//         cout <<'[' <<xpos <<", "<<ypos<<']'<<endl;
//     }
//     Point operator+(const Point&ref)
//     {
//         Point pos(xpos+ref.xpos,ypos+ref.ypos);
//         return pos;
//     }
//    friend ostream& operator<<(ostream& os, const Point& pos);
// };

// //진짜 많이 씀
// ostream& operator<<(ostream& os, const Point& pos)
// {
//     os<<'['<<pos.xpos<<", "<<pos.ypos<<']'<<endl;
//     return os;
// }

// int main()
// {
//     Point pos1(1,3);
//     cout<<pos1;
//     Point pos2(101,303);
//     cout<<pos2;
//     return 0;
// }

// #include<iostream>
// using namespace std;

// class Point
// {
// private:
//     int xpos,ypos;
//     /* data */
    
// public:
//     Point(int x=0,int y=0):xpos(x),ypos(y)
//     {}
//     void ShowPosition() const
//     {
//         cout <<'[' <<xpos <<", "<<ypos<<']'<<endl;
//     }
//     Point operator+(const Point&ref)
//     {
//         Point pos(xpos+ref.xpos,ypos+ref.ypos);
//         return pos;
//     }
//     friend ostream& operator<<(ostream& os, const Point& pos);
//     friend istream& operator>>(istream&,Point& pos);
// };

// ostream& operator<<(ostream& os, const Point& pos)
// {
//     os<<'['<<pos.xpos<<", "<<pos.ypos<<']'<<endl;
//     return os;
// }

// istream& operator>>(istream& is,Point& pos)
// {
//     is>>pos.xpos>>pos.ypos;
//     return is;
// }

// int main()
// {
//     Point pos1;
//     cout<<"x, y 좌표 순으로 입력: ";
//     cin>>pos1;
//     cout<<pos1;
//     return 0;
// }

// #include <iostream>
// using namespace std;
// class First
// {
// private:
//     int num1,num2;
//     /* data */
// public:
//     First(int n1=0,int n2=0/* args */):num1(n1), num2(n2)
//     {}
//     void ShowData() {cout << num1 <<", "<<num2<<endl; }
// };

// class Second
// {
// private:
//     int num3, num4;
//     /* data */
// public:
//     Second(int n3=0,int n4=0/* args */):num3(n3),num4(n4)
//     {}
//     void ShowData() {cout << num3 <<", "<<num4<<endl; }     
//     Second& operator=(const Second& ref)
//     {
//         cout<<"Second& operator=()"<<endl;
//         num3=ref.num3;
//         num4=ref.num4;
//         return *this;
//     }
// };

// int main()
// {
//     First fsrc(111,222);
//     First fcpy;
//     Second ssrc(333,444);
//     Second scpy;
//     fcpy=fsrc;
//     scpy=ssrc;
//     fcpy.ShowData();
//     scpy.ShowData();

//     First fob1,fob2;
//     Second sob1,sob2;
//     fob1=fob2=fsrc;
//     sob1=sob2=ssrc;

//     fob1.ShowData();
//     fob2.ShowData();
//     sob1.ShowData();
//     sob2.ShowData();
//     return 0;
// }

#include <iostream>
#include <cstring>

using namespace std;

class Person
{
private:
    /* data */
    char*name;
    int age;
public:
    Person(char* myname, int myage)
    {
        int len=strlen(myname)+1;
        name=new char[len];
        strcpy(name,myname);
        age=myage;
    }
    Person(const Person &copy):age(copy.age)
    {
        name= new char[strlen(copy.name)+1];
        strcpy(name,copy.name);
        cout <<"call the copy constructor"<<endl;
    }

    void ShowPersonInfo() const
    {
        cout << "이름: "<<name<<endl;
        cout << "나이: "<<age <<endl;
    }
    Person& operator=(const Person& ref)
    {
        delete[]name;
        int len=strlen(ref.name)+1;
        name=new char[len];
        strcpy(name,ref.name);
        age=ref.age;
        cout <<"call the = operator"<<endl;
        return *this;
    }
    ~Person()
    {
        delete []name;
        cout<<"called destructor!"<<endl;

    }
};

int main()
{
    Person man1("Lee dong woo",29);
    Person man2("Yoon ji yul",22);
    man2=man1;
    Person man3 =man2;
    man1.ShowPersonInfo();
    man2.ShowPersonInfo();
    man3.ShowPersonInfo();
    return 0;
}