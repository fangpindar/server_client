#pragma comment(lib, "Ws2_32.lib")
 
#include <WinSock2.h>
#include <iostream>
#include <string.h>
#include <windows.h> 
#include <conio.h> 
using namespace std;
/****************************************************************************/
SOCKET sConnect;
int r;
char message[200];
char sendbuf[50];
DWORD WINAPI DoSomething(LPVOID parameter)
{	
	while(1){
		ZeroMemory(message, 200);
    	r = recv(sConnect, message, sizeof(message), 0);
    	if(strcmp(sendbuf,"exit")==0)break;
    	cout<<message<<endl;
	}
} 
/****************************************************************************/
int main(void)
{
    WSAData wsaData;
    WORD DLLVersion;
    DLLVersion = MAKEWORD(2,1);
    r = WSAStartup(DLLVersion, &wsaData);
 
    SOCKADDR_IN addr;
 
    int addlen = sizeof(addr);
    
    sConnect = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);


    connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
    //����server���T��
    ZeroMemory(message, 200);
    r = recv(sConnect, message, sizeof(message), 0);
    cout <<"Connection successd!! you are Client("<<message<<")"<<endl;

	DWORD ThreadID , parameter;
	HANDLE ThreadHandle;
	ThreadHandle =  CreateThread(NULL,
								 0,
								 DoSomething, //thread�n���檺function
								 &parameter, //function�ݭn���Ѽ�
								 0,
								 &ThreadID); //�x�sthread id	

	while(strcmp(sendbuf,"exit")){
		while(!kbhit()){

		}
		cout<<"enter message:";
		cin.getline(sendbuf,50);//�ݧ�i 
		send(sConnect,sendbuf,(int)strlen(sendbuf),0);
	}
	cout<<"The connect is over!\n";
	system("pause");
    closesocket(sConnect);
    WSACleanup(); 
 	return 0;
}
