#ifndef ZMSCLASS_K__
#define ZMSCLASS_K__
#include<iostream>
#include<string>
#include<sstream>
#include<mariadb/conncpp.hpp>
#include<nlohmann/json.hpp>
using namespace std;
using json=nlohmann::json;
//Customer들의 정보를 담은 헤더파일
class King 
{
private:
        
protected:
std::unique_ptr<sql::Connection> setting()
{
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/GHRD");
        
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
    King(/* args */){}
    ~King(){}
//로그인 함수

string GetAccount(string msg)
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
    json j =json::parse(msg);
    
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

string Get_gdp(string msg)
{
   try
   {           
    string k="데이터를 찾을 수 없는 국가입니다.";
    ostringstream oss;
    long max=0;
    long data;
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT gdp2013,gdp2014,gdp2015,gdp2016,gdp2017,gdp2018,gdp2019,gdp2020 FROM gdp WHERE CountryName = ?"));
    stmnt->setString(1,msg);
    unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
    if(res->rowsCount()==0)
    {
        k="데이터없음";
        return k;
    }
    while (res->next())
    {
        data=res->getLong(1);        
        max= max<data ? data:max;
        data=res->getLong(2);
        max= max<data ? data:max;
        data=res->getLong(3);
        max= max<data ? data:max;
        data=res->getLong(4);
        max= max<data ? data:max;
        data=res->getLong(5);
        max= max<data ? data:max;
        data=res->getLong(6);
        max= max<data ? data:max;
        data=res->getLong(7);
        max= max<data ? data:max;
        }
    if(max==NULL)
        return k;
    oss<<max;
    return oss.str();
    
    }catch(const sql::SQLException& e)
    {
        std::cerr << e.what() << '\n';
    }
    return NULL;
}


string GdpAndMadls()
{
    //SELECT A.team,A.SOG_total_medals,B.gdp2013,B.gdp2014,B.gdp2015,B.gdp2016,B.gdp2017,B.gdp2018,B.gdp2019,B.gdp2020 FROM winter as A INNER JOIN gdp as B ON A.code=B.Code;
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT A.SOG_total_medals,B.gdp2013,B.gdp2014,B.gdp2015,B.gdp2016,B.gdp2017,B.gdp2018,B.gdp2019,B.gdp2020,A.team FROM winter as A INNER JOIN gdp as B ON A.code=B.Code;"));
    unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
    int medals;
    int medalsSum=0;
    long gdp;
    long gdpMax=0;
    ostringstream oss;
    vector<int> madals;
    vector<long> Gdpcont;
    vector<string> name;
    while (res->next())
    {                
        oss<<"CountryName:"<<res->getString(10)<<" 2013gdp: ";
        oss<<res->getLong(2)<<" 2014gdp:";
        oss<<res->getLong(3)<<" 2015gdp:";
        oss<<res->getLong(4)<<" 2016gdp:";
        oss<<res->getLong(5)<<" 2017gdp:";
        oss<<res->getLong(6)<<" 2018gdp:";
        oss<<res->getLong(7)<<" 2019gdp:";
        oss<<res->getLong(8)<<" 2020gdp:";
        oss<<res->getLong(9)<<" total_madals:";
        oss<<res->getInt(1)<<"\n";
    } 
    //gdp 8개    
    return oss.str();  
}

string Get_SummerOlyp(string msg)
{        
   try
   { 
    if(msg.compare("ALL")==0)
    {
        ostringstream oss("");
        string name;
        int num[5];
        string data;
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT * FROM summer"));
        unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
        while (res->next())
        {
            name=res->getString(2);
            num[0]=res->getInt(3);
            num[1]=res->getInt(4);
            num[2]=res->getInt(5);
            num[3]=res->getInt(6);
            num[4]=res->getInt(7);
            oss<<name<<": Gold: "<<num[0]<<" Silver: "<<num[1]<<" Bronze: "<<num[2]<<" Total: "<<num[3]<<" Rank: "<<num[4]<<"\n";
        }
        return oss.str();
    }
    ostringstream oss("");
    sql::SQLString data =msg;
    string name;
    int num[4];
    //std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT Gold,Silver,Bronze,Rank_by_Total FROM summer WHERE country = ?"));
    stmnt->setString(1,msg);
    // unique_ptr<sql::ResultSet>res(stmnt->executeQuery("SELECT gold,silver,bronze,total FROM summer WHERE country ='United States';"));
    unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
    res->next();
    num[0]=res->getInt(1);
    num[1]=res->getInt(2);
    num[2]=res->getInt(3);
    num[3]=res->getInt(4);
    oss<<msg<<": Gold: "<<num[0]<<": silver:"<<num[1]<<": bronze :"<<num[2]<<" : total :"<<num[3]<<"\n";
    return oss.str();
    }catch(sql::SQLException e)
    {
        cerr<<e.what()<<endl;
    }
}


};
#endif