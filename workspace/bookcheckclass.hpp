#ifndef BOOKCCLASS_H__
#define BOOKCCLASS_H__
#include <iostream>
#include <mariadb/conncpp.hpp>
#include <string>
#include <map>
#include <sstream>
using namespace std;

class bookcheckclass
{
private:
    /* data */

protected:
std::unique_ptr<sql::Connection> setting()
{
        sql::Driver *driver = sql::mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://10.10.21.122/BOOKS");
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "JDJ"}, {"password", "1234"}});
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    return conn;    
}
std::unique_ptr<sql::Connection> conn=setting();
public:
    bookcheckclass(/* args */)
    {}
    ~bookcheckclass()
    {
    }

string splitfun(string msg)
{
    istringstream iss(msg);
    string splitmsg[3];
    string k="-1";
    for (int i = 0; i < 3; i++)
    {
        getline(iss,splitmsg[i],',');
    }
    char test;
    splitmsg[1].copy(&test,1);
    int func=atoi(&test);
    switch (func)
    {
    case 1:
       k=TitleFind(splitmsg[2]);    
        return k;
        break;
    case 2:
       k= WriterFind(splitmsg[2]);
        return k;
        break;
    case 3:
       k= CompanyFind(splitmsg[2]);
        return k;
        break;
    case 4:
        k=BookcodeFind(splitmsg[2]);
        return k;
        break;
    case 5:
        k=FindcodeFind(splitmsg[2]);
        return k;
        break;
    default:
        break;
    }
}


string TitleFind(std::string msg)// 제목
{   
    ostringstream oss;
    string b_title;//책제목을 담을 스트링타입 변수 
    map<string,int> rent; 
    std::string title=msg;
    try
    {
        unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
        sql::ResultSet* res = psmt -> executeQuery(); 
        string aa;
        vector<string>::iterator iter;
        while(res -> next())
        {
           aa = res -> getString(1);
           rent.insert(pair<string,int>(aa,res->getInt(2)));
        }    
        unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE booktitle LIKE ? "));
        title="%"+title+"%";
        pstmt ->setString(1,title);
        res = pstmt->executeQuery();
        while (res->next())
        {
            aa=res->getString(3);
            if (rent[aa]>0)
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
            else
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
        }
        b_title=oss.str();   

 
        return b_title;    
    }
    
    catch(const std::exception& e)
    {
        std::cerr << "연결 오류 " << e.what() << '\n';
    }
}


string CompanyFind(std::string msg) //출판사
{
    ostringstream oss;
    string b_company;//출판사를 담을 스트링타입 변수 
    map<string,int> rent; 
    std::string company=msg;
    try
    {
        unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
        sql::ResultSet* res = psmt -> executeQuery(); 
        string aa;
        vector<string>::iterator iter;
        while(res -> next())
        {
           aa = res -> getString(1);
           rent.insert(pair<string,int>(aa,res->getInt(2)));
        }    
        unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE company LIKE ? "));
        company="%"+company+"%";
        pstmt ->setString(1,company);
        res = pstmt->executeQuery();
        while (res->next())
        {
            aa=res->getString(3);
            if (rent[aa]>0)
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
            else
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
        }
        b_company=oss.str();   

 
        return b_company;    
    }
    
    catch(const std::exception& e)
    {
        std::cerr << "연결 오류 " << e.what() << '\n';
    }
    
}

