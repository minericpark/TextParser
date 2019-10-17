/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {

    FILE *fp;
    struct node_struct *head, *sHead, *test1;

    if ((fp = fopen("test.txt", "r+")) == NULL) {
        printf ("File could not be opened");
    }
    head = txt2words(fp);
    print_list(head, 0);
    sHead = search(head, "EBook", strcmpvoid);
    print_list(sHead, 1);
    free_list(sHead, 1);
    free_list(head, 1);
    fclose(fp);

    return 0;
}

int isTypeOne (char checkSymbol) { /*Verifies if char is char, num, -, ' : 1 for true, 0 for false*/
    char *quote = "'";

    if (isdigit(checkSymbol) != 0 || isalpha(checkSymbol) != 0 || checkSymbol == '-' || checkSymbol == *quote) {
        return 1;
    }
    else {
        return 0;
    }
}

int isTypeTwo (char checkSymbol) { /*Verifies if char is symbol excluding some exceptions (e.g. -, ' ', '\n'): 1 for true, 0 for false*/

    if (isdigit(checkSymbol) == 0 && isalpha(checkSymbol) == 0) {
        if (checkSymbol != '-' && checkSymbol != ' ' && checkSymbol != '\n') {
            return 1;
        }
        return 0;
    }
    else {
        return 0;
    }
}

void print_list (struct node_struct *head, int type) { /*Prints entire linked list*/

    struct node_struct *temp;

    if (type == 0) {
        while (head != NULL) {
            printf ("%s\n", head->data);
            head = head->next;
        }
    }
    else {
        temp = head->data;
        while (temp != NULL) {
            printf ("%s\n", (char *)(temp->data));
            temp = head->next;
        }
    }

}

int strcmpvoid (const void *a, const void *b) {
    char *ptr_a, *ptr_b;

    ptr_a = (char*)a;
    ptr_b = (char*)b;

    if (strcmp(ptr_a, ptr_b) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

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
    /*char *storeWord;
    const char *split = " \n";
    char tempSym = ' ';*/
    int wordSize = 0;
    int i = 0;
    /*int j = 0;
    int type = 0;*/

    /*If first letter of word char/num -> type 1 (isalpha, isdigit)
     * If first letter of word sym -> type 2 (ispunt)
     * If first letter of word newline -> type 3 (match newline)
     * Else type 1*/

    /*Split words in line with strtok (from spaces)*/
    /*Check word given*/
/*
    ptr = &head;
    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {

        if (strcmp(tempLine, "\n") == 0) {
            printf ("newline found\n");
            storeWord = strtok(tempLine, " ");
        }
        else {
            storeWord = strtok(tempLine, split);
        }
        printf ("%s %c\n", storeWord, storeWord[0]);
        if (isdigit(storeWord[0]) != 0 || isalpha(storeWord[0]) != 0) {
            printf ("type one\n");
        }
        else if (ispunct(storeWord[i]) != 0) {
            printf("type two\n");
        }
        else {
            printf ("either type ")
        }
        while (storeWord != NULL) {
            for (i = 0; i < strlen(storeWord); i++) {
                if (isTypeOne(storeWord[i]) != 0) {
                    printf ("still type1\n");
                }
                else if (ispunct(storeWord[i]) != 0) {
                    printf ("sym detected\n");
                }
                else {
                    printf ("strange line detected\n");
                }
            }
            storeWord = strtok(NULL, split);
        }
    }
*/
    fseek(fp, 0, SEEK_SET);
    ptr = &head; /*Set pointer to address of head*/
    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) { /*Run through entire text of given file*/

        /*printf ("%s", tempLine);*/
        /*printf ("%d\n", strlen(tempLine));*/
        if (tempLine[1] == '\n' && strlen(tempLine) == 2) { /*Checks if line is newline only, stores and reset string + wordSize*/
            /*printf ("newline detected");*/
            wordSize = 1;
            tempWord[0] = tempLine[0];
            *ptr = malloc(sizeof(struct node_struct));
            (*ptr)->data = malloc(strlen(tempWord) + 1);
            strcpy((*ptr)->data, tempWord);
            ptr = &((*ptr)->next);
            /*printf("\nword: %s", tempWord);
            printf ("\nwordSize: %d\n", wordSize);*/
            memset(tempWord, 0, strlen(tempWord));
            wordSize = 0;
            /*printf ("%p\n", (void *)(ptr));*/
        }
        for (i = 0; i < strlen(tempLine); i++) { /*Check entire for loop*/
            if (isTypeOne(tempLine[i]) != 0) { /*Checks if char at i is of type one (defined at function)*/
                /*printf ("\ndetected alph, word at %d", wordSize);*/
                if (wordSize > 0) {
                    if (tempLine[i] == '-' && tempLine[i] == tempLine[i+1]) { /*If there exists double hyphen, store and reset temp string*/
                        *ptr = malloc(sizeof(struct node_struct));
                        (*ptr)->data = malloc(strlen(tempWord) + 1);
                        strcpy((*ptr)->data, tempWord);
                        ptr = &((*ptr)->next);
                        /*printf("\nword: %s", tempWord);
                        printf ("\nwordSize: %d\n", wordSize);*/
                        memset(tempWord, 0, strlen(tempWord));
                        wordSize = 1;
                        /*printf ("%p\n", (void *)(ptr));*/
                    }
                    else if (isTypeOne(tempLine[i-1]) != 1) { /*If prior char is a type one char, store and reset string*/
                        *ptr = malloc(sizeof(struct node_struct));
                        (*ptr)->data = malloc(strlen(tempWord) + 1);
                        strcpy((*ptr)->data, tempWord);
                        ptr = &((*ptr)->next);
                        /*printf("\nword: %s", tempWord);
                        printf ("\nwordSize: %d\n", wordSize);*/
                        memset(tempWord, 0, strlen(tempWord));
                        wordSize = 1;
                        /*printf ("%p\n", (void *)(ptr));*/
                    }
                    else { /*Otherwise increment wordsize by one*/
                        wordSize++;
                    }
                }
                else {
                    wordSize++;
                }
                tempWord[wordSize - 1] = tempLine[i]; /*Store char into temp string*/
            } else if (isTypeTwo(tempLine[i]) != 0) { /*Checks if char at i is of type two (defined at function)*/
                /*printf ("\ndetected sym, word at %d", wordSize);*/
                if (wordSize > 0) {
                    if (tempLine[i - 1] != tempLine[i]) { /*Checks if prior char is the same as current char*/
                        *ptr = malloc(sizeof(struct node_struct));
                        (*ptr)->data = malloc(strlen(tempWord) + 1);
                        strcpy((*ptr)->data, tempWord);
                        ptr = &((*ptr)->next);
                        /*printf("\nword: %s", tempWord);
                        printf("\nwordSize: %d\n", wordSize);*/
                        memset(tempWord, 0, strlen(tempWord));
                        wordSize = 1;
                        /*printf ("%p\n", (void *)(ptr));*/
                    } else { /*Otherwise increment wordsize by one*/
                        wordSize++;
                    }
                } else {
                    wordSize++;
                }
                tempWord[wordSize - 1] = tempLine[i]; /*Store char into temp string*/
            }
            else if (tempLine[i] == '\n') { /*If this is a newline, reset string*/
                /*printf ("detected newline");*/
                memset(tempWord, 0, strlen(tempWord));
                wordSize = 0;
            }
            else { /*If this is a space, store and reset string*/
                /*printf ("\ndetected space, word at %d", wordSize);*/
                *ptr = malloc(sizeof(struct node_struct));
                (*ptr)->data = malloc(strlen(tempWord) + 1);
                strcpy((*ptr)->data, tempWord);
                ptr = &((*ptr)->next);
                /*printf("\nword: %s", tempWord);
                printf ("\nwordSize: %d\n", wordSize);*/
                memset(tempWord, 0, strlen(tempWord));
                wordSize = 0;
                /*printf ("%p\n", (void *)(ptr));*/
            }
        }
    }
    /*Append last node + data (word) into linked list*/
    *ptr = malloc (sizeof(struct node_struct));
    (*ptr)->data = malloc (strlen(tempWord) + 1);
    strcpy((*ptr)->data, tempWord);
    ptr = &((*ptr)->next);
    printf ("%p\n", (void *)(ptr));
    /*printf("\nword: %s", tempWord);
    printf ("\nwordSize: %d\n", wordSize);*/
    memset(tempWord, 0, strlen(tempWord));
    /*printf ("%p\n", (void *)(ptr));*/

    /*Figure out why this not working*/
    *ptr = NULL; /*Set final pointer to null*/

    return head;
}

