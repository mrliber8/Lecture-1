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
    for (int i = 0; i < 4; i++) {
        printf("waarde van array1[%d] = %f \n", i, array1[i]);
    }
    for (int i = 0; i < 4; i++) {
        printf("waarde van array2[%d] = %f \n", i, array2[i]);
    }

    //Roep de functie maxArrays aan
    for (int i = 0; i < 4; i++) {
        maxArrays(array1Ptr, array2Ptr, array3Ptr);
        array1Ptr +=1;
        array2Ptr +=1;
        array3Ptr +=1;
    }

    //Print de waarde van array 3
    for (int i = 0; i < 4; i++) {
        printf("waarde van array3[%d] = %f \n", i, array3[i]);
    }
    
}


void maxArrays(float *array1Ptr, float *array2Ptr, float *array3Ptr){
    //Check of array 1 of 2 groter is en zet de grootste waarde in array3
    if (*array1Ptr > *array2Ptr)
    {
        *array3Ptr = *array1Ptr;
    }
    else {
        *array3Ptr = *array2Ptr;
    }

}