// #include<iostream>
// int main()
// {
//     using namespace std;
//     cout << "C++의 세계로 오십시오.";
//     cout << endl;
//     cout <<"후회하지 않으실 겁니다!" <<endl;
//     return 0;
// }

// #include<iostream>

// int main()
// {
//     using namespace std;

//     int carrots;

//     carrots =25;

//     cout<< "나는 당근을 " << carrots << "개 가지고 있다.";
//     cout <<endl;
//     carrots =carrots-1;
//     cout << "아삭아삭, 이제 당근은" <<carrots <<"개이다." <<endl;
//     return 0;
// }

// #include <iostream>
// #include <cmath>
// int main()
// {
    
//     using namespace std;
    
//     double area;
//     cout <<"마루 면적을 평방피트 단위로 입력하시오: ";
//     cin>>area;
//     double side;
//     side=sqrt(area);
//     cout <<"사각형 마루라면 한 변이 "<<side //endl이 나오기 전까지는 연속적으로 출력해주고 코드상에서도 한문장으로 본다.
//     <<"피트에 상당합니다."<<endl;// endl로 문자을끝내면 자동으로 줄바꿈을 해준다
//     cout<<"멋지네요!"<<endl;
//     return 0;
// }

// #include <iostream>
// void simon(int);

// int main()
// {
//     using namespace std;
//     simon(3);
//     cout <<"정수를 하나 고르시오: ";
//     int count;
//     cin >> count;
//     simon(count);
//     cout << "끝!" <<endl;
//     return 0;
// }

// void simon(int n)
// {
//     using namespace std;
//     cout<<"Simon 왈 , 발가락을 "<< n <<"번 두드려라." <<endl;
// }

// #include <iostream>
// int stonetolb(int);

// int main()
// {
//     using namespace std;
//     int stone;
//     cout <<"체중을 스톤 단위로 입력하시오: ";
//     cin >>stone;
//     int pounds = stonetolb(stone);
//     cout << stone << "스톤은 ";
//     cout <<pounds << "파은드입니다." << endl;
//     return 0;
// }

// int stonetolb(int sts)
// {
//     return 14*sts;
// }

// #include <iostream>

// int main()
// {
//     using namespace std;
//     cout << "long int 의 바이트수" << sizeof(long)<<endl;
// }

// #include<iostream>
// #define ZERO 0
// #include <climits>
// int main()
// {
//     using namespace std;
//     short Dohee =SHRT_MAX;
//     unsigned short Insuk =Dohee;

//     cout << "도희의 계좌에는 " <<Dohee << "$이 들어 있고,";
//     cout << "인숙이의 계좌에도" <<Insuk <<"$이 들어있다." << endl;
//     cout << "각각의 계좌에 1원씩 입금한다." <<endl <<"이제";
//     Dohee++;
//     Insuk++;
//     cout << "도희의 잔고는 " << Dohee << "$이 되었고,";
//     cout << "인숙의 잔고는 " << Insuk << "$이 되었다." <<endl;
//     cout << "이럴수가! 도희가 나 몰래 대출을 했나?"<<endl;
//     Dohee=ZERO;
//     Insuk=ZERO;
//     cout << "도희의 계좌에는 " <<Dohee << "$이 들어 있고,";
//     cout << "인숙이의 계좌에도" <<Insuk <<"$이 들어있다." << endl;
//     cout << "각각의 계좌에 1원씩 입금한다." <<endl <<"이제";
//     Dohee--;
//     Insuk--;
//     cout << "도희의 잔고는 " << Dohee << "$이 되었고,";
//     cout << "인숙의 잔고는 " << Insuk << "$이 되었다." <<endl;
//     cout << "이럴수가! 인숙이가 복권당첨이 됐나?"<<endl;
//     return 0;
// }

// #include <iostream>

// int main()
// {
//     using namespace std;
//     char ch= 'M';
//     int i =ch;
//     cout << ch << "의 ASCII 코드는" <<i << "입니다."<<endl;
//     cout << "이 문자 코드에 1을 더해 보겠습니다." << endl;
//     ch = ch+1;
//     i=ch;
//     cout <<ch <<"의 ASCII 코드는"<<i <<"입니다."<<endl;

//     cout <<"cout.put(ch)를 사용하여  char형 변수 ch를 화면의 출력:";
//     cout.put(ch);
//     cout.put('!');
//     cout <<endl <<"종료"<<endl;
//     return 0;
// }

// #include <iostream>

// int main()
// {
//     using namespace std;
//     cout.setf(ios_base::fixed, ios_base::floatfield); //ios_base ::fixed,부동소수점 형태를 고정소수점 형태로 표현한다.
//     float tree =3;
//     int guess =3.9832;
//     int debt = 7.3E12;
//     cout << "tree = " <<tree <<endl;
//     cout << "guess = "<<guess <<endl;
//     cout <<"debt = "<<debt <<endl;
//     return 0;
// }

