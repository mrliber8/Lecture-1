/*
Schrijf een C programma die de gebruiker vraag om een zin.
Na invoer wordt de lengte van deze ingevoerde zin uitgeprint (in aantal chars).
Lever het bestand in met de naam: “week2-2.c”.

Strings.
*/

#include <stdio.h>

#define MAX_INPUT_LENGTH 100

int main(int argc, char const *argv[])
{

    //Initialiseer een char die de zin kan bevatten.
    char sentence[MAX_INPUT_LENGTH];

    //Vraag de user om input
    printf("Enter a sentance, max %d characters: ", MAX_INPUT_LENGTH);

    //Lees de string in
    fgets(sentence, MAX_INPUT_LENGTH, stdin); 
 
    //print de lengte van de complete zin -1 vanwege de newline character
    printf("De lengte van de ingevoerde zin is: %lu karakters.\n", strlen(sentence) -1);
    

    return 0;
}