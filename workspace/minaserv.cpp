#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <pthread.h>
#include <netinet/tcp.h>
#include <unordered_map>
#include "opencv4/opencv2/opencv.hpp"
#include <nlohmann/json.hpp>
#include "DBforimg.hpp"
#define BUF_SZIE 4000
#define MAX_CLNT 100
using namespace std;
using json = nlohmann::json;

void *handle_clnt(void *arg);
// void oneread_oneread(int mysock,string msg);
void chat_msg(string clnts, char *msg, int len);
void error_handling(string message);
void send_clnt(string msg, int sock);

// void* QnAToFile_T(void* arg);
void chatprotocol(string msg, int sock);
// void chatprotocol(int clnt_sock,int* login,chatserver* my,King* king,string msg,string* aka,int* status);
int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];

unordered_map<int, int> clnt_fid;	 // 고유번호->소켓
unordered_map<int, string> clnt_aka; // 소켓->이름
unordered_map<string, int> waitqna;	 // 고객이름->소켓
unordered_map<string, int> goqna;	 // cs이름->소켓
unordered_map<string, int> csonline; // cs들이 로그인하면 저장좀해야겠으
unordered_map<string, string (*)(string, int)> theyfun;
unordered_multimap<string, string> fileDriver; // 파일을 위한 대화내용 연결 딕셔너리
pthread_mutex_t mutx;

// opencv프로젝트시작
void snedVectorMsg(string msg, int sock); // 크기만큼 할당해서 데이터 보내기
vector<uchar> reciveimdata;				  // 이미지 데이터를 임시저장할 벡터
string saveimg(string msg, int sock);
string getimg(string msg, int sock);
string getprice(string msg, int sock);
string usemoneydata(string msg, int sock);

int main(int argc, char *argv[])
{
	signal(SIGPIPE, SIG_IGN);

	int serv_sock, clnt_sock;
	sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	pthread_t t_id;
	srand(time(NULL));
	// if(argc!=2)
	// {
	//     cout<<"Usage : "<<argv[0] <<" <prot>\n";
	//     exit(1);
	// }
	memset(clnt_socks, 0, MAX_CLNT * 2);

	pthread_mutex_init(&mutx, NULL);

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	// int recvBufSize = 64000; // Example: 8KB
	// if (setsockopt(serv_sock, SOL_SOCKET, SO_RCVBUF, &recvBufSize, sizeof(recvBufSize)) < 0) {
	//     std::cerr << "setsockopt failed" << std::endl;
	//     close(serv_sock);
	//     return 1;
	// }

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi("10001"));

	theyfun.insert(pair<string, string (*)(string, int)>("이미지전송", getimg));
	theyfun.insert(pair<string, string (*)(string, int)>("값호출", getprice));
	theyfun.insert(pair<string, string (*)(string, int)>("DAYDAY", usemoneydata));
	if (bind(serv_sock, (sockaddr *)&serv_adr, sizeof(serv_adr)))
		error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	// pthread_detach(t_id);
	// pthread_create(&t_id,NULL,QnAToFile_T,(void*)&clnt_sock);
	// pthread_detach(t_id);
	// pthread_create(&t_id,NULL,showcustomer,(void*)&clnt_sock);
	// pthread_detach(t_id);

	while (1)
	{
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (sockaddr *)&clnt_adr, &clnt_adr_sz);
		// int recv_buffer_size = 64000; // 수신 버퍼 크기 설정
		// if (setsockopt(clnt_sock, SOL_SOCKET, SO_RCVBUF, &recv_buffer_size, sizeof(recv_buffer_size)) < 0)
		//  {
		//     perror("Setsockopt for SO_RCVBUF failed");
		//     exit(EXIT_FAILURE);
		// }
		pthread_mutex_lock(&mutx); // handle_cnt에서 순서를 정렬할때 새로들어오는것을 막아주기위해 lock 함
		clnt_socks[clnt_cnt++] = clnt_sock;
		pthread_mutex_unlock(&mutx);
		pthread_create(&t_id, NULL, handle_clnt, (void *)&clnt_sock); // 쓰레드 id하나로 클라이언트 수만큼 쓰래드를 생성해주는 부분 클라이언트는 1개의 전용 쓰래드를 할당받음
		pthread_detach(t_id);										  // 할당한 쓰래드를 프로세스 종료와 함께 종료시키거나 클라이언트가 종료하면 자동으로 쓰레드가 종료되게 때어냄
		puts("Connected client IP: ");
		puts(inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);
	return 0;
}

