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

class chatserver 
{
private:
        
protected:
std::unique_ptr<sql::Connection> setting()
{
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/Animal");
        
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


string GetAccount(string msg)
{
    try
    {
    json j=json::parse(msg);
    string k;
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO cs_info VALUES(DEFAULT,?,?,?)"));
    stmnt->setString(1,(string)j["userdata"][0]);
    stmnt->setString(2,(string)j["userdata"][1]);
    stmnt->setString(3,(string)j["userdata"][2]);
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

string GetAccount2(string msg)
{
    try
    {
    json j=json::parse(msg);
    string k;
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO customer_info VALUES(DEFAULT,?,?,?)"));
    stmnt->setString(1,(string)j["userdata"][0]);
    stmnt->setString(2,(string)j["userdata"][1]);
    stmnt->setString(3,(string)j["userdata"][2]);
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

int getlogin(string msg)
{

    json j=json::parse(msg);
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT cs_pk,cs_name FROM cs_info WHERE cs_id = ? AND cs_pw= ?"));
    stmnt->setString(1,(string)j["id"]);
    stmnt->setString(2,(string)j["pw"]);
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

int getlogin2(string msg)
{
   
    json j=json::parse(msg);
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT customer_pk,customer_name FROM customer_info WHERE customer_id = ? AND customer_pw= ?"));
    stmnt->setString(1,(string)j["id"]);
    stmnt->setString(2,(string)j["pw"]);
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

string surveySave(string msg)
{
    try{
    json j=json::parse(msg);
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO survay VALUES(?,?,?,?,?,?)"));
    stmnt->setString(1,(string)j["myname"]);
    stmnt->setInt(2,atoi(((string)j["wauf"]).c_str()));
    stmnt->setInt(3,atoi(((string)j["animal"]).c_str()));
    stmnt->setInt(4,atoi(((string)j["program"]).c_str()));
    stmnt->setInt(5,atoi(((string)j["kind"]).c_str()));
    stmnt->setInt(6,atoi(((string)j["back"]).c_str()));
    stmnt->executeQuery();
    }catch(sql::SQLException &e)
    {
        return e.what();
    }

    return (string)"저장성공!";
}

string Getsurvey(string msg)
{
    try
    {
        json j=json::parse(msg);
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT wauf,animal,program,kind,back FROM survay WHERE cusname = ? "));
        stmnt->setString(1,(string)j["cusname"]);
        unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
        json k;
        k["wauf"]=json::array();
        k["animal"]=json::array();
        k["program"]=json::array();
        k["kind"]=json::array();
        k["back"]=json::array();
        
        while(res->next())
        {
        k["wauf"]+=res->getInt(1);
        k["animal"]+=res->getInt(2);
        k["program"]+=res->getInt(3);
        k["kind"]+=res->getInt(4);
        k["back"]+=res->getInt(5);
        }    
        string data=k.dump(1);

        return data;       
    }catch(sql::SQLException &e)
    {
        return e.what();
    }catch(json::exception &e){
        return (string)"이름을 확인해주세요";
    }
    return (string)"문제가있습니다";
}

//SELECT AVG(wauf),AVG(animal),AVG(program),AVG(kind),AVG(back) FROM survay;



string GetsurveyAVG(string msg)
{
    try
    {
        
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT AVG(wauf),AVG(animal),AVG(program),AVG(kind),AVG(back) FROM survay"));        
        unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
        json k;
                
        while(res->next())
        {
            k["wauf"]=to_string(res->getDouble(1));
            k["animal"]=to_string(res->getDouble(2));
            k["program"]=to_string(res->getDouble(3));
            k["kind"]=to_string(res->getDouble(4));
            k["back"]=to_string(res->getDouble(5));
        }    
        
        string data=k.dump(2);

        return data;       
    }catch(sql::SQLException &e)
    {
        return e.what();
    }
    return (string)"문제가있습니다";
}


void Counseling(string csaka,string cusaka,string msg)
{
    try{
    int cs_info;
    int cus_info;
    ostringstream oss;
    time_t curTime =time(NULL);
    tm* PLocal =NULL;
    PLocal=localtime(&curTime);
    localtime_r(&curTime,PLocal);
    oss<<PLocal->tm_year+1900<<PLocal->tm_mon +1<<PLocal->tm_mday<<PLocal->tm_hour
    <<PLocal->tm_min<<PLocal->tm_sec;  
    string filename=oss.str()+csaka+"to"+cusaka+".txt";
    string filepath="/home/lms/test/myc-1/TextFolder/"+filename;
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT cs_pk FROM cs_info WHERE cs_name=?"));
    stmnt->setString(1,csaka);
    unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
    res->next();
    cs_info=res->getInt(1);
    std::unique_ptr<sql::PreparedStatement> atmnt(conn->prepareStatement("SELECT customer_pk FROM customer_info WHERE customer_name=?"));
    atmnt->setString(1,cusaka);
    unique_ptr<sql::ResultSet>zes(atmnt->executeQuery());
    zes->next();
    cus_info=zes->getInt(1);
    ofstream fout;
    fout.open(filepath);
    fout<<msg;
    fout.close();    
    std::unique_ptr<sql::PreparedStatement> ktmnt(conn->prepareStatement((string)"INSERT INTO Animal.qna_info"+
    (string)"(qna_pk, cs_name, customer_name, cs_unique, customer_unique, datapath,qna_date)VALUES(DEFAULT,?,?,?,?,?,NOW())"));
    ktmnt->setString(1,csaka);
    ktmnt->setString(2,cusaka);
    ktmnt->setInt(3,cs_info);
    ktmnt->setInt(4,cus_info);
    ktmnt->setString(5,filepath);    
    ktmnt->executeQuery();    
}catch(sql::SQLException &e)
{
    cerr<<e.what()<<endl;
}
}
};


#endif 