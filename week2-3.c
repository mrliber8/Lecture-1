/*
3.	Structures
Schrijf een C programma die de gebruiker een array van structures laat invullen (3 elementen). De gewenste structure beschrijft een student is als volgt gedefinieerd:
•	De structure heeft als naam “student”
•	De “student” structure bevat een string om de “naam” van de “student” op te slaan
•	De “student” structure bevat een variabele om de “leeftijd” van de “student” op te slaan
•	De “student” structure bevat een structure van een “opleiding”
•	De “opleiding” structure bevat een string om de “naamOpleiding” van de “opleiding” op te slaan
•	De “opleiding” structure bevat een variabele om het “instroomJaar” van de “student” aan deze “opleiding” in op te slaan.
De gebruiken kan de informatie van drie studenten invoeren, en deze informatie wordt uitgeprint wanneer de gebruiker klaar is met het invullen van de informatie.

Lever het bestand in met de naam: “week2-3.c”.

*/

#include <stdio.h>

// Structure genaamd opleiding met 2 elementen
struct opleiding
{
    // De “opleiding” structure bevat een string om de “naamOpleiding” van de “opleiding” op te slaan
    char opleidingNaam[20];
    // De “opleiding” structure bevat een variabele om het “instroomJaar” van de “student” aan deze “opleiding” in op te slaan.
    int instroomjaar;
};


// Structure genaamd student met 3 elementen
struct student
{
    //De “student” structure bevat een string om de “naam” van de “student” op te slaan
    char naam[20];

    //De “student” structure bevat een variabele om de “leeftijd” van de “student” op te slaan
    int leeftijd;

    //De “student” structure bevat een structure van een “opleiding”
    struct opleiding opl;
};
 


int main(void)
{
    int count = 0;

    //Declareer de student structure
    struct student stu[10];
    
    // Als test print de size
    printf("The size of structure student : %ld\n", sizeof(stu)); 

    // Vul de structure
    printf("Wat is de naam?: ");
    scanf("%s", stu[count].naam);
    printf("Wat is de leeftijd?: ");
    scanf("%d", &stu[count].leeftijd);
    printf("Wat is de opleidingsnaam?: ");
    scanf("%s", stu[count].opl.opleidingNaam);
    printf("Wat is het instroomjaar?: ");
    scanf("%d", &stu[count].opl.instroomjaar);


    //count++;
    printf("test");
    printf("%s %d %s %d\n", stu[count].naam, stu[count].leeftijd, stu[count].opl.opleidingNaam, stu[count].opl.instroomjaar);

	return 0;
}

