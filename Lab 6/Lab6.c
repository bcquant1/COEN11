//Brandon Quant
//COEN 11 Lab #6
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char name2[20];
void add(void);
void cancel(int);
void list (void);
void checksizes(void);
int checkduplicates (char *);
void cancelall (void);
void change(void);

#define NODE struct node 
#define NODE2 struct node2

struct node{
    int number;
    char name[20];
    NODE *next;
};

struct node2{
    NODE *head;
    NODE *tail;
};

NODE2 waitlist[4] = {{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}};

int main(){
    int num;
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
		printf("How may people are you deleting\n");
		scanf ("%d", &num); 
		cancel(num);
		break;
	    case 3:
		list();
		break;
	    case 4:
		checksizes();
		break;
	    case 5:
		change();
	    case 8:
		cancelall();
	    case 9:
		return 0;
		break;
	    default:
		printf("Enter a valid number.\n");
	}
    }
}

void add (void){ //adds the name, and size
    char name2[20];
    int size;
    NODE *p;
    int i;

    printf("What is your name\n");
    scanf ("%s", name2);
    if (checkduplicates(name2) == 1){ //checks for duplicates
	printf("This name is already used. Please choose another name\n");
	return;
    }
    printf("What is your group size\n");
    scanf ("%d", &size);
    if ((p = (NODE*) malloc(sizeof(NODE))) == (NODE*)NULL){ //checks if the memory is allocated correctly
	printf("Error\n");
	return;
    }
    if (size == 1 || size == 2){ //depending on the group size, p is put in a certain linked list
	if (waitlist[0].head == NULL){
	    waitlist[0].head = p;
	    waitlist[0].tail = p;
	}
	else{
	    waitlist[0].tail->next = p;
	    waitlist[0].tail = p;
	}
    }
    if (size == 3 || size == 4){
	if (waitlist[1].head == NULL){
	    waitlist[1].head = p;
	    waitlist[1].tail = p;
	}
	else{
	    waitlist[1].tail->next = p;
	    waitlist[1].tail = p;
	}
    }
    if (size == 5 || size == 6){
	if (waitlist[2].head == NULL){
	    waitlist[2].head = p;
	    waitlist[2].tail = p;
	}
	else{
	    waitlist[2].tail->next = p;
	    waitlist[2].tail = p;
	}
    }
    if (size > 6){
	if (waitlist[3].head == NULL){
	    waitlist[3].head = p;
	    waitlist[3].tail = p;
	}
	else{
	    waitlist[3].tail->next = p;
	    waitlist[3].tail = p;
	}
    }
    strcpy(p->name, name2); // copies the name into the linked list
    p->number = size; // coppies the group size into the liked list
    p->next = NULL;
    return;
}

void cancel(int num){ // cancel the number of people that are inputed by the user
    NODE *p, *q;
    NODE *temp;
    int sum = num;
    int i;
    for (i = 0; i<4; i++){
	p = waitlist[i].head;
	while (p != NULL && p->number <= num){
	    num -= p->number; //subtracts the number in the array list from the number inputed from the user
	    if (p == waitlist[i].head){ //checks if the number is at the head
		waitlist[i].head = p->next;
		printf("%s with a group size of %d has been deleted\n", p->name, p->number);
		p= p->next;
		free (p);
	    }
	    else if (p == waitlist[i].tail){ // checks if the number is at the tail
		waitlist[i].head = waitlist[i].tail = NULL;	
		printf("%s with a group size of %d has been deleted\n", p->name, p->number);
		free(p);
		break;
	    }
	}
    }
}

void list(void){ // lists out the names and group size
    NODE *p;
    int i;
    int flag = 0;
    
    for (i = 0; i < 4; i++){
	if (i == 0){
	    printf("Group size from 1-2\n");
	}
	else if (i == 1){
	    printf("Group size from 3-4\n");
	}
	else if (i == 2){
	    printf("Group size from 5-6\n");
	}
	else{
	    printf("Group size greater than 7\n");
	}
	
	if (waitlist[i].head == NULL){
	    printf("The group size is empty\n");    
	}
	else{
	    p = waitlist[i].head;
	    while (p != NULL){
		printf("Name: %s, Group Size: %d\n", p->name, p->number);
		p = p->next;
	    }
	}
    }
    return;
}
void checksizes (void){ // check if the size inputed is any of the group sizes in the linked list 
    int input3;
    int i;
    NODE *p;
    printf("Enter a size\n");
    scanf("%d", &input3);
    for (i = 0; i < 4; i++){
	p = waitlist[i].head;
	while (p != (NODE*)NULL){
	    if (p->number <= input3){
		printf("Names: %s\n", p->name);
		printf("Group Size: %d\n", p->number);
	    }
	    p = p->next;
	}
    }
}

int checkduplicates (char *names){ //checks if the name inputed is already in the linked list
    NODE *p;
    int i;
    for (i = 0; i < 4; i++){
	p = waitlist[i].head;
	while (p != (NODE*)NULL){
	    if (strcmp (names, p->name) == 0){ //checks for duplicates
		return 1;    
	    }
	    p = p->next;		
	}
    }
    return 0;
}
void cancelall (void){ // runs through the array of linked lists and cancels the whole array
    NODE *p, *q;
    int i;
    for (i = 0; i < 4; i++){
	p = q = waitlist[i].head;
	while (p != NULL){
	    q = p;
	    p = p->next;
	    free (q);
	}
    }
    printf("Thank you for using");
    return;
}
void change (void){ //changes the group size of a specific person in the array of linked lists
    NODE *p, *q, *temp;
    int i, number2;
    char name2[20];
    printf("Enter your name:\n");
    scanf("%s", name2);
    printf("Enter the size of the group\n");
    scanf("%d", &number2);
    for (i = 0; i < 4; i++){
	p = waitlist[i].head;
	while (p != NULL){
	    if (strcmp(p->name, name2) == 0){
		if ((p->number == 1 || p->number == 2) && (number2 == 1 || number2 == 2)){
		    p->number = number2;
		}
		else if (waitlist[0].head == NULL){
			waitlist[0].head = p;
			waitlist[0].tail = p;
		}
		else{
		    waitlist[0].tail->next = p;
		    waitlist[0].tail = p;
		}

		if ((p->number == 3 || p->number == 4) && (number2 == 3 || number2 == 4)){
		    p->number = number2;
		}	
		else if (waitlist[0].head == NULL){
		    waitlist[0].head = p;
		    waitlist[0].tail = p;
		}
		else{
		    waitlist[0].tail->next = p;
		    waitlist[0].tail = p;
		}

		if ((p->number == 5 || p->number == 6) && (number2 == 5 || number2 == 6)){
		    p->number = number2;
		}	
		else if (waitlist[0].head == NULL){
		    waitlist[0].head = p;
		    waitlist[0].tail = p;
		}
		else{
		    waitlist[0].tail->next = p;
		    waitlist[0].tail = p;
		}

		if ((p->number > 6) && (number2 > 6)){
		    p->number = number2;
		}	
		else if (waitlist[0].head == NULL){
		    waitlist[0].head = p;
		    waitlist[0].tail = p;
		}
		else{
		    waitlist[0].tail->next = p;
		    waitlist[0].tail = p;
		}

	    p->number = number2;
	    p->next = NULL;
	    }
	}
    }
    return;
}
