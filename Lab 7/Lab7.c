//Brandon Quant
//COEN 11 Lab #7

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add(char *, int);
void cancel(int);
void list (void);
void checksizes(void);
int checkduplicates (char *);
void read (char *);
void save (char *);

#define NODE struct node

struct node{
    int number;
    char name[20];
    NODE *next;
};

NODE *head = (NODE*)NULL;
NODE *tail = (NODE*)NULL;

int main(int argc, char *argv[]){
    int num;
    int input;
    char name2[20];
    int size;
    if (argc == 1){
	printf("The name of the file is missing\n");
	return 1;
    }
    read (argv[1]);

    while (1){ //keeps running until case 9 is chosen
	printf("Press 1 to be added to the waiting list\n");
	printf("Press 2 to cancel\n");
	printf("Press 3 to list the waiting list\n");
	printf("Press 4 to check sizes\n");
	printf("Press 9 to quit\n");
	scanf("%d", &input);
	switch (input){
	    case 1:		
		printf("What is your name\n");
		scanf ("%s", name2);
		if (checkduplicates(name2) == 1){ //checks for duplicates
		    printf("This name is already used. Please choose another name\n");
		    return 1;
		}
		printf("What is your group size\n");
		scanf ("%d", &size);
		add(name2,size);
		break;
	    case 2:
		printf("How may people are you deleting");
		scanf ("%d", &num); 
		cancel(num);
		break;
	    case 3:
		list();
		break;
	    case 4:
		checksizes();
		break;
	    case 9:
		save(argv[1]);
		return 0;
		break;
	    default:
		printf("Enter a valid number.\n");
	}
    }
}

void add (char *name2, int size){ //adds the name, and size
    NODE *p;

    if ((p = (NODE*) malloc(sizeof(NODE))) == (NODE*)NULL){ //checks if the memory is allocated correctly
	printf("Error\n");
	return;
    }

    if (head == NULL){ //checks if the head is at the beginning
	head = p;
	tail = p;
    }
    else{ // moves the tail to the end
	tail->next = p;
	tail = p;
    }
    strcpy(p->name, name2);
    p->number = size;
    p->next = NULL;
    return;
}

void cancel(int num){ // cancel the number of people that are inputed by the user
    NODE *p, *q;
    NODE *temp = NULL;
    p = q = head;
    while (p!= (NODE*)NULL && p->number != num){ // allows q to be one node behind p
	q = p;
	p = p->next;
    }
    if (p == (NODE*)NULL){ // if the group size is not found
	printf("No group size available for %d people\n",num);
	return;
    }
    if (p == head && p != tail && p->number == num){ // if p is at the head but p is not in the tail
	head = p->next;
	free(p);
	return;
    }
    if (p == head && p == tail && p->number == num){ //if there is only one node
	p = head = tail = NULL;
	return;
    }
    if (p->number == num){ // when the number is found
	temp = p;
	q->next = p->next;
	p = p->next;
	free(temp);
	return;
    }
    else{
	q->next= p->next;
    }
    free (p);
    return;
}

void list(void){ // lists out the names and group size
    NODE *p;
    if (head == (NODE*)NULL){
	printf("The list is empty\n");
	return;
    }
    p = head;
    while (p != (NODE*)NULL){ // traverses through the linked list
	printf("Name: %s, Group Size: %d\n", p->name, p->number);
	p = p->next;
    }
    return;
}
void checksizes (void){ // check if the size inputed is any of the group sizes in the linked list 
    int input3;
    NODE *p;
    printf("Enter a size\n");
    scanf("%d", &input3);
    p = head;
    while (p != (NODE*)NULL){
	if (p->number == input3){
	    printf("Names: %s\n", p->name);
	    printf("Group Size: %d\n", p->number);
	}
	p = p->next;
    }
}

int checkduplicates (char *names){ //checks if the name inputed is already in the linked list
    NODE *p;
    p = head;
    while (p != (NODE*)NULL){
	if (strcmp (names, p->name) == 0){ //checks for duplicates
	    return 1;    
	}
	p = p->next;		
    }
    return 0;
}
void read(char *filename){ //reads the file and puts the names and numbers in the linked list 
    char name3[20];
    int size3;
    FILE *fp;
    fp = fopen("filename.txt","r"); //creates the text file
    if (fp == NULL){
	printf("Error");
	return;
    }
    while ((fscanf(fp, "%s %d \n", name3, &size3)) == 2){ //runs through the text file
	add(name3,size3);
    } 
    
    fclose(fp);
}
void save (char *filename){ //prints the names and numbers in the linked list into the text file
    char name3[20];
    int size3;
    NODE *p;
    p = head;

    FILE *fp;
    fp = fopen("filename.txt","w"); //opens the text file
    if (fp == NULL){
	printf("Error");
	return;
    }
    while(p != NULL){ //runs through the linked list
	fprintf(fp, "%s %d\n", p->name, p->number);
	p = p->next;
    }
    fclose(fp); //closes the text file
}
