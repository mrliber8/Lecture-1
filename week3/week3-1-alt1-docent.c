#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EOL '\n'



FILE* open_file( char* filename, char* read_write )
{
	FILE *filePtr;
	char filename_default[20];
	char input_output[10];
		
	if ( !strcmp( read_write, "r" ) ) {   // strcmp() returns 0 if string are equal
		strcpy( input_output, "reading" );
		strcpy( filename_default, "input.txt" );
	}
	else if ( !strcmp( read_write, "w" ) ) {   // strcmp() returns 0 if string are equal
		strcpy(input_output, "writing");
		strcpy( filename_default, "output.txt" );	
	}
	else {
		printf("Onbekend parameter read_write in open_file \n");
		exit(0);
	}	
	
	printf("\n");
	printf("Enter the filename to open for %s . \t", input_output );
	printf("[ type number 1 to use default file \"%s\" ] \n", filename_default );	
	scanf("%s", filename);   
	
	if ( filename[0] == '1' ) {
		strcpy(filename, filename_default);	
		printf("Default file will be used\n");		
	}
	
    // Open file for reading or writing
    filePtr = fopen(filename, read_write );
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
	
	f_in_ptr = open_file( filename_read, "r" );	
	f_out_ptr = open_file( filename_write, "w" );	

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
