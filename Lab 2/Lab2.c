//Brandon Quant
//COEN 11 Lab 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char names[5][20];
int sizes[5];
int input;
int input2;
char name[20];
int size;
int sum = 0;
int counter = 0;
void add(void);
void cancel(void);
void list(void);

int main (){
    for (int i = 0; i < 5; i++){
	for (int j = 0; j < 20; j++){
	    names[i][j] = '\0';
	} 
    }
    for (int i = 0; i < 5; i++){
	sizes[i] = 0;
    }
    while (1){ //keeps running until case 4 is chosen
	printf("Press 1 to be added to the waiting list\n");
	printf("Press 2 to cancel\n");
	printf("Press 3 to list the waiting list\n");
	printf("Press 4 to quit\n");
	scanf("%d", &input);
	switch (input){
	    case 1:
		add();
		break;
	    case 2: 
		cancel();
		break;
	    case 3:
		list();
		break;
	    case 4:
		return 0;
		break;
	}
    }
}
void add (void){
    printf("What is your name\n");
    scanf ("%s", name);
    printf("What is the size of your group\n");
    scanf("%d", &size);
    for (int i = 0; i < 5; i++){
	if (strcmp (name, names[i]) == 0){ //checks for duplicates
	    printf("This name is already used. Please choose another name\n");
	    break;
	}
	if (names[i][0] == '\0'){ //copies the name and size from the inputs and puts them into the arrays
	    strcpy (names[i], name);
	    sizes[i] = size;
	    counter++;        
	    break;
	}
	if (counter == 5){
	    printf("There are no times. Come back tomorrow\n");
	    break;
	}
    }

}
void cancel(void){
    printf("How many people are you deleting from the waitlist?");
    scanf("%d", &input2);
    sum = input2;
    for (int i = 0; i < 5; i++){
	if (sizes[i] <= sum){ //checks if the element in that array is less than the sum or size input
	    sum = sum - sizes[i];
	    printf("%s with a group size of %d has been removed\n", names[i],sizes[i]);
	    names[i][0] = '\0';
	    sizes[i] = 0;	    	    
	    for (int j = i; j < 5; j++){
		if (j==4){
		    break;
		}
		else{
		    strcpy(names[j], names[j+1]); //shifts the elements in the array up
		    names[j+1][0] = '\0';
		    sizes[j] = sizes[j+1];
		}   
		counter--;
		if (i >=1){
		    i-= 1;
		}
	    }
	}
    }

}
void list(void){
    if (counter == 0){
	printf("The schedule is empty\n");
	return;
    }
    for (int i = 0; i < 5; i++){ // lists out all the names and group sizes left in the array
	if (names[i][0] != '\0'){
	    printf("Names: ");
	    printf("%s\n", names[i]);
	    printf("Group Size: ");
	    printf("%d\n", sizes[i]);	
	}
    }
}

