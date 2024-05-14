// Includes
#include<iostream>
#include<mariadb/conncpp.hpp>
#include<iomanip>
#include<sstream>
#include<vector>
#include<string>
#include<map>

class adb
{
private:
int historycount;
std::map<int,int> history;
protected:
int spiltmax(int max,int* array,int size)
{

    
    if(max>20000)
    {
        for (int i = 0; i < size; i++)
        {
          if(array[i]/1000!=0)  
            array[i]=array[i]/1000;
            else
                array[i]=0;
        }    
        return max/1000;
    }

    else if(max >1000 & max < 20000)
    {
        for (int i = 0; i < size; i++)
        {
            if(array[i]/500!=0)  
                array[i]=array[i]/500;
            else
                array[i]=0;
        }
        return max/500;
    }
    else if(max >100 & max <1000)
    {
        for (int i = 0; i < size; i++)
        {
            if(array[i]/100 !=0) 
                array[i]=array[i]/100;
            else
                array[i]=0;
        }
        return max/100;
    }
    else if(max <100)
    {
        for (int i = 0; i < size; i++)
        {
         if(array[i]/10 !=0)   
            array[i]=array[i]/10;
         else
            array[i]=0;
        }
        return max/10;
    }
 return 0;
}


std::unique_ptr<sql::Connection> setting()
{
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/ADB");
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "AKM"}, {"password", "1234"}});
        
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    return conn;    
}


std::unique_ptr<sql::Connection> conn=setting();
void goHistory(int shitory)
{
     
        switch (shitory)
        {
        case 1:
            showRegion();        
            break;
        case 2:
            showGBCCF_Region();
            break;
        case 3:
            showAgeSex();
            break;
        case 4:
            showGBCCFAgeSex();
            break;
        case 5:
            showGraphAgeSex();
            break;
        case 6:
            showPlace();
            break;
        case 7:
            showGBCCF_Place();
            break;
        default:
            break;
        }
  
}


public:
    adb(/* args */):historycount(1)
    {}
    ~adb(){}
//1
void showRegion(/*std::unique_ptr<sql::Connection> &conn*/)
{
    std::string cc="서울	부산	대구	인천	광주	대전	울산	세종	경기도	강원도	충청북도	충청남도	전라북도	전라남도	경상북도	경상남도	제주도	기타도시	도시이외";
    std::istringstream ss(cc);
    std::string a[19];
    for (int i = 0; i <19; i++)
    {
       ss>>a[i];
    }
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT * FROM REGION"));
    sql::ResultSet *res;
    res=stmnt->executeQuery();
    while (res->next())
    {
        for (int i = 1; i <= 21; i++)
        {
        if(i<3)    
            std::cout<<res->getString(i)<<", ";
        else if(i==16)
            std::cout<<"\n"<<a[i-3]<<" "<<res->getInt(i)<<"건 ";
        else
            std::cout<<a[i-3]<<" "<<res->getInt(i)<<"건 ";    
        

        }
        std::cout<<"\n";
        for (int  i = 0; i < 30; i++)
        {
          std::cout<<"------";
        }
        
        std::cout<<"\n\n\n";                  
    }
    if(historycount !=31)
    {
        history.insert(std::pair<int,int>(historycount,1));
        historycount++;
    }

}

//2
void showGBCCF_Region()
{
    try{
    std::string cc="서울	부산	대구	인천	광주	대전	울산	세종	경기도	강원도	충청북도	충청남도	전라북도	전라남도	경상북도	경상남도	제주도	기타도시	도시이외";
    std::istringstream ss(cc);
    std::string* a=new std::string[19];
    for (int i = 0; i <19; i++)
    {
       ss>>a[i];
    }
    
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    sql::ResultSet *res;
    res=stmnt->executeQuery("SELECT * FROM GBCCF_REGION");
    std::cout<<res->rowsCount();
    while (res->next())
    {
        for (int i = 1; i < 20; i++)
        {
        if(i==1)    
            std::cout<<res->getString(i)<<", ";
        else if(i==16)
            std::cout<<"\n"<<a[i-2]<<" "<<res->getInt(i)<<"건 ";
        else
            std::cout<<a[i-2]<<" "<<res->getInt(i)<<"건 ";    
        }
        std::cout<<"\n";
        for (int  j = 0; j < 30; j++)
        {
          std::cout<<"------";

        }
        
        std::cout<<"\n\n";                  
    }
    
    delete[] a;
  if(historycount !=31)
    {
        history.insert(std::pair<int,int>(historycount,2));
        historycount++;
    }
}catch(sql::SQLException &e)
{
    std::cout<<"마리아디비오류:"<<e.what()<<std::endl;
}
}

