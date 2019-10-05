/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int main() {

    FILE *fp;

    if ((fp = fopen("1342-0.txt", "r+")) == NULL) {
        printf ("File could not be opened");
    }
    txt2words(fp);
    fclose(fp);

    return 0;
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

    printf ("Running txt2words function");
    char tempLine[256] = "blank";
    char temp = ' ';

    while (fgets (tempLine, 256, fp) != NULL) {
        printf (tempLine);
        /*Read line, detect character then second char if it is word, then store into data, then prep the next struct */
        /*Check first character if its a digit, alphabetical character, hyphen or apostrophe*/
        if (isdigit(tempLine[0]) != NULL || isalpha(tempLine[0] != NULL || tempLine[0] == '-' || tempLine[0] == ',')) {

        }

    }

    return /*firstnode*/;
}

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

}

void free_list (struct node_struct *list, int free_data) {

}