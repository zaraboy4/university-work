#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int fd = open(argv[1], O_RDWR);
	char buff[3];
	read(fd, buff, 3);
	write(fd, "AAAA", 4);
	exit(0);
}
