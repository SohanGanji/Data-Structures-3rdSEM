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

struct Node* multiply(struct Node* num1, struct Node* num2) {
    int arr[2000] = {0};
    int i = 0, j = 0;

    struct Node* t1 = num1;
    while (t1) {
        j = 0;
        struct Node* t2 = num2;
        while (t2) {
            arr[i + j] += t1->digit * t2->digit;
            if (arr[i + j] >= 10) {
                arr[i + j + 1] += arr[i + j] / 10;
                arr[i + j] %= 10;
            }
            t2 = t2->next;
            j++;
        }
        t1 = t1->next;
        i++;
    }

    int size = i + j;
    while (size > 1 && arr[size - 1] == 0) size--;

    struct Node* result = NULL;
    for (int k = size - 1; k >= 0; k--) {
        insertAtTail(&result, arr[k]);
    }
    return result;
}

void printNumber(struct Node* head) {
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
    struct Node* product = multiply(n1, n2);
    printf("Product: ");
    printNumber(product);

    return 0;
}
