#ifndef LSCLASS_H__
#define LSCLASS_H__
#include<iostream>
#include<string>
#include<mariadb/conncpp.hpp>
#include<sstream>
#include<map>
#define YEAR 20240000;
using namespace std;
class lsclass
{
private:
bool login;
int glpid;
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
        login=false;
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
        if(res->rowsCount()==0)
        {
        unique_ptr<sql::PreparedStatement> statement(conn->prepareStatement("INSERT INTO GLID VALUES(DEFAULT,?,CURDATE(),DEFAULT,?,?,?,?,DEFAULT,DEFAULT,DEFAULT)"));
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
        return 0;
    }
    
    
    std::string loginService(std::string msg) //loginService
    { try{
        istringstream iss(msg);
        string splitmsg[3];
        string k="-1";
        for (int i = 0; i < 3; i++)
        {
            getline(iss,splitmsg[i],',');
        }
        unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT glcid,glcpw,glp FROM GLID WHERE glcid = ?"));
        stmnt->setString(1,splitmsg[1]);
        sql::ResultSet* res=stmnt->executeQuery();

        if(res->rowsCount() !=0)
        {
            res->next();
            if(res->getString(2)==splitmsg[2])
            {
                this->login=true;
                this->glpid=res->getInt(3);
                k="로그인 성공!";
                return k;
            }
            else
        k="아이디 또는 패스워드 오류";
            return k;
        }
        else
        {
            k="아이디 또는 패스워드 오류";
            return k;
        }
        return k;
        }
        catch(sql::SQLException &e)
        {
            cerr<<"SQLException: "<<e.what()<<endl;
        }
        return 0;
    }

    std::string rental(std::string msg)
    {
        try{
        istringstream iss(msg);
        string splitmsg[2];
        string k="-1";
        if(this->login==false)
        {
            k="로그인해주세요.";
            return k;
        }
        else
        {
            for (int i = 0; i < 2; i++)
            {
                getline(iss,splitmsg[i],',');
            }
            unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT vip FROM GLID WHERE glp = ?"));
            stmnt->setInt(1,this->glpid);
            sql::ResultSet* res=stmnt->executeQuery();
            string datebegin;
            string dateend;
            res->next();
            if(res->getInt(1)==0)
            {
                unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT CURDATE(),ADDDATE(CURDATE(),4)"));
                res=stmnt->executeQuery();
                res->next();
                datebegin=res->getString(1);
                dateend=res->getString(2);
                
                unique_ptr<sql::PreparedStatement> atmnt(conn->prepareStatement("SELECT bookcode FROM RENT WHERE bookcode = ?"));
                
                //stmnt(conn->prepareStatement("SELECT bookcode FROM RENT WHERE bookcode = ?"));
                atmnt->setString(1,splitmsg[1]);
                res=atmnt->executeQuery();
                if(res->rowsCount()!=0)
                {
                    k="이미 대여된 책입니다.";
                    return k;
                }
                unique_ptr<sql::PreparedStatement> ztmnt(conn->prepareStatement("INSERT INTO RENT VALUES(DEFAULT,?,?,?,?)"));
                ztmnt->setString(1,splitmsg[1]);
                ztmnt->setInt(2,this->glpid);
                ztmnt->setString(3,datebegin);
                ztmnt->setString(4,dateend);
                ztmnt->executeQuery();

                k="대여완료";
                return k;
            }
            
            else if(res->getInt(1)==1)
            {
                unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT CURDATE(),ADDDATE(CURDATE(),7)"));
                res=stmnt->executeQuery();
                res->next();
                datebegin=res->getString(1);
                dateend=res->getString(2);
                
                unique_ptr<sql::PreparedStatement> atmnt(conn->prepareStatement("SELECT bookcode FROM RENT WHERE bookcode = ?"));
                atmnt->setString(1,splitmsg[1]);
                res=atmnt->executeQuery();
                if(res->rowsCount()!=0)
                {
                    k="이미 대여된 책입니다.";
                    return k;
                }
                unique_ptr<sql::PreparedStatement> ztmnt(conn->prepareStatement("INSERT INTO RENT VALUES(DEFAULT,?,?,?,?)"));
                ztmnt->setString(1,splitmsg[1]);
                ztmnt->setInt(2,this->glpid);
                ztmnt->setString(3,datebegin);
                ztmnt->setString(4,dateend);
                ztmnt->executeQuery();
                k="대여완료";
                return k;

            }
            
            else if(res->getInt(1)>1)
            {
                unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT bandate FROM GLID WHERE glp= ?"));
                stmnt->setInt(1,this->glpid);
                sql::ResultSet* res=stmnt->executeQuery();
                res->next();
                k=res->getString(1)+"까지 이용이 불가합니다.";
                return k;
            }    
            
            return k;
            //vip가 0이면 일반 1이면 우수회원 2면 블랙회원
            //select CURDATE(),ADDDATE(CURDATE(),4);
        }
    }catch(sql::SQLException &e)
    {
        cerr<<"SQLException :"<<e.what()<<endl;
    }
    }

