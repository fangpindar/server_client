#pragma comment(lib, "Ws2_32")
 
#include <WinSock2.h>
#include <iostream>
#include <string.h>
#include <windows.h>
using namespace std;
/****************************************************************************/
int r;
int num = 0;
SOCKET sConnect[10]; 
int IDPool[10]={0};
int count = 0;
char message[200];
/****************************************************************************/
DWORD WINAPI DoSomething(LPVOID parameter)
{
	int index = count-1;
	//要做的事情↓↓↓↓
	int ID = 0;
	for(int i = 0; i<10; i++){
		if(IDPool[i]==0){
			ID = i;
			IDPool[i]=1;
			num++;
			break;
		}
	}
	cout << "server: got connection from new client. ("<<ID+1<<"/10)" << endl; 
    //傳送訊息給client
    //char *sendbuf = "Connection successd!! you are Client(";//+*(DWORD*)parameter+")\n";
    char sendbuf[2];
    char sendbuf2[1000];
	sprintf(sendbuf,"%d",ID);
    /*cout<<sendbuf;
    for(int x = 0;x<ID;x++)*sendbuf++;
    cout<<sendbuf;*/
    send(sConnect[index], sendbuf, (int)strlen(sendbuf), 0);
    while(strcmp(message,"exit")){
    	ZeroMemory(sendbuf2,1000);
        ZeroMemory(message, 200);
        r = recv(sConnect[index], message, sizeof(message), 0);
        if(strcmp(message,"exit")==0)break;
		cout <<"The message from client("<<ID<<"):"<<message << endl;
        strcat(sendbuf2,"The message from client(");
        strcat(sendbuf2,sendbuf);
        strcat(sendbuf2,"):");
        strcat(sendbuf2,message);
        for(int n = 0; n<count ; n++){
        	if(n != ID){
        		send(sConnect[n], sendbuf2, (int)strlen(sendbuf2), 0);//////////////////////////////////////////////////??????????????
			}
		}
	}
	//cout<<strcmp(message,"exit")<<endl;
	//cout<<message<<endl;
  	strcat(sendbuf2,"The Client (");
    strcat(sendbuf2,sendbuf);
    strcat(sendbuf2,") is disconnecting...");
    for(int n = 0; n<=num ; n++){
    	if(n != ID){
   			send(sConnect[n], sendbuf2, (int)strlen(sendbuf2), 0);//////////////////////////////////////////////////??????????????
		}
	}
	cout <<"The Client ("<<ID<<") is disconnecting..."<<endl;
	num--;
	IDPool[ID]=0;
	ZeroMemory(message, 200);
	//要做的事情↑↑↑↑
	return 0;
}
/****************************************************************************/
int main(void)
{
    WSAData wsaData;
    WORD DLLVSERION;
    DLLVSERION = MAKEWORD(2,1);
 
    
    r = WSAStartup(DLLVSERION, &wsaData);
    SOCKADDR_IN addr;
    int addrlen = sizeof(addr);

    SOCKET sListen;
    
    for(int i = 0; i<10;i++)
		sConnect[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 
    
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
 
   
    sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);
 
    SOCKADDR_IN clinetAddr;
	
	cout << "Server starting..." << endl;
	DWORD ThreadID[10] , parameter;
	HANDLE ThreadHandle;

    while(true)
    {
    	
        if(sConnect[count] = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen))
        {
			ThreadHandle =  CreateThread(NULL,
										 0,
										 DoSomething, //thread要執行的function
										 &parameter, //function需要的參數
										 0,
										 &ThreadID[count]); //儲存thread id
        	count++;
		}
    }
    WSACleanup(); 
    return 0;
}

