// #include<iostream>
// void cheers(int);
// double cube(double x);
// int main(void)
// {
//     using namespace std;
//     cheers(5);
//     cout <<"하나의 수를 입력하시오: ";
//     double side;
//     cin >> side;
//     double volume = cube(side);
//     cout <<"한 변의 길이가 " << side <<" 센티미터인 정육면체의 부피는 ";
//     cout << volume <<" 세제곱센티미터입니다."<<endl;
//     cheers(cube(2));
//     return 0;
// }

// void cheers(int n)
// {
//     using namespace std;
//     for (int i = 0; i <n; i++)
//         cout<<"Cheers! ";
//     cout <<endl;
// }

// double cube(double x)
// {
//     return x * x * x;
// }

// #include <iostream>
// const int ArSize= 8;
// int sum_arr(const int* begin, const int* end);

// int main()
// {
//     using namespace std;
//     int cookies[ArSize] = {1,2,4,8,16,32,64,128};

//     int sum=sum_arr(cookies,cookies + ArSize);
//     cout << "먹은 과자 수 합계: " <<sum << endl;
//     sum=sum_arr(cookies,cookies+3);
//     cout << "처음 세 사람은 과자 " << sum << "개를 먹었습니다."<<endl;
//     sum=sum_arr(cookies + 4,cookies+8);
//     cout <<"마지막 네 사람은 과자 "<< sum <<"개를 먹었습니다."<<endl;
//     return 0;
// }

// int sum_arr(const int* begin,const int * end)
// {
//     const int* pt;
//     int total  = 0;
//     for(pt=begin; pt !=end; pt++)
//         total = total +*pt;
//     return total;
// }

// #include<iostream>
// const int ArraySize=5;

// int* sum(int size,int(*)[ArraySize]);
// int* andDi(int size,int(*)[ArraySize]);
// int* max(int size,int(*)[ArraySize]);
// int* min(int size,int(*)[ArraySize]);
// using namespace std;
// int main()
// {
//  int a[5][ArraySize];
//  int count=0;
//  for (int i = 0; i < 5; i++)
//  {
//     for (int j = 0; j < ArraySize; j++)
//     {
//         a[i][j]=count;
//         count++;
//     }
//  }
//  int *pt=sum(5,a);
 
//  cout<<"총합\n";
//  for (int i = 0; i < 5; i++)
//  {
//     cout<<pt[i] <<endl;
//  }
//  delete [] pt;

// pt=andDi(5,a); 
// cout<<"평균\n";
//  for (int i = 0; i < 5; i++)
//  {
//     cout<<pt[i] <<endl;
//  }
//  delete [] pt;
// pt=max(5,a);
// cout<<"최대\n";
// for (int i = 0; i < 5; i++)
//  {
//     cout<<pt[i] <<endl;
//  }
//  delete [] pt;
// cout<<"최솟\n";
// pt=min(5,a);

// for (int i = 0; i < 5; i++)
//  {
//     cout<<pt[i] <<endl;
//  }
//  delete [] pt;

//  return 0;   
// }

// int* sum(int size,int (*array)[ArraySize])
// {
//         if(size <=0)
//             return NULL;
//     int* sum=new int[size];
    
//     for (int i = 0; i <size; i++)
//     {
//         sum[i]=0;
//         for (int j = 0; j < ArraySize; j++)
//         {
//             sum[i]+=array[i][j];
//         }
//     }
//     return sum;
// }

// int* andDi(int size,int (*array)[ArraySize])
// {
//         if(size <=0)
//             return NULL;
//     int total=0;
//     int* avg=new int[size];
//     for (int i = 0; i <size; i++)
//     {
//         avg[i]=0;
//         for (int j = 0; j < ArraySize; j++)
//         {
//           total+=array[i][j];
//         }
//         avg[i]=total/ArraySize;
//     }
//     return avg;
// }

// int* max(int size,int (*array)[ArraySize])
// {
//         if(size <=0)
//             return NULL;
//     int total=0;
//     int* max=new int[size];
//     for (int i = 0; i <size; i++)
//     {
//         max[i]=0;
//         total=0;
//         for (int j = 0; j < ArraySize; j++)
//         {
//           total= total<array[i][j] ? array[i][j] :total;  
//         }
//         max[i]=total;
//     }
//     return max;
// }

