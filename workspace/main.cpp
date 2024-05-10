// Includes
#include <iostream>
#include <mariadb/conncpp.hpp>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>

// DELETE문 실행 함수(id를 이용한)
std::vector<std::string> split(std::string str, char Delimiter)
{
    std::istringstream iss(str); // istringstream에 str을 담는다.
    std::string buffer;          // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
    std::vector<std::string> result;

    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (getline(iss, buffer, Delimiter))
    {
        result.push_back(buffer); // 절삭된 문자열을 vector에 저장
    }
    return result;
}

void deleteTask(std::unique_ptr<sql::Connection> &conn, std::string name) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("delete from tasks where name = ?"));
        // 객체에 값을 전달
        stmnt->setString(1, name);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        stmnt->executeQuery();
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error deleting task: " << e.what() << std::endl;
   }
}

// UPDATE문 실행 함수(이름을 이용하여 성별을 바꿈)
void updateTask(std::unique_ptr<sql::Connection> &conn, std::string name, int gender) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("update AIR set NUMR = ? where REGION = ?"));
        // 객체에 값을 전달
        stmnt->setInt(1, gender);
        stmnt->setString(2, name);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        stmnt->executeQuery();
        // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error updating task status: " << e.what() << std::endl;
   }
}
// Insert문 실행 함수
// 인자로 값을 넣는다. (id값은 AUTO_INCEREMENT이기 때문에 없어도 상관 없다.)
void addTask(std::unique_ptr<sql::Connection> &conn, std::string name, int age, bool gender) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into tasks values (default, ?, ?, ?)"));
        // 객체에 값을 전달
        stmnt->setString(1, name);
        stmnt->setInt(2, age);
        stmnt->setBoolean(3, gender);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        stmnt->executeQuery();
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
   }
}

// SELECT문 실행 함수
// void showTasks(std::unique_ptr<sql::Connection> &conn, std::string mydate, std::string myregion) {
//     try {
//         // createStaemet 객체 생성
//         std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        
//         // 쿼리를 실행
//         sql::SQLString date = "SELECT A.REGION,FESTIVAL.ENAME,A.DUST,A.SDUST FROM FESTIVAL INNER JOIN (SELECT NUMR ,MIN(DATE) AS DATE ,REGION,AVG(DUST) AS DUST,AVG(SDUST) AS SDUST  FROM AIR WHERE DATE LIKE ";
//         sql::SQLString when =" '%-"+mydate+" %'"; //'%-05-01 %'
//         sql::SQLString region = " AND REGION = '"  + myregion+ "' "; //= '중랑구' )~~~~
//         sql::SQLString rest =")AS A ON FESTIVAL.NUMR =A.NUMR ";

//         sql::ResultSet *res = stmnt->executeQuery(date+when+region+rest);
//         // 반복문을 통해서 내부의 값을 반환
//         while (res->next())
//         {
//             // std::cout << "id = " << res->getInt(1);
//             // std::cout << ", name = " << res->getString(2);
//             // std::cout << ", gender = ";
//             std::cout << "REGION = " << res->getString(1);
//             std::cout << ", ENAME = " << res->getString(2);
//             std::cout<< ", DUST = " <<res->getFloat(3);
//             std::cout<< ", SDUST = " <<res->getFloat(4)<<std::endl;
//             // std::cout << ", MGR = "<<res->getFloat(4);
//             // std::cout << ", HIREDATE = "<<res->getString(5);
//             // std::cout << ", SAL = "<<res->getFloat(6);
//             // std::cout << ", COMM = ";
//             // if(res->getFloat(7)==0)
//             // {
//             //     std::cout<<"NULL";
//             // }
//             // else
//             // {
//             //     std::cout<<res->getFloat(7);
//             // }
//             // std::cout << ", DEPTNO = "<<res->getFloat(8)<<std::endl;
//             // std::cout<<"사원명: "<<res->getString(1) << " 연봉: "<<res->getFloat(2)<<std::endl;            

//             // if (res->getBoolean(4)) {
//             //     std::cout << "Male" << std::endl;
//             // } else {
//             //     std::cout << "Female" << std::endl;
//             // }
//             // std::cout<<"바뀐 a: "<<a<<std::endl;    
//         }
    
