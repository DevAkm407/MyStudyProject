// 참조를 하는 이유!!!

//long double형 변수 a의 크기는 16바이트이지만 loung double* c는 8바이트이다.

//만약 100바이트짜리 사용자 정의 데이터 타입 letType이 있다고 하자 

// letType형 변수 a에 여러가지 데이터를 넣었고 그 데이터를 사용한다고 하자

//참조를 이용한다면 a의 데이터를 복사할 필요도 없고  a의 데이터를

//손상시키지 않은 상태로 이용할 수 있다 심지어 참조역활을 수행하는 변수는 8바이트이다.

// #include<stdio.h>
// int main()
// {
// int x=1000;
// int* p=&x;
// float* fp=&x;
// long double a;
// long double* c;
// printf("%zd는 p의 크기 %zd는fp의 크기 long double의크기: %zd long double 포인터의 크기: %zd\n "\
// ,sizeof(p),sizeof(fp),sizeof(a),sizeof(c));

// return 0;

// }



// #include<stdio.h>
// #include<stdlib.h>

// int main()
// {
//     int num1 =15;
//     int num2 =30;
//     int num3 =45;
//     int* p =&num1;
//     int* ptr1=&num1;
//     int* ptr2=&num2;
//     int* ptr3=&num3;
//     ptr1 = ptr2;
//     ptr2 = ptr3;
//     *ptr3 *= 2;
//     *ptr1 += *ptr3;
//     *ptr2 *=2;
//     printf("%d %d %d",num1,num2,num3);
//     return 0;
// }

// #include<stdio.h>
// #define MONTHS 12   
// int main(void)
// {
//     int days[MONTHS] = {31,28,31,30,31,30,31,31,30,31,30,31};
//     int index;

//     for ( index = 0; index < MONTHS; index++)
//     {
//         printf("%2d월: 날짤 수 %2d\n",index +1 ,days[index]);
//     }
//     return 0;
// }

// #include<stdio.h>
// #define SIZE 4
// int main(void){
//     int no_data[SIZE]={1492,1066};
//     int i;
//     printf("%2s%14s\n","i","no_data[i]");
//     for ( i = 0; i < SIZE; i++)
//     {
//        printf("%2d%14d\n",i,no_data[i]);
//     }
    
//     return 0;
// }

// #include<stdio.h>
// #define MONTHS 12   
// int main(void)
// {
//     int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
//     int index;
//     int sum=0;
    
//     for ( index = 0; index < MONTHS; index++)
//     {
//         sum+=days[index]*2; 
//         printf("%2d월: 날짤 수 %2d 모든배열의 합*2 %d\n",index +1 ,days[index],sum);
//     }
    
//     return 0;
// }



// #include<stdio.h>
// #define MONTHS 12
// #define YEARS 5
// int main()
// {
//     const float rain[YEARS][MONTHS]=
//     {
//         {4.3, 4.3, 4.3, 3.0, 2.0, 1.2, 0.2, 0.2, 0.4, 2.4, 3.5, 6.6},
//         {8.5, 8.2, 1.2, 1.6, 2.4, 0.0, 5.2, 0.9, 0.3, 0.9, 1.4, 7.3},
//         {9.1, 8.5, 6.7, 4.3, 2.1, 0.8, 0.2, 0.2, 1.1, 2.3, 6.1, 8.4},
//         {7.2, 9.9, 8.4, 3.3, 1.2, 0.8, 0.4, 0.0, 0.6, 1.7, 4.3, 6.2},
//         {7.6, 5.6, 3.8, 2.8, 3.8, 0.2, 0.0, 0.0, 0.0, 1.3, 2.6, 5.2}
//     };
    
//     int year,month,rainmonth;
    
//     float subtot, total;
//     printf("년도    강우량(인치)\n");
    
//     for ( year = 0; year < YEARS; year++)
//     {
//         total=0.0;
//         for (month = 0; month < MONTHS; month++)
//         {
//             if(total< rain[year][month]){
//                 total=rain[year][month];
//                 rainmonth=month;
//            }
//         }
//         printf("%d년의 가장 비가많이온날은 %d월입니다.\n",year+2010,rainmonth+1);
//     }
    



    
//     printf("\n");
//     return 0;
// }

