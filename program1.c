#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	puts("Before Fork");
	fork();
	sleep(30);
	puts("After Fork");
	return 0;
}

