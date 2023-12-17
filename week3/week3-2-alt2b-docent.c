#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct opleiding
{     
    char oplnaam[10];
    int instroomjaar;    
};

struct persoon
{   
    char naam[10];
    int leeftijd;
    struct opleiding opl;
	struct persoon *next_persoon; // pointer naar volgende element
}; 


void print_personen_list( struct persoon *persoon ) {

    printf("\n---Informatie:---\n");    
	struct persoon *personen_iterator = persoon;  // pointer om alle elementen te doorlopen. Pointer persoon moet naar begin blijven wijzen
	struct persoon *persoon_laatst = NULL;  // pointer naar laatst toegevoegde element aan de lijst
	
	while ( personen_iterator != NULL ) {
		// er is een volgend element in de lijst
        printf("\nNaam: %s\n", personen_iterator->naam);
        printf("Leeftijd: %d\n", personen_iterator->leeftijd);
        printf("Opleidingsnaam: %s\n", personen_iterator->opl.oplnaam);  
        printf("Instroomjaar: %d\n", personen_iterator->opl.instroomjaar);
		
		personen_iterator = personen_iterator->next_persoon ;
    }

	return;
}	


int main() { 

    //struct persoon personen[3];
    struct persoon *personen = NULL;	// pointer naar 1e element van lijst mer personen
	struct persoon *persoon_laatst = NULL;  // pointer naar laatst toegevoegde element aan de lijst

	bool stoppen = false ;
    printf("Voer aub de gegevens in:\n");
    while ( !stoppen ){

        // reserveer (nieuw) geheugen voor nieuwe struct persoon element
		struct persoon *persoonElemPtr = (struct persoon *)malloc(sizeof(struct persoon));
		// controleer of gehegen is toegewezen
        if( !persoonElemPtr ) {
			printf("Geheugen is op!");
            break;
        }
		
		printf("\nNaam: \n");
		scanf("%s", persoonElemPtr->naam );  // naam is pointer
		
        printf("Leeftijd: \n");
        scanf("%d", &persoonElemPtr->leeftijd );  // leeftijd is int
		
        printf("Opleidingsnaam: \n");    
        scanf("%s", persoonElemPtr->opl.oplnaam);  
		
        printf("Instroomjaar: \n");    
        scanf("%d", &persoonElemPtr->opl.instroomjaar);

		persoonElemPtr->next_persoon = NULL;  //

	    // laat vorige element doorverwijzen naar dit nieuwe element
		if ( personen == NULL ) {
			// lijst met personen is nog leeg
			personen = persoonElemPtr ;
			persoon_laatst = persoonElemPtr ;			
		}
		else {
			// laat vorige element wijzen naar dit nieuwe element	
			persoon_laatst->next_persoon = persoonElemPtr ;
			// update persoon_last
			persoon_laatst = persoonElemPtr ;		
		}

		// 
		char antwoord[10];
		printf("\n\nWilt u meer personen toevoegen (Ja/Nee)? \n");
		scanf("%s", antwoord );  // antwoord is pointer		
		
		//if ( ( strcmp( antwoord ,"j") ) && ( strcmp( antwoord ,"J") ) && ( strcmp( antwoord ,"Ja") ) && ( strcmp( antwoord , "JA" ) ) && ( strcmp( antwoord , "ja" ) ) ) {
		if ( ( antwoord[0] != 'J' ) && ( antwoord[0] != 'j' ) ) {
			stoppen = true ;
		}	
		//printf("stoppen = %s \n ", stoppen ? "true" : "false");
    }
	
	// print info in lijst
	print_personen_list( personen );
	
	
    return 0;
}