//3
void showAgeSex() {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT * FROM AGESEX "));
        // 객체에 값을 전달
        // stmnt->setInt(1,1);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        
        sql::ResultSet *res;
        res=stmnt->executeQuery();
        while (res->next())
        {
            std::cout <<res->getString(1)<<", ";
            std::cout <<res->getString(2)<<", 20대이하남성: ";
            std::cout <<res->getInt(3)<<"건 , 20~30세남성: ";
            std::cout <<res->getInt(4)<<"건 , 31~40세남성: ";
            std::cout <<res->getInt(5)<<"건 , 41~50세남성: ";
            std::cout <<res->getInt(6)<<"건 , 51~60세남성: ";
            std::cout <<res->getInt(7)<<"건 , 70세이상남성: ";
            std::cout <<res->getInt(8)<<"건 , 신원미상남성: ";
            std::cout <<res->getInt(9)<<"건"<<std::endl<<std::endl<<std::endl;
        }

        for (int i = 0; i < 50; i++)
        {
            std::cout <<"---";
        }
        std::cout<<"\n";
        res=stmnt->executeQuery();

        while (res->next())
        {
            std::cout <<res->getString(1)<<", ";
            std::cout <<res->getString(2)<<", 20대이하여성: ";
            std::cout <<res->getInt(9)<<"건 , 20~30세여성: ";
            std::cout <<res->getInt(10)<<"건 , 31~40세여성: ";
            std::cout <<res->getInt(11)<<"건 , 41~50세여성: ";
            std::cout <<res->getInt(12)<<"건 , 51~60세여성: ";
            std::cout <<res->getInt(13)<<"건 , 70세이상여성: ";
            std::cout <<res->getInt(14)<<"건 , 신원미상여성: ";
            std::cout <<res->getInt(15)<<"건"<<std::endl<<std::endl<<std::endl;
        }
        
        if(historycount !=31)
        {
            history.insert(std::pair<int,int>(historycount,3));
            historycount++;
        }
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
   }
}

//4
void showGBCCFAgeSex() {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT * FROM GBCCF_AGESEX "));
        // 객체에 값을 전달
        // stmnt->setInt(1,1);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        
        sql::ResultSet *res;
        res=stmnt->executeQuery();
        int mansCrime=0;
        while (res->next())
        {
            std::cout <<res->getString(1)<<", 20대이하남성: ";
            std::cout <<res->getInt(2)<<"건 , 20~30세남성: ";
            std::cout <<res->getInt(3)<<"건 , 31~40세남성: ";
            std::cout <<res->getInt(4)<<"건 , 41~50세남성: ";
            std::cout <<res->getInt(5)<<"건 , 51~60세남성: ";
            std::cout <<res->getInt(6)<<"건 , 70세이상남성: ";
            std::cout <<res->getInt(7)<<"건 , 신원미상남성: ";
            std::cout <<res->getInt(8)<<"건"<<std::endl<<std::endl<<std::endl;
            for (int i = 2; i <=8 ; i++)
            {
                mansCrime+=res->getInt(i);
            }
        }
        for (int i = 0; i < 50; i++)
        {
            std::cout <<"---";
        }
        std::cout<<"\n";
        res=stmnt->executeQuery();
        int woMansCrime=0;
        while (res->next())
        {
            std::cout <<res->getString(1)<<", 20대이하여성: ";
            std::cout <<res->getInt(9)<<"건 , 20~30세여성: ";
            std::cout <<res->getInt(10)<<"건 , 31~40세여성: ";
            std::cout <<res->getInt(11)<<"건 , 41~50세여성: ";
            std::cout <<res->getInt(12)<<"건 , 51~60세여성: ";
            std::cout <<res->getInt(13)<<"건 , 70세이상여성: ";
            std::cout <<res->getInt(14)<<"건 , 신원미상여성: ";
            std::cout <<res->getInt(15)<<"건"<<std::endl<<std::endl<<std::endl;
          for (int i = 9; i <= 15; i++)
        {
            woMansCrime +=res->getInt(i);
        }
        }
      
        std::cout<<"\n\n\n 남성 범죄 발생 수:"<<mansCrime<<"\t 여성 범죄 발생 수: "<<woMansCrime;

        if(historycount !=31)
         {
            history.insert(std::pair<int,int>(historycount,4));
            historycount++;
        }
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
   }
}

