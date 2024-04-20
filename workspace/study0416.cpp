// #include <iostream>
// using namespace std;

// class AAA
// {
// public:
//     AAA()
//     {
//         cout << "empty object" << endl;
//     }
//     void showYourname()
//     {
//         cout << "I'm class AAA" << endl;
//     }
// };

// class BBB
// {
// private:
//     AAA &ref;
//     const int & num;

// public:
//     BBB(AAA &r,const int & n)
//         : ref(r),num(n)
//         {
//         }
//     void ShowYourName()
//     {
//         ref.showYourname();
//         cout << "and" << endl;
//         cout << "I ref num" <<num <<endl;
//     }
// };

// int main()
// {
//     AAA obj1;
//     BBB obj2(obj1,20);
//     obj2.ShowYourName();
//     return 0;
// }

// #include<iostream>
// #include<cstring>
// using namespace std;

// class Person
// {
// private:
//     char * name;
//     int age;
// public:
//     Person(char * myname,int myage)
//     {
//         int len=strlen(myname)+1;
//         name=new char[len];
//         strcpy(name,myname);
//         age=myage;
//     }
//     void ShowPersonInof() const
//     {
//         cout<<"이름: " <<name <<endl;
//         cout <<"나이: " <<age <<endl;
//     }
//     ~Person()
//     {
//         delete [] name;
//         cout <<"called destructor!" <<endl;
//     }
// };

// int main()
// {
//     Person man1("LEE dong woo",29);
//     Person man2("jang dong gun",41);
//     man1.ShowPersonInof();
//     man2.ShowPersonInof();
//     return 0;
// }

// #include <iostream>
// #include <cstring>
// using namespace std;

// class Person
// {
// private:
//     char * name;
//     int age;
// public:
//     Person(char * myname,int myage)
//     {
//         int len=strlen(myname)+1;
//         name = new char[len];
//         strcpy(name,myname);
//         age=myage;
//     }
//     Person()
//     {
//         name=NULL;
//         age=0;
//         cout <<"called person()" <<endl;
//     }
//     void SetPersonInfo(char * myname,int myage)
//     {
//         name=myname;
//         age=myage;
//     }
//     void ShowPersonInfo() const
//     {
//         cout << "이름: "<<name <<", ";
//         cout <<"나이: "<<age<<endl;
//     }
    
//     ~Person()
//     {
//         delete[]name;
//         cout<<"called destructor!" <<endl;
//     }
// };

// int main()
// {
//     Person parr[3];
//     char namestr[100];
//     char * strptr;
//     int age;
//     int len;
//     for (int i = 0; i < 3; i++)
//     {
//         cout <<"이름: ";
//         cin >> namestr;
//         cout << "나이: ";
//         cin >> age;
//         len=strlen(namestr)+1;
//         strptr= new char[len];
//         strcpy(strptr,namestr);
//         parr[i].SetPersonInfo(strptr,age);
//     }
//     parr[0].ShowPersonInfo();
//     parr[1].ShowPersonInfo();
//     parr[2].ShowPersonInfo();   
//     return 0;
// }

// #include <iostream>
// #include <cstring>
// using namespace std;
// class SoSimple
// {
// private:
//     int num;
// public:
//     SoSimple(int n) : num(n)
//     {
//         cout <<"num="<<num<<", ";
//         cout<<"address="<<this<<endl;
//     }
//     void ShowSimpleData()
//     {
//         cout<<num<<endl;
//     }
//     SoSimple * GetThisPointer()
//     {
//         return this;
//     }
// };

// int main()
// {
//     SoSimple sim1(100);
//     SoSimple * ptr1=sim1.GetThisPointer();
//     cout << ptr1 <<", ";
//     ptr1->ShowSimpleData();

//     SoSimple sim2(200);
//     SoSimple * ptr2=sim2.GetThisPointer();
//     cout << ptr2 <<", ";
//     ptr2->ShowSimpleData();
//     return 0;
// }

// #include <iostream>
// using namespace std;

// class SelfRef
// {
// private:
//     int num;
// public:
//     SelfRef(int n) : num(n)
//     {
//         cout << "객체생성"<<endl;
//     }
//     SelfRef& Adder(int n)
//     {
//         num+=n;
//         return *this;
//     }
//     SelfRef& ShowTwoNumber()
//     {
//         cout << num <<endl;
//         return *this;
//     }
// };

// int main()
// {
//     SelfRef obj(3);
//     SelfRef &ref=obj.Adder(2);
//     obj.ShowTwoNumber();
//     ref.ShowTwoNumber();

//     ref.Adder(1).ShowTwoNumber().Adder(2).ShowTwoNumber();
//     return 0;
// }

