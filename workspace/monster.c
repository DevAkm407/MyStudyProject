#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include "function.h"

//function

//일단 fc인터럽트로 fc가증가하면 1을 0으로바꿔줄거임 그 다음 포인터로 그다음을 가르킬 거임 만약 5개의 fc인터럽트가 다 0이되면 다시 1로 초기화 하고 처음 1을 가리키게 하자
int main (void)
{
User* u=UserPointInitialization(u);
maps *m=MapsInitialization(m);
m=MonsterMapsRegenerative(m,u);
Monster* ster=MonsterInitialization(ster);
Boki* boki=BokiInitialization(boki);
while (1)
{  
    u=UserMovement(u,m,ster,boki);  
    m=MonsterMapsRegenerative(m,u);
    u=ShowMap(u,m,boki,ster);
}
free(u);
free(m);
free(ster);
free(boki);
return 0; 
}
//몬스터 초기화 첫 실행시 사용
//몬스터 층마다 초기화
// 매개변수로 maps*를 넣어야함 int floor는 몇층인지 나타냄 학생은 2 그 맵의 기본몬스터는 1 몬스터가 없으면 0
// 유저이동+조우