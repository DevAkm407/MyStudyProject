//1번

// #include<stdio.h>

// int main()
// {
//     char ch;
//     int count=0;
//     int total=0;
//     int cha=0;
//     printf("문자입력:");
//     while((ch=getchar()) !='#')
//     {
//         switch (ch)
//         {
//         case  ' ':
//             count+=1;
//             break;
//         case '\n':
//             total+=1;
//             break;
//         default:
//             cha+=1;
//             break;
//         }
//     }
//     printf("공백 개수 %d 개행 개수 %d 문자 개수 %d \n",count, total,cha);
//     return 0;
// }

//2번

// #include <stdio.h>
// int main()
// {  
//     char ch;
//     int conut=0;
//     printf("문자입력:");
//     while ((ch=getchar()) != '#')
//     {
//         if(conut%8==0)
//             printf("\n");
//         if(ch==10||ch==32)
//             continue;
//         conut++;\
//         putchar(ch);
//         printf(" %d ",(int)ch);
//     }       
// return 0;
// }

//3번

// #include<stdio.h>
// int main()
// {
//     int intput;
//     int zcount=0;
//     int dcount=0;
//     int zaver=0;
//     int dever=0;
//     printf("정수입력:");
//  while (scanf("%d",&intput)!=0&&intput!=0){
//     if(intput % 2==0){
//         zcount++;
//         zaver+=intput;
//     }
//     else{
//         dcount++;
//         printf("%d",intput);
//         dever+=intput;}
//  }
//    printf("%d개의 짝수 평균%f %d개의 홀수 평균: %f \n",zcount,(float)zaver/zcount,dcount,(float)dever/dcount); 
        
    
    
//     return 0;
// }

//4번

// #include<stdio.h>

// int main()
// {
// char ch;
// int dotcount=0;
// int exccount=0; 
// printf("문자입력:");
// while((ch=getchar()) !='#')
// {
//     if(ch =='.'){
//         putchar('!');
//         dotcount++;
//     }
//     else if(ch=='!'){
//         putchar('!');
//         putchar('!');
//         exccount++;           
//                     }
//     else
//         putchar(ch);
// }
// printf("%d개의 점 %d개의 !\n",dotcount,exccount);
// return 0;}

//5번
// #include<stdio.h>

// int main()
// {
// char ch;
// int dotcount=0;
// int exccount=0; 
// printf("문자입력:");
// while((ch=getchar()) !='#')
// {
//     switch (ch)
//     {
//     case '.':
//         putchar('!');
//         dotcount++;
//         break;
//     case '!':
//         putchar('!');
//         putchar('!');
//         exccount++;
//         break;
//     default:
//         putchar(ch);
//         break;
//     }
//       return 0;
//     }      
                    
// printf("%d개의 점 %d개의 !\n",dotcount,exccount);      
// }

//6번
// #include<stdio.h>

// int main()
// {
// char ch;
// int count=0;
// while ((ch=getchar())!='#')
// {
//     switch (ch)
//     {
//     case 'e':
//         while (( ch=getchar() ) == 'e')
//         {
//         }
//         if( ch =='i')
//             count++;
//         break;
//     default:
//         break;
//     }
// }
// printf("%d번의 ei가 출력되었습니다.",count);
// return 0;
// }

//7번
// #include <stdio.h>
// #define PRIMER 10.00
// #define PLUS 1.5

// int main()
// {

// }