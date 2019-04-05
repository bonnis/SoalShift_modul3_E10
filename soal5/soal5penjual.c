#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include <termios.h>  //_getch

pthread_t tid[2];
int *sellstock,exitsignal=0;

char getch(){

    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
 }

void* proses(void* arg)
{
    char inputkey;
    pthread_t id = pthread_self();
    if(pthread_equal(id,tid[0]))
	{
        while(!exitsignal)
        {
            printf("Shop\n");
            printf("Food stock : %d\n", *sellstock);
            printf("Choices\n1. Restock\n2. Exit\n");
            if(*sellstock<0) exitsignal=1;
            sleep(1);
            system("clear");
        }
    }
    else if(pthread_equal(id,tid[1]))
    {
        while(!exitsignal&&(*sellstock>=0))
        {
            inputkey=getch();
            if(inputkey=='1')
            {
                if(!exitsignal) *sellstock=*sellstock+5;
            }
            else if(inputkey=='2')
            {
                exitsignal=1;
            }
        }

    }
}

void main()
{
    key_t key = 9731;
    int err,i=0;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    sellstock = shmat(shmid, NULL, 0);
        
    while(i<2)
	{
		err=pthread_create(&(tid[i]),NULL,&proses,NULL);
		if(err!=0)
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		i++;
	}
    pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

    shmdt(sellstock);
    shmctl(shmid, IPC_RMID, NULL);
}