string FindcodeFind(std::string msg) // 등록번호
{
   ostringstream oss;
    string b_findcode;//등록번호를 담을 스트링타입 변수 
    map<string,int> rent; 
    std::string findcode=msg;
    try
    {
        unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
        sql::ResultSet* res = psmt -> executeQuery(); 
        string aa;
        vector<string>::iterator iter;
        while(res -> next())
        {
           aa = res -> getString(1);
           rent.insert(pair<string,int>(aa,res->getInt(2)));
        }    
        unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE findcode LIKE ? "));
        findcode="%"+findcode+"%";
        pstmt ->setString(1,findcode);
        res = pstmt->executeQuery();
        while (res->next())
        {
            aa=res->getString(3);
            if (rent[aa]>0)
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
            else
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
        }
        b_findcode=oss.str();   

 
        return b_findcode;    
    }
    
    catch(const std::exception& e)
    {
        std::cerr << "연결 오류 " << e.what() << '\n';
    }
    
}
string BookcodeFind(std::string msg)// 책 번호
{
    ostringstream oss;
    string b_bookcode;//책번호를 담을 스트링타입 변수 
    map<string,int> rent; 
    std::string bookcode=msg;
    try
    {
        unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
        sql::ResultSet* res = psmt -> executeQuery(); 
        string aa;
        vector<string>::iterator iter;
        while(res -> next())
        {
           aa = res -> getString(1);
           rent.insert(pair<string,int>(aa,res->getInt(2)));
        }    
        unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE bookcode LIKE ? "));
        bookcode="%"+bookcode+"%";
        pstmt ->setString(1,bookcode);
        res = pstmt->executeQuery();
        while (res->next())
        {
            aa=res->getString(3);
            if (rent[aa]>0)
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
            else
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
        }
        b_bookcode=oss.str();   

 
        return b_bookcode;    
    }
    
    catch(const std::exception& e)
    {
        std::cerr << "연결 오류 " << e.what() << '\n';
    }
    
}

string WriterFind(std::string msg)// 저자
{
    ostringstream oss;
    string b_writer;//저자를 담을 스트링타입 변수 
    map<string,int> rent; 
    std::string writer=msg;
    try
    {
        unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
        sql::ResultSet* res = psmt -> executeQuery(); 
        string aa;
        vector<string>::iterator iter;
        while(res -> next())
        {
           aa = res -> getString(1);
           rent.insert(pair<string,int>(aa,res->getInt(2)));
        }    
        unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE writer LIKE ? "));
        writer="%"+writer+"%";
        pstmt ->setString(1,writer);
        res = pstmt->executeQuery();
        while (res->next())
        {
            aa=res->getString(3);
            if (rent[aa]>0)
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
            else
                oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
        }
        b_writer=oss.str();   

 
        return b_writer;    
    }
    
    catch(const std::exception& e)
    {
        std::cerr << "연결 오류 " << e.what() << '\n';
    }
    
}

};



// string TitleFind(std::unique_ptr<sql::Connection> &)// 제목
// {   
//     ostringstream oss;
//     string b_title;//책제목을 담을 스트링타입 변수 
//     map<string,int> rent; 
//     std::string title;
//     std::cout <<"책의 제목을 입력해주세요." << std::endl;
//     getline(std::cin,title);
//     try
//     {
//         unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
//         sql::ResultSet* res = psmt -> executeQuery(); 
//         string aa;
//         vector<string>::iterator iter;
//         while(res -> next())
//         {
//            aa = res -> getString(1);
//            rent.insert(pair<string,int>(aa,res->getInt(2)));
//         }    
//         unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE booktitle LIKE ? "));
//         title="%"+title+"%";
//         pstmt ->setString(1,title);
//         res = pstmt->executeQuery();
//         while (res->next())
//         {
//             aa=res->getString(3);
//             if (rent[aa]>0)
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
//             else
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
//         }
//         b_title=oss.str();   

//         cout << b_title << endl;
//         return b_title;    
//     }
    
//     catch(const std::exception& e)
//     {
//         std::cerr << "연결 오류 " << e.what() << '\n';
//     }
// }
// string CompanyFind(std::unique_ptr<sql::Connection> &) //출판사
// {
//     ostringstream oss;
//     string b_company;//출판사를 담을 스트링타입 변수 
//     map<string,int> rent; 
//     std::string company;
//     std::cout <<"출판사명을 입력해주세요." << std::endl;
//     getline(std::cin,company);
//     try
//     {
//         unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
//         sql::ResultSet* res = psmt -> executeQuery(); 
//         string aa;
//         vector<string>::iterator iter;
//         while(res -> next())
//         {
//            aa = res -> getString(1);
//            rent.insert(pair<string,int>(aa,res->getInt(2)));
//         }    
//         unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE company LIKE ? "));
//         company="%"+company+"%";
//         pstmt ->setString(1,company);
//         res = pstmt->executeQuery();
//         while (res->next())
//         {
//             aa=res->getString(3);
//             if (rent[aa]>0)
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
//             else
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
//         }
//         b_company=oss.str();   

//         cout << b_company << endl;
//         return b_company;    
//     }
    
//     catch(const std::exception& e)
//     {
//         std::cerr << "연결 오류 " << e.what() << '\n';
//     }
    
