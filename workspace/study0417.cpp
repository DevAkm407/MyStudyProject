// #include <iostream>
// #include <cstring>
// using namespace std;
// class Girl;

// class Boy
// {
// private:
//     int height;
//     friend class Girl;
// public:
//     Boy(int len) : height(len)
//     {}
//     void ShowYourFriendInfo(Girl &frn);
// };

// class Girl
// {
//     private:
//         char phNum[20];
//     public:
//         Girl(char * num)
//         {
//             strcpy(phNum,num);
//         }
//     void ShowYourFriendInfo(Boy &frn);
//     friend class Boy;
// };

// void Boy::ShowYourFriendInfo(Girl &frn)
// {
//     cout <<"Her phone number: " << frn.phNum <<endl;
// }

// void Girl::ShowYourFriendInfo(Boy &frn)
// {
//     cout << "His height: " << frn.height << endl;
// }

// int main()
// {
//     Boy boy(170);
//     Girl girl("010-1234-5678");
//     boy.ShowYourFriendInfo(girl);
//     girl.ShowYourFriendInfo(boy);
//     return 0;
// }

// #include <iostream>
// using namespace std;

// class SoSimple
// {
// private:
//   static int simObjCnt;
// public:
//     SoSimple(/* args */)
//     {
//         simObjCnt++;
//         cout <<simObjCnt << "번째 SoSimple 객체" <<endl;
//     }    
// };
// int SoSimple::simObjCnt=0; 

// class SoComplex
// {
// private:
//   static int cmxObjCnt;
// public:
//   SoComplex(/* args */)
//   {
//     cmxObjCnt++;
//     cout<<cmxObjCnt<<"번째 SoComplex 객체"<<endl;
//   }
//   SoComplex(SoComplex &copy)
//   {
//     cmxObjCnt++;
//     cout<<cmxObjCnt<<"번째 SoComplex 객체"<<endl;
//   }
// };
// int SoComplex::cmxObjCnt=0;

// int main()
// {
//   SoSimple sim1;
//   SoSimple sim2;

//   SoComplex cmx1;
//   SoComplex cmx2=cmx1;
//   SoComplex();
//   return 0;
// }

