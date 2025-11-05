#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int digit;
    struct Node* next;
};

struct Node* createNode(int digit) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->digit = digit;
    newNode->next = NULL;
    return newNode;
}

void insertAtHead(struct Node** head, int digit) {
    struct Node* newNode = createNode(digit);
    newNode->next = *head;
    *head = newNode;
}

void insertAtTail(struct Node** head, int digit) {
    struct Node* newNode = createNode(digit);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void reverseList(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* curr = *head;
    struct Node* next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

struct Node* readNumber(char num[]) {
    struct Node* head = NULL;
    int len = strlen(num);
    for (int i = len - 1; i >= 0; i--) {
        insertAtTail(&head, num[i] - '0');
    }
    return head;
}

int compare(struct Node* num1, struct Node* num2) {
    int len1 = 0, len2 = 0;
    struct Node* t1 = num1; 
    struct Node* t2 = num2;
    while (t1) { len1++; t1 = t1->next; }
    while (t2) { len2++; t2 = t2->next; }
    if (len1 > len2) return 1;
    if (len2 > len1) return -1;

    reverseList(&num1);
    reverseList(&num2);
    t1 = num1; t2 = num2;
    while (t1 && t2) {
        if (t1->digit > t2->digit) { reverseList(&num1); reverseList(&num2); return 1; }
        if (t1->digit < t2->digit) { reverseList(&num1); reverseList(&num2); return -1; }
        t1 = t1->next; t2 = t2->next;
    }
    reverseList(&num1); reverseList(&num2);
    return 0;
}

struct Node* subtract(struct Node* num1, struct Node* num2, int* negative) {
    *negative = 0;
    int cmp = compare(num1, num2);
    if (cmp == 0) {
        return createNode(0);
    }
    if (cmp < 0) {
        struct Node* temp = num1;
        num1 = num2;
        num2 = temp;
        *negative = 1;
    }

    struct Node* result = NULL;
    struct Node* t1 = num1;
    struct Node* t2 = num2;
    int borrow = 0;

    while (t1) {
        int d1 = t1->digit - borrow;
        int d2 = (t2) ? t2->digit : 0;
        if (d1 < d2) {
            d1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        insertAtTail(&result, d1 - d2);
        t1 = t1->next;
        if (t2) t2 = t2->next;
    }

    reverseList(&result);
    while (result && result->digit == 0 && result->next) {
        struct Node* temp = result;
        result = result->next;
        free(temp);
    }
    reverseList(&result);

    return result;
}

void printNumber(struct Node* head, int negative) {
    reverseList(&head);
    if (negative) printf("-");
    struct Node* temp = head;
    while (temp) {
        printf("%d", temp->digit);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    char num1[1000], num2[1000];
    printf("Enter first large number: ");
    scanf("%s", num1);
    printf("Enter second large number: ");
    scanf("%s", num2);

    struct Node* n1 = readNumber(num1);
    struct Node* n2 = readNumber(num2);
    int negative;
    struct Node* diff = subtract(n1, n2, &negative);
    printf("Difference: ");
    printNumber(diff, negative);

    return 0;
}
