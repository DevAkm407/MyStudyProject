// #include<stdio.h>
// #include<ctype.h>
// #define SIZE 26

//프로그램이 연습

//1번
// int main(){
//     char ch[SIZE];
//     int i=0;

//     for(i=0; i<SIZE;i++ ){
//         ch[i]=('A'+i);
//         printf("%c",ch[i]);
//     }printf("\n");    
//     // while (i<SIZE)
//     // {
//     //     ch[i]=('A'+i);
//     //     printf("%c",ch[i]);
//     //     i++;
//     // }
//  return 0; 
// }

//2번
// int main(){
//     for (size_t i = 0; i < 6; i++)
//     {
//         for (size_t j = 0; j < i; j++)
//         {
//             printf("$");
//         }
//         printf("\n");
//     }
//     return 0;
// }

//3번
// int main(){
//   char ch='F';
//   for (size_t i = 0; i < 7; i++)
//     {
//         for (size_t j = 0; j < i; j++)
//         {
//             printf("%c",(char)(ch-j));
//         }
//         printf("\n");
//     }
//     return 0;  
// }

//4번

// int main(){
//       char ch='A';
//   for (size_t i = 0; i < 7; i++)
//     {
//         for (size_t j = 0; j < i; j++)
//         {
//             printf("%c",(ch));
//             ch=(char)(ch+1);
//         }
//         printf("\n");
//     }
//     return 0;  
// }

//5번
//scanf에서 대문자만 받게하기 ASCII참조 65~90
// #include<stdio.h>
// #include<ctype.h>
// int main(){
// char ch;
// char ce;
// char cw;
// int i=1;
// int j=0;    
// int k=0;  
// int a[10];
//    do{
//     printf("알파벳 대문자를 입력해주세요:");
//     scanf("%c",&ch);
//    }while (  ch<65||ch>90 ); //do while 문으로 원하는 알파벳을 입력받자
 
//  int alpindex= ch - 'A'; //A와비교해서 몇번 반복해야하는지 예를들어 E는 69 - 65= 4 
  
//   while(i<=alpindex+1){  //E를 예를 들면 E가 A보다 4크기 때문에 i가 적어도 4보다는 큰 숫자가 되어주어야한다.
//     for (size_t x = 0; x <alpindex+1-i ; x++) //공백
//     {
//         printf(" ");
//     }
//     for ( j = 0; j < i; j++) //가장 큰 알파벳까지 적는 부분 
//     {
//         ce='A'+j;
//         printf("%c",ce);
//     }
    
//     for ( k = 1; k < i; k++) //줄어도는 곳은 항상 위에 것 보다 1번덜 실행된다.
//     {
//         cw=ce-k;
//         printf("%c",cw);
        
//     }   
//   printf("\n");
//   i++;
//   }
// }

// 문제 6

// #include<stdio.h>
// #include<ctype.h>
// int main(){
//     int num;
//     int lastnum;
//     printf("시작하는 정수를 입력해주세요:");
//     scanf("%d",&num);
//     printf("마감하는 정수를 입력해주세요: ");
//     scanf("%d",&lastnum);
//     for(int i=num;i<=lastnum; i++)
//         printf("정수:%d 제곱: %d 세제곱:%d \n",i,i*i,i*i*i);
//      return 0;
// }

// //문제7
// #include<stdio.h>
// #include<string.h>
// int main(){
//     char ch[7]="famouos";
//     for (int i = strlen(ch); i >= 0 ; i--)
//     {
//         printf("%c",ch[i]);
//     }
//     printf("\n");
    
//     return 0;
// }

//문제8
// #include<stdio.h>
// int main(){
// double findex;
// double lindex;
// do {printf("첫번째 실수 입력:");
// scanf("%lf",&findex);
// printf("두번째 실수 입력:");

// }while(scanf("%lf",&lindex) !=1);
// printf("(%.3lf - %.3lf)/(%.3lf * %.3lf) = %.3lf",findex,lindex,findex,lindex,(findex-lindex)/(findex*lindex));
//}

//10번

// #include<stdio.h>

// int main()
// {
//     int mini;
//     int max;
//     int sum=0;
//     int prev;
//     printf("정수로 하한과 상한을 입력하시오: ");
//     scanf("%d %d",&mini,&max);
//     while(mini != max && max>mini)
//     {
//         sum=0;
//         prev=mini;
//         for ( mini=prev; mini <= max; mini++)
//         {
//             sum+=mini*mini;
           
