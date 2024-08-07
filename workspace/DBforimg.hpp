#ifndef IMGCLASS_K__
#define IMGCLASS_K__
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<sstream>
#include<math.h>
#include<mariadb/conncpp.hpp>
#include<nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;
//cs들의 정보를 담은 헤더파일

class Dbim 
{
private:
        
protected:
std::unique_ptr<sql::Connection> setting()
{
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/CNN");
        
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
    Dbim(/* args */){}
    ~Dbim(){}
//로그인 함수

string savepath(string msg)
{
    try
    {        
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO imtable VALUES(DEFAULT,?)"));
        stmnt->setString(1,msg);
        stmnt->executeQuery();
        return (string)"별일없것지";
    }catch(json::exception &e)
    {
        return (string)"json 형식오류";
    }
}

string savetext(string msg)
{
    const char* z;
    try
    {        
        json j=json::parse(msg);
    
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO tdtable VALUES(DEFAULT,(SELECT MAX(impk) FROM imtable),?)"));
    
        
        double z =  stod((string)j["text"]);
        // k.replace(k.find(","),k.length(),".");
        
        cout << z<< endl;
        
        
        stmnt->setDouble(1,z);        
        stmnt->executeQuery();
        
        return (string)"별일없것지";
    }    
    catch(json::exception &e)
    {
        return (string)"json 형식오류";
    }
    catch(std::exception &e)
    {
        puts(msg.c_str());
        return (string)"문자열 오류";
    }

}

string Getimg(string msg)
{
    json j=json::parse(msg);
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT impath FROM imtable WHERE impk= (SELECT tdpk FROM tdtable WHERE tdtime = ?)"));
    stmnt->setString(1,(string)j["time"]);
    stmnt->executeQuery();
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
    res->next();
    string k =(string)res->getString(1);
    
    return k;
}

string Getvalue(string msg)
{
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT tdvalue,tdtime FROM tdtable"));
    
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
    json k;
    k["value"]=json::array();
    k["time"]=json::array();
    while (res->next())
    {        
      k["value"] +=res->getString(1);
      k["time"] += res->getString(2);   
    }
        
    return k.dump(4);
}


string SetData(string msg)
{
    try
    {
        string k;
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO tdtable VALUES(DEFAULT,?,NOW())"));                       
        stmnt->setString(1,msg);
        stmnt->executeQuery();                
        k="데이터 저장 완료";
        return k;    
    }
    catch(const sql::SQLException& e)
    {
        std::cerr << e.what() << '\n';
    }    
    return (string)"회원가입 실패";
}

};


#endif 