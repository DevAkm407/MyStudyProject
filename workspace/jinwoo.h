#include <string>
#include <iostream>
#include<random>
#include<unistd.h>
#ifndef JINWOO_H_
#define JINWOO_H_
class jinwoo
{
private:
    std::string name;
    int level;
    double exp;
    double expBar;
    int deathcount;
    int easycount;
    void levelUp();
    void levleDown();
    int callrandom(int);
    int callrandom(int,int);
    double callrandom(double);
public:
    
    jinwoo();
    jinwoo(const std::string myname,int level,int expBar);
    jinwoo(const jinwoo& copy);
    ~jinwoo();
    void fight();
    void query();
    void easymode();
    int easycountreturn();
};
#endif