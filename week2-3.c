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
    //Declareer de student structure
    struct student stu;
    // Als test print de size
    printf("The size of structure student : %ld\n", sizeof(stu)); 

    // Vul de structure
    strcpy(stu.opl.opleidingNaam, "HBO-ICT NSE");
    stu.opl.instroomjaar = 2023;
    strcpy(stu.naam, "Patrick ten Brinke");
    stu.leeftijd = 25;

    // Print de structure
    printf("%s %d %s %d\n", stu.naam, stu.leeftijd, stu.opl.opleidingNaam, stu.opl.instroomjaar);

	return 0;
}

