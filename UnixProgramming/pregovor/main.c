#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
	char buff[255];
	int readBytes = read(0,buff,255);
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0744);
	int writtenBytes = write(fd,buff,readBytes);
	printf("read bytes: %d\n", readBytes);
	printf("written bytes: %d\n", writtenBytes);
	exit(0);
}
