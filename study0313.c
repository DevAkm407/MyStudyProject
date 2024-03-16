#include<stdio.h>

// 1번 데이터의 형변환

// void main(){
//     char ch;
//     int i;
//     float fl;
//     ch='C';
//     i=ch;
//     fl=i;    
//     printf("ch=%c,i=%d, fl = %2.2f\n",ch,i,fl);
//     ch=ch+1;
//     i= fl +2 * ch;
//     fl= 2.0 *ch+i;
//     printf("ch=%c,i=%d, fl = %2.2f\n",ch,i,fl);
//     ch=1107; //1107-1024=83
//     printf("이제 ch=%c\n",ch);
//     ch=80.99;
//     printf("이제 ch =%c\n",ch);
// }

//2번

// void pound(int n);

// int main(){
// int times=5;
// char ch='!';
// float f =6.0f;

// pound(times);
// pound(ch);
// pound(f);
// return 0;
// }

// void pound(int n){
//     while(n-- > 0){
//         printf("#");
//     }
//     printf("\n");
// }

//3번 캐스팅

// const int S_PER_M=60;
// const int S_PER_H=3600;
// const double M_PER_K=0.62137;
// void main(){
//     double distk, distm; //달린 거리(킬로미터와 마일)
//     double rate;         //평균 속도(mph, 시간당 마일 수로)
//     int min,sec;         //달린 시간(분 수와 초 수로)
//     int time;           //달린 시간(초 로만)
//     double mtime;       //1마일 달린 시간(초 로만)
//     int mmin,msec;      // 1마일을 달린 시간(분 수와 초 수로)

//     printf("이 프로그램은 미터단위계로 측정한 달리기 기록을\n");
//     printf("1마일을 달린 시간과, 평균속도(mph)로 변환한다.\n");
//     printf("달린 거리를 킬로미터 수로 입력하시오.\n");
//     scanf("%lf",&distk);
//     printf("달린 시간을 분 수와 초 수로 입력하시오.\n");
//     printf("먼저 분 수부터 입력하시오.\n");
//     scanf("%d",&min);
//     printf("이제 초 수를 입력하시오.\n");
//     scanf("%d",&sec);
//     //달린 시간을 순전한 초 수로 변환한다
//     time =S_PER_M*min+sec;
//     //킬로미터 수를 마일 수로 변환한다.
//     distm=M_PER_K*distk;
//     //초당 마일 수*시간당 초 =mph
//     rate=distm / time * S_PER_H;
//     //시간/거리 =마일당 시간
//     mtime = (double)time / distm;
//     mmin=(int)mtime / S_PER_M;
//     msec=(int)mtime % S_PER_M;
//     printf("당신은 %1.2f킬로미터(%1.2f마일)를 %d분, %d초에 달렸다.\n",distk,distm,min,sec);
//     printf("이 페이스 1마일을 %d분,%d초에 " "달린 것에 해당한다.\n",mmin,msec);
//     printf("평균속도는%1.2fmph였다.\n",rate);
//     }


//복습문제

