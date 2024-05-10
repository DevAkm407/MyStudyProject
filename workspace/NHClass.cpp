//필요한 헤더파일은 추가할것!
#include<iostream>
#include<string>

using namespace std;
class NHClass
{
private:
    /* data */
public:
NHClass(/* args */);
virtual    ~NHClass()=0;

int returncode(string codename)
{
    codename.compare("서울동부");
    
}

//1 공통적으로 필요한 기능
virtual void  chipProductWhereMarket(string filename)=0; //해당 데이터에서 품목 별로 어느 시장이 싼지 조사하는 함수 data네임은 파일이름

//2
//월별 가격 조회
virtual void  inquiryPriceAtmonth(int month)=0;    
//월별 가격 비교  
virtual void  cmpPriceAtmonth(int month1,int month2)=0;     

//지역별 가격 조회 조사지역코드 이용하기
virtual void  inquiryPriceAtRegion(int regioncode)=0;       
//가격비교
virtual void  cmpPriceAtRegion(int regioncode1,int regioncode2)=0;

//품목별 가격 조회 품목코드 이용
virtual void  inquiryPriceAtProduct(int productcode)=0; 
//가격비교
virtual void  cmpPriceAtProduct(int productcode1,int productcode2)=0;

//시장별 가격 조회 시장코드이용
virtual void  inquiryPriceAtMarket(int marketcode)=0;
//가격비교
virtual void  cmpPriceAtMarket(int marketcode1,int marketcode2)=0;

//3
//최대 가격조회
virtual void  inquiryMaxProduct(int productcode)=0;
//최소
virtual void  inquiryMinProduct(int productcode)=0;
//평균
virtual void  inquiryAvgProduct(int productcode)=0;

//4 
//특정 시장에서 최대 가격조회
virtual void  inquiryMaxProductAtMarket(int productcode,int marketcode)=0;
//최소
virtual void  inquiryMinProductAtMarket(int productcode,int marketcode)=0;
//평균
virtual void  inquiryAvgProductAtMarket(int productcode,int marketcode)=0;

//5
//특정 지역에서 최대 가격조회
virtual void  inquiryMaxProductAtRegion(int productcode,int regioncode)=0;
//최소
virtual void  inquiryMinProductAtRegion(int productcode,int regioncode)=0;
//평균
virtual void  inquiryAvgProductAtRegion(int productcode,int regioncode)=0;

//6
//데이터 추가보관
virtual void  newData(string filename1,string filename2)=0; 
//데이터 조회후 변경까지
virtual void  inquiryAfterModify(string filename)=0;
};






int main()
{

}


