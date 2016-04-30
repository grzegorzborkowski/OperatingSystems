#include "../lib/minunit.h"
#include "../lib/liblist.c"
#include <string.h>

int tests_run = 0;

static char *test_removeList() {
    Node *head = (Node *) malloc(sizeof(Node));
    head->next = (Node *) malloc(sizeof(Node));
    head = removeList(head);
    mu_assert("Error in test_removeList", head == NULL);
    return 0;
}

static char *test_initList_existingPersonEmptyEmail() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    Node *testListHead = initList(testPerson);
    mu_assert("error in initList_existingPersonEmptyEmail", testListHead->person->email == 0);
    removeList(testListHead);
    return 0;
}

static char *test_initList_existingPersonLastName() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    testPerson->last_name = "Kowalsky";
    Node *testListHead = initList(testPerson);
    mu_assert("error in initList_existingPersonLastName",
              strcmp(testListHead->person->last_name, "Kowalsky") == 0);
    removeList(testListHead);
    return 0;
}

static char *test_pushFront_newPersonToEmptyList() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    testPerson->first_name = "John";
    testPerson->last_name = "Kowalsky";
    testPerson->address = "Walbrzych";
    Node *testListHead = pushFront(NULL, testPerson);

    mu_assert("error in pushFront_newPersonToEmptyList",
              strcmp(testListHead->person->first_name, "John") == 0 );
    removeList(testListHead);
    return 0;
}

static char *test_pushFront_newPersonToExistingList() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    testPerson->first_name = "John";
    testPerson->last_name = "Kowalsky";
    testPerson->address = "Walbrzych";
    Node *testListHead = initList(testPerson);

    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    testPerson2->first_name = "Wladimir";
    testPerson2->last_name = "Nowak";
    testPerson2->address = "Wroclaw";

    testListHead = pushFront(testListHead, testPerson2);
    mu_assert("error in pushFront_newPersonToExistingList",
              strcmp(testListHead->person->first_name,"Wladimir") == 0);
    removeList(testListHead);
    return 0;
}

static char *test_pushFront_newPersonToExisitingListPointersTests() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    testPerson->first_name = "John";
    testPerson->last_name = "Kowalsky";
    testPerson->address = "Walbrzych";
    Node *testListHead = initList(testPerson);

    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    testPerson2->first_name = "Wladimir";
    testPerson2->last_name = "Nowak";
    testPerson2->address = "Wroclaw";

    testListHead = pushFront(testListHead, testPerson2);
    mu_assert("error in pushFront_newPersonToExistingListPointersTests",
              testListHead == testListHead->next->previous);
    removeList(testListHead);
    return 0;
}

static char *test_CompareTwoPeopleByName_EmptyObjects() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    mu_assert("error in compareTwoPeopleByName_EmptyObjects", compareTwoPeopleByName(testPerson, testPerson2) == 0);
    free(testPerson);
    free(testPerson2);
    return 0;
}

static char *test_CompareTwoPeopleByName_SameEmptyObject() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    mu_assert("error in compareTwoPeopleByName_SameEmptyObject", compareTwoPeopleByName(testPerson, testPerson) == 0);
    free(testPerson);
    return 0;
}

static char *test_CompareTwoPeopleByName_DifferentNotEmptyObject() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    testPerson->first_name = "Marian";
    testPerson2->last_name = "Zenek";
    mu_assert("error in compareTwoPeopleByName_DifferenNotEmptyObject",
              compareTwoPeopleByName(testPerson, testPerson2) == 0);
    free(testPerson);
    free(testPerson2);
    return 0;
}

static char *test_CompareTwoPeopleByName_SameNotEmptyObject() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    testPerson->first_name = "Marian";
    testPerson->last_name = "Kowalski";
    testPerson2->first_name = "Marian";
    testPerson2->last_name = "Kowalski";
    mu_assert("error in compareTwoPeopleByName_SameNotEmptyObject",
              compareTwoPeopleByName(testPerson, testPerson2) == 1);
    free(testPerson);
    free(testPerson2);
    return 0;
}