// int* min(int size,int (*array)[ArraySize])
// {
//         if(size <=0)
//             return NULL;
//     int total=0;
//     int* min=new int[size];
//     for (int i = 0; i <size; i++)
//     {
//         min[i]=0;
//         total=INT32_MAX;
//         for (int j = 0; j < ArraySize; j++)
//         {
//           total= total > array[i][j] ? array[i][j] :total;  
//         }
//         min[i]=total;
//     }
//     return min;
// }

// #include <iostream>
// unsigned int c_in_str(const char * str, char ch);
// int main()
// {
//     using namespace std;
//     char mmm[15] ="minimin";

//     char *wail ="ululate";
//     unsigned int ms = c_in_str(mmm,'m');
//     unsigned int us = c_in_str(wail,'u');
//     cout << mmm << "에는 m이 "<< ms << "개 들어 있습니다.\n";
//     cout << wail << "에는 u이 "<< us << "개 들어 있습니다.\n";
//     return 0;
// }

// unsigned int c_in_str(const char * str, char ch)
// {
//     int count =0;
//     while (*str)
//     {
//         if(*str == ch)
//             count++;
//         str++;
//     }   
//     return count;
// }

// #include <iostream>
// char * buildstr(char c,int n);
// int main()
// {
//     using namespace std;
//     int times;
//     char ch;

//     cout << "문자 하나를 입력하십시오: ";
//     cin >> ch;
//     cout << "정수 하나를 입력하십시오: ";
//     cin >> times;
//     char *ps = buildstr(ch,times);
//     cout << ps << endl;
//     delete [] ps;
//     ps =buildstr('+',20);
//     cout << ps << "-DONE-" << ps <<endl;
//     delete [] ps;
//     return 0;
// }

// char * buildstr(char c, int n)
// {
//     char * pstr = new char[n+1];
//     pstr[n] ='\0';
//     while (n-- > 0)
//     {
//         pstr[n] = c;
//     }
//     return pstr;
// }

// #include <iostream>
// struct travel_time
// {
//     int hours;
//     int mins;
// };

// const int Mins_per_hr =60;

// travel_time sum(travel_time t1, travel_time t2);
// void change(travel_time*);
// void show_time(travel_time);
// using namespace std;
// int main()
// {
    
//     travel_time day1 = {5, 45};
//     travel_time day2 = {4 , 55};
//     change(&day1);
//     travel_time trip = sum(day1,day2);
//     cout << "이틀간 소요시간: ";
//     show_time(trip);

//     travel_time day3 ={4,32};
//     cout << "사흘간 소요시간: ";
//     show_time(sum(trip,day3));

//     return 0;
// }

// travel_time sum(travel_time t1, travel_time t2)
// {
//     travel_time total;
//     total.mins = (t1.mins + t2.mins) % Mins_per_hr;
//     total.hours = t1.hours + t2.hours + (t1.mins + t2.mins) / Mins_per_hr;

//     return total;
// }

// void show_time(travel_time t)
// {
//     using namespace std;
//     cout << t.hours <<"시간 "
//     << t.mins <<"분\n";
// }

// void change(travel_time* t)
// { 
//     cout <<"시간을 입력해주세요.\n";
//     cin >>t->hours;
//     cout <<"분을 입력해주세요.\n";
//     cin >>t->mins;
// }

// #include<iostream>
// #include<string>
// using namespace std;
// const int SIZE = 5;
// void display(const string sa[],int n);
// int main()
// {
//     string list[SIZE];
//     cout << "좋아하는 밤하늘의 광경을 " <<SIZE <<"개 입력하시오:\n";
//     for (int i = 0; i < SIZE; i++)
//     {
//         cout << i + 1<<" : ";
//         getline(cin,list[i]);
//     }
//     cout <<"입력하신 내용은 다음과 같습니다:\n";
//     display(list,SIZE);
//     return 0;
// }

// void display(const string sa[], int n)
// {
//     for (int i = 0; i< n; i++)
//         cout<< i + 1<<": " << sa[i] <<endl; 
// }

