#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

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
void ShowArea();//분배된 구역을 출력, 사용자제공 X 프로그래머 오류확인용
//스레드함수
void* UTM(void* data);//상삼각화 스레드
void* BSS(void* data);//하삼각화 스레드




//전역 행렬(write , read)
float ** a;//행렬저장용 공유변수
float * b; // 백터저장용 공유변수
pthread_barrier_t our_barrier;

//단순히 읽기만 하는 변수 
int SIZE_MATRIX; // 행렬원소의 수
int SIZE_Vector;//벡터의 원소수
int *sPointer;//프로세스들의 행렬작업 시작점
int *lPointer;//프로세스들의 행렬작업 종료점 , 
int Max_Thread;
struct timeval run;



int main(int argc, char ** argv) {
	//반복, 임시저장 변수	
	int i,j,k; // 단순 반복변수
	//스레드 변수
	pthread_t* ptr =NULL;
	int CkErr =0;
	int* thId = 0;
	void* thState=0;
	//Time var
	struct timeval sp,ep;
	
	gettimeofday(&sp,NULL);
	if((argc)<5){
		printf("\n  입력토큰 ERR\n  ./hw3 <스레드수> <행렬파일> <벡터파일> <근의파일명> 순으로 입력해주세요  \n\n");
	return 0;
	}//Err

	//기본정보 read, 변수 동적할당
	Max_Thread = (int)atoi(argv[1]);
	ReadFile(argv);

	//스레드용 변수 할당
	ptr = (pthread_t*)malloc(sizeof(pthread_t) * (Max_Thread));
	thId =(int*)malloc(sizeof(int) * (Max_Thread));
	printf("성공적으로 행렬과 벡터를 읽었습니다.\n");	
	DivMatrix();
	printf("상삼각화를  실행합니다\n");
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_barrier_init(&our_barrier,NULL,Max_Thread);
	
	//상삼각화
	
		for(i=0; i<Max_Thread;i++){
		
			thId[i] = i; //한번만(처음만) id를 정의		
			CkErr =  pthread_create(&(ptr[i]), &attr, UTM, (void*)&(thId[i]));
			if(CkErr !=0){
				printf("THREAD ERR\n");
				break;
			}
		}
		for(j=0; j<Max_Thread;j++ ){
			pthread_join (ptr[j], &thState);
		}

	printf("상삼각화 완료, 후치대입 진행\n");
	for(i=0;i<SIZE_MATRIX;i++)
		InitMatrix(i);

	//후치대입
		for(i=0; i<Max_Thread;i++){	
			CkErr =  pthread_create(&(ptr[i]), &attr, BSS, (void*)&(thId[i]));
			if(CkErr !=0){
				printf("THREAD ERR\n");
				break;
			}
		}
		for(j=0; j<Max_Thread;j++ ){
			pthread_join (ptr[j], &thState);
		}
		printf("후치대입 완료\n");					

		

	gettimeofday(&ep,NULL);
	run.tv_sec = ep.tv_sec - sp.tv_sec;
	run.tv_usec = ep.tv_usec - sp.tv_usec;
	pthread_barrier_destroy(&our_barrier);
	SaveSolution(argv);
	
	//free
	free(thId);
	free(ptr);
	MyFree(); // 전역변수 free
	return 0;
}//main






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
void DivMatrix(){
	int i;
	int var1=0;
	int k=0;
	printf("\n<<행렬분할 시작합니다>>\n");
	k = SIZE_Vector / Max_Thread;
	var1 = SIZE_Vector%Max_Thread;
	var1 -= Max_Thread;
	var1 *= -1;
	for (i = 0; i < Max_Thread; i++) {
		if (i!=0) {
			sPointer[i] = lPointer[i-1];
			lPointer[i] = sPointer[i] + (k);
			if (i < Max_Thread - var1) { lPointer[i] += 1; }
		}
		else {
			sPointer[0] = 0;
			lPointer[0] = k;
			if (Max_Thread - var1!= 0) { lPointer[0] += 1; }
		}
	
	}
	printf("<<행렬분할이 완료되었습니다>>\n\n");

}