/*
1.모든 변수를 int형이라고 가정할 때, 다음 각 변수의 값은 얼마인가?
a. x = (2 + 3) * 6          정답 30
b. x = (12 + 6) / 2 * 3       정답 27
c. y= x = (2 + 3 ) / 4      정답 1
d. y = 3 + 2 * (x = 7 / 2 ) 정답 9

2.모든 변수를 int형이라고 가정할 때, 다음 각 변수의 값은 얼마인가?
a. (int)3.8 +3.3          정답 6
b. x = (2 + 3) *10.5      정답 52
c. x= 3/5 *22.0           정답 0
d. x= 22.0 * 3 / 5        정답 13

3.다음 식의 각각을 계산하라.
a. 30.0 / 40.0 * 5.0    정답 3.75 
b  30.0 /(4.0*5.0)      정답 1.50
c. 30 / 4 * 5           정답 35.0
e. 30 / 4.0 * 5         정답 37.5
f. 30 / 4  *5.0         정답 35.0

4.다음 프로그램에서 잘못된 부분을 찾아라.
    원본
    
    int main(){
        int i =1;
        float n;
        printf("조심해! 한 무더기의 소수점을 가진 수들이 쏟아지다!\n");
        while(i<30)
            n =1/i;
            printf("%f",n)l
        printf("이제 끝이다!\n");
        return;
    }
    수정본

    int main(){
        int  i= 1;
        float n;
        printf("조심해! 한 무더기의 소수점을 가진 수들이 쏟아지다!\n");
        while(i++<30){ 조건식에 증감이 없었던걸 수정,중 괄호 없었던걸 수정
            n=1/(float)i; //실수 나누기 실수로 계산해야함
            printf(" %f ",n);
        }
        printf("이제 끝이다!\n");
        return 0;   
    }

    5.다음은 리스트 5.9를 조금 다르게 설계한 프로그램이다.리스트 5.9에 있는 누개의 scanf()문을 하나의 scanf()문으로
    대체함으로써 코드를 단순하게 하려고 시도한 것으로 보인다. 무엇이 이 설계를 리스트 5.9보다 못하게 만들었을까?
    
    원본
    
    #include<stdio.h>
    #define S_TO_M 60
    int main(){
        int sec,min,left;
        printf("이 프로그램은 초 수로만 주어지는 시간을");
        printf("분 수와 초 수로 변환한다.\n");
        printf("초 소를 입력하시오.\n");
        printf("프로그램을 종료하려면 0을 입력하실오.\n")l
        while(sec > 0){
            scanf("%d",&sec);
            min = sec/S_TO_M;
            left = sec % S_TO_M;
            printf("%d초는 %d분, %d초입니다.\n")
            printf("다음 입력은?\n");
        }
        printf("안녕\n");
        return 0;
    }

    수정본
    #include<stdio.h>
    #define S_TO_M 60
    int main(){

    }


*/

//반복문
// #include <stdio.h>

// void main(){
//     long num;
//     long sum =0L;
//     int status;
//     printf("합을 구할 정수를 하나 입력하시오");
//     printf("(끝내려면 q): ");
//     status = scanf("%ld",&num);
//     while(status==1){
//         sum =sum+num;
//         printf("다음 정수를 입력하시오(끝내려면 q): ");
//         status =scanf("%ld",&num);

//     }
//     printf("입력된 정수들의 합은 %ld입니다.\n",sum);
    

// }

//반복문2

// #include<math.h>
// int main(){
//     const double ANSWER = 3.14159;
//     double response;

//     printf("원주율의 값이 얼마지?\n");
//     scanf("%lf",&response);
//     while(fabs(response-ANSWER)>0.0001) //가깝다는 것은 약간 큰것도 가까운 것이고 약간 작은 것도 가까운것이다.
//     {
//         printf("다시 말해 봐!\n");
//         scanf("%lf",&response);       
//     }
//     printf("충분히 가깝다\n");
//     return 0;
// }
 
// int main(){
//     int n = 3;
//     while (n)
//         printf("%2d:참\n",n--);
//     printf("%2d:거짓\n",n);
    
//     n=-3;
//     while (n)
//         printf("%2d:참\n",n++);

//     printf("%2d:거짓\n",n);
    
//     return 0;
// }


// void main(){
//     long num;
//     long sum =0L;
//     int status;
//     printf("합을 구할 정수를 하나 입력하시오");
//     printf("(끝내려면 q): ");
//     status = scanf("%ld",&num);
//     while(status=1){
//     //status=1 이 조건식에 들어가 있어 status를 확인할때마다 항상 1이 들어있어 true가 됩니다.
//         sum =sum+num;
//         printf("다음 정수를 입력하시오(끝내려면 q): ");
//         status =scanf("%ld",&num);
//     }
    
//     printf("입력된 정수들의 합은 %ld입니다.\n",sum);
    
// }

