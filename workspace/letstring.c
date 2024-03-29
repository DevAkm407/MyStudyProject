// #include<stdio.h>
// #define MSG "I am symbolic string constant."
// #define MAXLENGTH 81

// int main(void)
// {
//     char words[MAXLENGTH] ="I am a string in an array.";
//     const char* pt1 ="Something is pointing at me.";
//     puts("Here are some stings:");
//     puts(MSG);
//     puts(words);
//     words[8] ='p';
//     puts(words);
//     return 0;
// }

// #include<stdio.h>
// #define SLEN 40
// #define LIM 5

// int main()
// {
// const char* mytalents [LIM] ={
//     "Adding numbers swiftly",
//     "Multiplying accurately",
//     "Stashing data",
//     "Understanding the C language"
// };

// char yourtalents[LIM][SLEN] = {
//     "Walking in a straight line",
//     "sleeping","Watching television",
//     "Maliling letters","Reading email"
// };

// puts("Let's compare talents.");
// printf("%-36s %-25s\n","My Talents","Your Talents");
// for (int i = 0; i < LIM; i++)
// {
//     printf("%-36s %-25s \n",mytalents[i],yourtalents[i]);
// }
// printf("\n sizeof mytalents: %zd, sizeof yourtalents:%zd\n",sizeof(mytalents),sizeof(yourtalents));


// return 0;
// }

// #include<stdio.h>

// int main(void)
// {
//     const char* mesg="섣불리 판단하지 말라!";
//     const char* copy;
//     copy=mesg;
//     printf("%s\n",copy);
//     printf("mesg =%s; &mesg = %p; 값 = %p\n",mesg,&mesg,mesg);
//     printf("copy = %s; &copy = %p; 값 = %p\n",copy,&copy,copy);
    
//     return 0;
//     }

// #include <stdio.h>
// #define STLEN 14
// int main()
// {
//     char words[STLEN];
//     puts("문자열을 입력하세요.");
//     fgets(words,STLEN,stdin);
//     printf("당신의 문자열 두 번 (ptus(), 그리고 나서 fputs()):\n");
//     puts(words);
//     fputs(words,stdout);
//     puts("다른 문자열을 입력하세요.");
//     fgets(words,STLEN,stdin);
//     printf("당신의 문자열 두 번 (ptus(), 그리고 나서 fputs()):\n");
//     puts(words);
//     fputs(words,stdout);
//         puts("Done.");
//     return 0;
// }
// #include <stdio.h>
// #define STLEN 10
// int main()
// {
//     char words[STLEN];
//     puts("문자열을 입력하세요 (탈출하려면 빈 행):");
//     while (fgets(words,STLEN,stdin) != NULL && words[0] !='\n')
//         fputs(words,stdout);
//     puts("종료.\n");
//     return 0;

// }
// #include <stdio.h>
// #define STLEN 10
// int main(void)
// {
//     char words[STLEN];
//     int i;

//     puts("문자열을 입력하세요 (탈출하려면 빈행):");
//     while (fgets(words,STLEN,stdin) != NULL && words[0] != '\n') //fgets로 받은게 아무것도 없거나 첫번째 값이 개행문자가 아니라면
//     {
//         i =0;
//         while (words[i] != '\n' && words[i] != '\0') //i번째가 개행이아니고 널문자가 아니라면
//             i++;
//         if (words[i] == '\n') //개행문자라면 널문자로 바꿔버리기
//             words[i] ='\0';
//         else
//             while (getchar() != '\n')//그다음문자가 개행문자가 아니라면 컨티뉴
//                 continue;
//         puts(words);//개행문자면 출력
            
//     }
//    puts("종료.\n");
//    return 0; 
// }

// #include <stdio.h>
// #define STLEN 10
// char* s_gets(char* st, int n);
// int main(void)
// {
//     char* st;
//     st=s_gets(st,10);
//     puts(st);
//     return 0; 
// }

// char* s_gets(char* st,int n)
// {
//     char* ret_val;
//     int i=0;

//     ret_val=fgets(st,n,stdin);
//     if(ret_val){
//         while (st[i] != '\n' && st[i] != '\0') //i번째가 개행이아니고 널문자가 아니라면
//             i++;
//         if (st[i] == '\n') //개행문자라면 널문자로 바꿔버리기
//             st[i] ='\0';
//         else
//             while (getchar() != '\n')//그다음문자가 개행문자가 아니라면 컨티뉴
//                 continue;          
//     }
//     return ret_val;
// }

#include <stdio.h>
int main()
{
    char side_a[]="Side A";
    char dont[]={'W','O','W','!'};
    char side_b[]="Side B";
    puts(dont);
    return 0;
}