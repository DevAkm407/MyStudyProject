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

    oss<<max;
    return oss.str();
    
    }catch(const sql::SQLException& e)
    {
        std::cerr << e.what() << '\n';
    }
    return NULL;
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
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT Country, code, Gold, Silver, Bronze, Total, Rank_by_Total FROM GHRD.summer;"));
        unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
        while (res->next())
        {
            
            oss<<"국가이름:"<<res->getString(1)<<" 코드"
            <<res->getString(2)<<" 금매달:"
            <<res->getInt(3)<<" 은매달:"
            <<res->getInt(4)<<" 동매달:"
            <<res->getInt(5)<<" 총합매달수:"
            <<res->getInt(6)<<" 등수:"
            <<res->getInt(7)<<"\n";
          
        }
        return oss.str();
    }
    ostringstream oss("");
    sql::SQLString data =msg;
    string name;
    int num[4];
//    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
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


string PopuAndMedals()
{
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT A.SOG_total_medals, B.population2022 FROM winter as A INNER JOIN world_population as B ON A.code=B.CCA3"));
    unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
    int medals;
    int medalsSum=0;
    long population;
    long populationSum=0;
    ostringstream oss;
    while (res->next())
    {
        medalsSum +=res->getInt(1);
        populationSum +=res->getLong(2);
    }

    oss<<medalsSum<<" "<<populationSum;
    return oss.str();
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

string customer_info(string msg)
{
    //SELECT A.customer_name,A.customer_id,B.cs_name,B.qna_date FROM customer_info as A INNER JOIN qna_info AS B ON A.customer_name=B.customer_name where A.customer_name=?
    try{
    ostringstream oss;
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT A.customer_name,A.customer_id,B.cs_name,B.qna_date FROM customer_info as A INNER JOIN qna_info AS B ON A.customer_name=B.customer_name where A.customer_name=?"));
    stmnt->setString(1,msg);
    std::unique_ptr<sql::ResultSet>res(stmnt->executeQuery());    
    while (res->next())
    {
        oss<<"고객이름:"<<res->getString(1)<<" "
        <<"고객ID:"<<res->getString(2)<<" "
        <<"이전상담사이름:"<<res->getString(3)<<" "
        <<"이전상담일시:"<<res->getString(4)<<endl;
    }
    return oss.str();
    }catch(sql::SQLException &e)
    {
        puts(e.what());
    }
    string k="시스템 에러";
    return k;
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
    std::unique_ptr<sql::PreparedStatement> ktmnt(conn->prepareStatement((string)"INSERT INTO GHRD.qna_info"+
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
// //친구 찾기
// string findmyfriend()
// {
//     try{
//     if(login!=0)
//     {
//         ostringstream oss;
//         istringstream iss;
//         stringstream ss;
//         string myfrined;
//         vector<string> svec;
//         std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT myfriend from FRIEND WHERE proposer = ?"));
//         stmnt->setInt(1,login); 
        
//         unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
//         while (res->next())
//         {
//             myfrined=res->getString(1);
//             oss<<myfrined<<" ";
//         }
//         myfrined=oss.str();
//         ss.str(myfrined);
//         while (ss>> myfrined)
//         {
//         svec.emplace_back(myfrined);
//         }
//         vector<string>::iterator iter;
//         ostringstream ops;
//         istringstream azs;
        
//         for ( iter =svec.begin(); iter !=svec.end(); ++iter)
//         {   
//             myfrined=iter->substr(iter->find("-")+1);
//             ops<<myfrined<<" ";   
//         }
//         return ops.str();
//     }
//     string k="로그인하세요";
//     return k;
// }catch(sql::SQLException &e)
// {
//     cerr<<"SQL ERROR"<<e.what()<<endl;
// }
// return 0;
// }

// //친구목록 확인 파츠
// string akamyfriends(string msg)
// {
// try{
//     stringstream ss(msg);
//     ostringstream oss;
//     int buffer;
//     vector<int> myfriendfid;
//     while (ss>> buffer)
//     {
//         myfriendfid.emplace_back(buffer);
//     }
//     vector<int>::iterator iter;
//     string ls;
//     char c;
//     for ( iter =myfriendfid.begin(); iter!=myfriendfid.end() ; ++iter)
//     {
//         // cout<<*iter<<endl;
//         std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT aka FROM MEMBER WHERE fid = ?"));
//         stmnt->setInt(1,*iter);
//         unique_ptr<sql::ResultSet>res(stmnt->executeQuery());
//         res->next();
//         ls=res->getString(1);
//         oss<<*iter<<" "<<ls<<"\n";
    
//     }
// return oss.str();
// }catch(sql::SQLException &e)
// {
//     cerr<<"SQL ERROR"<<e.what()<<endl;
// }
// }

// //내 친구목록 확인
// string showMyFriend()
// {
//     string k,j;
//     k=findmyfriend();
//     j=akamyfriends(k);
//     return j;
// }

// //친구신청목록 확인
// string checkFriendRequest(int fid)
// {  
//     try{
//     unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT SHOOTER FROM SHOOTFRIEND WHERE TARGET = ?"));
//     stmnt->setInt(1,fid);
//     sql::ResultSet* res=stmnt->executeQuery();
//     string k;
//     ostringstream oss;
//     if(res->rowsCount()==0)
//     {
//             k="0";
//             return k;
//     }
//     sql::ResultSet* gess;
//     while (res->next())
//     {
//         unique_ptr<sql::PreparedStatement> ntmnt(conn->prepareStatement("SELECT aka FROM MEMBER WHERE fid = ?"));
//         ntmnt->setInt(1,res->getInt(1));
//         gess=ntmnt->executeQuery();
//         gess->next();
//         k=gess->getString(1);
//         oss<<res->getInt(1)<<": "<<k<<"님에게 친구요청이왔습니다.\n";
//     }    
//     k=oss.str();
//     return k;
//     }catch(sql::SQLException &e)
//     {
//         string j="sql에러";
//         cerr<<"SQLException: "<<e.what()<<endl;
//         return j;
//     }
//     return NULL;
// }

// //친구신청목록 확인후 수락하는 함수
// void registFriend(int myfid,int shootfid)
// {
//     try{
//     ostringstream oss;
//     unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO FRIEND VALUES(DEFAULT,?,?)"));
//     oss<<shootfid<<"-"<<myfid;
//     stmnt->setInt(1,shootfid);
//     stmnt->setString(2,oss.str()); 
//     oss.str("");
//     sql::ResultSet* res=stmnt->executeQuery();
//     unique_ptr<sql::PreparedStatement> ntmnt(conn->prepareStatement("INSERT INTO FRIEND VALUES(DEFAULT,?,?)"));
//     oss<<myfid<<"-"<<shootfid;
//     ntmnt->setInt(1,myfid);
//     ntmnt->setString(2,oss.str()); 
//     res=ntmnt->executeQuery();
    
//     unique_ptr<sql::PreparedStatement> ztmnt(conn->prepareStatement("DELETE FROM SHOOTFRIEND WHERE SHOOTER = ? AND TARGET = ? "));
//     ztmnt->setInt(1,shootfid);
//     ztmnt->setInt(2,myfid);
//     res=ztmnt->executeQuery();
//     }catch(sql::SQLException &e)
//     {
//         cerr<<"SQLException: "<<e.what();
//     }
// }

// //친구 거절
// void rejectFriend(int myfid,int shootfid)
// {
//   try
//     {  
//         unique_ptr<sql::PreparedStatement> ztmnt(conn->prepareStatement("DELETE FROM SHOOTFRIEND WHERE SHOOTER = ? AND TARGET = ? "));
//         ztmnt->setInt(1,shootfid);
//         ztmnt->setInt(2,myfid);
//         sql::ResultSet* res=ztmnt->executeQuery();
//     }catch(sql::SQLException &e)
//     {
//         cerr<<"SQLException: "<<e.what();
//     }
// }


// //친구요청
// string shoot(int myfid,int targetfid)
// {
//     ostringstream oss;
//     string k;
//     unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO SHOOTFRIEND VALUES(DEFAULT,?,?,0)"));
//     stmnt->setInt(1,myfid);
//     stmnt->setInt(2,targetfid);
//     sql::ResultSet* res=stmnt->executeQuery();
    
//     std::unique_ptr<sql::PreparedStatement> ztmnt(conn->prepareStatement("SELECT aka FROM MEMBER WHERE fid = ?"));
//     ztmnt->setInt(1,targetfid);
//     res=ztmnt->executeQuery();
//     res->next();
//     k=res->getString(1);
//     oss<<k<<"님에게 친구요청완료 \n";
//     k=oss.str();
//     return k;
// }
};


#endif 