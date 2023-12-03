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


    printf("Wat is de naam?: ");
    fgets(buf, 20, stdin);
    sscanf(buf, "%s", filename);

    inputFileName = fopen(filename, "r");

// https://www.learnc.net/c-tutorial/c-read-text-file/




    /* code */
    return 0;
}
