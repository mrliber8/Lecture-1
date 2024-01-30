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
    char keuze;

    char buf[100];

    //Declareer de student structure
    struct student stu[100];

    do
    {
        // Vul de structure
        printf("Wat is de naam?: ");
        fgets(buf, 20, stdin);
        sscanf(buf, "%s", stu[count].naam);

        printf("Wat is de leeftijd?: ");
        fgets(buf, 20, stdin);
        sscanf(buf, "%d", &stu[count].leeftijd);

        printf("Wat is de opleidingsnaam?: ");
        fgets(buf, 20, stdin);
        sscanf(buf, "%s", stu[count].opl.opleidingNaam);

        printf("Wat is het instroomjaar?: ");
        fgets(buf, 20, stdin);
        sscanf(buf, "%d", &stu[count].opl.instroomjaar);


        count++;

        printf("Wil je nog een student invullen? (y/n): ");
        fgets(buf, 20, stdin);
        sscanf(buf, "%c", &keuze);

    } while (keuze == 'y' || keuze == 'Y'); // OR ivm mogelijk gebruik van hoofdletter
    

   for (int i = 0; i < count; i++)
    {
        printf("De naam is: %s en de leeftijd is %d en de opleiding is %s en het instroomjaar is %d\n", stu[i].naam, stu[i].leeftijd, stu[i].opl.opleidingNaam, stu[i].opl.instroomjaar);
    }
   

	return 0;
}

