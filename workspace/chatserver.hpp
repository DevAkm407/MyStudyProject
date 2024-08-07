#ifndef CHSCLASS_H__
#define CHSCLASS_H__
#include<iostream>
#include<string>
#include<sstream>
#include<mariadb/conncpp.hpp>
using namespace std;

class chatserver 
{
private:
        
protected:
std::unique_ptr<sql::Connection> setting()
{
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/CHAT");
        
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "AKM"}, {"password", "1234"}});
        
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    return conn;    
}
std::unique_ptr<sql::Connection> conn=setting();
public:
    string aka;
    int login;
    chatserver(/* args */){}
    ~chatserver(){}
//로그인 함수
int getlogin(string msg)
{
    stringstream iss(msg);
    string splitmsg[3];
    for (int i = 0; i < 3; i++)
    {
        iss>>splitmsg[i];
    }
    
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT fid,aka FROM MEMBER WHERE id = ? AND pw= ?"));
    stmnt->setString(1,splitmsg[1]);
    stmnt->setString(2,splitmsg[2]);
    unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
    if(res->rowsCount()==0)
    {
        return 0;
    }
    res->next();
    this->login=res->getInt(1);
    this->aka=res->getString(2);
    return login;
}

//친구 찾기
string findmyfriend()
{
    try{
    if(login!=0)
    {
        ostringstream oss;
        istringstream iss;
        stringstream ss;
        string myfrined;
        vector<string> svec;
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT myfriend from FRIEND WHERE proposer = ?"));
        stmnt->setInt(1,login); 
        
        unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
        while (res->next())
        {
            myfrined=res->getString(1);
            oss<<myfrined<<" ";
        }
        myfrined=oss.str();
        ss.str(myfrined);
        while (ss>> myfrined)
        {
        svec.emplace_back(myfrined);
        }
        vector<string>::iterator iter;
        ostringstream ops;
        istringstream azs;
        
        for ( iter =svec.begin(); iter !=svec.end(); ++iter)
        {   
            myfrined=iter->substr(iter->find("-")+1);
            ops<<myfrined<<" ";   
        }
        return ops.str();
    }
    string k="로그인하세요";
    return k;
}catch(sql::SQLException &e)
{
    cerr<<"SQL ERROR"<<e.what()<<endl;
}
return 0;
}

//친구목록 확인 파츠
string akamyfriends(string msg)
{
try{
    stringstream ss(msg);
    ostringstream oss;
    int buffer;
    vector<int> myfriendfid;
    while (ss>> buffer)
    {
        myfriendfid.emplace_back(buffer);
    }
    vector<int>::iterator iter;
    string ls;
    char c;
    for ( iter =myfriendfid.begin(); iter!=myfriendfid.end() ; ++iter)
    {
        // cout<<*iter<<endl;
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT aka FROM MEMBER WHERE fid = ?"));
        stmnt->setInt(1,*iter);
        unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
        res->next();
        ls=res->getString(1);
        oss<<*iter<<" "<<ls<<"\n";
    
    }
return oss.str();
}catch(sql::SQLException &e)
{
    cerr<<"SQL ERROR"<<e.what()<<endl;
}
}

//내 친구목록 확인
string showMyFriend()
{
    string k,j;
    k=findmyfriend();
    j=akamyfriends(k);
    return j;
}

//친구신청목록 확인
string checkFriendRequest(int fid)
{  
    try{
    unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT SHOOTER FROM SHOOTFRIEND WHERE TARGET = ?"));
    stmnt->setInt(1,fid);
    sql::ResultSet* res=stmnt->executeQuery();
    string k;
    ostringstream oss;
    if(res->rowsCount()==0)
    {
            k="0";
            return k;
    }
    sql::ResultSet* gess;
    while (res->next())
    {
        unique_ptr<sql::PreparedStatement> ntmnt(conn->prepareStatement("SELECT aka FROM MEMBER WHERE fid = ?"));
        ntmnt->setInt(1,res->getInt(1));
        gess=ntmnt->executeQuery();
        gess->next();
        k=gess->getString(1);
        oss<<res->getInt(1)<<": "<<k<<"님에게 친구요청이왔습니다.\n";
    }    
    k=oss.str();
    return k;
    }catch(sql::SQLException &e)
    {
        string j="sql에러";
        cerr<<"SQLException: "<<e.what()<<endl;
        return j;
    }
    return NULL;
}

//친구신청목록 확인후 수락하는 함수
void registFriend(int myfid,int shootfid)
{
    try{
    ostringstream oss;
    unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO FRIEND VALUES(DEFAULT,?,?)"));
    oss<<shootfid<<"-"<<myfid;
    stmnt->setInt(1,shootfid);
    stmnt->setString(2,oss.str()); 
    oss.str("");
    sql::ResultSet* res=stmnt->executeQuery();
    unique_ptr<sql::PreparedStatement> ntmnt(conn->prepareStatement("INSERT INTO FRIEND VALUES(DEFAULT,?,?)"));
    oss<<myfid<<"-"<<shootfid;
    ntmnt->setInt(1,myfid);
    ntmnt->setString(2,oss.str()); 
    res=ntmnt->executeQuery();
    
    unique_ptr<sql::PreparedStatement> ztmnt(conn->prepareStatement("DELETE FROM SHOOTFRIEND WHERE SHOOTER = ? AND TARGET = ? "));
    ztmnt->setInt(1,shootfid);
    ztmnt->setInt(2,myfid);
    res=ztmnt->executeQuery();
    }catch(sql::SQLException &e)
    {
        cerr<<"SQLException: "<<e.what();
    }
}

//친구 거절
void rejectFriend(int myfid,int shootfid)
{
  try
    {  
        unique_ptr<sql::PreparedStatement> ztmnt(conn->prepareStatement("DELETE FROM SHOOTFRIEND WHERE SHOOTER = ? AND TARGET = ? "));
        ztmnt->setInt(1,shootfid);
        ztmnt->setInt(2,myfid);
        sql::ResultSet* res=ztmnt->executeQuery();
    }catch(sql::SQLException &e)
    {
        cerr<<"SQLException: "<<e.what();
    }
}


//친구요청
string shoot(int myfid,int targetfid)
{
    ostringstream oss;
    string k;
    unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO SHOOTFRIEND VALUES(DEFAULT,?,?,0)"));
    stmnt->setInt(1,myfid);
    stmnt->setInt(2,targetfid);
    sql::ResultSet* res=stmnt->executeQuery();
    
    std::unique_ptr<sql::PreparedStatement> ztmnt(conn->prepareStatement("SELECT aka FROM MEMBER WHERE fid = ?"));
    ztmnt->setInt(1,targetfid);
    res=ztmnt->executeQuery();
    res->next();
    k=res->getString(1);
    oss<<k<<"님에게 친구요청완료 \n";
    k=oss.str();
    return k;
}
};




#endif 