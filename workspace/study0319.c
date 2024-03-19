// #include<stdio.h>

// int main(){
//     char ch;
//     while   ((ch= getchar() ) != '#')
//     {
//         putchar(ch);
//     }
    
//     return 0;
// }
// #include<stdio.h>
// int main(){
//     char ch;
//     while   ((ch= getchar() ) != EOF) //End Of File -1이라는 상수 ctrl + D
//     {
//         putchar(ch);
//     }
    
//     return 0;
// }

// #include<stdio.h>
// int main(){
//     int guess=1;
//     char response;
//     printf("1에서 100까지 범위에 있는 한 정수를 생각하시오.\n");
//     printf("내가 추측하지요. 내 추측이 맞으면 y로 응답하고 ,\n");
//     printf("내 추측이 틀리면 n으로 응답하시오.\n");
//     printf("당신이 생각한 수가 %d입니까?\n",guess);
//     while ((response=getchar())!='y')
//     {
//        if(response =='n')
//         printf("그러면 %d입니까?\n",++guess);
//        else
//         printf("미안하지만,y 또는 n으로만 응답해 주시오.\n");
//        while( getchar()!='\n')
//             continue;
//     }
//     printf("그것봐요, 내가 맞출 수 있다고 했잖아요!\n");
//     return 0;
// }


// #include<stdio.h>

// void display(char cr,int lines, int width);

// int main()
// {
//     int ch;
//     int rows,cols;
//     printf("문자 하나와 두 개의 정수를 입력하시오.\n");
//     while ((ch=getchar()) != '\n')
//     {
//         if(scanf("%d %d",&rows,&cols )!=2)
//             break;
//         display(ch,rows,cols);
//         while(getchar() != '\n')
//             continue;
//         printf("또 다른 문자와 두 개의 정수를 입력하시오.\n");
//         printf("끝내내려면 그냥 Enter 키를 누르시오.\n");
//     }
//     printf("안녕!\n");
//     return 0;
// }

// void display(char cr, int lines, int width)
// {
//     int row,col;

//     for(row = 1; row <= lines; row++)//row의 써진 값만큼 반복
//     {
//         for (col =1; col <= width; col++)
//             putchar(cr); //cols에 써진값만큼 cr이 만들어짐
//         putchar('\n');
//     }
// }

// #include<stdio.h>
// #include<stdbool.h>

// long get_long(void);
// bool bad_limits(long begin, long end, long low, long high);


// double sum_squares(long a, long b);
// int main()
// {
//     const long MIN = -10000000L;
//     const long MAX = +10000000L;
//     long start;
//     long stop;
//     double answer;

//     printf("이 프로그램은 어떤 범위에 있는 정수들의 제곱의 합을 계산한다.\n"
//     "범위에 시작값은 -10000000보다 작을 수 없다.\n"
//     "범위에 시작값은 +10000000보다 클 수 없다.\n"
//     "시작값과 마감값을 입력하시오.\n"
//     "(끝내려면 두 값으 모두 0으로 입력):\n 범위의 시작값:");

//     start = get_long();

//     printf("범위의 마감값: ");

//     stop=get_long();
    
//     while(start !=0 || stop !=0 )
//     {
//         if(bad_limits(start,stop,MIN,MAX))    
//             printf("범위를 다시 지정하시오.\n");
        
//         else
//         {
//             answer =sum_squares(start,stop);
            
//             printf("정수들의 제곱의 합");
            
//             printf("%ld에서 %ld까지의 범위에 있는 정수들의 제곱의 합은 %g입니다.\n",start,stop,answer);
//         }
//         printf("시작값과 마감값을 입력하시오.\n"
//                 "(끝내려면 두값을 모두 0으로 입력):\n");
        
//         printf("범위의 시작값: ");
        
//         start =get_long();
        
//         printf("범위의 마감값: ");
        
//         stop=get_long();
//     }
//     printf("종료!\n");
    
//     return 0;
// }

// long get_long(void){
//     //scanf로 입력받은 input을 반환함
//     long input;
//     char ch;
//     while(scanf("%ld",&input)!=1)
//     {
//         while((ch=getchar()) !='\n' )
//             putchar(ch);
//         printf(": 정수가 아닙니다.\n25, -179 ,3과 같은");
//         printf("정수값을 입력하시오: ");
//     }
//     return input;
// }

// double sum_squares(long a, long b)
// {
//     // a부터 b까지의 제곱들의 합을 구하는 그거
//     double total = 0;
//     long i;
//     for ( i = a; i < b; i++)
//     {
//         total += (double)i *(double)i;
//     }
//     return total;
    
// }

// bool bad_limits(long begin, long end, long low, long high)
// {
//     //시작값과 마감감의 범위조정
    
//     bool not_good =false;

//     if(begin >end)
//     {
//         printf("시작값은 마감값보다 크면 안 됩니다.\n");
//         not_good =true;
//     }
//     if(begin <low || end < low)
//     {
//         printf("시작값과 마감값은 %ld보다 크거나 같아야 합니다.\n",low);
//         not_good =true;
//     }
//     if (begin >high ||end>high)
//     {
//         printf("시작값과 마감값은 %ld보다 작거나 같아야 합니다.\n",high);
//         not_good =true;
//     }
    
//     return not_good;
// }

// #include<stdio.h>

// char get_choice(void);
// char get_first(void);
// int get_int(void);
// void count(void);

// int main()
// {
//     int choice;
//     void count(void);

//     while ((choice = get_choice()) !='q')
//     {
//         switch (choice)
//         {
//         case 'a' : printf("쌀 때 사서 비쌀 때 파시오.\n");
//                      break;
//         case 'b' :putchar('\a');
//                     break;
//         case 'c': count();
//                     break;
//         default:
//             printf("프로그램 에러!\n");
//             break;
//         }
//     }
//     printf("안녕!\n");
//     return 0;
// }

// void count(void)
// {
//     int n,i;
//     printf("몇까지 카운트할까요? 정수 하나를 입력하시오:\n");
//     n = get_int();
//     for ( i = 0; i < n; i++)
//     {
//        printf("%d\n",i);
//     }
//     while (getchar()!= '\n')
//     {
//         continue;
//     }
// }

// char get_choice(void)
// {
//     int ch;
//     printf("a,b,c,q 중에서 하나를 선택하시오:\n");
//     printf("a.조언      b.경고\n");
//     printf("c.카운트    q.종료\n");
//     ch=get_first();
//     while ((ch<'a' ||ch>'c') && ch!='q')
//     {
//         printf("a,b,c,q 중에서 하나를 선택해야 합니다.\n");
//         ch = get_first();

//     }
//     return ch;    
// }

// char get_first(void)
// {
//     int ch;
//     ch=getchar();
//     while (getchar() !='\n')
//     {
//         continue;
//     }
//     return ch;
// }

// int get_int(void)
// {
//     int input;
//     char ch;
//     while (scanf("%d",&input) != 1)
//     {
//         while ((ch=getchar())!='\n')
//         {
//             putchar(ch);
//         }
//         printf(":정수가 아닙니다.\n25,-178,3과 같은 ");
//         printf("정수값을 입력하시오: ");

//     }
//     return input;
// }

