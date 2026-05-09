#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_WRONLY | O_APPEND | O_CREAT, 0744);
	printf("%d\n", fd);
	if (fd == -1) {
		printf("opening file failed\n");
		exit(1);
	}
	char buff[255];
	int n;
	while ( ( n = read(0, buff, 255) ) > 0) {
		printf("read bytes: %d", n);
		if (n != write(fd, buff, n)) {
			printf("writing to file failed\n");	
			exit(2);
		}
			
	}	
	exit(0);
}