void *handle_clnt(void *arg)
{
	int clnt_sock = *((int *)arg);
	int i;
	int *status = new int;
	int *str_len = new int;
	int *login = new int;
	char *msg = new char[BUF_SZIE];
	string *aka = new string;
	int flag = 1;

	setsockopt(clnt_sock, IPPROTO_TCP, TCP_NODELAY, (void *)&flag, sizeof(int));
	unordered_map<string, int>::iterator iter;
	unordered_map<int, string>::iterator ater;
	string mymsg;
	memset(msg, 0, BUF_SZIE);
	while ((*str_len = recv(clnt_sock, msg, BUF_SZIE, 0)) != 0)
	{
		msg[*str_len] = 0;
		mymsg = msg;
		if (*status == 1)
		{
			continue;
		}
		chatprotocol(mymsg, clnt_sock);
		memset(msg, 0, BUF_SZIE);
		// puts(msg);
	}
	pthread_mutex_lock(&mutx);	   // 만약 다른 클라이언트가 비슷한 시기에 접속을 종료했다면 밑에 for문이 돌기전에 진입하게된다.그렇게되면 소켓번호를
	for (i = 0; i < clnt_cnt; i++) // 재정렬하는 과정에서 하나가 또 지워지거나 정렬하고. 있는거 또 정렬해서 순번이 꼬이는 사건이 발생할 수 있다. 그 사건을 막기위한 lock
	{
		if (clnt_sock == clnt_socks[i])
		{
			while (i++ < clnt_cnt - 1)
				clnt_socks[i] = clnt_socks[i + 1]; // i번째를 탈락시켰기 때문에 i번째 소켓을 i+1번째로 한칸 씩 덮어쒸운다.
			break;
		}
	}
	clnt_cnt--;
	iter = waitqna.find(*aka);
	// 딕셔너리 키 벨류 iter->first 키 iter->second 벨류

	if (iter != waitqna.end())
	{
		waitqna.erase(iter->first);
	}
	iter = csonline.find(*aka);

	if (iter != csonline.end())
	{
		csonline.erase(*aka);
	}
	ater = clnt_aka.find(clnt_sock);

	if (ater != clnt_aka.end())
	{
		clnt_aka.erase(clnt_sock);
	}

	pthread_mutex_unlock(&mutx); // 모든 정렬이 끝나고나서 unlock
	clnt_fid.erase(*login);
	delete str_len;
	delete login;
	delete msg;
	close(clnt_sock);
	return NULL;
}

void chatprotocol(string msg, int sock)
{

	try
	{
		json j = json::parse(msg);
		string k;
		unordered_map<string, string (*)(string, int)>::iterator iter;
		iter = theyfun.find(j["protocol"]);
		puts(j["protocol"].dump().c_str());
		if (iter != theyfun.end())
		{
			k = iter->second(msg, sock);
			if (k.compare("X") != 0)
				snedVectorMsg(k, sock);
		}
		else if (k.compare("X") == 0)
		{
			puts("문제없음");
		}
		else
		{
			k = "프로토콜 오류" + msg;
			puts(k.c_str());
			snedVectorMsg(k, sock);
		}
	}
	catch (json::exception &e)
	{
		puts(msg.c_str());
		// snedVectorMsg((string)"json타입이 아닙니다.",sock);
	}
}

string getimg(string msg, int sock)
{
	ostringstream oss;
	json j;
	uchar *buffer = new uchar[BUF_SZIE];
	int len;
	while (true)
	{
		try
		{

			while ((len = recv(sock, buffer, BUF_SZIE, 0)) != 0)
			{
				cout << strlen((char *)buffer) << endl;
				buffer[len] = 0;
				json j = json::parse((string)(char *)buffer);

				if (((string)j["protocol"]).compare("이미지전송완료") == 0)
				{
					string k = saveimg(j.dump(), sock);
					return k;
				}
			}
		}
		catch (const json::exception &e)
		{
			for (int i = 0; i < len; i++)
			{
				reciveimdata.push_back(buffer[i]);
			}
			if (strlen((char *)buffer) == 4000)
				return "길이가 4000바이트 이상입니다.";
		}
	}

	return (string) "X";
}

string saveimg(string msg, int sock)
{
	try
	{
		Dbim dbim;
	
		vector<uchar> imgdata;

		cv::Mat img = cv::imdecode(cv::Mat(reciveimdata), -1);
		cv::imshow("img", img);
		cv::waitKey(3000);
		cv::destroyAllWindows();
		ostringstream oss2;
		time_t curTime = time(NULL);
		tm *PLocal = NULL;
		PLocal = localtime(&curTime);
		localtime_r(&curTime, PLocal);
		oss2 << PLocal->tm_year + 1900 << PLocal->tm_mon + 1 << PLocal->tm_mday << PLocal->tm_hour
			 << PLocal->tm_min << PLocal->tm_sec;
		string filename = "/home/lms/test/myc-1/ImageFolder/" + oss2.str() + ".png";
		if (cv::imwrite(filename, img))
		{

			puts(dbim.savepath(filename).c_str());
			puts(dbim.savetext(msg).c_str());
		}

		reciveimdata.erase(reciveimdata.begin(), reciveimdata.end());

		return (string) "이미지수신성공!";
	}
	catch (cv::Exception &e)
	{
		puts(e.what());
		reciveimdata.erase(reciveimdata.begin(), reciveimdata.end());
	}
	return (string) "X";
}

string getprice(string msg, int sock)
{
	Dbim db;
	string value = db.Getvalue();
	return value;
}

string usemoneydata(string msg, int sock)
{
	Dbim db;
	string value = db.GetVariousvalue();
	return value;
}

void snedVectorMsg(string msg, int sock)
{
	int k = msg.length();
	char *vchar = new char[k + 1];
	msg.copy(vchar, k);
	write(sock, vchar, k);
	delete vchar;
}

void error_handling(string message)
{
	cerr << message << endl;
	exit(1);
}