#include <stdio.h>
#include "week1-3.h"

int main()
{
    int testIntiger;
    printf("Make an option between the following three choises: \n");
    printf("1. If you enter a negative number, the program will close \n");
    printf("2. If you enter a zero, 10 zero's will be displayed \n");
    printf("3. If you enter a positive number, hello world will be printed \n");
    printf("Now enter an integer:  ");
    scanf("%d", &testIntiger);
    printf("number = %d \n", testIntiger);

    if (testIntiger < 0) {
        printf("Now Closing....");
        return 0;
    }
    else if (testIntiger > 0)
    {
        main_print();
    }
    else if (testIntiger == 0)
    { 
        printf("Hello World");
    }
}
