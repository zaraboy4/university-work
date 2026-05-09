#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	execvp(argv[1], &argv[1]);
	exit(2);
}
