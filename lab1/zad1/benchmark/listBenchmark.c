#include "../lib/liblist.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
#ifdef DYNAMIC

    void *handle = dlopen("lib_shared.so", RTLD_LAZY);
    char *error;
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();

    void (*print_times)(clock_t, tms*, tms*)=dlsym(handle, "print_times");
    Node* (*initList)(Person*) = dlsym(handle, "initList");
    Node*(*pushFront)(Node*, Person*) = dlsym(handle, "pushFront");
    Node*(*removeList)(Node*)=dlsym(handle, "removeList");
    Node*(*removeElementFromList)(Node*,Node*)=dlsym(handle, "removeElementFromList");
    Node*(*sortList)(Node*)=dlsym(handle, "sortList");

    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

#endif

    tms tms_start;
    tms tms_interval;
    clock_t clock_end, clock_start;
    clock_start = clock();
    clock_end = clock();
    times(&tms_start);
    times(&tms_interval);

    printf("First checkpoint. Beginning of the program\n");
    printf("---------------------------\n");
    print_times(clock_end - clock_start, &tms_start, &tms_interval);
    printf("---------------------------\n");


    Person *person = (Person *) malloc(sizeof(Person));
    person->first_name = "Jan";
    person->last_name = "Sobieski";
    Node *listHead = initList(person);
    Person *secondPerson = (Person *) malloc(sizeof(Person));
    secondPerson->first_name = "Stefan";
    secondPerson->last_name = "Batory";
    pushFront(listHead, secondPerson);
    Person *thirdPerson = (Person *) malloc(sizeof(Person));
    thirdPerson->first_name = "Boleslaw";
    thirdPerson->last_name = "Chrobry";
    pushFront(listHead, thirdPerson);
    Person *fourthPerson = (Person *) malloc(sizeof(Person));
    fourthPerson->first_name = "Henryk";
    fourthPerson->last_name = "Walezy";
    pushFront(listHead, fourthPerson);

    printf("Second checkpoint. After generating the list\n");
    printf("---------------------------\n");
    clock_t clock_interval = clock();
    times(&tms_interval);
    print_times(clock_interval - clock_start, &tms_start, &tms_interval);
    printf("---------------------------\n");

    Person *toRemove = (Person *) malloc(sizeof(Person));
    toRemove->first_name = "Stefan";
    toRemove->last_name = "Batory";
    Node *nodeToRemove = initList(toRemove);

    listHead = removeElementFromList(listHead, nodeToRemove);
    printf("Third checkpoint. After removing a element \n");
    printf("---------------------------\n");
    clock_interval = clock();
    times(&tms_interval);
    print_times(clock_interval - clock_start, &tms_start, &tms_interval);
    printf("---------------------------\n");

    listHead = sortList(listHead);

    printf("Fourth checkpoint. After sorting the list \n");
    printf("---------------------------\n");
    clock_interval = clock();
    times(&tms_interval);
    print_times(clock_interval - clock_start, &tms_start, &tms_interval);
    printf("---------------------------\n");

    removeList(listHead);
    printf("Last checkpoint. After deleting the list :\n");
    printf("---------------------------\n");
    clock_interval = clock();
    times(&tms_interval);
    print_times(clock_interval - clock_start, &tms_start, &tms_interval);

#ifdef DYNAMIC
    dlclose(handle);
#endif

    return 0;
}
