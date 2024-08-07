#ifndef API_DATA_PROCESSING_CLASS_APPAP__
#define API_DATA_PROCESSING_CLASS_APPAP__
#include<nlohmann/json.hpp>
#include <iostream>
#include <cstdlib>
#include<cstring>
#include<vector>
#include<array>
using json = nlohmann::json;
class ShowYourData
{
private:
    struct MemoryStruct 
    {
    char *memory;
    size_t size;
    
    MemoryStruct() : memory((char*)malloc(1)), size(0) {}
    ~MemoryStruct() { free(memory); }
    };

    static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        size_t realsize = size * nmemb;
        MemoryStruct *mem = (MemoryStruct *)userp;

        char *ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
        if(ptr == NULL) {
            std::cerr << "Not enough memory (realloc returned NULL)" << std::endl;
            return 0;
        }

        mem->memory = ptr;
        std::memcpy(&(mem->memory[mem->size]), contents, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
        return realsize;
    }

public:
    std::string AnimalData(std::string data,int clk)
    {
    CURL *curl;
    CURLcode res;
    std::string k;
    MemoryStruct chunk;
    json j=json::parse(data);
    //X-Api-Key
    std::string serviceKey = "gDqHoozs61B5ueUgELCNzA==BNnwzywrO1HJpfw8"; // 서비스 키를 여기에 입력하세요.
    std::string url = "https://api.api-ninjas.com/v1/animals?name=";
    url +=(string)j["animal"];
    curl_slist *headrs =NULL;
    headrs = curl_slist_append(headrs,"X-Api-Key: gDqHoozs61B5ueUgELCNzA==BNnwzywrO1HJpfw8");


    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headrs);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            k=curl_easy_strerror(res);
        } 
        else {
            // std::cout << chunk.size << " bytes retrieved" << std::endl;
            
            k =(std::string)chunk.memory;//받아온데이터를 string타입으로 변환
            try{
            json js=json::parse(k);
            return js[0].dump(4);
            }catch(json::parse_error &e)
            {
                puts(e.what());
            }
            
            

            
            // std::cout << chunk.memory << std::endl;
                                                        
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();    
    return k ;
    }

    std::string GPTMAN(std::string msg,int clk)
    {
    CURL *curlpost;
    CURLcode res;
    std::string k;
    MemoryStruct chunk;
    json kz=json::parse(msg);
    string data =kz["qna"];    
    // json j=json::parse(data);
    //X-Api-Key
    // std::string serviceKey = "gDqHoozs61B5ueUgELCNzA==BNnwzywrO1HJpfw8"; // 서비스 키를 여기에 입력하세요.
    std::string url = "https://api.openai.com/v1/chat/completions";
    // url +=(string)j["animal"];
    curl_slist *headrs =NULL;
    headrs = curl_slist_append(headrs, "Content-Type: application/json");
    headrs = curl_slist_append(headrs, "Authorization: Bearer  sk-proj-H4Z1zR1fsZOzNC5oqsOaT3BlbkFJCBTKXr0Q1KJZGnEJmxEO");
    string initdata= R"(
    {
    "model": "gpt-3.5-turbo",
    "messages": [
        {"role": "system", "content": "친절하지만 종종 반말을 해줘"},
        {"role": "user", )";
    
   string initdata2=R"( "content": )"+ (string)"\""+data+(string)"\"" +R"( }
    ],
    "max_tokens": 1000
})";
    initdata+=initdata2;
 
   
    curl_global_init(CURL_GLOBAL_ALL);
    curlpost = curl_easy_init();
    // char* encoded =curl_easy_escape(curlpost,initdata.c_str(),0);
    if(curlpost) {
        curl_easy_setopt(curlpost, CURLOPT_TIMEOUT, 20L); // 20초 타임아웃 설정
        curl_easy_setopt(curlpost, CURLOPT_CONNECTTIMEOUT, 10L);// 연결 타임아웃 설정
        curl_easy_setopt(curlpost, CURLOPT_URL, url.c_str());  
        curl_easy_setopt(curlpost,CURLOPT_HTTPHEADER,headrs);
        curl_easy_setopt(curlpost, CURLOPT_POST, 1L);
        curl_easy_setopt(curlpost, CURLOPT_POSTFIELDS,initdata.c_str());
        // curl_easy_setopt(curlpost,  CURLOPT_COPYPOSTFIELDS, encoded);
        curl_easy_setopt(curlpost, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curlpost, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curlpost, CURLOPT_USERAGENT, "libcurl-agent/1.0");
         
        res = curl_easy_perform(curlpost);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            k=curl_easy_strerror(res);
        } 
        else {
            // std::cout << chunk.size << " bytes retrieved" << std::endl;
            
            k =(std::string)chunk.memory;//받아온데이터를 string타입으로 변환

            // std::cout << chunk.memory << std::endl;
                                                        
        }

        curl_easy_cleanup(curlpost);
    }
json j=json::parse(k);



    curl_global_cleanup();    
    return (string)j["choices"][0]["message"]["content"];
    }




};
#endif