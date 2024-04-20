// #include <iostream>
// struct inflatalbe
// {
//   char name[20];
//   float volume;
//   double price;
// };

// int main()
// {
//     using namespace std;
//     inflatalbe bouquet ={
//         "sunflowers",
//         0.20,
//         12.49
//     };
//     inflatalbe choice;
//     cout << "bouquet: " <<bouquet.name <<" for $";
//     cout << bouquet.price <<endl;

//     choice =bouquet;
//     cout << "choice: " <<choice.name <<" for $";
//     cout << choice.price <<endl;

//     return 0;
// }

// #include <iostream>
// struct inflatalbe
// {
//   char name[20];
//   float volume;
//   double price;
// };

// int main()
// {
//     using namespace std;
//     inflatalbe guest=
//     {
//         "Glorious Gloria",
//         1.88,
//         29.99
//     };
//     inflatalbe pal=
//     {
//         "Audacious Arthur",
//         3.12,
//         32.99
//     };
//     cout<<"지금 판매하고 있는 모형풍선은\n"<<guest.name;
//     cout<<"와 "<<pal.name<<"입니다.\n";
//     cout << "두 제품을 $";
//     cout << guest.price + pal.price <<"에 드리겠습니다.\n";
//     return 0;
// }

// #include<iostream>

// struct inflatable
// {
//    char name[20];
//    float volume;
//    double price;
// };

// int main()
// {
//     using namespace std;
//     inflatable guests[2]=
//     {
//         {"Bambi",0.5,21.99},
//         {"Godzilla",2000,565.99}
//     };

//     cout <<guests[0].name <<"와 "<<guests[1].name
//     <<"의 부피를 합하면\n"
//     << guests[0].volume +guests[1].volume
//     <<" 세제곱피트입니다.\n";
//     return 0;
// }

// #include <iostream>
// int main()
// {
//     using namespace std;
//     int updates = 6;
//     int * p_updates;
//     p_updates =&updates;
//     cout<<"값: updates = "<<updates;
//     cout << ", *p_updates = " << *p_updates << endl;
//     cout << "주소: &updates = " << &updates;
//     cout << ", pu_updates = " <<p_updates << endl;
//     *p_updates = *p_updates + 1;
//     cout << "변경된 updates = " << updates << endl;
//     return 0;
// }

// #include <iostream>
// int main()
// {
//     using namespace std;
//     int nights =1001;
//     int *pt =new int;
//     *pt =1001;
//     cout << "nights의 값 = ";
//     cout << nights << ": 메모리 위치 " << &nights <<endl;
//     cout << "int 형";
//     cout << "값 = " << *pt <<": 메모리 위치 = " << pt <<endl;
    
//     double * pd = new double;
//     *pd = 10000001.0;
    
//     cout << "double 형 ";
//     cout << "값 = "<<*pd << ": 메모리 위치 " << pd <<endl;
//     cout << "포인터 pd의 메모리 위치: " << &pd << endl;
//     cout << "pt의 크기  = " << sizeof(pt);
//     cout << "*pt의 크기 = " <<sizeof(*pt)<<endl;
//     cout << "pd의 크기 = "<<sizeof pd;
//     cout << ": *pd의크기 = " << sizeof(*pd) <<endl;
//     return 0;   
// }

// #include <iostream>

// int main()
// {
//     using namespace std;
//     double *p3 =new double [3];
//     p3[0] =0.2;
//     p3[1] =0.5;
//     p3[2] =0.8;
//     cout << "p3[1]은 " <<p3[1] << "입니다.\n";
//     p3 = p3 +1;
//     cout << "이제는 p3[0]이 "<< p3[0] <<"이고, ";
//     cout << "p3[1]이 " <<p3[1] << "입니다.\n";
//     p3 =p3 -1 ;
//     delete [] p3;
//     return 0;
// }

//pw = pw +1  ,20000.0
//ps = ps +1  ,2

// #include<iostream>
// #include<cstring>
// int main()
// {
//     using namespace std;
//     char animal[20] ="bear";
//     const char *bird ="wren";
//     char * ps;
//     cout <<animal << " and ";
//     cout <<bird << "\n";
//     cout << "동물의 종류를 입력하십시오: ";
//     cin >> animal;

