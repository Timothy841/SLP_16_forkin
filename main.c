#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(){
  printf("Parent!\n");
  int file = open("/dev/urandom", O_RDONLY);
  int f = fork();
  int p;
  if (f){
    p = fork();
  }
  if (f && p){//parent
    int status;
    int a = waitpid(-1, &status, 0);
    if (WIFEXITED(status)){
      printf("Parent: Child pid:%d waited %d seconds\n", a, WEXITSTATUS(status));
    }
    else{
      printf("Something went wrong. Return %d\n", WEXITSTATUS(status));
    }
    printf("Parent done!\n");
    return 0;
  }
  else{//child
    unsigned int b;
    read(file, &b, 4);
    b = b%4+2;
    sleep(b);
    printf("Child pid:%d Slept %d seconds\n", getpid(), b);
    close(file);
    return b;
  }
}
