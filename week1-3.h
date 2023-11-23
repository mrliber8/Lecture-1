#include <stdio.h>

void print_function( char letter );


void main_print()
{
    int ctr;
    char star = '*';
    char dash = '-';
    for (ctr = 0 ; ctr < 10; ctr++ )
    {
        print_function( star );
        print_function( dash );
        printf("\n");
    }
    return 0;
}


void print_function ( char letter )
{
    int i; // Declareren van een andere variabele
    for ( i = 0; i < 9; i++) 
    {
        printf("%c", letter);
    }
}