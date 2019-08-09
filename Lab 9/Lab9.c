//Brandon Quant
//COEN 11 Lab #9

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct node{
    int number;
    char name[20];
    struct node *next;
}NODE;

void add(char *, int);
void cancel(int);
void list (void);
void checksizes(void);
int checkduplicates (char *);
void readtext (char *);
void save (char *);
void listbackwards (NODE *p);
void namebackwards (char *);
void deleteall (NODE *p);
void* auto_save (void *);
void read_auto (char *);

NODE *head = (NODE*)NULL;
NODE *tail = (NODE*)NULL;
pthread_mutex_t  mutex;

int main(int argc, char *argv[]){
    int num;
    int input;
    int i;
    char name2[20];
    int size;
    int count = 0;
    NODE *p;
    if (argc == 1){
	printf("The name of the file is missing\n");
	return 1;
    }
    pthread_t thr;
    pthread_mutex_init (&mutex, NULL);
    pthread_create(&thr, NULL, auto_save, (void *) argv[2]);
    readtext (argv[1]);
    while (1){ //keeps running until case 9 is chosen
	printf("Press 1 to be added to the waiting list\n");
	printf("Press 2 to cancel\n");
	printf("Press 3 to list the waiting list\n");
	printf("Press 4 to check sizes\n");
	printf("Press 5 to reverse the list\n");
	printf("Press 6 to reverse the names in the list\n");
	printf("Press 7 to print the names\n");
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
	    case 5:
		listbackwards(head);
		break;
	    case 6:
		p = head;
		while (p != NULL){
		    namebackwards(p->name);
		    printf("\n");
		    p = p->next;
		}
		break;
	    case 7:
		read_auto(argv[2]);
		break;
	    case 9:
		pthread_mutex_lock(&mutex);
		pthread_cancel(thr);
		pthread_mutex_unlock(&mutex);
		save(argv[1]);
		deleteall(head);
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
void readtext(char *filename){ //reads the file and puts the names and numbers in the linked list 
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
    fp = fopen(filename,"w"); //opens the text file
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
void listbackwards (NODE *p){
	if (p == NULL){ 
	    return;
	}
	listbackwards(p->next); //calling listbackwards at the next node in the linked list

	printf("Names: %s", p->name);
	printf(" Group Size: %d\n", p->number);
}
void namebackwards (char *name){
    if (*name == '\0'){ //checks when *name is at the end of the string
	return;
    } 
    namebackwards(name+1); //calling namebackwards at the next character
    printf("%c", *name);
}
void deleteall(NODE *p){
    if (p == NULL){
	return;
    }    
    deleteall(p->next); //calling deleteall at the next node in the linked list
    free (p);
}
void* auto_save (void *filename){ //saves the nodes in the linked list into a binary file
    FILE *fp;
    NODE *p;
    while (1){
	p = head;
	pthread_mutex_lock(&mutex); //locks
	if ((fp = fopen(filename,"wb"))== NULL){
	    printf("Error\n");
	}
	while (p != NULL){ // traversing through the linked list
	    fwrite(p, sizeof(NODE), 1, fp); 
	    p = p->next;
	}
	fclose(fp);
	pthread_mutex_unlock(&mutex); //unlock
	sleep(15); //sleep for 15 seconds
    }	
    return NULL;
}
void read_auto (char *filename){ // prints out all the names in the binary file
    FILE *fp;
    NODE temp;
    char name[20];
    pthread_mutex_lock(&mutex); //lock
    if ((fp = fopen(filename ,"rb")) == NULL){
	printf("Error\n");
	return;
    }
    while ((fread(&temp, sizeof(NODE), 1, fp) == 1)){	//running through the binary file
	    printf("Names: %s\n", temp.name);
	    printf("Group Size: %d\n", temp.number);
    }
    fclose(fp);
    pthread_mutex_unlock(&mutex); //unlock
    return;
}