// #include<iostream>
// #include<array>
// #include<string>
// using namespace std;
// const int Seasons =4;
// const array<string,Seasons> sname ={"Spring","Summer","Fall","wWnter"};

// void fill(array<double,Seasons> *pa);
// void show(array<double,Seasons> da);

// int main()
// {
//     array<double,Seasons> expenses;
//     fill(&expenses);
//     show(expenses);
//     return 0;
// }

// void fill(array<double,Seasons>*pa)
// {
//     for (int i = 0; i < Seasons; i++)
//     {
//         cout << sname[i] <<"에 소요되는 비용:";
//         cin >> (*pa) [i]; 
// }
// }

// void show(array<double,Seasons>da)
// {
//     double total=0.0;
//     cout <<"\n계절별 비용S\n";
//     for (int i = 0; i < Seasons; i++)
//     {
//         cout << sname[i] <<" : $" <<da[i] <<endl;
//         total +=da[i];
//     }
//     cout <<"총 비용 : $" <<total <<endl;
// }

// #include<iostream>
// void countdown(int n);

// int main()
// {
//     countdown(4);
//     return 0;
// }

// void countdown(int n)
// {
//     using namespace std;
//     cout << "카운트 다운 ..."<< n << endl;
//     if(n>0)
//         countdown(n-1);
//     cout << n << ": kaboom!\n";
// }

// #include<iostream>
// using namespace std;
// double glidong(int);
// double moonsoo(int);

// void estimate(int lines, double (*pf)(int));

// int main()
// {
//     int code;
//     cout << "필요한 코드의 행 수를 입력하십시오: ";
//     cin >> code;
//     cout <<"홍길동의 시간 예상:\n";
//     estimate(code,glidong);
//     cout<<"박문수의 시간 예상:\n";
//     estimate(code,moonsoo);
//     return 0;
// }

// double  glidong(int lns)
// {
//     return 0.05*lns;
// }

// double moonsoo(int lns)
// {
//     return 0.03 * lns + 0.0004 * lns *lns;
// }

// void estimate(int lines, double(*pf)(int))
// {
//     cout<< lines <<"행을 작성하는 데 ";
//     cout << (*pf)(lines) <<"시간이 걸립니다.\n";
// }

// #include<iostream>

// inline double square(double x){return x*x;}

// int main(){
//     using namespace std;
//     double a,b;
//     double c =13.0;

//     a=square(5.0);
//     b= square(4.5 +7.5);
//     cout << "a = " << a << ", b = " << b <<endl;
//     cout << "c =" << c;
//     cout << ", c의 제급 ="<<square(c++) << endl;
//     cout << "현재 c ="<< c <<endl;
//     return 0;
// }

// #include <iostream>
// int main()
// {
//     using namespace std;
//     int rats =101;
//     int* a;
//     int & rodents = rats;
//     cout <<"rats = " <<rats;
//     cout << ", rodents = "<< rodents <<endl;
//     rodents++;
//     cout <<"rats = "<<rats;
//     cout << ", rodents ="<<rodents <<endl;
//     cout <<"rats의 주소 =" <<&rats;
//     cout << ", rodents의주소 = "<<&rodents <<endl;
//     return 0;
// }

// #include <iostream>
// void swapr(int & a,int & b);
// void swapp(int *p, int *q);
// void swapv(int a,int b);
// using namespace std;
// int main()
// {
//     int wallet1 =3000;
//     int wallet2 =2500;

//     cout <<"지갑 1 =" <<wallet1 << "원";
//     cout <<", 지갑 2 = " <<wallet2 <<"원\n";
//     cout <<"참조를 이용하여 내용들을 교환:\n";
//     swapr(wallet1,wallet2);
//     cout << "지갑 1 = " <<wallet1 <<"원";
//     cout <<", 지갑 2 = " <<wallet2 <<"원\n";

//     cout <<"포인터를 이용하여 내용들을 다시 교환:\n";
//     swapp(&wallet1, &wallet2);
//     cout << "지갑 1 = " <<wallet1 << "원";
//     cout << ", 지갑 2 = " <<wallet2 << "원\n";

//     swapv(wallet1,wallet2);
//     cout << "지갑 1 = " <<wallet1 << "원";
//     cout << ", 지갑 2 = " <<wallet2 << "원\n";
//     return 0;
// }

