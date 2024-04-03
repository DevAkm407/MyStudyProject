#include "maps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

struct termios org_term;
struct termios new_term;

enum monters {empty,nomal,students,baphomet,lee,ryu};
enum inpc {npcempty,pandora,prist,dwarf};
enum wepon {basicsword,longsword,japensword,nigthsword_saj};
enum dep {armor,boots,cape,gloves,mask};

//전투함수,층마다 일반몬스터만 상대
int battle(int floor,int monstercode)
{

}

//보스전투 5층에서만 나오는 보스와 싸움
int battel_boss(int bossname)
{}
//기본 터미널 모드 저장
void save_input_mode(void)
{
		tcgetattr(STDIN_FILENO, &org_term); // STDIN으로부터 터미널 속성을 받아온다
}
//터미널 enter없이 사용
void set_input_mode(void)
{
		tcgetattr(STDIN_FILENO, &new_term); // STDIN으로부터 터미널 속성을 받아온다
		new_term.c_lflag &= ~(ICANON | ECHO);  // ICANON, ECHO 속성을 off
		new_term.c_cc[VMIN] = 1;               // 1 바이트씩 처리
		new_term.c_cc[VTIME] = 0;              // 시간은 설정하지 않음
		tcsetattr(STDIN_FILENO, TCSANOW, &new_term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}
//원래 enter로 바꾸기
void reset_input_mode(void)
{
		tcsetattr(STDIN_FILENO, TCSANOW, &org_term);  // STDIN에 기존의 터미널 속성을 바로 적용
}
//세팅하는거 대충
int movement(void)
{
    save_input_mode();
    set_input_mode();
    char ch=getchar();
    ch=getchar();
    ch=getchar();
  return ch;  
}


int gold_drop(Boki* boki,int floor)/*골드 드랍 함수*/
{
    srand(time(NULL));
    int get_gold;
    switch (floor)/*층*/
    {
    case 1:
        get_gold=(rand()%26)+5;/*5~30개*/
        boki->gold+=get_gold;
        printf("%d 골드 획득\n",get_gold);
        break;
    case 2:
        get_gold=(rand()%56)+5;/*5~60개*/
        boki->gold+=get_gold;
        printf("%d 골드 획득\n",get_gold);
        break;
    case 3:
        get_gold=(rand()%96)+5;/*5~100개*/
        boki->gold+=get_gold;
        printf("%d 골드 획득\n",get_gold);
        break;
    case 4:
        get_gold=(rand()%126)+5;/*5~130개*/
        boki->gold+=get_gold;
        printf("%d 골드 획득\n",get_gold);
        break;
    case 5:
        get_gold=rand()%196+5;/*5~200개*/
        boki->gold+=get_gold;
        printf("%d 골드 획득\n",get_gold);
        break;
    default:
        break;
    }
    return get_gold;
}

int gold_drop_boss(Boki* boki, int boss)/*보스 골드 드랍 함수*/
{   
    srand(time(NULL));
    int get_gold;
    switch (boss)
    {
    case 1:/*네임드 우리반학생용사들*/
        get_gold=(rand()%496)+5;/*5~500*/
        boki->gold+=get_gold;
        printf("%d 골드 획득\n",get_gold);
        break;
    case 2:/*바포메트*/
        get_gold=(rand()%696)+5;/*5~700*/
        boki->gold+=get_gold;
        printf("%d 골드 획득\n",get_gold);
        break;
    case 3:/*이동녘*/
        get_gold=(rand()%996)+5;/*5~1000*/
        boki->gold+=get_gold;
        printf("%d 골드 획득\n",get_gold);
        break;
    case 4:/*류홍걸*/
        get_gold=(rand()%2996)+5;/*5~3000*/
        boki->gold+=get_gold;
        printf("%d 골드 획득\n",get_gold);
        break;
    
    default:
        break;
    }
    return get_gold;
}

int drop_2teer20(Boki* boki) /*2티어 20프로 드랍 함수*/
{
    boki->bokiEquipment.rare.cottencape[0][0]=1;
    boki->bokiEquipment.rare.halfarmor[0][0]=1;
    boki->bokiEquipment.rare.k80mask[0][0]=1;
    boki->bokiEquipment.rare.rubbergloves[0][0]=1;
    boki->bokiEquipment.rare.slipper[0][0]=1;

    srand(time(NULL));/*랜덤사용*/
    int get_chance;/*획득확률*/
    int twen;
    get_chance=rand()%100+1;/*100퍼중에*/
    if (get_chance<=20)/*20프로*/
    {
        twen=rand()%6+1;/*1~6(장비가 6개)*/
        switch (twen)
        {
        case 1:
           for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.weapon.longsword[i][0]==0)
                {
                    boki->bokiEquipment.weapon.longsword[i][0]=1;
                    printf("장검획득\n");
                    break;
                }
           }
           break;
        case 2:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.rare.cottencape[i][0]==0)
                {
                    boki->bokiEquipment.rare.cottencape[i][0]=1;
                    printf("면망토획득\n");
                    break;
                }
           }
            break;
        case 3:
           for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.rare.halfarmor[i][0]==0)
                {
                    boki->bokiEquipment.rare.halfarmor[i][0]=1;
                    printf("반팔갑빠획득\n");
                    break;
                }
           }
            break;
        case 4:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.rare.k80mask[i][0]==0)
                {
                    boki->bokiEquipment.rare.k80mask[i][0]=1;
                    printf("k80마스크획득\n");
                    break;
                }
           }
            break;
        case 5:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.rare.rubbergloves[i][0]==0)
                {
                    boki->bokiEquipment.rare.rubbergloves[i][0]=1;
                    printf("고무장갑획득\n");
                    break;
                }
           }
            break;
        case 6:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.rare.slipper[i][0]==0)
                {
                    boki->bokiEquipment.rare.slipper[i][0]=1;
                    printf("슬리퍼획득\n");
                    break;
                }
           }
            break;
        default:
            break;
        }
    }
    else
    {
        twen=0;
        printf("획득한 아이템이 없습니다.\n");
    }
    return twen;
}

