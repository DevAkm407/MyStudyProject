#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
int main(void)
{
    char userName;
    int random;
    float dra; //배수를 의미
    int random1;
    float dra1; //소수점을 의미
    unsigned int exp = 0;
    int gameCount=0;
    double expBar=30000.0;
    char input = 0;
    int lv=1;
    int death=0;
    int expindex[5];
    int ending=0;
    while (1)
    {
        gameCount++;
        srand(time(NULL));
        
        random = rand()%5+1;
        random1 = rand()%9;  //5이상일때 안나오게 4까지만 나오게
        dra=random;
        dra1=random1;
        float bonus = dra+dra1*0.1;
        if (bonus > 5.0)
        {
            bonus=5.0;
        }
       
        
        
        
        

        
        for (int i = 0; i<=4; i++)
        {
         //   sleep(1);
           // int choexp = rand()%7000-3500;
            int choexp = rand()%3500;
            int minusp= rand()%10;
            if(minusp==9) //마이너스 경험치가 나올확률 을 10%로 조정
                choexp=-1*choexp;
            
            expindex[i] = choexp;
            printf("%d\n", expindex[i]); //5번 반복했나?
        
        
        

                exp = exp+(choexp*bonus);
             //   srand(time(NULL));
          //  double randexp = (rand() %71) + 180;// ( 250 - 180 + 1 ) + 180; // 250-180= 70+1 = 71 +180 ) 0~70 + 180   1.8~2.5
            
            double plusexp = 15000;
            

            if ( exp < 0 ){
                lv--;
                expBar=expBar-plusexp;   
                if(lv<0){
                printf("훈련 중에 공룡이 경험치를 획득하지 못하고 사망했습니다.\n\n");
                printf("                 @@@@@                  \n");                
                printf("              @@       @\n");
                printf("                @@@@@@@                \n");
                printf("\t                                   [!Knock Down!] \n");
                printf("               @@@@@@@@\n");
                printf("             @@@@@@@@@@@@      \t[!Knock Down!]\n");
                printf("             @@@  @@@@@@@\n");
                printf("             @@@@@@@@\n");
                printf("             @@@@@@@@@@@       ┏━━━━━━━━━━━━━━━━┓\n");
                printf("     *      @@@@@@@@           ┃                ┃\n");
                printf("     @     @@@@@@@@@@@@@@      ┃ !!game  over!! ┃\n");
                printf("      @@  @@@@@@@@@@@   @      ┃                ┃\n");
                printf("         @@@@@@@@@@@@@         ┗━━━━━━━━━━━━━━━━┛\n");
                printf("          @@@@@@@@@@@           공룡이 획득한 총 경험치 : %d\n", exp);
                printf("          @@        @@          공룡이 생존했던 턴 수 : %d\n", gameCount);
                printf("         @@@@      @@@          당신은 나쁜 아버지였습니다.\n");
                death++;
                break;
                }
                
                }
            else if ( exp > expBar )
            { 
                lv += 1;
                //exp = exp - expBar;
                // plusexp = randexp  / 100.0;
                //printf("%f plusexp의값\n",plusexp);
                expBar = expBar + plusexp; //레벨업시 필요한 경험치량 수식이 틀렸었어서 고침
               
                printf("[Level up!]레벨 %d 가 되었습니다!\n",lv);
                
            }

            if (lv == 99 )
              {
                printf("[Level up!]\n레벨 %d 가 되었습니다!\n",lv);
                printf("\n               @@@@@@@@@@\n");
                printf("             @@@@@@@@@@@@@@    \t [!!Ending!!]\n");
                printf("             @@@  @@@@@@@@@\n");
                printf("             @@@@@@@@@@@@@@\n");
                printf("             @@@@@@@@@          ┏━━━━━━━━━━━━━━━━┓\n");
                printf("     *      @@@@@@@@@@@@        ┃                ┃\n");
                printf("     @     @@@@@@@@@            ┃ !!축하합니다!! ┃\n");
                printf("     @@  @@@@@@@@@@@@@@@@@      ┃                ┃\n");
                printf("     @@@@@@@@@@@@@@@@@   @      ┗━━━━━━━━━━━━━━━━┛\n");
                printf("     @@@@@@@@@@@@@@@@@\n");
                printf("      @@@@@@@@@@@@@@@@           공룡이 획득한 총 경험치 : %d\n", exp);
                printf("       @@@@@@@@@@@@@@            공룡이 진행한 총 훈련 횟수 : %d\n", gameCount);
                printf("         @@@@@@@@@@@             당신은 좋은 아버지였습니다.\n");
                printf("         @@      @@\n");
                printf("         @@@@    @@@@\n");
                
                exit(1);
                
            }
        
        
       
        if(death>0)
        exit(1);
    
    }
    
 
    
    
    int sum=0;
    int lvexp=(int)expBar-exp;    
    for (int i = 0; i < 5; i++)
    {
         sum+=expindex[i];
        printf("%d턴 경험치는 %d입니다.\n",i+1,expindex[i]);
    }
    
    printf("이벤트 경험치 배율은 %f 입니다.\n",bonus);
    
    if(lvexp<0)
        lvexp=-1*lvexp;
    printf("얻은 총경험치는 %d입니다.\n현재 레벨업시 필요한 경험치:%d\n  현재 레벨업 기준 경험치 %lf\n 현재 레벨은 %d입니다.\n",(int)(sum*bonus), lvexp,expBar,lv);
    
    sum=0;
    int sbrk=0;
    
    printf("다음 턴을 진행하시겠습니까? (Y/N)\n");
    while(1)
    {    
        input=getchar();
        switch (input)
        {
        case '\n':
                    printf("다음 턴을 진행하시겠습니까? (Y/N)\n");
                    printf("문자를 입력해주세요.\n");
                    break;
        
        case 'y':
        case 'Y': 
                sbrk++;
                while ((input=getchar())!='\n')
                    {      
                    }
                break;
        
        case 'n':
        case 'N': 
            ending++;
            while ((input=getchar()) !='\n'){}
            break;
        default:
            printf("y 또는 n 을 입력해주세요.\n");
            break;
        
        }
       if(sbrk>0)
            break; 
       if(ending>0)
            break;    
    }
    if(ending>0)
        break;
    }
    


 return 0;   
    
}