//     ps= animal;
//     cout <<ps <<"s!\n";
//     cout << "strcpy() 사용전:\n";
//     cout <<(int *) animal << ": " << animal <<endl;
//     cout <<(int *) ps << ": "<< ps <<endl;
//     ps = new char[strlen(animal)+1];
//     strcpy(ps,animal);
//     cout <<"strcpy() 사용후:\n";
//     cout <<(int *) animal <<": " << animal <<endl;
//     cout <<(int *) ps << ": "<< ps <<endl;
//     delete [] ps;
//     return 0;
// }

// #include <iostream>
// struct inflatable
// {
//     char name[20];
//     float volume;
//     double price;
// };
// inflatable* getin(void);
// void getout(inflatable*);
// int main()
// {
//     using namespace std;
//     inflatable * ps =getin();
//     getout(ps);
//     delete ps;
//     return 0;
// }

// void getin(inflatable* ps)
// {
//     using namespace std;
//     cout << "모형풍선의 이름을 입력하십시오: ";
//     cin.get(ps->name,20);
//     cout <<"부피를 세제곱 피트 단위를 입력하십시오: ";
//     cin >> (*ps).volume;
//     cout << "가격을 달러 단위로 입력하십시오: $";
//     cin >> ps->price;
// }

// void getout(inflatable* ps)
// {
//     using namespace std;
//     cout <<"이름: " << (*ps).name <<endl;
//     cout << "부피: " <<ps->volume << " cubic feet\n";
//     cout << "가격: $" <<ps->price <<endl;
// }


// inflatable* getin(void)
// {

//     using namespace std;
//     inflatable * ps = new inflatable;

//     cout << "모형풍선의 이름을 입력하십시오: ";

//     cin.get(ps->name,20);

//     cout <<"부피를 세제곱 피트 단위를 입력하십시오: ";

//     cin >> (*ps).volume;

//     cout << "가격을 달러 단위로 입력하십시오: $";

//     cin >> ps->price;

//     return ps;

// }

//s01 = 1998
/*
pa ->s02 = 1999;

trio[0] =2003;

1번 2003

arp[3] = {1998,1999,?}

2번 1999

**ppa =arp => ppa =1998 부터

ppb =arp[3]

3번 1998

4번 1999

*/

// #include <iostream>
// #include <vector>
// #include <array>
// using namespace std;
// int main()
// {
    
//     double a1 [4] ={1.2,2.3,3.6,4.8};
//     vector<double> a2(4);
//     a2[0]=1.0/3.0;
//     a2[1]=1.0/5.0;
//     a2[2]=1.0/7.0;
//     a2[3]=1.0/9.0;
//     array<double,4> a3= {3.14,2.72,1.62,1.41};
//     array<double,4> a4;
//     a4=a3;
//     cout <<"a1[2]: " <<a1[2] << " at " << &a1[2] <<endl;
//     cout <<"a2[2]: " <<a2[2] << " at " << &a2[2] <<endl;
//     cout <<"a3[2]: " <<a3[2] << " at " << &a3[2] <<endl;
//     cout <<"a4[2]: " <<a4[2] << " at " << &a4[2] <<endl;
    
//     //잘못됨
//     a1[-2] =20.2;
//     cout <<"a1[-2]: " <<a1[-2] << " at " << &a1[-2] <<endl;
//     cout <<"a3[2]: " <<a3[2] << " at " << &a3[2] <<endl;
//     cout <<"a4[2]: " <<a4[2] << " at " << &a4[2] <<endl;


//     return 0;
// }


// #include<iostream>
// #include<string>

// int main()
// {
//     using namespace std;
//     cout << "단어를 하나 입력하시오: ";
//     string word;
//     cin >>word;

//     char temp;
//     int i,j;

//     for (j=0,i=word.size()-1;j<i;--i,++j)
//     {
//         temp = word[i];
//         word[i] = word[j];
//         word[j] =temp;
//     }
//     cout << word << "\n종료.\n";
//     return 0;
// }

// #include <iostream>
// int main()
// {
//     using namespace std;
//     char ch;
//     int count =0;
//     cin.get(ch);
//     while (cin.fail() == false)
//     {
//         cout << ch;
//         ++count;
//         cin.get(ch);
//     }
//     cout << count << "문자를 읽었습니다.\n";
    
    
    
//     }

// #include <iostream>
// int main()
// {
//     using namespace std;
//     char ch;
//     int count =0;
//     cin.get(ch);
//     while ((ch = cin.get() ) != EOF)
//     {
//         cout << ch;
//         ++count;
//         cin.get(ch);
//     }
//     cout << count << "문자를 읽었습니다.\n";
//     }

