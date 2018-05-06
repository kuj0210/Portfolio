#include "stems.h"
#include "request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define FALSE 0
#define ERR -1

 
struct msg {
	int confd;
	long time;
}typedef msg;

 

struct Q {
	msg* msgList;
	pthread_t* ptr;			

	int rear;
	int front;
	int count;
	int msgListSize;
	int thrpSize;
}typedef Q;

 

 

void initQ(Q*p, int thp, int qsize);
int dequeue(Q* p, msg* rmsg);
int enqueue(Q* p, msg nmsg);
 
void recvMsg(Q* p, msg* rmsg);
void sendMsg(Q* p, msg nmsg);

 

 

					

sem_t sem_FULL;
sem_t sem_EMP;
sem_t sem_LOCK;

 
Q msgQ;

 

void getargs_ws(int *port)
{
	FILE *fp;
	if ((fp = fopen("config-ws.txt", "r")) == NULL)
		unix_error("config-ws.txt file does not open.");
	fscanf(fp, "%d", port);
	fclose(fp);
}

 

 

 

void* consumer(void* data)

{
	msg rmsg;
	rmsg.confd =0;
	while(1){	
		printf("i'am born\n");
		recvMsg(&msgQ, &rmsg);
		printf("i get request... but...i am sleepy so i sleep 5min....\n");
		sleep(5);
		requestHandle(rmsg.confd, rmsg.time);
		Close(rmsg.confd);
	} 

}

 

 

 

 

 

int main(void)

 

{

 

	int listenfd, connfd, port, clientlen;

	struct sockaddr_in clientaddr;

	msg nmsg;

	pid_t  pid =0;

	initWatch();

	getargs_ws(&port);

	

 

 

	listenfd = Open_listenfd(port);
	pid = fork();
 	if(pid == 0){
    		printf("check\n");
    		Execve("./pushClient.cgi",NULL,NULL);
  	}else{
	initQ(&msgQ,5,5);
	printf("after init\n");
	bootQ(&msgQ);
    	printf("check2\n");

		while (1) {

			clientlen = sizeof(clientaddr);

			connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *)&clientlen);

			nmsg.confd = connfd;

			nmsg.time = getWatch();

			sendMsg(&msgQ,nmsg);

							 

		}

	 }

	return(0);

 

}

 

 

 

void initQ(Q*p, int thp, int qsize) {

	p->msgListSize = qsize;

	p->msgList = (msg*)malloc(sizeof(msg)*qsize);

	p->thrpSize = thp;

	p->ptr = (pthread_t*)malloc(sizeof(pthread_t) * (msgQ.thrpSize));

 

	p->rear = 0;

	p->front = 0;

 

	sem_init(&sem_EMP, 0, 0);

	sem_init(&sem_FULL, 0, 1);

	sem_init(&sem_LOCK, 0, 1);

}

 

void bootQ(Q*p) {

	int i = 0;

	int CkErr= FALSE;

	int thState=FALSE;

	for (i = 0; i<p->thrpSize; i++) {

		CkErr = pthread_create(&(p->ptr[i]), NULL, consumer, &thState);

		if (CkErr != FALSE) {

			printf("THREAD FALSE\n");

		}

	}

}

 

void freeQ(Q*p) {

	p->msgList = (msg*)malloc(sizeof(msg)*(p->msgListSize));

	p->ptr = (pthread_t*)malloc(sizeof(pthread_t) * (msgQ.thrpSize));

	free(p->msgList);

	free(p->ptr);

}

int dequeue(Q* p, msg* rmsg) {

	int i = 0;

	

	if (p->count != 0) {

		rmsg->confd = p->msgList[p->front].confd;

		rmsg->time = p->msgList[p->front].time;

		p->count--;

		p->front++;

		p->front %= p->msgListSize;

		return TRUE;

	}

	else

		return FALSE;

 

	return ERR;

}

 

int enqueue(Q* p, msg nmsg) {

	

	if (p->count < p->msgListSize) {

		p->msgList[p->rear].confd = nmsg.confd;

		p->msgList[p->rear].time = nmsg.time;

		p->rear++;

		p->rear %= p->msgListSize;
		p->count++;

		return TRUE;

	}

	else {

		

		return FALSE;

	}

	return ERR;

 

}

void sendMsg(Q* p, msg nmsg){

	int ck = FALSE;

	sem_wait(&sem_FULL);

	sem_wait(&sem_LOCK);

	ck = enqueue(p, nmsg);

	sem_post(&sem_LOCK);

	sem_post(&sem_EMP);

	if (ck == FALSE)

		printf("msgQ Full\n");

	else if (ck == ERR)

		printf("send ERR\n");

}

 

void recvMsg(Q* p, msg* rmsg) {

	int ck = FALSE;

	sem_wait(&sem_EMP);

	sem_wait(&sem_LOCK);

	ck = dequeue(p, rmsg);

	sem_post(&sem_LOCK);

	sem_post(&sem_FULL);

 

	if (ck == FALSE)

		printf("MSG EMP\n");

	else if (ck == ERR)

		printf("recv ERR\n");

}

 
