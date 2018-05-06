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
#define FIN -1

struct msg{
	int source;
	int target;
}typedef msg;

struct Q{
	msg* msgList;
	pthread_t* ptr;
	int rear; //size
	int max;
	int thrpSize;
}typedef Q;

//메세지 큐 관련 함수
void initQ(Q*p,int thp,int qsize);
int dequeue(Q* p,msg* rmsg);
void recv(int id,Q* p,msg* rmsg);
void send(Q* p,int s,int t);
int enqueue(Q* p,int s, int t);





//행조작관련 함수
void InitMatrix(int Line);//입력받은 라인의 첫원소로 행렬과 배열을 나눈다
int Copy_MatrixLine(int index, int size, float** Orig, float * Copy);//한행 복사
void DivMatrix();//스레드별 구역을 분배
//파일입출력, 동적할당관련 함수
void ReadFile(char** fName);//전역변수 할당 및 파일리드 함수
void MyFree();//전역변수 free함수
void SaveSolution(char** fName);
//확인용 함수
void ShowMB();//프로그래머 오류확인용 행렬/벡터 출력
//스레드함수
void* UTM(void* data);//상삼각화 스레드
void* BSS(void* data);//하삼각화 스레드


//전역 메세지 큐
Q msgQ;
//전역 행렬(write , read)
float ** a;//행렬저장용 공유변수
float * b; // 백터저장용 공유변수
//세마포 변수
sem_t sem_FULL;
sem_t sem_EMP;
sem_t sem_LOCK;
sem_t sem_NEXT;

//단순히 읽기만 하는 변수 
int SIZE_MATRIX; // 행렬원소의 수
int SIZE_Vector;//벡터의 원소수
struct timeval run;



int main(int argc, char ** argv) {
	int i,j,k; // 단순 반복변수
	//스레드
	
	int CkErr =0;
	void* thState=0;
	//Time var
	struct timeval sp,ep;
	gettimeofday(&sp,NULL);
	if((argc)<6){
		printf("\n  입력토큰 ERR\n  ./hw3 <스레드풀크기><메세지큐크기><행렬파일> <벡터파일> <근의파일명> 순으로 입력해주세요  \n\n");
	return 0;
	}//Err
	//기본정보 read, 변수 동적할당
	
	ReadFile(argv);
	initQ(&msgQ,(int)atoi(argv[1]),(int)atoi(argv[2]));
	//스레드용 변수 할당
	
	printf("성공적으로 행렬과 벡터를 읽었습니다.\n");	
	

	
	InitMatrix(0);
	sem_init(&sem_EMP,0,0);
	sem_init(&sem_FULL,0,1);
	sem_init(&sem_LOCK,0,1);
	//상삼각화	
	for(i=0; i<msgQ.thrpSize;i++){//스레드생성
		CkErr=pthread_create(&(msgQ.ptr[i]), NULL, UTM,&thState);	
		if(CkErr !=0){
				printf("THREAD ERR\n");
		}
	}
	
	for(i=0;i<SIZE_Vector;i++){
			sem_init(&sem_NEXT,0,0); // == size - i -1
		for(j=i+1;j<SIZE_Vector;j++){
			sem_wait(&sem_FULL);//가득 찼으면 대기
			sem_wait(&sem_LOCK);//누가 쓴다면 기다려라
			send(&msgQ,i,j);
			sem_post(&sem_LOCK);// 다썻다 알려라
			sem_post(&sem_EMP);// 하나 넣었다 알려라
			
		}
		for(k=0; k<SIZE_Vector-i-1;k++)
			sem_wait(&sem_NEXT);
		if(i%(int)((SIZE_Vector)*0.1)==0)		
			printf("상삼각화>--------%d/%d\n",i,SIZE_Vector);
	}
	for(i=0;i<msgQ.thrpSize;i++){
			sem_wait(&sem_FULL);//가득 찼으면 대기
			sem_wait(&sem_LOCK);//누가 쓴다면 기다려라
			send(&msgQ,FIN,FIN);
			sem_post(&sem_LOCK);// 다썻다 알려라
			sem_post(&sem_EMP);// 하나 넣었다 알려라
	}
	for(i=0; i<msgQ.thrpSize;i++){
		pthread_join((msgQ.ptr[i]),NULL);
	}
	for(i=0;i<SIZE_Vector;i++)
		InitMatrix(i);
	
//////////////////////////////////////////////


	sem_init(&sem_EMP,0,0);
	sem_init(&sem_FULL,0,1);
	sem_init(&sem_LOCK,0,1);
	for(i=0; i<msgQ.thrpSize;i++){//스레드생성
		CkErr=pthread_create(&(msgQ.ptr[i]), NULL, BSS,&thState);	
		if(CkErr !=0){
				printf("THREAD ERR\n");
		}
	}
  
	for(i=SIZE_Vector-1;i>-1;i--){
			sem_init(&sem_NEXT,0,0); // == size - i -1
		for(j=i-1;j>-1;j--){
			sem_wait(&sem_FULL);//가득 찼으면 대기
			sem_wait(&sem_LOCK);//누가 쓴다면 기다려라
			send(&msgQ,i,j);
			sem_post(&sem_LOCK);// 다썻다 알려라
			sem_post(&sem_EMP);// 하나너헝ㅆ다 알려라
			
		} 
		for(k=0; k<j;k++)
			sem_wait(&sem_NEXT);
		if(i%(int)((SIZE_Vector)*0.1)==0)		
			printf("%d/%d--------<후치대입\n",i,SIZE_Vector);
	}
	for(i=0;i<msgQ.thrpSize;i++){
			sem_wait(&sem_FULL);//가득 찼으면 대기
			sem_wait(&sem_LOCK);//누가 쓴다면 기다려라
			send(&msgQ,FIN,FIN);
			sem_post(&sem_LOCK);// 다썻다 알려라
			sem_post(&sem_EMP);// 하나너헝ㅆ다 알려라

	}
	for(i=0; i<msgQ.thrpSize;i++){
		pthread_join((msgQ.ptr[i]),NULL);
	}

	
	sem_destroy(&sem_EMP);
	sem_destroy(&sem_FULL);
	sem_destroy(&sem_LOCK);
	
		
	//시간측정
	gettimeofday(&ep,NULL);
	run.tv_sec = ep.tv_sec - sp.tv_sec;
	run.tv_usec = ep.tv_usec - sp.tv_usec;
	SaveSolution(argv);
	
	//free
	
	MyFree(); // 전역변수 free
	return 0;
}//main


