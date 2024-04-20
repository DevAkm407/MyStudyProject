// #include <stdio.h>

// void SimpleAdder(int n1,int n2)
// {
//     printf("%d + %d = %d \n",n1,n2,n1+n2);
// }

// void ShowString(char * str)
// {
//     printf("%s \n",str);
// }

// int main(void)
// {
//     char * str= "Function Pointer";
//     int num1=10,num2=20;

//     void (*fptr1)(int,int) =SimpleAdder;
//     void (*fptr2)(char *) = ShowString;

//     fptr1(num1,num2);
//     fptr2(str);

//     return 0;
// }

// #include <stdio.h>

// int WhoIsFirst(int age1, int age2, int(*cmp)(int n1, int n2))
// {
//     return cmp(age1,age2);
// }

// int OlderFirst(int age1, int age2)
// {
//     if(age1>age2)
//         return age1;
//     else if (age1<age2)
//         return age2;
//     else
//         return 0;
// }

// int YoungerFirst(int age1,int age2)
// {
//     if(age1<age2)
//         return age1;
//     else if (age1>age2)
//         return age2;
//     else
//         return 0;}

// int main(void)
// {
//     int age1=20;
//     int age2=30;
//     int first;
//     printf("입장순서 1\n");
//     first=WhoIsFirst(age1,age2,OlderFirst);
//     printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n",age1,age2,first);

//     printf("입장순서 2\n");
//     first=WhoIsFirst(age1,age2,YoungerFirst);
//     printf("%d세와 %d세 중 %d세가 먼저 입장! \n\n",age1,age2,first);

//     return 0;
// }
#include <stdio.h>
#include<string.h>
#include<ctype.h>
#define LEN 81
char* s_gets(char* st, int n);
char showmenu(void);
void eatline(void);
void show(void(*fp)(char *),char* str);
void ToUpper(char*);
void ToLower(char *);
void Transpose(char*);
void Dummy(char*);
int main()
{
    char line[LEN];
    char copy[LEN];
    char choice;
    void (*pfun)(char*);
    puts("문자열을 입력하시오(끝내려면 빈 라인): ");
    while (fgets(line,LEN,stdin) !=NULL && line[0] != '\0')
    {
        while ((choice = showmenu()) !='n')
        {
            switch (choice)
            {
            case 'u': pfun =ToUpper; break;
            case 'l': pfun= ToLower;break;
            case 't': pfun = Transpose; break;
            case 'o': pfun = Dummy;break;
            }
            strcpy(copy,line);
            show(pfun,copy);
        }
        puts("문자열을 입력사시오(끝내려면 빈 라인): ");
    }
    puts("안녕!");
    return 0;
}

char showmenu(void)
{
    char ans;
    puts("메뉴에서 원하는 작업을 선택하시오:");
    puts("u)대문자로 변환 l)소문자로 변환");
    puts("t)대소문자로 교차 변환 o)원본을 그대로");
    puts("n) 다음 문자열");
    ans=getchar();
    ans=tolower(ans);
    eatline();
    while (strchr("ulton",ans)==NULL)
    {
        puts("u,l,t,o,n 중에서 어느 하나를 선택하시오:");
        ans =tolower(getchar());
        eatline();
    }
    return ans;
}
void eatline(void)
{
    while (getchar()!='\n')
        continue;
}

void ToUpper(char * str)
{
    while (*str)
    {
        *str =toupper(*str);
        str++;
    }
}

void ToLower(char *str)
{
    while (*str)
    {
       *str =tolower(*str);
       str++;
    } 
}

void Transpose(char * str)
{
    while (*str)
    {
        if(islower(*str))
            *str = toupper(*str);
        else if (isupper(*str))
            *str =tolower(*str);
        str++;
    }
}

void Dummy(char * str)
{

}

void show(void(*fp)(char *),char*str)
{
    (*fp)(str);
    puts(str);
}

char*s_gets(char*st,int n)
{
    char*ret_val;
    char* find;

    ret_val=fgets(st,n,stdin);
    if(ret_val)
    {
        find = strchr(st,'\n');
        if(find)
            *find='\0';
        else
            while (getchar() !='\n')
                continue;
            
    }
    return ret_val;
}