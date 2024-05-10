#include <iostream>
#include <mariadb/conncpp.hpp>

void dustavg(std::unique_ptr<sql::Connection> &conn, std::string region)
{
    std::string clock[24] = {"% 0:00", "% 1:00", "% 2:00", "% 3:00", "% 4:00", "% 5:00", "% 6:00", "% 7:00", "% 8:00", "% 9:00", "% 10:00", "% 11:00",
                            "% 12:00", "% 13:00", "% 14:00", "% 15:00", "% 16:00", "% 17:00", "% 18:00", "% 19:00", "% 20:00", "% 21:00", "% 22:00", "% 23:00"};
    try
    {
        std::unique_ptr<sql::PreparedStatement> stmnt1(conn->prepareStatement("select avg(dust) from AIR where date like ? and region = ?"));
        std::unique_ptr<sql::PreparedStatement> stmnt2(conn->prepareStatement("select variance(dust) from AIR where date like ? and region = ?"));
        std::cout << "---------------" << std::endl;
        for(int i=0; i<24; i++)
        {
            std::cout << i << ":00 미세먼지" << std::endl;
            stmnt1->setString(1, clock[i]);
            stmnt1->setString(2, region);
            sql::ResultSet *res1 = stmnt1->executeQuery();
            stmnt2->setString(1, clock[i]);
            stmnt2->setString(2, region);
            sql::ResultSet *res2 = stmnt2->executeQuery();
            while (res1->next())
            {
                std::cout << "평균 = " << res1->getFloat(1) << std::endl;
                if(res1->getFloat(1) <= 30)
                {
                    std::cout << "미세먼지 농도: 좋음" << std::endl;
                }
                else if(res1->getFloat(1) <= 80)
                {
                    std::cout << "미세먼지 농도: 보통" << std::endl;
                }
                else if(res1->getFloat(1) <= 150)
                {
                    std::cout << "미세먼지 농도: 나쁨" << std::endl;
                }
                else
                {
                    std::cout << "미세먼지 농도: 매우 나쁨" << std::endl;
                }
            }
            while (res2->next())
            {
                std::cout << "분산 = " << res2->getFloat(1) << std::endl;
                std::cout << "---------------" << std::endl;
            }
        }
    }
    catch(sql::SQLException& e)
    {
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
    }
}

int main()
{
    std::string region;
    try
    {
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://10.10.21.122/studyakm");
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "JH"}, {"password", "1234"}});
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

        std::cout << "지역을 입력하시오(ex.동대문구): ";
        std::cin >> region;
        dustavg(conn, region);   
    }

    // 연결 실패시 오류 발생 
    catch(sql::SQLException& e)
    {
        std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
        // 프로그램 비정상 종료
        return 1;
    }
    
    return 0;
}