// #include<stdio.h>
// #define PERIOD '.'

// int main(){
//     int ch;
//     int charcount = 0;

//     while((ch = getchar()) != PERIOD) // ch의 값이 . 이아니면 참 enter누르면 \n이 들어가기 때문에 그 개수도 포함됌
//     {
//         if(ch !='"' && ch != '\''); // ch가 "가 아니고 ch가 \' 아니면 참
//             charcount++;
//     }
//     printf("따옴표는 빼고, 문자 %d개가 들어 있습니다.\n",charcount);
 
//     return 0;
// }

// #include <stdio.h>
// #include <ctype.h>
// #include <stdbool.h>
// #define STOP '|'
// int main()
// {
//     char c;         //현재 읽은 문자
//     char prev;      //바로 전에 읽은 문자
//     long n_chars =0L;   //문자 수
//     int n_lines=0;      //라인 수
//     int n_words=0;      //단어 수
//     int p_lines=0;      //불완전 라인 수
//     bool inword=false;  // c가 여전히 한 단어 안에 속해 있으면 true

//     printf("분석할 영문 텍스트를 입력하시오(끝내려면 |):\n");
    
//     prev ='\n';
    
//     //n_chars는 화이트스페이스를 포함한 모든 입력을 말한다.
//     //n_words는 화스트 스페이스가 들어와서 inword를 false가되고 그다음 문자가 오면 공백도아니고 true도아니여서 +가된다. 이러한 로직으로 단어수를센다.
//     //prev는 c의 마지막 단어를 저장한다.따라서 마지막엔 \n을 가지고있는다.
//     while ((c= getchar()) != STOP)
//     {
//         n_chars++;
//         if(c =='\n')
//             n_lines++;
//         if(!isspace(c) && ! inword) //isspace()함수는 전달인자가 화이트스페이스 문자이면 참을 리턴한다.
//         {
//             inword = true;
//             n_words++;

//         }
//         if (isspace(c) && inword)
//             inword = false;
    
//         prev =c;
//     }
    
//     if(prev !='\n')
//         p_lines=1;
    
//     printf("문자 수 =%ld,단어 수 =%d,라인 수= %d, ",n_chars,n_words,n_lines);
//     printf("불완전 라인 수 =%d\n",p_lines);

// }


//  조건 ? 참 : 거짓
// #include<stdio.h>
// #define COVERAGE 350

// int main()
// {
//     int sq_feet;
//     int cans;

//     printf("페인트로 칠할 면적을 평방피트 단위로 입력하시오:\n");
//     while (scanf("%d",&sq_feet) == 1)
//     {
//         cans = sq_feet /COVERAGE;
//         cans +=(sq_feet % COVERAGE ==0 ) ? 0 : 1;
//         printf("페인트 %d통(%s)을 구입해야 한다.\n",cans, cans ==1 ? "can":"cans");
//         printf("다음 값을 입력하시오(끝내려면 q):\n");
//     }
//     return 0;   
// }

//coutinue 

// #include <stdio.h>
// int main()
// {
// const float MIN =0.0f;
// const float MAX = 100.0f;

// float score;
// float total =0.0f;
// int n =0;
// float min =MAX;
// float max =MIN;

// printf("첫 번쨰 스코어를 입력시오(끝내려면 q): ");
// while (scanf("%f",&score) ==1)
// {
//     if(score < MIN || score > MAX) //-가 들어가면 실행
//     {
//         printf("%0.1f: 유효한 값이 아닙니다. 다시 입력하시오: ",score);
//         continue;
//     }
//     printf("%0.1f: 유효한 값입니다.\n",score);
//     min = (score < min) ? score: min;  //참이면 min가 score 거짓이면 이전값 유지
//     max = (score > max) ? score: max;  //참이면 max가 score 거짓이면 이전값 유지 
//     total += score;                    //입력된 모든값을 더해줌
//     n++;                               //count업
//     printf("다음 스코어를 입력하시오(끝내려면 q): ");//시작이 scanf니까 텍스트 띄어주기                                                                    
// }
//     if( n > 0 )
//     {
//         printf("스코어 %d개의 평균은 %0.1f입니다.\n",n,total / n);//n으로 센 카운트 출력 평균은 모든 값의 총합/모든 값의 개수
//         printf("최저 = %0.1f, 최고 = %0.1f\n",min,max); 
//     }
//     else
//         printf("유효한 값을 전혀 입력하지 않았습니다.\n");
//     return 0;
// }

