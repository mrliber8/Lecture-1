/*
1.	Files
Schrijf een C programma dat een bestand opent (.txt) en de volgende acties uitvoert.
•	Het aantal karakters van het gehele bestand wordt geteld en aan het einde uitgeprint. Karakters, zoals LF en EOF, die niet zichtbaar zijn voor iemand die het bestand opent in een tekst editor moeten niet worden meegeteld.
•	De tekst wordt gekopieerd naar een nieuw bestand, waarbij alle karakters 1 ASCII waarde opschuiven tenzij de nieuwe waarde ervoor zorgt dat de indeling in regels wordt gewijzigd (zie onderstaande bullet) 
•	Zorg dat het programma ook werkt voor .txt bestanden met meer dan één regel tekst: tekst die in originele bestand op één regel staat moet op dezelfde regel in het gekopieerde bestand blijven staan. 
Enkele voorbeelden van het opschuiven van ASCII-karakters:
’A’ → ’B’
’@’ → ’A’
’Z’ → ’[’

Lever het bestand in met de naam: “week3-1.c”.
*/

#include <stdio.h>


int main()
{
    char filename[100];
    char buf[100];

    FILE *inputFileName, *outputFileName;

    
    //Vraag om de input file name
    printf("Wat is de input naam?: ");
    fgets(buf, 100, stdin);
    sscanf(buf, "%s", filename);

    inputFileName = fopen(filename, "r");

    if (inputFileName == NULL)
    {
        printf("Error, controleer of de naam goed is, %s kan niet worden gevonden", filename);
        fclose(inputFileName);
        return -1;
    }

    //Vraag om de output file name
    printf("Wat is de output naam?: ");
    fgets(buf, 100, stdin);
    sscanf(buf, "%s", filename);

    outputFileName = fopen(filename, "w");

    if (outputFileName == NULL)
    {
        printf("Error, controleer of de naam goed is, %s kan niet worden gevonden", filename);
        fclose(outputFileName);
        return -1;
    }
    

    //Standaard filennames om testen makkelijker te maken
    //inputFileName = fopen("readTest.txt", "r");
    //outputFileName = fopen("writeTest.txt", "w");

    char ch;
    int counter = 0;

    while ((ch = fgetc(inputFileName)) != EOF)
    {
        // Karakters, zoals LF en EOF, die niet zichtbaar zijn voor iemand die het bestand opent in een tekst editor moeten niet worden meegeteld.
        // Newline is '\n', ' ' en '.' staan erin zodat de opmaak gelijk blijft
        if (ch != '\n' && ch != ' ' && ch != '.')
        {
            ch += 1;
            counter += 1;
        } else if (ch == ' ' || ch == '.')
        {
            //Niet ascii verhogen vanwege de opmaak, maar counter moet wel worden verhoogd natuurlijk
            counter += 1;
        }
        // Display de char als test in de terminal       
        putchar(ch);

        // Schrijf de char naar de nieuwe txt file
        fputc(ch, outputFileName);
    }

    // Sluit de files weer
    fclose(inputFileName);
    fclose(outputFileName);


    // Het aantal karakters van het gehele bestand wordt geteld en aan het einde uitgeprint.
    printf("\nAantal characters = %d", counter );

    return 0;
}