// #include <iostream>
// using namespace std;
// class Sosimple
// {
// private:
//     int num1;
//     int num2;
// public:
//     Sosimple(int n1, int n2)
//         :num1 (n1),num2(n2) {}
//     Sosimple(Sosimple &copy)
//         :num1(copy.num1),num2(copy.num2)
//         {
//             cout << "Called SoSimple(somle &copy)"<<endl;
//         }
//     void ShowSimpleData()
//     {
//         cout << num1 <<endl;
//         cout << num2 <<endl;
//     }
// };

// int main()
// {
//     Sosimple sim1(15,30);
//     cout << "생성 및 초기화 직전"<<endl;
//     Sosimple sim2 =sim1;
//     cout << "생성 및 초기화 직후" <<endl;
//     sim2.ShowSimpleData();
//     return 0;
// }

// #include <iostream>
// #include <cstring>
// using namespace std;

// class Person
// {
// private:
//     char * name;
//     int age;
// public:
//     Person(char * myname,int myage)
//     {
//         int len=strlen(myname)+1;
//         name = new char[len];
//         strcpy(name,myname);
//         age=myage;
//     }
//     Person()
//     {
//         name=NULL;
//         age=0;
//         cout <<"called person()" <<endl;
//     }
//     void SetPersonInfo(char * myname,int myage)
//     {
//         name=myname;
//         age=myage;
//     }
//     void ShowPersonInfo() const
//     {
//         cout << "이름: "<<name <<", ";
//         cout <<"나이: "<<age<<endl;
//     }
    
//     ~Person()
//     {
//         delete[]name;
//         cout<<"called destructor!" <<endl;
//     }
// };

// int main()
// {
//     Person man1("Lee dong nuck",39);
//     Person man2=man1;
//     man1.ShowPersonInfo();
//     man2.ShowPersonInfo();
//     return 0;
// }

// #include <iostream>
// #include <string>
// using namespace std;
// class NameCard
// {
// private:
//     string* name;
//     string* companyName;
//     string* cNumber;
//     int position;
// public:
//     enum rank{CLERK,SENIOR,ASSIST,MANAGER};
//     NameCard(string myname,string mycompany, string phonenumber,int rank)
//     {
//     name = new string(myname);
//     companyName = new string(mycompany);
//     cNumber = new string(phonenumber);
//     position = rank;
//     }
//     NameCard(const NameCard& copy):position(copy.position)
//     {
//         name =new string(*copy.name);
//         companyName = new string(*copy.companyName);
//         cNumber = new string(*copy.cNumber);
//     }
//     void ShowNameCardInfo()
//     {
//         cout << "이름: "<<*name <<"회사이름: " <<*companyName << "전화번호: "<<*cNumber;
//         switch (position)
//         {
//         case CLERK:
//             cout << " 직급:CLERK"<<endl;
//             break;
//         case SENIOR:
//             cout << " 직급:SENIOR"<<endl;
//             break;
//         case ASSIST:
//             cout << " 직급:ASSIST"<<endl;
//             break;
//         case MANAGER:
//             cout << " 직급:MANAGER"<<endl;
//             break;
//         default:
//             break;
//         } 
//     }
//     ~NameCard()
//     {
//         delete[]name;
//         delete[]companyName;
//         delete[]cNumber;
//     }
// };

// int main()
// {
//     NameCard manClerk("Lee","ABCEng","010-1111-2222",NameCard::CLERK);
//     NameCard man2("a","b","c",0);
//     man2=manClerk;
//     man2.ShowNameCardInfo();
//     return 0;
// }


// #include <iostream>
// using namespace std;
// class Sosimple
// {
// private:
//     int num;
// public:
//     Sosimple(int n)
//         :num (n) {}
//     Sosimple(Sosimple &copy)
//         :num(copy.num)
//         {
//             cout << "Called SoSimple(somle &copy)"<<endl;
//         }
//     Sosimple& AddNum(int n)
//     {
//         num+=n;
//         return *this;
//     }
//     void ShowSimpleData()
//     {
//         cout <<"num: " << num<<endl;
//     }
// };

// Sosimple SimpleFuncObj(Sosimple ob)
// {
//     cout << "return 이전" <<endl;
//     return ob;
// }

// int main()
// {
//     Sosimple obj(7);
//     SimpleFuncObj(obj).AddNum(30).ShowSimpleData();
//     obj.ShowSimpleData();
//     return 0;
// }

// #include <iostream>
// using namespace std;

// class Temporary
// {
// private:
//     int num;
// public:
//     Temporary(int n): num(n)
//     {
//         cout <<"creat obj: " << num <<endl;
//     }
//     ~Temporary()
//     {
//         cout << "destroy obj: "<<num <<endl;
//     }

//     void ShowTempInfo()
//     {
//         cout << "My num is "<<num <<endl;
//     }
// };

// int main()
// {
//     Temporary(100);
//     cout<<"*********** after make!" <<endl<<endl;
//     Temporary(200).ShowTempInfo();
//     cout<<"*********** after make!" <<endl<<endl;

//     const Temporary &ref=Temporary(300);
//     cout<<"*********** endof main!" <<endl<<endl;
//     return 0;
// }


