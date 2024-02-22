#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	pid_t pid = fork();

	if (pid == -1) {
//		If fork() returns -1, an error happened.
			perror("fork failed");
		return 1;
	} else if (pid == 0) {
//		If fork() returns 0, we are in the child process.
			printf("This is the child process with PID %d\n", getpid());
	} else {
//		If fork() returns a positive number, we are in the parent process
//		and the return value is the PID of the newly created child process.
			printf("This is the parent process, the child's PID is %d, my PID is %d\n",pid,getpid());
	}

//	Both processes continue from here.
		while(1){
			sleep(10);
		}
		return 0;
}