static char *test_findElement_ElementExists() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    Person *testPerson3 = (Person *) malloc(sizeof(Person));

    Person *elementToFind = (Person *) malloc(sizeof(Person));
    testPerson->first_name = "Abdel";
    testPerson->last_name = "Akacja";
    testPerson2->first_name = "Boguslaw";
    testPerson2->last_name = "Bluszcz";
    testPerson3->first_name = "Cezary";
    testPerson3->last_name = "Czomber";

    elementToFind->first_name = "Abdel";
    elementToFind->last_name = "Akacja";

    Node *list = initList(testPerson);
    list = pushFront(list, testPerson2);
    list = pushFront(list, testPerson3);

    mu_assert("error in findElement_ElementExists", findElement(list, elementToFind) != 0);
    removeList(list);
    free(elementToFind);
    return 0;
}

static char *test_findElement_ElementDoesNotExist() {
    Person *testPerson = (Person *) malloc(sizeof(Person));
    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    Person *testPerson3 = (Person *) malloc(sizeof(Person));

    Person *elementToFind = (Person *) malloc(sizeof(Person));
    testPerson->first_name = "Abdel";
    testPerson->last_name = "Akacja";
    testPerson2->first_name = "Boguslaw";
    testPerson2->last_name = "Bluszcz";
    testPerson3->first_name = "Cezary";
    testPerson3->last_name = "Czomber";

    elementToFind->first_name = "Dionizy";
    elementToFind->last_name = "Dab";

    Node *list = initList(testPerson);
    list = pushFront(list, testPerson2);
    list = pushFront(list, testPerson3);

    mu_assert("error in findElement_ElementDoesNotExist", findElement(list, elementToFind) == 0);
    removeList(list);
    free(elementToFind);
    return 0;
}

static char *test_removeElementFromList_emptyElementFromExistingList() {
    Node *emptyNode = (Node *) malloc(sizeof(Node));

    Person *testPerson1 = (Person *) malloc(sizeof(Person));
    testPerson1->first_name = "John";
    testPerson1->last_name = "Kowalsky";
    testPerson1->address = "Walbrzych";
    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    testPerson2->first_name = "Wladimir";
    testPerson2->last_name = "Nowak";
    testPerson2->address = "Wroclaw";


    Node *testListHead = initList(testPerson1);
    testListHead = pushFront(testListHead, testPerson2);

    Node *listAfterRemoval = removeElementFromList(testListHead, emptyNode);

    mu_assert("error in removeElementFromList_emptyElementFromExistingList",
              testListHead == listAfterRemoval);
    removeList(listAfterRemoval);
    return 0;
}

static char *test_removeElementFromList_firstElement() {
    Person *testPerson1 = (Person *) malloc(sizeof(Person));
    testPerson1->first_name = "John";
    testPerson1->last_name = "Kowalsky";
    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    testPerson2->first_name = "Wladimir";
    testPerson2->last_name = "Nowak";

    Node *testListHead = initList(testPerson1);
    testListHead = pushFront(testListHead, testPerson2);

    Node *secondNode = testListHead->next;

    Person *removePerson = (Person *) malloc(sizeof(Person));
    removePerson->first_name = "Wladimir";
    removePerson->last_name = "Nowak";
    Node *nodeToRemove = (Node *) malloc(sizeof(Node));
    nodeToRemove->person = removePerson;
    nodeToRemove->previous = NULL;
    nodeToRemove->next = secondNode;

    Node *listAfterRemoval = removeElementFromList(testListHead, nodeToRemove);
    mu_assert("error in removeElementFromList_firstElement",
              strcmp(listAfterRemoval->person->first_name ,"John") == 0);
    removeList(listAfterRemoval);
    free(removePerson);
    return 0;
}

