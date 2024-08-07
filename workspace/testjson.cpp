#include<nlohmann/json.hpp>
#include <iostream>
#include <cstdlib>
#include<cstring>
#include<curl/curl.h>
#include<vector>
#include<array>

using json = nlohmann::json;
struct MemoryStruct {
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

int main()
{
    
    CURL *curl;
    CURLcode res;

    MemoryStruct chunk;
    
    //X-Api-Key
    std::string serviceKey = "gDqHoozs61B5ueUgELCNzA==BNnwzywrO1HJpfw8"; // 서비스 키를 여기에 입력하세요.
    std::string url = "https://api.api-ninjas.com/v1/animals?name=cheetah";
    curl_slist *headrs =NULL;
    headrs = curl_slist_append(headrs,"X-Api-Key: gDqHoozs61B5ueUgELCNzA==BNnwzywrO1HJpfw8");


    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headrs);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } 
        else {
            // std::cout << chunk.size << " bytes retrieved" << std::endl;
            
            std::string k =(std::string)chunk.memory;//받아온데이터를 string타입으로 변환
            json j=json::parse(k);
            std::cout<<"location ";
            for (std::string location : j[0]["locations"])
            {
                std::cout<<location<<" ";
            }
            
                      
            // std::cout << chunk.memory << std::endl;
                                                
        
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
    // json j={
    //     {"id","myid"},
    //     {"created",12345567},
    //     {"model","gpt-3.5-turbo-0125"},
    //     {"choices",{"index",0,"massage",{"role","assistant","content","Hello! How cain iassist you today?"}},{"logprobs",NULL,"finsh_reason","stop"}},
    //     {"usage",{"prompt_tokens",21},{"completion_tokens",9},{"total_tokens",30}},
    //     {"system_finterprint",NULL}

    // };
    // const auto JSON_INDENT = 2;
    // std::string strJson = R"(
    //     {

    //     "id": "",

    //     "object": "",

    //     "created":  "",

    //     "model": "gpt-3.5-turbo-0125",

    //     "choices": [

    //         {

    //         "index": 0,

    //         "message": {

    //             "role": "assistant",

    //             "content": "Hello! How can I assist you today?"

    //         },

    //         "logprobs": null,

    //         "finish_reason": "stop"

    //         }

    //                 ],

    //         "usage":     {

    //                         "prompt_tokens": 21,

    //                         "completion_tokens": 9,

    //                         "total_tokens": 30

    //                     },

    //     "system_fingerprint": null

    //     }
    //     )";
    
    // json obj=json::parse(strJson);
    // json obj2=obj["choices"][0]["message"]["content"];
    // std::cout<<obj2.dump(JSON_INDENT);
    

        

            
    // auto j =json::parse(strJson);
    // for(json::iterator it =obj2.begin(); it !=obj2.end(); ++it)
    // {
    //     std::cout <<"Key :\"" << it.key() <<"\" "      
    //     std::cout <<"velue:\""<<it.value() <<"\""<<std::endl;
    // }
     
    // std::cout << j<<std::endl;


    // return 0;
}