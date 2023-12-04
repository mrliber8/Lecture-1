/*
Schrijf een C programma dat een data structuur (“struct”) aanmaakt voor het opslaan van informatie over personen. De gewenste structuur beschrijft een persoon en is als volgt gedefinieerd:
•	De structuur heeft als naam “Persoon”
•	De “Persoon” structuur bevat een string om de “naam” van de “Persoon” op te slaan
•	De “Persoon” structuur bevat een variabele om de “leeftijd” van de “Persoon” op te slaan
De gebruiker kan steeds weer de informatie van een extra persoon invoeren, en het programma zal deze steeds weer in een nieuwe structuur opslaan. Hiervoor zal dus ook steeds meer geheugen gereserveerd moeten worden doormiddel van realloc() ( initieel malloc() ).
Het plaatsen van de structuur elementen in niet-sequentiële geheugenadressen en de pointers hierbij in 1 blok alloceren mag ook, maar dat is puur bonus.
Na elke invoeren van een nieuw element wordt alle informatie van alle aangemaakte structuren uitgeprint.

*/


// Code is grotendeels hetzelfde als in week 2 opdr 3
// Alleen gebruik ik voor de struct nu typedef
// En gebruik ik nu #define voor de size ipv de hele tijd los '20' erin zetten



#include <stdio.h>

#define NAAM_CHAR_SIZE 20

typedef struct
{
    char naam[NAAM_CHAR_SIZE];
    int leeftijd;
} Persoon; 


int main()
{
    int capacity = 1;
    // Als persoon NULL is dan werkt realloc hetzelfde als malloc
    // Ik laat malloc er alsnog in staan in omdat dit van de opdracht moet en vanwege de uitleg in de do while loop
    Persoon *persoon = malloc(capacity * sizeof(Persoon));

    if (persoon == NULL)
    {
        printf("Initiele geheugen toewijziging is niet gelukt");
        return -1;
    }
    


    int count = 0;
    char keuze;
    char buf[NAAM_CHAR_SIZE];

    // Ongeveer dezelfde do while logica als week2-3:
    do
    {
        /*
         Als we capacity op 0 zetten kunnen we de if eigenlijk weg halen want elke keer
          als de while loop runt dan moet die geincreased worden, zelf vind ik dit
          wel nicer met de if erin want als je al zeker weet dat je bijvoorbeeld 5 wilt 
          invullen dan kun je hem gelijk op 5 zetten en de realloc de eerste paar keer overslaan
        */

        // Als count en capacity gelijk zijn dan is het geheugen vol
        if (count == capacity) {
            // Increment zodat er ruimte is voor 1 extra
            capacity += 1;
            // Reallocate het geheugen met 1 extra
            persoon = realloc(persoon, capacity * sizeof(Persoon));
        }

        if (persoon == NULL)
        {
            printf("realloc is niet gelukt");
            return -1;
        }
        else {
            // Vul de structure
            printf("Wat is de naam?: ");
            fgets(buf, NAAM_CHAR_SIZE, stdin);
            sscanf(buf, "%s", persoon[count].naam);

            printf("Wat is de leeftijd?: ");
            fgets(buf, NAAM_CHAR_SIZE, stdin);
            sscanf(buf, "%d", &persoon[count].leeftijd);

            count++;

            printf("Wil je nog een persoon invullen? (y/n): ");
            fgets(buf, 5, stdin);
            sscanf(buf, "%c", &keuze);
        }

    } while (keuze == 'y' || keuze == 'Y');
    
    // Print de inhoud van de structs
    for (int i = 0; i < count; i++)
    {
        printf("De naam is: %s en de leeftijd is %d\n", persoon[i].naam, persoon[i].leeftijd);
    }

    // Bevrijd het geheugen weer.
    free(persoon);
    
    return 0;
}