void main(){
    //1~10까지 출력하기
    int i=0;
    while (i++ <10)
    {
        printf("%d\n",i); 
    }
    //10~1까지 출력하기
    while (i-- > 1)
    {
        printf("%d\n",i);
    }
    
    //0~100까지 짝수 출력하기
    i=0;
    printf("\n");
    while (i<101)
    {
        printf("%d\n",i);
        i=i+2;
    }
    i=0;
    int c=0;
    printf("\n");

//정삼각형 만들기   
    i=1;
    c=0;
    int j=0;
   
    while(i<16){
        while (j++<16-i) printf(" ");
        
        while(c++<i){
            printf("* ");
            }
    
    printf("\n");
    
    c=0;
    j=0;   
    i=i+2;
    }
    printf("\n");
////////////////////////////////////////////////////////////////////////
//마름모 만들기
    i=1;
    c=0;
    j=0;
   //마름모 상단
    while(i<16){
        while (j++<16-i) printf(" ");
        
        while(c++<i){
            printf("* ");
            }
    
    printf("\n");
    
    c=0;
    j=0;   
    i=i+2;
    }
    
    i=13;
    c=0;
    j=0;
   //마름모 하단
    while(i>0){
        while (j++<16-i) printf(" ");
        
        while(c++<i){
            printf("* ");
            }
    
    printf("\n");
    
    c=0;
    j=0;   
    i=i-2;
    }
    printf("\n\n\n");
    //모래시계
    /////////////////////////////////////////////////////////////////////
    
    i=0;
    j=0;
    c=0;
    //모래시계 상단
    while(i++<10){
        
        while (c++<i)
        {
            printf(" ");
        }
        
        
        while (j++<11-i)
        {
            printf("* ");    
        }
        c=0;
        j=0;
        printf("\n"); 
    }   
    printf("\b");

    i=0;
    j=0;
    c=0;
    
    //모래 시계 하단
    
    while(i++<10){
        
        while (c++<10-i)
        {
            printf(" ");
        }
        while (j++<i+1)
        {
            printf("* ");    
        }
        c=0;
        j=0;

        printf("\n"); 
    }

/////////////////////////////////////////////////////////////////////////    












    
    //크리스마스 트리만들기
    
    i=1;
    j=0;
    c=1;
    int k=0;
    int s=0;
    int w=0;
    printf("정수를 입력해주세요: ");
    scanf("%d",&i);    
    
    
    while (j++<i) //전체반복획수
    {
        while (c<=5)//총 3개의 잎을만들기 때문에 3번반복
        {
            while (s++<(2*i+3)-(c+k))//k는 최종적으로 i*2만큼 증가함 하지만 마지막으로 사용되는 k는 (i*2)-2 이기때문에 공백이 모자를 가능성이 있음
            //c는 어차피 1~5까지 밖에 변하지 않는 수 마지막줄의 별의 개수는 k+5개지만 왼쪽을 기준으로는 1개씩증가하는 모습을 보이기에 +3을 사용함
            {
                printf(" ");
            }
            while (w++<c+k)//별표
            {
                printf("* ");
            }
            printf("\n");
            w=0;//별초기화
            s=0;//공백 초기화 
            c=c+2;//별이 2개씩 증가하니까 그부분 표현
        }
        c=1;
        k=k+2;        //k는 최종적으로 i*2
    }
    //밑둥이 가운대에 있다고 느끼게 되는 부분은 트리에 꼭대기에 있는 별의 지점이다 해당지점은 2*i+3개의공백을가지고 별을 찍는다
    //찍히는 별의 가운대가 3번째 이므로 공백의 개수를 2*i개로 결정한다.
    
    j=0;
    c=0;
    while (j++<3)
    {
        while (c++<(2*i))

        {
         printf(" ");   
        }
        c=0;
        printf("* * * * *\n");
    }
   ///////////////////////////////////////////////////////////////////////////
   
   
   
   
    // 화살표 만들기
    //정수 입력받기 
    //그 횟수만큼 화살표의 길이가정해짐 삼각형이 받은 정수 값/2 
    //정사각형의 길이 받은정수값/2 
//     i=0;
//     j=0;
//     c=1;
//     k=0;
//     printf("정수를 입력해주세요: ");
//     scanf("%d",&i);
//     while (c<i+1)
//     {
//         while (k++<i-c)
//         {
//             printf(" ");
//         }
//         while (j++<c)
//         {
//            printf("* ");
//         }
//        printf("\n");
//         k=0;
//         j=0;
//         c=c+2;
//     }
//    c=0;
//    k=0;
//    j=0;
//    while(c++<(float)i/2)
//    {
//     while(k++<(float)i/2) printf(" ");
//     while (j++<(float)i/2) printf("* ");
//     k=0;
//     j=0;
//     printf("\n");
//    } 




}