int drop_3teer20(Boki* boki) /*3티어 20프로 드랍 함수*/
{
    srand(time(NULL));/*랜덤사용*/
    int get_chance;/*획득확률*/
    get_chance=rand()%100+1;/*100퍼중에*/
    int twen;
    if (get_chance<=20)/*20프로*/
    {
        twen=rand()%6+1;/*1~6(장비가 6개)*/
        switch (twen)
        {
        case 1:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.weapon.japensword[i][0]==0)
                {
                    boki->bokiEquipment.weapon.japensword[i][0]=1;
                    printf("일본도획득\n");
                    break;
                }
           }
            break;
        case 2:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.cottengloves[i][0]==0)
                {
                    boki->bokiEquipment.epic.cottengloves[i][0]=1;
                    printf("면장갑획득\n");
                    break;
                }
           }
            break;
        case 3:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.hoodarmor[i][0]==0)
                {
                    boki->bokiEquipment.epic.hoodarmor[i][0]=1;
                    printf("후드갑빠획득\n");
                    break;
                }
           }
            break;
        case 4:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.k94mask[i][0]==0)
                {
                    boki->bokiEquipment.epic.k94mask[i][0]=1;
                    printf("k94마스크획득\n");
                    break;
                }
           }
            break;
        case 5:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.silkcape[i][0]==0)
                {
                    boki->bokiEquipment.epic.silkcape[i][0]=1;
                    printf("비단망토획득\n");
                    break;
                }
           }
            break;
        case 6:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.sneakers[i][0]==0)
                {
                    boki->bokiEquipment.epic.sneakers[i][0]=1;
                    printf("k94마스크획득\n");
                    break;
                }
           }
            break;
        default:
            break;
        }
    }
    else
    {
        twen=0;
        printf("획득한 아이템이 없습니다.\n");
    }
    return twen;
}

int drop_3teer30(Boki* boki) /*3티어 30프로 드랍 함수*/
{
    srand(time(NULL));/*랜덤사용*/
    int get_chance;/*획득확률*/
    get_chance=rand()%100+1;/*100퍼중에*/
    int twen;
    if (get_chance<=30)/*30프로*/
    {
        twen=rand()%6+1;/*1~6(장비가 6개)*/
        switch (twen)
        {
        case 1:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.weapon.japensword[i][0]==0)
                {
                    boki->bokiEquipment.weapon.japensword[i][0]=1;
                    printf("일본도획득\n");
                    break;
                }
           }
            break;
        case 2:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.cottengloves[i][0]==0)
                {
                    boki->bokiEquipment.epic.cottengloves[i][0]=1;
                    printf("면장갑획득\n");
                    break;
                }
           }
            break;
        case 3:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.hoodarmor[i][0]==0)
                {
                    boki->bokiEquipment.epic.hoodarmor[i][0]=1;
                    printf("후드갑빠획득\n");
                    break;
                }
           }
            break;
        case 4:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.k94mask[i][0]==0)
                {
                    boki->bokiEquipment.epic.k94mask[i][0]=1;
                    printf("k94마스크획득\n");
                    break;
                }
           }
            break;
        case 5:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.silkcape[i][0]==0)
                {
                    boki->bokiEquipment.epic.silkcape[i][0]=1;
                    printf("비단망토획득\n");
                    break;
                }
           }
            break;
        case 6:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.epic.sneakers[i][0]==0)
                {
                    boki->bokiEquipment.epic.sneakers[i][0]=1;
                    printf("k94마스크획득\n");
                    break;
                }
           }
            break;
        default:
            break;
        }
    }
    else
    {
        twen=0;
        printf("획득한 아이템이 없습니다.\n");
    }
    return twen;
}

int drop_4teer5(Boki* boki) /*4티어 5프로 드랍 함수*/
{
    srand(time(NULL));/*랜덤사용*/
    int get_chance;/*획득확률*/
    get_chance=rand()%100+1;/*100퍼중에*/
    int five;
    if (get_chance<=5)/*5프로*/
    {
        five=rand()%6+1;/*1~6(장비가 6개)*/
        switch (five)
        {
            case 1:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.weapon.nigthsword_saj[i][0]==0)
                {
                    boki->bokiEquipment.weapon.nigthsword_saj[i][0]=1;
                    printf("싸울아비장검획득\n");
                    break;
                }
           }
            break;
        case 2:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.airjodan[i][0]==0)
                {
                    boki->bokiEquipment.legend.airjodan[i][0]=1;
                    printf("에어조단획득\n");
                    break;
                }
           }
            break;
        case 3:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.bulletcape[i][0]==0)
                {
                    boki->bokiEquipment.legend.bulletcape[i][0]=1;
                    printf("방탄망토획득\n");
                    break;
                }
            }
            break;
        case 4:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.dragonarmor[i][0]==0)
                {
                    boki->bokiEquipment.legend.dragonarmor[i][0]=1;
                    printf("용갑빠획득\n");
                    break;
                }
           }
            break;
        case 5:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.leardergloves[i][0]==0)
                {
                    boki->bokiEquipment.legend.leardergloves[i][0]=1;
                    printf("가죽장갑획득\n");
                    break;
                }
           }
            break;
        case 6:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.tigermask[i][0]==0)
                {
                    boki->bokiEquipment.legend.tigermask[i][0]=1;
                    printf("타이거마스크획득\n");
                    break;
                }
           }
        default:
            break;
        }
    }
    else
    {
        five=0;
        printf("획득한 아이템이 없습니다.\n");
    }
    return five;
}