    std::string giveBack(std::string msg)
    {   
        try{
        istringstream iss(msg);
        string splitmsg[2];
        string k="-1";
        string enddate[4];
        for (int i = 0; i < 2; i++)
        {
            getline(iss,splitmsg[i],',');
        }
        if(this->login==false)
        {
            k="로그인해주세요.";
            return k;
        }
        else
        {
                unique_ptr<sql::PreparedStatement> atmnt(conn->prepareStatement("SELECT bookcode,glp,rentend FROM RENT WHERE bookcode = ?"));
                sql::ResultSet* res;
                string ndate[4];
                char realenddate[3][5];
                atmnt->setString(1,splitmsg[1]);
                res=atmnt->executeQuery();
                res->next();
                enddate[0]=res->getString(3);
                int* indate=new int[3];
                int* iete= new int[3];
                if(res->rowsCount()!=0 && res->getInt(2)==this->glpid)
                {
                    unique_ptr<sql::PreparedStatement> ztmnt(conn->prepareStatement("DELETE FROM RENT WHERE bookcode = ?"));
                    ztmnt->setString(1,splitmsg[1]);
                    ztmnt->executeQuery();
                    
                    istringstream sst(enddate[0]);
                    for (int i = 1; i < 4; i++)
                    {
                        getline(sst,enddate[i],'-');
                        enddate[i].copy(realenddate[i-1],enddate[i].length());
                        realenddate[i-1][enddate[i].length()]=0;
                        iete[i-1]=atoi(realenddate[i-1]);
                    }

                    
                    unique_ptr<sql::PreparedStatement> ftmnt(conn->prepareStatement("SELECT CURDATE()"));
                    res=ftmnt->executeQuery();
                    res->next();
                    ndate[0]=res->getString(1);
                    istringstream ssdt(ndate[0]);
                    char realndate[3][5];
                    
                    for (int i = 1; i < 4; i++)
                    {
                        getline(ssdt,ndate[i],'-');
                        ndate[i].copy(realndate[i-1],ndate[i].length());
                        realndate[i-1][ndate[i].length()]=0;
                        indate[i-1]=atoi(realndate[i-1]);
                    }
                    // cout<<realenddate[0]<<realndate[0];
                    if(indate[0] > iete[0] || indate[1] > iete[1] || indate[2] > iete[2])
                    {
                        int latecount;
                        string j="";
                        unique_ptr<sql::PreparedStatement> ltmnt(conn->prepareStatement("SELECT latecount FROM GLID WHERE glp = ?"));
                        ltmnt->setInt(1,this->glpid);
                        res=ltmnt->executeQuery();
                        res->next();
                        latecount=res->getInt(1);                        
                        if(latecount +1 == 3)
                        {
                            
                            unique_ptr<sql::PreparedStatement> btmnt(conn->prepareStatement("UPDATE GLID SET vip = 2  where glp = ?"));
                            btmnt->setInt(1,this->glpid);
                            btmnt->executeQuery();


                            string banddate;
                            unique_ptr<sql::PreparedStatement> htmnt(conn->prepareStatement("SELECT ADDDATE(CURDATE(),30) "));
                            res=htmnt->executeQuery();
                            res->next();
                            banddate = res->getString(1);
                            unique_ptr<sql::PreparedStatement> vtmnt(conn->prepareStatement("UPDATE GLID SET bandate = ?  where glp = ?"));
                            vtmnt->setString(1,banddate);
                            vtmnt->setInt(2,this->glpid);
                            vtmnt->executeQuery();
                            j="3회 연체하셔서 " +banddate+ " 까지 block 되셨습니다.\n";
                        }

                        unique_ptr<sql::PreparedStatement> btmnt(conn->prepareStatement("UPDATE GLID SET latecount = ? where glp = ?"));
                        btmnt->setInt(1,latecount+1);
                        btmnt->setInt(2,this->glpid);
                        btmnt->executeQuery();
                        k= j+"반납완료되었습니다.";
                        delete indate;
                        delete iete;
                        
                        return k;

                    } 
                    else
                    {
                        string j="";
                        int rentcount;
                        unique_ptr<sql::PreparedStatement> ltmnt(conn->prepareStatement("SELECT rentcount,latecount FROM GLID WHERE glp = ?"));
                        ltmnt->setInt(1,this->glpid);
                        res=ltmnt->executeQuery();
                        res->next();
                        rentcount=res->getInt(1);

                        unique_ptr<sql::PreparedStatement> btmnt(conn->prepareStatement("UPDATE GLID SET rentcount = ?  where glp = ?"));
                        btmnt->setInt(1,rentcount+1);
                        btmnt->setInt(2,this->glpid);
                        btmnt->executeQuery();

                        delete indate;
                        delete iete;    
                        k=j+" 반납완료되었습니다.감사합니다.";
                        return k;   
                    }
                    
                    delete indate;
                    delete iete;
                
                    k="반납완료되었습니다.";
                    return k;
                }
                else
                {
                    delete indate;
                    delete iete;
                    k="대여한 책이아닙니다.";
                    return k;
                }
        }
        return k;
    }catch(sql::SQLException &e)
    {
        cerr<<"SQLException : "<<e.what()<<endl;
    }
    }

