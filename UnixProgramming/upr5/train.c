#include <stdlib.h>
#include <unistd.h>

int main()
{
	if (fork() > 0) {
		int i;
		for (i = 0; i < 100; ++i)
			write(1, "parent\n", 7);
	}
	else {
		int i;
		for (i = 0; i < 100; ++i)
			write(1, "child\n", 6);
	}
	exit(0);
}