int drop_4teer20(Boki* boki) /*4티어 20프로 드랍 함수*/
{
    srand(time(NULL));/*랜덤사용*/
    int get_chance;/*획득확률*/
    get_chance=rand()%100+1;/*100퍼중에*/
    int twen;
    if (get_chance<=20)/*20프로*/
    {
        twen=rand()%6+1;/*1~6(장비가 6개)*/
        switch (twen)
        {
            case 1:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.weapon.nigthsword_saj[i][0]==0)
                {
                    boki->bokiEquipment.weapon.nigthsword_saj[i][0]=1;
                    printf("싸울아비장검획득\n");
                    break;
                }
           }
            break;
        case 2:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.airjodan[i][0]==0)
                {
                    boki->bokiEquipment.legend.airjodan[i][0]=1;
                    printf("에어조단획득\n");
                    break;
                }
           }
            break;
        case 3:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.bulletcape[i][0]==0)
                {
                    boki->bokiEquipment.legend.bulletcape[i][0]=1;
                    printf("방탄망토획득\n");
                    break;
                }
            }
            break;
        case 4:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.dragonarmor[i][0]==0)
                {
                    boki->bokiEquipment.legend.dragonarmor[i][0]=1;
                    printf("용갑빠획득\n");
                    break;
                }
           }
            break;
        case 5:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.leardergloves[i][0]==0)
                {
                    boki->bokiEquipment.legend.leardergloves[i][0]=1;
                    printf("가죽장갑획득\n");
                    break;
                }
           }
            break;
        case 6:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.tigermask[i][0]==0)
                {
                    boki->bokiEquipment.legend.tigermask[i][0]=1;
                    printf("타이거마스크획득\n");
                    break;
                }
           }
        default:
            break;
        }
    }
    else
    {
        twen=0;
        printf("획득한 아이템이 없습니다.\n");
    }
    return twen;
}

int town_movement(Boki* boki)/*순간이동 주문서 획득*/
{
    boki->consume.scroll.tmscrollpaper;
    srand(time(NULL));/*랜덤사용*/
    int get_chance; /*획득확률*/
    int tm;
    get_chance=rand()%100+1;/*1~100까지*/
    if (get_chance<=20)/*20보다 작거나 같으면*/
    {
        tm=rand()%3+1; /*획득 개수는 1~3개*/
        boki->consume.scroll.tmscrollpaper+tm;
        //*item_address.address_tmscrollpaper=item_table.scroll.tmscrollpaper+=tm;
        printf("순간이동주문서 %d개획득\n",tm);
    }
    else
    {
        tm=0;
        printf("순간이동주문서를 획득하지 않았습니다.\n");
    }
    
    return tm;/*획득 개수 리턴*/
}

int drop_4teer10(Boki* boki) /*4티어 10프로 드랍 함수*/
{
    srand(time(NULL));/*랜덤사용*/
    int get_chance;/*획득확률*/
    int ten;
    get_chance=rand()%100+1;/*100퍼중에*/
    if (get_chance<=10)/*10프로*/
    {
        ten=rand()%6+1;/*1~6(장비가 6개)*/
        switch (ten)
        {
            case 1:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.weapon.nigthsword_saj[i][0]==0)
                {
                    boki->bokiEquipment.weapon.nigthsword_saj[i][0]=1;
                    printf("싸울아비장검획득\n");
                    break;
                }
           }
            break;
        case 2:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.airjodan[i][0]==0)
                {
                    boki->bokiEquipment.legend.airjodan[i][0]=1;
                    printf("에어조단획득\n");
                    break;
                }
           }
            break;
        case 3:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.bulletcape[i][0]==0)
                {
                    boki->bokiEquipment.legend.bulletcape[i][0]=1;
                    printf("방탄망토획득\n");
                    break;
                }
            }
            break;
        case 4:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.dragonarmor[i][0]==0)
                {
                    boki->bokiEquipment.legend.dragonarmor[i][0]=1;
                    printf("용갑빠획득\n");
                    break;
                }
           }
            break;
        case 5:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.leardergloves[i][0]==0)
                {
                    boki->bokiEquipment.legend.leardergloves[i][0]=1;
                    printf("가죽장갑획득\n");
                    break;
                }
           }
            break;
        case 6:
            for (int i = 0; i < 5; i++)
           {
            if(boki->bokiEquipment.legend.tigermask[i][0]==0)
                {
                    boki->bokiEquipment.legend.tigermask[i][0]=1;
                    printf("타이거마스크획득\n");
                    break;
                }
           }
        }
    }
    else
    {
        ten=0;
        printf("획득한 아이템이 없습니다.\n");
    }
    return ten;
}


//사용자 위치를 초기화 하는 함수(동적할당함)
User* UserPointInitialization(User* user)
{
   user=(User*)malloc(sizeof(User));
   user->userPoint[0]=0;
   user->userPoint[1]=0;
   user->floorcount[0]=0;
    user->fcinterrupt[0]=-1;
   
   return user;
}

