#include <stdio.h>
#include"item.h"
struct Oaks_warrior
{
    int damage;
    int hp;
    int gold;
};

struct Zombie
{
    int damage;
    int hp;
    int gold;
};

struct Ghoul
{
    int damage;
    int hp;
    int gold;
};

struct Skeleton
{
    int damage;
    int hp;
    int gold;
};

struct Spartoi
{
    int damage;
    int hp;
    int gold;
};

struct Student
{
    char* name;
    int damage;
    int hp;
    int gold;
};

struct Baphomet{
    int hp;
    int damage;
};

struct lee{
    int hp;
    int damage;
};

struct ryu
{
    int hp;
    int damage;
};

typedef struct Monster
{
   struct Oaks_warrior oaks_warrior;
   struct Zombie zombie;
   struct Ghoul ghoul;
   struct Skeleton skeleton;
   struct Spartoi spartoi;
   struct Student hero;
   struct Baphomet Baphomet;
   struct lee boss;
   struct ryu realboss;
}Monster;