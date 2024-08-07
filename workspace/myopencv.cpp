#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include "opencv4/opencv2/opencv.hpp"
#include<nlohmann/json.hpp>
using namespace cv;
using namespace std;
using json = nlohmann::json;
int main()
{     
   Mat img =imread("/home/lms/ess.png");
   imshow("img",img);
   waitKey(0);
   destroyAllWindows();
    
    
    

   
   
    return 0;
}