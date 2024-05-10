#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main()
{
    
    string filename="data.txt";
    ifstream i;
    ofstream a;
    string buffer;
    size_t c=0;
    int d=0;
    int e=0;
    i.open(filename,ios_base::in);
    string* kk;
    i.seekg(0,ios_base::end);
    int size=i.tellg();
    buffer.resize(size);
    i.seekg(0,ios_base::beg);
    i.read(&buffer[0],size);
    i.close();
    ofstream aaaaaa;
    a.open(filename,ios_base::out);
    d=stoi(buffer.substr(0,buffer.find(',')));
    c=buffer.find('\n')+1;
    kk=new string (buffer.substr(c,buffer.find('\n')));
    e=stoi(buffer.substr(c,buffer.find(',')));
    if(d!=e)
    {
        a<<buffer.substr(0,buffer.find('\n'))<<endl;
        a<<*kk<<endl;
    }
    delete kk;
    int vm=0;
    while (vm<1308)
    {
        c=buffer.find('\n',c)+1;
        kk=new string (buffer.substr(c,buffer.find('\n')));
        e=std::stoi(buffer.substr(c,buffer.find(',')));
        if(d!=e)
            a<<*kk<<endl;
        delete kk;
    }
    a.close();
    return 0;    
}