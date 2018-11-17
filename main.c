#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int random_gen() {
  int rand_file = open("/dev/random", O_RDONLY);
  int i;
  int random_int = read(rand_file, &i, sizeof(int));
  close(rand_file);
  return i;
}

int main(int argc, char const *argv[]) {
  printf("Parent pid: %i ppid: %i now forking...\n", getpid(), getppid());
  int f = fork();
  if(f == -1) {
  	printf("%s\n", strerror(errno));
	}
  if(f != 0) {
    f = fork();
  }
	if(f == 0) {
    printf("I am a child pid: %i ppid: %i\n", getpid(), getppid());
    int sleep_time = random_gen();
    sleep_time = (abs(sleep_time) % 16) + 5;
    // printf("Sleep time: %d\n", sleep_time);
    sleep(sleep_time);
    printf("Child sleeping finished!\n");
    return sleep_time;
	}
	else {
		int status;
    int child = wait(&status);
    // printf("%d\n", status);
    printf("Completed child's pid: %d It was asleep for %d seconds.\n", child, status/256);
    printf("Parent is done!\n");
	}
  return 0;
}
