#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>


#define BUF_SIZE 100
#define MAX_CLNT 256
#define NAME_SIZE 20
#define ALL 10
#define DISPLAY 11
#define WHISP 12

struct IDSOCKET {
	SOCKET Socket;
	char ID[NAME_SIZE];
	in_addr add;
}typedef IDSOCKET;


unsigned WINAPI HandleClnt(void * arg);
void SendMsg(char * msg, int len, int flag, char*Senter);
void ErrorHandling(char * msg);
int clntCnt = 0;
IDSOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;
int IdArr[MAX_CLNT];

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz;
	HANDLE  hThread;
	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");	hMutex = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	while (1) {
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);//Block ���ѷ���
		
		WaitForSingleObject(hMutex, INFINITE);
		for (int i = 0; i < NAME_SIZE; i++)
			clntSocks[clntCnt].ID[i] = NULL;
		clntSocks[clntCnt].Socket = hClntSock;
		recv(hClntSock, clntSocks[clntCnt].ID, sizeof(clntSocks[clntCnt].ID), 0);
		clntSocks[clntCnt].add = clntAdr.sin_addr;

		
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&clntSocks[clntCnt], 0, NULL);
		clntCnt++;
		
		ReleaseMutex(hMutex);

		
		printf("Connected client IP: %s \n",inet_ntoa(clntAdr.sin_addr));
		printf("������ ��:%d\n", clntCnt);
	}
	closesocket(hServSock);
	WSACleanup();
	return 0;
}
unsigned WINAPI HandleClnt(void * arg)
{
	IDSOCKET hClntSock = *((IDSOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];
	int flag = ALL;
	
	//Ŭ���̾�Ʈ�� q/Q �Է������� ���ѷ���

	while (1) {
		strLen = recv((hClntSock.Socket), msg, sizeof(msg), 0);
		
		if (strLen  == 0 || strLen==-1) {
			break;
		}
		else if(!strncmp(msg, "/i\n",3) || !strncmp(msg, "/I\n",3)){
			flag = DISPLAY;
		}
		//�ӼӸ�
		else if (!strncmp(msg, "/h", 2) || !strncmp(msg, "/H", 2)) {
			flag = WHISP;
		}
		//�⺻ �޼���������
		else {
			flag = ALL;
		}
		SendMsg(msg, strLen, flag, hClntSock.ID);
}
	
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i<clntCnt; i++)   // remove disconnected client
	{
		if (hClntSock.Socket == clntSocks[i].Socket)
		{
			while (i++ < clntCnt - 1) {
				clntSocks[i].add = clntSocks[i-1].add;
				strncpy((clntSocks[i-1].ID), (clntSocks[i].ID),NAME_SIZE);
				clntSocks[i-1].Socket = clntSocks[i].Socket;
			}
			break;
		}
	}

	clntCnt--; 

	ReleaseMutex(hMutex);
	closesocket(hClntSock.Socket);
	return 0;
}
void SendMsg(char * msg, int len, int flag,char*Senter)   // send to all
{
	int i,j;
	char addressee[NAME_SIZE];//�޴���

	WaitForSingleObject(hMutex, INFINITE);
	if (flag == ALL) {
		
		for (i = 0; i < clntCnt; i++) {
			send(clntSocks[i].Socket, Senter, NAME_SIZE, 0);
			send(clntSocks[i].Socket, msg, len, 0);
		}
	}
	else if (flag == DISPLAY) {
		char DISPmsg[BUF_SIZE];
		for (i = 0; i < clntCnt; i++) {
			//i����� ȣ���� ����� �´ٸ�
			if (strcmp(Senter, clntSocks[i].ID)==0) {
				for (j = 0; j < clntCnt; j++) {//���ֵ� ��������
					sprintf(DISPmsg, "%s %s\n", clntSocks[j].ID, inet_ntoa(clntSocks[j].add));
					send(clntSocks[i].Socket, DISPmsg, BUF_SIZE, 0);
					Sleep(1);
				}
				break;	
			}	
		}	
	}///i��ɾ� �� 
	else if (flag == WHISP) {
		char MSG[100];//�޼����� ������ ��
		char NewMsg[100];//���信 �°� �������Ұ�
		char* p=NULL;
		p= strtok(msg, " "); // /h�� �̾Ƴ�
		strcpy(addressee, strtok(NULL, " "));// [�г���] �޾ƿ�
		for (i = 0; i < clntCnt; i++) {
			//�Ӹ������ �´ٸ�
			if (strcmp(addressee, clntSocks[i].ID) == 0) {
				p = strtok(NULL, "\n");
				strcpy(MSG, p);
				sprintf(NewMsg, "�Ӽ�>%s:%s \n", Senter, MSG);// �Ӽ�>[����] �޼��� ���·� ����		
				send(clntSocks[i].Socket, NewMsg, len+8, 0);
				//break;
			}
				
			}
		}
	
	ReleaseMutex(hMutex);
	
}

void ErrorHandling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}