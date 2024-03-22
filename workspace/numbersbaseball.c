#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    int number[3]={10,10,10};
    int usernum[3]={11,11,11};
    int i=0;
    int strike=0;
    int ball=0;
    srand(time(NULL));
    while (number[2]==10)
    {
        int randnum=rand()%10;
        if(randnum!=number[i])
        {
            number[i]=randnum;
        i++;
        }
    }
    printf("숫자를 입력해 주세요(0~9):");
    while(usernum[0] ==usernum[1] || usernum[0]==usernum[2] || usernum[1] ==usernum[2] ){
        for (int j = 0; j < 3; j++)
        {
            scanf("%d",&usernum[j]);
            if(usernum[j]>10)
                printf("다시 입력해주세요. (0~9)\n");
        }
      if (usernum[0] ==usernum[1] || usernum[0]==usernum[2] || usernum[1] ==usernum[2])
        printf("중복 숫자입력하셨습니다 다시입력해주세요:");
    }   
    
    for ( i = 0; i < 3; i++)
    {
       if( number[i]==usernum[i]){
            printf("스트라이크");
            strike++;
       }
       else
       ball++;
    }
    printf("%d스트라이크 %d볼");

}