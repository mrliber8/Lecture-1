/*
Schrijf een C programma die de gebruiker vraag om een zin.
Na invoer wordt de lengte van deze ingevoerde zin uitgeprint (in aantal chars).
Lever het bestand in met de naam: “week2-2.c”.
*/

#include <stdio.h>

int main(int argc, char const *argv[])
{

    char sentance[50];
    printf("Enter a sentance, max 100 characters: ");
    fgets(sentance, sizeof(sentance), stdin);  // read string

    sentance[strcspn(sentance, "\n")] = 0;

    printf("De lengte van de ingevoerde zin is: %lu karakters.\n", strlen(sentance));



    //printf("Sentrance is: ");
    //puts(sentance);


    //scanf("%S", sentance);
    //printf("The sentace was %S.", sentance);
    return 0;
}


