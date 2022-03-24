#include <unistd.h>
void init(int* s,int val){
    *s = val;
}
void sem_wait(int* s){
    *s = *s-1;
    while(*s < 0){
        sleep(0.5);
    }
}
void sem_signal(int* s){
    *s = *s+1;
}