//break

// #include<stdio.h>
// int main()
// {
//     float length,width;
//     printf("사각형의 길이를 입력하시오:\n");
//     while(scanf("%f",&length)==1) //길이를 받는 걸로 시작 숫자가 아니면 scanf가 0을 반환함
//     {
//         printf("길이 = %0.2f:\n",length); //length의 값을 소수점 2자리까지만 표현
//         printf("너비를 입력하시오:\n"); 
//         if(scanf("%f",&width) != 1) // 숫자가아니면 while 문 break
//             break;
//         printf("너비 = %0.2f:\n",width);    
//         printf("넓이 =%0.2f:\n",length*width); //넓이 구하는 공식 가로*세로
//         printf("사각형의 길이를 입력하시오:\n");
//     }
//     printf("종료!\n");

//     return 0;
// }

//swich case 문

// #include <stdio.h>
// #include<ctype.h>
// int main()
// {
//     char ch;
//     printf("알파벳 글자를 입력하시오. ");
//     printf("그러면 내가\n그 글자로 시작하는 동물 이름을 하나 대겠습니다.\n");
//     printf("글자를 하나 입력하시오(끝내려면 #):\n");
//     while ((ch = getchar()) != '#')
//     {
//         if('\n' == ch)
//             continue;
//         if(islower(ch))
//             switch (ch)
//             {
//             case 'a':
//                 printf("argali,아시아의 야생 양\n");
//                 break;
//             case 'b':
//                 printf("babirusa,말레이 반도의 야생 돼지\n");
//                 break;
//             case 'c':
//                 printf("coati,미국너구리\n");
//                 break;
//             case 'd':
//                 printf("desman,물에 사는 두더지 비슷한 동물\n");
//                 break;
//             case 'e':
//                 printf("echidna,바늘두더지\n");
//                 break;
//                 case 'f':
//                     printf("fisher, 갈색을 띤 담비\n");
//                 break;
//             default:
//                     printf("에이,너무 어렵다\n");
//                 break;
//             }
//     else
//         printf("나는 소문자만 알아듣는다.\n"); //입력을받았지만 소문자가 아니면 실행
//     while (getchar() !='\n')
//         continue;
//     printf("다른 글자를 하나 입력하시오(끝내려면 #):\n");
//     }
//     printf("안녕!\n");

//     return 0;
    
    
// }

//다수의 레이블 switch case

// #include<stdio.h>
// int main(){
//     char ch;
//     int a_ct,e_ct,i_ct,o_ct,u_ct;

//     a_ct=e_ct=i_ct=o_ct=u_ct=0;
//     printf("간단한 영문 텍스트를 입력하시오(끝내려면 #):\n");
//     while ((ch = getchar()) != '#')
//     {
//         switch (ch)
//         {
//         case 'a':
//         case 'A': a_ct++;              
//                   break;
//         case 'e':
//         case 'E':e_ct++;
//                  break;
//         case 'i':
//         case 'I':i_ct++;
//                  break;
//         case 'o':
//         case 'O':o_ct++;
//                  break;
//         case 'u':
//         case 'U':u_ct++;
//                  break;
//         default:
//             break;
//         }
//     }
//     printf("모음의 수   A   E   I   O   U\n");
//     printf("          %4d %4d %4d %4d\n",a_ct,e_ct,i_ct,u_ct);
//     return 0;
// }

