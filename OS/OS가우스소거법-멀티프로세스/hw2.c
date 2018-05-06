#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

int Copy_MatrixLine(int index, int size, float* Orig, float * Copy);


typedef struct {
	float * a;//행렬저장용 공유변수
	float * b; // 백터저장용 공유변수
	float * c; // 행렬의 한행을 저장할 변수
	int SIZE_MATRIX; // 행렬원소의 수
	int SIZE_Vector;//벡터의 원소수
	int *sPointer;//프로세스들의 행렬작업 시작점
	int *lPointer;//프로세스들의 행렬작업 종료점
	int *pPLine;//부모가 자식에게 메세지를 보냄
	int *cPLine;//자식이 부모에게 메세지를 보냄
	int *jLine;// 가우스 소거법 시 복사해서 사용할 행을 저장
} Gaus;


int main(int* argc, char ** argv) {
	//Matrix,Vector Var
	float d = 0; //벡터 및 행렬 원소를 저장할 buff
	int pSize = atoi(argv[1]); //입력받은 프로세스
	pid_t pid = -1; //자식이 잘생겼는지 확인할 변수
	int pPid = (int)getpid();//부모 id
	int index = 0;//자식 id

	//proces var
	int shm_fd;//공유변수 오류 체크용 변수
	Gaus G;//작업 시 필요한 데이터들이 모인 구조체(공유메모리들 및 행관련 기본정보)

	//Time var
	clock_t Start_Point, End_Point;//시간확인용
	double TIME = 0;//시간확인용

	//for Var
	int i = 0; //상삼각형 형태로 변환중인 행
	int j = 0;// 변환을 위해 현재 값을 끌어다 쓰고있는 행
	int k = 0;// 단순 반복을 위핸 변수 or 반복문 내에서 반복을 하거나 int값을 임시 저장하는 변수

	// File open Var
	int fd = -1; //행렬read 함수에 사용될 변수
	int fd2 = -1; //벡터 read 함수에 사용될 변수

	//초기화
	G.SIZE_MATRIX = 0;
	G.SIZE_Vector = 0;


	// File Open
	fd = open(argv[2], O_RDONLY);
	fd2 = open(argv[3], O_RDONLY);
	if (fd < 0) printf("%s 행렬파일을 열지 못했습니다!\n", argv[2]);
	if (fd2 < 0)printf("%s 벡터파일을 열지 못했습니다!\n", argv[3]);
	read(fd, &G.SIZE_MATRIX, sizeof(int));
	read(fd2, &G.SIZE_Vector, sizeof(int));
	if (G.SIZE_MATRIX < 0 || G.SIZE_Vector<0)
		printf("매트릭스 또는 벡터의 크기를 읽지 못하였습니다!\n");
	else if (G.SIZE_Vector != G.SIZE_MATRIX)
		printf("매트릭스와 벡터의 크기가 달라 가우스 소거법을 할 수 없습니다\n");
	G.SIZE_MATRIX *= G.SIZE_MATRIX;


	//Matirx 
	shm_fd = -1;
	shm_fd = shm_open("Matrix", O_CREAT | O_RDWR, 0777);
	if (shm_fd == -1) { printf("SHM EORR\n"); }
	ftruncate(shm_fd, G.SIZE_MATRIX * sizeof(float));
	G.a = (float *)mmap(0, G.SIZE_MATRIX * sizeof(float), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

	//Vecor
	shm_fd = -1;
	shm_fd = shm_open("Vector", O_CREAT | O_RDWR, 0777);
	if (shm_fd == -1) { printf("SHM EORR\n"); }
	ftruncate(shm_fd, G.SIZE_Vector * sizeof(float));
	G.b = (float *)mmap(0, G.SIZE_Vector * sizeof(float), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

	//sPointer
	shm_fd = -1;
	shm_fd = shm_open("sPointer", O_CREAT | O_RDWR, 0777);
	if (shm_fd == -1) { printf("SHM EORR\n"); }
	ftruncate(shm_fd, sizeof(int)* pSize + 1);
	G.sPointer = (int *)mmap(0, sizeof(int)* pSize + 1, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

	//lPointer
	shm_fd = -1;
	shm_fd = shm_open("lPointer", O_CREAT | O_RDWR, 0777);
	if (shm_fd == -1) { printf("SHM EORR\n"); }
	ftruncate(shm_fd, sizeof(int)* (pSize + 1));
	G.lPointer = (int *)mmap(0, sizeof(int)* pSize + 1, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

	//cPLine
	shm_fd = -1;
	shm_fd = shm_open("cPLine", O_CREAT | O_RDWR, 0777);
	if (shm_fd == -1) { printf("SHM EORR\n"); }
	ftruncate(shm_fd, sizeof(int)* (pSize + 1));
	G.cPLine = (int *)mmap(0, sizeof(int)* pSize + 1, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

	//pPLine
	shm_fd = -1;
	shm_fd = shm_open("pPLine", O_CREAT | O_RDWR, 0777);
	if (shm_fd == -1) { printf("SHM EORR\n"); }
	ftruncate(shm_fd, sizeof(int)* (pSize + 1));
	G.pPLine = (int *)mmap(0, sizeof(int)* pSize + 1, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

	//jLine
	shm_fd = -1;
	shm_fd = shm_open("jLine", O_CREAT | O_RDWR, 0777);
	if (shm_fd == -1) { printf("SHM EORR\n"); }
	ftruncate(shm_fd, sizeof(int));
	G.jLine = (int *)mmap(0, sizeof(int), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

	G.c = (float*)malloc(sizeof(float) * G.SIZE_Vector);


	//행렬/벡터 읽어오기
	for (i = 0; i < G.SIZE_Vector; i++) {
		read(fd2, &(G.b[i]), sizeof(float));// 벡터 파일에서 벡터를 읽음
	}
	for (i = 0; i < G.SIZE_MATRIX; i++) {//행렬 파일에서 행렬을 읽어옮
		read(fd, &(G.a[i]), sizeof(float));
	}

	close(fd);
	close(fd2);


	k = G.SIZE_Vector / pSize; //
	j = G.SIZE_Vector%pSize;
	j -= pSize;
	j *= -1;
	*(G.jLine) = 0;


	//Divide Matrix
	for (i = 0; i < pSize + 1; i++) {
		if (i) {
			G.sPointer[i + 1] = G.lPointer[i];
			G.lPointer[i + 1] = G.sPointer[i + 1] + (k);
			if (i < pSize - j) { G.lPointer[i + 1] += 1; }
		}
		else {
			G.sPointer[1] = 0;
			G.lPointer[1] = k;
			if (pSize - j != 0) { G.lPointer[i + 1] += 1; }
		}
		G.cPLine[i] = 0;
		G.pPLine[i] = 1;
	}

	time(&Start_Point);
	G.pPLine[0] = 10;
	G.cPLine[0] = 10;
	d = G.a[0];
	for (i = 0; i < G.SIZE_Vector; i++) {
		G.a[i] /= d;
	}
	G.b[0] /= d;




	//fork!!
	for (i = 0; i < pSize; i++) {
		if (pPid == getpid()) { // 부모만 자식을 생성
			index = i + 1;
			pid = fork();
			if (pid < 0) { printf("%d Child Err\n", i);  break; }
			pid = -1;
		}

	}



	//부모영역			
	if (pPid == (int)getpid()) {
		printf("상삼각화를 실행중입니다!\n");
		//상삼각화
		while (*(G.jLine) < G.SIZE_Vector-1) {
			for (i = 1; i < pSize + 1; i++) {
				if (G.cPLine[i] != 1)
					break;
			}//for i pipe check
			if (i == pSize + 1) {//자식이 일다했다면,
				G.pPLine[0] = 0;//Stop!
				if( (*G.jLine)%(G.SIZE_Vector/5)==0 )
					printf("상삼각화 진행도::%d / %d \n",(*G.jLine),G.SIZE_Vector);
				*(G.jLine) += 1;//작업줄변경
				//작업된 행렬 최적화(대각라인을 1로 변경)
				d = G.a[G.SIZE_Vector*(*G.jLine) + (*G.jLine)];
				G.b[(*G.jLine)] /= d;
				for (i = 0; i < G.SIZE_Vector; i++) {//pipe read
					if (i < pSize + 1 && i != 0) { G.cPLine[i] = 0; }//자식 메세지라인 비워줌
					G.a[G.SIZE_Vector*(*G.jLine) + i] /= d;
				}
				for (j = 1; j < pSize + 1; j++) { G.pPLine[j] = 1; }//pipe write
				G.pPLine[0] = 10;//pipe write
			}//if i=size
		}//while(*(G.jLine) < G.SIZE_Vector) 상삼각적업 끝
		


		
		G.pPLine[0] = 0;//초기화	
		*(G.jLine) = G.SIZE_Vector-1;//초기화


		while(1){
	
			for (i = 1; i < pSize + 1; i++) {
				if (G.cPLine[i] != -1)
					break;
			}//for i pipe check
			if (i == pSize + 1) //자식이 일다했다면,
				break;

		}//while(1)pipe read 
		printf("후치대입이 실행됩니다\n");
		
		for (j = 1; j < pSize + 1; j++) { G.cPLine[j] = 0; }//pipe read
		for (j = 1; j < pSize + 1; j++) { G.pPLine[j] = 1; }//pipe write
		G.pPLine[0] = 20;//후치대입해
	
		//부모::후치대입
		while (*(G.jLine) > -1) {
			for (i = 1; i < pSize + 1; i++) {
					if (G.cPLine[i] != 1){break;}	
			}//for i pipe check
			
			if (i == pSize + 1) {//자식이 일다하면
				G.pPLine[0] = 0;//stop! - pipe write
				if( (*G.jLine)%(G.SIZE_Vector/5)==0 || (*G.jLine)== G.SIZE_Vector-1)
					printf("후치대입 진행도:: %d / %d \n",(*G.jLine),G.SIZE_Vector);
				*(G.jLine) -= 1; // 작업라인 옮기고
				for (j = 0; j < pSize + 1; j++) { G.cPLine[j] = 0; } //pipe read
				for (j = 1; j < pSize + 1; j++) { G.pPLine[j] = 1; } //pipe write
				
				G.pPLine[0] = 20;//pipe write
				

			}//if i=size



		}


		while(1){
	
			for (i = 1; i < pSize + 1; i++) {
				if (G.cPLine[i] != -1)
					break;
			}//for i pipe check
			if (i == pSize + 1) //자식이 일다했다면,
				break;

		}//while(1)pipe read 

		// waite

		// file open for write
		fd = -1;
		fd = open(argv[4], O_RDWR | O_CREAT, 0644 | O_APPEND);
		if (fd < 0) {
			printf("파일쓰기 오류, 근을 찾았으나 저장이 불가능합니다.\n");
			return 0;
		}

		//save
		write(fd, &G.SIZE_Vector, sizeof(G.SIZE_Vector));
		for (i = 0; i < G.SIZE_Vector; i++)
			write(fd, &(G.b[i]), sizeof(float));

		
		time(&End_Point);
		TIME = difftime(End_Point,Start_Point);
		printf("\n");
		printf("Creat :%s !Porcess:%s jobTime: %f(초) \n", argv[4],argv[1] ,TIME);



		munmap((void*)G.a, G.SIZE_MATRIX);
		shm_unlink("Matrix");
		munmap((void*)G.b, G.SIZE_Vector);
		shm_unlink("Vector");
		munmap((void*)G.sPointer, sizeof(int)* (pSize + 1));
		shm_unlink("sPointer");
		munmap((void*)G.lPointer, sizeof(int)* (pSize + 1));
		shm_unlink("lPointer");
		munmap((void*)G.cPLine, sizeof(int)* (pSize + 1));
		shm_unlink("cPLine");
		munmap((void*)G.pPLine, sizeof(int)* (pSize + 1));
		shm_unlink("pPLine");
		munmap((void*)G.jLine, sizeof(int));
		shm_unlink("jLine");
		free(G.c);
		
		exit(0);
		return 0;
	}//if (pPid == (int)getpid())

	else if ((int)getpid() != pPid) {
	
		while (*(G.jLine) > -1) {
			if (*G.jLine < 0) break;
			// 자식::상삼각화
			while (*(G.jLine) < G.SIZE_Vector && G.pPLine[0] == 10) {//pipe read
				if((*G.jLine)==G.SIZE_Vector){break;}
				if (G.pPLine[index] == 1) {
					G.pPLine[index] = 0;//pipe read
				
					Copy_MatrixLine((*G.jLine), G.SIZE_Vector, G.a, G.c);//작업중인 한라인 복사
					//할당받은 라인순회
					for (i = G.sPointer[index]; i < G.lPointer[index]; i++) {
						if (i > (*G.jLine)) {
							d = G.a[i*G.SIZE_Vector + (*G.jLine)];
							//printf("d:%lf\n",d);
							for (j = (*G.jLine); j < G.SIZE_Vector; j++)
								G.a[G.SIZE_Vector*i + j] -= G.c[j] * d;
							G.b[i] = G.b[i] - G.b[(*G.jLine)] * d;		
						}//if (i > (*G.jLine)
					}//	for (i = G.sPointer[index]; i < G.lPointer[index]; i++)
					G.cPLine[0] = 0;
					G.cPLine[index] = 1;//pipe write
				}//if (G.pPLine[index] == 1)
			}//while (*(G.jLine) < G.SIZE_Vector + 1 && G.pPLine[0] == 10) 상삼각화 끝
			
			if(G.cPLine[0]==0)
				G.cPLine[index] = -1;////pipe write 후치대입이 끝남을 알림

			

			//자식::후치대입부 
			while (*(G.jLine) > -1 && G.pPLine[0] == 20) {
				if (G.pPLine[index] == 1) {
					G.pPLine[index] = 0;
					//자기영역순회
	
					if ((*G.jLine) < 0) break;
					for (i = G.sPointer[index]; i < G.lPointer[index]; i++) {
						if(i<(*G.jLine)){
							d = G.b[(*G.jLine)];
							G.b[i] = G.b[i] - (d * G.a[(i)*G.SIZE_Vector + (*G.jLine)]);
							G.a[(i)*G.SIZE_Vector + (*G.jLine)]=0;
						}
					}//for (i = G.sPointer[index]; i < G.lPointer[index]; i++)
					G.cPLine[0] = 100;
					G.cPLine[index] = 1;
				}//if(G.pPLine[index]==1)
			}//while(*(G.jLine) >-1 && G.pPLine[0]==20)  후치대임루프	
		}//while (*(G.jLine) > -1) 무한루프
		G.cPLine[index] = -1;
	 exit(0);
	}//else if ((int)getpid() != pPid)
	exit(0);
	return 0;
}







int Copy_MatrixLine(int index, int size, float* Orig, float * Copy) {

	int i = 0;
	for (i = 0; i < size; i++) {
		Copy[i] = Orig[index*size + i];
	}

	return 0;

}


