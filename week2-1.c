/*
Schrijf een functie in C genaamd maxArrays(). 
Deze functie vergelijkt steeds twee floats van twee arrays op dezelfde index en plaatst de grotere waarde in een derde array. 
Zie tabel hieronder als voorbeeld. Gebruik hierbij uiteraard pointers, gezien je de arrays mee wilt geven aan de functie. 
De arrays worden dus in de main functie aangemaakt en niet in de maxArrays() functie.
Print de waarden van array 1 en array 2 voordat de functie is aangeroepen.
Print de waarden van array 3 nadat de functie is aangeroepen.
*/

#include <stdio.h>

int main( void ){
    //initialiseer de arrays
    float array1[] = {0.7, 3.3, 0.5, 10.3};
    float array2[] = {4.1, 1.5, 0.5, 2.3};
    float array3[4]; //Goede array = {4.1, 3.3, 0.5, 10.3}

    //Initialiseer de pointers
    float* array1Ptr = &array1[0];
    float* array2Ptr = &array2[0];
    float* array3Ptr = &array3[0];

    //Print de waarde van array 1 & 2
    printf("waarde van array1 = %f \n", *array1Ptr);
    printf("waarde van array2 = %f \n", *array2Ptr);

    //Roep de functie maxArrays aan


    //Print de waarde van array 3
    printf("waarde van array3 = %f \n", *array3Ptr);

}


void maxArrays(){
    //Check of array 1 of 2 groter is

    //Zet de grootste waarde in array3

}