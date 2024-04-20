#include <iostream>
#include <fstream>
#include <string>

int main()
{
using namespace std;
ofstream outfile;

outfile.open("scores.txt");
outfile << 1;
outfile.close();
return 0;
}