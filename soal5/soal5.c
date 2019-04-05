#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>   //_getch
#include <termios.h>  //_getch

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


pthread_t tid[7];
char nama[75];
int scene=1,exitsignal=0;
int health=300,hunger=200,hygiene=100,foodstock=0,bathcooldown=0;//standby variables
int ehealth=0;//battle variables
int *sellstock;//shop variables

void* proses(void *arg)
{
    pthread_t id = pthread_self();
    if(pthread_equal(id,tid[0]))
	{
        //Scene updater
        while(!exitsignal)
        {
            if (scene==1)
            {
                printf("%s's Status\n",nama);
                printf("Health : %d\n",health);
                printf("Hunger : %d\n",hunger);
                printf("Hygiene : %d\n",hygiene);
                printf("Food left : %d\n",foodstock);
                if(bathcooldown>0) printf("Bath will be ready in %ds\n",bathcooldown);
                else printf("Bath is ready\n");
                printf("Choices\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
            }
            else if (scene==2)
            {
                printf("%s's Health : %d\n",nama,health);
                printf("Enemy's Health : %d\n",ehealth);
                printf("Choices\n1. Attack\n2. Run\n");
            }
            else if (scene==3)
            {
                printf("Shop food stock : %d\n",*sellstock);
                printf("Your food stock : %d\n",foodstock);
                printf("Choices\n1. Buy\n2. Back\n");
            }
            sleep(1);
            system("clear");
            
        }
    }
    if(pthread_equal(id,tid[1])) //hunger counter
	{
        while(!exitsignal){
            if(scene==2) continue;
            sleep(10);
            if(scene!=2) hunger-=5;
            if(hunger<=0) exitsignal=1;
        }
    }
    if(pthread_equal(id,tid[2])) //hygiene counter
	{
        while(!exitsignal){
            if(scene==2) continue;
            sleep(30);
            if(scene!=2) hygiene-=10;
            if(hygiene<=0) exitsignal=1;
        }
    }
    if(pthread_equal(id,tid[3])) //health counter
	{
        while(!exitsignal){
            if(scene==2) continue;
            sleep(10);
            if(scene!=2) health+=5;
        }
    }
    if(pthread_equal(id,tid[4])) //bathcooldown counter
	{
        while(!exitsignal){
            if(bathcooldown>0)
            {
                sleep(1);
                bathcooldown--;
            }
        }       
    }
    if(pthread_equal(id,tid[5])) //scene organizer
	{
        while(!exitsignal){
            int inputkey;
            if(scene==1)
            {
                inputkey=getch();
                if(inputkey=='1')
                {
                    if(foodstock>0)
                    {
                        hunger+=15;
                        if(hunger>200)hunger=200;
                        foodstock--;
                    }
                }
                else if(inputkey=='2')
                {
                    if(bathcooldown==0)
                    {
                        hygiene+=30;
                        bathcooldown=20;
                    }
                }
                else if(inputkey=='3')
                {
                    ehealth=100;
                    scene=2;
                }
                else if(inputkey=='4')
                {
                    scene=3;
                }
                else if(inputkey=='5')
                {
                    exitsignal=1;
                }
                else continue;
            }
            else if(scene==2)
            {
                inputkey=getch();
                if(inputkey=='1')
                {
                    ehealth-=20;
                    if(ehealth>0)
                    {
                        health-=20;
                    }
                    else scene=1;
                }
                else if(inputkey=='2')
                {
                    scene=1;
                }
            }
            else if(scene==3)
            {
                inputkey=getch();
                if(inputkey=='1')
                {
                    if(*sellstock>0)
                    {
                        *sellstock=*sellstock-1;
                        foodstock++;
                    }
                }
                else if(inputkey=='2')
                {
                    scene=1;
                }
            }
        }
    }
}

int main (void)
{
	int i=0;
	int err;
    int key = 9731;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    sellstock = shmat(shmid, NULL, 0);
    *sellstock=0;

    printf("Masukkan nama monster mu >");
    fgets(nama,100,stdin);
    nama[strlen(nama)-1]='\0';
	while(i<6)
	{
		err=pthread_create(&(tid[i]),NULL,&proses,NULL);
		if(err!=0)
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		i++;
	}
    
	pthread_join(tid[0],NULL);
	pthread_join(tid[5],NULL);
    system("clear");
    printf("Anda kalah!\n");
    *sellstock=-1;
    sleep(5);
    shmdt(sellstock);
    shmctl(shmid, IPC_RMID, NULL);
	exit(0);
	return 0;
}