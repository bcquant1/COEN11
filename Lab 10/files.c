#include "lab10.h"

void readtext(char *filename){ //reads the file and puts the names and numbers in the linked list 
    char name3[20];
    int size3;
    FILE *fp;
    fp = fopen(filename,"r"); //creates the text file
    if (fp == NULL){
	printf("Error");
	return;
    }
    while ((fscanf(fp, "%s%d \n", name3, &size3)) == 2){ //runs through the text file
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
	fprintf(fp, "%s\t%d\n", p->name, p->number);
	p = p->next;
    }
    fclose(fp); //closes the text file
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

void writefile (char *filename, int key){ //encrypts the linked list and writes to the text file
    char *t;
    char temp[20];
    NODE *p = head;
    FILE *fp;
    fp = fopen(filename, "w") //creates the file;
    if (fp == NULL){
	printf("Error\n");
	return;
    }
    while (p != NULL){
	sprintf(temp, "%s\t%d\n", p->name, p->number);
	t = temp;
	while (*t != '\n'){ //encrypts
	    *t = *t ^ key;
	    t++;    
	}
	fprintf(fp, "%s", temp); //printing to the text file
	p= p->next;
    }
    fclose(fp);
    
}
void readfile (char *filename, int key){ //decrypts the text file and writes to the linked list
    char temp[20];
    FILE *fp;
    char *t;
    char name[20];
    int size;
    fp = fopen(filename,"r"); //creates the text file
    if (fp == NULL){
	printf("Error");
	return;
    }
    while ((fgets(temp, 20, fp) != NULL)){ 
	t = temp;
	while (*t != '\n'){ //decrypts
	    *t = *t ^ key;
	    t++;
	}
	sscanf(temp, "%s\t%d\n",name,&size); //runs through the text file
	add(name,size);
    } 
    fclose(fp);

}

