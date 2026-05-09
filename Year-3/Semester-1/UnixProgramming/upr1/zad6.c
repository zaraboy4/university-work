#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (fork() > 0) {
		int status;
		wait(&status);
		printf("status: %d\n", status >> 8);
		if (status != 0)
			write(1, "cmd failed\n", 11);
		else
			write(1, "cmd succeed\n", 12);
	}
	else {
		execvp(argv[1], &argv[1]);
		write(1, "debug\n", 6);
		exit(1);
	}
	exit(0);
}	