//방향키로 사용자가 움직이는것을 해주는 함수
User* UserMovement(User* user,maps* monmap)
{
//위 65 아레 66 왼쪽 68 오른족 67
int mov=movement();
user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]]=' ';
int a[2];
memcpy(a,user->userPoint,sizeof(int)*2);
switch (mov)
{
//위
case 65:
    a[0]-=1;
    if(a[0]<0){
        printf("맵위 쪽 끝입니다.\n");
        a[0]=0;
        break;
    }
   else      
        break;
//아레
case 66:
    a[0]+=1;
    if(a[0]>49)
     {
        printf("맵 아레 쪽 끝입니다.\n");
        a[0]=49;
        break;
    }   
    else
        break;
//왼쪽
case 68:
     a[1]-=1;
    if(user->userPoint[1]<0)
    {
        printf("맵 왼쪽 끝입니다.\n");
        a[1]=0;
        break;
    }
else 
    break;
//오른쪽
case 67:
    a[1]+=1;
    if(user->userPoint[1]>49)
    {
        printf("맵 오른쪽 끝입니다.\n");
        a[1]=49;
        break;
    }
   else     
        break;
default:
    break;
}
system("clear");

memcpy(user->userPoint,a,sizeof(int)*2);

return user;
}

//맵을 보여주고 사용자가 몬스터를 만났을때 상호 작용을 하는 함수
User* ShowMap(User* user,maps* monmap,Boki* boki)
{
    if(user->floorcount[0]!=5&&user->userPoint[0]==49&&user->userPoint[1]==49){
    printf("다음층으로 이동하시겠습니까?y or n\n");
    char ch=getchar();
    while(1){
    if(ch=='y'||ch=='Y'){
        user->fcinterrupt[0]=-1;
        user->floorcount[0]++;
        user->userPoint[0]=0;
        user->userPoint[1]=0;
        system("clear");
        break;
    }
    else if(ch=='n'||ch=='n'){ 
            user->userPoint[1]--;
            break;
    }        
    system("clear");
    printf("다음층으로 이동하시겠습니까?y or n\n");
    ch=getchar();
    }
    }
if(user->floorcount[0]!=0&&user->userPoint[0]==1&&user->userPoint[1]==1){
    printf("이전층으로 이동하시겠습니까?y or n\n");
    char ch=getchar();
    while(1){   
    if(ch=='y'||ch=='Y'){
        user->fcinterrupt[0]=-1;
        user->floorcount[0]--;
        user->userPoint[0]=47;
        user->userPoint[1]=47;
        system("clear");
        break;
    }
    else if(ch=='n'||ch=='n'){
        user->userPoint[0]++;
        break;
    }
    system("clear");
    printf("이전층으로 이동하시겠습니까?y or n\n");
    ch=getchar();
}
}
user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]]='$';

for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            printf("%c",user->userInterFaceMap[i][j]);
        } 
        printf("\n");
    }
