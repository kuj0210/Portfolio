#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int Copy_MatrixLine(int index, int size, float** Orig, float * Copy);

 
int main(int* argc, char ** argv) {
 //Matrix,Vector Var
 int SIZE_MATRIX = -1;
 int SIZE_Vector = -1;
 float ** a = NULL;// Matrinx
 float * b = NULL; // Vetor
 float * c = NULL; // BuffVetor
 float d = 0;      // Buff
 
 //Time var
 clock_t Start_Point,End_Point;
 float Time_Load =0;
 float Time_Job =0;
 float Time_Save =0;

 //for Var
 int i = 0; //상삼각형 형태로 변환중인 행
 int j = 0;// 변환을 위해 현재 값을 끌어다 쓰고있는 행
 int k = 0;// 단순 반복을 위핸 변수

 // File open Var
 int fd = -1; //행렬read 함수에 사용될 변수
 int fd2 = -1; //벡터 read 함수에 사용될 변수
 char* Save = NULL; // Save Vector Var 


 // File Open
 fd = open(argv[1], O_RDONLY);
 fd2 = open(argv[2], O_RDONLY);
 if (fd<0) printf("%s 행렬파일을 열지 못했습니다!\n",argv[1]);
 if (fd2<0)printf("%s 벡터파일을 열지 못했습니다!\n",argv[2]);



 read(fd, &SIZE_MATRIX, sizeof(int));
 read(fd2, &SIZE_Vector, sizeof(int));
 if (SIZE_MATRIX<0)
  printf("매트릭스 크기를 읽지 못하였습니다!\n");
 else if (SIZE_Vector != SIZE_MATRIX)
  printf("매트릭스와 벡터의 크기가 달라 가우스 소거법을 할 수 없습니다\n");

 


 //2차원 행렬 동적할당
 a = (float**)malloc(sizeof(float*) * SIZE_MATRIX);
 for (i = 0; i<SIZE_MATRIX; i++) {
  a[i] = (float*)malloc(sizeof(float) * SIZE_MATRIX);
 }
 // 벡터동적할
 b = (float*)malloc(sizeof(float) * SIZE_MATRIX);
 c = (float*)malloc(sizeof(float) * SIZE_MATRIX);

 Start_Point = clock();
 End_Point = clock();
 //행렬/벡터 읽어오기
 for (i = 0; i < SIZE_MATRIX; i++) {
  read(fd2, &(b[i]), sizeof(float));// 벡터 파일에서 벡터를 읽음
 
  for (j = 0; j<SIZE_MATRIX; j++) {//행렬 파일에서 행렬을 읽어옮
   read(fd, &(a[i][j]), sizeof(float));
  
  }
 }

 End_Point = clock();
 Time_Load = (End_Point - Start_Point)/1000;
 close(fd);
 close(fd2);
 
 

 // job
 Start_Point = clock();
 for (i = 0; i < SIZE_MATRIX; i++) {
  if (i == 0) {
   d = a[0][0];
   for (j = 0; j < SIZE_MATRIX; j++) {
    a[0][j] = a[0][j] / d;
   }
   b[0] = b[0] / d;
  }
  else {
   for (j = 0; j < i; j++) {
    Copy_MatrixLine(j, SIZE_MATRIX, a, c); // 매트릭스의 한 행 복사
    d = b[j];
    for (k = 0; k < SIZE_MATRIX; k++) {
     c[k] = c[k] * a[i][j];
    }
    d = b[j] * a[i][j];
    // a[][]와 b의 i번째행 복사 및 배수값 완료
    //복사한 행을 기준행에 빼줌
    for (k = 0; k < SIZE_MATRIX; k++) {
     a[i][k] -= c[k];
    }
    b[i] = b[i] - d;
    //값을 빼줌
   }
   if (a[i][j] != 0) {
    d = a[i][j];
    for (k = 0; k < SIZE_MATRIX; k++) {
     a[i][k] /= d;
    }
    b[i] /= d;
   }
   else {
    printf("행조작으로 같은 값으로 변환되는 행이있습니다.\n");
    return 0;
   }
  }

 } // 상삼각형 형태로 행조작하는 곳!

 for (i = SIZE_MATRIX - 1; i > 0; i--) {
  d = b[i];
  for (j = 0; j < i; j++) {
   b[j] -= a[j][i] * d;
   a[j][i] = 0;
  }

 }

 End_Point = clock();
 Time_Job = (End_Point - Start_Point)/1000;


 // file open for write
 fd = -1;
 fd = open(argv[3], O_RDWR| O_CREAT,0644|O_APPEND);
 if(fd<0){
	printf("파일쓰기 오류, 근을 찾았으나 저장이 불가능합니다.\n");
	return 0;
 }

 Start_Point = clock();

 
 //save
 
 write(fd,&SIZE_MATRIX,sizeof(SIZE_MATRIX));
 for(i=0;i<SIZE_MATRIX;i++)
  write(fd,&(b[i]),sizeof(float));


 End_Point = clock();
 Time_Save = (End_Point - Start_Point)/1000;


 
 printf("Creat :%s ! LoadTime: %f / jobTime: %f / SaveTime : %f\n",argv[3],Time_Load,Time_Job,Time_Save);
 
//Free memory	
 for (i = 0; i<SIZE_MATRIX; i++) {
  free(a[i]);
 }
 free(a);
 free(b);
 free(c);

 


 return 0;
}

 

 

 

 

int Copy_MatrixLine(int index, int size, float** Orig, float * Copy) {

 int i = 0;
 for (i = 0; i < size; i++)
  Copy[i] = Orig[index][i];

 return 0;

}
 

