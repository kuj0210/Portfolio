#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <unistd.h>

int t1,t2,t3,t4;
pthread_barrier_t our_barrier;

void *thread1() {
  sleep(2);
  printf("Enter value for t1:  ");
  scanf("%d",&t1);
  pthread_barrier_wait(&our_barrier);
  printf("\nvalues entered by the threads are  %d %d %d %d \n",t1,t2,t3,t4);
  return NULL;
}


void *thread2() {
  sleep(4);
  
  printf("Enter value for t2:  ");
  scanf("%d",&t2);
  pthread_barrier_wait(&our_barrier);
  
  printf("\nvalues entered by the threads are  %d %d %d %d \n",t1,t2,t3,t4);
  return NULL;
}

void *thread3() {

  sleep(6);
  
  printf("Enter value for t3:  ");
  scanf("%d",&t3);
  pthread_barrier_wait(&our_barrier);
  
  printf("\nvalues entered by the threads are  %d %d %d %d \n",t1,t2,t3,t4);
  return NULL;
}

void *thread4() {
  sleep(8);
  
  printf("Enter value for t4:  ");
  scanf("%d",&t4);
  pthread_barrier_wait(&our_barrier);
  
  printf("\nvalues entered by the threads are  %d %d %d %d \n",t1,t2,t3,t4);
  return NULL;
}


int main(void) {

  pthread_t thread_id_1,thread_id_2,thread_id_3,thread_id_4;
  pthread_attr_t attr;
  int ret;
  
  pthread_attr_init(&attr);
  pthread_barrier_init(&our_barrier,NULL,4);
  ret=pthread_create(&thread_id_1,&attr,&thread1,NULL);
  if(ret!=0) {
    printf("Unable to create thread1");
  }
  ret=pthread_create(&thread_id_2, &attr,&thread2,NULL);
  
  if(ret!=0) {
    printf("Unable to create thread2");
  }
  ret=pthread_create(&thread_id_3, &attr,&thread3,NULL);
  
  if(ret!=0) {
    printf("Unable to create thread3");
  }
  ret=pthread_create(&thread_id_4, &attr,&thread4,NULL);
  
  if(ret!=0) {
    printf("Unable to create thread4");
  }
  printf("\n Created threads \n");
  pthread_join(thread_id_1,NULL);
  pthread_join(thread_id_2,NULL);
  pthread_join(thread_id_3,NULL);
  pthread_join(thread_id_4,NULL);
  pthread_barrier_destroy(&our_barrier);
  return(0);
}
