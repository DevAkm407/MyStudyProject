#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<float.h>
#define DENSITY 62.4
#define PRAISE "You are an extraordinary being."
#define PI 3.14159
// 1번

// void main(){
//     float weight,volume;
//     int size,letters;
//     char name[40];
//     printf("하이! 이름이 뭐에요?\n");
//     scanf("%s",name);
//     printf("%s씨,몸무게는 몇 파운드나 나가요?\n",name);
//     scanf("%f",&weight);
//     size = sizeof name;
//     letters = strlen(name);
//     volume = weight/DENSITY;
//     printf("옳거니,%s 씨의 몸은 %2.2f입방피트를 차지합니다.\n",name,volume);
//     printf("그리고 이름이 %d글자니까,\n",letters);
//     printf("저장하려면 %d바이트가 필요합니다.\n",size);   
// }

// 2번

// void main(){
// char name[40];

// printf("실례지만 성함이 어떻게 되시는지?\n");
// scanf("%s",name);
// printf("반갑습니다,%s씨.%s\n",name,PRAISE);
// printf("이름은 %zd글자인데 메모리 셀 %zd개를 차지합니다.\n",strlen(name),sizeof name);
// printf("감탄문은 %zd글자인데",strlen(PRAISE));
// printf("메모리 셀 %zd개를 차지합니다.\n",sizeof PRAISE);

// }  

//3번

// void main(){
//     float area,circum,radius;
//     printf("피자의 반지름이 얼마냐?\n");
//     scanf("%f",&radius);
//     area=PI*radius*radius;
//     circum=2.0*PI*radius;
//     printf("피자의 기본 매개변수는 다음과 같다:\n");
//     printf("circumference = %1.2f,\narea=%1.2f\n",circum,area);
// }

// 4번
// void main(){
//     printf("이 시스템이 표현하는 수의 한계:\n");
//     printf("int형 최대값:%d\n",INT_MAX);
//     printf("long long형 최소값:%lld\n",LLONG_MIN);
//     printf("이 시스템에서 1바이트 %d비트이다.\n",CHAR_BIT);
//     printf("double형 최대값:%e\n",DBL_MAX);
//     printf("float형 최소값:%e\n",FLT_MIN);
//     printf("float형 정밀도는 소수점 아래%d자리까지\n",FLT_DIG);
//     printf("float형 epsilon = %e\n",FLT_EPSILON);
// }

//5번

// void main(){
//     const double RENT =3852.99;
//     printf("*%f*\n",RENT);
//     printf("*%e*\n",RENT);
//     printf("*%4.2f*\n",RENT);
//     printf("*%3.1f*\n",RENT);
//     printf("*%10.3f*\n",RENT);
//     printf("*%10.3E*\n",RENT);
//     printf("*%+4.2f*\n",RENT);
//     printf("*%010.2f*\n",RENT);

// }

//6번

// void main(){

//     printf("이것은 긴 문자열을 출력하는");
//     printf("첫 번째 방법이다.\n");
//     printf("이것은 긴 문자열을 출력하는 \
//     두번째 방법이다.\n");
//     printf("이것은 긴 문자열을 출력하는"
//     " 가장 새로운 방법이다.\n");

// }

//7번

// void main(){
//     unsigned width,precision;
//     int number=256;
//     double weight =242.5;

//     printf("필드 너비를 입력하시오:\n");
//     scanf("%d",&width);
//     printf("Number:%*d:\n",width,number);
//     printf("필드 너비와 정밀도를 함께 입력하시오:\n");
//     scanf("%d %d",&weight,&precision);
//     printf("Weight= %*.*f\n",width,precision,weight);
//     printf("종료!\n");
// }

// //8번
// void main(){
// int n;
// printf("3개의 정수를 입력하기오:\n");
// scanf("%*d %*d %d",&n);
// printf("마지막으로 입력한 정수는 %d이다.\n",n);
// }


