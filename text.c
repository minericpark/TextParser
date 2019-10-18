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
    struct node_struct *head, *sHead, *test1, *test2, *cHead, *test3;

    if ((fp = fopen("test.txt", "r+")) == NULL) {
        printf ("File could not be opened");
    }
    printf ("\ntxt2words test:\n");
    head = txt2words(fp);
    printf ("%d\n", length(head));
    print_list(head, 0);
    remove_repeats(head, strcmpvoid);
    printf ("\nremove_repeat test:\n");
    print_list(head, 0);
    printf ("\nsearch test:\n");/*
    sHead = search(head, "chapter", strcmpvoid);
    printf ("%d\n", length(sHead));
    /*print_list(sHead, 1);*//*
    test1 = sHead->data;
    /*printf ("%s\n", (char*)(test1->data));
    printf ("%p\n", (void*)(test1));*//*
    test2 = ((struct node_struct *) (sHead->next))->data;
    /*printf ("%s\n", (char*)(test2->data));
    printf ("%p\n", (void*)(test2));*//*
    printf ("\ncopy test:\n");
    cHead = copy (test1, test2);
    printf ("%d\n", length(cHead));
    /*test3 = cHead->data;
    printf ("%s\n", (char*)(test3->data));
    printf ("%p\n", (void*)(test3));*/
    /*print_list(cHead, 0);*/
    free_list(head, 1);/*
    free_list(sHead, 0);
    free_list(cHead, 0);*/
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

/*Function prints the list of the the given linked list at head and relies on type
 * Type 1 -> Linked list with data->string print, Type 2 -> Linked list with data->nodes print*/
void print_list (struct node_struct *head, int type) { /*Prints entire linked list*/

    if (type == 0) {
        while (head != NULL) {
            printf ("%s\n", (char *) head->data);
            head = head->next;
        }
    }
    else {
        while (head != NULL) {
            printf ("%s\n", (char *)((struct node_struct *)(head->data))->data);
            /*printf ("%p\n", (void*)(head->data));*/
            head = head->next;
        }
    }

}

/*Function compares two void pointers and returns 1 if they are equal, or 0 otherwise*/
int strcmpvoid (const void *a, const void *b) {
    char *ptr_a, *ptr_b;

    ptr_a = (char*)a;
    ptr_b = (char*)b;

    if (strcmp(ptr_a, ptr_b) == 0) {
        return 0;
    }
    else {
        return 1;
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

    struct node_struct *head, **ptr;
    char tempLine[256] = " ";
    char tempWord[265] = " ";
    int wordSize = 0;
    int i = 0;

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

/*Function searches through linked list list to find target with a compar function provided. Returns a
 * pointer to the head of the new linked list composed of the address of nodes to the found targets*/
struct node_struct *search (struct node_struct *list, char *target, int (*compar)(const void *, const void *)) {
    struct node_struct *temp = list;
    struct node_struct **ptr, *head;

    ptr = &head;
    while (temp != NULL) { /*Run through entire list given*/
        /*Compare value to of data to target*/
        if (compar (target, temp->data) == 0) {
            /*Then found*/
            /*printf ("found\n");
            printf ("%p\n", (void *)(temp));*/
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

/*Function takes in node start and end, and scans from start up to end. Then creates a linked
 * list composed of address of data pointers of all words between start and just before end,
 * and returns it. */
struct node_struct *copy (struct node_struct *start, struct node_struct *end) {

    struct node_struct *temp = start; /*Assign start to temp*/
    struct node_struct **ptr, *head;

    ptr = &head;
    /*printf ("%p\n", (void *)(head));*/
    while (temp != NULL) { /*Run through entire list given*/
        if (temp == end) { /*Determines if temp has reached end, then exits loop*/
            /*Then found*/
            /*printf ("done\n");*/
            break;
        }
        /*printf ("%p\n", (void *)(temp));
        printf ("%s\n", (char *)(temp->data));*/
        *ptr = malloc (sizeof(struct node_struct));
        (*ptr)->data = malloc (sizeof(struct node_struct));
        (*ptr)->data = &(*temp->data); /*Copy data pointer*/
        ptr = &((*ptr)->next);
        temp = temp->next;
    }
    *ptr = NULL;

    /*printf ("%p\n", (void *)(head));*/

    return head;
}

void remove_repeats (struct node_struct *list, int (*compar)(const void *, const void *)) {

    struct node_struct *current, *search, *temp, *prev, *next;
    current = list;
    search = list->next;

    while (current != NULL) {
        while (search != NULL) {
            printf ("%s vs %s \n", current->data, search->data);
            if (compar(current->data, search->data) == 0) {
                temp = search->next;
                if (search->next == NULL) {
                    prev->next = NULL;
                    free(search->data);
                    free(search);
                }
                else {
                    printf ("found\n");
                    next = temp->next;
                    search->next = next->next;
                    free(search->data);
                    free(search);
                }
            }
            prev = search;
            search = search->next;
        }
        current = current->next;
        search = current->next;
    }
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
    struct node_struct *temp, *temp2;

    if (free_data != 0) { /*Checks if free_data is 0 or not*/
        /*Free data*/
        while (list != NULL) {
            temp = list;
            temp2 = (struct node_struct *)temp->data;
            list = list->next;
            free(temp2);
            free(temp->data);
            free(temp);
        }
    }
    else { /*If free data is 0, free only the nodes*/
        while (list != NULL) {
            temp = list;
            list = list->next;
            free(temp->data);
            free(temp);
        }
    }
}

/*

void ftext (FILE *fp, struct node_struct *list) {

}

struct node_struct *sort (struct node_struct *list, int (*compar)(const void *, const void *)) {

}
*/