//     // 실패시 오류 메세지 반환
//     } catch(sql::SQLException& e){
//       std::cerr << "Error selecting tasks: " << e.what() << std::endl;
//    }
// }
void uT(std::unique_ptr<sql::Connection> &conn) {
    std::map<std::string,std::string> mep;
    try {
        // PreparedStatement 객체 생성
        // std::unique_ptr<sql::PreparedStatement> atmnt(conn->prepareStatement("insert into tasks values (default, ?, ?, ?)"));
        // 객체에 값을 전달
        // stmnt->setString(1, name);
        // stmnt->setInt(2, age);
        // stmnt->setBoolean(3, gender);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        // stmnt->executeQuery();
        //SELECT * FROM SADDRESS
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        sql::SQLString aa ="SELECT * FROM SADDRESS";
        sql::ResultSet *ba=stmnt->executeQuery(aa);
        std::string cc,x,z;
       
        if(ba->rowsCount()==0)
            std::cout<<"쿼리문제\n";
        while (ba->next())
        {
            cc=ba->getString(3);
            std::istringstream ss(cc);   
            ss>>x>>z;
            std::cout<<z<<std::endl;
            x=ba->getString(2);
            // x+="%";
            std::cout<<x<<std::endl;
            std::unique_ptr<sql::PreparedStatement> atmnt(conn->prepareStatement("UPDATE SUBWAY SET REGION = ? WHERE STATION LIKE ?"));
            atmnt->setString(1,z);
            atmnt->setString(2,x);
            atmnt->executeQuery();
        }
        

    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
   }
}
void showSubWay(std::unique_ptr<sql::Connection> &conn, std::string mydate,std::string myregion) {
    try {
        // createStaemet 객체 생성
        std::unique_ptr<sql::Statement> sway(conn->createStatement());
        std::string zp;
        sql::ResultSet *tes=sway->executeQuery("SELECT DISTINCT LINE,STATION FROM SUBWAY WHERE REGION= '"+myregion+"'");
        while (tes->next())
        {
            std::cout<<"호선: "<<tes->getString(1);
            std::cout<<", 역이름: "<<tes->getString(2)<<std::endl;
        }
        std::cout<<"\n 혹시 찾는 역이 없습니까? y or n\n";
        getline(std::cin,zp);
        
        if(zp=="y" || zp=="Y")
        {
            std::string pp="NO%";
            tes=sway->executeQuery("SELECT LINE,STATION FROM SUBWAY WHERE REGION LIKE '데이터%' GROUP BY STATION");
            
            if(tes->rowsCount()==0)
                std::cout<<"쿼리문제\n";
            while (tes->next())
            {

            std::cout<<"호선: "<<tes->getString(1);
            std::cout<<", 역이름: "<<tes->getString(2)<<std::endl;
            }
        }
        
        
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // 쿼리를 실행
        std::cout<<"예시)서울대입구\n"<<"역 이름을 입력해주세요:";
        std::string mystation;
        getline(std::cin,mystation);
        mydate=mydate.substr(0,mydate.find('-'));
        //SELECT LINE,STATION,ROUND(AVG(TIME9TO12)) AS '9~12탑승객 평균',ROUND(AVG(TIME13TO16)) AS '13~16탑승객 평균',ROUND(AVG(TIME17TO20)) AS '17~20탑승객 평균' FROM SUBWAY WHERE MONTH LIKE '%05%' AND LINE = (SELECT DISTINCT LINE FROM SUBWAY WHERE STATION ='서울대입구') GROUP BY STATION
        sql::SQLString aa="SELECT DISTINCT LINE FROM SUBWAY WHERE STATION = '"+ mystation+"'";
        sql::ResultSet *res = stmnt->executeQuery(aa);
        std::string myline;
        int rowcount=res->rowsCount();
        while (res->next())
        {
            std::cout << "호선 이름 = " << res->getString(1)<<std::endl;
            if(rowcount==1)
            {
                myline=res->getString(1);
            }
        }
        
        if(rowcount !=1)
        {
            std::cout<<"몇 호선을 타시겠습니까? ";
            getline(std::cin,myline);          
        }        
        
        
        sql::SQLString date = "SELECT LINE,STATION,ROUND(AVG(TIME9TO12)) AS '9~12탑승객 평균',ROUND(AVG(TIME13TO16)) AS '13~16탑승객 평균',ROUND(AVG(TIME17TO20)) AS '17~20탑승객 평균' FROM SUBWAY WHERE MONTH LIKE";
        sql::SQLString when =" '%"+mydate+"%'";
        sql::SQLString region = " AND LINE ='"+myline+"'";
        sql::SQLString rest =" GROUP BY STATION";
        
        res=stmnt->executeQuery(date+when+region+rest);    
    
        if(res->rowsCount()==0)
            std::cout<<"쿼리문제있음"<<std::endl;
        // std::cout<<res->rowsCount()<<std::endl;
        while (res->next()) 
        {
            
            std::cout << "LINE = " << res->getString(1);
            std::cout << ", STATION = " << res->getString(2);
            std::cout<< ", \t\t9~12탑승객 평균= " <<res->getInt(3);
            std::cout<< ", 13~16탑승객 평균 = " <<res->getInt(4);
            std::cout<< ", 17~20탑승객 평균 = " <<res->getInt(5)<<std::endl<<std::endl;
        }   
    
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
   }

}

