#include "monster1.h"

struct town
{
int townmaps[50][50];

};

struct firstfloor
{
int firstfloormaps[50][50];
int monstermaps[50][50];
Monster* first;
};

struct secondfloor
{
int secondfloormaps[50][50];
int monstermaps[50][50];
Monster* second;
};

struct thirdfloor
{
int thirdfloormaps[50][50];
int monstermaps[50][50];
Monster* third;
};

struct fourthfloor
{
int fourthfloormaps[50][50];
int monstermaps[50][50];
Monster* fourth;
};

struct fifthfloor
{
int fifthfloormaps[50][50];
int monstermaps[50][50];
Monster* fifth;
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

typedef struct UsersGraphicsMap
{
    int userPoint[2];
    char userInterFaceMap[50][50];
    int floorcount[1];
    int fcinterrupt[1];
}User;