//         }
//         printf("%d부터 %d까지,제곱들의 합은 %d\n",prev*prev,max*max,sum);
//         printf("다음 하한과 상한을 입력하시오: ");
//         scanf("%d %d",&mini,&max);
//     }
//     printf("종료!");
//     return 0; 
// }

//11번
// 8개의 정수를 읽어 배열에 저장한다.-> 사용자입력으로 정수를 8개 입력받는다?
// #include<stdio.h>
// #define SIZE 8
// int main()
// {
//     int array[SIZE];
//     for (int  i = 0; i < SIZE; i++)
//     {
//         printf("정수를 입력해 주세요: ");
//         scanf("%d",&array[i]);
//     }
//     for (int  i=SIZE-1; i >= 0; i--)
//     {
//             printf("%d ",array[i]);
//     }
//     printf("\n");
//     return 0;
// }

//12번 
//double형을 쓰는게 좋은것 같고 사용자가 지정하는 수를 받고 +만 하는것돠 +,- 반복되는거 2개를 구현
// #include<stdio.h>

// int main()
// {
//     double sum=0;
//     double plusminus=0;
//     int minus=-1;
//     int max;
//     printf("최대값을 입력해주세요:");
//     scanf("%d",&max);
//     for (int i = 1; i <= max; i++)
//     { 
//         sum+= (1.0/(float)i);  
//     }
//     for (int i = 1; i <= max; i++)
//     {
//         minus*=-1;
//         plusminus+=minus*1.0/(float)(i);
//     }
//      printf("첫번째 값: %lf 두번째 값: %.9lf",sum,plusminus);  

//     return 0;
// }

//13번

// #include<stdio.h>
// #define SIZE 8
// int main()
// {
// int array[SIZE];
// int twozz=1;
// for (int i = 0; i <SIZE ; i++)
// {
//     twozz*=2;
//     array[i]=twozz;
// }
// int i=0;
// do{
//     printf("%d\n",array[i]);
//     i++;
// }while(i<SIZE);
// return 0;
// }


//14번
// #include <stdio.h>
// #define SIZE 8
// int main()
// {   
//     double array[SIZE];
//     double arraysum[SIZE];
//     int sum=0;
//     for (int i = 0; i < SIZE; i++)
//     {
//        int input;
//        printf("%d번째 숫자입력:",i);
//        scanf("%d",&input);
//        array[i]=input;
//        sum+=input;
//        arraysum[i]=sum;
//     }
    
//     for (int i = 0; i < SIZE; i++)
//     {
//         printf("%.2lf ",array[i]);
//     }
//     printf("\n");
//     for (int i = 0; i < SIZE; i++)
//     {
//         printf("%.2lf ",arraysum[i]);
//     }   
//     return 0;
// }

//15번
// #include<stdio.h>
// int main()
// {
//     char ch[255];
//     int i=0;
//     printf("문자열을 입력해 주세요: ");
//     while(scanf("%c",&ch[i])!=0 && ch[i] !='\n'){
//         i++;
//         }
   
//     for (int j = 0; j <=i; j++)
//     {
//         printf("%c",ch[j]);
//     }
    
//     return 0;
// }

//16번

// #include<stdio.h>
// int main()
// {
//     int year=0;
//     double Daphne=5000.0;
//     double Deirdre=2000.0;
//     while (Deirdre<Daphne)
//     {
//         year++;
//         Daphne+=100.0;
//         Deirdre*=1.05;
//     }
//     printf("Deirdre가 Daphne을 초과하는대 걸린 햇수:%d 그리고 그돈%lf\n",year,Deirdre);
// return 0;
// }


//17번 
// #include<stdio.h>

// int main()
// {
// double lucky=1000000.0;
// int year=0;
// while (lucky-100000 > 0)
// {
//     year++;
//     lucky*=1.08;
//     lucky-=100000;
// }
// printf("%d년뒤 그는 거지가 되었다.\n",year);
// return 0;
// }

//18번
#include<stdio.h>
int main(){
    int Rabund=5;
    int count=1;
    while(Rabund<150){
        Rabund-=count;
        Rabund*=2;
        count++;
    }
    printf("%d명이고%d주 걸렸다.",Rabund,count);
    return 0;
}
