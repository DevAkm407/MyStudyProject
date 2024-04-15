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
    void levelUp();
    void levleDown();
    int callrandom(int);
    double callrandom(double);
public:
    jinwoo();
    jinwoo(const std::string myname,int level,int expBar);
    ~jinwoo();
    void fight();
    void query();
    
};


#endif