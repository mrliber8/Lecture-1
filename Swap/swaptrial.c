#include <stdio.h>

void swap(int, int);

int main()
{
	int a=3, b=5;
	printf("before swap: a: %d, and b: %d\n", a, b);
	swap(a, b);
	printf("after swap: a: %d, and b: %d\n", a, b);
	return(0);
}

void swap(int x, int y)
{
	int h = x;
	x = y;
	y = h;
}
