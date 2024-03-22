// #include <stdio.h>
// #define SIZE 4
// int main(void)
// {
//     short dates[SIZE];
//     short* pti;
//     short index;
//     double bills[SIZE];
//     double* ptf;

//     pti =dates;
//     ptf =bills;
//     printf("%23s %15s\n", "short", "double");
//     for ( index = 0; index < SIZE; index++)
//     {
//         printf("포인터 + %d: %10p %10p\n",index,pti+index,ptf+index);
//     }
//     return 0;
// }

// #include<stdio.h>
// #define MONTHS 12
// int main()
// {
//     int days[MONTHS] ={31,28,31,30,31,30,31,31,30,31,30,31};
//     int index;
//     for ( index = 0; index < MONTHS; index++)
//     {
//         printf("%2d월: 날짜 수 %2d\n",index+1,*(days+index));
//     }
//     return 0;
// }

// #include<stdio.h>
// #define SIZE 10
// int sum(int ar[],int n);
// int main()
// {
//     int marbles[SIZE] ={20,10,5,39,4,16,19,26,31,20};
//     long answer;
//     answer = sum(marbles,SIZE);
//     printf("구슬의 전체 개수는 %ld개입니다.\n",answer);
//     printf("marbles의 크기는 %zd바이트입니다.\n",sizeof marbles);
//     return 0;
// }

// int sum(int ar[],int n)
// {
//     int i;
//     int total=0;
//     for ( i = 0; i < n; i++)
//     {
//         total +=ar[i];
//     }
//     printf("ar의 크기는 %zd바이트입니다.\n",sizeof ar);
//     return total;
// }



// #include<stdio.h>
// #define SIZE 10
// int sump(int* start,int* end);
// int main(void)
// {
//     int marbles[SIZE]={20,10,5,39,4,16,19,26,31,20};
//     long answer;
    
//     answer=sump(marbles,marbles+SIZE); //marbles+SIZE 사실상 0번지+10
//     printf("구슬의 전체 개수는 %ld개입니다.\n",answer);
//     return 0;
// }

// int sump(int* start,int* end)
// {
//     int total =0;
//     while (start <end)
//     {
//         total+=*start; //인디렉션으로 값을 더해준다
//         start++;
//     }
//     return total;
// }


// #include<stdio.h>
// int data[2]={100,200};
// int moredata[2] ={300,400};
// int main(void)
// {
// int*p1,*p2,*p3;
// p1=p2=data;
// p3=moredata;
// printf(" *p1 = %d, *p2= %d, *p3 = %d\n",*p1,*p2,*p3);
// printf(" *p1++ = %d, *++p2= %d, (*p3)++ = %d\n",*p1++,*++p2,(*p3)++);
// printf(" *p1 = %d, *p2= %d, *p3 = %d\n",*p1,*p2,*p3);
// return 0;
// }

/*
p1=&data[0]
p2=&data[0]
p3=&moredata[0]

100, 100, 300

100, 200, 300

200, 200, 301

*/

//해당 배열의 길이를 반환하는 함수
//배열이 함수에 주소를 반환함
//해당 주소로 그 배열의 길이를 알수 있을까?
//void*로 받는다고 해도 알기가 힘들어 보이는대...
//배열의 인덱스가 끝나는 부분을 알수만 있으면 길이를 반환할 수 있다.
//사실 오류코드를 알아내서 하면 쉬울것 같긴하다...날먹이지만

// #include<stdio.h>
// int main(){
//     int a[1]={0,1};
//     for (int i = 0; i < 3; i++)
//     {
//         a[i]=2;
//         printf("%d\n",a[i]);
//     }
//     return 0;
//     }

/* *ptr1 = 100
   *ptr2 = 300
   *ptr3 = 500

   *ptr1=100
   *ptr1=200
   *ptr2=300
   *ptr2=200
   *ptr1=100
   *ptr2=300
*/

/*
    *ptr1 = 100
    *ptr2 = 300
    *ptr3 = 500

    *ptr1 = 500
    *ptr1 = 503
    *ptr1= 500
    *ptr1 = out of index
    *ptr2 = 300
    *ptr2 = 200
    *ptr1 = 500
    *ptr2 = 300
    ptr2-ptr1 = -2
    ptr3-2= 300 
*/

// #include<stdio.h>

// int main()
// {
//     int urn[5] ={100,200,300,400,500};
//     int *ptr1,*ptr2,*ptr3;

//     ptr1=urn;
    
//     ptr2=&urn[2];
    
//     printf("포인터의 값,역참조된 포인터가 가리키는 값,포인터의 주소:\n");
    
//     printf("ptr1 = %p, *ptr1 = %d, &ptr1= %p\n",ptr1,*ptr1,&ptr1);