// void swapr(int & a,int & b)
// {
//     int temp;
//     temp =a;
//     a = b;
//     b=temp;
// }

// void swapp(int * p,int * v)
// {
//     int temp;
//     temp =*p;
//     *p = *v;
//     *v=temp;
// }

// void swapv(int  a,int  b)
// {
//     int temp;
//     temp =a;
//     a = b;
//     b=temp;
// }

// #include <iostream>
// double cube(double a);
// double refcube(double &ra);
// using namespace std;
// int main()
// {
//     double x =3.0;
//     cout << cube(x);
//     cout << " = " << x << "의 세제곱\n";
//     cout << refcube(x);
//     cout << " = " << x << "의 세제곱\n";
//     return 0;
// }

// double cube(double a)
// {
//     a *= a* a;
//     return a;
// }

// double refcube(double &ra)
// {
//     ra *= ra * ra;
//     return ra;
// }

// #include <iostream>
// #include <string>
// using namespace std;
// struct free_throws
// {
//     string name;
//     int made;
//     int attempts;
//     float percent;
// };

// void display(const free_throws & ft);
// void set_pc(free_throws & ft);
// free_throws & accumulate(free_throws & target,const free_throws & source);

// int main()
// {
//     free_throws one ={"Ifrelsa Branch",13,14};
//     free_throws two = {"Andor knott",10,16};
//     free_throws three = {"Minnie Max",7,9};
//     free_throws four = {"Whily Looper",5,9};
//     free_throws five = {"Long Long",6,14};
//     free_throws team = {"Throwgoods",0,0};
    
//     free_throws dup;
//     set_pc(one);
//     display(one);
//     accumulate(team,one);
//     display(team);
//     display(accumulate(team,two));
//     display(team);
//     display(accumulate(team,three));
//     accumulate(accumulate(team,three),four);
//     dup = accumulate(team,five);
//     cout <<"team 출력:\n";
//     display(team);
//     cout<<"대입 이후 dup 출력:\n";
//     display(dup);
//     set_pc(four);
//     accumulate(dup,five)=four;
//     cout<<"문제 소지가 있는 대입 이후 dup 출력:\n";
//     display(dup);
//     return 0;
// }

// void display(const free_throws & ft)
// {
//     cout << "Name: " <<ft.name<<'\n';
//     cout << "Made: "<<ft.made <<'\t';
//     cout << "Attempts: "<<ft.attempts << '\t';
//     cout << "Percent: " << ft.percent << '\n';
// }

// void set_pc(free_throws & ft)
// {
//     if(ft.attempts != 0)
//         ft.percent =100.0f*float(ft.made)/float(ft.attempts);
//     else
//     ft.percent = 0;
// }

// free_throws & accumulate(free_throws &target,const free_throws &source)
// {
//     target.attempts += source.attempts;
//     target.made += source.made;
//     set_pc(target);
//     return target;
// }

// #include<iostream>
// unsigned long left(unsigned long num, unsigned ct);
// char * left(const char * str, int n = 1);

// int main()
// {
//     using namespace std;
//     char * trip= "Hawaii!!";
//     unsigned long n=12345678;
//     int i;
//     char * temp;
//     for ( i = 1; i < 10; i++)
//     {
//         cout << left(n,i) << endl;
//         temp =left(trip,i);
//         cout << temp <<endl;
//         delete []temp;
//     }
//     return 0;

// }

// unsigned long left(unsigned long num, unsigned ct)
// {
//     unsigned digits = 1;
//     unsigned long n=num;

//     if(ct==0 || num ==0)
//         return 0;
//     while (n /=10)
//         digits++;
//     if (digits >ct)
//     {
//         ct =digits -ct;
//         while (ct--)
//             num/=10;
//         return num;
//     }
//     else return num;
// }

// char* left(const char* str,int n)
// {
//     if(n< 0)
//         n =0;
//     char* p =new char[n+1];
//     int i;
//     for ( i = 0; i <n &&str[i]; i++)
//         p[i] =str[i];
//     while(i<=n)
//         p[i++] = '\0';
//     return p;   
// }
