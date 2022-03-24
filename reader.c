#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semaphore.h"// I create my own libary
int main(){
    int* s;// declaration semaphore1 == s
    int semid1;// declaration semaphore1 id
    semid1 = shmget((key_t)1222, 1024, 0666);
    s = shmat(semid1, NULL, 0);
    int* p;// declaration semaphore2 == p
    int semid2;// declaration semaphore2 id
    semid2 = shmget((key_t)1223, 1024, 0666);
    p = shmat(semid2, NULL, 0);
    void* shared_memory;// declaration the shared memory
    int shmid;// declaration id of the shared memory
    shmid = shmget((key_t)1221, 1024, 0666);
    shared_memory = shmat(shmid, NULL, 0);
    while(1){
        sem_wait(p);// *p = *p-1
        printf("Data read from shared memory is : %s\n",(char*)shared_memory);
        sem_signal(s);// *s = *s+1
    }
    return 0;
}