//     ptr3 =ptr1 +4;
    
//     printf("\n포인터에 정수를 더한다.:\n");

//     printf("ptr1 +4 = %p, *(ptr4 + 3) = %d\n",ptr1 +4,*(ptr1 +3 ));

//     ptr1++;

//     printf("\nptr1++을 수행한 후의 값:\n");

//     printf("ptr1 = %p, *ptr2 = %d,&ptr2 = %p\n",ptr2,*ptr2, &ptr2); 
    
//     --ptr1;
//     ++ptr2;
    
//     printf("\n두 포인터를 최초의 값으로 복원하다.:\n");
    
//     printf("ptr3 = %p, ptr1 = %p, ptr2 - ptr1 =%td\n",ptr2,ptr1,ptr2 - ptr1);

//     printf("\n포인터에서 정수를 뺀다:\n");
    
//     printf("ptr3 = %p, ptr3 -2 = %p\n",ptr3,ptr3 -2);

//     return 0;
// }


// #include<stdio.h>

// int main(void)
// {
//     int x[5]={1,2,3,4,5};
    
//     const int* j=x;
    
//     printf("%d\n",*j);  //x의 0번째 
    
//     printf("%d\n",*(j+1)); //x의 1번째를 가져오는 것도 가능하다.
    
//     printf("%d\n",*(j+2)); // 2번쨰도 가능
    
//     printf("%d\n",*(j+3)); // 3번째도 가능
    
//     printf("%d\n",*(j+4));// 주소를 바꾸는 건 가능
    
//     return 0;
// }

/*zippo 0번지를 0이라고 하자
  zippo +1은 8번지
  zippo[0]+1 은 4번지
  *zippor +1 은 4번지
  zippo[0][0]은 0번지
  *zippo[0]은 0번지
  **zippo은 0번지
  zippo[2][1]은 20번지
  *(*(zippo+2) + 1)은 20번지
*/ 

// #include<stdio.h>

// int main(void)
// {
//     int zippo[4][2]= { {2,4}, {6,8} ,{1,3} ,{5, 7} };
//     int (*pz)[2];
//     pz= zippo;
//     printf("    pz =%p,     pz +1 =%p\n",pz,    pz+1);
//     printf("pz[0] = %p,     pz[0] + 1 =%p\n",pz[0],pz[0] +1);
//     printf(" *pz = %p,      *pz +1 =%p\n",*pz,*pz +1);
//     printf("pz[0][0] = %d\n",pz[0][0]);
//     printf("    *pz[0] = %d\n", *pz[0]);
//     printf("    **pz = %d\n", pz[2][1]);
//     printf("*(*(pz+2) +1 ) =%d\n",*(*(pz+2) +1 ));

//     return 0;

    
// }


/*
p -> num1

q -> num2

r -> num1
pp -> p ->num1

*pp -> q -> num2 => p-> num2 

**pp -> p -> num2-> 1024

pp -> r ->num1

**pp-> r -> 1024 *2 = 2048 

num1 = 2048
num2 = 1024 

*/

// #include<stdio.h>
// #define ROWS 3
// #define COLS 4
// void sum_rows(int ar[][COLS],int rows);
// void sum_cols(int [][COLS],int);
// int sum2d(int(*ar)[COLS],int rows);
// int main(void)
// {
//     int junk[ROWS][COLS] = {
//         {2,4,6,8},
//         {3,5,7,9},
//         {12,10,8,6}
//     };

//     sum_rows(junk,ROWS);
//     sum_cols(junk,ROWS);
//     printf("모든 원소들의 합계 =%d\n",sum2d(junk,ROWS) );

//     return 0;
// }



// void sum_rows(int ar[][COLS], int rows)
// {
//     int r;
//     int c;
//     int tot;

//     for(r=0; r<rows;r++)
//     {
//         tot = 0;
//         for ( c = 0; c < COLS; c++)
//             tot +=ar[r][c];
//         printf("%d행: 소계 =%d\n",r,tot);
//     }
// }



// void sum_cols(int ar[][COLS],int rows)
// {
//     int r;
//     int c;
//     int tot;
//     for ( c = 0; c < COLS; c++){
//         tot=0;
//     for ( r = 0 ; r < rows; r++)
//         {
//             tot+= ar[r][c];    
//         }
//     printf("%d열: 소계 = %d\n",c,tot);
//     }
// }



// int sum2d(int ar[][COLS],int rows)
// {
//     int r;
//     int c;
//     int tot =0;

//     for ( r = 0; r < rows; r++)
//     {
//         for ( c = 0; c < COLS; c++)
//         {
//             tot +=ar[r][c];
//         }
        
//     }
//     return tot; 
// }
