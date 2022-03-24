#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include "semaphore.h"// I create my own library
int main(){
    int* s;// declaration semaphore1 == s
    int semid1;// declaration semaphore1 id
    semid1 = shmget((key_t)1222, 1024, 0666|IPC_CREAT);
    s = shmat(semid1, NULL, 0);
    init(s,1);// *s = 1
    int* p;// declaration semaphore2 == p
    int semid2;// declaration semaphore2 id
    semid2 = shmget((key_t)1223, 1024, 0666|IPC_CREAT);
    p = shmat(semid2, NULL, 0);
    init(p,0);// *p = 0
    void* shared_memory;// declaration the shared memory
    char buffer[30];
    int shmid;// declaration id of the shared memory
    shmid = shmget((key_t)1221, 1024, 0666|IPC_CREAT);
    shared_memory = shmat(shmid, NULL, 0);
    while(1){
        sem_wait(s);// *s = *s-1
        printf("Enter some data to write to shared_memory : ");
        gets(buffer);// scanf the value of buffer
        strcpy((char*)shared_memory,buffer);
        sem_signal(p);// *p = *p+1
    }
    return 0;
}