/*
부록문제
1.리스트4.1을 다시 실행하라.이번에는 이름을 요구할 떄,second name과 first name을
분리하여 입력시켜라. 무슨 일이 일어나는가? 그 이유는 무엇인가?

답:second name과 first name을 분리시키서 입력하면 2번째 scanf가 실해되지 않고 넘어간다.
그이유는 scanf가 backspace를 만나면 데이터를 버퍼에 입력하고 다음 데이터를 만나면 버퍼에 넣는다.
즉 하나의 데이터라고 생각하고 입력했지만 backspace를 사용함으로 써 2개의 데이터로 분리되었고
second name은 사용되어 없어졌지만 first name이 버퍼에 남아 다음 scanf가 실행됨과 동시에 입력되어
사용자 입력을 받지못한다.

2.아래의 각예제들을 완전한 프로그램의 일부라고 가정하자. 그렇다면 각각 무엇을 출력하겠는가?
a.printf("그는 그 그림을 $%2.2f에 팔았다.\n",2.345e2);
정답:그는 그 그림을 $234.50에 팔았다.
b.printf("%c%c%c\n",'H',105,'\41');
정답:Hi!
c.#define Q "그의 햅릿은 저속하지 않고 재미있었다."
  printf("%s\n는 %d 문자이다.\n",Q,strlen(Q));
정답:그의 햅릿은 저속하지 않고 재미있었다.
는 53 문자이다. 
d.printf("%2.2e은%2.2f과 같으냐?\n",1201.0,1201.0);
정답:1.20e+03은1201.00과 같으냐?

3.문제2c.에서 문자열 Q를 큰따옴표로 감싼상태로 출력하려면 무엇을 변경해야 하는가?
정답:%s를 \"%s\"로해주면 된다.

4.다음과 같은 프로그램에서 에러를 찾아라
define B 거짓말
define X 10
main(int)
{
    int age;
    char name;
    printf("이름이 뭡니까?");
    scanf("%s",name);
    printf("좋아요,%c씨,나이는 얼마죠?\n",name);
    scanf("%f",age);
    xp = age +X;
    printf("%s!최소한%d세는 되어 보이는데.\n",B,xp);
    return 0;
}

수정본
#define B "거짓말" #빼먹음 ""빼먹음
#define X 10 #빼먹음
int main() ()에 넣을꺼면 변수를 재대로 넣어야함,main 자료형지정해줘야함
{
    int age;
    char[20] name;
    printf("이름이 뭡니까?");
    scanf("%s",name);
    printf("좋아요,%s씨,나이는 얼마죠?\n",name); %c가아니라%s로사용해야함
    scanf("%d",&age); %f가아니라 %d age가아니라 &age를 사용해야함
    int xp = age +X; int로 자료형 지정
    printf("%s!최소한%d세는 되어 보이는데.\n",B,xp);
    return 0;
}

5.#define BOOK "전쟁과 평화"
int main(){
    float cost = 12.99;
    float percent =80.0;
다음과 같이 출력하기 위해 BOOK,cost,percent를 사용하는 printf()문을 작성하라.
신간 '전쟁과 평화"를 $12.99에 드립니다.
그것은 정가의 80%가격입니다/

정답:
#define BOOK "전쟁과 평화"
int main(){
    float cost = 12.99;
    float percent = 80.0;
    printf("신간 \"%s\"를 $%.2f에 드립니다.\n그것은 정가의 %d%% 가격입니다 ",Book,cost,percent);
}

*/

//연산자

// #define ADJUST 7.31
// int main(){
//     const double SCALE=0.333;
//     double shoe,foot;

//     shoe=9.0;
//     foot=SCALE * shoe + ADJUST;
//     printf("신발 사이즈(남자용) 발길이\n");
//     printf("%10.1f %15.2f인치\n",shoe,foot);
//     return 0;
// }

//연산자2

// #define ADJUST 7.31
// int main(){
//     const double SCALE=0.333;
//     double shoe,foot;
//     printf("신발 사이즈(남자용)       발길이\n");
//     shoe=3.0;
//     while(shoe <18.5){
//         foot = SCALE * shoe + ADJUST;
//         printf("%10.1f %15.2f 인치\n",shoe,foot);
//         shoe = shoe +1.0;
//     }
//     printf("그 신발이 발에 맞는다면,그것을 신으세요.\n");    
//     return 0;
// }

// #define SQUARES 64
// int main(){
//     const double CROP=2E16;
//     double current,total;
//     int count =1;
//     printf("네모카 추가\t\t누계\t\t");
//     printf("세계 수확량과의\t\t\n");
//     printf("번 호 낱알 수\t\t낱알 수\t\t");
//     printf("상대비율\t\t\n");
//     total=1.0;
//     current=1.0;
//     printf("%4d %13.2e %12.2e %12.2e\n",count,current,total,total/CROP);
//     while (count<SQUARES)
//     {
//         count=count+1;
//         current =2.0*current;
//         total=total +current;
//         printf("%4d %12.e %12.2e %12.2e\n",count,current,total,total/CROP);

//     }
//     printf("이제 끝이다.\n");
//     return 0;
    
// }

//증가 연산자 ++a, a++

// int main(){
//     int a =1;
//     int b=1;
//     int a_post,pre_b;
//     a_post =a++;
//     pre_b=++b;
//     printf("a\ta_post\tb\tpre_b\n");
//     printf("%d\t%d\t%d\t%d\n",a,a_post,b,pre_b);
//     return 0;
// }

// #define MAX 100
// int main(){
//     int count =MAX +1;
//     while (--count>0)//--가 먼저 계산
//     {
//         printf("%d 병의샘물이 냉장고에 있었네,%d 병이!\n",count,count);
//         printf("그 중 한 병을 꺼내 마셨지,\n");
//         printf("%d 병의 샘물이 아직 남았네!\n\n",count-1);
//     }
//     return 0;
// }

//연습문제

/*

int num1 = 0;
int num2 = 10;
int result1 = num1++ + num2; 답:10      
다음 num1 = 1 num2 = 10
int result2 = ++num1 + num2++ 답:12     
다음 num1=2 num2=11 
int result3 = num1-- + num1-- - --num2;답 -7 
다음num1 = 0 num2=10 
int result4 = num2++ * num1++ - --num2 +num1; 답:-9 
다음num1=1 num2=-9

*/

// void main(){

// int num1 = 0;
// int num2 = 10;
// int result1 = num1++ + num2;// 답:10  다음 num1 = 1 num2 = 10
// int result2 = ++num1 + num2++; //답:12 다음 num1=2 num2=11 
// int result3 = num1-- + num1-- - --num2;//답 -7 다음num1 = 0 num2=10 
// int result4 = num2++ * num1++ - --num2 +num1; //답:-9 다음num1=2 num2=9
// printf("%d\t%d\t%d\t%d\n",result1,result2,result3,result4);
// }
// void up_and_down(int);

// int main(void){
//     up_and_down(1);
//     return 0;
// }

// void up_and_down(int n){
//     printf("Level %d: n의 메모리 주소 %p\n",n,&n);
//     if(n<4)
//         up_and_down(n+1);
//     printf("Level %d: n의 메모리 주소 %p\n",n,&n);
// }