// #include <iostream>
// const int Cities =5;
// const int Years =4;
// using namespace std;
// int max(int(*)[Cities]);
// int main()
// {
//     const char* cities[Cities] ={
//         "Seoul","Jeju","Busan","Gangneung",
//         "Daegu"
//     };
//     int maxtemps[Years][Cities]=
//     {
//         {35,32,33,36,35},
//         {33,32,34,35,31},
//         {33,34,32,35,34},
//         {36,35,34,37,35}
//     };

//     cout << "2009년부터 2012년까지의 연중 최고 온도\n\n";
//     for (int city = 0; city < Cities; ++city)
//     {
//         cout << cities[city] << ":\t";
//         for (int year  = 0; year < Years; ++year)
//         {
//             cout << maxtemps[year][city] <<"\t";
//         }
//         cout <<endl;       
//     }
//     int m=max(maxtemps);
//     cout << "최대값: " << m <<endl;
//     return 0;
// }


// int max(int(*max)[Cities])
// {
//     int m=0;
//     for (int city = 0; city < Cities; ++city)
//     {
//         for (int year  = 0; year < Years; ++year)
//         {
//             m= m < max[year][city] ? max[year][city] : m ;
//         }       
//     }
// return m;
// }

// #include <iostream>
// const char* qualify[4]=
// {
//     "만미터 달리기",
//     "모래사장 씨름",
//     "비치 발리",
//     "부매랑 던지기"
// };
// int main()
// {
//     using namespace std;
//     int age;
//     cout << "나이를 입력하십시오: ";
//     cin>> age;
//     int index;
//     if(age >17 && age <35)
//         index =0;
//     else if(age >=35 && age <50)
//         index =1;
//     else if(age >=50 && age <65)
//         index =2;
//     else
//         index = 3;
//     cout << "당신은 " << qualify[index] << "에 참가할 수 있습니다.\n";
//     return 0;
// }

// #include <iostream>
// #include<cctype>
// using namespace std;
// int main()
// {
//     cout << "분석할 텍스트를 입력하십시오. "
//         "입력의 끝을 @으로 표시하십시오.\n";
//     char ch;
//     int whitespace =0;
//     int digits =0;
//     int chars =0;
//     int punct = 0;
//     int others = 0;
//     cin.get(ch);
//     while (ch !='@')
//     {
//         if(isalpha(ch))
//             chars++;
//         else if (isspace(ch))
//            whitespace++;
//         else if (isdigit(ch))
//             digits++;
//         else if(ispunct(ch))
//             punct++;
//         else
//             others++;
//         cin.get(ch);
//     }
//     cout <<"알파벳 문자 "<<chars<<", "
//     <<"화이트스페이스 "<<whitespace<<", "
//     <<"숫자 "<<digits <<", "
//     <<"구두점 "<<punct <<", "
//     << "기타 "<<others <<endl;
//     return 0;
// }

// #include <iostream>
// const int Max = 5;
// int main()
// {
//     using namespace std;
//     int golf[Max];
//     cout << "골프 점수를 입력하시오.\n";
//     cout << "총 " << Max <<" 라운드 점수를 입력해야 합니다.\n";
//     int i;
//     for ( i = 0; i < Max; i++)
//     {
//         cout << "round #" <<i+1 <<": ";
//         while (!(cin>>golf[i]))
//         {
//             cin.clear();
//             while(cin.get() != '\n')
//                 continue;
//             cout << "골프 점수를 입력하십시오: ";
    
//         }
        
//     }
//     double total= 0.0;
//     for ( i = 0; i <Max; i++)
//         total +=golf[i];
    
//     cout<<"총 "<<Max<<"라운드의 평균 점수 = "
//     <<total /Max <<endl;
//     return 0;
// }

/*
연습문제 1번
else if 를 사용하면 
위에 if가 실행되면 자동으로 검사하지 않고 넘어간다.
그런대 if if로 하면 위에if가 실행된사실과 무관하게 계속 검사한다.
즉 연산횟수에 영향을 준다.

연습문제 2번

++char와  char +1의 cout에서 차이점은
앞에있는 방법으로 사용하면 문자가 나오지만 뒤에 방법을 이용하면 정수가 나온다.

연습문제 3번
ct1은 9 ct2는 0

연습문제 4번
a.weight>=115 && weight<125
b. ch == q|| ch ==Q
c. x%2==0 && x ==26
d.x%2==0 && x%26 ==0
e.donation<=1000&&donation>=2000||guest ==1
f.(ch>='A'&&ch<='Z') || (ch>='a' && ch<='z') 
*/