void showPlaceAndDust(std::unique_ptr<sql::Connection> &conn, std::string mydate, std::string myregion) {
    try {
        // createStaemet 객체 생성
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        
        // 쿼리를 실행
        sql::SQLString date = "SELECT A.REGION,FESTIVAL.BDATE,FESTIVAL.EDATE,FESTIVAL.ENAME,A.DUST,A.SDUST FROM FESTIVAL INNER JOIN (SELECT NUMR ,MIN(DATE) AS DATE ,REGION, AVG(DUST) AS DUST,AVG(SDUST) AS SDUST FROM AIR WHERE DATE LIKE ";
        sql::SQLString when =" '%-"+mydate+" %'";
        sql::SQLString region = " AND REGION = '"  + myregion+ "' ";
        sql::SQLString rest =")AS A ON FESTIVAL.NUMR =A.NUMR ";

        sql::ResultSet *res = stmnt->executeQuery(date+when+region+rest);
        // 반복문을 통해서 내부의 값을 반환
        
        while(res->rowsCount()==0){
            std::cout<<"찾은 데이터가 없습니다"<<std::endl;
            std::cout<<"시간을입력해주세요:ex)month-date ";
            getline(std::cin,mydate);
            sql::SQLString when =" '%-"+mydate+" %'";
            std::cout<<"장소을입력해주세요: ";
            getline(std::cin,myregion);
            sql::SQLString region = " AND REGION = '"  + myregion+ "' ";
            res = stmnt->executeQuery(date+when+region+rest);
        }
        std::cout<<std::endl;
        while (res->next()) 
        {
             std::cout<< "미세먼지 예상치 = " <<res->getFloat(5);
            std::cout<< ", 초미세먼지 예상치 = " <<res->getFloat(6)<<std::endl<<std::endl;
            std::cout << "지역 = " << res->getString(1);
            std::cout << ", 시작 날짜 = " << res->getString(2);
            std::cout << ", 끝나는 날짜 = " << res->getString(3);
            std::cout << ", 행사이름 = " << res->getString(4)<<std::endl<<std::endl;
           
        } 
        showSubWay(conn,mydate,myregion);
         
        res=stmnt->executeQuery("select AVG(RP_PER) from WEATHER WHERE DATE LIKE"+when);

        while (res->next())
        {
            std::cout<<"날짜: "+mydate<<" 강수확률: "<<res->getFloat(1)<<std::endl; 
        }
        
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
   }
}




int main() {
    try {
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/studyakm");
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "AKM"}, {"password", "1234"}});
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
        //중랑구 5월 1일에 해당하는 
        std::cout<<"시간을입력해주세요:ex)month-date ";
        std::string a;
        getline(std::cin,a);
        std::string b;
        std::cout<<"장소을입력해주세요: ";
        getline(std::cin,b);
        showPlaceAndDust(conn,a,b);
        
        // showSubWay(conn,"05-10");
        // addTask(conn, "Tom", 15, false);
        // addTask(conn, "None", 0, false);
        std::map<std::string,int>::iterator iter;
        // for(iter=utom.begin(); iter!=utom.end();++iter)
        // {
        // updateTask(conn,iter->first,iter->second);
        // }
        // deleteTask(conn, "None");
        // std::cout << "-------------------------------" << std::endl;
        // showTasks(conn);
        // 연결 실패시 오류 발생    
    } catch(sql::SQLException& e) {
        std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
        // 프로그램 비정상 종료
        return 1;
    }   
    
    return 0;
}