#include<stdio.h>

//for문

// int main(){
//     int num;
//     printf("    n     n의 세제곱\n");
//     for (int num = 0; num <=6 ; num++)
//     {
//         printf("%5d %5d\n",num,num*num*num);
//     }
//    return 0; 
// }

//for문예제

// int main(){
//     int secs;

//     for(secs =5 ; secs>0; secs--){
//         printf("%d초!\n",secs);
//     }
//     printf("발사!\n");
//     return 0;
// }

//for 문안에 꼭 ++가 아니여도 된다.

// int main(){
//     int n;
//     for (n=2; n<60; n=n+13)
//         printf("%d \n",n);
//     return 0;
// }



//문자는 정수로 형변환해서 ASCII코드를 읽어온다. 따라서 for문을 ASCII코드 즉 정수형태로 사용할 수 있다.

// int main(){
//     char ch;
//     for(ch='a'; ch<='z';ch++)
//         printf("%c에 해당하는 ASCII 코드값은 %d입니다.\n",ch,ch);
//     return 0;
// }

// int main(){
//     // for(int num = 1; num <= 6; num++)
//     //     printf("%d\n",num);
//     // for(int num=1;num*num*num<=216;num++)
//     //   printf("%d\n",num);
//     // double debt;
//     // for(debt = 100.0; debt <150.0; debt =debt*1.1)
//     //     printf("당신의 신용불량채무는 이제 $%.2f입니다.\n",debt);
//     // int x;
//     // int y=55;
    
//     // for(x=1;y<=75; y=(++x * 5) + 50)
//     //     printf("%10d %10d\n",x,y);
    
//     // int ans, n;
//     // ans =2;
//     // for(n = 3; ans <= 25;)
//     //     ans= ans* n;
//     // printf("n =%d; ans= %d.\n",n,ans);
//     // for(; ; )
//     //     printf("나는 끝없이 절망한다!\n");
    
//     // int num =0;
//     // for(printf("수를 계속해서 입력하시오!\n"); num !=6;
//     // scanf("%d",&num));
//     // printf("그것이 바로 내가 원하는 수입니다!\n");
//     return 0;
// }
// int main(){
// const int secret_code =13;
// int code_entered;

// do{
//     printf("13일의 금요일 공포증 치료 동호회에 들어오려면,\n");
//     printf("비밀 코드 번호를 입력하시오: ");
//     scanf("%d",&code_entered);
// }while (code_entered !=secret_code);
// printf("축하합니다 치료되었습니다!\n");

// }


// #define ROWS 6
// #define CHARS 10
// int main(){
// int row;
// char ch;

// for(row =0 ; row<ROWS; row++)
// {
//     for(ch='A'; ch< ('A' + CHARS); ch++)
//         printf("%c",ch);
//     printf("\n");
// }

// return 0;
// }

// #define ROWS 6
// #define CHARS 6
// int main(){
// int row;
// char ch;

// for(row =0 ; row<ROWS; row++)
// {
//     for(ch=('A'+row); ch< ('A' + CHARS); ch++) //ch에 이작점이 row에 의해 변경된다.
//         printf("%c",ch);
//     printf("\n");
// }

// return 0;
// }



// 변수의 이름을 잘 정해보도록 하고 특정한 상수를 쓸거면 이름을 지어주자

// #define SIZE 10
// #define PAR 72
// int main(){
//     int index,score[SIZE];
//     int sum =0;
//     float average;
//     printf("%d개의 골프 스코어를 입력하시오:\n",SIZE);
    
//     for(index=0; index<SIZE; index++)
//         scanf("%d",&score[index]);
//     printf("읽은 스코어들은 다음과 같다:\n");
    
//     for(index=0; index <SIZE; index++)
//         printf("%5d",score[index]);
//     printf("\n");
    
//     for(index=0; index < SIZE; index++)
//         sum +=score[index];
//     average = (float) sum/SIZE;
//     printf("스코어의 합 =%d, 평균 = %.2f\n ",sum,average);
    
//     printf("핸디캡이 %.0f이다.\n",average-PAR);
    
