// #include<stdio.h>


// void SimpleFunc(void)
// {
//     static int num1=0;
//     int num2=0;
//     num1++,num2++;
//     printf("static: %d, local: %d \n",num1,num2);
// }

// int main(void)
// {
//     int i;
//     for ( i = 0; i < 3; i++)
//     {
//         SimpleFunc();
//     }
    
//     return 0;
// }

// #include<stdio.h>
// #include<stdlib.h>

// int main(void)
// {
//     int *ptr1 =(int *)malloc(sizeof(int));
//     int *ptr2 =(int*)malloc(sizeof(int)*7);
//     int i;
//     *ptr1 = 20;
//     for ( i = 0; i < 7; i++)
//        ptr2[i]=i+1;
//     printf("%d \n",*ptr1);
//     for(i=0; i<7; i++)
//         printf("%d ",ptr2[i]);
//     free(ptr1);
//     free(ptr2);
//     return 0;
// }

// #include<stdio.h>
// #include<stdlib.h>

// char* ReadUserName(void)
// {
//     char *name=(char*)malloc(sizeof(char)*30);
//     printf("Whtat's your name?: ");
//     fgets(name,30,stdin);
//     return name;
// }

// int main()
// {
//     char *name1;
//     char *name2;
//     name1=ReadUserName();
//     printf("name1 %s \n", name1);
//     name2=ReadUserName();
//     printf("name2 %s \n", name2);

//     printf("again name1 %s \n", name1);
//     printf("again name2 %s \n", name2);
//     free(name1);
//     free(name2);
//     return 0;
// }

// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// char* ReadUserName(int len)
// {
//     char ch[len];
//     printf("단어를 입력해주세요:");

//     fgets(ch,len,stdin);
//     char *name=(char*)malloc(sizeof(char)*(len));
//     char ch1[len];
//     int count=0;
//     int index=0;
//     char (*ptr)[3];
//     for (int i = 0; i < len; i++)
//     {
//         ch1[i]=' ';
//     }

    
//     name[len-1]='\0';
//     ch1[len-1]='\0';
//     printf("%s\n",ch1);
//     return name;
// }
// int main(){
// printf("길이를 입력해주세요.");
// int a;
// scanf("%d",&a);
// while(getchar() !='\n')
//     continue;
// char* name1=ReadUserName(a);
// printf("%s\n",name1);
// free(name1);
// return 0;
// }
// #include<stdio.h>
// #include<stdlib.h>

// int main()
// {
//     int *pi;
//     int i,sum=0;

//     pi=(int*)malloc(5*sizeof(int));

//     if(pi==NULL)
//     {
//         printf("메모리가 부족합니다.\n");
//         exit(1);
//     }
//     printf("다섯 명의 나이를 입력하세요:");
//     for ( i = 0; i < 5; i++)
//     {
//         scanf("%d",&pi[i]);
//         sum += pi[i];
//     }
//     printf("다섯 명의 평균 나이:%.1f\n",(sum/5.0));
//     free(pi);
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>

// void InputScores(int* base,int asize); //asize 명의 성적을 입력받는 함수
// void ViewScores(int* base,int asize); //asize 명의 성적을 출력하는 함수
// int InputScore(int num); //num 번의 학생 성적을 입력받는 함수

// int main()
// {
//     int* base = NULL;  //동적으로 할당받아 학생들의 성적을 관리할 메모리의 시작 주소
//     int max_stu= 0;   //관리할 학생 수
//     printf("최대 관리할 학생 수를 입력하세요.\n");
//     scanf("%d",&max_stu);
//     base = (int*)malloc(sizeof(int) * max_stu); //성적을 보관할 메모리를 할당
//     InputScores(base,max_stu); //학생들의 성적 입력 요청
//     ViewScores(base,max_stu); //학생들의 성적 출력
//     free(base); //동적으로 할당한 메모리 해제
//     return 0;
// }

// void InputScores(int* base,int asize)
// {
//     for (int i = 0; i <  asize; i++)
//     {
//         printf("성적 입력:");
//         scanf("%d",&base[i]);
//     }
// }

// void ViewScores(int* base,int asize)
// {
//     for (int i = 0; i < asize; i++)
//     {
//        printf("%d번 성적:%d\n",i+1,base[i]);
//     }
    
// }

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *pi;
    int size=5;
    int cnt =0;
    int i;
    int num;
    pi =(int*)calloc(size,sizeof(int));
    while(1)
    {
        printf("양수를 입력하세요 => ");
        scanf("%d",&num);
        if(num <= 0) break;
        if(cnt < size)
        {
            pi[cnt++]=num;
        }
        else{
            size +=5;
            pi=(int*)realloc(pi,size*sizeof(int));
            pi[cnt++]=num;
        }
    }
    for ( i = 0; i < cnt; i++)
    {
       printf("%5d",pi[i]);
    }
    free(pi);

    return 0;
}