// }
// string FindcodeFind(std::unique_ptr<sql::Connection> &) // 등록번호
// {
//    ostringstream oss;
//     string b_findcode;//등록번호를 담을 스트링타입 변수 
//     map<string,int> rent; 
//     std::string findcode;
//     std::cout <<"등록번호를 입력해주세요." << std::endl;
//     getline(std::cin,findcode);
//     try
//     {
//         unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
//         sql::ResultSet* res = psmt -> executeQuery(); 
//         string aa;
//         vector<string>::iterator iter;
//         while(res -> next())
//         {
//            aa = res -> getString(1);
//            rent.insert(pair<string,int>(aa,res->getInt(2)));
//         }    
//         unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE findcode LIKE ? "));
//         findcode="%"+findcode+"%";
//         pstmt ->setString(1,findcode);
//         res = pstmt->executeQuery();
//         while (res->next())
//         {
//             aa=res->getString(3);
//             if (rent[aa]>0)
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
//             else
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
//         }
//         b_findcode=oss.str();   

//         cout << b_findcode << endl;
//         return b_findcode;    
//     }
    
//     catch(const std::exception& e)
//     {
//         std::cerr << "연결 오류 " << e.what() << '\n';
//     }
    
// }
// string BookcodeFind(std::unique_ptr<sql::Connection> &)// 책 번호
// {
//     ostringstream oss;
//     string b_bookcode;//책번호를 담을 스트링타입 변수 
//     map<string,int> rent; 
//     std::string bookcode;
//     std::cout <<"책번호를 입력해주세요." << std::endl;
//     getline(std::cin,bookcode);
//     try
//     {
//         unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
//         sql::ResultSet* res = psmt -> executeQuery(); 
//         string aa;
//         vector<string>::iterator iter;
//         while(res -> next())
//         {
//            aa = res -> getString(1);
//            rent.insert(pair<string,int>(aa,res->getInt(2)));
//         }    
//         unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE bookcode LIKE ? "));
//         bookcode="%"+bookcode+"%";
//         pstmt ->setString(1,bookcode);
//         res = pstmt->executeQuery();
//         while (res->next())
//         {
//             aa=res->getString(3);
//             if (rent[aa]>0)
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
//             else
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
//         }
//         b_bookcode=oss.str();   

//         cout << b_bookcode << endl;
//         return b_bookcode;    
//     }
    
//     catch(const std::exception& e)
//     {
//         std::cerr << "연결 오류 " << e.what() << '\n';
//     }
    
// }

// string WriterFind(std::unique_ptr<sql::Connection> &)// 저자
// {
//     ostringstream oss;
//     string b_writer;//저자를 담을 스트링타입 변수 
//     map<string,int> rent; 
//     std::string writer;
//     std::cout <<"저자를 입력해주세요." << std::endl;
//     getline(std::cin,writer);
//     try
//     {
//         unique_ptr<sql::PreparedStatement> psmt(conn -> prepareStatement("SELECT bookcode,glp FROM RENT"));
//         sql::ResultSet* res = psmt -> executeQuery(); 
//         string aa;
//         vector<string>::iterator iter;
//         while(res -> next())
//         {
//            aa = res -> getString(1);
//            rent.insert(pair<string,int>(aa,res->getInt(2)));
//         }    
//         unique_ptr<sql::PreparedStatement> pstmt(conn -> prepareStatement("SELECT * FROM JANGDUCK WHERE writer LIKE ? "));
//         writer="%"+writer+"%";
//         pstmt ->setString(1,writer);
//         res = pstmt->executeQuery();
//         while (res->next())
//         {
//             aa=res->getString(3);
//             if (rent[aa]>0)
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) + " 저자: " << res -> getString(6) + " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) << " 대여 불가능" << "\n";
//             else
//                 oss << "책 번호: " << res -> getString(3) << " 제목: " << res -> getString(5) << " 저자: " << res -> getString(6) << " 출판사: " << res -> getString(7) << " 등록 번호: " << res -> getString(9) <<"\n";
//         }
//         b_writer=oss.str();   

//         cout << b_writer << endl;
//         return b_writer;    
//     }
    
//     catch(const std::exception& e)
//     {
//         std::cerr << "연결 오류 " << e.what() << '\n';
//     }
    
// }

#endif BOOKCCLASS_H__