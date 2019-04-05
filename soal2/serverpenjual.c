#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#define PORT 8080

pthread_t thread1, thread2;

void* jual(void *arg){
  key_t key = 1234;
  int *stock;

  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  stock = shmat(shmid, NULL, 0);
  *stock = 2; 
  pthread_t id = pthread_self();

  if(pthread_equal(id, thread1)){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
   while(1){
      valread = read( new_socket , buffer, 1024);
      if(strcmp(buffer,"tambah")==0){
        *stock += 1;
      }
   }
}

else if(pthread_equal(id, thread2)){
    while(1){
      printf("Stock saat ini %d\n", *stock);
      sleep(5);
    }
  }

}

int main(int argc, char const *argv[]) {
 
  pthread_create(&thread1, NULL, &jual, NULL);
  pthread_create(&thread2, NULL, &jual, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

    return 0;
}