// #include <iostream>
// int main()
// {
//     using namespace std;
//     int yams[3];
//     yams[0] =7;
//     yams[1] =8;
//     yams[2] =6;
    
//     int yamcosts[3] ={200,300,50};

//     cout << "고구마 합계 = ";
//     cout << yams[0] + yams[1] + yams[2] <<endl;
//     cout << yams[1] << "개가 들어 있는 포장은 ";
//     cout << "개당 " << yamcosts[1] <<"원씩입니다.\n";
//     int total = yams[0] * yamcosts[0] +yams[1] *yamcosts[1];
//     total = total +yams[2]*yamcosts[2];
//     cout << "세 포장의 총 가격은 " <<total << "원입니다\n";
//     cout << "\nyams 배열의 크기는 "<< sizeof yams;
//     cout <<"바이트 입니다.\n";
//     cout <<"원소 하나의 크기는 " <<sizeof yams[0];
//     cout << "바이트입니다.\n";
//     return 0;
// }

// #include<iostream>
// #include<cstring>

// int main()
// {
//     using namespace std;
//     const int Size =15;
//     char name1[Size];
//     char name2[Size]="C++owboy";

//     cout << "안녕하세요 ! 저는 "<<name2;
//     cout <<"입니다! 실례지만 성함이?\n";
//     cin >>name1;
//     cout <<"아, "<<name1 <<"씨! 당신의 이름은";
//     cout<<strlen(name1) <<"자입니다만 \n";
//     cout <<sizeof(name1) << "바이트 크기의 배열에 저장되었습니다.\n";
//     cout << "이름이 "<< name1[0] <<"자로 시작하는군요.\n";
//     name2[3] ='\0';
//     cout <<"제 이름의 처음 세 문자는 다음과 같습니다: ";
//     cout<<name2<<endl;
//     return 0;
// }

// #include <iostream>
// int main()
// {
//     using namespace std;
//     const int ArSize =20;
//     char name[ArSize];
//     char dessert[ArSize];

//     cout <<"이름을 입력하세요:\n";
//     cin >>name;
//     cout <<"좋아하는 디저트를 입력하세요:\n";
//     cin >> dessert;
//     cout <<"맛있는 "<< dessert;
//     cout << " 디저트를 준비하겠습니다. " << name << " 님!" <<endl;
//     return 0; 
// }

// #include <iostream>
// int main()
// {
//     using namespace std;
//     const int ArSize =20;
//     char name[ArSize];
//     char dessert[ArSize];

//     cout <<"이름을 입력하세요:\n";
//     cin.getline(name,ArSize);
//     cout <<"좋아하는 디저트를 입력하세요:\n";
//     cin.getline(dessert,ArSize);
//     cout <<"맛있는 "<< dessert;
//     cout << " 디저트를 준비하겠습니다. " << name << " 님!" <<endl;
//     return 0; 
// }

// #include <iostream>
// #include <string>
// int main()
// {
//     using namespace std;
//     char charr1[20];
//     char charr2[20] ="jaguar";
//     string str1;
//     string str2 ="panther";
//     cout <<"고양이과의 동물 한 종을 입력하시오: ";
//     cin >> charr1;
//     cout << "고양이과의 또 다른 동물 한 종을 입력하시오: ";
//     cin >> str1;
//     cout << "아래 동물들은 모두 고양이과입니다: \n";
//     cout << charr1 << " " << charr2 << " "
//     << str1 << " " << str2 
//     << endl;
//     cout << charr2 << "에서 세 번째 글자: "
//     <<charr2[2] << endl;
//     cout << str2 << "에서 세 번째 글자: "
//     <<str2[2] <<endl;
//     return 0; 
// }

// #include <iostream>
// #include <string>
// int main()
// {
//     using namespace std;
//     string s1 = "penguin";
//     string s2,s3;
//     cout << "string 객체를 string 객체에 대입할 수 있다: s2 =s1\n";
//     s2 =s1;
//     cout << "s1: " << s1 << ", s2: " << s2 << endl;
//     cout << "string 객체에 C 스타일 문열을 대입할 수 있다.\n";
//     cout << "s2= \"buzzard\"\n";
//     s2 ="buzzard";
//     cout << "s2: " <<s2 <<endl;
//     cout << "string 객체들을 결합할 수 있다: s3 =s1 + s2\n";
//     s3 =s1 + s2;
//     cout << "s3: " <<s3 <<endl;
//     cout << "string 객체들을 추가할 수 있다.\n";
//     s1 +=s2;
//     cout <<"s1 += s2 --> s1= " <<s1<<endl;
//     s2 += "for a day";
//     cout << "s2 +=  \" for aday\" --> s2 = " << s2 <<endl;
//     return 0; 
// }

