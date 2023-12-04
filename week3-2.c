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
// En gebruik ik nu define ipv de hele tijd los '20' erin zetten
// TO DO: De realloc logica


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
    Persoon *persoon = malloc(capacity * sizeof(Persoon));


    int count = 0;
    char keuze;
    char buf[NAAM_CHAR_SIZE];

    // Ongeveer dezelfde do while logica als week2-3:
    do
    {
        // Vul de structure
        printf("Wat is de naam?: ");
        fgets(buf, NAAM_CHAR_SIZE, stdin);
        sscanf(buf, "%s", persoon[count].naam);

        printf("Wat is de leeftijd?: ");
        fgets(buf, NAAM_CHAR_SIZE, stdin);
        sscanf(buf, "%d", &persoon[count].leeftijd);

        count++;

        printf("Wil je nog een student invullen? (y/n): ");
        fgets(buf, 5, stdin);
        sscanf(buf, "%c", &keuze);


        /* code */
    } while (keuze == 'y' || keuze == 'Y');
    
    for (int i = 0; i < count; i++)
    {
        printf("De naam is: %s en de leeftijd is %d\n", persoon[i].naam, persoon[i].leeftijd);
    }

    // Free the memory
    free(persoon);
    
    return 0;
}

