//Brandon Quant
//COEN 11 Lab #3
#include <stdio.h>
#include <string.h>

int input;
int input2;
int input3;
char name2[20];
int sum = 0;
int counter = 0;
void add(void);
void cancel(void);
void list (void);
void checksizes(void);
int checkduplicates (char *);

typedef struct info{
    char name[20];
    int size;
}INFO;

INFO waitlist[5];
INFO *p = waitlist;

int main(){
    while (1){ //keeps running until case 9 is chosen
	printf("Press 1 to be added to the waiting list\n");
	printf("Press 2 to cancel\n");
	printf("Press 3 to list the waiting list\n");
	printf("Press 4 to check sizes\n");
	printf("Press 9 to quit\n");
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
		checksizes();
		break;
	    case 9:
		return 0;
		break;
	    default:
		printf("Enter a valid number.\n");
	}
    }
}


void add (void){
    printf("What is your name\n");
    scanf ("%s", name2);
    printf("What is the size of your group\n");
    scanf("%d", &p->size); // copies the size into the structure
    for (int i = 0; i < 5; i++){
	if (checkduplicates(name2) == 1){ //checks for duplicates
	    printf("This name is already used. Please choose another name\n");
	    break;
	}
	if (p->name[0] == '\0'){
	    strcpy (p->name, name2); //copies the name into the structure
	    counter++;	
	    p++;
	    break;
	}
    }        
	if (counter == 5){
	    printf("There are no times. Come back tomorrow\n");
	    return;
	}

}
void cancel(void){
    p = waitlist;
    printf("How many people are you deleting from the waitlist?");
    scanf("%d", &input2);
    sum = input2;
    for (int i = 0; i < counter; i++,p++){
	if (p->size <= sum){ //checks if the element in that array is less than the sum or size input
	    sum = sum - waitlist[i].size;
	    printf("%s with a group size of %d has been removed\n", p->name, p->size);
	    p->name[0] = '\0';
	    p->size = 0;	    	    	     
	    for (int j = i; j < 5; j++){
		if (j==4){
		    break;
		}
		else{
		    strcpy(waitlist[j].name, waitlist[j+1].name); //shifts the elements in the array up
		    waitlist[j].size = waitlist[j+1].size;
		}
	    }  
	    counter--;
	    if (i >=1){
		i-= 1;
	    }
	}
    }
}
void list(void){
    if (counter == 0){
	printf("The schedule is empty\n");
	return;
    }
    p = waitlist;
    for (int i = 0; i < 5; i++){ // lists out all the names and group sizes left in the array
	if (p-> name[0] != '\0'){
	    printf("Names: ");
	    printf("%s\n", waitlist[i].name);
	    printf("Group Size: ");
	    printf("%d\n", waitlist[i].size);	
	    p++;
	}
    }
}
void checksizes (void){
    p = waitlist;
    printf("Enter a size\n");
    scanf("%d", &input3);
    for (int i = 0; i < counter; i++,p++){
	if (p->size <= input3){ //checks if the sizes are smaller than the input
	    if (p->size != 0){
	    printf("Names: %s\n", waitlist[i].name);
	    printf("Group Size: %d\n", waitlist[i].size);
	    }
	}    
    } 
}
int checkduplicates (char *names){
    for (int i = 0; i < counter; i++){
	if (strcmp (names, waitlist[i].name) == 0){ //checks for duplicates
	    return 1;    
	}
		
    }
    return 0;
}
