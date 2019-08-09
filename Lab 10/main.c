#include "lab10.h"

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
    readfile (argv[1],atoi(argv[3]));
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
		writefile(argv[1],atoi(argv[3]));
		deleteall(head);
		return 0;
		break;
	    default:
		printf("Enter a valid number.\n");
	}
    }
}