/*
클래스 선언 정의

class 클래스 이름
{
  private: 보통 맴버 변수를 정의한다. 맴버 변수들은 맴버 함수내에서 중요한 역활을 할 것이기 때문에 함부로 변경하지 못하게 막는다.
  대충 변수
  대충 변수

  public: private: 부분은 이부분을 만나는 순간 범위가 끝난다. public은 클래스가 가지고 있는 속성을 반영하는 맴버 함수들을 보통가지고 있다.
  생성자  #맴버변수를 초기화하는 함수를 만들고 그 함수를 찾는 과정은 귀찮은 과정이다. 생성자를 통해 필요한 맴버 변수들을 초기화한다.
  소멸자  #클래스가 없어지면서 해야할 일들을 한다. 보통 힙에 때려박은 변수들을 delete하는대 사용한다.
  값 가져오는 함수 get(대충 필요한 값) #일단 get이라는 이름은 그냥 지어준거다.std가 아니다. private로 선언된 변수에 접근할 수 없기 때문에 get을 이용해 값을 불러오자
  값 수정하는 함수 set(대충 변경할 값) #이것도 그냥 set이라고 지어준것이다.private로 선언된 변수에 직접적인 간섭이 안되니 함수가 허락하는 변수들을 함수를 이용해 수정하자.
  대충 함수
  대충 함수
}; <-클래스 선언이 끝났다는걸 ;으로 표현해준다.

생성자 오버로딩이란 처음에 초기화 할때 여러가지 옵션을 넣고 싶을때 사용한다.
안쪽에 a,b,c이렇게 3개의 값을 지정해 줄때 a,b,c를 한번에 a,b만 a,c만 이렇게 다양하게 초기화 할수있는 옵션을 제공한다.
객체를 생성하는 사용자는 따로 함수를 찾아보는게 아닌 단순하게 값을 몇개 넣을 것인가만 고민하면 자동으로 사용된다.
(디폴트 매개변수를 사용하면 여러 상황에서 오버로딩보다 편할 수 있다)

초기화리스트,멤버 이니셜라이저
생성자로 변수들을 초기화해야하는대 const가 있다던지 &타입이라던지 이런것들은 생성과 동시에 값이 들어가야만한다.
그런대 매개변수를 통해 값을 넣어주는 방식으론 어려우니 생성과 동시에 값을 넣어주는 : 이니셜라이저를 이용해 편리하게 해결하자
(속도도 빨라진다)

파괴자란 객체가 없어지는 순간에 자동으로 실행되는 함수이다. 이 함수를 통해서 객체내부에 만들어진 힙영역데이터들을 delete해줄 수 있고
객체가 끝나면서 무언가 해야할일이 있다면 이 파괴자를 통해서 구현하면된다.

this포인터란 내가 만든 객체안에서 나 자신을 가르키는 포인터이다. 나 자신을 표현한거나 명시적으로 객체 자신의 데이터라는 것을 표현할때
사용하면 유용하다.

클래스를 활용해서 객체 선언하는 방법

클래스이름 객체이름; 으로 선언한다 #class name;

1.객체를 stack에 선언하는 방법 -> class name; 또는 class name(초기설정);

2.객체를 stack에 선언하는 방법 -> class* name= new class;

객체를 통해서 맴버 변수에 접근하는 방법

객체.get() #가져오기. 당연히 해당 함수는 직접구현해야한다.

객체.set() #수정하기. 당연히 해당 함수는 직접구현해야한다.

만약 public에 변수를 선언해다면

객체.변수이름 으로 접근할 수 있다


복사 생성자란 무엇인가?

복사 생성자는 객체가 객체를 복사할때 실행되는 함수다.

디폴트 복사 생성자는 평소에 변수들을 복사할때 일어나는 값복사이다. int a=3; int b=a; 이렇게 하면 a의 값인3을 b가 복사하는 것처럼말이다.
그런대 int c=3; int* a=&c; 경우에 int* b=a; 이렇게 하면 어떤 일이 일어날까? 알다싶이 b는 a의 값인 c의 주소를 가져간다.
그러면 b는 c를 가르키게 되고 a와 b모두 c를 가르키는 일이 일어난다.
디폴트 복사 생성자는 이런 일을 일으키는 문제가 있다.
객체 name= 객체vain
이렇게 복사가 일어나면 name에 포인터 변수들의 주소를 vain의 포인터 변수가 가르키게 된다.

만약 name이 없어져 버리면 vain은 쓰래기 값이 들어간 없어져 버린 name의 잔재를 가르킬 수 도 있다.

이러한 현상을 얕은 복사라고 한다.

깊은 복사는 같은 주소를 가르키게 하지 않고 따로 동적으로 힙메모리를 할당해주어서 객체에 포인터가 자신만의 
데이터를 가지게 해주는 것이다. 새로 힙메모리를 할당해주고 그메모리 주소를 주면
복사해온 객체가 없어져도 복사가 끝난 객체의 포인터들이 가르키는 데이터와 주소는 여전히 힙영역에 잘 보관되어있을 것이다.

깊은 복사 방법
생성자(const classname& 이름)
:생성자(이름)
{
  포인터타입 변수=new 데이터타입(*이름.변수) #복사해오는 객체의 변수도 포인터이기 때문에 값에 접근하려면 * 을 이용해야한다.
}

*/



/*
class Cat: public Animal{}; #이경우는 Cat. 으로 Animal의 함수를 이용할 수 있다.

class Honda: prvate Car {}; #이경우는 Honda. 으로 Car의 함수를 이용할 수는 없지만 Honda 내부에서 Car를 이용할 수 있다.

class Honda: protect Car {}; #이경우는 Honda를 상속한 무언가가 Car의 기능을 내부에서 사용할 수 있다.

*/


/*
Enterprise resource planning system
ERP system 전사적 자원 관리시스템

*/


// #include <iostream>
// #include <cstring>
// using namespace std;

// class PermanentWorker
// {
// private:
//   char name[100];
//   int salary;
// public:
//   PermanentWorker(char* name,int money)
//     : salary(money)
//     {
//       strcpy(this->name,name);
//     }
//     int GetPay() const
//     {
//       return salary;
//     }
//     void ShowSalaryInfo() const
//     {
//       cout << "name: " <<name <<endl;
//       cout << "salary: " <<GetPay()<<endl<<endl;
//     }
// };

// class EmplyeeHandler
// {
// private:
//   PermanentWorker* empList[50];
//   int empNum;
// public:
//   EmplyeeHandler(/* args */) :empNum(0)
//   {}
  
//   void AddEmployee(PermanentWorker* emp)
//   {
//     empList[empNum++]=emp;
//   }

//   void ShowAllSalaryinfo() const
//   {
//     for(int i=0; i< empNum; i++)
//       empList[i]->ShowSalaryInfo();
//   }

//   void ShowTotalSalary() const
//   {
//     int sum=0;
//     for (int i=0; i<empNum; i++)
//       sum+=empList[i]->GetPay();
//     cout<<"salary sum: "<<sum<<endl;
//   }
//   ~EmplyeeHandler()
//   {
//     for(int i=0; i<empNum; i++)
//       delete empList[i]; 
//   }
// };

// int main()
// {
//   EmplyeeHandler handler;

//   handler.AddEmployee(new PermanentWorker("KIM",1000));
//   handler.AddEmployee(new PermanentWorker("LEE",1500));
//   handler.AddEmployee(new PermanentWorker("JUN",2000));

