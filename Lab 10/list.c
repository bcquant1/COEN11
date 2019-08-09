#include "lab10.h"

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
