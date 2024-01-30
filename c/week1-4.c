#include <stdio.h>
#define PI 3.14159

void calculateCircumference(float *diameterPtr);


int main(){
    
    float diameter;

    printf("Enter a diameter \n");
    scanf("%f", &diameter);
    printf("Chosen diameter = %f \n", diameter);

    float *diameterPtr = &diameter;

    calculateCircumference(diameterPtr);

    printf("The circumference is: %f\n", diameter);
}

void calculateCircumference(float *diameterPtr){

    //printf("CcalculateCircumference test = %f \n", *diameterPtr);

    *diameterPtr = 2 * PI * *diameterPtr;
}