/*
    1.다음 중 어느 표현식이 true이고, 어느 표현식이 false인지 결정하라.
    a. 100 >3 && 'a' > 'c' false 이유는 a가 c보다 정수형태에서 작은 숫자이다.
    b. 100 > 3 || 'a' > 'c' true 이유는 100 > 3이 true이기 때문에 (오른쪽 식은 고려하지않는다.)
    c.!(100 > 3 ) false 이유는 안쪽에 수식이 참이고 그걸 부정하는 !연산자가 있기 때문이다.

    2.다음과 같은 조건을 각각 나타내는 표현식을 작성하라.
    a. number는 90보다 크거나 같지만 100보다는 작다. number >= 90 && number < 100
    b. ch는 문자 q도 아니고 문자 k도 아니다.    ch !='q' && ch != 'k'
    c. number는 1부터 9까지의 범위에 있지만 5는 아니다. number >=1 && number <= 9 && number != 5
    d. number는 1과 9까지의 범위에 있지 않다. number < 1 && number > 9
    
    3.다음 프로그램은 불필요하게 복잡한 관계 표현식을 사용하고 있으며, 몇 가지 명백한 에러를 가지고 있다.
      프로그램을 간결하게 고치고 에러도 수정하라.

      #include<stdio.h>
      int main()
      {
        int weight,height; //weight는 파운드, height는 인치
        scanf("%d",&weight);  //&주소 연산자 수정, 한번에 두번 입력받는것을 수정(편의성)
        scanf("%d",&height);

        if(weight < 100 && height > 64) //무게가 100보다 작고 높이가 64보다 크다
            if(height >= 72) //높이가 72보다 크거나같다
                printf("몸무게에 비해 키가 너무 크네요.\n");
            else if (height <72 ) //높이가 72보다 작고 64보다 크다 수정 사항 : 이미 위에 if문에서 64보다 큰 값이 들어오기때문에
                printf("몸무게에 비해 키가 조금 크네요.\n");                //64보다 큰지 볼 필요가 없음
        else if (weight > 300 &&  height < 48 ) // 무게가 300보다 크고 300보다 작거나 같지않고 길이가 48보다 작으면 수정사항 무게가 300보다 크다는 말이 300보다 작거나 같지않다는 뜻 필요없은 조건은 제거 
                // height는 이미 48보다 작아서 48보다 작은지 구별할필요가 없다.
                printf("몸무게에 비해 키가 아주 작네요.\n");
        else
            printf("이상적인 몸무게입니다.\n");
        
        return 0;
      }

    4.다음과 같은 표현식들의 값은 각각 얼마인가?
    a. 5 > 2                답:true
    b. 3 + 4 > 2 && 3 < 2   답:false
    c. x >= y || y > x      답:True
    d. d = 5 + ( 6 > 2 )    답:6 
    e. 'X' > 'T' ? 10: 5    답:10
    f. x > y ? y > x : x>y  답:false

    5.다음 프로그램은 무엇을 출력하는가?
    #include <stdio.h>
    {
        int num;
        for(num1;num<=11;num++)
        {
            if(num%3==0)
                puchar('$');
            else
                putchar('*');
            putchar('#');
            putchar('%');        
        }
        putchar('\n');
        return 0;
    }
정답:*#%*#%$#%*#%*#%$#%*#%*#%$#%*#%*#%

    6.다음 프로그램은 무엇을 출력하는가?
    #include<stdio.h>
    int main()
    {
        int i=0;
        while(i < 3){
            switch(i++){
                case 0 : printf("fat");
                case 1 : printf("hat");
                default:printf("oh no!");

            }
            putchar('\n');        
        }
        return 0;
    }
정답:fat
     hat
     on no!

7.다음 프로그램은 무엇이 잘못되었을까?
#include<stdio.h>
int main()
{
    char ch;
    int lc =0;
    int uc =0;
    int oc =0;

    while((ch=getchar()) != '#' )
    {
        if('a' <= ch >='z') //&&를 쓰고싶어 하는듯?
            lc++;
        else if(!( ch < 'A' ) || !(ch > 'Z'))  //A보다 크거나 같거나 Z보다 작거나 같다.이지만 어차피 'A'보다 크면 'Z'보다 작다.
                                                A 보다 작은대 Z보다 작다는것은 결국 모든범위를 말하는 것이다. 조건문의 의미를 잃는다.
    }
}
8.다음 프로그램은 무엇을 출력하는가?.
#include<stdio.h>
int main()
{
    int age =20;

    while(age++ <= 65)
    {
        if( (age %20) ==0 )
            printf("%d세입니다.승진할 나이입니다.\n",age);
        if(age==65)
            printf("%d세입니다. 퇴직할 나이입니다.\n",age);

    }
    return 0;
}
정답 20세입니다.승진할 나이입니다.
40세입니다.승진할 나이입니다.
60세입니다.승진할 나이입니다. 
65세입니다 퇴직할 나이입니다.
*/

