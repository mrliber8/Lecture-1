#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct persoon
{   
    char naam[10];
    int leeftijd;
}; 


void print_personen_arr( struct persoon *persoon, int aantal ) {

    printf("\n---Informatie:---\n");    
	struct persoon *personen_iterator = persoon;  // pointer om alle elementen te doorlopen. Pointer persoon moet naar begin blijven wijzen
	
	for ( int i =0; i < aantal; i++ ) {	
        printf("\nNaam: %s\n", persoon[i].naam);
        printf("Leeftijd: %d\n", persoon[i].leeftijd);
    }

	return;
}	


int main() { 

    //struct persoon personen[3];
    struct persoon *personen = NULL;	// pointer naar 1e element van lijst mer personen
	struct persoon *persoon_laatst = NULL;  // pointer naar laatst toegevoegde element aan de lijst

	int aantal_personen = 0;


	bool stoppen = false ;
    printf("Voer aub de gegevens in:\n");
    
	while ( !stoppen ){
		aantal_personen++;    // ga er vanuit dat nieuwe persoon toegevoegd kan worden
		personen = (struct persoon *)realloc( personen, aantal_personen * sizeof(struct persoon) ); // als personen = NULL dan realloc gelijk aan malloc
		
		if( !personen ) {
			printf("Geheugen is op!");
			aantal_personen--;   // toch niet gelukt om nieuwe persoon toe te voegen			
            stoppen = true;
        }
		else {			
			persoon_laatst = &personen[ aantal_personen - 1 ];			
		
			printf("\nNaam: \n");
			scanf("%s", persoon_laatst->naam );  // naam is pointer
			
			printf("Leeftijd: \n");
			scanf("%d", &persoon_laatst->leeftijd );  // leeftijd is int

			// 
			char antwoord[10];
			printf("\n\nWilt u meer personen toevoegen (J/N)? \n");
			scanf("%s", antwoord );  		
			
			if ( ( antwoord[0] != 'J' ) && ( antwoord[0] != 'j' ) ) {
				stoppen = true ;
			}	
			//printf("stoppen = %s \n ", stoppen ? "true" : "false");
		}
    }
	
	// print info in lijst
	print_personen_arr( personen, aantal_personen );
	
	
    return 0;
}