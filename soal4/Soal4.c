#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pthread_t tid[3];

void* proses(void *arg)
{
    pthread_t id = pthread_self();
    if(pthread_equal(id,tid[0]))
	{
        system("ps -aux | tail -n10 >> /home/bonnis/Documents/FolderProses1/SimpanProses1.txt");
        system("zip -j -q /home/bonnis/Documents/FolderProses1/KompresProses1.zip /home/bonnis/Documents/FolderProses1/SimpanProses1.txt");
        system("rm /home/bonnis/Documents/FolderProses1/SimpanProses1.txt");
        system("echo Menunggu 15 detik untuk mengekstrak kembali");
        sleep(15);
        system("unzip -q -o /home/bonnis/Documents/FolderProses1/KompresProses1.zip -d /home/bonnis/Documents/FolderProses1");
    }
    if(pthread_equal(id,tid[1]))
	{
        system("ps -aux | tail -n10 >> /home/bonnis/Documents/FolderProses2/SimpanProses2.txt");
        system("zip -j -q /home/bonnis/Documents/FolderProses2/KompresProses2.zip /home/bonnis/Documents/FolderProses2/SimpanProses2.txt");
        system("rm /home/bonnis/Documents/FolderProses2/SimpanProses2.txt");
        system("echo Menunggu 15 detik untuk mengekstrak kembali");
        sleep(15);
        system("unzip -q -o /home/bonnis/Documents/FolderProses2/KompresProses2.zip -d /home/bonnis/Documents/FolderProses2");
    }
}

int main(void)
{
	int i=0;
	int err;
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
	exit(0);
	return 0;
}