//5
void showGraphAgeSex() {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT * FROM GBCCF_AGESEX "));
        // 객체에 값을 전달
        // stmnt->setInt(1,1);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        std::string cn="남자(20세이하)	남자(21-30세)	남자(31-40세)	남자(41-50세)	남자(51-60세)	남자(61-70세)	남자(71세이상)	남자(미상)	여자(20세이하)	여자(21-30세)	여자(31-40세)	여자(41-50세)	여자(51-60세)	여자(61-70세)	여자(71세이상)	여자(미상)";
        std::istringstream ss(cn);
        std::string cln[13];   
        for (int i = 0; i < 13; i++)
        {
            ss>>cln[i];
        }
        std::string ccf[15]; 
        std::vector<int> a[8];
        sql::ResultSet *res;
        int count=0;
        res=stmnt->executeQuery();
        while (res->next())
        {
        ccf[count]=res->getString(1);
        a[0].push_back(res->getInt(2));
        a[1].push_back(res->getInt(3));
        a[2].push_back(res->getInt(4));
        a[3].push_back(res->getInt(5));
        a[4].push_back(res->getInt(6));
        a[5].push_back(res->getInt(7));
        a[6].push_back(res->getInt(8));
        a[7].push_back(res->getInt(9));
        count++;
        }
        int s=0;
        int max=0;
        std::string stop;
        

        while(--count)
        {
            int* z = new int[8];
            for (int  i = 0; i < 8; i++)
            {
                max = max < a[i][s] ? a[i][s] : max;
                z[i]=a[i][s];
            }
           
        
            max=spiltmax(max,z,8);
            
            for (int  i = 0; i < 8; i++)
            {
              
                z[i]-=max;
             
            }
            
            // for (int i = 0; i <7; i++)
            // {
            //     std::cout <<z[i]<<" ";
            // }
            std::cout<<ccf[15-count]<<"\n";
            for (int i = 0; i < max; i++)
            {

                if(z[0]==0)
                {
                    std::cout<<"#";
                }
                else
                {
                    z[0]++;
                //    std::cout<<" ";
                }  
                if(z[1]==0)
                    std::cout<<std::setw(30)<<"#";
                else
                {
                    z[1]++;
                    // std::cout<<" ";
                }
                
                if(z[2]==0)
                    std::cout<<std::setw(30) <<"#";
                else
                {
                z[2]++;
                // std::cout<<" ";
                }
                if(z[3]==0)
                   std::cout<<std::setw(30)<<"#";
                else{
                    z[3]++;
                    // std::cout<<" ";
                    }
                if(z[4]==0)
                    std::cout<<std::setw(30)<<"#";
                else{
                    z[4]++;
                    // std::cout<<" ";
                }
                if(z[5]==0)
                    std::cout<<std::setw(30)<<"#";
                else
                {
                    z[5]++;
                    // std::cout<<" ";
                }
                if(z[6]==0)
                    std::cout<<std::setw(30)<<"#";
                else
                {    
                    z[6]++;
                    // std::cout<<" ";
                }
                
                if(z[7]==0)
                    std::cout<<std::setw(30)<<"#";
                else
                {    
                    z[7]++;
                    // std::cout<<" ";
                }
            std::cout<<"\n";
            }
           
           std::cout<<"\n"<<cln[0]<<std::setw(30)<<cln[1]<<std::setw(30)<<cln[2]<<std::setw(30)<<cln[3]<<std::setw(30)<<cln[4]
           <<std::setw(30)<<cln[5]<<std::setw(30)<<cln[6]<<std::setw(30)<<cln[7]<<"\n";
            s++;
            std::cout<<"다른 그래프도 보시겠습니까? y or n ";
            getline(std::cin,stop);
            if(stop == "n" || stop =="N")
            {
                break;
                delete z;
            }
            std::cout <<count<<std::endl;
            delete z;
        }
    
        std::string cnn="여자(20세이하)	 여자(21-30세)	여자(31-40세)	여자(41-50세)	여자(51-60세)	여자(61-70세)	여자(71세이상)	여자(미상)";
        std::istringstream sss(cnn);
        std::string clnn[8];   
        for (int i = 0; i < 8; i++)
        {
            sss>>clnn[i];
        }
        std::cout<<"\n";
        res=stmnt->executeQuery();
        int woMansCrime=0;
        count=0;
        for (int  i = 0; i <8 ; i++)
        {
            a[i].clear();
            
        }
        ccf->clear();\
        while (res->next())
        {
            ccf[count]=res->getString(1);
            a[0].push_back(res->getInt(9));
            a[1].push_back(res->getInt(10));
            a[2].push_back(res->getInt(11));
            a[3].push_back(res->getInt(12));
            a[4].push_back(res->getInt(13));
            a[5].push_back(res->getInt(14));
            a[6].push_back(res->getInt(15));
            count++;
        }
      
        s=0;
        max=0;
        std::string stopp;
        
        while(--count)
        {
            int* z = new int[8];
            for (int  i = 0; i < 8; i++)
            {
                max = max < a[i][s] ? a[i][s] : max;
                z[i]=a[i][s];
            }
           
            max=spiltmax(max,z,8);
            
            for (int  i = 0; i < 8; i++)
            {
              
                z[i]-=max;
             
            }
            
            // for (int i = 0; i <7; i++)
            // {
            //     std::cout <<z[i]<<" ";
            // }
            std::cout<<ccf[15-count]<<"\n";
            for (int i = 0; i < max; i++)
            {

                if(z[0]==0)
                {
                    std::cout<<"#";
                }
                else
                {
                    z[0]++;
                //    std::cout<<" ";
                }  
                if(z[1]==0)
                    std::cout<<std::setw(30)<<"#";
                else
                {
                    z[1]++;
                    // std::cout<<" ";
                }
                
                if(z[2]==0)
                    std::cout<<std::setw(30) <<"#";
                else
                {
                z[2]++;
                // std::cout<<" ";
                }
                if(z[3]==0)
                   std::cout<<std::setw(30)<<"#";
                else{
                    z[3]++;
                    // std::cout<<" ";
                    }
                if(z[4]==0)
                    std::cout<<std::setw(30)<<"#";
                else{
                    z[4]++;
                    // std::cout<<" ";
                }
                if(z[5]==0)
                    std::cout<<std::setw(30)<<"#";
                else
                {
                    z[5]++;
                    // std::cout<<" ";
                }
                if(z[6]==0)
                    std::cout<<std::setw(30)<<"#";
                else
                {    
                    z[6]++;
                    // std::cout<<" ";
                }
                
                if(z[7]==0)
                    std::cout<<std::setw(30)<<"#";
                else
                {    
                    z[7]++;
                    // std::cout<<" ";
                }
            std::cout<<"\n";
            }
           
           std::cout<<"\n"<<clnn[0]<<std::setw(30)<<clnn[1]<<std::setw(30)<<clnn[2]<<std::setw(30)<<clnn[3]<<std::setw(30)<<clnn[4]
           <<std::setw(30)<<clnn[5]<<std::setw(30)<<clnn[6]<<std::setw(30)<<clnn[7]<<"\n";
            s++;
            std::cout<<"다른 그래프도 보시겠습니까? y or n ";
            getline(std::cin,stopp);
            if(stopp == "n" || stopp =="N")
            {
                break;
                delete z;
            }
            std::cout <<count<<std::endl;
            delete z;
        }

        if(historycount !=31)
        {
            history.insert(std::pair<int,int>(historycount,5));
            historycount++;
        }
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
   }
}

