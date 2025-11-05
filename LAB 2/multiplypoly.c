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
    if (c == 0) return;
    struct Term* term = createTerm(c, e);
    if (*head == NULL) {
        *head = term;
        return;
    }
    struct Term* temp = *head;
    struct Term* prev = NULL;
    while (temp && temp->exp > e) {
        prev = temp;
        temp = temp->next;
    }
    if (temp && temp->exp == e) {
        temp->coeff += c;
        if (temp->coeff == 0) {
            if (prev) prev->next = temp->next;
            else *head = temp->next;
            free(temp);
        }
        free(term);
    } else {
        if (prev == NULL) {
            term->next = *head;
            *head = term;
        } else {
            term->next = prev->next;
            prev->next = term;
        }
    }
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

struct Term* multiplyPolynomials(struct Term* p1, struct Term* p2) {
    struct Term* result = NULL;
    for (struct Term* a = p1; a != NULL; a = a->next) {
        for (struct Term* b = p2; b != NULL; b = b->next) {
            int newCoeff = a->coeff * b->coeff;
            int newExp = a->exp + b->exp;
            appendTerm(&result, newCoeff, newExp);
        }
    }
    return result;
}

int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;

    appendTerm(&poly1, 3, 2);
    appendTerm(&poly1, 2, 1);
    appendTerm(&poly1, 1, 0);

    appendTerm(&poly2, 1, 1);
    appendTerm(&poly2, 1, 0);

    printf("Poly 1: ");
    displayPoly(poly1);

    printf("Poly 2: ");
    displayPoly(poly2);

    struct Term* result = multiplyPolynomials(poly1, poly2);

    printf("Product: ");
    displayPoly(result);

    return 0;
}
