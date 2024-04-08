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
User* UserPointInitialization(User* user);

User* UserMovement(User* user,maps* monmap,Monster* rm,Boki* boki);

User* ShowMap(User* user, maps* monmap, Boki* boki,Monster* rm);

Monster* MonsterInitialization(Monster* imonster);

Monster* MonterRegenerative(Monster* rm, Boki* boki, User* user);

//강화 함수들 엘릭서 사용시 엘리서부분을 1로 설정할것
void WReinForcement(Boki* boki, int count, int armed,int elixir);

void FDepReinForce(Boki* boki, int count, int armed,int elixir);

void SDepReinForce(Boki* boki, int count, int armed,int elixir);

void TDepReinForce(Boki* boki, int count, int armed,int elixir);

void FoDepReinForce(Boki* boki, int count, int armed,int elixir);

void itemInitialization(Boki* boki);

void TownBack(Boki* boki, User* user);

int gold_drop(Boki* boki, int floor);

int gold_drop_boss(Boki* boki, int boss);

int drop_2teer20(Boki* boki);

int drop_3teer20(Boki* boki);

int drop_3teer30(Boki* boki);

int drop_4teer5(Boki* boki);

int drop_4teer10(Boki* boki);

int drop_4teer20(Boki* boki);

int town_movement(Boki* boki);

int tp_movement(Boki* boki);

int elixir_drop(Boki* boki,Monster* monster,int a);

//소비창 사용
void consume_window(Boki* boki,User* user);

//텔포위치저장
void TpsSave(User* user,Boki* boki);

//텔포사용
void TpsUseMove(User* user,Boki* boki);

void Pandora(Boki* boki);

void Prist(Boki* boki);

void Dwarf(Boki* boki);
//전투함수,층마다 일반몬스터만 상대
int battle(Monster *monster, Boki *boki, int floor, int monstername);
//보스전투 5층에서만 나오는 보스와 싸움
int battle_boss(Monster *monster, Boki *boki,int monstername);

void battle_boss_attack(Monster *monster, Boki *boki, int monstername);

void battle_attack(Monster *monster, Boki *boki, int floor, int monstername);

int equip_sword(  Boki* boki);

int equip_mask( Boki* boki);

int equip_armor(  Boki* boki);

int equip_cape(  Boki* boki);

int equip_gloves(  Boki* boki);

int equip_boots(  Boki* boki);

int equip(Boki* boki);

void reinforce(Boki* boki);

void Ereinforce(Boki* boki);
//전방끝

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

void reset_input_mode(void)
{
		tcsetattr(STDIN_FILENO, TCSANOW, &org_term);  // STDIN에 기존의 터미널 속성을 바로 적용
}

//세팅하는거 대충
int movement(void)
{
    save_input_mode();
    set_input_mode();
    char ch;
    while(1){
    if ((ch = getchar()) == 101 ||ch == 108 || ch==116 || ch==105 || ch == 65 || ch == 66 || ch== 67 || ch == 68)
        return ch;
    }
    return 0;
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

int town_movement(Boki* boki)/*마을이동 주문서 획득*/
{
    boki->consume.scroll.tmscrollpaper;
    srand(time(NULL));/*랜덤사용*/
    int get_chance; /*획득확률*/
    int tm;
    get_chance=rand()%100+1;/*1~100까지*/
    if (get_chance<=20)/*20보다 작거나 같으면*/
    {
        tm=rand()%3+1; /*획득 개수는 1~3개*/
        boki->consume.scroll.tmscrollpaper+=tm;
        //*item_address.address_tmscrollpaper=item_table.scroll.tmscrollpaper+=tm;
        printf("마을이동주문서 %d개획득\n",tm);
    }
    else
    {
        tm=0;
        printf("마을이동주문서를 획득하지 않았습니다.\n");
    }
    
    return tm;/*획득 개수 리턴*/
}

int tp_movement(Boki* boki)/*순간이동 주문서 획득*/
{
    srand(time(NULL));/*랜덤사용*/
    int get_chance; /*획득확률*/
    int tm;
    get_chance=rand()%100+1;/*1~100까지*/
    if (get_chance<=30)/*20보다 작거나 같으면*/
    {
        tm=rand()%3+1; /*획득 개수는 1~3개*/
        boki->consume.scroll.teleportscroll+=tm;
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
User* UserMovement(User* user,maps* monmap,Monster* rm,Boki* boki)
{
//위 65 아레 66 왼쪽 68 오른족 67
    
    int mov=movement();
user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]]=' ';
switch (mov)
{
//위
case 65:
    user->userPoint[0]-=1;
    if(user->userPoint[0]<0){
        printf("맵위 쪽 끝입니다.\n");
        user->userPoint[0]=0;
        break;
    }
   else      
        break;
//아레
case 66:
    user->userPoint[0]+=1;
    if(user->userPoint[0]>49)
     {
        printf("맵 아레 쪽 끝입니다.\n");
        user->userPoint[0]=49;
        break;
    }   
    else
        break;
//왼쪽
case 68:
     user->userPoint[1]-=1;
    if(user->userPoint[1]<0)
    {
        printf("맵 왼쪽 끝입니다.\n");
        user->userPoint[1]=0;
        break;
    }
else 
    break;
//오른쪽
case 67:
    user->userPoint[1]+=1;
    if(user->userPoint[1]>49)
    {
        printf("맵 오른쪽 끝입니다.\n");
        user->userPoint[1]=49;
        break;
    }
   else     
        break;
//알파벳 e
case 101:
    //장비창 불러오는 함수
    equip(boki);
    sleep(1);
    break;
//알파벳 i
case 105:
    //소비창 불러오는 함수
    consume_window(boki,user);
    sleep(1);
    break;
//알파벳 t
case 116:
    //텔포위치 저장
    TpsSave(user,boki);
    sleep(1);
break;

default:
    break;
}
system("clear");


return user;
}

//맵을 보여주고 사용자가 몬스터를 만났을때 상호 작용을 하는 함수
User* ShowMap(User* user,maps* monmap,Boki* boki,Monster* rm)
{
    srand(time(NULL));
   static char* name[28]={"강진영","권철민","김건","김민아","김성근",
    "김승수","김영곤","김재신","김혜빈","노주영","박민건","박선후"
    ,"박장미","박희정","서훈","안광민","오은지","유시온","이동준",
    "이준호","이은승","이준호","이철","임석현","조대정","조세빈",
    "황운하","황은비"};
    rm = MonterRegenerative(rm, boki, user);
    int lms;
    int battle1=1;
    int rbattle=10;
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
if(user->floorcount[0]==0)
{
user->userInterFaceMap[5][5]='#';
user->userInterFaceMap[7][7]='@';
user->userInterFaceMap[10][10]='^';    
}

user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]]='$';
if(user->floorcount[0] != 0){
    user->userInterFaceMap[1][1]='0'; 
}

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
case 0:
    //몬스터 또는 npc 조우상황을 스위치로 작성하려고함
    switch (monmap->town.townmaps[user->userPoint[0]][user->userPoint[1]])
    {
    case pandora:
        //판도라 전용 함수
        Pandora(boki);
        break;
    case prist:
        //프리스트 전용함수
        Prist(boki);
        break;
    case dwarf:
        //드워프 전용함수
        Dwarf(boki);
        break;
    default:
        break;
    }
    break;

case 1:
    switch (monmap->firstfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //1층일반 몬스터와 전투
        system("clear");
       if(battle1=battle(rm,boki,user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            boki->fhp*=1.01;
            monmap->firstfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
            user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';      
        }
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            break;
        }
        else if(battle1==3)
            break;
    break;       
    case students:
        //학생용사들과 전투
        system("clear");
        
        while(rbattle <=30){
        if(battle1=battle_boss(rm,boki,students)== 1)
        {
            lms=rand()%29;
            rm->hero.name=name[lms];
            rm->hero.hp=boki->chp *2;
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            tp_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
            monmap->firstfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
            user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';      
            rbattle=rand()%100;
        }
        
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            rbattle=100;
        } 
        else if(battle1==3)
            rbattle=100;
    }
    break;
    }
    break;
case 2:
    switch (monmap->secondfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //2층 일반 몬스터와 전투
         system("clear");
        if(battle1=battle(rm,boki,user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            boki->fhp*=1.02;
            monmap->secondfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        }
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
       else if(battle1==3)
            break;
    break;
    case students:
        //학생용사들과 전투
         system("clear");
        while(rbattle <=30){
        if(battle1=battle_boss(rm,boki,students)== 1)
        {
            lms=rand()%29;
            rm->hero.name=name[lms];
            rm->hero.hp=boki->chp *2;
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            tp_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
            //여기까지 보지마
            monmap->secondfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
            //여기야 여기
            user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';      
            
            rbattle=rand()%100;
        }
        
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            rbattle=100;
        } 
        else if(battle1==3)
            rbattle= 100;
    }
    break;
    }
    break;
case 3:
    switch (monmap->thirdfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //3층 일반 몬스터와 전투
       system("clear");
       if(battle1=battle(rm,boki,user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            boki->fhp*=1.03;
        monmap->thirdfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        }
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
       else if(battle1==3)
            break;
    break;       
    case students:
        //학생용사들과 전투
         system("clear");
        while(rbattle <=30){
        if(battle1=battle_boss(rm,boki,students)== 1)
        {
            lms=rand()%29;
            rm->hero.name=name[lms];
            rm->hero.hp=boki->chp *2;
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            tp_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
            //여기까지 보지마
            monmap->thirdfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
            //여기야 여기
            user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';      
            
            rbattle=rand()%100;
        }
        
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            rbattle=100;
        } 
        else if(battle1==3)
            rbattle= 100;
    }
    break;
    }
    
    break;
case 4:
    switch (monmap->fourthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //4층 일반 몬스터와 전투
        system("clear");
        if(battle1=battle(rm,boki,user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            drop_2teer20(boki);
            boki->fhp*=1.05;
        monmap->fourthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        }
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
      else if(battle1==3)
            break;
    break;       
    case students:
        //학생용사들과 전투
        system("clear");
        while(rbattle <=30){
        if(battle1=battle_boss(rm,boki,students)== 1)
        {
            lms=rand()%29;
            rm->hero.name=name[lms];
            rm->hero.hp=boki->chp *2;
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            tp_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
            //여기까지 보지마
            monmap->fourthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
            //여기야 여기
            user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';      
            rbattle=rand()%100;
        }
        
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            rbattle=100;
        } 
        else if(battle1==3)
            rbattle= 100;
    }
    break;
    } 
