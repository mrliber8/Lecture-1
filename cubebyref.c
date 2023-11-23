#include <stdio.h>

void cubeByRef(int*);

int main()
{
	int i=5;
	cubeByRef(&i);
	printf("result = %d ",i);
	return(0);
}

void cubeByRef(int *iPtr)
{
   *iPtr =  *iPtr * *iPtr * *iPtr;
}
