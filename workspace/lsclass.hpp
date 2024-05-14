#ifndef LSCLASS_H__
#define LSCLASS_H__
#include<iostream>
#include<string>
#include<mariadb/conncpp.hpp>
#include<sstream>
using namespace std;
class lsclass
{

private:

protected:
std::unique_ptr<sql::Connection> setting()
{
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/BOOKS");
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "AKM"}, {"password", "1234"}});
        
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    return conn;    
}
std::unique_ptr<sql::Connection> conn=setting();
public:
    lsclass(/* args */)
    {
    }
    ~lsclass()
    {}

    std::string sign_up(std::string msg)
    {
        try{
        istringstream iss(msg);
        string splitmsg[6];
        string k="-1";
        for (int i = 0; i < 6; i++)
        {
            getline(iss,splitmsg[i],',');
        }
        unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT glcid FROM GLID WHERE glcid = ?"));
        stmnt->setString(1,splitmsg[3]);
        sql::ResultSet* res=stmnt->executeQuery();
        if(res->rowsCount()==0){
        
        unique_ptr<sql::PreparedStatement> statement(conn->prepareStatement("INSERT INTO GLID VALUES(DEFAULT,?,DEFAULT,?,?,?,?)"));
        statement->setString(1,splitmsg[1]);//name
        statement->setString(2,splitmsg[2]);//address
        statement->setString(3,splitmsg[3]);//id
        statement->setString(4,splitmsg[4]);//pw
        statement->setString(5,splitmsg[5]);//pnum
        statement->executeQuery();
        k= "회원가입 되었습니다.";
        return k;
        }
        else
        {   k="회원가입 실패";
            return k;
        }
        
        return k;
        }
        catch(sql::SQLException &e)
        {
            cerr<<"SQLException: "<<e.what()<<endl;
        }
    }
};

#endif LSCLASS_H_
