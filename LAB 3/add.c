#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int digit;
    struct Node* next;
};

struct Node* createNode(int digit) {
    struct Node* n = malloc(sizeof(struct Node));
    n->digit = digit;
    n->next = NULL;
    return n;
}

void insertAtTail(struct Node** head, int digit) {
    struct Node* newNode = createNode(digit);
    if (!*head) { *head = newNode; return; }
    struct Node* temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

struct Node* stringToList(char* num) {
    struct Node* head = NULL;
    for (int i = strlen(num) - 1; i >= 0; i--)
        insertAtTail(&head, num[i] - '0');
    return head;
}

struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL, *curr = head;
    while (curr) {
        struct Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void printList(struct Node* head) {
    head = reverseList(head);
    while (head) { printf("%d", head->digit); head = head->next; }
    printf("\n");
}

struct Node* addLists(struct Node* n1, struct Node* n2) {
    struct Node* result = NULL;
    int carry = 0;
    while (n1 || n2 || carry) {
        int sum = carry;
        if (n1) { sum += n1->digit; n1 = n1->next; }
        if (n2) { sum += n2->digit; n2 = n2->next; }
        carry = sum / 10;
        insertAtTail(&result, sum % 10);
    }
    return result;
}

int main() {
    char a[1000], b[1000];
    printf("Enter first large number: ");
    scanf("%s", a);
    printf("Enter second large number: ");
    scanf("%s", b);

    struct Node* num1 = stringToList(a);
    struct Node* num2 = stringToList(b);

    struct Node* sum = addLists(num1, num2);
    printf("Sum: ");
    printList(sum);
}
