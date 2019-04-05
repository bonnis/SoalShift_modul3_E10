#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //library thread
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

pthread_t thread1, thread2;  //thread 1 : agmal, thread2 : iraj
int flagA=0, flagI=0, berhentiI=0, berhentiA=0, z;


typedef struct{
  int agmal, iraj;
}fitur;



void * fungsi (void* ptr){
  pthread_t id = pthread_self();
  fitur *stat = (fitur*) ptr;

 
  if(z==1){
    if(berhentiI == 1){
      sleep(10);
      berhentiI=0;
    }
    else{
      stat->iraj -= 20;
      flagI++;

      if(flagI == 3){
        berhentiA =1;
        printf("Agmal Ayo Bangun disabled 10 s\n");
        flagI = 0;
      }
    }
  }

else if(z==0){
    if(berhentiA == 1){
      sleep(10);
      berhentiI=0;
    }
    else{
      stat->agmal += 15;
      flagA++;
      if(flagA == 3){
        berhentiI =1;
        printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
        flagA = 0;
      }
    }
  }
}

int main()
{
  fitur status;
  int input;
  status.agmal = 0;
  status.iraj = 100;
  printf("Fitur-fitur :\n");
  printf("Tekan 1 untuk mengaktifkan fitur 'Agmal Ayo Bangun'\n");
  printf("Tekan 2 untuk mengaktifkan fitur 'Iraj Ayo Tidur\n'");
  printf("Tekan 3 untuk mengaktifkan fitur 'Menampilkan All status'\n");
    while(1){
      scanf("%d", &input);

      if(input == 1){
          z =0;
          pthread_create(&thread1, NULL, fungsi, &status);
      }
      else if(input ==2){
          z=1;
   printf("masuk sini\n");
          pthread_create(&thread2, NULL, fungsi, &status);
      }
    
      else if(input == 3){
        printf("Agmal WakeUp_status %d\nIraj Spirit_status %d\n", status.agmal, status.iraj);
      }

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 
     if((status.agmal>=100)){
        printf("Agmal Terbangun, mereka bangun pagi dan barolahraga\n");
        break;
      }
     if(status.iraj <= 0){

        printf("Iraj ikut tidur, dan bangun kesiangan bersama agmal\n"); 
        break;
      }
   }
    exit(EXIT_SUCCESS);
}


	int i;
	printf("Masukkan nilai T : ");
	scanf("%d", &T);
	printf("Masukkan nilai N : ");
	scanf("%d", &N);
	for (i=0;i<T;i++)
	{
		pthread_t tid[i];
		pthread_create(&(tid[i]),NULL,fungsi,NULL);
		pthread_join(tid[i],NULL);
	}
 
    	return 0;
}
