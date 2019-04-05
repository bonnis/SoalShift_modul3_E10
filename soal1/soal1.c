#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 100

void * faktorial( void *ptr );
int status=1;

typedef struct{
  int n;
  int hasil;
}number;

int main()
{
  int input, temp, x, y=-1;

  number angka[MAX];

  //input 
  while(1){
    scanf("%d", &x);
    y += 1;
    if(x < 0){
      break;
    }
    else if(x >=0){
      angka[y].n = x;
    }
  }

  pthread_t thread[y];

  for(int i =0; i< y; i++){
    for(int j =i+1; j<y; j++){
      if(angka[i].n < angka [j].n){
        temp = angka[i].n;
        angka[i].n = angka[j].n;
        angka[j].n = temp;
      }
    }
  }

//membuat thread sebanyak input
  for (int i =0; i<y; i++){
    pthread_create(&thread[i], NULL, faktorial, &angka[i]);
  }

  //join thread
  for(int i=0; i<y; i++){
    pthread_join(thread[i], NULL);
  }

  exit(EXIT_SUCCESS);
}

void * faktorial (void * ptr){
  
  while(status == 0){
  
  }
  status = 0;
  number *N = (number*) ptr;
  int fact = 1;

  for (int i=1; i<=N->n; i++){
    fact *= i;
  }

  N->hasil = fact;
  printf("%d! = %d\n", N->n, fact);
  status = 1;
}