//6
void showPlace()
{
try{
    std::string cc="연립다세대	단독주택	고속도로	노상	백화점	슈퍼마켓	편의점	대형할인매장	시장	상점	숙박시설	유흥업소	사무실	공장	공사지역	창고	역대합실	지하철	흥행장	유원지	학교	금융기관	의료기관	종교기관	산야	해상	부대	공터	주차장	공중화장실	피씨방	기타";
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT * FROM PLACE"));
    std::istringstream ss(cc);
    std::string columns[34];
    for (int i = 0; i < 32; i++)
    {
        ss>>columns[i];
    }
    sql::ResultSet *res;
    res=stmnt->executeQuery();
    while (res->next())
    {
        for (int i = 1; i <= 32; i++)
        {
                if(i<3)
                {
                    std::cout<<res->getString(i)<<"  ";
                }
                else
                    std::cout <<columns[i-3]<<" :  "<<res->getString(i)<<"건  ";
                if(i==16)
                    std::cout<<std::endl<<std::endl;
        }
         for (int j = 0; j < 60; j++)
                    {
                        std::cout<<"---";
                    }
                    
        std::cout<<std::endl<<std::endl;
    }
    if(historycount !=31)
    {
        history.insert(std::pair<int,int>(historycount,6));
        historycount++;
    }
    }catch(sql::SQLSyntaxErrorException e)
    {
        std::cerr << "Error inserting new task: " << e.what() << std::endl;
    }

    
}

