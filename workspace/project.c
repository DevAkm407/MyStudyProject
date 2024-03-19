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
            double randexp = (rand() % 71) + 180;// ( 250 - 180 + 1 ) + 180; // 250-180= 70+1 = 71 +180 ) 0~70 + 180   1.8~2.5
            double plusexp = 0;
            

            if ( exp < 0 ){
                lv--;
                expBar=expBar/randexp;   
                if(lv<0){
                    printf("마이너스래~언니 드러와 ~~~~\n");
                printf("%dlv로 사망하셨습니다.\n",lv);
                death++;
                break;
                }
                
                }
            else if ( exp > expBar )
            { 
                lv += 1;
                //exp = exp - expBar;

                plusexp = randexp  / 100.0;
                printf("%f plusexp의값\n",plusexp);
                expBar = expBar * plusexp; //레벨업시 필요한 경험치량 수식이 틀렸었어서 고침
               
                printf("[Level up!]레벨 %d 가 되었습니다!\n",lv);
                
            }

            if (lv == 99 )
                printf("만랩됐어! 언니 드러와");  
        
        
        
    }
    if(death>0){
        break;
    }
    
    int sum=0;
    
    for (int i = 0; i < 5; i++)
    {
         sum+=expindex[i];
        printf("%d턴 경험치는 %d입니다.\n",i+1,expindex[i]);
    }
    
    printf("이벤트 경험치 배율은 %f 입니다.\n",bonus);
    
    printf("얻은 총경험치는 %d입니다.\n현재 레벨업시 필요한 경험치:%d\n 현재 레벨은 %d입니다.",(int)(sum*bonus), (int)expBar-exp,lv);
    
    sum=0;
    
    
    printf("다음 턴을 진행하시겠습니까? (Y/N)\n");
    
    scanf("%c", &input);  
        
    if(input=='n'||input=='N'){
        printf("얻은 총경험치는 %d입니다.\n현재 레벨은 %d입니다.\n현재까지 진행한 턴수는:%d번입니다.\n",(int)(exp) , lv , gameCount);
        break;
    }
    getchar(); 
    }


 return 0;   
    
}
