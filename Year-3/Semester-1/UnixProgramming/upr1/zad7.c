#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int m, n;
	scanf("%d %d", &m, &n);
	char option[50];
	sprintf(option, "-c%d-%d", m, n);
	if (fork() > 0) {
		int status;
		wait(&status);
		if (status != 0)
			write(1, "failed\n", 7);
		else
			write(1, "succeed\n", 8);
	}
	else {
		execlp("cut", "cut", option, argv[1],  NULL);
		exit(4);	
	}
	exit(0);
}