switch (user->floorcount[0])
{
// case 0:
//     //몬스터 또는 npc 조우상황을 스위치로 작성하려고함
//     switch (monmap->town.townmaps[user->userPoint[0]][user->userPoint[1]])
//     {
//     case pandora:
//         //판도라 전용 함수
//         system("clear");
//         printf("판도라 상점\n");
//         getchar();
//         break;
//     case prist:
//         //프리스트 전용함수
//         break;
//     case dwarf:
//         //드워프 전용함수
//         break;
//     default:
//         break;
//     }
//     break;

case 1:
    switch (monmap->firstfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //1층일반 몬스터와 전투
        if(battle(user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            boki->fhp*=1.01;
            monmap->firstfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
            user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';      
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            break;
        }
    case students:
        //학생용사들과 전투
        if(battle(user->floorcount[0],students)== 1)
        {
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
            monmap->firstfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
            user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';      
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            break;
        }
        break;
    }
    
    break;
case 2:
    switch (monmap->secondfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //2층 일반 몬스터와 전투
         if(battle(user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            boki->fhp*=1.02;
            monmap->secondfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
       
        break;
    case students:
        //학생용사들과 전투
         if(battle(user->floorcount[0],students)== 1)
        {
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
        monmap->secondfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            break;
        }
    }
    break;
case 3:
    switch (monmap->thirdfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //3층 일반 몬스터와 전투
       if(battle(user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            boki->fhp*=1.03;
        monmap->thirdfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
        break;
    case students:
        //학생용사들과 전투
         if(battle(user->floorcount[0],students)== 1)
        {
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
        monmap->thirdfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            break;
        }
    }
    
    break;
case 4:
    switch (monmap->fourthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //4층 일반 몬스터와 전투
        if(battle(user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            drop_2teer20(boki);
            boki->fhp*=1.05;
        monmap->fourthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
        break;
    case students:
        //학생용사들과 전투
        if(battle(user->floorcount[0],students)== 1)
        {
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
        monmap->fourthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            break;
        }
        
        
    } 
break;
case 5:
    switch (monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //5층 일반 몬스터와 전투
        if(battle(user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            drop_2teer20(boki);
            boki->fhp*=1.07;
        monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
    case students:
        //학생용사들과 전투
        if(battle(user->floorcount[0],students)== 1)
        {
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
        monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            break;
        }
    case baphomet:
        //바포메트와 전투
        if(battel_boss(baphomet)== 1)
        {
            gold_drop_boss(boki,baphomet-1);
            drop_3teer20(boki);
            drop_4teer5(boki);

        boki->fhp*=1.30;
        monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
    case lee:
        //리얼보스와 전투
        if(battel_boss(lee)== 1)
        {
            gold_drop_boss(boki,lee-1);
            drop_3teer20(boki);
            drop_4teer10(boki);
        boki->fhp*=1.60;
        monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
    case ryu:
        //찐막보스와 전투
        if(battel_boss(ryu)== 1)
        {
            gold_drop_boss(boki,ryu-1);
            drop_3teer30(boki);
            drop_4teer20(boki);
        boki->fhp*=2.00;
        monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        break;
        }
        else{
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
    }
    break;
default:
    break;
}
return user;
}

//좌표맵초기화
maps* MapsInitialization(maps* monmap)
{
    monmap=(maps*)malloc(sizeof(maps));
    
    return monmap;
}

//몬스터가 있는 맵 초기화
maps* MonsterMapsRegenerative(maps* monmap,User* user)
{
   srand(time(NULL));
   int* a=user->fcinterrupt;
   if(*a==-1){     
   int copymap[50][50];
   switch (user->floorcount[0])
   {
   case 0:
        for (int i = 0; i < 50; i++)
        {
            for (int j= 0; j<50; j++)
            {
            copymap[i][j]=npcempty;
            }
            
        }
    copymap[5][5]=pandora;
    copymap[7][7]=prist;
    copymap[10][10]=dwarf;    
    memcpy(monmap->town.townmaps,copymap,sizeof(int)*2500);
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if(monmap->town.townmaps[i][j]==pandora)
            user->userInterFaceMap[i][j]='#';
            else if(monmap->town.townmaps[i][j]== prist)
                user->userInterFaceMap[i][j]='@';
            else if(monmap->town.townmaps[i][j]==dwarf)
                user->userInterFaceMap[i][j]='^';
            else
                user->userInterFaceMap[i][j]=' ';
            
        }
        
    }
    user->userInterFaceMap[49][49]='0';
   break;
   
   case 1: 
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
            
                int mmr=rand()%100;
                if(mmr>=70)
                    copymap[i][j]=students;
                else if(mmr<=50)
                    copymap[i][j]=nomal;
                else
                    copymap[i][j]=empty;
            }
        }
        memcpy(monmap->firstfloor.monstermaps,copymap,sizeof(int)*2500);
        for (int k = 0; k < 50; k++){
            for (int z = 0; z < 50; z++)
            {
                if(monmap->firstfloor.monstermaps[k][z]==empty)
                    user->userInterFaceMap[k][z]=' ';
                else
                    user->userInterFaceMap[k][z]='?'; 
            }
        }
        user->userInterFaceMap[49][49]='0';
    break;
    
   case 2: 
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                int mmr=rand()%100;
                if(mmr>=70)
                    copymap[i][j]=students;
                else if(mmr<=50)
                    copymap[i][j]=nomal;
                else
                    copymap[i][j]=empty;
            }
            
            
        }
        memcpy(monmap->secondfloor.monstermaps,copymap,sizeof(int)*2500);
        for (int k = 0; k < 50; k++){
            for (int z = 0; z < 50; z++)
            {
                    if(monmap->secondfloor.monstermaps[k][z]==empty)
                        user->userInterFaceMap[k][z]=' ';
                    else
                        user->userInterFaceMap[k][z]='?';
            }
        }
        user->userInterFaceMap[49][49]='0';
    break;
        
    case 3: 
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
               
                int mmr=rand()%100;
                if(mmr>=70)
                    copymap[i][j]=students;
                else if(mmr<=50)
                    copymap[i][j]=nomal;
                else
                    copymap[i][j]=empty;
            }
        }
        memcpy(monmap->thirdfloor.monstermaps,copymap,sizeof(int)*2500);
        for (int k = 0; k < 50; k++){
            for (int z = 0; z < 50; z++)
            {
            if(monmap->thirdfloor.monstermaps[k][z]==empty)
                user->userInterFaceMap[k][z]=' ';
            else
                user->userInterFaceMap[k][z]='?';
            }
        }
        user->userInterFaceMap[49][49]='0';
    break;
        
    case 4: 
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
               
                int mmr=rand()%100;
                if(mmr>=70)
                    copymap[i][j]=students;
                else if(mmr<=50)
                    copymap[i][j]=nomal;
                else
                    copymap[i][j]=empty;
            }
        }
        memcpy(monmap->fourthfloor.monstermaps,copymap,sizeof(int)*2500);
        for (int k = 0; k < 50; k++){
            for (int z = 0; z < 50; z++)
            {
                    if(monmap->fourthfloor.monstermaps[k][z]==empty)
                        user->userInterFaceMap[k][z]=' ';
                    else
                        user->userInterFaceMap[k][z]='?';
            }
        }
        user->userInterFaceMap[49][49]='0';
    break;
    
    case 5: 
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
           
                int mmr=rand()%100;
                if(mmr>=70)
                    copymap[i][j]=students;
                else if(mmr>=30||mmr<=50)
                    copymap[i][j]=nomal;
                else if(mmr>=51 || mmr<=60)
                    copymap[i][j]=baphomet;
                else if(mmr>=61 || mmr<=65)
                    copymap[i][j]=lee;
                else if (mmr>=66||mmr<=69)
                    copymap[i][j]=ryu;
                else 
                    copymap[i][j]=empty;
            }
        }
    memcpy(monmap->fifthfloor.monstermaps,copymap,sizeof(int)*2500);
    for (int k = 0; k < 50; k++)
    {
        for (int z = 0; z < 50; z++)
        {
             if(monmap->fifthfloor.monstermaps[k][z]==empty)
                user->userInterFaceMap[k][z]=' ';
            else
                user->userInterFaceMap[k][z]='?';
        }
    }
    break;
   default:
        break;
   }
*a=2;
}
    return monmap;
}

