#include<iostream>
#include<string>
using namespace std;

class  Appliances
{
private:
    static int count;
public:
    Appliances(/* args */)
    {
        count++;
        if(count==10)
            count=0;
    }
    Appliances(const Appliances& copy)
    {
        count++;
    }
    virtual ~Appliances(){}
    int getcount() const {return count;}
    virtual void on() =0;
    virtual void off() =0;
    virtual void up1() =0;
    virtual void down1()=0;
    virtual void down2()=0;
    virtual void up2() =0;
    virtual void mode(string) =0;
    virtual void registration() =0;
};
int Appliances::count=-1;

class Tv :public Appliances
{
private:
    int channel;
    int volume;
    int number;
    string* sleepingtime;
    string* companyName;
    string* place;  
public:
    Tv(string cn,string p)
    {
        channel=1;
        volume=10;
        number=getcount();
        sleepingtime=new string("없음");
        companyName=new string(cn);
        place =new string(p);
        registration();
    }
    Tv(const Tv& copy):channel(copy.channel),volume(copy.volume)
    {
        this->sleepingtime=new string(*copy.sleepingtime);
        this->companyName=new string(*copy.companyName);
    }
    
    virtual ~Tv()
    {
        cout<<"Tv 삭제"<<endl;
        delete sleepingtime;
        delete companyName;
        delete place;
        
    }
    void registration()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "티비가 등록되었습니다."<<endl;
    }

    void on()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "티비가 켜졌습니다."<<endl;
    }

    void off()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "티비가 꺼졌습니다."<<endl;
    }
    void up1()
    {
        channel++;
        cout <<"채널up 현재채널은: "<<channel <<"입니다."<<endl; 
    }
    
    void up2()
    {
        volume++;
        cout <<"볼륨up 현재볼륨은: "<<volume <<"입니다."<<endl; 
    }
    void down1()
    {
        channel--;
        cout <<"채널down 현재채널은: "<<channel <<"입니다."<<endl; 
    }
    
    void down2()
    {
        volume--;
        cout <<"볼륨down 현재볼륨은: "<<volume <<"입니다."<<endl; 
    }
    void mode(string stime)
    {
        delete sleepingtime;
        sleepingtime=new string(stime);
        cout<<"텔레비젼 취침시간을 "<<*sleepingtime<<"으로 설정했습니다."<<endl;
    }

};

class Air_conditioner :public Appliances
{
private:
    double Temperature;
    int winPower;
    int number;
    string* sleepingtime;
    string* companyName;
    string* place;  
public:
    Air_conditioner(string cn,string p)
    {
        Temperature=18.0;
        winPower=10;
        number=getcount();
        sleepingtime=new string("없음");
        companyName=new string(cn);
        place =new string(p);
        registration();
    }
    Air_conditioner(const Air_conditioner& copy):Temperature(copy.Temperature),winPower(copy.winPower)
    {
        this->sleepingtime=new string(*copy.sleepingtime);
        this->companyName=new string(*copy.companyName);
    }
    
    virtual ~Air_conditioner()
    {
        cout<<"에어컨 삭제"<<endl;
        delete sleepingtime;
        delete companyName;
        delete place;
        
    }
    void registration()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "에어컨이 등록되었습니다."<<endl;
    }
    
    void on()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "에어컨이 켜졌습니다."<<endl;
    }

    void off()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "에어컨이 꺼졌습니다."<<endl;
    }
    void up1()
    {
        Temperature++;
        cout <<"온도up 현재온도는: "<<Temperature <<"입니다."<<endl; 
    }
    
    void up2()
    {
        winPower++;
        cout <<"바람up 현재바람세기는: "<<winPower <<"입니다."<<endl; 
    }
    void down1()
    {
        Temperature--;
        cout <<"온도down 현재온도는: "<<Temperature <<"입니다."<<endl; 
    }
    
    void down2()
    {
        winPower--;
        cout <<"바람down 현재바람세기는: "<<winPower <<"입니다."<<endl; 
    }
    void mode(string stime)
    {
      
        delete sleepingtime;
        sleepingtime=new string(stime);
        cout<<"에어컨 취침시간을 "<<*sleepingtime<<"으로 설정했습니다."<<endl;
    }

};

