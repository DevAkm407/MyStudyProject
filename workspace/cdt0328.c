#include<stdlib.h>
#include<stdio.h>
void MaxMin(int* max,int* min);
void MaxMaxMinMin(int** max, int** min);
void PointMax(int* a,int** max,int size);
void CalVag(int (*score)[3],int size,double* average);
int main()
{
//int ary[5] ={1,6,3,9,4};
//int* max=NULL;
//PointMax(ary,&max,5);
//MaxMin(max,min);
//MaxMaxMinMin(maxmax,minmin);
int score[5][3] ={{100,90,80},
{60,70,85},{76,79,70},{100,100,95},{85,80,90} };
double average[3];
CalVag(score,5,average);
printf("국어 평균 :%f\n",average[0]);
printf("수학 평균 :%f\n",average[1]);
printf("영어 평균 :%f\n",average[2]);
return 0;
}

void MaxMin(int* max,int* min)
{
    int a=*(max);
    *(max)=*(max) < *(min) ? *(min) : *(max);
    *(min)=a  < *(min) ? a : *(min);
}

void MaxMaxMinMin(int** max, int** min)
{
    int a=**(max);
    **(max)=**(max) < **(min) ? **(min) : **(max);
    **(min)=a  < **(min) ? a : **(min);
}

void PointMax(int* a,int** max,int size)
{
    *max=&a[0];
    for (int i = 0; i < size; i++)
    {
        **max = a[i] > **max ? a[i]: **max ;
    }  
}
void CalVag(int (*score)[3],int size,double* average)
{
    double sum0=0;
    double sum1=0;
    double sum2=0;
    for (int i = 0; i < size; i++)
    {
        sum0+=score[i][0];
        
        sum1+=score[i][1];
        
        sum2+=score[i][2];
    }
    average[0]=sum0/size;
    average[1]=sum1/size;
    average[2]=sum2/size;
}
/*
   1번. 8 8
        4 4
        0 0
        2 2
   
   2번. 4개
   
   3번. 배열의 0번지, +1번지, +1번지

   4번. a.12,16 b. 12 , 14

   5번. a.12,14 b.12 ,16

   6번. a.&grid[22][56] b.&grid[22][0],grid[22] c.&gird[0][0],grid,gird[0]
   
   7번. a.int digits[10]; b. float rates[6]; c. int mat[3][5]; d. char* psa[20]; e. char* pstr[20];

   8번.a.int E[1,2,4,8,16,32] b.E[2] c. int e[100]; e[99]=-1; d.int e[100]; e[5]=101; e[10]=101; e[11]=101; e[12]=101; e[3]=101;

   9번. 0~9까지

   10번. a.True     b.false     c.false     d.false     e.true      f.false     g.false     h.true     
*/