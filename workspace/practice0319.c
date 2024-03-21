// #include<stdio.h>

// void vendingMachine(void);
// int donneretgi(void);
// int sum_menu(int monney);


// int main()
// {
//     vendingMachine();
//     return 0;
// }


// void vendingMachine(void)
// {
// int monney=donneretgi();
// printf("1)콜라 1200\n2)우주맛 콜라 1900\n3)제로콜라 1200\n"
// "4)스프라이트 1100\n5)환타 900\n6)닥터페퍼 1100\n7)몬스터 1800\n"
// "8)파워에이드 1900\n9)네스티 1600\n10)글라소 비타민 워터 2100\n11)미닛메이드 1700\n12)조지아 커피 900\n"
// "13)암바사 900\n14)마테차 1700\nS)계산하기\nX)종료하기\n");
// int order=sum_menu(monney);
// if(order!=0)
//     printf("남은돈 %d입니다.",order);
// }

// int donneretgi(void)
// {
//     int alpha;
//     printf("돈을 넣어 주세요 >");
//     scanf("%d",&alpha);
//     if(alpha<900)
//         printf("돈이 부족합니다.");
//     return alpha;
// }

// int sum_menu(int monney)
// {
//  int cash=monney;
//  int sum=0;
//  int choice;
//  int count=0;
//  char ch;
//  while (count==0)
//  {
//  printf("원하는 음료를 선택 하세요 >");
//  if(scanf("%d",&choice)==0){
//     while((ch=getchar()) !='\n')
//         choice=(int)ch;
//  }
//  switch (choice)
//  {
//  case 1:
//     sum +=1200;
//     break;
//  case 2:
//     sum +=1900;
//     break;
//  case 3:
//     sum +=1200;
//     break;
//  case 4:
//     sum +=1100;
//     break;
//  case 5:
//     sum +=900;
//     break;
//  case 6:
//     sum +=1100;
//     break;
//  case 7:
//     sum +=1800;
//     break;
//  case 8:
//     sum +=1900;
//     break;
//  case 9:
//     sum +=1600;
//     break;
//  case 10:
//     sum +=2100;
//     break;
// case 11:
//     sum +=1700;
//     break;
// case 12:
//     sum +=900;
//     break;    
// case 13:
//     sum +=900;
//     break;
// case 14:
//     sum +=1700;
//     break;
// case 83:
//     monney=monney-sum;
//     if(monney<0){
//        printf("돈이 부족합니다. 다시 고르세요.\n");
//        sum=0;
//        monney=cash;
//        break;
//     }
//     count++;
//     break;
// case 88:
//         count++;
// default: 
//     printf("잘못된 입력입니다.\n");
//     break;
//  }
//  }
// return monney;
// }


#include<stdio.h>

void vendingMachine(void);
int donneretgi(void);
int sum_menu(int monney);


int main()
{
    vendingMachine();
    return 0;
}


void vendingMachine(void)
{
int monney=donneretgi();
printf("1)콜라 1200\n2)우주맛 콜라 1900\n3)제로콜라 1200\n"
"4)스프라이트 1100\n5)환타 900\n6)닥터페퍼 1100\n7)몬스터 1800\n"
"8)파워에이드 1900\n9)네스티 1600\n10)글라소 비타민 워터 2100\n11)미닛메이드 1700\n12)조지아 커피 900\n"
"13)암바사 900\n14)마테차 1700\nS)계산하기\nX)종료하기\n");
int order=sum_menu(monney);
if(order!=0)
    printf("남은돈 %d입니다.",order);
}

int donneretgi(void)
{
    int alpha;
    printf("돈을 넣어 주세요 >");
    scanf("%d",&alpha);
    getchar();
    if(alpha<900)
        printf("돈이 부족합니다.");
    return alpha;
}

int sum_menu(int monney)
{
 int cash=monney;
 int sum=0;
 char choice;
 int count=0;
 while (count==0)
 {
    printf("원하는 음료를 선택 하세요 >\n");
 switch (choice=getchar())
 {
    case'1':
        switch (choice=getchar())
        {
            case'\n':
                sum +=1200;
                break;
            case '0':
                sum +=2100;     
                break;
            case '1':
                sum +=1700;    
                break;
            case '2':
                sum +=900;    
                break;
            case '3':
                sum +=900;    
                break;
            case '4':
                sum +=1700;    
                break;
            default:
                break;
        }
        break;
    case'2':
        sum +=1900;
        break;
    case'3':
        sum +=1200;
        break;
    case'4':
        sum +=1100;
        break;
    case'5':
        sum +=900;
        break;
    case'6':
        sum +=1100;
        break;
    case'7':
        sum +=1800;
        break;
    case'8':
        sum +=1900;
        break;
    case'9':
        sum +=1600;
        break;
    case'S':
        monney=monney-sum;
        if(monney<0){
        printf("돈이 부족합니다. 다시 고르세요.\n");
        sum=0;
        monney=cash;
        break;
        }
        count++;
        break;
    case'X':
            count++;
    case'\n':
        
        break;
    default: 
        printf("잘못된 입력입니다.\n");
        break;
 }
    if(choice!='\n')
        choice=getchar();
        
 }
return monney;
}