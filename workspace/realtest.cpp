#include "csinfo.hpp"
#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<sstream>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include"customer_info.hpp"
#include<fstream>
#include<fcntl.h>
#include"nlohmann/json.hpp"
using json =nlohmann::json;
int main()
{
string k=R"({
    "text" : "84.8"
})";
json j=json::parse(k);
double z =  stod((string)j["text"]);
// k.replace(k.find(","),k.length(),".");
        
cout << z<< endl;




return 0;
}