//--------------+파일입출력 , 동적할당관련 함수+--------------
void ReadFile(char** fName){
	int fd = -1; //행렬read 함수에 사용될 변수
	int fd2 = -1; //벡터 read 함수에 사용될 변수
	int i = 0;
	int j = 0;
	printf("\n<<입력받은 %s , %s 파일을 읽는중 입니다.>>\n",fName[2],fName[3]);
	// 열기
	fd = open(fName[2], O_RDONLY);
	fd2 = open(fName[3], O_RDONLY);
	if (fd < 0) printf("%s 행렬파일을 열지 못했습니다!\n", fName[2]);
	if (fd2 < 0)printf("%s 벡터파일을 열지 못했습니다!\n", fName[3]);
	
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
	//인데스 저장용 배열 할당
	sPointer=(int*)malloc(sizeof(int) * (Max_Thread)); 
	lPointer=(int*)malloc(sizeof(int) * (Max_Thread));


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
	free(sPointer);
	free(lPointer);
	free(b);
	for (i = 0; i<SIZE_MATRIX; i++) {
		free(a[i]);
 	}
	free(a);
	
}

void SaveSolution(char** fName){
	int	fd=-1;
	int i=0;

	fd= open(fName[4], O_RDWR | O_CREAT, 0644| O_APPEND);
	if (fd < 0) {
		printf("\n\n<<파일쓰기 오류, 근을 찾았으나 저장이 불가능합니다.>>\n");
	}
	write(fd, &SIZE_MATRIX, sizeof(SIZE_MATRIX));
	for (i = 0; i < SIZE_Vector; i++)
		write(fd, &(b[i]), sizeof(float));

	printf("\n<<Creat :%s !ThreadCount:%s RunTime: %d.%06lu >>\n", fName[4],fName[1],run.tv_sec,run.tv_usec);
	

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

void ShowArea(){
	int i =0;
	for (i = 0; i < Max_Thread; i++)
		printf("%d번째 Thread:<%d - %d> \n",i,sPointer[i],lPointer[i]);

}




//--------------+쓰레드 함수+--------------
void* UTM(void* data){
	//변수선언부	
	int index =*((int*)data);
	int i=0;
	int j=0;
	float var =0;
	float* buffer =  (float*)malloc(sizeof(float) * SIZE_MATRIX);
	int jLine = 0;
	float aii=0;
	pthread_barrier_wait(&our_barrier);
	for(jLine =0 ; jLine<SIZE_MATRIX; jLine++){
		pthread_barrier_wait(&our_barrier);
		Copy_MatrixLine(jLine, SIZE_Vector, a, buffer);//작업중인 한라인 복사
			//할당받은 라인순회
			for (i = sPointer[index]; i < lPointer[index]; i++) {
							if (i > (jLine)) {
								var = a[i][jLine];
						
								for (j = jLine; j < SIZE_Vector; j++)
									a[i][j] -= buffer[j] * var;
									b[i] = b[i] - b[(jLine)]/a[jLine][jLine] * var;		
								}//if (i > (*G.jLine)
					
			}//	for (i = G.sPointer[index]; i < G.lPointer[index]; i++)
			// 죽을거야ㅜ
	}
	
	free(buffer);
	pthread_exit(0);
}

void* BSS(void* data){
	//변수선언부	
	int index =*((int*)data);
	int i=0;
	int j=0;
	int jLine =0;
	float var =0;
	for(jLine =SIZE_MATRIX ; jLine>-1; jLine--){
		pthread_barrier_wait(&our_barrier);
		//하삼각화 수행부	
		for (i = sPointer[index]; i < lPointer[index]; i++) {
			if(i<(jLine)){
				var = b[(jLine)];
				b[i] = b[i] - (var * a[i][jLine]);
				a[i][jLine]=0;
			}
		}//for (i = G.sPointer[index]; i < G.lPointer[index]; i++)
		// 죽을거야ㅜ
	}
	pthread_exit(0);
}






