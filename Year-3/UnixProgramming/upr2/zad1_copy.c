#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1) {
		printf("opening %s failed\n", argv[1]);
		exit(0);
	}
	char buff[10];
	int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0744);
	int n = 0;
	while ( (n = read(fd1, buff, 10)) > 0 ) {
		write(fd2, buff, n);
		// if (n != write(fd2, buff, n) ) {
			// printf("occured error during copying\n");
			// exit(0);
		// }
	}
	exit(0);
}	
