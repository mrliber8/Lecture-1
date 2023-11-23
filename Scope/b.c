#include "a.h"

int main()
{
	printf("At start of main function x has value: %d\n", x);
	int i, x = 0;
	for (i=0; i < 1; i++) {
		int x = 3;
		a();
		printf("In loop of main function x has value: %d\n", x);
	}
	return(0);
}
