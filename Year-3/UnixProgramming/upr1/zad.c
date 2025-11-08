#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int number = 5;
	char buff[30];
	sprintf(buff, "%d", number);
	write(1, buff, strlen(buff));
	exit(0);
}
