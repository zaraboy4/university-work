#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char* argv[])
{
	if (fork() > 0) {
		int status = 0;
		wait(&status);
		printf("status: %d\n", status >> 8);
		if (status != 0)
			printf("cmd failed\n");
		else
			printf("cmd succeed\n");	
	}
	else {
		execlp(argv[1], argv[1], argv[2], NULL); 
		exit(3);
	}
	exit(0);
}
