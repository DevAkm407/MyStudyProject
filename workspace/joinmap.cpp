#ifndef JOINMAP_H_
#define JOINMAP_H_
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
using namespace std;
class joinmap
{
private:
    ifstream i;
    string buffer;
    map<string,string>regionmap;
    map<string,string>marketmap;
    map<string,string>productmap;
public:
    joinmap(/* args */)
    {
    
    i.open("regioncode.txt",ios_base::in);
    while (getline(i,buffer))
    {
       regionmap.insert( pair<string,string> (buffer.substr(0,buffer.find(',')),buffer.substr(buffer.find(',')+1)  ) );
    }
    i.close();
    
    i.open("marketcode.txt",ios_base::in);
    while (getline(i,buffer))
    {
       marketmap.insert( pair<string,string> (buffer.substr(0,buffer.find(',')),buffer.substr(buffer.find(',')+1)  ) );
    }
    i.close();
    
    i.open("productcode.txt",ios_base::in);
    while (getline(i,buffer))
    {
       marketmap.insert( pair<string,string> (buffer.substr(0,buffer.find(',')),buffer.substr(buffer.find(',')+1)  ) );
    }
    
    }

    virtual ~joinmap(){};
    
    //지역번호찾기
    string joinregion(string region)
    {
      map<string,string>::iterator it= regionmap.find(region);
    if(it ==regionmap.end())
        return "못찾음";
        
    return regionmap[region];
    }

    //시장번호찾기
    string joinmarket(string region)
    {
      map<string,string>::iterator it= marketmap.find(region);
    if(it ==marketmap.end())
        return "못찾음";
    
    return marketmap[region];
    }

    //물품번호찾기
    string joinproduct(string region)
    {
      map<string,string>::iterator it= productmap.find(region);
    if(it ==productmap.end())
        return "못찾음";
    
    return productmap[region];
    }

};

#endif