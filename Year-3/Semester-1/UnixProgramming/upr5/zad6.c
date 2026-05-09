#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT);
	int fd1 = dup(fd);
	fork();
	write(fd, "helloooo", 8);
	write(fd1, "kvaki", 5);
	exit(0);
}