#include<stdio.h>

void reverse(int* p);

int main()
{
    // //1번
    // int sum=0;
    // for (int i = 1; i <= 100; i++)
    // {
    //     sum +=i;
    // }
    // printf("%dsum\n",sum);
    //2번
    // int sum=0;
    // for (int i = 0; i <= 100; i+=2)
    // {
    //     sum+=i;
    // }
    // printf("%d",sum);}
    
    //3번
//     int sum=0;
//     for (int i = 1; i <= 100; i++)
//     {
//         sum += i%2==0 ? i : 0;
//     }
//     printf("%d",sum);
// }


    //4번
//     int sum=0;
//     int minus=-1;
//     for (int i = 1; i<=100; i++)
//     {
//         minus*=-1;
//         sum +=minus*i;
//     }
//     printf("%d\n",sum);
// }
    //5번
//     int sum=1;
//     for (int i = 1; i <= 5; i++)
//     {
//         sum *=i;
//     }
// }
    //6번
    // int n=0;
    // for (int i = 1; i <= 10; i++)
    // {
    //     n= 10%i==0 ? i : 0;
    //     printf("%d n이 0이아니면 10의 약수\n",n);
    // }

    //7번
    // int n=0;
    // int n1=10;
    // int n2=20;
    // for (int i = 1; i <= n1; i++)
    // {
    //     n= (n1%i==0&&n2%i==0)?i:0;
    //     printf("n이 0이아니면 공약수 %d\n",n);
    // }
    
    //1번
    // int a[10];
    // for (int i = 0; i < 10; i++)
    // {
    //     a[i]=i+1;
    //     printf("%d\n",a[i]);
    // }
    
    //2번
    // int a[10];
    // for (int i = 0; i <10 ; i++)
    // {
    //     a[i]=(i+1)*10;
    //     printf("%d\n",a[i]);
    // }
    
    //3번
    // int a[10];
    // for (int i = 0; i <10 ; i++)
    // {
    //     a[i]=(i+1)*10;
    //     printf("%d\n",a[i]);
    // }
    // int j;
    // printf("\n");
    // for (int i = 0; i <5 ; i++)
    // {
    //     j=a[i];
        
    //     a[i]=a[9-i];
    //     a[9-i]=j;    
    // }
    // for (int i = 0; i < sizeof a/sizeof a[0]; i++)
    // {
    //     printf("%d\n",a[i]);
    // }
    
    //4번
    // int a[]={1,2,3,4,5,6,7,8,9};
    // int max=a[0];
    // for(int i=0; i<10; i++){
    //     max= max < a[i] ? a[i]:max;
    // }
    // printf("%d\n",max);
    
    //5번
    // int a[]={1,2,3,4,5,6,7,8,9};
    // int b[sizeof a/sizeof a[0]];
    // for (int i = 0; i < sizeof a/sizeof a[0]; i++)
    // {
    //     b[i]=a[sizeof a/sizeof a[0] - 1-i]; 
    //     printf("%d\n",b[i]);
    // }

    // 6번
    // int a[]={1,2,3,4,5,6,7,8,9};
    // int k=a[0];
    // for (int i = 0; i <sizeof a/sizeof a[0] -1 ; i++)
    // {
    //     a[i]=a[i+1];
    // }
    //   a[sizeof a/sizeof a[0]-1] =k;
    // for (int i = 0; i < sizeof a/sizeof a[0]; i++)
    // {
    //     printf("%d\n",a[i]);
    // }
   
    int a[10]={1,2,3,4,5,6,7,8,9};
    long b=1;
    reverse(a);
    int* p=&a[0];
    for(int i = 0;  i<sizeof a/sizeof a[0]-1;i++){
        printf("%d\n",a[i]); 
        }
    return 0;
}

void reverse(int* p)
{
    int k=p[0];
    for (int i = 0; i <sizeof p/sizeof p[0] -1 ; i++)
    {
        p[i]=p[i+1];\
    }
      p[sizeof p/sizeof p[0]-1] =k;
    
}