//   handler.ShowAllSalaryinfo();
//   handler.ShowTotalSalary();
//   return 0;
// }

// #include <iostream>
// #include <cstring>
// using namespace std;

// class Person
// {
// private:
//   int age;
//   char name[50];
// public:
//   Person(int myage, char *myname) :age(myage)
//   {
//     strcpy(name,myname);
//   }

//   void WhatYourName() const
//   {
//     cout << "My name is "<<name<<endl;
//   }

//   void HowOldAreYou() const
//   {
//     cout<<"I'm" <<age <<" years old" <<endl;
//   }
// };

// class UnivStudent:public Person
// {
// private:
//   char major[50];
// public:
//   UnivStudent(char * myname,int myage,char * mymajor):Person(myage,myname)
//   {
//     strcpy(major,mymajor);
//   }
//   void WhoAreYou() const
//   {
//     WhatYourName();
//     HowOldAreYou();
//     cout<<"My major is " << major <<endl <<endl;
//   }
// };

// int main()
// {
//   UnivStudent ustd1("Lee",22,"Computer eng.");
//   ustd1.WhoAreYou();

//   UnivStudent ustd2("Yoon",21,"Electronic eng.");
//   ustd2.WhoAreYou();
//   return 0;
// }

// #include <iostream>
// using namespace std;

// class Sobase
// {
// private:
//   int baseNum;
// public:
//   Sobase(/* args */) :baseNum(20)
//   {
//     cout <<"soBase()" <<endl;
//   }
//   Sobase(int n) :baseNum(n)
//   {
//     cout <<"soBase(int n)" <<endl;
//   }
//   void ShowBaseData()
//   {
//     cout<<baseNum<<endl;
//   }
// };

// class SoDerived : public Sobase
// {
// private:
//   int derivNum;
// public:
//   SoDerived(/* args */) : derivNum(30)
//   {
//     cout <<"SoDerived()"<<endl;
//   }
//   SoDerived(int n) : derivNum(n)
//   {
//     cout <<"SoDerived(int n)"<<endl;
//   }
//   SoDerived(int n1,int n2) : Sobase(n1),derivNum(n2)
//   {
//     cout <<"SoDerived(int n1,int n2)"<<endl;
//   }
  
//   void ShowDerivData()
//   {
//     ShowBaseData();
//     cout<<derivNum<<endl;
//   }
// };

// int main()
// {
//   cout<<"case1.... "<<endl;
//   SoDerived dr1;
//   dr1.ShowDerivData();
//   cout<<"------------------"<<endl;
//   cout<<"case2...." <<endl;
//   SoDerived dr2(12);
//   dr2.ShowDerivData();
//   cout<<"------------------" <<endl;
//   SoDerived dr3(23,24);
//   dr3.ShowDerivData();
//   return 0;
// }


/*
다형성(Polymorphism)

C++의 바인딩 방식은 정적 바인딩이다
내가 처음에 지정한 형태로만 생성이 된다.

그래서 virtual을 붙여주면 런타임시 객체에 함수를 결정할 수 있다.

부모의 class* 로 자식의 객체를 동적으로 생성했더라도
자식의 멤버함수를 실행시킬 수 있다.
*/

/*
함수 오버라이딩이란?
부모클래스의 함수를 같은 이름의 함수로 
자식클래스에서 변경해서 사용하는 것

*/

// #include <iostream>
// using namespace std;

// class Person
// {
// public:
//  virtual void Sleep() { cout<<"Sleep"<<endl;}
// };

// class Student:public Person
// {
// public:
// virtual void Study() { cout<<"Study"<<endl;}
// virtual void Sleep() { cout<<"Sleep2"<<endl;}
// };

// class PartTimeStudent:public Student
// {
// public:
// virtual void Work() { cout<<"Work"<<endl;}
// };

// int main()
// {
//   Person* ptr1 =new Student();
//   Person* ptr2 =new PartTimeStudent();
//   Student* ptr3=new PartTimeStudent();
//   ptr1->Sleep();
//   ptr2->Sleep();
//   ptr3->Study();
//   delete ptr1; delete ptr2; delete ptr3;
//   return 0;
// }

// #include <iostream>
// #include <cstring>
// using namespace std;

// class Employee
// {
// private:
//   char name[100];
// public:
//   Employee(char * name)
//   {
//     strcpy(this->name,name);
//   }
//   void ShowYourName() const
//   {
//     cout <<"name: "<<name<<endl;
//   }
// };

// class PermanentWorker:public Employee
// {
// private:
//   int salary;
// public:
//   PermanentWorker(char* name,int money)
//     :Employee(name),salary(money)
//     {}
//   int GetPay() const
//   {
//     return salary;
//   }
//   void ShowSalaryInfo() const
//   {
//     ShowYourName();
//     cout<<"salary: "<<GetPay()<<endl<<endl;
//   }
// };

