#include <time.h>
#include <dlfcn.h>
#include <sys/times.h>

#ifndef listlib_header
#define listlib_header

struct Person {
    char *first_name;
    char *last_name;
    unsigned day_of_birth;
    unsigned month_of_birth;
    unsigned year_of_birth;
    char *email;
    char *phone_number;
    char *address;
};

struct Node {
    struct Node *previous;
    struct Node *next;
    struct Person *person;
};

typedef struct Person Person;
typedef struct Node Node;
typedef struct tms tms;

clock_t clock(void);
clock_t times(tms *buffer);

void print_times(clock_t, tms *, tms *);

void printPerson(Person *person);

void printList(Node *listHead);

Node *initList(Person *person);

int compareTwoPeopleByName(Person *person1, Person *person2);

Node *pushFront(Node *listHead, Person *person);

Node *generateDataIntoList(Node *listHead);

Node *findElement(Node *listHead, Person *person);

Node *removeList(Node *listHead);

Node *removeElementFromList(Node *listHead, Node *toRemove);

int lastNameComparator(Person *person1, Person *person2);

Node *sortList(Node *listHead);

#endif