#include <stdio.h>

void print_function( char letter );
int ctr;

int main( void )
{
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

// We gebruiken 2x ctr, dus als print function verhoogd dan runt de main geen tweede keer
// Dus om het te fixen moeten we voor print_function een andere variabele gebruiken 
void print_function ( char letter )
{
    int i; // Declareren van een andere variabele
    for ( i = 0; i < 9; i++) 
    {
        printf("%c", letter);
    }
}