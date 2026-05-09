#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int fd1 = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, 0744);
	if (fork() > 0) {
		write(1, "parent", 6);
		wait(NULL);
		lseek(fd1, 0, SEEK_SET);
		char buff[255];
		int read_bytes = read(fd1, buff, 255);
		int i;
		for (i = 0; i < read_bytes; ++i) {
			write(1, &buff[i], 1);
			write(1, " ", 1);
		}		
	}
	else {
		write(1, "child", 6);
		write(fd1, "Hello", 6);
	}
	exit(0);
}
