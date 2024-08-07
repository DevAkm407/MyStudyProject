#ifndef CHSCLASS_HB__
#define CHSCLASS_HB__
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <mariadb/conncpp.hpp>
#define BUF_SIZE 100
#define NAME_SIZE 30
using namespace std;

class CHAT
{
private:

protected:
    int sock;
    string input1;
    string input2;
    string id;
    string pw;
    string username;
    string nickname;
    string usernum;
    int usernumber;
    int num;
    char name[NAME_SIZE] = "[DEFAULT]";
    char msg[BUF_SIZE];
    ostringstream words;
    string text;
    int text_len;
    int tn;
     std::unique_ptr<sql::Connection> setting()
    {
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://10.10.21.122:3306/CHAT");
        
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "HB"}, {"password", "1234"}});
        
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    return conn;    
    }
    std::unique_ptr<sql::Connection> conn = setting();
public:
    
    CHAT()
    {
    tn=0;
    }
    ~CHAT()
    {}
    string aka;
/*아이디 비밀번호 닉네임 이름*/
    string signUp(string text)
    {
        string parts[4];
        stringstream ss(text);
        string temp;
        for (int i = 0; i < 4; i++)
        {
            ss >> parts[i];
        }
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        sql::SQLString select_id = "SELECT * FROM MEMBER WHERE id = '" + parts[2] + "'";
        sql::ResultSet *res = stmnt->executeQuery(select_id);
        res->next();
        if (res->rowsCount() == 0)
                {    
                   
                    
                }
                else
                {
                    temp = "중복된 ID입니다.";
                    return temp;
                }
                
         std::unique_ptr<sql::Statement> pstmnt(conn->createStatement());
        sql::ResultSet *res2 = pstmnt->executeQuery("SELECT aka FROM MEMBER WHERE aka = '" + parts[1] + "'");
        res2->next();

                if (res2->rowsCount() == 0)
                {    
                   
                }
                else
                {
                    temp = "중복된 닉네임입니다.";
                    return temp;
                }


            std::unique_ptr<sql::PreparedStatement> mstmnt(conn->prepareStatement("INSERT INTO MEMBER VALUES (default, ?, ?, ?, ?)"));
            mstmnt->setString(1, parts[0]);
            mstmnt->setString(2, parts[1]);
            mstmnt->setString(3, parts[2]);
            mstmnt->setString(4, parts[3]);
            mstmnt->executeQuery();

            temp = "회원가입이 완료되었습니다.";
            return temp;

    }
    
    int gettn()
    {
        return tn;
    }
    // void SignUp( std::unique_ptr<sql::Connection> &conn, int sock, string username, string nickname, string id, string pw)
    // {
    //     try 
    //     {
    //         cout << "\n====================================================================" << endl;
    //         cout << "회원가입을 시작합니다. 항목을 차례대로 입력해주세요." << endl << endl;
    //         cout << "ID : ";
    //         getline(cin, id);
    //         cout << endl << endl;
    //         std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    //         sql::SQLString select_id = "SELECT * FROM MEMBER WHERE id = '" + id + "'";
    //         sql::ResultSet *res = stmnt->executeQuery(select_id);
    //         res->next();
    //         while (1)
    //         {
    //             if (res->rowsCount() == 0)
    //             {    
    //                 cout << "사용 가능한 ID입니다." << endl;
    //                 break;
    //             }
    //             else
    //             {
    //                 cout << "중복된 ID입니다. 다시 입력해주세요." << endl;
    //                 cout << "ID : ";
    //                 getline(cin, id);
    //             }
                
    //             res = stmnt->executeQuery(select_id);
    //             res->next();
    //         }
    //         cout << endl;
    //         cout << "비밀번호 : ";
    //         getline(cin, pw);
    //         cout << "이름 : ";
    //         getline(cin, username);
    //         cout << "닉네임 : ";
    //         getline(cin, nickname);
    //         std::unique_ptr<sql::Statement> pstmnt(conn->createStatement());
    //         sql::ResultSet *res2 = pstmnt->executeQuery("SELECT aka FROM MEMBER WHERE aka = '" + nickname + "'");
    //         res2->next();
    //         while (1)
    //         {
    //             if (res2->rowsCount() == 0)
    //             {    
    //                 cout << "사용 가능한 닉네임입니다." << endl;
    //                 break;
    //             }
    //             else
    //             {
    //                 cout << "중복된 닉네임입니다. 다시 입력해주세요." << endl;
    //                 cout << "닉네임 : ";
    //                 getline(cin, nickname);
    //             }
                
    //             res2 = pstmnt->executeQuery("SELECT aka FROM MEMBER WHERE aka = '" + nickname + "'");
    //             res2->next();
    //         }

    //         words << "1," << username << "," << nickname << "," << id << "," << pw;
            
    //         text = words.str();
    //         text_len = text.length();
    //         text.copy(msg, text_len);
    //         write(sock, msg, text_len+1);

    //         memset(msg, 0, text_len+1);

    //         std::unique_ptr<sql::PreparedStatement> mstmnt(conn->prepareStatement("INSERT INTO MEMBER VALUES (default, ?, ?, ?, ?)"));
    //         mstmnt->setString(1, username);
    //         mstmnt->setString(2, nickname);
    //         mstmnt->setString(3, id);
    //         mstmnt->setString(4, pw);
    //         mstmnt->executeQuery();

    //         cout << "\n회원가입이 완료되었습니다." << endl;

    //         std::unique_ptr<sql::Statement> cstmnt(conn->createStatement());        
    //         sql::ResultSet *res3 = cstmnt->executeQuery(select_id + " AND pw = '" + pw + "'");
    //         while (res3->next()) 
    //         {
    //             usernumber = res3->getInt(1);
    //             cout << "회원님의 고유번호는 [" << usernumber << "]번 입니다." << endl;
    //         }
    //         cout << "\n====================================================================" << endl;
    //     } 

    //     catch(sql::SQLException& e)
    //     {
    //         std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    //     }
    // }    
    int LoginSuccess(string msg)
    {
        string parts[2];
        stringstream ss(msg);
        int aaaa;
        for (int i = 0; i < 2; i++)
        {
            ss >> parts[i];
        }
        std::unique_ptr<sql::PreparedStatement> dstmnt(conn->prepareStatement("SELECT fid,aka FROM MEMBER WHERE id = ? AND pw= ?"));
                dstmnt->setString(1, parts[0]);
                dstmnt->setString(2, parts[1]);
        sql::ResultSet *res = dstmnt->executeQuery();
        res->next();
        string temp;  
        if (res->rowsCount() != 0)
                {    
                    temp=res->getString(2);
                    aka=temp;
                    aaaa=res->getInt(1);
                    return aaaa;
                }
                else
                {
                    tn++;
                    return 0;
                }


                
                // dstmnt->setInt(3, stoi(parts[2]));
                // sql::ResultSet *res4 = 
    }
    int LoginFail(string msg)
    {
        string parts[3];
        stringstream ss(msg);
        for (int i = 0; i < 3; i++)
        {
            ss >> parts[i];
        }
         std::unique_ptr<sql::PreparedStatement> dstmnt(conn->prepareStatement("SELECT * FROM MEMBER WHERE id = ? AND pw = ? AND fid = ?"));
                dstmnt->setString(1, parts[0]);
                dstmnt->setString(2, parts[1]);
                dstmnt->setInt(3, stoi(parts[2]));
                sql::ResultSet *res4 = dstmnt->executeQuery();
                   if (res4->rowsCount() != 0)
                {    
                   
                    return -1;
                }
                else
                {
                    return res4->getInt(1);
            
                }

    }
    // int LoginSuccess()
    // {        
    //     try 
    //     { 
    //         ostringstream words;
    //         string text;
    //         int text_len;
            

    //         cout << "\n====================================================================" << endl;
    //         cout << "로그인을 위해 회원 ID와 비밀번호를 입력해주세요." << endl << endl;
    //         while (1)
    //         {
    //             cout << "ID : ";
    //             getline(cin, id);
    //             cout << "PW : ";
    //             getline(cin, pw);
    //             std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    //             sql::SQLString select_id = "SELECT * FROM MEMBER WHERE id = '" + id + "'";
    //             sql::ResultSet *res = stmnt->executeQuery(select_id);
    //             if (res->next())
    //             {
    //                 if (res->getString(5) == pw)
    //                 {    
    //                     cout << "\n로그인에 성공하였습니다." << endl;
    //                     words << "2," << id << "," << pw;

    //                     text = words.str();
    //                     text_len = text.length();
    //                     text.copy(msg, text_len);
    //                     write(sock, msg, text_len+1);

    //                     memset(msg, 0, text_len+1);
    //                     turn = 0;

    //                     std::unique_ptr<sql::Statement> cstmnt(conn->createStatement());        
    //                     sql::ResultSet *res3 = cstmnt->executeQuery(select_id + " AND pw = '" + pw + "'");
    //                     while (res3->next()) 
    //                     {
    //                         usernumber = res3->getInt(1);
    //                         cout << "회원님의 고유번호는 [" << usernumber << "]번 입니다." << endl;
    //                     }
    //                     cout << "\n====================================================================" << endl;
    //                     return usernumber;
    //                 }
    //                 else
    //                 {
    //                     cout << "틀림" << endl;
    //                 }                                     
    //             }
    //             else 
    //             {    
    //                 cout << "회원 정보가 없습니다." << endl;
    //             }
    //         }            
    //     }
    //     catch(sql::SQLException& e)
    //     {
    //         std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    //     }
    // }

    // int LoginFail(std::unique_ptr<sql::Connection> &conn)
    // {
    //     try
    //     {
    //         turn++;
    //         cout << "ID 또는 비밀번호 오류 " << turn << "회입니다. 다시 입력해주세요." << endl << endl;
    //         while (turn >= 5)
    //         {
    //             cout << "로그인 5회 이상 실패하여 본인 인증이 필요합니다." << endl << endl;
    //             cout << "ID, 비밀번호, 고유번호를 입력해주세요." << endl;
    //             cin.ignore();
    //             cout << "ID : ";
    //             getline(cin, id);                            
    //             cout << "PW : ";                            
    //             getline(cin, pw);
    //             cout << "고유번호 : ";
    //             cin >> num;
    //             std::unique_ptr<sql::Statement> dstmnt(conn->createStatement());
    //             sql::SQLString select_id = "SELECT * FROM MEMBER WHERE id = '" + id + "'";
    //             sql::ResultSet *res4 = dstmnt->executeQuery(select_id + " AND pw = '" + pw + "'");
                
    //             while (res4->next())
    //             {
    //                 if (res4->getInt(1) == num)
    //                 {
    //                     cout << "\n로그인에 성공하였습니다." << endl;
    //                     words << "2," << id << "," << pw;

    //                     text = words.str();
    //                     text_len = text.length();
    //                     text.copy(msg, text_len);
    //                     write(sock, msg, text_len+1);

    //                     memset(msg, 0, text_len+1);
    //                     turn = 0;
    //                     return num;
    //                 }
    //                 else
    //                 {
    //                     if (res4->getInt(1) == num)
    //                     {
    //                         cout << "\n로그인에 성공하였습니다." << endl;
    //                         words << "2," << id << "," << pw;

    //                         text = words.str();
    //                         text_len = text.length();
    //                         text.copy(msg, text_len);
    //                         write(sock, msg, text_len+1);

    //                         memset(msg, 0, text_len+1);
    //                         turn = 0;
    //                         return num;
    //                     }
    //                     else
    //                         return 0;
    //                 }
    //             }
    //         }
    //     }
    //     catch(sql::SQLException& e)
    //     {
    //         std::cerr << "Error selecting tasks: " << e.what() << std::endl;
    //     }
    // }

    // void LoginFriends(int sock) 
    // {
    //     ostringstream words;
    //     string text;
    //     int text_len;

    //     cout << "\n====================================================================" << endl;
    //     cout << "접속한 친구 목록을 조회합니다." << endl;
    //     words << "3";

    //     text = words.str();
    //     text_len = text.length();
    //     text.copy(msg, text_len);
    //     write(sock, msg, text_len+1);

    //     memset(msg, 0, text_len+1);
    // }

    // void Chat(int sock)
    // {
    //     ostringstream words;
    //     string text;
    //     int text_len;

    //     cout << "\n====================================================================\n\n";
    //     cout << "1:1 대화를 시작합니다." << endl;
    //     cout << "접속한 친구 중 대화할 친구를 선택해주세요." << endl;
    //     cout << "친구 고유번호 : ";
    //     getline(cin, usernum);
    //     words << "4," << usernum;

    //     text = words.str();
    //     text_len = text.length();
    //     text.copy(msg, text_len);
    //     write(sock, msg, text_len+1);

    //     memset(msg, 0, text_len+1);
    //     cout << "\n====================================================================\n\n";
    // }

    // void TogetherChat(int sock)
    // {
    //     ostringstream words;
    //     string text;
    //     int text_len;
    //     string count;

    //     cout << "\n====================================================================\n\n";
    //     cout << "단체 채팅을 시작합니다." << endl;
    //     cout << "접속한 친구 중 대화할 친구를 선택해주세요." << endl;
    //     cout << "고유번호 : ";
    //     getline(cin, usernum);
    //     words << "5," << usernum << "," << count;

    //     text = words.str();
    //     text_len = text.length();
    //     text.copy(msg, text_len);
    //     write(sock, msg, text_len+1);

    //     memset(msg, 0, text_len+1);
    //     cout << "\n====================================================================\n\n";
    // }

    // void RandomChat(int sock)
    // {
    //     ostringstream words;
    //     string text;
    //     int text_len;

    //     cout << "랜덤 채팅을 시작합니다." << endl;
    //     words << "6";

    //     text = words.str();
    //     text_len = text.length();
    //     text.copy(msg, text_len);
    //     write(sock, msg, text_len+1);

    //     memset(msg, 0, text_len+1);
    //     cout << "\n====================================================================\n\n";
    // }

    // void Start(std::unique_ptr<sql::Connection> &conn)
    // {
    //     cout << "\n====================================================================\n\n";
    //     cout << " 원하는 항목 번호를 입력해주세요." << endl;
    //     cout << "1) 회원가입\n2) 로그인" << endl;
    //     getline(cin, input1);
    //     if (input1 == "1")
    //     {
    //         SignUp(conn, sock, username, nickname, id, pw);
    //     }
    //     else if (input1 == "2")
    //     {
    //         LoginSuccess(conn, sock, id, pw, usernum);
    //         cout << "\n원하는 항목 번호를 입력해주세요." << endl << endl;
    //         cout << "1) 접속 친구 확인\n2) 1:1 채팅\n3) 단체 채팅\n4) 랜덤 채팅" << endl;
    //         cin.ignore();
    //         getline(cin, input2);
    //         cout << endl;
    //         switch(stoi(input2))
    //         {
    //             case 1 :LoginFriends(sock);
    //                     break;
    //             case 2 :Chat(sock);
    //                     break;
    //             case 3 :TogetherChat(sock);
    //                     break;
    //             case 4 :RandomChat(sock);
    //                     break;
    //             default : break;
    //         }     
    //     }
    //     else
    //     cout << "다시 입력해주세요." << endl;     
    // }
};
#endif 