//--------------+큐제어 함수+--------------
void initQ(Q*p,int thp,int qsize){
	p->msgList = (msg*)malloc(sizeof(msg)*qsize);
	p->rear = 0;
	p->max = qsize;
	p->thrpSize = thp;
	p->ptr = (pthread_t*)malloc(sizeof(pthread_t) * (msgQ.thrpSize));
}
int dequeue(Q* p,msg* rmsg){
	int i = 0;
	rmsg->source =FIN;
	rmsg->target =FIN;
	if(p->rear>0){
		rmsg->source =p->msgList[0].source;
		rmsg->target =p->msgList[0].target;
		for(i=0;i<p->rear;i++){
			if(i+1==p->rear)break;
			p->msgList[i].source=p->msgList[i+1].source;
			p->msgList[i].target=p->msgList[i+1].target;
		}
		p->rear--;
		return TRUE;
	}
	else 
		return FALSE;
}

int enqueue(Q* p,int s, int t){
	if(p->rear < p->max){
		p->msgList[p->rear].source = s;
		p->msgList[p->rear].target = t;
		p->rear++;
		return TRUE;
	}
	else{
		printf("푸쉬오류\n");
		return FALSE;
	}
	printf("푸쉬조건 종료 에러\n");
	
}
void send(Q* p,int s,int t){
	int ck=FALSE;
	ck = enqueue(p,s,t);
	if(ck==FALSE)
		printf("삽입오류\n");
}

void recv(int id,Q* p,msg* rmsg){
	int ck=FALSE;	
		ck = dequeue(p,rmsg);
		if(ck==FALSE)
			printf("수령오류\n");	
}


//--------------+행조작관련 함수+--------------
void InitMatrix(int Line){
	float aii = 0;
	int i=0;
	aii = a[Line][Line];
	for(i=0;i<SIZE_MATRIX;i++)
		a[Line][i]/=aii;
	b[Line]/=aii;
}

int Copy_MatrixLine(int index, int size, float** Orig, float * Copy) {
	int i = 0;
	float var =Orig[index][index];
	for (i = 0; i < size; i++) {
		Copy[i] = Orig[index][i]/var;
	}
	return 0;
}

