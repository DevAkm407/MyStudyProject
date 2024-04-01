#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//맵구현+몬스터 배치  어려움(동적할당 사용함)(광민)
typedef struct boki
{
    int fhp;
    int chp;
    int damage;
}boki;

struct oaks_warrior
{
    int damage;
    int hp;
    int gold;
};

struct zombie
{
    int damage;
    int hp;
    int gold;
};

struct ghoul
{
    int damage;
    int hp;
    int gold;
};

struct skeleton
{
    int damage;
    int hp;
    int gold;
};

struct spartoi
{
    int damage;
    int hp;
    int gold;
};

struct student
{
    int name;
    int damage;
    int hp;
    int gold;
};

typedef struct monster
{
   struct oaks_warrior oaks_warrior;
   struct zombie zombie;
   struct ghoul ghoul;
   struct skeleton skeleton;
   struct spartoi spartoi;
   struct student hero;
}monster;

struct npc
{
    /* data */
};

struct town
{
struct npc npc;
int townmaps[50][50];

};

struct firstfloor
{
int firstfloormaps[50][50];
int monstermaps[50][50];
monster* first;
};

struct secondfloor
{
int secondfloormaps[50][50];
int monstermaps[50][50];
monster* second;
};

struct thirdfloor
{
int thirdfloormaps[50][50];
int monstermaps[50][50];
monster* third;
};

struct fourthfloor
{
int fourthfloormaps[50][50];
int monstermaps[50][50];
monster* fourth;
};

struct fifthfloor
{
int fifthfloormaps[50][50];
int monstermaps[50][50];
monster* fifth;
};

typedef struct maps
{

struct town town;
struct firstfloor firstfloor;
struct secondfloor secondfloor;
struct thirdfloor thirdfloor;
struct fourthfloor fourthfloor;
struct fifthfloor fifthfloor;
}maps;

//function
maps* MapsInitialization(maps*);
maps* MapsReallocation(maps*);
monster* MonsterInitialization(monster*);
monster* MonterRegenerative(monster*,boki* user,int);
maps* MonsterMapsRegenerative(maps*,int);
int main (void)
{

}
maps* MapsInitialization(maps* mapspointer)
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            mapspointer->town.townmaps[i][j];
            mapspointer->firstfloor.firstfloormaps[i][j];
            mapspointer->secondfloor.secondfloormaps[i][j];
            mapspointer->thirdfloor.thirdfloormaps[i][j];
            mapspointer->fourthfloor.fourthfloormaps[i][j];
            mapspointer->fifthfloor.fifthfloormaps[i][j];
        }
    }
 return mapspointer;   
}


monster* MonsterInitialization(monster* imonster)
{
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
}

monster* MonterRegenerative(monster* rm,boki* user,int floor)
{
    srand(time(NULL));
    char* name[27]={"강진영","권철민","김건","김민아","김성근",
    "김승수","김경곤","김재신","김혜빈","노주영","박민건","박선후"
    ,"박장미","박희정","서훈","안광민","오은지","유시온","이동준",
    "이준호","이은승","이준호","이철","임석현","조대정","조세빈",
    "황운하","황은비"};
    switch (floor)
    {
    case 1:
        rm->oaks_warrior.hp = (rand() % 51 )+50;
        rm->oaks_warrior.damage = (rand() % 6) +10;
        rm->hero.name=name[rand()%28];
        rm->hero.hp= user->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        break;
    case 2:
        rm->zombie.hp= (rand() % 131) +50;
        rm->zombie.damage =(rand() % 14) +17;
        rm->hero.name=name[rand()%28];
        rm->hero.hp= user->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        break;
    case 3:
        rm->ghoul.hp=(rand() % 61) +120;
        rm->ghoul.damage = (rand() % 26)+20;
        rm->hero.name=name[rand()%28];
        rm->hero.hp= user->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        break;
    case 4:
        rm->skeleton.hp = (rand() % 61)+200;
        rm -> skeleton.damage =(rand() % 28)+28;
        rm->hero.name=name[rand()%28];
        rm->hero.hp= user->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        break;
    case 5:
        rm->spartoi.hp =(rand()% 101)+260;
        rm->spartoi.damage = (rand()%44)+32;   
        rm->hero.name=name[rand()%28];
        rm->hero.hp= user->chp * 2;
        rm->hero.damage=(rand()%201)+100;
        break;
    default:
        break;
    }
}
//매개변수로 maps*를 넣어야함 int floor는 몇층인지 나타냄 학생은 2 그 맵의 기본몬스터는 1 몬스터가 없으면 0
maps* MonsterMapsRegenerative(maps* monmap,int floor)
{
   srand(time(NULL));
   switch (floor)
   {
   case 1: 
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                int mmr=rand()%100;
                if(mmr>=70)
                    monmap->firstfloor.monstermaps[i][j]=2;
                else if(mmr<=50)
                    monmap->firstfloor.monstermaps[i][j]=1;
                else
                    monmap->firstfloor.monstermaps[i][j]=0;
            }
            
        }
        
        break;
    
   case 2: 
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                int mmr=rand()%100;
                if(mmr>=70)
                    monmap->secondfloor.monstermaps[i][j]=2;
                else if(mmr<=50)
                    monmap->secondfloor.monstermaps[i][j]=1;
                else
                    monmap->secondfloor.monstermaps[i][j]=0;
            }
            
            
        }
        break;
        
    case 3: 
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                int mmr=rand()%100;
                if(mmr>=70)
                    monmap->thirdfloor.monstermaps[i][j]=2;
                else if(mmr<=50)
                    monmap->thirdfloor.monstermaps[i][j]=1;
                else
                    monmap->thirdfloor.monstermaps[i][j]=0;
            }
            
            
        }
        break;
        
    case 4: 
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                int mmr=rand()%100;
                if(mmr>=70)
                    monmap->fourthfloor.monstermaps[i][j]=2;
                else if(mmr<=50)
                    monmap->fourthfloor.monstermaps[i][j]=1;
                else
                    monmap->fourthfloor.monstermaps[i][j]=0;
            }
        }
        break;
    case 5: 
    
    break;
   default:
        fputs("floor 값이 이상합니다!!!",stdin);
        break;
   }
   
    return monmap;
}