static char *test_removeElementFromList_middleElement() {
    Person *testPerson1 = (Person *) malloc(sizeof(Person));
    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    Person *testPerson3 = (Person *) malloc(sizeof(Person));

    testPerson1->first_name = "Zbigniew";
    testPerson1->last_name = "Ostatek";

    testPerson2->first_name = "Wladimir";
    testPerson2->last_name = "Srodkowy";

    testPerson3->first_name = "Andrzej";
    testPerson3->last_name = "Pierwszy";

    Node *testListHead = initList(testPerson1);
    testListHead = pushFront(testListHead, testPerson2);
    testListHead = pushFront(testListHead, testPerson3);

    Node *nodeToRemove = (Node *) malloc(sizeof(Node));
    Person *removePerson = (Person *) malloc(sizeof(Person));
    removePerson->first_name = "Wladimir";
    removePerson->last_name = "Srodkowy";
    nodeToRemove->person = removePerson;
    nodeToRemove->previous = testListHead;
    nodeToRemove->next = testListHead->next->next;

    Node *listAfterRemoval = removeElementFromList(testListHead, nodeToRemove);
    mu_assert("error in testRemoveElementFromList_middleElement",
              strcmp(listAfterRemoval->next->person->first_name,"Zbigniew") == 0);
    removeList(listAfterRemoval);
    free(nodeToRemove);
    free(removePerson);
    return 0;
}

static char *test_removeElementFromList_lastElement() {
    Person *testPerson1 = (Person *) malloc(sizeof(Person));
    Person *testPerson2 = (Person *) malloc(sizeof(Person));
    Person *testPerson3 = (Person *) malloc(sizeof(Person));

    testPerson1->first_name = "Zbigniew";
    testPerson1->last_name = "Ostatek";

    testPerson2->first_name = "Wladimir";
    testPerson2->last_name = "Srodkowy";

    testPerson3->first_name = "Andrzej";
    testPerson3->last_name = "Pierwszy";

    Node *testListHead = initList(testPerson1);
    testListHead = pushFront(testListHead, testPerson2);
    testListHead = pushFront(testListHead, testPerson3);

    Node *secondNode = testListHead->next;

    Node *nodeToRemove = (Node *) malloc(sizeof(Node));
    Person *removePerson = (Person *) malloc(sizeof(Person));
    removePerson->first_name = "Zbigniew";
    removePerson->last_name = "Ostatek";
    nodeToRemove->person = removePerson;
    nodeToRemove->previous = secondNode;

    Node *listAfterRemoval = removeElementFromList(testListHead, nodeToRemove);
    mu_assert("error in testRemoveElementFromList_lastElement",
              listAfterRemoval->next->next == NULL);
    removeList(listAfterRemoval);
    free(nodeToRemove);
    free(removePerson);
    return 0;
}

static char *test_sortList() {
    return 0;
}

static char *all_tests() {
    mu_run_test(test_removeList);
    mu_run_test(test_initList_existingPersonEmptyEmail);
    mu_run_test(test_initList_existingPersonLastName);
    mu_run_test(test_pushFront_newPersonToEmptyList);
    mu_run_test(test_pushFront_newPersonToExistingList);
    mu_run_test(test_pushFront_newPersonToExisitingListPointersTests);
    mu_run_test(test_CompareTwoPeopleByName_EmptyObjects);
    mu_run_test(test_CompareTwoPeopleByName_SameEmptyObject);
    mu_run_test(test_CompareTwoPeopleByName_DifferentNotEmptyObject);
    mu_run_test(test_CompareTwoPeopleByName_SameNotEmptyObject);
    mu_run_test(test_findElement_ElementExists);
    mu_run_test(test_findElement_ElementDoesNotExist);
    mu_run_test(test_removeElementFromList_emptyElementFromExistingList);
    mu_run_test(test_removeElementFromList_firstElement);
    mu_run_test(test_removeElementFromList_middleElement);
    mu_run_test(test_removeElementFromList_lastElement);
    mu_run_test(test_sortList);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s", result);
    }
    else {
        printf("ALL UNITS TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}