//7
void showGBCCF_Place()
{
    try {
    std::string cc="연립다세대	단독주택	고속도로	노상	백화점	슈퍼마켓	편의점	대형할인매장	시장	상점	숙박시설	유흥업소	사무실	공장	공사지역	창고	역대합실	지하철	흥행장	유원지	학교	금융기관	의료기관	종교기관	산야	해상	부대	공터	주차장	공중화장실	피씨방	기타";
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT * FROM NOSIX"));
    std::istringstream ss(cc);
    std::string columns[34];
    for (int i = 0; i < 32; i++)
    {
        ss>>columns[i];
    }
    sql::ResultSet *res;
    res=stmnt->executeQuery();
    while (res->next())
    {
        for (int i = 1; i <= 32; i++)
        {
                if(i==1)
                {
                    std::cout<<res->getString(i)<<"  ";
                }
                else
                    std::cout <<columns[i-2]<<" :  "<<res->getString(i)<<"건  ";
                if(i==16)
                    std::cout<<std::endl<<std::endl;
        }
        for (int j = 0; j < 60; j++)
        {
            std::cout<<"---";
        }
                    
        std::cout<<std::endl<<std::endl;
    }
    if(historycount !=31)
    {
        history.insert(std::pair<int,int>(historycount,7));
        historycount++;
    }
    }catch(sql::SQLSyntaxErrorException e)
    {
        std::cerr << "Error inserting new task: " << e.what() << std::endl;
    }    
}

void showHistory()
{
    std::map<int,int>::iterator iter;
    std::string a;
    for ( iter =history.begin(); iter !=history.end(); ++iter)
    {
        switch (iter->second)
        {
        case 1:
            a="지역별 범죄기록";
            break;
        case 2:
            a="지역별 범죄기록(범죄대분류기준)";
            break;
        case 3:
            a="나이및성별 범죄기록";
            break;
        case 4:
            a="나이및성별 범죄기록(범죄대분류기준)";
            break;        
        case 5:
            a="나이및성별 범죄기록(그래프출력으로)";
            break;
        case 6:
            a="장소별 범죄기록";
            break;
        case 7:
            a="장소별 범죄기록(범죄대분류기준)";
            break;
        default:
            a.clear();
            break;
        }
        std::cout<<iter->first<<"번째 열람기록: "<<a<<std::endl;
    }
    char* b =new char[20];
    std::string ss;
    std::cout<<"다시 열람하고싶은 자료가있습니까? y or n"<<std::endl;
    getline(std::cin,ss);
    if(ss=="y" || ss=="Y")
    {
        
        std::cout<<"몇번자료를 열람하고 싶으십니까? 입력해주세요: ";
        std::cin.getline(b,20);
        while(atoi(b)==0)
            std::cin.getline(b,20);
        std::map<int,int>::iterator ater;
        ater=history.find(atoi(b));
        if(history.count(atoi(b))==0){
            std::cout<<"조회번호를 잘못입력 하셨습니다.\n";
        }
        
        else
        {   
        goHistory(ater->second);
        }
        delete b;
    }
}


};




int main() {
   
        adb a;
        char* k=new char[20];
        while (1)
        {
            char m;
            std::cout<<"원하는 기능을 선택해주세요\n\n"<<"1.지역별 범죄 조회 2.지역별 범죄 통계 3.나이및성별 범죄 조회 4.나이및성별 범죄통계 조회 5.나이및 성별 범죄 그래프 조회 6.장소별 범죄 조회 "
            <<"7.장소별 범죄통계조회 8.히스토리 조회 9.종료"<<std::endl<<"입력:";
            std::cin.getline(k,20);   
            std::cout<<"\n";
            switch (atoi(k))
            {
            case 1:
                a.showRegion();
                break;
            case 2:
                a.showGBCCF_Region();
                break;
            case 3:
                a.showAgeSex();
                break;
            case 4:
                a.showGBCCFAgeSex();
                break;
            case 5:
                a.showGraphAgeSex();
                break;
            case 6:
                a.showPlace();
                break;
            case 7:
                a.showGBCCF_Place();
                break;
            case 8:
                a.showHistory();
                break;                
            case 9:
                delete k;
                return 0;
                break;
            default:
                std::cout<<"다시입력해주세요\n";
                break;
            }
        }
        

    
    return 0;
}