struct node_struct *search (struct node_struct *list, char *target, int (*compar)(const void *, const void *)) {
    struct node_struct *temp = list;
    struct node_struct **ptr, *head;

    ptr = &head;
    while (temp != NULL) { /*Run through entire list given*/
        /*Compare value to of data to target*/
        if (compar (target, temp->data) == 1) {
            /*Then found*/
            printf ("found\n");
            /*printf ("%p\n", (void *)(temp));*/
            *ptr = malloc (sizeof(struct node_struct));
            (*ptr)->data = malloc (sizeof(struct node_struct));
            (*ptr)->data = &(*temp);
            ptr = &((*ptr)->next);
        }
        temp = temp->next;
    }
    *ptr = NULL;

    /*printf (length(head));*/

    return head;
}

/*Function follows through entire linked list provided by list and increments a counter:
 * Returns the final count (length) of linked list*/
int length (struct node_struct *list) {

    int wordCount = 0;
    struct node_struct *current = list;

    while (current != NULL) {
        wordCount++;
        current = current->next;
    }
    return wordCount;
}

/*Function frees the linked list provided by list: only nodes if free_data is equal
 * to 0, or everything (including data) if free_data is equal to anything elsewise */
void free_list (struct node_struct *list, int free_data) {
    struct node_struct *temp;

    if (free_data != 0) { /*Checks if free_data is 0 or not*/
        /*Free data*/
        while (list != NULL) {
            temp = list;
            list = list->next;
            free(temp->data);
            free(temp);
        }
    }
    else { /*If free data is 0, free only the nodes*/
        while (list != NULL) {
            temp = list;
            list = list->next;
            free(temp);
        }
    }
}

/*

struct node_struct *copy (struct node_struct *start, struct node_struct *end) {

}

void ftext (FILE *fp, struct node_struct *list) {

}

struct node_struct *sort (struct node_struct *list, int (*compar)(const void *, const void *)) {

}

void remove_repeats (struct node_struct *list, int (*compar)(const void *, const void *)) {

}
*/