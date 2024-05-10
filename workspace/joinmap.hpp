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
    map<string,int>regionmap; //키 타입 string 밸류 타입 int 맵이름 regionmap;
    map<string,int>marketmap;
    map<string,int>productmap;
public:
    joinmap(/* args */)
    {
    
    i.open("regioncode.txt",ios_base::in);
    while (getline(i,buffer))
    {
       regionmap.insert( pair<string,int> (buffer.substr(0,buffer.find(',')),stoi(buffer.substr(buffer.find(',')+1))  ) );
    }
    i.close();
    
    i.open("marketcode.txt",ios_base::in);
    while (getline(i,buffer))
    {
       marketmap.insert( pair<string,int> (buffer.substr(0,buffer.find(',')),stoi(buffer.substr(buffer.find(',')+1))  ) );
    }
    i.close();
    
    i.open("productcode.txt",ios_base::in);
    while (getline(i,buffer))
    {
       productmap.insert( pair<string,int> (buffer.substr(0,buffer.find(',')),stoi(buffer.substr(buffer.find(',')+1))  ) );
    }
    }

    virtual ~joinmap(){};
    
    //지역번호찾기
    int joinregion(string region)
    {
      map<string,int>::iterator it= regionmap.find(region);
    if(it ==regionmap.end())
        return -1;
        
    return regionmap[region];
    }

    //시장번호찾기
    int joinmarket(string region)
    {
      map<string,int>::iterator it= marketmap.find(region);
    if(it ==marketmap.end())
        return -1;
    
    return marketmap[region];
    }

    //물품번호찾기
    int joinproduct(string region)
    {
      map<string,int>::iterator it= productmap.find(region);
    if(it ==productmap.end())
        return -1;
    
    return productmap[region];
    }


};


vector<string> split(string str, char Delimiter)
{
    istringstream iss(str); // istringstream에 str을 담는다.
    string buffer;          // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼

    vector<string> result;

    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (getline(iss, buffer, Delimiter))
    {
        result.push_back(buffer); // 절삭된 문자열을 vector에 저장
    }

    return result;
}
#endif
