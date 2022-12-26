#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int ac, char **av)
{
	int n;
	int j;

	n = atoi(av[1]);
	j = usleep(n);
	printf("%d\n",j);
	return 0;
}
