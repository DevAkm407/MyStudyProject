#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    using namespace std;
    ifstream pipe("mypipe");
    string data;
    getline(pipe,data);
    cout << "Received from test.cpp" << data << endl;
    return 0;
}