//몬스터 초기화
Monster* MonsterInitialization(Monster* imonster)
{
    imonster=(Monster*)malloc(sizeof(Monster));

    srand(time(NULL));
    
    imonster->oaks_warrior.hp = (rand() % 51 )+50;
    imonster->oaks_warrior.damage = (rand() % 6) +10;
    
    imonster->zombie.hp= (rand() % 131) +50;
    imonster->zombie.damage =(rand() % 14) +17;
    
    imonster->ghoul.hp=(rand() % 61) +120;
    imonster->ghoul.damage = (rand() % 26)+20;
    
    imonster->skeleton.hp = (rand() % 61)+200;
    imonster -> skeleton.damage =(rand() % 28)+28;
    
    imonster->spartoi.hp =(rand()% 101)+260;
    imonster->spartoi.damage = (rand()%44)+32;
    return imonster;   
}

//몬스터 다시 생성 
Monster* MonterRegenerative(Monster* rm,Boki* boki,User* user)
{
    srand(time(NULL));
    char* name[28]={"강진영","권철민","김건","김민아","김성근",
    "김승수","김경곤","김재신","김혜빈","노주영","박민건","박선후"
    ,"박장미","박희정","서훈","안광민","오은지","유시온","이동준",
    "이준호","이은승","이준호","이철","임석현","조대정","조세빈",
    "황운하","황은비"};
    switch (user->floorcount[0])
    {
    case 1:
        rm->oaks_warrior.hp = (rand() % 51 )+50;
        rm->oaks_warrior.damage = (rand() % 6) +10;
        rm->hero.name=name[rand()%28];
        rm->hero.hp= boki->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        break;
    case 2:
        rm->zombie.hp= (rand() % 131) +50;
        rm->zombie.damage =(rand() % 14) +17;
        rm->hero.name=name[rand()%28];
        rm->hero.hp= boki->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        break;
    case 3:
        rm->ghoul.hp=(rand() % 61) +120;
        rm->ghoul.damage = (rand() % 26)+20;
        rm->hero.name=name[rand()%28];
        rm->hero.hp= boki->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        break;
    case 4:
        rm->skeleton.hp = (rand() % 61)+200;
        rm -> skeleton.damage =(rand() % 28)+28;
        rm->hero.name=name[rand()%28];
        rm->hero.hp= boki->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        break;
    case 5:
        rm->spartoi.hp =(rand()% 101)+260;
        rm->spartoi.damage = (rand()%44)+32;   
        rm->hero.name=name[rand()%28];
        rm->hero.hp= boki->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        rm->Baphomet.hp=boki->chp*5;
        rm->Baphomet.damage=(rand()%271)+180;
        rm->boss.hp=boki->chp*7;
        rm->boss.damage=(rand()%221)+330;
        rm->realboss.hp=boki->chp*10;
        rm->realboss.damage=(rand()%801)+500;
        break;
    default:
        break;
    }
}

//무기 강화함수
void WReinForcement(Boki* boki,int count,int armed)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    printf("aaaa:%d\n",aaaa);
    if(aaaa>=8){
        switch (armed)
        {
        case basicsword:          
            if(boki->bokiEquipment.weapon.basicsword[count][0] !=0 &&boki->bokiEquipment.weapon.basicsword[count][2]!=10)
            {
                boki->bokiEquipment.weapon.basicsword[count][1]*=1.1;
                boki->bokiEquipment.weapon.basicsword[count][2]+=1;            
            }
            break;
        case longsword:
            if(boki->bokiEquipment.weapon.longsword[count][0] !=0&&boki->bokiEquipment.weapon.longsword[count][2]!=10)
            {
                boki->bokiEquipment.weapon.longsword[count][1]*=1.1;
                boki->bokiEquipment.weapon.longsword[count][2]+=1;            
            }
            break;
        
        case japensword:
        if(boki->bokiEquipment.weapon.japensword[count][0] !=0&&boki->bokiEquipment.weapon.japensword[count][2]!=10)
            {
                boki->bokiEquipment.weapon.japensword[count][1]*=1.1;
                boki->bokiEquipment.weapon.japensword[count][2]+=1;            
            }
        break;
        
        case nigthsword_saj:
            if(boki->bokiEquipment.weapon.nigthsword_saj[count][0] !=0&&boki->bokiEquipment.weapon.nigthsword_saj[count][2]!=10)
            {
                boki->bokiEquipment.weapon.nigthsword_saj[count][1]*=1.1;
                boki->bokiEquipment.weapon.nigthsword_saj[count][2]+=1;            
            }
            break;    
        }
    }
    else
    {
        switch (armed)
        {
         case basicsword:          
            boki->bokiEquipment.weapon.basicsword[count][0]=0;    
            break;
        
        case longsword:
            boki->bokiEquipment.weapon.longsword[count][0]=0;
            break;
        
        case japensword:
            boki->bokiEquipment.weapon.japensword[count][0]=0;
        break;
        
        case nigthsword_saj:
            boki->bokiEquipment.weapon.nigthsword_saj[count][0]=0;
            break;    
        }
    }    
}

