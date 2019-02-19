#include <unistd.h>
#include <stdio.h>

int main(){
    sleep(5);
    int pid = getpid();
    int parentsPID = getppid();
    printf("PID= %d \n",pid);
    printf("PPID= %d \n",parentsPID);
    return 0;
}