//     return 0;

// }
// #include <stdio.h>
// int main(){
//     const int FREEZING = 0;
//     float temperature;
//     int cold_days =0;
//     int all_days =0;
//     printf("최저 기온들의 목록을 입력하시오.\n");
//     printf("섭씨 단위를 사용하시오(입력을 끙내려면 q).\n");
//     while(scanf("%f",&temperature )==1)
//     {
//         all_days++; //제대로 된 숫자를 입력 받아서 총 날짜++
//         if(temperature <FREEZING)
//             cold_days++; //입력한 온도가 0보다 작으면 ++
//     }
//     if (all_days!=0)
//         all_days,100.0*(float)cold_days/all_days); //백분율 공식  전체 나누기 일부 *100 하면 일부가 몇퍼센트인지 알수있다.
//     if(all_days ==0)
//         printf("입력된 데이터가 없습니다!\n");
//     return 0;
// }

// #define SPACE ' '
// int main(){
//     char ch;
    
//     ch = getchar(); //사용자 입력을 받는다. 엔터도 포함 엔터는 \n으로 입력됌
//     while (ch != '\n')
//     {
//         if(ch == SPACE)
//             putchar(ch);
//         else
//             putchar(ch + 1);
        
//         ch = getchar(); //버퍼에 남아있는 데이터를 읽음 마지막은 \n -<엔터 누른거
//     }
//     putchar(ch);

//     return 0;
// }

// #include<ctype.h>
// int main(){
// char ch;
// while ((ch = getchar())!='\n'){
//     if (isalpha(ch) && ch>96)
//         putchar(ch-32);
//     else
//         putchar(ch);
// }
// putchar(ch);
// return 0;
// }
// #define RATE1 0.13230
// #define RATE2 0.15040
// #define RATE3 0.30025
// #define RATE4 0.34025

// #define BREAK1 360.0
// #define BREAK2 468.0
// #define BREAK3 720.0
// #define BASE1 (RATE1 *BREAK1)
// #define BASE2 (BASE1 +(RATE2 *(BREAK2 - BREAK1)))
// #define BASE3 (BASE1 +BASE2+ (RATE3 *(BREAK3-BREAK2)) )

// int main(){
//     double kwh;
//     double bill;
//     printf("사용한 전력량을 입력하시오.\n");
//     scanf("%lf",&kwh);
//     if (kwh <= BREAK1)
//         bill =RATE1 *kwh;
//     else if (kwh <= BREAK2)
//         bill =BASE1 +(RATE2 * (kwh -BREAK1));
//     else if (kwh <= BREAK3)
//         bill = BASE2 +(RATE3 *(kwh -BREAK2));
//     else
//         bill = BASE3 +(RATE4 * (kwh - BREAK3));
//     printf("%.1f kwh의 전기요금은 $%1.2f입니다.\n",kwh,bill);
    
//     return 0;
    
    
// }

// #include<stdio.h>
// #include<stdbool.h>

// int main(){
//     unsigned long num;
//     unsigned long div;
//     bool isPrime;
//     printf("검사할 정수를 하나 입력하시오");
//     printf("(끝내려면 q)\n");
//     while(scanf("%lu",&num)== 1){
        
//         for(div =2, isPrime =true; (div*div)<=num; div++)   
//         {
//             if(num %div ==0) //2로 나누어 나머지가 없으면 그다음 루프에서 3으로 나누고 나머지없으면 ~N번까지 나누어서등등
//             {
//                 if((div*div)!=num)
//                     printf("%lu,%lu:둘다 %lu약수다.\n",div,num/div,num);
//                 else
//                     printf("%lu,%lu의 약수다.\n",div,num);
//                 isPrime = false; //아무튼 나누어 졌으니까 false로 바꿔줌 소수가 아니라는것을 표현하기위해서
//             }
//         }
//         if(isPrime)
//             printf("%lu::소수다.\n",num);
//         printf("검사할 또 다른 정수를 하나 입력하시오");
//         printf("(끝내려면 q)\n");
//     }
//     printf("안녕!\n");

//     return 0;
// }