// class EmplyeeHandler
// {
// private:
//   Employee* empList[50];
//   int empNum;
// public:
//   EmplyeeHandler(/* args */) :empNum(0)
//   {}
//   void AddEmployee(Employee* emp)
//   {
//     empList[empNum++]=emp;
//   }
//   void ShowAllSalryInfo() const
//   {

//   }
//   void ShowTotalSalary() const
//   {
//       int sum=0;
//       cout<<"salary sum: "<<sum<<endl;
//   }
//   ~EmplyeeHandler()
//   {
//     for (int i = 0; i < empNum; i++)
//     {
//       delete empList[i];
//     }    
//   }
// };

// int main()
// {
//   EmplyeeHandler handler;

//   handler.AddEmployee(new PermanentWorker("Kim",1000));
//   handler.AddEmployee(new PermanentWorker("LEE",1500));
//   handler.AddEmployee(new PermanentWorker("JUN",2000));

//   handler.ShowAllSalryInfo();
//   handler.ShowTotalSalary();
//   return 0;
// }


// #include <iostream>
// #include <cstring>
// using namespace std;

// class Employee
// {
// private:
//   char name[100];
// public:
//   Employee(char * name)
//   {
//     strcpy(this->name,name);
//   }
// virtual  void ShowYourName() const
//   {
//     cout <<"name: "<<name<<endl;
//   }
//  virtual int GetPay() const
//   {}
// };

// class PermanentWorker:public Employee
// {
// private:
//   int salary;
// public:
//   PermanentWorker(char* name,int money)
//     :Employee(name),salary(money)
//     {}
// virtual  int GetPay() const
//   {
//     return salary;
//   }
// virtual  void ShowSalaryInfo() const
//   {
//     ShowYourName();
//     cout<<"salary: "<<GetPay()<<endl<<endl;
//   }
// };

// class TemporaryWorker:public Employee
// {
// private:
//   int workTime;
//   int payPerHour;
// public:
//   TemporaryWorker(char*name,int pay/* args */)
//   :Employee(name),workTime(0),payPerHour(pay)
//   {}
// virtual  void AddWorkTime(int time)
//   {
//     workTime+=time;
//   }

//  virtual int GetPay() const
//   {
//     return workTime*payPerHour;
//   }

// virtual  void ShowSalaryInfo() const
//   {
//     ShowYourName();
//     cout<<"salary: "<<GetPay()<<endl<<endl;
//   }
// };

// class SalesWorker:public PermanentWorker
// {
// private:
//   int salesResult;
//   double bonusRatio;
// public:
//   SalesWorker(char*name,int money,double ratio/* args */)
//   :PermanentWorker(name,money),salesResult(0),bonusRatio(ratio)
//   {}
// virtual  void AddSalesResult(int value)
//   {
//     salesResult+=value;
//   }

// virtual  int GetPay() const
//   {
//     return PermanentWorker::GetPay()+(int)(salesResult*bonusRatio);
//   }

// virtual  void ShowSalaryInfo() const
//   {
//     ShowYourName();
//     cout<<"salary: "<<GetPay()<<endl<<endl;
//   }
// };

// class EmplyeeHandler
// {
// private:
//   Employee* empList[50];
//   int empNum;
// public:
//   EmplyeeHandler(/* args */) :empNum(0)
//   {}
//   void AddEmployee(Employee* emp)
//   {
//     empList[empNum++]=emp;
//   }
//   void ShowAllSalryInfo() const
//   {
//     for (int i = 0; i < empNum; i++)
//       {
//         empList[i]->ShowYourName();
//         /* code */
//       }
//   }
//   void ShowTotalSalary() const
//   {
//       int sum=0;
//       for (int i = 0; i < empNum; i++)
//       {
//         sum+=empList[i]->GetPay();
//         /* code */
//       }
      
//       cout<<"salary sum: "<<sum<<endl;
//   }
//   ~EmplyeeHandler()
//   {
//     for (int i = 0; i < empNum; i++)
//     {
//       delete empList[i];
//     }    
//   }
// };

// int main()
// {
//   EmplyeeHandler handler;
//   handler.AddEmployee(new PermanentWorker("KIM",1000));
//   handler.AddEmployee(new PermanentWorker("LEE",1500));

//   TemporaryWorker * alba=new TemporaryWorker("Jung",700);
//   alba->AddWorkTime(5);
//   handler.AddEmployee(alba);

//   SalesWorker* seller=new SalesWorker("Hong",1000,0.1);
//   seller->AddSalesResult(7000);
//   handler.AddEmployee(seller);

//   handler.ShowAllSalryInfo();
//   handler.ShowTotalSalary();
//   return 0;
// }