class Air_purifier :public Appliances
{
private:
    string* winVector;
    int winPower;
    int number;
    string* sleepingtime;
    string* companyName;
    string* place;  
public:
    Air_purifier(string cn,string p)
    {
        winPower=10;
        winVector=new string("정면");
        number=getcount();
        sleepingtime=new string("없음");
        companyName=new string(cn);
        place =new string(p);
        registration();
    }
    Air_purifier(const Air_purifier& copy):winPower(copy.winPower)
    {
        this->winVector=new string(*copy.winVector);
        this->sleepingtime=new string(*copy.sleepingtime);
        this->companyName=new string(*copy.companyName);
    }

    virtual ~Air_purifier()
    {
        cout<<"공기청정기 삭제"<<endl;
        delete sleepingtime;
        delete companyName;
        delete place;
        
    }
    
    void registration()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "공기청정기가 등록되었습니다."<<endl;
    }

    void on()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "공기청정기가 켜졌습니다."<<endl;
    }

    void off()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "공기청정기가 꺼졌습니다."<<endl;
    }
    void up1()
    {
        delete winVector;
        winVector=new string("위");
        cout <<"방향up 현재 바람방향은: "<< *winVector<<"입니다."<<endl; 
    }
    
    void up2()
    {
        winPower++;
        cout <<"바람up 현재바람세기는: "<<winPower <<"입니다."<<endl; 
    }
    void down1()
    {
        delete winVector;
        winVector=new string("아래");
        cout <<"방향down 현재바람방향은: "<<*winVector <<"입니다."<<endl; 
    }
    
    void down2()
    {
        winPower--;
        cout <<"바람down 현재바람세기는: "<<winPower <<"입니다."<<endl; 
    }
    void mode(string stime)
    {
        delete sleepingtime;
        sleepingtime=new string(stime);
        cout<<"공기청정기 취침시간을 "<<*sleepingtime<<"으로 설정했습니다."<<endl;
    }
};


class Light :public Appliances
{
private:
    string* companyName;
    string* place;
    int number;
    void up1() {}
    void down1(){}
    void down2(){}
    void up2() {}
    void mode(string) {}
public:
    Light(string cn,string p)
    {
        companyName=new string(cn);
        place =new string(p);
        number=getcount();
        registration();
    }
    Light(const Light& copy)
    {
        this->companyName=new string(*copy.companyName);
    }

    virtual ~Light()
    {
        cout<<"전등 삭제"<<endl;
        delete companyName;
        delete place;
        
    }
    void registration()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "전등이 등록되었습니다."<<endl;
    }
    void on()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "전등이 켜졌습니다."<<endl;
    }

    void off()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "전등이 꺼졌습니다."<<endl;
    }
    
};

class Clock :public Appliances
{
private:
    int hour;
    int min;
    int number;
    string* sleepingtime;
    string* companyName;
    string* place;  
public:
    Clock(string cn,string p)
    {
        hour=12;
        min=0;
        number=getcount();
        sleepingtime=new string("없음");
        companyName=new string(cn);
        place =new string(p);
        registration();
    }
    
    Clock(const Clock& copy):hour(copy.hour),min(copy.min)
    {
        this->sleepingtime=new string(*copy.sleepingtime);
        this->companyName=new string(*copy.companyName);
    }

    virtual ~Clock()
    {
        cout<<"시계 삭제"<<endl;
        delete sleepingtime;
        delete companyName;
        delete place;
    }
    void registration()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "시계가 등록되었습니다."<<endl;
    }
    void on()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "시계가 켜졌습니다."<<endl;
    }

    void off()
    {
        cout<<number<<"번 "<< *place<<"의 "<< *companyName<<"사 " << "시계가 꺼졌습니다."<<endl;
    }
    void up1()
    {
        hour++;
        if(hour==24)
            hour=0;
        cout <<"시간up 현재 시간(hour)은: "<< hour<<" 입니다."<<endl; 
    }
    
    void up2()
    {
        min++;
        if(min==60)
            min=0;
        cout <<"분up 현재분(minute)은: "<<min <<" 입니다."<<endl; 
    }
    void down1()
    {
        hour--;
        if(hour==-1)
            hour=23;
        cout <<"시간down 현재시간(hour)은: "<<hour <<" 입니다."<<endl; 
    }
    
    void down2()
    {
        min--;
        if(min==-1)
            min=59;
        cout <<"분down 현재분(minute)은: "<<min <<"입니다."<<endl; 
    }
    void mode(string stime)
    {
        delete sleepingtime;
        sleepingtime=new string(stime);
        cout<<"알람시간을 "<<*sleepingtime<<"으로 설정했습니다."<<endl;
    }
};