break;
case 5:
    switch (monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]])
    {
    case nomal:
        //5층 일반 몬스터와 전투
        system("clear");
        if(battle1=battle(rm,boki,user->floorcount[0],nomal)== 1)
        {
            gold_drop(boki,user->floorcount[0]);
            town_movement(boki);
            drop_2teer20(boki);
            boki->fhp*=1.07;
        monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        }
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
      else if(battle1==3)
            break;
    break;       
    case students:
        //학생용사들과 전투
        system("clear");
       while(rbattle <=30){
       if(battle1=battle_boss(rm,boki,students)== 1)
        {
            gold_drop_boss(boki,students-1);
            town_movement(boki);
            tp_movement(boki);
            drop_2teer20(boki);
            drop_3teer20(boki);
            boki->fhp*=1.20;
        monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        rbattle=rand()%100;
        }
        if(boki->chp <= 0 || battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
           rbattle=100;
        }
    else if(battle1==3)
       rbattle=100;
    }
    break;
    case baphomet:
        //바포메트와 전투
        system("clear");
        if(battle1=battle_boss(rm,boki,baphomet)== 1)
        {
            gold_drop_boss(boki,baphomet-1);
            drop_3teer20(boki);
            tp_movement(boki);
            drop_4teer5(boki);

            boki->fhp*=1.30;
            monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
            user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
            rbattle=rand()%100;
            if(rbattle<=20){
                if(battle1=battle_boss(rm,boki,students)== 1)
                    {
                        gold_drop_boss(boki,students-1);
                        town_movement(boki);
                        tp_movement(boki);
                        drop_2teer20(boki);
                        drop_3teer20(boki);
                        boki->fhp*=1.20;
                    monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
                    user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
                    break;
                    }
                if(boki->chp <= 0 ||battle1 ==0)
                    {
                        boki->chp=boki->fhp*0.1;
                        user->floorcount[0]=0;
                        user->userPoint[0]=0;
                        user->userPoint[1]=0;
                        user->fcinterrupt[0]=-1;      
                    break;
                    }
                    }
       
        }
    if(boki->chp <= 0 ||battle1 ==0)
    {
        boki->chp=boki->fhp*0.1;
        user->floorcount[0]=0;
        user->userPoint[0]=0;
        user->userPoint[1]=0;
        user->fcinterrupt[0]=-1;      
            break;
    }
        else if(battle1==3)
            break;
    break;
    case lee:
        //리얼보스와 전투
        system("clear");
        if(battle1=battle_boss(rm,boki,lee)== 1)
        {
            gold_drop_boss(boki,lee-1);
            drop_3teer20(boki);
            tp_movement(boki);
            drop_4teer10(boki);
            elixir_drop(boki,rm,lee);
        boki->fhp*=1.60;
        monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
        user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
        rbattle=rand()%100;
        if(rbattle<=20){
            if(battle1=battle_boss(rm,boki,students)== 1)
                {
                    gold_drop_boss(boki,students-1);
                    town_movement(boki);
                    tp_movement(boki);
                    drop_2teer20(boki);
                    drop_3teer20(boki);
                    boki->fhp*=1.20;
                monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
                user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
                break;
                }
            if(boki->chp <= 0 ||battle1 ==0)
                {
                    boki->chp=boki->fhp*0.1;
                    user->floorcount[0]=0;
                    user->userPoint[0]=0;
                    user->userPoint[1]=0;
                    user->fcinterrupt[0]=-1;      
                break;
                }
        }
        
        }
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
              break;
        }
        else if(battle1==3)   
            break;
    break;
    case ryu:
        //찐막보스와 전투
        system("clear");
        if(battle1=battle_boss(rm,boki,ryu)== 1)
        {
            gold_drop_boss(boki,ryu-1);
            drop_3teer30(boki);
            tp_movement(boki);
            drop_4teer20(boki);
            elixir_drop(boki,rm,ryu);
            boki->fhp*=2.00;
            monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
            user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
            rbattle=rand()%100;
                                            if(rbattle<=20){
                                                if(battle1=battle_boss(rm,boki,students)== 1)
                                                    {
                                                        gold_drop_boss(boki,students-1);
                                                        town_movement(boki);
                                                        tp_movement(boki);
                                                        drop_2teer20(boki);
                                                        drop_3teer20(boki);
                                                        boki->fhp*=1.20;
                                                    monmap->fifthfloor.monstermaps[user->userPoint[0]][user->userPoint[1]]=empty;
                                                    user->userInterFaceMap[user->userPoint[0]][user->userPoint[1]] =' ';
                                                    break;
                                                    }
                                                if(boki->chp <= 0 ||battle1 ==0)
                                                    {
                                                        boki->chp=boki->fhp*0.1;
                                                        user->floorcount[0]=0;
                                                        user->userPoint[0]=0;
                                                        user->userPoint[1]=0;
                                                        user->fcinterrupt[0]=-1;      
                                                    break;
                                                    }
                                                    }
        }
        if(boki->chp <= 0 ||battle1 ==0)
        {
            boki->chp=boki->fhp*0.1;
            user->floorcount[0]=0;
            user->userPoint[0]=0;
            user->userPoint[1]=0;
            user->fcinterrupt[0]=-1;      
            break;
        }
        else if(battle1==3)
            break;
    break;
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
        copymap[1][1]=empty;
        memcpy(monmap->firstfloor.monstermaps,copymap,sizeof(int)*2500);
        for (int k = 0; k < 50; k++){
            for (int z = 0; z < 50; z++)
            {
                if(monmap->firstfloor.monstermaps[k][z]==empty)
                    user->userInterFaceMap[k][z]=' ';
                else if((monmap->firstfloor.monstermaps[k][z]==nomal))
                    user->userInterFaceMap[k][z]='?'; 
                else if((monmap->firstfloor.monstermaps[k][z]==students))
                    user->userInterFaceMap[k][z]='!';
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
        copymap[1][1]=empty;
        memcpy(monmap->secondfloor.monstermaps,copymap,sizeof(int)*2500);
        for (int k = 0; k < 50; k++){
            for (int z = 0; z < 50; z++)
            {
                    if(monmap->secondfloor.monstermaps[k][z]==empty)
                        user->userInterFaceMap[k][z]=' ';
                    else if((monmap->secondfloor.monstermaps[k][z]==nomal))
                        user->userInterFaceMap[k][z]='?';
                    else if((monmap->secondfloor.monstermaps[k][z]==students))
                         user->userInterFaceMap[k][z]='!';
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
        copymap[1][1]=empty;
        memcpy(monmap->thirdfloor.monstermaps,copymap,sizeof(int)*2500);
        for (int k = 0; k < 50; k++){
            for (int z = 0; z < 50; z++)
            {
            if(monmap->thirdfloor.monstermaps[k][z]==empty)
                user->userInterFaceMap[k][z]=' ';
            else if((monmap->thirdfloor.monstermaps[k][z]==nomal))
                        user->userInterFaceMap[k][z]='?';
            else if((monmap->thirdfloor.monstermaps[k][z]==students))
                    user->userInterFaceMap[k][z]='!';
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
        copymap[1][1]=empty;
        memcpy(monmap->fourthfloor.monstermaps,copymap,sizeof(int)*2500);
        for (int k = 0; k < 50; k++){
            for (int z = 0; z < 50; z++)
            {
                    if(monmap->fourthfloor.monstermaps[k][z]==empty)
                        user->userInterFaceMap[k][z]=' ';
                else if((monmap->fourthfloor.monstermaps[k][z]==nomal))
                    user->userInterFaceMap[k][z]='?';
                else if((monmap->fourthfloor.monstermaps[k][z]==students))
                        user->userInterFaceMap[k][z]='!';
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
                if(mmr<30)
                    copymap[i][j]=students;
                
                else if(mmr>=30&&mmr<=50)
                    copymap[i][j]=nomal;
                
                else if(mmr>=51 && mmr<=60)
                    copymap[i][j]=baphomet;
                
                else if(mmr>=61 && mmr<=75)
                    copymap[i][j]=lee;
                
                else if (mmr>=76&&mmr<=89)
                    copymap[i][j]=ryu;
                else 
                    copymap[i][j]=empty;
            }
        }
    copymap[1][1]=empty;
    memcpy(monmap->fifthfloor.monstermaps,copymap,sizeof(int)*2500);
    for (int k = 0; k < 50; k++)
    {
        for (int z = 0; z < 50; z++)
        {
             if(monmap->fifthfloor.monstermaps[k][z]==empty)
                user->userInterFaceMap[k][z]=' ';
            else if((monmap->fifthfloor.monstermaps[k][z]==nomal))
                        user->userInterFaceMap[k][z]='?';
            else if((monmap->fifthfloor.monstermaps[k][z]==students))
                    user->userInterFaceMap[k][z]='!';
            else if((monmap->fifthfloor.monstermaps[k][z]==baphomet))
                        user->userInterFaceMap[k][z]='+';
            else if((monmap->fifthfloor.monstermaps[k][z]==lee))
                    user->userInterFaceMap[k][z]='%';
            else if((monmap->fifthfloor.monstermaps[k][z]==ryu))
                        user->userInterFaceMap[k][z]='~';
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
    "김승수","김영곤","김재신","김혜빈","노주영","박민건","박선후"
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
return rm;
}

//무기 강화함수
void WReinForcement(Boki* boki,int count,int armed,int elixir)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    if(elixir == 1)
        aaaa=9;
    if(aaaa>=8){
        printf("강화성공!\n");
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
        printf("저런...강화실패...\n");
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
void FDepReinForce(Boki* boki,int count,int armed,int elixir)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    if(elixir == 1)
        aaaa=9;
    if(aaaa>=8){
        printf("강화성공!\n");
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
        printf("저런...강화실패...\n");
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
void SDepReinForce(Boki* boki,int count,int armed,int elixir)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    if(elixir == 1)
        aaaa=9;
    if(aaaa>=8){
        printf("강화성공!\n");
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
        printf("저런...강화 실패..\n");
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
void TDepReinForce(Boki* boki,int count,int armed,int elixir)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    if(elixir == 1)
        aaaa=9;
    if(aaaa>=8){
        printf("강화성공!\n");
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
        printf("저런...강화 실패...\n");
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
void FoDepReinForce(Boki* boki,int count,int armed,int elixir)
{
    srand(time(NULL));
    int aaaa=rand()%10;
    if(elixir == 1)
        aaaa=9;
    if(aaaa>=8){
        printf("강화성공!\n");
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
        printf("저런...강화실패...\n");
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

//공격력 방어력 초기화
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

void TownBack(Boki* boki, User* user)
{
    user->floorcount[0] = 0;
    user->fcinterrupt[0] = -1;
    user->userPoint[0] = 4;
    user->userPoint[1] = 5;
}

Boki* BokiInitialization(Boki* boki)
{
    
    boki=(Boki*)malloc(sizeof(Boki));
    memset(boki,0,sizeof(Boki));
    
    boki->fhp=300;
    boki->chp=boki->fhp;
    boki->damage=0;
    boki->def=0;
    boki->gold=300;
    boki->bokiEquipment.weapon.basicsword[0][0]=1;
    boki->bokiEquipment.nomal.basicarmor[0][0]=1;
    boki->bokiEquipment.nomal.basicboots[0][0]=1;
    boki->bokiEquipment.nomal.basiccape[0][0]=1;
    boki->bokiEquipment.nomal.basicgloves[0][0]=1;
    boki->bokiEquipment.nomal.basicmask[0][0]=1;
    itemInitialization(boki);
    memset(boki->tpCoordinate,-1,sizeof(coordinate)*7);
return boki;
}

void consume_window(Boki* boki,User* user)
{
    system("clear");
    printf("아이템을 사용\n");
    printf("1)빨간물약\t\t2)주황물약\n3)맑은물약\t\t4)고농도물약\n5)마을이동주문서\t\t6)장비강화주문서\n"
            "7)순간이동주문서\t\t8)엘릭서\n");
    
    char a;
    int item_choice;
    printf("선택:");
    a=getchar();
    item_choice=atoi(&a);
    switch (item_choice)
    {
    case 1:
    if(boki->consume.potion.redpotion>0)
    {
        printf("빨간물약을 사용합니다.");
        boki->consume.potion.redpotion--;
        boki->chp+=30;
        if(boki->chp>=boki->fhp)
        {
            boki->chp=boki->fhp;
        }
        printf("남은 빨간물약 %d개\n",boki->consume.potion.redpotion);
        printf("사용후체력%d\n",boki->chp);
        
    }
    break;
    case 2:
    if(boki->consume.potion.orangepotion>0)
    {
        printf("주황물약을 사용합니다.\n");
        boki->consume.potion.orangepotion--;
        boki->chp+=50;
        if(boki->chp>=boki->fhp)
        {
            boki->chp=boki->fhp;
        }
        printf("남은 주황물약 %d개\n",boki->consume.potion.orangepotion);
        printf("사용후체력%d\n",boki->chp);
        
    }
    break;
    case 3:
    if(boki->consume.potion.purepotion>0)
    {
        printf("맑은물약을 사용합니다.\n");
        boki->consume.potion.purepotion--;
        boki->chp+=70;
        if(boki->chp>=boki->fhp)
        {
            boki->chp=boki->fhp;
        }
        printf("남은 맑은물약 %d개\n",boki->consume.potion.purepotion);
        printf("사용후체력%d\n",boki->chp);
    }
    break;
    case 4:
    if(boki->consume.potion.highpotion>0)
    {
        printf("고농도물약을 사용합니다.\n");
        boki->consume.potion.highpotion--;
        boki->chp+=150;
        if(boki->chp>=boki->fhp)
        {
            boki->chp=boki->fhp;
        }
        printf("남은 고농도물약 %d개\n",boki->consume.potion.highpotion);
        printf("사용후체력%d\n",boki->chp);
    }
    break;
    case 5:
    if(boki->consume.scroll.tmscrollpaper>0)
    {
        printf("마을이동주문서를 사용합니다.\n");
        boki->consume.scroll.tmscrollpaper--;
        TownBack(boki,user);
        printf("남은 마을 이동주문서 %d개\n",boki->consume.scroll.tmscrollpaper);
    }
    break;
    case 6:
    if(boki->consume.scroll.ermagicscroll>0)
    {
        printf("장비강화주문서를 사용합니다.\n");
        boki->consume.scroll.ermagicscroll--;
        reinforce(boki);
        equip(boki);
        printf("남은 장비강화주문서 %d개\n",boki->consume.scroll.ermagicscroll);
    }
    break;
    case 7:
        if(boki->consume.scroll.teleportscroll>0)
    {
        printf("순간이동주문서를 사용합니다.\n");
        boki->consume.scroll.teleportscroll--;
        TpsUseMove(user,boki);
        printf("남은 순간이동주문서 %d개\n",boki->consume.scroll.teleportscroll);
    }
    break;
    case 8:
        if(boki->consume.elixir>0)
    {
        printf("엘릭서를 사용합니다.\n");
        boki->consume.elixir--;
        Ereinforce(boki);
        equip(boki);
        printf("남은 엘릭서 %d개\n",boki->consume.elixir);
    }
    break;
    default:
        break;
    }

}

void TpsSave(User* user,Boki* boki)
{
    for (int i = 0; i < 7; i++)
    {
       if(boki->tpCoordinate[i].floorInfo ==-1){
        boki->tpCoordinate[i].floorInfo=user->floorcount[0];
        boki->tpCoordinate[i].userTpInfo[0]=user->userPoint[0];
        boki->tpCoordinate[i].userTpInfo[1]=user->userPoint[1];
        printf("해당좌표를 %d번째에 저장했습니다.\n",i);        
        break;
       }
    else
        {
            printf("모든 순간이동 좌표가 가득찼습니다.\n");
        }
    }       
}

void TpsUseMove(User* user,Boki* boki)
{
    char b;
    printf("어떤 좌표로 이동하시겠습니까?\n");
    sleep(1);
    for (int i = 0; i < 7; i++)
    {
       if(boki->tpCoordinate[i].floorInfo !=-1)
       {
        printf("%d번째좌표 %d층 %d , %d 좌표로 이동하라면 %d를 눌러주세요\n",i,boki->tpCoordinate[i].floorInfo,
        boki->tpCoordinate[i].userTpInfo[0],boki->tpCoordinate[i].userTpInfo[1],i);
       }      
    }
    b = getchar();
    int a = atoi(&b);
    if(boki->tpCoordinate[a].floorInfo !=-1)
    {
        printf("%d번\n",a);
        user->floorcount[0]=boki->tpCoordinate[a].floorInfo;
        user->fcinterrupt[0]=-1;
        user->userPoint[0]=boki->tpCoordinate[a].userTpInfo[0];
        user->userPoint[1]=boki->tpCoordinate[a].userTpInfo[1];
        printf("이동완료!\n");
    }

    else
    {
        printf("잘못된 좌표를 입력하셨습니다.\n");
    }
}

int elixir_drop(Boki* boki,Monster* monster,int a)
{
    // boki->consume.elixir;
    srand(time(NULL));
    int get_elixir;
    int chance_elixir;
    chance_elixir=rand()%101;
    switch (a)
    {
    case 4:
    if (chance_elixir<=10)
    {
        get_elixir=rand()%3+1;
        boki->consume.elixir+=get_elixir;
        printf("엘릭서 %d개 획득\n",get_elixir);
        break;
    }
    else
        printf("X");
    break;

    case 5:
    if (chance_elixir<=20)
    {
        get_elixir=rand()%3+1;
        boki->consume.elixir+=get_elixir;
        printf("엘릭서 %d개 획득\n",get_elixir);
    }
        break;

    default:
        get_elixir=0;
        printf("엘릭서를 획득하지 못했습니다.\n");

        break;
    }

    return get_elixir;
}

void Pandora(Boki* boki)
{
    char a;
    int b;
    int c;
    system("clear");
    printf("무엇을 구매하시겠습니까?\n");
    printf("1)빨간물약: 30골드\t 2)주황물약: 50골드\t 3)맑은물약: 100골드\t 4)고농도 물약:200골드\t \
    5)마을 이동 주문서: 100골드\t 6)장비");
    a=getchar();
    
    b=atoi(&a);

    switch (b)
    {
    case 1:
    if(boki->gold>=30){
        printf("빨간물약 구매 완료!");
        boki->gold-=30;
        boki->consume.potion.redpotion +=1;
    }
    else
    {
        printf("돈이 없습니다.\n");
    }    
        break;
    case 2:
    if(boki->gold>=50){
        printf("주황 물약 구매 완료!");
        boki->gold-=50;
        boki->consume.potion.orangepotion +=1;
    }
    else
    {
        printf("돈이 없습니다.\n");
    }        break;
    case 3:
    if(boki->gold>=100){
        printf("맑은 물약 구매 완료!");
        boki->gold-=100;
        boki->consume.potion.purepotion +=1;
    }
    else
    {
        printf("돈이 없습니다.\n");
    }
    break;

    case 4:
    if(boki->gold>=200){
        printf("고농축 물약 구매 완료!");
        boki->gold-=200;
        boki->consume.potion.highpotion +=1;
    }
    else
    {
        printf("돈이 없습니다.\n");
    }
        break;
    case 5:
    if(boki->gold>=100){
        printf("마을이동 주문서 구매 완료!");
        boki->gold-=100;
        boki->consume.scroll.tmscrollpaper +=1;
    }
    else
    {
        printf("돈이 없습니다.\n");
    }
        break;
    case 6:
     system("clear");
    printf("무엇을 구매하시겠습니까?\n");
    printf("1)기본갑빠: 30골드\t 2)기본장화: 30골드\t 3)기본망토: 30골드\t 4)기본장갑:30골드\t \
    5)기본 마스크:30골드\t 6)기본검:30골드\t");
    a=getchar();
    c=atoi(&a);
    switch (c)
    {
    case 1:
    if(boki->gold>=30){
        printf("기본갑빠 구매 완료!");
        boki->gold-=30;
        for (int i = 0; i < 5; i++)
        {
            if (boki->bokiEquipment.nomal.basicarmor[i][0] ==0){
                 boki->bokiEquipment.nomal.basicarmor[i][0] =1;
        break;
        }
        }
    }
    else
    {
        printf("돈이 없습니다.\n");
    }    
        break;
    case 2:
    if(boki->gold>=30){
        printf("기본장화 구매 완료!");
        boki->gold-=30;
        for (int i = 0; i < 5; i++)
        {
            if (boki->bokiEquipment.nomal.basicboots[i][0] ==0){
                 boki->bokiEquipment.nomal.basicboots[i][0] =1;
        break;
        }
        
        }
    }
    else
    {
        printf("돈이 없습니다.\n");
    }    
        break;
    case 3:
     if(boki->gold>=30){
        printf("기본망토 구매 완료!");
        boki->gold-=30;
        for (int i = 0; i < 5; i++)
        {
            if (boki->bokiEquipment.nomal.basiccape[i][0] ==0){
                 boki->bokiEquipment.nomal.basiccape[i][0] =1;
        break;
        }

        }
    }
    else
    {
        printf("돈이 없습니다.\n");
    }    
        break;
    case 4:
    if(boki->gold>=30){
        printf("기본장갑 구매 완료!");
        boki->gold-=30;
        for (int i = 0; i < 5; i++)
        {
            if (boki->bokiEquipment.nomal.basicgloves[i][0] ==0){
                 boki->bokiEquipment.nomal.basicgloves[i][0] =1;
        break;
        }

        }
    }
    else
    {
        printf("돈이 없습니다.\n");
    }    
    break;
    case 5:
    if(boki->gold>=30){
        printf("기본마스크 구매 완료!");
        boki->gold-=30;
        for (int i = 0; i < 5; i++)
        {
            if (boki->bokiEquipment.nomal.basicmask[i][0] ==0){
                 boki->bokiEquipment.nomal.basicmask[i][0] =1;
        break;
        }

        }
    }
    else
    {
        printf("돈이 없습니다.\n");
    }    
    break;
    case 6:
    if(boki->gold>=30){
        printf("기본검 구매 완료!");
        boki->gold-=30;
        for (int i = 0; i < 5; i++)
        {
            if (boki->bokiEquipment.weapon.basicsword[i][0] ==0){
                 boki->bokiEquipment.weapon.basicsword[i][0] =1;
        break;
        }

        }
    }
    else
    {
        printf("돈이 없습니다.\n");
    }    
    break;
    default:
    printf("다른건 안팝니다.\n");
    break;
    }

    break;
    default:
        printf("다른건 안팝니다.\n");
        break;
    }
sleep(1);
}

void Prist(Boki* boki)
{
    char a;
    int b;
    system("clear");
    printf("성소입니다. 피 채울까요? y or n\n");
    a=getchar();
    switch (a)
    {
    case 121:
        printf("다 채움\n");
        boki->chp=boki->fhp;
        printf("보키 현재 체력: %d ",boki->chp);    
        break;
    
    case 110:
        printf("안 채움\n");
        break;
    
    default:
        break;
    }
    sleep(1);
}

void Dwarf(Boki* boki)
{
    char a;
    int b;
    system("clear");
    printf("무엇을 구매하시겠습니까?\n");
    printf("1)장비 강화 주문서 \t");
    a=getchar();
    b=atoi(&a);
    switch (b)
    {
    case 1:
    if(boki->gold>=300){
        printf("장비 강화 주문서 구매 완료!");
        boki->gold-=300;
        boki->consume.scroll.ermagicscroll +=1;
    }
    else
    {
        printf("돈이 없습니다.\n");
    }    
        break;
    default:
        printf("다른건 안팝니다.\n");
        break;
    }
sleep(1);
}

int battle(Monster *monster, Boki *boki, int floor, int monstername) // 스위치 사용해서 몬스터네임이 1로 들어오면 1층애들만난다.  학생용사가 2, int battleboss
{ 
    while (1)
    {   
        printf("1.전투\n2.물약사용\n3.도망 \n");
        int choice;
        char aaaa;
        int item_choice;
        while (1)
        {
        aaaa=getchar();
        choice=atoi(&aaaa);    
        if(choice==1||choice==2||choice==3)
        {
            break;
        }
        }
        
        if(choice==1)
        {
            switch (floor)
            {
            case 1://오크전사
                    monster->oaks_warrior.hp -= boki->damage; // 유저의 공격
                    printf("오크전사 남은 hp %d\n", monster->oaks_warrior.hp);
                    printf("boki %d체력\n", boki->chp);
                    boki->chp -= monster->oaks_warrior.damage; //몬스터의 공격
                    printf("boki 남은 hp %d\n", boki->chp);
                        if (monster->oaks_warrior.hp <= 0) //몬스터가 죽었을 때
                            {
                                printf("승리했습니다.\n"); // 승리 메세지 출력
                                return 1;
                            }
                        else if (boki->chp <= 0)
                            {
                                printf("패배했습니다.\n"); //패배 메세지 출력
                                return 0;
                            }
                    else if (monster->oaks_warrior.hp > 0) //몬스터가 살아 있으면 콘티뉴
                        break;
            case 2://좀비
                    monster->zombie.hp -= boki->damage;
                    printf("좀비 남은 hp %d\n", monster->zombie.hp);
                    printf("boki %d체력\n", boki->chp);
                    boki->chp -= monster->zombie.damage;
                    printf("boki 남은 hp %d\n", boki->chp);
                    if (monster->zombie.hp <= 0)
                        {
                            printf("승리했습니다.\n");
                            return 1;
                        }
                    else if (boki->chp <= 0)
                        {
                            printf("패배했습니다.\n");
                            return 0;
                        }
                    else if (monster->zombie.hp > 0)
                        break;
            case 3: // 구울 전투
                    monster->ghoul.hp -= boki->damage;
                    printf("구울 남은 hp %d\n", monster->ghoul.hp);
                    printf("boki %d체력\n", boki->chp);
                    boki->chp -= monster->ghoul.damage;
                    printf("boki 남은 hp %d\n", boki->chp);
                    if (monster->ghoul.hp <= 0)
                        {
                            printf("승리했습니다.\n");
                            return 1;
                        }
                    else if (boki->chp <= 0)
                        {
                            printf("패배했습니다.\n");
                            return 0;
                        }
                    else if (monster->ghoul.hp > 0)
                        break;
            case 4:// 스켈레톤 전투
                    monster->skeleton.hp -= boki->damage;
                    printf("스켈레톤 남은 hp %d\n", monster->skeleton.hp);
                    printf("boki %d체력\n", boki->chp);
                    boki->chp -= monster->skeleton.damage;
                    printf("boki 남은 hp %d\n", boki->chp);
                    if (monster->skeleton.hp <= 0)
                        {
                            printf("승리했습니다.\n");
                            return 1;
                        }
                    else if (boki->chp <= 0)
                        {
                            printf("패배했습니다.\n");
                            return 0;
                        }
                    else if (monster->skeleton.hp > 0)
                        break;
            case 5://스파토이
                monster->spartoi.hp -= boki->damage;
                    printf("스파토이 남은 hp %d\n", monster->spartoi.hp);
                    printf("boki %d체력\n", boki->chp);
                    boki->chp -= monster->spartoi.damage;
                    printf("boki 남은 hp %d\n", boki->chp);
                    if (monster->spartoi.hp <= 0)
                        {
                            printf("승리했습니다.\n");
                            return 1;
                        }
                    else if (boki->chp <= 0)
                        {
                            printf("패배했습니다.\n");
                            return 0;
                        }
                    else if (monster->spartoi.hp > 0)
                        break;
            default:
                break;

            }
        }
        else if(choice==2)//물약 사용
        {
            char lk;
            int item_choice;
            printf("\n아이템을 선택해주세요\n 1.빨간물약 2.주황물약 3.맑은물약 4.고농도물약\n ");
            lk=getchar();
            item_choice=atoi(&lk);
            switch(item_choice)
            {
                case 1: //빨간물약
                {
                    if (boki->consume.potion.redpotion>0)
                    {
                        boki->consume.potion.redpotion -= 1;
                        printf("빨간물약을 사용합니다. 남은 빨간물약개수:%d\n", boki->consume.potion.redpotion);
                        boki->chp +=30;

                        if(boki->chp > boki->fhp)
                        {
                            boki->chp = boki->fhp;
                        }
                        printf("현재HP:%d\n", boki->chp);
                        battle_attack(monster, boki, floor,monstername);
                        choice=0;    
                    }
                    break;
                }
                case 2: //주황포션
                {
                    if (boki->consume.potion.orangepotion>1)
                    {
                        boki->consume.potion.orangepotion -= 1;
                        printf("주황물약을 사용합니다. 남은 주황물약개수:%d\n", boki->consume.potion.orangepotion);
                        boki->chp = boki->chp+50;
                        if(boki->chp > boki->fhp)
                        {
                            boki->chp = boki->fhp;
                        }
                        printf("현재HP:%d\n", boki->chp);
                        battle_attack(monster, boki, floor,monstername);
                        choice=0;
                    }
                    break;
                }                    
                case 3: //맑은물약
                {
                    if (boki->consume.potion.purepotion>1)
                    {
                        boki->consume.potion.purepotion -= 1;
                        printf("맑은물약을 사용합니다. 남은 맑은물약개수:%d\n", boki->consume.potion.purepotion);
                        boki->chp = boki->chp+70;
                        if(boki->chp > boki->fhp)
                        {
                            boki->chp = boki->fhp;
                        }
                        printf("현재HP:%d\n", boki->chp);
                        battle_attack(monster, boki, floor,monstername);
                        choice=0;
                    }
                    break;
                }                    
                case 4: //고농도물약
                {
                    if (boki->consume.potion.redpotion>1)
                    {
                        boki->consume.potion.redpotion -= 1;
                        printf("고농도물약을 사용합니다. 남은 고농도물약개수:%d\n", boki->consume.potion.highpotion);
                        boki->chp = boki->chp+150;
                        if(boki->chp > boki->fhp)
                        {
                            boki->chp = boki->fhp;
                        }
                        printf("현재HP:%d\n", boki->chp);
                        battle_attack(monster, boki, floor,monstername);
                        choice=0;
                    }
                break; 
                }
                
                default:
                    break;
                    
            }
        }
        else if(choice == 3) //도망가기
        {
            srand(time(NULL));
            int random = rand()%100+1; //1부터 100까지 출력
            if (random <= 30) //1부터 30까지 랜덤수
                {
                    printf("%d, 도망성공\n", random);
                    return 3;
                }
            else
            {
                printf("%d 도망실패\n", random);
            }
            
        }
    }
}    

int battle_boss(Monster *monster, Boki *boki,int monstername)
{
    while (1)

    {
        boki->chp;
        printf("1.전투\n2.물약 사용\n3.도망 \n");
        char aaaa;
        int choice;
        int item_choice;
         while (1)
        {
        aaaa=getchar();
        choice=atoi(&aaaa);    
        if(choice==1||choice==2||choice==3)
        {
            break;
        }
        }
        if(choice==1)
        switch (monstername)
        {
            case 2: 
                monster->hero.hp-= boki->damage;
                printf("%s 남은 hp %d\n",monster->hero.name,monster->hero.hp);
                printf("boki %d체력\n", boki->chp);
                boki->chp -= monster->hero.damage;
                printf("boki 남은 hp %d\n", boki->chp);
                if (monster->hero.hp <= 0)
                {
                    printf("승리했습니다.\n");
                    return 1;
                }
                else if (boki->chp <= 0)
                {
                    printf("패배했습니다.\n");
                    return 0;
                }
                else if (monster->hero.hp > 0)
                    break;

            case 3:
                monster->Baphomet.hp -= boki->damage;
                printf("baphomet 남은 hp %d\n", monster->Baphomet.hp);
                printf("boki %d체력\n", boki->chp);
                boki->chp -= monster->Baphomet.damage;
                printf("boki 남은 hp %d\n", boki->chp);
                if (monster->Baphomet.hp <= 0)
                {
                    printf("승리했습니다.\n");
                    return 1;
                }
                else if (boki->chp <= 0)
                {
                    printf("패배했습니다.\n");
                    return 0;
                }
                else if (monster->Baphomet.hp > 0)
                    break;
            case 4:
                monster->boss.hp-=boki->damage;
                printf("lee 남은 hp %d\n",monster->boss.hp);
                printf("boki %d체력", boki->chp);
                boki->chp -= monster->boss.damage;
                printf("boki 남은 hp %d\n", boki->chp);
                if (monster->boss.hp <= 0)
                {
                    printf("승리했습니다.\n");
                    return 1;
                }
                else if (boki->chp <= 0)
                {
                    printf("패배했습니다.\n");
                    return 0;
                }
                else if (monster->boss.hp > 0)
                    break;
            case 5:
                monster->realboss.hp-=boki->damage;
                printf("ryu 남은 hp %d\n",monster->realboss.hp);
                printf("boki %d체력\n", boki->chp);
                boki->chp -= monster->realboss.damage;
                printf("boki 남은 hp %d\n", boki->chp);
                if (monster->realboss.hp <= 0)
                {
                    printf("승리했습니다.\n");
                    return 1;
                }
                else if (boki->chp <= 0)
                {
                    printf("패배했습니다.\n");
                    return 0;
                }
                else if (monster->realboss.hp > 0)
                    break;
            default:
                break;
        }
        else if(choice==2)//물약 사용
        {
            int item_choice;
            printf("\n아이템을 선택해주세요\n 1.빨간물약 2.주황물약 3.맑은물약 4.고농도물약\n ");
            aaaa =getchar();
            item_choice=atoi(&aaaa);
            switch(item_choice)
            {
                case 1: //빨간물약
                {
                    if (boki->consume.potion.redpotion>0)
                    {
                        boki->consume.potion.redpotion -= 1;
                        printf("빨간물약을 사용합니다. 남은 빨간물약개수:%d\n", boki->consume.potion.redpotion);
                        boki->chp +=30;

                        if(boki->chp > boki->fhp)
                        {
                            boki->chp = boki->fhp;
                        }
                        printf("현재HP:%d\n", boki->chp);
                        battle_boss_attack(monster,boki,monstername);
                        choice=0;    
                    }
                    break;
                }
                case 2: //주황포션
                {
                    if (boki->consume.potion.orangepotion>1)
                    {
                        boki->consume.potion.orangepotion -= 1;
                        printf("주황물약을 사용합니다. 남은 주황물약개수:%d\n", boki->consume.potion.orangepotion);
                        boki->chp = boki->chp+50;
                        if(boki->chp > boki->fhp)
                        {
                            boki->chp = boki->fhp;
                        }
                        printf("현재HP:%d\n", boki->chp);
                        battle_boss_attack(monster,boki,monstername);
                        choice=0;
                    }
                    break;
                }                    
                case 3: //맑은물약
                {
                    if (boki->consume.potion.purepotion>1)
                    {
                        boki->consume.potion.purepotion -= 1;
                        printf("맑은물약을 사용합니다. 남은 맑은물약개수:%d\n", boki->consume.potion.purepotion);
                        boki->chp = boki->chp+70;
                        if(boki->chp > boki->fhp)
                        {
                            boki->chp = boki->fhp;
                        }
                        printf("현재HP:%d\n", boki->chp);
                        battle_boss_attack(monster,boki,monstername);
                        choice=0;
                    }
                    break;
                }                    
                case 4: //고농도물약
                {
                    if (boki->consume.potion.redpotion>1)
                    {
                        boki->consume.potion.redpotion -= 1;
                        printf("고농도물약을 사용합니다. 남은 고농도물약개수:%d\n", boki->consume.potion.highpotion);
                        boki->chp = boki->chp+150;
                        if(boki->chp > boki->fhp)
                        {
                            boki->chp = boki->fhp;
                        }
                        printf("현재HP:%d\n", boki->chp);
                        battle_boss_attack(monster,boki,monstername);
                        choice=0;
                    }
                break; 
                }
                
                default:
                    break;
                    
            }
        }
        else if(choice == 3) //도망가기
        {
            srand(time(NULL));
            int random = rand()%100+1; //1부터 100까지 출력
            if (random <= 30) //1부터 30까지 랜덤수
                {
                    printf("%d, 도망성공\n", random);
                    return 3;
                }
            else
            {
                printf("%d 도망실패\n", random);
            }
            
        }
    
    }
}    
    
void battle_boss_attack(Monster *monster, Boki *boki,  int monstername)
{
    switch (monstername)
    {
        case 2:
            boki->chp -= monster->hero.damage;
            printf("boki 남은 hp %d\n", boki->chp);
            break;
        case 3:
            boki->chp -= monster->Baphomet.damage;
            printf("boki 남은 hp %d\n", boki->chp);
            break;
        case 4:
            boki->chp -= monster->boss.damage;
            printf("boki 남은 hp %d\n", boki->chp);
            break;
        case 5:
            boki->chp -= monster->realboss.damage;
            printf("boki 남은 hp %d\n", boki->chp);
            break;
        default:
            break;
    }
}


void battle_attack(Monster *monster, Boki *boki, int floor, int monstername)
{ 


    switch (floor)
    {
    case 1://오크전사
            boki->chp -= monster->oaks_warrior.damage; //몬스터의 공격
            printf("boki 남은 hp %d\n", boki->chp);
            break;
    case 2://좀비
            boki->chp -= monster->zombie.damage;
            printf("boki 남은 hp %d\n", boki->chp);
            break;
    case 3: // 구울 전투
            boki->chp -= monster->ghoul.damage;
            printf("boki 남은 hp %d\n", boki->chp);
            break;
    case 4:// 스켈레톤 전투
            boki->chp -= monster->skeleton.damage;
            printf("boki 남은 hp %d\n", boki->chp);
            break;
    case 5://스파토이
            boki->chp -= monster->spartoi.damage;
            printf("boki 남은 hp %d\n", boki->chp);
            break;
    default:
        break;

    }
}


int equip_sword(  Boki* boki){
    char aaaaaa;
  static  int depend_choice;
    
   
    // 무기장착
      while (1)
        {
        aaaaaa=getchar();
        depend_choice=atoi(&aaaaaa); //문자숫자를 진짜 숫자로 바꿔줌 근대 숫자가아니면 0반환   
        if(depend_choice==1||depend_choice==2||depend_choice==3||depend_choice==4)
        {
            break;
        }
        }
    // boki->bokiEquipment.weapon.basicsword[depend_choice][1] = 5;// 마스크 첫번째 방어구 방어력 입력 개수, 방어력, 강화
   
    // boki->bokiEquipment.weapon.basicsword[0][0] = 1;// 테스트 때문에 방어구 한개 넣어서 확인해보기
    switch(depend_choice)
        {   
            case 1 ://1티어 무기 장착하기
            static int equip_choice;
            
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.weapon.basicsword[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n 기본검 %d 번 장비의 공격력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.weapon.basicsword[i][1],boki->bokiEquipment.weapon.basicsword[i][2] );
                }
            }
            printf("번호를 입력하세요. \n");
        while (1)
        {
        aaaaaa=getchar();  
        equip_choice=atoi(&aaaaaa); //차 변수 주소로들어가서 *변수=> 1 실제 1이아니라 문자 1은 정수로 49임 그런대 이걸 함수가 그냥 정수 1로바꿔줌 
        if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
        {
            break;
        }
        } //5개중에 고르기 0~4번
            
        if(boki->bokiEquipment.weapon.basicsword[equip_choice-1][0] != 0){ 
            printf("무기가있네요\n");// 무기가 있는지 확인
            boki->damage = boki->bokiEquipment.weapon.basicsword[equip_choice-1][1]; //복이 공격력에 무기 공격력 입히기
            printf("무기를 장착했습니다.\n");
            break;
            }else{
            printf("무기가 없습니다.\n");
            break;
            }
            case 2 ://2티어 무기 장착하기 depend_choice 2
            // int equip_choice;
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.weapon.longsword[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n 장검 %d 번 장비의 공격력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.weapon.longsword[i][1],boki->bokiEquipment.weapon.longsword[i][2] );
                }
            }
            printf("번호를 입력하세요. \n");
              while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            }  //5개중에 고르기 0~4번
            if(boki->bokiEquipment.weapon.longsword[equip_choice-1][0] != 0){ // 무기가 있는지 확인
            boki->damage = boki->bokiEquipment.weapon.longsword[equip_choice-1][1]; //복이 공격력에 무기 공격력 입히기
            printf("무기를 장착했습니다.\n");
            break;
            }else{
            printf("무기가 없습니다.\n");
            break;
            }
            case 3 ://3티어 무기 장착하기
            // int equip_choice;
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.weapon.japensword[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n 일본도 %d 번 장비의 공격력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.weapon.japensword[i][1],boki->bokiEquipment.weapon.japensword[i][2] );
                }
            }
            printf("번호를 입력하세요. \n");
              while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.weapon.japensword[equip_choice-1][0] != 0){ // 무기가 있는지 확인
            boki->damage = boki->bokiEquipment.weapon.japensword[equip_choice-1][1]; //복이 공격력에 무기 공격력 입히기
            printf("무기를 장착했습니다.\n");
            break;
            }else{
            printf("무기가 없습니다.\n");
            break;
            }
            case 4 ://1티어 무기 장착하기
            // int equip_choice;
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.weapon.nigthsword_saj[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n 싸울아비장검 %d 번 장비의 공격력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.weapon.nigthsword_saj[i][1],boki->bokiEquipment.weapon.nigthsword_saj[i][2] );
                }
            }
            printf("번호를 입력하세요. \n");
              while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.weapon.nigthsword_saj[equip_choice-1][0] != 0){ // 무기가 있는지 확인
            boki->damage = boki->bokiEquipment.weapon.nigthsword_saj[equip_choice-1][1]; //복이 공격력에 무기 공격력 입히기
            printf("무기를 장착했습니다.\n");
            break;
            }else{
            printf("무기가 없습니다.\n");
            break;
            }
    }
    return boki->damage;
}
//1티어 방어구 장착하기
int equip_mask( Boki* boki){
    char aaaaaa;
 static   int depend_choice;
    //초기화
    
    // boki->bokiEquipment.nomal.basicmask[0][1] = 0;// 테스트 때문에 방어구 한개 넣어서 확인해보기
    // printf("%d",boki->bokiEquipment.nomal.basicmask[0][1]);
    // 1티어 방어구 장착하기
      while (1)
        {
        aaaaaa=getchar();
        depend_choice=atoi(&aaaaaa);  
        if(depend_choice==1||depend_choice==2||depend_choice==3||depend_choice==4)
        {
            break;
        }
        }
    switch(depend_choice)
        {    
            case 1 ://1티어 마스크 장착하기
         static  int equip_choice;
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.nomal.basicmask[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n기본마스크 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.nomal.basicmask[i][1],boki->bokiEquipment.nomal.basicmask[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            }//5개중에 고르기 0~4번
            if(boki->bokiEquipment.nomal.basicmask[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.nomal.basicmask[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 2 ://1티어 갑바 장착하기
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.rare.k80mask[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\nk80마스크%d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.rare.k80mask[i][1],boki->bokiEquipment.rare.k80mask[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.rare.k80mask[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.rare.k80mask[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 3 ://1티어 망토 장착하기
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.epic.k94mask[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\nk94마스크 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.epic.k94mask[i][1],boki->bokiEquipment.epic.k94mask[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            }//5개중에 고르기 0~4번
            if(boki->bokiEquipment.epic.k94mask[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.epic.k94mask[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 4 ://1티어 장갑 장착하기

            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.legend.tigermask[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n타이거마스크 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.legend.tigermask[i][1],boki->bokiEquipment.legend.tigermask[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            }//5개중에 고르기 0~4번
            if(boki->bokiEquipment.legend.tigermask[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.legend.tigermask[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            boki->bokiEquipment.legend.tigermask[equip_choice][0] = 0;
            printf("%d번 방어구를 장착했습니다.\n",equip_choice);
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
    }
return boki->def;
}

//아머 장착하기
int equip_armor(  Boki* boki){
    char aaaaaa;
 static   int depend_choice;
    //초기화
   
    // 아머 장착하기    getchar(aaaaaa);
    while (1)
        {
        aaaaaa=getchar();
        depend_choice=atoi(&aaaaaa);  //티어는 4개
        if(depend_choice==1||depend_choice==2||depend_choice==3||depend_choice==4)
        {
            break;
        }
        }
    switch(depend_choice)
        {   
            case 1 :// 티어는 4개
           static int equip_choice;
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.nomal.basicarmor[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n기본갑바%d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.nomal.basicarmor[i][1],boki->bokiEquipment.nomal.basicarmor[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.nomal.basicarmor[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.nomal.basicarmor[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 2 ://1티어 갑바 장착하기
            
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.rare.halfarmor[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n반팔갑옷 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.rare.halfarmor[i][1],boki->bokiEquipment.rare.halfarmor[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            }//5개중에 고르기 0~4번
            if(boki->bokiEquipment.rare.halfarmor[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.rare.halfarmor[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 3 ://1티어 망토 장착하기
            
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.epic.hoodarmor[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n후드갑바 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.epic.hoodarmor[i][1],boki->bokiEquipment.epic.hoodarmor[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.epic.hoodarmor[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.epic.hoodarmor[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 4 :// 드래곤갑바
            
            for(int i=0; i<5; i++){
            if(boki->bokiEquipment.legend.dragonarmor[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n드래곤갑바 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.legend.dragonarmor[i][1],boki->bokiEquipment.legend.dragonarmor[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } // 5개중에 고르기 0~4번
            if(boki->bokiEquipment.legend.dragonarmor[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.legend.dragonarmor[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            } 
    }
    return boki->def;
}

//망토 장착하기
int equip_cape(  Boki* boki){
    char aaaaaa;
  static  int depend_choice;
    //초기화
   

    // 3티어 방어구 장착하기    getchar(aaaaaa);
    while (1)
        {
        aaaaaa=getchar();
        depend_choice=atoi(&aaaaaa);  //티어는 4개
        if(depend_choice==1||depend_choice==2||depend_choice==3||depend_choice==4)
        {
            break;
        }
        }
   static int equip_choice;
    switch(depend_choice)
        {   //이거이거 뭐지 이거이거 뭐니
        //1 티어 방어구를 한번에 착용하기 
        // 그렇게 하려면 어떻게 해야하지 선택을 하게해서 1티어리스트 뽑아주고 선택하게 하기 
            case 1 ://마스크 장착하기
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.nomal.basiccape[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n기본망토%d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.nomal.basiccape[i][1],boki->bokiEquipment.nomal.basiccape[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.nomal.basiccape[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.nomal.basiccape[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 2 :// 갑바 장착하기
            
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.rare.cottencape[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n천망토 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.rare.cottencape[i][1],boki->bokiEquipment.rare.cottencape[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.rare.cottencape[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.rare.cottencape[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 3 ://1티어 망토 장착하기
            
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.epic.silkcape[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n실크망토 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.epic.silkcape[i][1],boki->bokiEquipment.epic.silkcape[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.epic.silkcape[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.epic.silkcape[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 4 :// 장갑 장착하기
            
            for(int i=0; i<5; i++){
            if(boki->bokiEquipment.legend.bulletcape[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n방탄망토%d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.legend.bulletcape[i][1],boki->bokiEquipment.legend.bulletcape[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
            {
            aaaaaa=getchar();
            equip_choice=atoi(&aaaaaa);  
            if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
            {
                break;
            }
            } // 5개중에 고르기 0~4번
            if(boki->bokiEquipment.legend.bulletcape[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.legend.bulletcape[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
    }
    return boki->def;
}

//장갑 장착하기
int equip_gloves(  Boki* boki){
    char aaaaaa;
  static  int depend_choice;
    //초기화


    // 4티어 방어구 장착하기    getchar(aaaaaa);
    while (1)
        {
        aaaaaa=getchar(); //티어는 4개
        depend_choice=atoi(&aaaaaa);  
        if(depend_choice==1||depend_choice==2||depend_choice==3||depend_choice==4)
        {
            break;
        }
        }
    switch(depend_choice)
        { 
        //4 티어 방어구를 한번에 착용하기 
        // 그렇게 하려면 어떻게 해야하지 선택을 하게해서 1티어리스트 뽑아주고 선택하게 하기 
            case 1 ://4티어 마스크 장착하기
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.nomal.basicgloves[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n기본장갑%d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.nomal.basicgloves[i][1],boki->bokiEquipment.nomal.basicgloves[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
          static  int equip_choice;
            while (1)
        {
        aaaaaa=getchar();
        equip_choice=atoi(&aaaaaa);  
        if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
        {
            break;
        }
        }//5개중에 고르기 0~4번
            if(boki->bokiEquipment.nomal.basicgloves[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.nomal.basicgloves[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 2 ://4티어 갑바 장착하기
            
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.rare.rubbergloves[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n고무장갑 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.rare.rubbergloves[i][1],boki->bokiEquipment.rare.rubbergloves[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
           while (1)
        {
        aaaaaa=getchar();
        equip_choice=atoi(&aaaaaa);  
        if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
        {
            break;
        }
        }//5개중에 고르기 0~4번
            if(boki->bokiEquipment.rare.rubbergloves[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.rare.rubbergloves[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 3 ://4티어 망토 장착하기
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.epic.cottengloves[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n천장갑 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.epic.cottengloves[i][1],boki->bokiEquipment.epic.cottengloves[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
        {
        aaaaaa=getchar();
        equip_choice=atoi(&aaaaaa);  
        if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
        {
            break;
        }
        } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.epic.cottengloves[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.epic.cottengloves[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 4 ://4티어  장착하기
            
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.legend.leardergloves[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n가죽갑옷%d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.legend.leardergloves[i][1],boki->bokiEquipment.legend.leardergloves[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
           while (1)
        {
        aaaaaa=getchar();
        equip_choice=atoi(&aaaaaa);  
        if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
        {
            break;
        }
        }// 5개중에 고르기 0~4번
            if(boki->bokiEquipment.legend.leardergloves[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.legend.leardergloves[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }            
    }
    return boki->def;
}

int equip_boots(  Boki* boki){// 부츠
    char aaaaaa;
  static  int depend_choice;
    //초기화

    printf("부츠 장착창입니다..\n");
    
    // 4티어 방어구 장착하기    getchar(aaaaaa);
    while (1)
        {
        aaaaaa=getchar();
        depend_choice=atoi(&aaaaaa);  
        if(depend_choice==1||depend_choice==2||depend_choice==3||depend_choice==4)
        {
            break;
        }
        }
    switch(depend_choice)
        { 
        //4 티어 방어구를 한번에 착용하기 
        // 그렇게 하려면 어떻게 해야하지 선택을 하게해서 1티어리스트 뽑아주고 선택하게 하기 
            case 1 ://4티어 마스크 장착하기
           static int equip_choice;
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.nomal.basicboots[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n기본부츠%d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.nomal.basicboots[i][1],boki->bokiEquipment.nomal.basicboots[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
        {
        aaaaaa=getchar();
        equip_choice=atoi(&aaaaaa);  
        if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
        {
            break;
        }
        } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.nomal.basicboots[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.nomal.basicboots[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 2 ://4티어 갑바 장착하기
            
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.rare.slipper[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n슬리퍼 %d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.rare.slipper[i][1],boki->bokiEquipment.rare.slipper[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
        {
        aaaaaa=getchar();
        equip_choice=atoi(&aaaaaa);  
        if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
        {
            break;
        }
        } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.rare.slipper[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.rare.slipper[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 3 ://4티어 망토 장착하기
            
            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.epic.sneakers[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n스니커즈%d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.epic.sneakers[i][1],boki->bokiEquipment.epic.sneakers[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
        {
        aaaaaa=getchar();
        equip_choice=atoi(&aaaaaa);  
        if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
        {
            break;
        }
        } //5개중에 고르기 0~4번
            if(boki->bokiEquipment.epic.sneakers[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.epic.sneakers[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
            case 4 :

            for(int i=0; i<5; i++){ //아이템 정보출력
            if(boki->bokiEquipment.legend.airjodan[i][0] != 0){ //i번째 장비의 정보 출력
                printf("\n조던%d 번 장비의 방어력%f : \n 강화수치 %f\n", i+1,boki->bokiEquipment.legend.airjodan[i][1],boki->bokiEquipment.legend.airjodan[i][2] );
                }
            }
            printf("방어구번호를 입력하세요. \n");
            while (1)
        {
        aaaaaa=getchar();
        equip_choice=atoi(&aaaaaa);  
        if(equip_choice==1||equip_choice==2||equip_choice==3||equip_choice==4||equip_choice==5)
        {
            break;
        }
        }//타이거 마스크 5개중에 고르기 0~4번
            if(boki->bokiEquipment.legend.airjodan[equip_choice-1][0] != 0){ // 방어구가 있는지 확인
            boki->def += boki->bokiEquipment.legend.airjodan[equip_choice-1][1]; //복이 방어력에 방어구 방어력 입히기
            printf("방어구를 장착했습니다.\n");
            break;
            }else{
            printf("방어구가 없습니다.\n");
            break;
            }
    }
    return boki->def;
}

int equip(Boki* boki){
    
    int sum;
    printf("\n장비 장착창입니다 \n");
   

    printf("무기창입니다\n");
    printf("1번기본검   2번 장검    3번 일본도     4번 싸울아비장검\n");
        boki->def = 0;
        boki->damage = 0;
        sum +=  equip_sword( boki);

    printf("마스크 장비창입니다.\n");
    printf("1번 기본마스크      2번 k84마스크       3번k90마스크        4번타이거마스크     \n");
       sum +=  equip_mask(boki);

    printf("갑바 장비창입니다.\n");
    printf("1번 기본갑바      2번 반팔갑바       3번 후드갑바        4번용갑바     \n");

       sum +=  equip_armor(boki);

    printf("망토 장비창입니다.\n");
    printf("1번 기본망토      2번 면망토       3번 비단망토        4번 방탄망토     \n");

        sum +=   equip_cape(boki);

    printf("장갑 장비창입니다.\n");
    printf("1번 기본장갑      2번 고무장갑       3번 면장갑        4번 가죽장갑     \n");

       sum +=  equip_gloves(boki);
    printf("부츠 장비창입니다.\n");
    printf("1번 기본부츠      2번 슬리퍼       3번 스니커즈        4번 조던     \n");

       sum +=  equip_boots(boki);
    
    return sum;
}

void reinforce(Boki* boki)
{
    char bb;
    int re;
    int re2;
    int re3;
    printf("어떤 장비를 강화 하고 싶습니까?\n");
    printf("1) 무기 2) 아머 3) 마스크 4) 망토 5)장갑 6)부츠\n");
    while (1)
    {
    bb=getchar();
    re=atoi(&bb);
    if(re == 1 || re ==2||re ==3||re ==4||re ==5||re ==6)
    {
        break;
    }    
    }
    
    switch (re)
    {
    case 1:
        printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본검 2) 일본검 3) 장검 4) 싸울아비장검\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
        case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.weapon.basicsword[i][0] !=0) 
                    printf("basicsword%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.weapon.basicsword[0][0]==0)
                        break;
                WReinForcement(boki,0,basicsword,0);
            break;
           case 1:
                if(boki->bokiEquipment.weapon.basicsword[1][0]==0)
                        break;
                WReinForcement(boki,1,basicsword,0);
            break;
            case 2:
                if(boki->bokiEquipment.weapon.basicsword[2][0]==0)
                        break;
                WReinForcement(boki,2,basicsword,0);
            break;
            case 3:
                if(boki->bokiEquipment.weapon.basicsword[3][0]==0)
                        break;
                WReinForcement(boki,3,basicsword,0);
            break;
            case 4:
                if(boki->bokiEquipment.weapon.basicsword[4][0]==0)
                        break;
                WReinForcement(boki,4,basicsword,0);
            break;
            default:
                break;
            }
            break;
        
        case 2:
        
            while (1)
            {
            bb=getchar();
            re2=atoi(&bb);
            if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
            {
                break;
            }    
            }
            switch (re2)
            {
            case 1:
                for (int i = 0; i < 5; i++)
                {
                if   (boki->bokiEquipment.weapon.japensword[i][0] !=0) 
                        printf("japensword%d번째 장비입니다\n",i);
                }
                printf("몇번째 장비를 강화 하시겠습니까?\n");
                while (1)
                {
                bb=getchar();
                re3=atoi(&bb);
                if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
                {
                    break;
                }    
                }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.weapon.japensword[0][0]==0)
                            break;
                    WReinForcement(boki,0,japensword,1);
                break;
            case 1:
                    if(boki->bokiEquipment.weapon.japensword[1][0]==0)
                            break;
                    WReinForcement(boki,1,japensword,1);
                break;
                case 2:
                    if(boki->bokiEquipment.weapon.japensword[2][0]==0)
                            break;
                WReinForcement(boki,2,japensword,1);
                break;
                case 3:
                    if(boki->bokiEquipment.weapon.japensword[3][0]==0)
                            break;
                    WReinForcement(boki,3,japensword,1);
                break;
                case 4:
                    if(boki->bokiEquipment.weapon.japensword[4][0]==0)
                            break;
                    WReinForcement(boki,4,japensword,1);
                break;
                default:
                    break;
                }
                //여기까지
                
                break;
            }
        
         case 3:
            for (int i = 0; i < 5; i++)
            {
             if   (boki->bokiEquipment.weapon.longsword[i][0]!=0)
                printf("longsword%d번째 장비입니다\n",i);
            }
            //여기까지
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.weapon.longsword[0][0]==0)
                        break;
                WReinForcement(boki,0,longsword,1);
            break;
           case 1:
                if(boki->bokiEquipment.weapon.longsword[1][0]==0)
                        break;
                 WReinForcement(boki,1,longsword,1);
            break;
            case 2:
                if(boki->bokiEquipment.weapon.longsword[2][0]==0)
                        break;
               WReinForcement(boki,2,longsword,1);
            break;
            case 3:
                if(boki->bokiEquipment.weapon.longsword[3][0]==0)
                        break;
                WReinForcement(boki,3,longsword,1);
            break;
            case 4:
                if(boki->bokiEquipment.weapon.longsword[4][0]==0)
                        break;
                WReinForcement(boki,4,longsword,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.weapon.nigthsword_saj[i][0]!=0)
                printf("nigthsword_saj%d번째 장비입니다\n",i);
            }
            //여기까지
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
        {
            case 0:
                if(boki->bokiEquipment.weapon.nigthsword_saj[0][0]==0)
                        break;
                WReinForcement(boki,0,nigthsword_saj,1);
            break;
           case 1:
                if(boki->bokiEquipment.weapon.nigthsword_saj[1][0]==0)
                        break;
                 WReinForcement(boki,1,nigthsword_saj,1);
            break;
            case 2:
                if(boki->bokiEquipment.weapon.nigthsword_saj[2][0]==0)
                        break;
               WReinForcement(boki,2,nigthsword_saj,1);
            break;
            case 3:
                if(boki->bokiEquipment.weapon.nigthsword_saj[3][0]==0)
                        break;
                WReinForcement(boki,3,nigthsword_saj,1);
            break;
            case 4:
                if(boki->bokiEquipment.weapon.nigthsword_saj[4][0]==0)
                        break;
                WReinForcement(boki,4,nigthsword_saj,1);
            break;
            }
       }     //여기까지
        break;
case 2:
        //dddd
        printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본아머 2) 반팔아머 3) 후드아머 4) 용갑빠\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
        case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basicarmor[i][0] !=0) 
                    printf("basicarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basicarmor[0][0]==0)
                            break;
                    FDepReinForce(boki,0,armor,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basicarmor[1][0]==0)
                            break;
                FDepReinForce(boki,1,armor,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basicarmor[2][0]==0)
                            break;
                    FDepReinForce(boki,2,armor,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basicarmor[3][0]==0)
                            break;
                    FDepReinForce(boki,3,armor,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basicarmor[4][0]==0)
                            break;
                    FDepReinForce(boki,4,armor,1);
                break;
                default:
                    break;
                }
                break;
        case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.halfarmor[i][0] !=0) 
                    printf("halfarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.halfarmor[0][0]==0)
                        break;
                SDepReinForce(boki,0,armor,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.halfarmor[1][0]==0)
                        break;
            SDepReinForce(boki,1,armor,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.halfarmor[2][0]==0)
                        break;
                SDepReinForce(boki,2,armor,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.halfarmor[3][0]==0)
                        break;
                SDepReinForce(boki,3,armor,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.halfarmor[4][0]==0)
                        break;
                SDepReinForce(boki,4,armor,1);
            break;
            default:
                break;
            }
            break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.hoodarmor[i][0] !=0) 
                    printf("hoodarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.hoodarmor[0][0]==0)
                        break;
                TDepReinForce(boki,0,armor,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.hoodarmor[1][0]==0)
                        break;
               TDepReinForce(boki,1,armor,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.hoodarmor[2][0]==0)
                        break;
                TDepReinForce(boki,2,armor,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.hoodarmor[3][0]==0)
                        break;
                TDepReinForce(boki,3,armor,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.hoodarmor[4][0]==0)
                        break;
                TDepReinForce(boki,4,armor,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.legend.dragonarmor[i][0] !=0) 
                    printf("dragonarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.dragonarmor[0][0]==0)
                        break;
                FoDepReinForce(boki,0,armor,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.dragonarmor[1][0]==0)
                        break;
               FoDepReinForce(boki,1,armor,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.dragonarmor[2][0]==0)
                        break;
                FoDepReinForce(boki,2,armor,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.dragonarmor[3][0]==0)
                        break;
                FoDepReinForce(boki,3,armor,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.dragonarmor[4][0]==0)
                        break;
                FoDepReinForce(boki,4,armor,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        
        }
        break;
    //여기까지 가장큰거
    case 3:
        printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본마스크 2) k80마스크 3) k94마스크 4) 타이거마스크\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
    case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basicmask[i][0] !=0) 
                    printf("basicmask%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basicmask[0][0]==0)
                            break;
                    FDepReinForce(boki,0,mask,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basicmask[1][0]==0)
                            break;
                FDepReinForce(boki,1,mask,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basicmask[2][0]==0)
                            break;
                    FDepReinForce(boki,2,mask,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basicmask[3][0]==0)
                            break;
                    FDepReinForce(boki,3,mask,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basicmask[4][0]==0)
                            break;
                    FDepReinForce(boki,4,mask,1);
                break;
                default:
                    break;
                }
                break;
    case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.k80mask[i][0] !=0) 
                    printf("k80mask%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.k80mask[0][0]==0)
                        break;
                SDepReinForce(boki,0,mask,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.k80mask[1][0]==0)
                        break;
            SDepReinForce(boki,1,mask,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.k80mask[2][0]==0)
                        break;
                SDepReinForce(boki,2,mask,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.k80mask[3][0]==0)
                        break;
                SDepReinForce(boki,3,armor,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.k80mask[4][0]==0)
                        break;
                SDepReinForce(boki,4,armor,1);
            break;
            default:
                break;
            }
        break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.k94mask[i][0] !=0) 
                    printf("hoodarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.k94mask[0][0]==0)
                        break;
                TDepReinForce(boki,0,mask,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.k94mask[1][0]==0)
                        break;
               TDepReinForce(boki,1,armor,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.k94mask[2][0]==0)
                        break;
                TDepReinForce(boki,2,mask,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.k94mask[3][0]==0)
                        break;
                TDepReinForce(boki,3,mask,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.k94mask[4][0]==0)
                        break;
                TDepReinForce(boki,4,mask,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if (boki->bokiEquipment.legend.tigermask[i][0] !=0) 
                    printf("tigermask%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.tigermask[0][0]==0)
                        break;
                FoDepReinForce(boki,0,mask,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.tigermask[1][0]==0)
                        break;
               FoDepReinForce(boki,1,mask,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.tigermask[2][0]==0)
                        break;
                FoDepReinForce(boki,2,mask,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.tigermask[3][0]==0)
                        break;
                FoDepReinForce(boki,3,mask,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.tigermask[4][0]==0)
                        break;
                FoDepReinForce(boki,4,mask,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        default:
            break;
         }
        break;
    //여기까지 가장큰거
case 4:
   printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본망토 2) 면망토 3) 비단망토 4) 방탄망토\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
    case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basiccape[i][0] !=0) 
                    printf("basiccape%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basiccape[0][0]==0)
                            break;
                    FDepReinForce(boki,0,cape,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basiccape[1][0]==0)
                            break;
                FDepReinForce(boki,1,cape,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basiccape[2][0]==0)
                            break;
                    FDepReinForce(boki,2,cape,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basiccape[3][0]==0)
                            break;
                    FDepReinForce(boki,3,cape,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basiccape[4][0]==0)
                            break;
                    FDepReinForce(boki,4,cape,1);
                break;
                default:
                    break;
                }
                break;
    case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.cottencape[i][0] !=0) 
                    printf("cottencape%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.cottencape[0][0]==0)
                        break;
                SDepReinForce(boki,0,cape,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.cottencape[1][0]==0)
                        break;
            SDepReinForce(boki,1,cape,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.cottencape[2][0]==0)
                        break;
                SDepReinForce(boki,2,cape,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.cottencape[3][0]==0)
                        break;
                SDepReinForce(boki,3,cape,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.cottencape[4][0]==0)
                        break;
                SDepReinForce(boki,4,cape,1);
            break;
            default:
                break;
            }
        break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.silkcape[i][0] !=0) 
                    printf("silkcape%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.silkcape[0][0]==0)
                        break;
                TDepReinForce(boki,0,cape,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.silkcape[1][0]==0)
                        break;
               TDepReinForce(boki,1,cape,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.silkcape[2][0]==0)
                        break;
                TDepReinForce(boki,2,cape,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.silkcape[3][0]==0)
                        break;
                TDepReinForce(boki,3,cape,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.silkcape[4][0]==0)
                        break;
                TDepReinForce(boki,4,cape,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if (boki->bokiEquipment.legend.bulletcape[i][0] !=0) 
                    printf("bulletcape%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.bulletcape[0][0]==0)
                        break;
                FoDepReinForce(boki,0,cape,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.bulletcape[1][0]==0)
                        break;
               FoDepReinForce(boki,1,cape,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.bulletcape[2][0]==0)
                        break;
                FoDepReinForce(boki,2,cape,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.bulletcape[3][0]==0)
                        break;
                FoDepReinForce(boki,3,cape,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.bulletcape[4][0]==0)
                        break;
                FoDepReinForce(boki,4,cape,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        default:
            break;
         }
        break;
    //여기까지 왕큰거
    case 5:
       printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본장갑 2) 고무장갑 3) 면장갑 4) 가죽장갑\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
    case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basicgloves[i][0] !=0) 
                    printf("basicgloves%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basicgloves[0][0]==0)
                            break;
                    FDepReinForce(boki,0,gloves,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basicgloves[1][0]==0)
                            break;
                FDepReinForce(boki,1,gloves,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basicgloves[2][0]==0)
                            break;
                    FDepReinForce(boki,2,gloves,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basicgloves[3][0]==0)
                            break;
                    FDepReinForce(boki,3,gloves,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basicgloves[4][0]==0)
                            break;
                    FDepReinForce(boki,4,gloves,1);
                break;
                default:
                    break;
                }
                break;
    case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.rubbergloves[i][0] !=0) 
                    printf("ru&bbergloves%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.rubbergloves[0][0]==0)
                        break;
                SDepReinForce(boki,0,gloves,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.rubbergloves[1][0]==0)
                        break;
            SDepReinForce(boki,1,gloves,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.rubbergloves[2][0]==0)
                        break;
                SDepReinForce(boki,2,gloves,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.rubbergloves[3][0]==0)
                        break;
                SDepReinForce(boki,3,gloves,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.rubbergloves[4][0]==0)
                        break;
                SDepReinForce(boki,4,gloves,1);
            break;
            default:
                break;
            }
        break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.cottengloves[i][0] !=0) 
                    printf("cottengloves%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.cottengloves[0][0]==0)
                        break;
                TDepReinForce(boki,0,gloves,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.cottengloves[1][0]==0)
                        break;
               TDepReinForce(boki,1,gloves,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.cottengloves[2][0]==0)
                        break;
                TDepReinForce(boki,2,gloves,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.cottengloves[3][0]==0)
                        break;
                TDepReinForce(boki,3,gloves,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.cottengloves[4][0]==0)
                        break;
                TDepReinForce(boki,4,gloves,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if (boki->bokiEquipment.legend.leardergloves[i][0] !=0) 
                    printf("leardergloves%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.leardergloves[0][0]==0)
                        break;
                FoDepReinForce(boki,0,gloves,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.leardergloves[1][0]==0)
                        break;
               FoDepReinForce(boki,1,gloves,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.bulletcape[2][0]==0)
                        break;
                FoDepReinForce(boki,2,gloves,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.leardergloves[3][0]==0)
                        break;
                FoDepReinForce(boki,3,gloves,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.leardergloves[4][0]==0)
                        break;
                FoDepReinForce(boki,4,gloves,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        default:
            break;
         }
        break;
    //여기까지 왕큰거
    case 6:
       printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본부츠 2) 슬리퍼 3) 운동화 4) 에어조단");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
    case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basicboots[i][0] !=0) 
                    printf("basicboots%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basicboots[0][0]==0)
                            break;
                    FDepReinForce(boki,0,boots,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basicboots[1][0]==0)
                            break;
                FDepReinForce(boki,1,boots,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basicboots[2][0]==0)
                            break;
                    FDepReinForce(boki,2,boots,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basicboots[3][0]==0)
                            break;
                    FDepReinForce(boki,3,boots,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basicboots[4][0]==0)
                            break;
                    FDepReinForce(boki,4,boots,1);
                break;
                default:
                    break;
                }
                break;
    case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.slipper[i][0] !=0) 
                    printf("slipper%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.slipper[0][0]==0)
                        break;
                SDepReinForce(boki,0,boots,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.slipper[1][0]==0)
                        break;
            SDepReinForce(boki,1,boots,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.slipper[2][0]==0)
                        break;
                SDepReinForce(boki,2,boots,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.slipper[3][0]==0)
                        break;
                SDepReinForce(boki,3,boots,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.slipper[4][0]==0)
                        break;
                SDepReinForce(boki,4,boots,1);
            break;
            default:
                break;
            }
        break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.sneakers[i][0] !=0) 
                    printf("sneakers%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.sneakers[0][0]==0)
                        break;
                TDepReinForce(boki,0,boots,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.sneakers[1][0]==0)
                        break;
               TDepReinForce(boki,1,boots,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.sneakers[2][0]==0)
                        break;
                TDepReinForce(boki,2,boots,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.sneakers[3][0]==0)
                        break;
                TDepReinForce(boki,3,boots,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.sneakers[4][0]==0)
                        break;
                TDepReinForce(boki,4,boots,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if (boki->bokiEquipment.legend.airjodan[i][0] !=0) 
                    printf("airjodan%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.airjodan[0][0]==0)
                        break;
                FoDepReinForce(boki,0,boots,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.airjodan[1][0]==0)
                        break;
               FoDepReinForce(boki,1,boots,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.airjodan[2][0]==0)
                        break;
                FoDepReinForce(boki,2,boots,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.airjodan[3][0]==0)
                        break;
                FoDepReinForce(boki,3,boots,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.airjodan[4][0]==0)
                        break;
                FoDepReinForce(boki,4,boots,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        default:
            break;
         }
        break;
    //여기까지 왕큰거
    }
    
    
}

void Ereinforce(Boki* boki)
{
    char bb;
    int re;
    int re2;
    int re3;
    printf("어떤 장비를 강화 하고 싶습니까?\n");
    printf("1) 무기 2) 아머 3) 마스크 4) 망토 5)장갑 6)부츠\n");
    while (1)
    {
    bb=getchar();
    re=atoi(&bb);
    if(re == 1 || re ==2||re ==3||re ==4||re ==5||re ==6)
    {
        break;
    }    
    }
    
    switch (re)
    {
    case 1:
        printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본검 2) 일본검 3) 장검 4) 싸울아비장검\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
        case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.weapon.basicsword[i][0] !=0) 
                    printf("basicsword%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.weapon.basicsword[0][0]==0)
                        break;
                WReinForcement(boki,0,basicsword,1);
            break;
           case 1:
                if(boki->bokiEquipment.weapon.basicsword[1][0]==0)
                        break;
                WReinForcement(boki,1,basicsword,1);
            break;
            case 2:
                if(boki->bokiEquipment.weapon.basicsword[2][0]==0)
                        break;
                WReinForcement(boki,2,basicsword,1);
            break;
            case 3:
                if(boki->bokiEquipment.weapon.basicsword[3][0]==0)
                        break;
                WReinForcement(boki,3,basicsword,1);
            break;
            case 4:
                if(boki->bokiEquipment.weapon.basicsword[4][0]==0)
                        break;
                WReinForcement(boki,4,basicsword,1);
            break;
            default:
                break;
            }
            break;
        
        case 2:
        
            while (1)
            {
            bb=getchar();
            re2=atoi(&bb);
            if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
            {
                break;
            }    
            }
            switch (re2)
            {
            case 1:
                for (int i = 0; i < 5; i++)
                {
                if   (boki->bokiEquipment.weapon.japensword[i][0] !=0) 
                        printf("japensword%d번째 장비입니다\n",i);
                }
                printf("몇번째 장비를 강화 하시겠습니까?\n");
                while (1)
                {
                bb=getchar();
                re3=atoi(&bb);
                if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
                {
                    break;
                }    
                }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.weapon.japensword[0][0]==0)
                            break;
                    WReinForcement(boki,0,japensword,1);
                break;
            case 1:
                    if(boki->bokiEquipment.weapon.japensword[1][0]==0)
                            break;
                    WReinForcement(boki,1,japensword,1);
                break;
                case 2:
                    if(boki->bokiEquipment.weapon.japensword[2][0]==0)
                            break;
                WReinForcement(boki,2,japensword,1);
                break;
                case 3:
                    if(boki->bokiEquipment.weapon.japensword[3][0]==0)
                            break;
                    WReinForcement(boki,3,japensword,1);
                break;
                case 4:
                    if(boki->bokiEquipment.weapon.japensword[4][0]==0)
                            break;
                    WReinForcement(boki,4,japensword,1);
                break;
                default:
                    break;
                }
                //여기까지
                
                break;
            }
        
         case 3:
            for (int i = 0; i < 5; i++)
            {
             if   (boki->bokiEquipment.weapon.longsword[i][0]!=0)
                printf("longsword%d번째 장비입니다\n",i);
            }
            //여기까지
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.weapon.longsword[0][0]==0)
                        break;
                WReinForcement(boki,0,longsword,1);
            break;
           case 1:
                if(boki->bokiEquipment.weapon.longsword[1][0]==0)
                        break;
                 WReinForcement(boki,1,longsword,1);
            break;
            case 2:
                if(boki->bokiEquipment.weapon.longsword[2][0]==0)
                        break;
               WReinForcement(boki,2,longsword,1);
            break;
            case 3:
                if(boki->bokiEquipment.weapon.longsword[3][0]==0)
                        break;
                WReinForcement(boki,3,longsword,1);
            break;
            case 4:
                if(boki->bokiEquipment.weapon.longsword[4][0]==0)
                        break;
                WReinForcement(boki,4,longsword,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.weapon.nigthsword_saj[i][0]!=0)
                printf("nigthsword_saj%d번째 장비입니다\n",i);
            }
            //여기까지
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
        {
            case 0:
                if(boki->bokiEquipment.weapon.nigthsword_saj[0][0]==0)
                        break;
                WReinForcement(boki,0,nigthsword_saj,1);
            break;
           case 1:
                if(boki->bokiEquipment.weapon.nigthsword_saj[1][0]==0)
                        break;
                 WReinForcement(boki,1,nigthsword_saj,1);
            break;
            case 2:
                if(boki->bokiEquipment.weapon.nigthsword_saj[2][0]==0)
                        break;
               WReinForcement(boki,2,nigthsword_saj,1);
            break;
            case 3:
                if(boki->bokiEquipment.weapon.nigthsword_saj[3][0]==0)
                        break;
                WReinForcement(boki,3,nigthsword_saj,1);
            break;
            case 4:
                if(boki->bokiEquipment.weapon.nigthsword_saj[4][0]==0)
                        break;
                WReinForcement(boki,4,nigthsword_saj,1);
            break;
            }
       }     //여기까지
        break;
case 2:
        //dddd
        printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본아머 2) 반팔아머 3) 후드아머 4) 용갑빠\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
        case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basicarmor[i][0] !=0) 
                    printf("basicarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basicarmor[0][0]==0)
                            break;
                    FDepReinForce(boki,0,armor,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basicarmor[1][0]==0)
                            break;
                FDepReinForce(boki,1,armor,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basicarmor[2][0]==0)
                            break;
                    FDepReinForce(boki,2,armor,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basicarmor[3][0]==0)
                            break;
                    FDepReinForce(boki,3,armor,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basicarmor[4][0]==0)
                            break;
                    FDepReinForce(boki,4,armor,1);
                break;
                default:
                    break;
                }
                break;
        case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.halfarmor[i][0] !=0) 
                    printf("halfarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.halfarmor[0][0]==0)
                        break;
                SDepReinForce(boki,0,armor,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.halfarmor[1][0]==0)
                        break;
            SDepReinForce(boki,1,armor,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.halfarmor[2][0]==0)
                        break;
                SDepReinForce(boki,2,armor,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.halfarmor[3][0]==0)
                        break;
                SDepReinForce(boki,3,armor,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.halfarmor[4][0]==0)
                        break;
                SDepReinForce(boki,4,armor,1);
            break;
            default:
                break;
            }
            break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.hoodarmor[i][0] !=0) 
                    printf("hoodarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.hoodarmor[0][0]==0)
                        break;
                TDepReinForce(boki,0,armor,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.hoodarmor[1][0]==0)
                        break;
               TDepReinForce(boki,1,armor,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.hoodarmor[2][0]==0)
                        break;
                TDepReinForce(boki,2,armor,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.hoodarmor[3][0]==0)
                        break;
                TDepReinForce(boki,3,armor,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.hoodarmor[4][0]==0)
                        break;
                TDepReinForce(boki,4,armor,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.legend.dragonarmor[i][0] !=0) 
                    printf("dragonarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.dragonarmor[0][0]==0)
                        break;
                FoDepReinForce(boki,0,armor,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.dragonarmor[1][0]==0)
                        break;
               FoDepReinForce(boki,1,armor,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.dragonarmor[2][0]==0)
                        break;
                FoDepReinForce(boki,2,armor,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.dragonarmor[3][0]==0)
                        break;
                FoDepReinForce(boki,3,armor,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.dragonarmor[4][0]==0)
                        break;
                FoDepReinForce(boki,4,armor,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        
        }
        break;
    //여기까지 가장큰거
    case 3:
        printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본마스크 2) k80마스크 3) k94마스크 4) 타이거마스크\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
    case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basicmask[i][0] !=0) 
                    printf("basicmask%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basicmask[0][0]==0)
                            break;
                    FDepReinForce(boki,0,mask,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basicmask[1][0]==0)
                            break;
                FDepReinForce(boki,1,mask,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basicmask[2][0]==0)
                            break;
                    FDepReinForce(boki,2,mask,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basicmask[3][0]==0)
                            break;
                    FDepReinForce(boki,3,mask,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basicmask[4][0]==0)
                            break;
                    FDepReinForce(boki,4,mask,1);
                break;
                default:
                    break;
                }
                break;
    case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.k80mask[i][0] !=0) 
                    printf("k80mask%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.k80mask[0][0]==0)
                        break;
                SDepReinForce(boki,0,mask,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.k80mask[1][0]==0)
                        break;
            SDepReinForce(boki,1,mask,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.k80mask[2][0]==0)
                        break;
                SDepReinForce(boki,2,mask,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.k80mask[3][0]==0)
                        break;
                SDepReinForce(boki,3,armor,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.k80mask[4][0]==0)
                        break;
                SDepReinForce(boki,4,armor,1);
            break;
            default:
                break;
            }
        break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.k94mask[i][0] !=0) 
                    printf("hoodarmor%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.k94mask[0][0]==0)
                        break;
                TDepReinForce(boki,0,mask,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.k94mask[1][0]==0)
                        break;
               TDepReinForce(boki,1,armor,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.k94mask[2][0]==0)
                        break;
                TDepReinForce(boki,2,mask,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.k94mask[3][0]==0)
                        break;
                TDepReinForce(boki,3,mask,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.k94mask[4][0]==0)
                        break;
                TDepReinForce(boki,4,mask,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if (boki->bokiEquipment.legend.tigermask[i][0] !=0) 
                    printf("tigermask%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.tigermask[0][0]==0)
                        break;
                FoDepReinForce(boki,0,mask,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.tigermask[1][0]==0)
                        break;
               FoDepReinForce(boki,1,mask,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.tigermask[2][0]==0)
                        break;
                FoDepReinForce(boki,2,mask,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.tigermask[3][0]==0)
                        break;
                FoDepReinForce(boki,3,mask,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.tigermask[4][0]==0)
                        break;
                FoDepReinForce(boki,4,mask,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        default:
            break;
         }
        break;
    //여기까지 가장큰거
case 4:
   printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본망토 2) 면망토 3) 비단망토 4) 방탄망토\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
    case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basiccape[i][0] !=0) 
                    printf("basiccape%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basiccape[0][0]==0)
                            break;
                    FDepReinForce(boki,0,cape,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basiccape[1][0]==0)
                            break;
                FDepReinForce(boki,1,cape,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basiccape[2][0]==0)
                            break;
                    FDepReinForce(boki,2,cape,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basiccape[3][0]==0)
                            break;
                    FDepReinForce(boki,3,cape,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basiccape[4][0]==0)
                            break;
                    FDepReinForce(boki,4,cape,1);
                break;
                default:
                    break;
                }
                break;
    case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.cottencape[i][0] !=0) 
                    printf("cottencape%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.cottencape[0][0]==0)
                        break;
                SDepReinForce(boki,0,cape,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.cottencape[1][0]==0)
                        break;
            SDepReinForce(boki,1,cape,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.cottencape[2][0]==0)
                        break;
                SDepReinForce(boki,2,cape,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.cottencape[3][0]==0)
                        break;
                SDepReinForce(boki,3,cape,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.cottencape[4][0]==0)
                        break;
                SDepReinForce(boki,4,cape,1);
            break;
            default:
                break;
            }
        break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.silkcape[i][0] !=0) 
                    printf("silkcape%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.silkcape[0][0]==0)
                        break;
                TDepReinForce(boki,0,cape,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.silkcape[1][0]==0)
                        break;
               TDepReinForce(boki,1,cape,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.silkcape[2][0]==0)
                        break;
                TDepReinForce(boki,2,cape,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.silkcape[3][0]==0)
                        break;
                TDepReinForce(boki,3,cape,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.silkcape[4][0]==0)
                        break;
                TDepReinForce(boki,4,cape,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if (boki->bokiEquipment.legend.bulletcape[i][0] !=0) 
                    printf("bulletcape%d번째 장비입니다\n",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.bulletcape[0][0]==0)
                        break;
                FoDepReinForce(boki,0,cape,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.bulletcape[1][0]==0)
                        break;
               FoDepReinForce(boki,1,cape,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.bulletcape[2][0]==0)
                        break;
                FoDepReinForce(boki,2,cape,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.bulletcape[3][0]==0)
                        break;
                FoDepReinForce(boki,3,cape,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.bulletcape[4][0]==0)
                        break;
                FoDepReinForce(boki,4,cape,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        default:
            break;
         }
        break;
    //여기까지 왕큰거
    case 5:
       printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본장갑 2) 고무장갑 3) 면장갑 4) 가죽장갑\n");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
    case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basicgloves[i][0] !=0) 
                    printf("basicgloves%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basicgloves[0][0]==0)
                            break;
                    FDepReinForce(boki,0,gloves,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basicgloves[1][0]==0)
                            break;
                FDepReinForce(boki,1,gloves,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basicgloves[2][0]==0)
                            break;
                    FDepReinForce(boki,2,gloves,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basicgloves[3][0]==0)
                            break;
                    FDepReinForce(boki,3,gloves,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basicgloves[4][0]==0)
                            break;
                    FDepReinForce(boki,4,gloves,1);
                break;
                default:
                    break;
                }
                break;
    case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.rubbergloves[i][0] !=0) 
                    printf("ru&bbergloves%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.rubbergloves[0][0]==0)
                        break;
                SDepReinForce(boki,0,gloves,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.rubbergloves[1][0]==0)
                        break;
            SDepReinForce(boki,1,gloves,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.rubbergloves[2][0]==0)
                        break;
                SDepReinForce(boki,2,gloves,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.rubbergloves[3][0]==0)
                        break;
                SDepReinForce(boki,3,gloves,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.rubbergloves[4][0]==0)
                        break;
                SDepReinForce(boki,4,gloves,1);
            break;
            default:
                break;
            }
        break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.cottengloves[i][0] !=0) 
                    printf("cottengloves%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.cottengloves[0][0]==0)
                        break;
                TDepReinForce(boki,0,gloves,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.cottengloves[1][0]==0)
                        break;
               TDepReinForce(boki,1,gloves,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.cottengloves[2][0]==0)
                        break;
                TDepReinForce(boki,2,gloves,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.cottengloves[3][0]==0)
                        break;
                TDepReinForce(boki,3,gloves,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.cottengloves[4][0]==0)
                        break;
                TDepReinForce(boki,4,gloves,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if (boki->bokiEquipment.legend.leardergloves[i][0] !=0) 
                    printf("leardergloves%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.leardergloves[0][0]==0)
                        break;
                FoDepReinForce(boki,0,gloves,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.leardergloves[1][0]==0)
                        break;
               FoDepReinForce(boki,1,gloves,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.bulletcape[2][0]==0)
                        break;
                FoDepReinForce(boki,2,gloves,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.leardergloves[3][0]==0)
                        break;
                FoDepReinForce(boki,3,gloves,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.leardergloves[4][0]==0)
                        break;
                FoDepReinForce(boki,4,gloves,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        default:
            break;
         }
        break;
    //여기까지 왕큰거
    case 6:
       printf("어떤 장비를 강화 하고 싶습니까?\n");
        printf("1) 기본부츠 2) 슬리퍼 3) 운동화 4) 에어조단");
        while (1)
        {
        bb=getchar();
        re2=atoi(&bb);
        if(re2 == 1 || re2 ==2||re2 ==3||re2 ==4)
        {
            break;
        }    
        }
        switch (re2)
        {
    case 1:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.nomal.basicboots[i][0] !=0) 
                    printf("basicboots%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3==0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
                switch (re3)
                {
                case 0:
                    if(boki->bokiEquipment.nomal.basicboots[0][0]==0)
                            break;
                    FDepReinForce(boki,0,boots,1);
                break;
                case 1:
                    if(boki->bokiEquipment.nomal.basicboots[1][0]==0)
                            break;
                FDepReinForce(boki,1,boots,1);  
                    break;
                case 2:
                    if(boki->bokiEquipment.nomal.basicboots[2][0]==0)
                            break;
                    FDepReinForce(boki,2,boots,1);
                break;
                case 3:
                    if(boki->bokiEquipment.nomal.basicboots[3][0]==0)
                            break;
                    FDepReinForce(boki,3,boots,1);
                break;
                case 4:
                    if(boki->bokiEquipment.nomal.basicboots[4][0]==0)
                            break;
                    FDepReinForce(boki,4,boots,1);
                break;
                default:
                    break;
                }
                break;
    case 2:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.rare.slipper[i][0] !=0) 
                    printf("slipper%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            //w
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            //w
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.rare.slipper[0][0]==0)
                        break;
                SDepReinForce(boki,0,boots,1);
            break;
            case 1:
                if(boki->bokiEquipment.rare.slipper[1][0]==0)
                        break;
            SDepReinForce(boki,1,boots,1);  
                break;
            case 2:
                if(boki->bokiEquipment.rare.slipper[2][0]==0)
                        break;
                SDepReinForce(boki,2,boots,1);
            break;
            case 3:
                if(boki->bokiEquipment.rare.slipper[3][0]==0)
                        break;
                SDepReinForce(boki,3,boots,1);
            break;
            case 4:
                if(boki->bokiEquipment.rare.slipper[4][0]==0)
                        break;
                SDepReinForce(boki,4,boots,1);
            break;
            default:
                break;
            }
        break;
        
        
        case 3:
            for (int i = 0; i < 5; i++)
            {
            if   (boki->bokiEquipment.epic.sneakers[i][0] !=0) 
                    printf("sneakers%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.epic.sneakers[0][0]==0)
                        break;
                TDepReinForce(boki,0,boots,1);
            break;
           case 1:
                if(boki->bokiEquipment.epic.sneakers[1][0]==0)
                        break;
               TDepReinForce(boki,1,boots,1);  
                break;
            case 2:
                if(boki->bokiEquipment.epic.sneakers[2][0]==0)
                        break;
                TDepReinForce(boki,2,boots,1);
            break;
            case 3:
                if(boki->bokiEquipment.epic.sneakers[3][0]==0)
                        break;
                TDepReinForce(boki,3,boots,1);
            break;
            case 4:
                if(boki->bokiEquipment.epic.sneakers[4][0]==0)
                        break;
                TDepReinForce(boki,4,boots,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        case 4:
             for (int i = 0; i < 5; i++)
            {
            if (boki->bokiEquipment.legend.airjodan[i][0] !=0) 
                    printf("airjodan%d번째 장비입니다",i);
            }
            printf("몇번째 장비를 강화 하시겠습니까?\n");
            while (1)
            {
            bb=getchar();
            re3=atoi(&bb);
            if(re3 == 0|| re3 == 1 || re3 ==2||re3 ==3||re3 ==4)
            {
                break;
            }    
            }
            switch (re3)
            {
            case 0:
                if(boki->bokiEquipment.legend.airjodan[0][0]==0)
                        break;
                FoDepReinForce(boki,0,boots,1);
            break;
           case 1:
                if(boki->bokiEquipment.legend.airjodan[1][0]==0)
                        break;
               FoDepReinForce(boki,1,boots,1);  
                break;
            case 2:
                if(boki->bokiEquipment.legend.airjodan[2][0]==0)
                        break;
                FoDepReinForce(boki,2,boots,1);
            break;
            case 3:
                if(boki->bokiEquipment.legend.airjodan[3][0]==0)
                        break;
                FoDepReinForce(boki,3,boots,1);
            break;
            case 4:
                if(boki->bokiEquipment.legend.airjodan[4][0]==0)
                        break;
                FoDepReinForce(boki,4,boots,1);
            break;
            default:
                break;
            }
            //여기까지
            break;
        default:
            break;
         }
        break;
    //여기까지 왕큰거
    }
    
    
}
