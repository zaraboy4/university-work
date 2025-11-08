#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	printf("this is parent\n");
	int cd = fork();
	if (cd > 0) {
		printf("this is parent\n");
	}
	else {
		printf("this is child\n");
	}
	exit(0);
}
