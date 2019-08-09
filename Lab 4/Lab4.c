
//Brandon Quant
//COEN 11 Lab #3
#include <stdio.h>
#include <string.h>

int counter = 0;
void add(void);
void cancel(void);
void list (void);
void checksizes(void);
int checkduplicates (char *);

typedef union unionanme{  
    int minage;
    float avgage;
    char phonenum[10];
}UNIONINFO;

typedef struct info{
    char name[20];
    int size;
    int maxage;
    UNIONINFO u; 
}INFO;

INFO waitlist[5];
INFO *p = waitlist;

int main(){ //prints out the interface and goes to the respective functions based on the input
    int input;
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
		printf("This is an invalid number");
	}
    }
}

void add (void){ //adds the name, size, max age, and union member depending on the max age
    char name2[20];
    int age;
    if (counter == 5){
	printf("There are no times. Come back tomorrow\n");
	return;
    }
    printf("What is your name\n");
    scanf ("%s", name2);
    for (int i = 0; i < 5; i++){
	if (checkduplicates(name2) == 1){ //checks for duplicates
	    printf("This name is already used. Please choose another name\n");
	    break;
	}
    }
    strcpy (p->name, name2); //copies the name into the structure
    counter++;	

    printf("What is the size of your group\n");    
    scanf("%d", &p->size); // copies the size into the structure
    
    printf("What is the max age\n"); // copies the max age in the structure
    scanf("%d",	&age);
    p->maxage = age;   

    if (age < 18){
	printf("Please type in a phone number\n");
	scanf("%s",p->u.phonenum); // copies the phone number into the union in the structure
    }
    else if (age > 60){
	printf("Please type in the minimum age\n");
	scanf ("%d", &p->u.minage); // copies the minimum age into the union in the structure
    }
    else{
	printf("Please type in the average age\n");
	scanf("%f", &p->u.avgage); // copies the average age into the union in the structure
    }       
    p++;

}
void cancel(void){ // cancels the inputed number of people and shifts all the elements up
    int input2;
    int sum;
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
		//p--;
	    }
	}
    }
}
void list(void){ //lists out the names, group sizes, max age, and the union member depending on the max age
    int i;
    int j;
    if (counter == 0){
	printf("The schedule is empty\n");
	return;
    }
    p = waitlist;
    for (i = 0; i < counter; i++){ // lists out all the names, sizes, max age, and union member
	if (p-> name[0] != '\0'){
	    printf("Names: ");
	    printf("%s\n", waitlist[i].name);
	    printf("Group Size: ");
	    printf("%d\n", waitlist[i].size);
	    printf("Max Age: ");
	    printf("%d\n", waitlist[i].maxage);
	    printf("Extra info:\n ");
	    if (waitlist[i].maxage < 18){
		printf("Phone Number: ");
		for (j = 0; j < 10; j++){
		    printf("%c", waitlist[i].u.phonenum[j]);
		}	
		printf("\n");
	    }	
	    else if(waitlist[i].maxage > 60){
		printf("Minimum age: ");
		printf("%d\n", waitlist[i].u.minage);
	    }
	    else{
		printf("Average age: ");
		printf("%f\n", waitlist[i].u.avgage);
	    }
	    p++;
	}
    }
}
void checksizes (void){ // prints out sizes that are smaller than the input
    p = waitlist;
    int input3;
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
int checkduplicates (char *names){ // checks the inputted name with the names in the array to check for duplicates
    for (int i = 0; i < counter; i++){
	if (strcmp (names, waitlist[i].name) == 0){ //checks for duplicates
	    return 1;    
	}
		
    }
    return 0;
}
