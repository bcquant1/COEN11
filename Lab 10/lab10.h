
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
void writefile (char *, int);
void readfile(char *, int);
extern NODE *head;
extern NODE *tail;
extern pthread_mutex_t  mutex;
