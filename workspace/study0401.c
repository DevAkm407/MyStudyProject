// #include<stdio.h>
// #include<string.h>
// #include<stdbool.h>
// #define FUNDLEN 50
// #define N 2

// struct funds
// {
//     char bank[FUNDLEN];
//     double  bandkfund;
//     char save[FUNDLEN];
//     double savefund;
// };

// double sum(struct funds* money,int n);

// int main(void)
// {
//     struct funds jones[N]={
//         {"국민은행"
//         ,4032.27
//         ,"동아상호신용금고",
//         8543.94
//         },
//         {
//             "우리은행",
//             3620.88,
//             "대한상호신용금고",
//             3802.91
//         }
//     };
//     struct funds* s;
//     printf("jones 씨네 두 형제의 총 잔고는 $%.2f입니다.\n",sum(jones,N));
//     return 0;
// }

// double sum(struct funds* money,int n)
// {
//     double total;
//     int i;

//     for ( i = 0,total =0; i < n; i++){
//         money[i].bandkfund=money[i].bandkfund*1.05;
//         money[i].savefund=money[i].savefund*1.05;
//         total+=money[i].bandkfund+money[i].savefund;
//     }
//     return total;
// }
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
char* s_gets(char *st,int);
enum spectrum {red,orange,yellow,green,blue,violet};
const char* colors[]={"red","orange","yellow","green","blue","violet"};
#define LEN 30

int main(void)
{
    char choice[LEN];
    enum spectrum color;
    bool color_is_found =false;

    puts("컬러를 입력하시오(끝내려면 빈 라인):");
    while (s_gets(choice,LEN) !=NULL && choice[0] != '\0')
    {
        for (color = red; color <= violet; color++)
        {
            if(strcmp(choice,colors[color]) == 0 )
            {
                color_is_found= true;
                break;
            }
        }
        if(color_is_found){
            switch (color)
            {
            case red:
              puts("장미는 red.");        
                break;
            case orange:
              puts("양귀비는 orange.");        
                break;
            case yellow:
              puts("해바라기는 yellow.");        
                break;
            case green:
              puts("잔디는 green.");        
                break;
            case blue:
              puts("블루벨은 blue.");        
                break;
            case violet:
              puts("제비꽃은 violet.");        
                break;
            default:
                printf("%s컬러는 잘 모르겠습니다.\n",choice);
                break;
            }
        }
        color_is_found = false;
        puts("다음 컬러를 입력하시오(끝내려면 빈 라인):");    
}
puts("안녕!");
return 0;
}

char *s_gets(char* st,int n)
{
    char* ret_val;
    char* find;
    ret_val=fgets(st,n,stdin);
    if(ret_val){
        find =strchr(st,'\n');
        if(find)
            *find='\0';
        else
            while (getchar() != '\n')
            {
                continue;
            }    
    }
return ret_val;
}