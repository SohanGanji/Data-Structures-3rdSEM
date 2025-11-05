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

struct Term* addPolynomials(struct Term* p1, struct Term* p2) {
    struct Term* result = NULL;
    struct Term** last = &result;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp > p2->exp) {
            *last = createTerm(p1->coeff, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            *last = createTerm(p2->coeff, p2->exp);
            p2 = p2->next;
        } else {
            int sum = p1->coeff + p2->coeff;
            if (sum != 0)
                *last = createTerm(sum, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
        if (*last)
            last = &((*last)->next);
    }

    while (p1 != NULL) {
        *last = createTerm(p1->coeff, p1->exp);
        last = &((*last)->next);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        *last = createTerm(p2->coeff, p2->exp);
        last = &((*last)->next);
        p2 = p2->next;
    }

    return result;
}

int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;

    appendTerm(&poly1, 5, 3);
    appendTerm(&poly1, 4, 1);
    appendTerm(&poly1, 2, 0);

    appendTerm(&poly2, 3, 3);
    appendTerm(&poly2, -4, 1);
    appendTerm(&poly2, 6, 0);

    printf("Poly 1: ");
    displayPoly(poly1);

    printf("Poly 2: ");
    displayPoly(poly2);

    struct Term* result = addPolynomials(poly1, poly2);

    printf("Sum: ");
    displayPoly(result);

    return 0;
}