    int datesplit(string date)
    {
        istringstream iss;
        ostringstream oss;
        string split[3];
        iss.str(date);
        for (int i = 0; i < 3; i++)
        {
            getline(iss,split[i],'-');
        }
        oss<<split[0]<<split[1]<<split[2];
        int idate=stoi(oss.str());
        return idate;
    }

    int givemonth(int date)
    {
        int month;
        month =date%YEAR;
        month=month/100;
        switch (month)
        {
        case 1:
            return 100-31;
            break;
        case 2:
            return 100-28;
            break;
        case 3:
            return 100-31;
        case 4:
            return 100-30;
            break;    
        case 5:
            return 100-31;
            break;        
        case 6:
            return 100-30;
            break;
        case 7:
            return 100-31;
            break;
        case 8:
            return 100-31;
            break;
        case 9:
            return 100-30;
            break;
        case 10:
            return 100-31;
            break;
        case 11:
            return 100-30;
            break;
        case 12:
            return 100-31;
            break;                        
        default:
            break;
        }
    }

    void dateCheck( )
    {
       try{ 
        multimap<int,string> rentcheck;
        map<int,string> signcheck;
        map<int,int> rentcount;
        map<int,int> latecount;
        multimap<int,string>::iterator iter;
        multimap<int,int>::iterator ater;
        sql::ResultSet* res;
        string cdate;
        string endate;
        int* cccdate=new int;
        int* eeedate=new int;
        int* one=new int;
        *one=0;
    
        while (1)
        {
            sleep(10);
            unique_ptr<sql::PreparedStatement> btmnt(conn->prepareStatement("SELECT glp,rentend FROM RENT"));
            res=btmnt->executeQuery();
            while(res->next())
            {
                rentcheck.insert(pair<int,string>(res->getInt(1),res->getString(2)));
                    
            }
            unique_ptr<sql::PreparedStatement> pstt(conn->prepareStatement("SELECT CURDATE()"));
            res=pstt->executeQuery();
            res->next();
            cdate = res->getString(1);    
            *cccdate=datesplit(cdate);
            unique_ptr<sql::PreparedStatement> wtmnt(conn->prepareStatement("SELECT glp,signeddate,rencount,latecount FROM GLID"));
            res=wtmnt->executeQuery();
            while (res->next())
            {
                signcheck.insert(pair<int,string>(res->getInt(1),res->getString(2))) ;
                
            }
            

            for ( iter = rentcheck.begin(); iter!=rentcheck.end(); ++iter)
            {
                *eeedate=datesplit(iter->second);
                
                if(*cccdate-*eeedate-givemonth(*eeedate) >=14)
                {
                    if(*one!=iter->first)
                    {
                        *one=iter->first;
                    
                    unique_ptr<sql::PreparedStatement> xtmnt(conn->prepareStatement("UPDATE GLID SET vip = 2 WHERE glp = ?"));
                        xtmnt->setInt(1,iter->first);
                        xtmnt->executeQuery();

                    cout<<iter->first<<"블랙\n";
                    }      
                }
            } 
            
            for ( iter =signcheck.begin(); iter!=signcheck.end(); ++iter)
            {
                *cccdate=*cccdate%YEAR;
                if(*cccdate>10000)
                    *cccdate-10000+1200;
                *eeedate=datesplit(iter->second)%YEAR;
                *cccdate=*cccdate/100;
                *eeedate=*eeedate/100;
                if(*cccdate-*eeedate>=6)
                {
                    
                }  
            }
            
                
        
            unique_ptr<sql::PreparedStatement> otmnt(conn->prepareStatement("UPDATE GLID SET vip = 1  where glp = ?"));
        
        }
    }catch(sql::SQLException &e)
    {
        cerr<<"sql::SQLException: "<<e.what()<<endl;
    } 
    }

};

#endif LSCLASS_H_