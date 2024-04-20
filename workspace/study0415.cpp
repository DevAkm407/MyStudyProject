// #include <iostream>
// #include <string>
// #include <fstream>

// int main()
// {
//     using namespace std;
    
//     char automobile[50];
//     int year;
//     double a_price;
//     double d_price;

//     ofstream outFile;
//     outFile.open("carinofo.txt");

//     cout<<"자동차메이커와 차종을 입력하시오: ";
//     cin.getline(automobile,50);
//     cout << "연식을 입력하시오: ";
//     cin >> year;
//     cout << "구입 가격을 입력하시오: ";
//     cin >> a_price;
//     d_price =0.913 *a_price;
//     cout << fixed;
//     cout.precision(2);
//     cout.setf(ios_base::showpoint);
//     cout << "메이커와 차종: " << automobile <<endl;
//     cout << "연식: " << year <<endl;
//     cout << "구입 가격 $" << a_price <<endl;
//     cout << "현재 가격 $" << d_price << endl;

//     outFile <<fixed;
//     outFile.precision(2);
//     outFile.setf(ios_base::showpoint);
//     outFile << "메이커와 차종: " << automobile <<endl;
//     outFile << "연식: " << a_price << endl;
//     outFile << "구입 가격 $" << a_price <<endl;
//     outFile << "현재 가격 $" << d_price << endl;

//     outFile.close();
//     return 0;
//     }

// #include <iostream>
// #include <fstream>
// #include <cstdlib>
// #include <string>

// const int SIZE = 60;
// int main()
// {
//     using namespace std;
//     string filename;
//     ifstream inFile;
//     cout <<"데이터 파일의 이름을 입력하시오: ";
//     getline(cin,filename);
//     inFile.open(filename);
//     if(!inFile.is_open())
//     {
//         cout << filename << " 파일을 열 수 없습니다." << endl;
//         cout << "프로그램을 종료합니다.\n";
//         exit(EXIT_FAILURE);
//     }
//     double value;
//     double sum = 0.0;
//     int count = 0;

//     inFile >> value;
//     while (inFile.good())
//     {
//         ++count;
//         sum += value;
//         inFile >> value;
//     }
//     if(inFile.eof())
//         cout << "파일 끝에 도달했습니다.\n";
//     else if(inFile.fail())
//         cout << "데이터 불일치로 입력이 종료되었습니다.\n";
//     else 
//         cout << "알 수 없는 이유로 입력이 종료되었습니다\n";
//     if (count == 0)
//         cout << "데이터가 없습니다.\n";
//     else
//     {
//         cout << "읽은 항목의 개수: " <<count << endl;
//         cout << "합계: " << sum <<endl;
//         cout << "평균: " <<sum / count << endl;
//     }

//     inFile.close();
//     return 0;
    
// }

// #include <iostream>
// #include "stock00.h"

// int main()
// {
//     Stock fluffy_the_cat;
//     fluffy_the_cat.acquire("NanoSmart",20,12.50);
//     fluffy_the_cat.show();
//     fluffy_the_cat.buy(15,18.125);
//     fluffy_the_cat.show();
//     fluffy_the_cat.sell(300000,0.125);
//     fluffy_the_cat.show();
//     return 0;
// }

#include <iostream>
#include "stock10.h"

int main()
{
    using std::cout;
    cout <<"생성자를 사용하여 새로운 객체들을 생성한다.\n";
    Stock stock1("NanoSmart",12,20.0);
    stock1.show();
    Stock stock2 =Stock("Boffo objects",2,2.0);
    stock2.show();
    
    cout <<"stock1을 stock2에 대입한다.\n";
    stock2 =stock1;
    cout <<"stock1과 stock2를 출력한다.\n";
    stock1.show();
    stock2.show();
    
    cout <<"생성자를 사용하여 객체를 재설정한다.\n";
    stock1 =Stock("Nifty Foods",10,50.0);
    cout << "갱신된 sotck1:\n";
    stock1.show();
    cout <<"프로그램을 종료합니다.\n";
    return 0;
}