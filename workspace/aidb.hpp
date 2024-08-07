#ifndef KMSCLASS_K__
#define KMSCLASS_K__
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
class DBConnect 
{
private:
        
protected:
std::unique_ptr<sql::Connection> setting()
{
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/Diamond");
        
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
    DBConnect(/* args */){}
    ~DBConnect(){}
//로그인 함수


// string SetAccount(string msg)
// {
//     try
//     {
//         json j=json::parse(msg);
//         string k;
//         std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO userdata VALUES(DEFAULT,?,?,?)"));                       
//         stmnt->setString(1,(string)j["id"]);
//         stmnt->setString(2,(string)j["pw"]);
//         stmnt->setString(3,(string)j["name"]);
//         stmnt->executeQuery();                
//         k="회원가입 완료";
//         return k;    
//     }
//     catch(const sql::SQLException& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
    
//     return (string)"회원가입 실패";
// }

// string UserLogin(string msg)
// {
//     try
//     {
//         json j=json::parse(msg);
//         string k;
//         std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT user_name FROM userdata WHERE user_id=? AND user_pw=?"));                       
//         stmnt->setString(1,(string)j["id"]);
//         stmnt->setString(2,(string)j["pw"]);                        
//         std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
//         res->next();
//         if(res->getRow()==0)
//             return (string)"로그인실패";                        
//         return (string)res->getString(1);
//     }
//     catch(const sql::SQLException& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
    
//     return (string)"회원가입 실패";
// }

string SetUser_Search_Data(string msg)
{

    try
    {
        json j=json::parse(msg);
        string k;
        std::unique_ptr<sql::PreparedStatement> atmnt(conn->prepareStatement("SELECT user_pk FROM userdata WHERE user_name= ?"));
        atmnt->setString(1,(string)j["username"]);
        std::unique_ptr<sql::ResultSet> ras(atmnt->executeQuery());
        ras->next();
        j["user_pk"]=ras->getInt(1);
        
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO user_search VALUES(DEFAULT,?,?,?,?,?)")); 
        stmnt->setInt(1,(int)j["user_pk"]);
        stmnt->setFloat(2,(float)j["carat"]);
        stmnt->setInt(3,(int)j["color"]);
        stmnt->setInt(4,(int)j["clarity"]);
        stmnt->setDouble(5,(double)j["price"]);
        stmnt->executeQuery();
        k="회원가입 완료";
        return k;    
    }            
    catch(const sql::SQLException& e)
    {
        std::cerr << e.what() << '\n';
    }

    return (string)"회원가입 실패";
}



string GetSearchData(string msg)
{
    try
    {
        json j=json::parse(msg);
        std::unique_ptr<sql::PreparedStatement> atmnt(conn->prepareStatement("SELECT user_pk FROM userdata WHERE user_name= ?"));
        atmnt->setString(1,(string)j["username"]);
        std::unique_ptr<sql::ResultSet> ras(atmnt->executeQuery());
        ras->next();
        j["user_pk"]=ras->getInt(1);
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT user_carat,user_color,user_clarity,user_price FROM user_search WHERE user_pk=? ")); 
        stmnt->setInt(1,(int)j["user_pk"]);
        std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
        json result;
        result["carat"]=json::array();
        result["color"]=json::array();
        result["clarity"]=json::array();
        result["price"]=json::array();
        while (res->next())
        {        
            result["carat"] +=res->getFloat(1);
            result["color"] +=res->getInt(2);
            result["clarity"] +=res->getInt(3);
            result["price"] +=res->getInt(4);
        }
        puts(result.dump().c_str());
        return result.dump(4);
    }
    catch(const sql::SQLException& e)
    {        
        std::cerr << e.what() << '\n';
    }
    

}

//SELECT AVG(wauf),AVG(animal),AVG(program),AVG(kind),AVG(back) FROM survay;

};


#endif 