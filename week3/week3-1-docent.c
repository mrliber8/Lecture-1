#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EOL '\n'

FILE* open_read_file( char* filename )
{
	FILE *filePtr;
	char filename_default[100]="input.txt";

	printf("\n");
	printf("Enter the filename to open for reading.\t");
	printf("[ type number 1 to use default file \"%s\" ] \n", filename_default );	
	scanf("%s", filename);   
	
	if ( filename[0] == '1' ) {
		strcpy(filename, filename_default);	
		printf("Default input file will be used\n");		
	}
	
    // Open one file for reading
    filePtr = fopen(filename, "r");
    if (filePtr == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }	
	
	return filePtr;
}	

FILE* open_write_file( char* filename )
{
	FILE *filePtr;
	char filename_default[100]="output.txt";

	printf("\n");	
	printf("Enter the filename to open for writing.\t");
	printf("[ type number 1 to use default file \"%s\" ]\n", filename_default );	
	scanf("%s", filename);   
	if ( filename[0] == '1' ) {
		strcpy(filename, filename_default);	
		printf("Default output file will be used\n");
	}
	
    // Open one file for writing
    filePtr = fopen(filename, "w");
    if (filePtr == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }	
	
	return filePtr;
}	

int main()
{
    FILE *f_in_ptr, *f_out_ptr;
    char filename_read[100], filename_write[100];
	char c_read, c_write;
	
	f_in_ptr = open_read_file( filename_read );	
	f_out_ptr = open_write_file( filename_write );	
	
	int ctr = 0;
	
	// nieuwe char gelezen aan eind van while loop zodat EOF niet wordt weggeschreven
	// daarom moet je wel eerst de char lezen voor while
	c_read = fgetc( f_in_ptr );
	while ( c_read != EOF ) { 
	
		if ( ( c_read != EOL ) && ( c_read != ' ' ) && ( c_read != '.' )  ) {	// c_read kan nooit gelijk zijn aan EOF hier, Asci waarde 10 staat voor LF	
			// character gevonden die moet worden opgeschoven
			c_write = c_read + 1;
			ctr++;
			printf("\nctr=%d\tc=%c\tasci=%d", ctr, c_read, (int)c_read );
			if ( (int)c_read < 100 ) { printf(" "); }
			printf("\tc_out=%c", c_write );
			
		}
		else {						
			c_write = c_read;
			if ( c_read != EOL ) { // EOL telt niet als character, spaties en punten wel
				ctr++;
				printf("\nctr=%d\tc=%c\tasci=%d", ctr, c_read, (int)c_read );
			}	
		}	
		fputc( c_write, f_out_ptr);		
		c_read = fgetc( f_in_ptr );
	

		if ( c_read == EOF ) { printf("\nctr=%d\tc=EOF: NOT WRITTEN TO FILE", ctr+1 ); }	

    }


    printf("\nContent of %s has been ascii shifted by 1",filename_read );  
    printf("\nContents copied to %s", filename_write );
	printf("\nNumber of characters in file = %d\n", ctr );
  
    fclose(f_in_ptr);
    fclose(f_out_ptr);
		
    return 0;
}
