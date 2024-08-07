#include<iostream>
#include "nlohmann/json.hpp"
using namespace std;
using json=nlohmann::json;

int main()
{
  
  string data=R"(
  {
   "key" : "데이터전송",
   "shape" : "클로버",
   "num" : [1,2,3,4]
  })";
  json j = json::parse(data);
  j["price"]=3100;

  cout<<j.dump()<<endl;



  return 0;

}