//--------------+파일입출력 , 동적할당관련 함수+--------------
void ReadFile(char** fName){
	int fd = -1; //행렬read 함수에 사용될 변수
	int fd2 = -1; //벡터 read 함수에 사용될 변수
	int i = 0;
	int j = 0;
	printf("\n<<입력받은 %s , %s 파일을 읽는중 입니다.>>\n",fName[3],fName[4]);
	// 열기
	fd = open(fName[3], O_RDONLY);
	fd2 = open(fName[4], O_RDONLY);
	if (fd < 0) printf("%s 행렬파일을 열지 못했습니다!\n", fName[3]);
	if (fd2 < 0)printf("%s 벡터파일을 열지 못했습니다!\n", fName[4]);
	
	read(fd, &SIZE_MATRIX, sizeof(int));
	read(fd2, &SIZE_Vector, sizeof(int));
	if (SIZE_MATRIX < 0 || SIZE_Vector<0)
		printf("매트릭스 또는 벡터의 크기를 읽지 못하였습니다!\n");
	else if (SIZE_Vector != SIZE_MATRIX)
		printf("매트릭스와 벡터의 크기가 달라 가우스 소거법을 할 수 없습니다\n");
	//행렬,벡터 동적할당
	
	b=(float*)malloc(sizeof(float) *SIZE_MATRIX);;
	a=(float**)malloc(sizeof(float*) *SIZE_MATRIX);
	for (i = 0; i<SIZE_MATRIX; i++) {
	 	a[i] = (float*)malloc(sizeof(float) * SIZE_MATRIX);
	 }
	


	  //행렬/벡터 읽어오기
	for (i = 0; i < SIZE_MATRIX; i++) {
		read(fd2, &(b[i]), sizeof(float));// 벡터 파일에서 벡터를 읽음
		for (j = 0; j<SIZE_MATRIX; j++) {//행렬 파일에서 행렬을 읽어옮
		   read(fd, &(a[i][j]), sizeof(float));
  		 }
 	}
	printf("<<파일을 닫습니다.>>\n\n");
	close(fd);
	close(fd2);

}
void MyFree(){
	int i =0;
	free(msgQ.msgList);
	free(msgQ.ptr);
	free(b);
	for (i = 0; i<SIZE_MATRIX; i++) {
		free(a[i]);
 	}
	free(a);
	
}

void SaveSolution(char** fName){
	int	fd=-1;
	int i=0;

	fd= open(fName[5], O_RDWR | O_CREAT, 0644| O_APPEND);
	if (fd < 0) {
		printf("\n\n<<파일쓰기 오류, 근을 찾았으나 저장이 불가능합니다.>>\n");
	}
	write(fd, &SIZE_MATRIX, sizeof(SIZE_MATRIX));
	for (i = 0; i < SIZE_Vector; i++)
		write(fd, &(b[i]), sizeof(float));

	printf("\n<<Creat :%s !ThreadCount:%s RunTime: %d.%06lu >>\n", fName[5],fName[1],run.tv_sec,run.tv_usec);
	

}




//--------------+확인용 함수+--------------
void ShowMB(){
	int p =0;
	int q= 0;
	printf("\n<<통합행렬입니다>>\n");
	for(p=0; p< SIZE_MATRIX;p++){
		for(q=0; q< SIZE_MATRIX;q++)
				printf("<%f> ",a[p][q]);
		printf(" |<%f>\n",b[p]);
	}
	printf("\n");
	printf("\n");
}


//--------------+쓰레드 함수+--------------
void* UTM(void* data){
	//메세지관련변수선언부
	msg mine;
	int id=*((int*)data);
	//변수선언부
	int i=0;
	int j=0;
	float var =0;
	float* buffer =  (float*)malloc(sizeof(float) * SIZE_MATRIX);

	while(1){
		sem_wait(&sem_EMP);//비었다면 대기
	  	sem_wait(&sem_LOCK);//누가쓰고있다면
		recv(id,&msgQ,&mine);
		sem_post(&sem_LOCK);//다썻다 알려라
		sem_post(&sem_FULL);//하나썻다 알려라
		if(mine.source == FIN) break;
		var = a[mine.target][mine.source];
		Copy_MatrixLine(mine.source, SIZE_Vector, a, buffer);//소스행 복사
		for(i=mine.source;i<SIZE_Vector;i++){
			a[mine.target][i] -= buffer[i] * var;			
		}
		b[mine.target]-=b[(mine.source)]/a[mine.source][mine.source] * var;
		sem_post(&sem_NEXT);
	}
	free(buffer);
	pthread_exit(0);
}

void* BSS(void* data){
	//메세지관련변수선언부
	msg mine;
	int id=*((int*)data);
	//변수선언부
	int i=0;
	int j=0;
	float var =0;
	
	while(1){
		sem_wait(&sem_EMP);//비었다면 대기
	  	sem_wait(&sem_LOCK);//누가쓰고있다면
		recv(id,&msgQ,&mine);
		sem_post(&sem_LOCK);//다썻다 알려라
		sem_post(&sem_FULL);//하나썻다 알려라
		if(mine.source == FIN) break;
		

		var = b[(mine.source)];
		b[mine.target] = b[mine.target] - (var * a[mine.target][mine.source]);
		a[mine.target][mine.source]=0;
		sem_post(&sem_NEXT);
		
	}
	
	pthread_exit(0);
}






