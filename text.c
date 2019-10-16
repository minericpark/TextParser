/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int main() {

    FILE *fp;

    if ((fp = fopen("test.txt", "r+")) == NULL) {
        printf ("File could not be opened");
    }
    txt2words(fp);
    fclose(fp);

    return 0;
}

int isTypeOne (char checkSymbol) { /*String of char, num, -, '*/
    char *quote = "'";

    if (isdigit(checkSymbol) != 0 || isalpha(checkSymbol) != 0 || checkSymbol == '-' || checkSymbol == *quote) {
        return 1;
    }
    else {
        return 0;
    }
}

int isTypeTwo (char checkSymbol) { /*String of symbols*/

    if (isdigit(checkSymbol) == 0 && isalpha(checkSymbol) == 0) {
        if (checkSymbol != '-' && checkSymbol != ',' && checkSymbol != ' ') {
            return 1;
        }
        return 0;
    }
    else {
        return 0;
    }
}

void print_list (struct node_struct *head) {

    while (head->next) {
        printf ("%s\n", head->data);
        head = head->next;
    }

};

/*Split words and malloc for each, then place into linked list*/
/*Word is: continuous sequence of characters, numbers, single-hyphens, single apostrophes*/
/*Any contiguous sequence of identical punctuation symbols or*/
/*Blank line*/
/*Function reads text from file pointer one line at a time, split each line into words, allocate
 * a string for each word, storing the address of the string in the data pointer. Assemble
 * words in the original order (first word at head of list) into a linked list. Return pointer to first
 * node of linked list*/
struct node_struct *txt2words (FILE *fp) {

    printf ("Running txt2words function\n");
    struct node_struct *head, **ptr;
    char tempLine[256] = " ";
    char tempWord[265] = " ";
    char tempSym = ' ';
    int wordSize = 0;
    int i = 0;

    ptr = &head;
    while (fgets (tempLine, 256, fp) != NULL) {
        printf("%s\n", tempLine);

        for (i = 0; i < strlen(tempLine); i++) {
            if (isTypeOne(tempLine[i]) != 0) {
                if (wordSize > 0) {
                    if (isTypeOne(tempLine[i-1]) != 1) {
                        *ptr = malloc( sizeof( struct node_struct ) );
                        (*ptr)->data = malloc (strlen(tempWord) + 1);
                        strcpy((*ptr)->data, tempWord);
                        ptr = &((*ptr)->next);
                        printf("\n word: %s", tempWord);
                        printf ("\nwordSize: %d\n", wordSize);
                        memset(tempWord, 0, strlen(tempWord));
                        wordSize = 0;
                    }
                    else {
                        wordSize++;
                    }
                }
                else {
                    wordSize++;
                }
                tempWord[wordSize] = tempLine[i];
            } else if (isTypeTwo(tempLine[i]) != 0) {
                if (wordSize > 0) {
                    if (isTypeTwo(tempLine[i-1]) != 1 || tempLine[i-1] != tempLine[i]) {
                        *ptr = malloc( sizeof( struct node_struct ) );
                        (*ptr)->data = malloc (strlen(tempWord) + 1);
                        strcpy((*ptr)->data, tempWord);
                        ptr = &((*ptr)->next);
                        printf("\n word: %s", tempWord);
                        printf ("\nwordSize: %d\n", wordSize);
                        memset(tempWord, 0, strlen(tempWord));
                        wordSize = 0;
                    }
                    else {
                        wordSize++;
                    }
                }
                else {
                    wordSize++;
                }
                tempWord[wordSize] = tempLine[i];
            } else if (strcmp(tempLine,"\n") != 0){ /*Newline*/
                *ptr = malloc( sizeof( struct node_struct ) );
                (*ptr)->data = malloc (strlen(tempWord) + 1);
                strcpy((*ptr)->data, tempWord);
                ptr = &((*ptr)->next);
                printf("\n word: %s", tempWord);
                printf ("\nwordSize: %d\n", wordSize);
                memset(tempWord, 0, strlen(tempWord));
                wordSize = 0;
                tempWord[wordSize] = tempLine[i];
            }
            else {
                *ptr = malloc( sizeof( struct node_struct ) );
                (*ptr)->data = malloc (strlen(tempWord) + 1);
                strcpy((*ptr)->data, tempWord);
                ptr = &((*ptr)->next);
                printf("\n word: %s", tempWord);
                printf ("\nwordSize: %d\n", wordSize);
                memset(tempWord, 0, strlen(tempWord));
                wordSize = 0;
                tempWord[wordSize] = tempLine[i];
            }
        }
    }
    printf("\n word: %s", tempWord);
    printf ("\nwordSize: %d\n", wordSize);
    memset(tempWord, 0, strlen(tempWord));
    wordSize = 0;
    *ptr = NULL;

    print_list(head);

    return head;
}

/*

struct node_struct *search (struct node_struct *list, char *target, int (*compar)(const void *, const void *)) {

}

struct node_struct *copy (struct node_struct *start, struct node_struct *end) {

}

void ftext (FILE *fp, struct node_struct *list) {

}

struct node_struct *sort (struct node_struct *list, int (*compar)(const void *, const void *)) {

}

void remove_repeats (struct node_struct *list, int (*compar)(const void *, const void *)) {

}

int length (struct node_struct *list) {

    return 0;
}

void free_list (struct node_struct *list, int free_data) {


}*/