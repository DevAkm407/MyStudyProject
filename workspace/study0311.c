#include<stdio.h>
#include<stdlib.h>
// void IntOverFlow(long int integer){
//     int small=integer;
//     printf("%d가 %ld와 다르다면 overflow또는 underflow가 발생한것입니다.\n",small,integer);
// }

// void FloatOverFlow(long double F_pointer){
//     float small = (float)F_pointer;
//     printf( "%.9f가%.9Lf와 다르다면 오버플로우 또는 언더플로우가 발생한 것입니다.\n",small,F_pointer);
// }
int main(void){
    
    // float weight;
    // float value;
    // printf("당신릐 몸무게를 플래티넘 가치로 계산하면 얼마나 나갈까요?\n");
    // printf("어디 한번 계산해 봅시다.\n");
    // printf("몸무게를 파운드 단위로 입력하시요: ");
    // scanf("%f",&weight);//weight에 주소를 가지고 와서 해당 주소에 데이터(리터럴)을 넣어줌
    // value= 1700*weight*14.5833;
    // printf("당신의 몸무게를 플래티넘 가치로 계산하면 $%.2f입니다.\n",value);
    // printf("당신의 몸값은 그 정도 가치가 나갑니다. 플래티넘 가격이 떨어지면,\n가치를 유지하기 위해 식사량을 늘려야합니다.\n");
   
    // int ten=10;
    // int two=2;

    // printf("바르게 지정했을 때: ");
    // printf("%d에서 %d를 빼면 %d\n",ten,2,ten-two);
    // printf("틀리게 지정했을 때?: ");
    // printf("%d에서 %d를 빼면 %d\n",ten);
    // printf("%d에서 %d를 빼면 %d\n",ten,two,ten-two);//빼먹은거 수정

    // int x =100;
    // printf("10진수 =%d; 8진수 = %o; 16진수 %x\n",x,x,x);
    // printf("10진수 =%d; 8진수 = %#o; 16진수 %#x\n",x,x,x);
    
    // int i =2147483647;
    // unsigned int j = 4294967295;
    // printf("%d %d %d\n",i,i+1,i+2);
    // printf("%u %u %u\n",j,j+1,j+2);
    
    // char ch;
    // printf("키보드를 영문 모드로 놓고,문자 하나를 입력하시오.\n");
    // scanf("%c",&ch);
    // printf("문자%c에 대응하는 코드값은 %d이다.\n",ch,ch);
    
    // float aboat = 32000.0;
    // double abet =2.14e9;
    // long double dip= 5.23e-5;
    // printf("%f은 %e로 표현할 수 있다.\n",aboat,aboat);
    // printf("그것은 16진수 2의 거듭제곱으로 %a이다.\n",aboat);
    // printf("%f은 %e로 표현할 수 있다.\n",abet,abet);
    // printf("%Lf은 %Le로 표현할 수 있다\n",dip,dip);
      
    //자료형의 크기

    // printf("int형의 크기: %zd바이트\n",sizeof(int));
    // printf("char형의 크기: %zd바이트\n",sizeof(char));
    // printf("long형의 크기: %zd바이트\n",sizeof(long));
    // printf("long long 형의 크기: %zd바이트\n",sizeof(double));
    // printf("long double형의 크기:%zd바이트\n",sizeof(long double));

    /*
    1.다음과 같은 종류의 각 데이터에는 어떤 데이터형을 사용해야 하는가?(때로는 한 가지 이상의 데이터형이
    적용될 수도 있다.)
    a.서울시 인구 int
    b.dvd 영화 제작비 long
    c.이 장에서 가장 많이 사용한 글자 char
    d.이 장에 그 글자가 나타난 횟수 int
    
    2. int형 대신 long형 변수를 사용하는 이유는 무엇인가? int형으로 표현할 수 없는 범위를 표현하기 위해서

    4.다음과 같은 각 상수들에 대해 데이터형과 의미가 무엇인지 말하라.
    a. '\b' char 이스케이프 문자 백스페이스를 의미한다.
    b. 1066 정수형 리터럴 1066을 의미한다.int
    c 99.44 실수형 리터럴 99.44를 의미한다.float
    d.0xAA 16진수형 리터럴 AA를 의미한다.int
    e.2.0e30 실수형 지수식 리터럴 2.0e30을 의미한다.long double    
    
    5.Dottie Cawm이 에러가 잔뜩 들어 있는 프로그램을 하나 작성했다. 어디가
    잘못되었는지 꼬치꼬치 지적해 주어라.
    #include<stdio.h> #누락
    //함수 자료형 누락
    //괄호가 아니라 중괄호에 들어가야함
    void main(){
    float g;h;  //h초기화 안함 쓰지도 않음 g;이아니라 ,를 사용해야함
    float tax,rate; //rate초기화 안함
    g= 1.0e21; 지수만 있고 실수가없음 그리고 e21은 너무 큰값임 long double형으로 선언해야함.
    tax=rate*g; //rate가 초기화 핋요 g수식 변경필요
    }
    6.다음의 각 상수들에 대해(선언문에서 사용할)데이터형과 printf()포멧 지정자를 써 넣어라.
    
    a. 12 int %d
    b. 0x3 int %x
    c. 'c' char %c
    d. 2.34E07 double %Le
    e. '\040' char %c
    f. 7.0 float %f
    g. 6L long %ld
    h. 6.0f float %f
    i. 0x5.b6p12 double %a
    
    7.위와동일
    a.012 int %o
    b.2.9e05L long double %e
    c.'s' char %c
    d.100000 int %d
    e.'\n' char %c
    f.20.0f float %f
    g.0x44 int %x
    h.-40 int %d

    8.어떤 프로그램이 다음과 같은 선언들로 시작한다고 가정하라.
    int imate=2;
    long shot=53456;
    char grade='A';
    float log = 2.71828;
    printf("%d등에 당첨될 확률은 %ld분의 1이다.\n",imatem,shot);
    printf("%f의 성적의 %c학점이 아니다.\n",log,grade);

    9.ch를 char형 변수라고 가정하자. 캐리지 리턴 문자를 이스케이프 시퀀스,10진수 값
    8진수 문자 상수,16진수 문자 상수로 대입하는 문장을 각각 작성하라.(ASCII 코드값을 사용한다고 가정한다.)
    #include <stdio.h>
    void main(){
    char ch = '\r';
    printf("%d  %o  %x",ch,ch,ch);

    10.다음과 같이 작성된 프로그램에서 잘못된 곳을 수정하라.(c에서 /는 나눗셈을 의미한다.)
    void main(){
        int cows,legs;
        printf("젓소들의 다리를 세어보니 모두 몇개더냐?\n");
        scanf("%d",&legs);
        cows = legs / 4;
        printf("그렇다면 젖소가%d마리로구나.\n",cows);
    }
    11.다음과 같은 이스케이프 시퀀스가 나타내는 것은 각각 무엇인가?
    a. \n   다음줄로 커서 이동
    b. \\   \를 문자로 사용
    c. \"   "를문자로 사용
    d. \t    들여 쓰기
    */
  
  /*  int inte;
   printf("숫자입력:");
   scanf("%d",&inte);
   printf("%c\n",inte);*/
  
    // IntOverFlow(210000000000);
    // FloatOverFlow(0.123456789);
    // printf("갑작스런 소리에 깜짝 놀라 샐리는 외쳤다,\n \"호박대왕이다!\"\a");
    // float g;
    // float tax,rate;
    // g=1.0e3;
    // rate=2.0;
    // tax=rate*g;
    // printf("\n%f\n",tax);
    // char ch = '\r';
    // printf("%d %x %o\n",ch,ch,ch);
    return 0;
}