// #include <iostream>
// #include <string>
// #include <cstring>
// int main()
// {
//     using namespace std;
//     char charr[20];
//     string str;
//     cout << "입력 이전에 charr에 있는 문자열의 길이: "
//     << strlen(charr) <<endl;
//     cout <<"입력 이전에 str에 있는 문자열의 길이: "
//     <<str.size()<<endl;
//     cout <<"텍스트 한 행을 입력하시오:\n";
//     cin.getline(charr,20);
//     cout <<"입력한 텍스트: "<< charr <<endl;
//     cout <<"또 다른 텍스트 한 행을 입력하시오:\n";
//     getline(cin ,str);
//     cout <<"입력한 텍스트: "<< str<< endl;
//     cout << "입력 이후에 charr에 있는 문자열의 길이: "
//     << strlen(charr) <<endl;   
//     cout <<"입력 이후에 str에 있는 문자열의 길이: "
//     <<str.size()<<endl;
    
//     return 0;
// }

/*
클래스 생성자와 소멸자

생성자를 통해 클래스에서 선언한 맴버 변수를 초기화해서 사용할 수 있다.

보통 맴버 변수를 private로 선언하는대 이렇게 선언하면 외부에서 맴버 변수를 직접적으로

불러와 사용할 수 없다. 따라서 맴버 변수의 변화를 주려면 생성자를 이용해야한다.

기존의 헤더파일에서 함수를 쓴다던지 구조체를 이용한 변수를 사용한다던지 그러한 

부분에서 무분별하게 포인터를 사용했었다. 만약 포인터를 사용하다가

실수를 해서 어떤 부분에서 값이 이상해졌다면 찾기 힘들었을 것이다.

그런대 클래스는 내가 만들었던 헤더파일을 하나의 객체로 만들어준다.

구조체가 내가 원하는 변수들의 모음이었다면(함수포인터가 있지만 초기화 과정이 많이 귀찮다.)

클래스는 내가원하는 기능들을 어떤 변수를 선언하듯이 사용할 수 있다는 점이 좋은것 같다.

내가 c에서 어떤 특정한 함수를 여러번 사용한다고 할때 그 함수는 분명 같은 기능을 하지만 다른
것이다.

클래스는 함수와 여러가지 변수들의 집합이지만 내가 이것을 사용한다고 할때

하나의 클래스를 두고 나눠쓰는 느낌이 아니라 위에 함수처럼 여러번 사용하면

여러개의 같지만 다른 함수가 생성되는 느낌으로 사용할 수 있는 것이다.

이 말은 마치 c에서 하나의 헤더파일을 변수로 만들어서 사용하는 느낌이 들 정도이다.

옛날에도 부터 지금까지 객체라는 개념이 모호하게 느껴졌는대

헤더파일을 만들면서 프로젝트를 진행해봐서 객체라는 개념이 많이 뚜렷해진 느낌이다.

헤더파일을 클래스 처럼 만드려면 분명 엄청나게 큰 사이즈의 구조체안에

수많은 함수포인터가 들어가야 할것이다.

그런대 클래스는 그렇게 복잡한 과정을 거치지 않고 사용자가 무분별하게 변수를 사용하는 것을 막아

조금 더 안전하게 프로그래밍 할 수있게 해주고 생성과 동시에 초기화가 가능하여 사용자가 함수를 사용함에 있어서

c언어보다 편리함을 느끼게 해줄 것 같다.(다만 함수의 리턴타입 같은것을 신경쓰며 프로그래밍해야하는 것은 같다)

동적할당을 해줘야 한다면 한번에 해결할 수도 있다 

만약 class 타입에 변수 C와 헤더파일안에 구조체와 함수를 생각해보자

여러가지 구조체가 있고 그 구조체마다 쓰임이 다르면 각각의 구조체를 전부 할당해줘야 한다.
(LinEz프로젝트에서 했던 것처럼)

그런대 만약에 클래스로 만들었다면 그냥 클래스 타입 변수 C만 동적할당한다면?

당연히 해제도 C만 하면된다.

여러가지 함수와 변수의 생명주기를 한방에 해결할 수 있다.

segmentation에러가 발생해서 부랴부랴 static을 선언한다던지

따로 급하게 동적할당을 해준다던지 하는 구조적인 문제를 한방에 해결 할 수 있다.

(단 클래스 내부에서 동적할당을 한다면 소멸자를 이용해서 제거해야한다.)

지금 당장 생각난 클래스의 장점은 이정도 밖에 생각이 나지 않는다.

헤더 파일을 많이 만들어보고 사용해본 경험이 없어 아직 불편함을 크게 느끼지 못한 것일 수도 있다.

*/


