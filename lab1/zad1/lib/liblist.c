#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liblist.h"
#include <time.h>
#include <unistd.h>
#include <sys/times.h>

void print_times(clock_t real, tms *tms_start, tms *tms_end) {
    long clk = sysconf(_SC_CLK_TCK);
    double clktck = (double) (clk);
    printf("Real time: %f\n", real / (double) (CLOCKS_PER_SEC));
    printf("User time: %f\n", (tms_end->tms_utime - tms_start->tms_utime / clktck));
    printf("System time : %f\n", tms_end->tms_stime - tms_start->tms_stime / clktck);
}

void printPerson(Person *person) {
    if (person != NULL) {
        printf("first_name: %s \n", person->first_name);
        printf("last_name: %s \n", person->last_name);
        printf("day_of_birth: %d \n", person->day_of_birth);
        printf("month_of_birth: %d \n", person->month_of_birth);
        printf("year_of_birth: %d \n", person->year_of_birth);
        printf("email: %s \n", person->email);
        printf("phone_number: %s \n", person->phone_number);
        printf("address: %s \n", person->address);
    }
    else {
        printf("No such person \n");
    }
}

void printList(Node *listHead) {
    Node *tmpHead = (Node *) malloc(sizeof(Node));
    tmpHead = listHead;
    while (tmpHead != NULL) {
        printf("----------------------------\n");
        printPerson(tmpHead->person);
        tmpHead = tmpHead->next;
    }
}

Node *initList(Person *person) {
    Node *listHead;
    listHead = (Node *) malloc(sizeof(Node));
    listHead->person = person;
    listHead->next = NULL;
    listHead->previous = NULL;
    return listHead;
}

int compareTwoPeopleByName(Person *person1, Person *person2) {
    if (person1->first_name != NULL && person2->last_name != NULL
        && person1->first_name == person2->first_name &&
        person1->last_name && person2->last_name)
        return 1;
    else return 0;
}

Node *pushFront(Node *listHead, Person *person) {
    Node *newListHead = initList(person);
    if (listHead != NULL) {
        listHead->previous = newListHead;
    }
    newListHead->previous = NULL;
    newListHead->next = listHead;
    return newListHead;
}

Node *findElement(Node *listHead, Person *person) {
    Node *newListHead = (Node *) malloc(sizeof(Node));
    newListHead = listHead;
    while (newListHead != NULL) {
        if (compareTwoPeopleByName(newListHead->person, person) == 1) {
            return newListHead;
        }
        newListHead = newListHead->next;
    }
    return NULL;
}

Node *removeList(Node *listHead) {
    Node *current = listHead;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    listHead = NULL;
    return listHead;
}

Node *removeElementFromList(Node *listHead, Node *toRemove) {
    if (toRemove == NULL) {
        return listHead;
    }
    if (toRemove->person == NULL) {
        return listHead;
    }

    Node *first = (Node *) malloc(sizeof(Node));
    Node *second = (Node *) malloc(sizeof(Node));
    first = listHead;
    second = listHead;
    while (second != NULL) {
        if (compareTwoPeopleByName(second->person, toRemove->person) == 1) {
            // found element is first in the list
            if (second->previous == NULL) {
                listHead = second->next;
                free(second->person);
                free(second);
                return listHead;
            }

            // found element is in the middle of the list
            if (second->previous != NULL && second->next != NULL) {
                first = second->previous;
                first->next = second->next;
                free(second->person);
                free(second);
                return listHead;
            }

            // found element is the last one in the list
            if (second->next == NULL) {
                first = second->previous;
                first->next = NULL;
                free(second->person);
                free(second);
                return listHead;
            }
        }
        second = second->next;
    }
    return listHead;
}

int lastNameComparator(Person *person1, Person *person2) {
    if (person1 != NULL && person2 != NULL && person1->last_name != NULL &&
        person2->last_name != NULL) {
        return strcmp(person1->last_name, person2->last_name);
    }
    return 0;
}

Node *sortList(Node *listHead) {
    Node *newListHead = (Node *) malloc(sizeof(Node));
    newListHead = listHead;
    Node *temp1 = (Node *) malloc(sizeof(Node));
    Node *temp = (Node *) malloc(sizeof(Node));
    Person *person = (Person *) malloc(sizeof(Person));

    if (listHead == NULL) {
        return NULL;
    }

    for (temp1 = listHead; temp1 != NULL; temp1 = temp1->next) {
        for (temp = temp1->next; temp != NULL; temp = temp->next) {
            if (strcmp(temp1->person->last_name, temp->person->last_name) > 0) {
                person = temp1->person;
                temp1->person = temp->person;
                temp->person = person;
            }
        }
    }
    free(person);
    free(temp1);
    free(temp);
    return newListHead;
}