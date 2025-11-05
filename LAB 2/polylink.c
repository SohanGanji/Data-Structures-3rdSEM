#include <stdio.h>
#include <stdlib.h>

struct Term {
    int coeff;
    int exp;
    struct Term* next;
};

struct Term* createTerm(int c, int e) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    newTerm->coeff = c;
    newTerm->exp = e;
    newTerm->next = NULL;
    return newTerm;
}

void appendTerm(struct Term** head, int c, int e) {
    struct Term* term = createTerm(c, e);
    if (*head == NULL) {
        *head = term;
        return;
    }
    struct Term* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = term;
}

void displayPoly(struct Term* head) {
    while (head != NULL) {
        if (head->coeff != 0) {
            if (head != NULL && head != head->next) {
                if (head->coeff > 0 && head != head->next)
                    printf("+");
            }
            if (head->exp == 0)
                printf("%d", head->coeff);
            else if (head->exp == 1)
                printf("%dx", head->coeff);
            else
                printf("%dx^%d", head->coeff, head->exp);
        }
        head = head->next;
        if (head != NULL && head->coeff >= 0)
            printf(" ");
    }
    printf("\n");
}


int main() {
    struct Term* poly = NULL;
    appendTerm(&poly, 4, 3);
    appendTerm(&poly, 2, 1);
    appendTerm(&poly, 5, 0);
    displayPoly(poly);
    return 0;
}
