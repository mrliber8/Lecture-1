/*
Schrijf een C programma die de gebruiker vraag om een zin.
Na invoer wordt de lengte van deze ingevoerde zin uitgeprint (in aantal chars).
Lever het bestand in met de naam: “week2-2.c”.

Strings.
*/

#include <stdio.h>

int main(int argc, char const *argv[])
{

    //Initialiseer een char die de zin kan bevatten.
    char sentance[100];

    //Vraag de user om input
    printf("Enter a sentance, max 100 characters: ");

    //Lees de string in
    fgets(sentance, sizeof(sentance), stdin); 
    //scanf("%s",sentance); 

    //print de lengte van de complete zin
    printf("De lengte van de ingevoerde zin is: %lu karakters.\n", strlen(sentance));

    //Bepaal de lengte zonder spaces en end
    int sentanceLength = strlen(sentance);
    for (int i = 0; i < strlen(sentance); i++)
    {
        if (sentance[i] == ' ' || sentance[i] == '\0' )
        {
            sentanceLength += -1;
        }
    }

    printf("De lengte zonder spaces en trailing end is: %lu kartakters.\n", sentanceLength);

    return 0;
}