//1티어 방어구 강화 함수
void FDepReinForce(Boki* boki,int count,int armed)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    if(aaaa>=8){
        switch (armed)
        {
        case armor:          
            if(boki->bokiEquipment.nomal.basicarmor[count][0] !=0&&boki->bokiEquipment.nomal.basicarmor[count][2]!=10)
            {
                boki->bokiEquipment.nomal.basicarmor[count][1]*=1.1;
                boki->bokiEquipment.nomal.basicarmor[count][2]+=1;            
            }
            break;
        case boots:
            if(boki->bokiEquipment.nomal.basicboots[count][0] !=0&&boki->bokiEquipment.nomal.basicboots[count][2]!=10)
            {
                boki->bokiEquipment.nomal.basicboots[count][1]*=1.1;
                boki->bokiEquipment.nomal.basicboots[count][2]+=1;            
            }
            break;
        
        case cape:
        if(boki->bokiEquipment.nomal.basiccape[count][0] !=0&&boki->bokiEquipment.nomal.basiccape[count][2]!=10)
            {
                boki->bokiEquipment.nomal.basiccape[count][1]*=1.1;
                boki->bokiEquipment.nomal.basiccape[count][2]+=1;            
            }
        break;
        
        case gloves:
            if(boki->bokiEquipment.nomal.basicgloves[count][0] !=0&&boki->bokiEquipment.nomal.basicgloves[count][2]!=10)
            {
                boki->bokiEquipment.nomal.basicgloves[count][1]*=1.1;
                boki->bokiEquipment.nomal.basicgloves[count][2]+=1;            
            }
            break;    
        case mask:
        if(boki->bokiEquipment.nomal.basicmask[count][0] !=0&&boki->bokiEquipment.nomal.basicmask[count][2]!=10)
            {
                boki->bokiEquipment.nomal.basicmask[count][1]*=1.1;
                boki->bokiEquipment.nomal.basicmask[count][2]+=1;            
            }
        break;
        }
    }
    
    else
    {
        switch (armed)
        {
         case armor:          
            boki->bokiEquipment.nomal.basicarmor[count][0]=0;    
            break;
        
        case boots:
            boki->bokiEquipment.nomal.basicboots[count][0]=0;
            break;
        
        case cape:
           boki->bokiEquipment.nomal.basiccape[count][0]=0;
        break;
        case gloves:
            boki->bokiEquipment.nomal.basicgloves[count][0]=0;
        break;
        case mask:
           boki->bokiEquipment.nomal.basicmask[count][0]=0;
            break;    
        }
    }
}

//2티어 방어구 강화 함수
void SDepReinForce(Boki* boki,int count,int armed)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    if(aaaa>=8){
        switch (armed)
        {
        case armor:          
            if(boki->bokiEquipment.rare.halfarmor[count][0] !=0&&boki->bokiEquipment.rare.halfarmor[count][2]!=10)
            {
                boki->bokiEquipment.rare.halfarmor[count][1]*=1.1;
                boki->bokiEquipment.rare.halfarmor[count][2]+=1;            
            }
            break;
        case boots:
            if(boki->bokiEquipment.rare.slipper[count][0] !=0&&boki->bokiEquipment.rare.slipper[count][2]!=10)
            {
                boki->bokiEquipment.rare.slipper[count][1]*=1.1;
                boki->bokiEquipment.rare.slipper[count][2]+=1;            
            }
            break;
        
        case cape:
        if(boki->bokiEquipment.rare.cottencape[count][0] !=0&&boki->bokiEquipment.rare.cottencape[count][2]!=10)
            {
                boki->bokiEquipment.rare.cottencape[count][1]*=1.1;
                boki->bokiEquipment.rare.cottencape[count][2]+=1;            
            }
        break;
        
        case gloves:
            if(boki->bokiEquipment.rare.rubbergloves[count][0] !=0&&boki->bokiEquipment.rare.rubbergloves[count][2]!=10)
            {
                boki->bokiEquipment.rare.rubbergloves[count][1]*=1.1;
                boki->bokiEquipment.rare.rubbergloves[count][2]+=1;            
            }
            break;    
        case mask:
        if(boki->bokiEquipment.rare.k80mask[count][0] !=0&&boki->bokiEquipment.rare.k80mask[count][2]!=10)
            {
                boki->bokiEquipment.rare.k80mask[count][1]*=1.1;
                boki->bokiEquipment.rare.k80mask[count][2]+=1;            
            }
        break;
        }
    }
    
    else
    {
        switch (armed)
        {
         case armor:          
            boki->bokiEquipment.rare.halfarmor[count][0]=0;    
            break;
        
        case boots:
            boki->bokiEquipment.rare.slipper[count][0]=0;
            break;
        
        case cape:
           boki->bokiEquipment.rare.cottencape[count][0]=0;
        break;
        case gloves:
            boki->bokiEquipment.rare.rubbergloves[count][0]=0;
        break;
        case mask:
           boki->bokiEquipment.rare.k80mask[count][0]=0;
            break;    
        }
    }
}

//3티어 방어구 강화 함수
void TDepReinForce(Boki* boki,int count,int armed)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    if(aaaa>=8){
        switch (armed)
        {
        case armor:          
            if(boki->bokiEquipment.epic.hoodarmor[count][0] !=0&&boki->bokiEquipment.epic.hoodarmor[count][2]!=10)
            {
                boki->bokiEquipment.epic.hoodarmor[count][1]*=1.1;
                boki->bokiEquipment.epic.hoodarmor[count][2]+=1;            
            }
            break;
        case boots:
            if(boki->bokiEquipment.epic.sneakers[count][0] !=0&&boki->bokiEquipment.epic.sneakers[count][2]!=10)
            {
                boki->bokiEquipment.epic.sneakers[count][1]*=1.1;
                boki->bokiEquipment.epic.sneakers[count][2]+=1;            
            }
            break;
        
        case cape:
        if(boki->bokiEquipment.epic.silkcape[count][0] !=0&&boki->bokiEquipment.epic.silkcape[count][2]!=10)
            {
                boki->bokiEquipment.epic.silkcape[count][1]*=1.1;
                boki->bokiEquipment.epic.silkcape[count][2]+=1;            
            }
        break;
        
        case gloves:
            if(boki->bokiEquipment.epic.cottengloves[count][0] !=0&&boki->bokiEquipment.epic.cottengloves[count][2]!=10)
            {
                boki->bokiEquipment.epic.cottengloves[count][1]*=1.1;
                boki->bokiEquipment.epic.cottengloves[count][2]+=1;            
            }
            break;    
        case mask:
        if(boki->bokiEquipment.epic.k94mask[count][0] !=0&&boki->bokiEquipment.epic.k94mask[count][2]!=10)
            {
                boki->bokiEquipment.epic.k94mask[count][1]*=1.1;
                boki->bokiEquipment.epic.k94mask[count][2]+=1;            
            }
        break;
        }
    }
    
    else
    {
        switch (armed)
        {
         case armor:          
            boki->bokiEquipment.epic.hoodarmor[count][0]=0;    
            break;
        
        case boots:
            boki->bokiEquipment.epic.sneakers[count][0]=0;
            break;
        
        case cape:
           boki->bokiEquipment.epic.silkcape[count][0]=0;
        break;
        case gloves:
            boki->bokiEquipment.epic.cottengloves[count][0]=0;
        break;
        case mask:
           boki->bokiEquipment.epic.k94mask[count][0]=0;
            break;    
        }
    }
}