class Remote_control
{
private:
  Appliances* appList[10];
public:
    Remote_control()
    {
        for (int  i = 0; i < 10; i++)
        {
            appList[i]=NULL;
        }
    }
    
    ~Remote_control()
    {
        cout<<"리모컨 삭제"<<endl;
        for (int i = 0; i < 10; i++)
        {
        if(appList[i] !=NULL)  
            delete appList[i];
        }
        
    }
    //클래스이름,회사이름,장소를 문자열로 기입할것
    Appliances* registAccessories(string classname, string companyName,string place)
    {
        Appliances* a;
        if(classname.compare("Tv")==0||classname.compare("티비")==0)
        {
            a= new Tv(companyName,place);
            appList[a->getcount()]=a;
        }

        else if(classname.compare("Air_conditioner")==0||classname.compare("에어컨")==0)
        {
            a= new Air_conditioner(companyName,place);
            appList[a->getcount()]=a;
        
        }

        else if(classname.compare("Air_purifier")==0||classname.compare("공기청정기")==0)
        {
            a= new Air_purifier(companyName,place);
            appList[a->getcount()]=a;
        }
    
        else if(classname.compare("Light")==0||classname.compare("전등")==0)
        {
            a= new Light(companyName,place);
            appList[a->getcount()]=a;
        }

        else if(classname.compare("Clock")==0||classname.compare("시계")==0)
        {
            a= new Clock(companyName,place);
            appList[a->getcount()]=a;
        }
        else
        {
            cout<<"만들어진 객체가 없습니다 return NULL"<<endl;    
            return NULL;
        } 
        
        cout<<classname<<" 만들기 성공 return "<<classname<<endl;
        return a;
    }
    //Appliances*로 받을것

    Appliances* allRegist_10()
    {
        registAccessories("Tv","L","거실");
        registAccessories("Tv","S","안방");
        registAccessories("Air_conditioner","L","거실");
        registAccessories("에어컨","S","안방");
        registAccessories("Air_purifier","L","거실");
        registAccessories("Light","L","거실");
        registAccessories("Light","L","안방");
        registAccessories("Light","L","현관");
        registAccessories("Light","L","화장실");
        registAccessories("Clock","L","거실");
        registAccessories("Clock","L","안방");
        return *this->appList;
    }
    
    void allOn()
    {
        for (int i = 0; i < 10; i++)
        {
           if(appList[i] !=NULL)
                appList[i]->on();
        }
    }

    void allOff()
    {
        for (int i = 0; i < 10; i++)
        {
           if(appList[i] !=NULL)
                appList[i]->off();
        }
    }
    void allUp1()
    {
        for (int i = 0; i < 10; i++)
        {
           if(appList[i] !=NULL)
                appList[i]->up1();
        }
    }
    void allUp2()
    {
        for (int i = 0; i < 10; i++)
        {
           if(appList[i] !=NULL)
                appList[i]->up2();
        }
    }
    
    void allDown1()
    {
        {
        for (int i = 0; i < 10; i++)
        {
           if(appList[i] !=NULL)
                appList[i]->down1();
        }
    }
    }
    
    void allDown2()
    {
        for (int i = 0; i < 10; i++)
        {
           if(appList[i] !=NULL)
                appList[i]->down2();
        }
    }
        

    void allMode(string time)
    {
        for (int i = 0; i < 10; i++)
        {
           if(appList[i] !=NULL)
                appList[i]->mode(time);
        }
    }
};

int main()
{
    Remote_control* remocon =new Remote_control(); 
    Appliances* allApps;
    allApps=remocon->allRegist_10();
    remocon->allOn();
    remocon->allOff();
    remocon->allUp1();
    remocon->allUp2();
    remocon->allDown1();
    remocon->allDown2();
    remocon->allMode("10시30분");
    delete remocon;
    return 0;
}