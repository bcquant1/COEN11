// Brandon Quant
// COEN Tuesday Afternoon Lab
// lab1.c


#include <stdio.h>
#include <stdlib.h>


int main (){
    int count = 0;
    int divisor;
    int quotient;
    srand((int) time (NULL));
    for (int i  = 0; i < 10; i++){ // this runs the division test 10 times
        divisor = rand() % 12 + 1;
        quotient = rand () % 13;
            if (divide(divisor,quotient)  == 1){
                printf ("Congrats, you got it correct \n");
                count++;
            }
            else{
                printf("That was incorrect \n");
                printf("The correct quotient is %d\n", quotient);
            }
    }
    printf("You got ");
    printf("%d", count);
    printf(" out of 10  correct \n");
    return 0;
}

int divide (int divisor, int quotient){ //this checks if the input is the same as the quotient
    int input;
    int dividend;
    dividend = divisor * quotient;
    printf("%d / %d = ", dividend,divisor);
    scanf ("%d", &input);
    if (input == quotient ){
        return 1;
    }
    else{
        return 0;
    }

	
}