//4티어 방어구 강화 함수
void FoDepReinForce(Boki* boki,int count,int armed)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    if(aaaa>=8){
        switch (armed)
        {
        case armor:          
            if(boki->bokiEquipment.legend.dragonarmor[count][0] !=0&&boki->bokiEquipment.legend.dragonarmor[count][2]!=10)
            {
                boki->bokiEquipment.legend.dragonarmor[count][1]*=1.1;
                boki->bokiEquipment.legend.dragonarmor[count][2]+=1;            
            }
            break;
        case boots:
            if(boki->bokiEquipment.legend.airjodan[count][0] !=0&&boki->bokiEquipment.legend.airjodan[count][2]!=10)
            {
                boki->bokiEquipment.legend.airjodan[count][1]*=1.1;
                boki->bokiEquipment.legend.airjodan[count][2]+=1;            
            }
            break;
        
        case cape:
        if(boki->bokiEquipment.legend.bulletcape[count][0] !=0&&boki->bokiEquipment.legend.bulletcape[count][2]!=10)
            {
                boki->bokiEquipment.legend.bulletcape[count][1]*=1.1;
                boki->bokiEquipment.legend.bulletcape[count][2]+=1;            
            }
        break;
        
        case gloves:
            if(boki->bokiEquipment.legend.leardergloves[count][0] !=0&&boki->bokiEquipment.legend.leardergloves[count][2]!=10)
            {
                boki->bokiEquipment.legend.leardergloves[count][1]*=1.1;
                boki->bokiEquipment.legend.leardergloves[count][2]+=1;            
            }
            break;    
        case mask:
        if(boki->bokiEquipment.legend.tigermask[count][0] !=0&&boki->bokiEquipment.legend.tigermask[count][2]!=10)
            {
                boki->bokiEquipment.legend.tigermask[count][1]*=1.1;
                boki->bokiEquipment.legend.tigermask[count][2]+=1;            
            }
        break;
        }
    }
    
    else
    {
        switch (armed)
        {
         case armor:          
            boki->bokiEquipment.legend.dragonarmor[count][0]=0;    
            break;
        
        case boots:
            boki->bokiEquipment.legend.airjodan[count][0]=0;
            break;
        
        case cape:
           boki->bokiEquipment.legend.bulletcape[count][0]=0;
        break;
        case gloves:
            boki->bokiEquipment.legend.leardergloves[count][0]=0;
        break;
        case mask:
           boki->bokiEquipment.legend.tigermask[count][0]=0;
            break;    
        }
    }
}

void itemInitialization(Boki* boki)/*아이템 공격력, 방어구 초기화*/
{
    for (int i = 0; i < 5; i++)
    {
        boki->bokiEquipment.weapon.basicsword[i][1]=2;
        boki->bokiEquipment.weapon.japensword[i][1]=10;
        boki->bokiEquipment.weapon.longsword[i][1]=5;
        boki->bokiEquipment.weapon.nigthsword_saj[i][1]=20;
        boki->bokiEquipment.nomal.basicarmor[i][1]=1;
        boki->bokiEquipment.nomal.basicboots[i][1]=1;
        boki->bokiEquipment.nomal.basiccape[i][1]=1;
        boki->bokiEquipment.nomal.basicgloves[i][1]=1;
        boki->bokiEquipment.nomal.basicmask[i][1]=1;
        boki->bokiEquipment.rare.cottencape[i][1]=4;
        boki->bokiEquipment.rare.halfarmor[i][1]=4;
        boki->bokiEquipment.rare.k80mask[i][1]=4;
        boki->bokiEquipment.rare.rubbergloves[i][1]=4;
        boki->bokiEquipment.rare.slipper[i][1]=4;
        boki->bokiEquipment.epic.cottengloves[i][1]=8;
        boki->bokiEquipment.epic.hoodarmor[i][1]=8;
        boki->bokiEquipment.epic.k94mask[i][1]=8;
        boki->bokiEquipment.epic.silkcape[i][1]=8;
        boki->bokiEquipment.epic.sneakers[i][1]=8;
        boki->bokiEquipment.legend.airjodan[i][1]=13;
        boki->bokiEquipment.legend.bulletcape[i][1]=13;
        boki->bokiEquipment.legend.dragonarmor[i][1]=13;
        boki->bokiEquipment.legend.leardergloves[i][1]=13;
        boki->bokiEquipment.legend.tigermask[i][1]=13;
    }
}










