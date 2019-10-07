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
    char tempLine[256] = " ";
    char tempWord[265] = " ";
    char temp = ' ';
    int wordSize = 0;
    int i = 0;

    while (fgets (tempLine, 256, fp) != NULL) {
        memset(tempWord, 0, sizeof(tempWord));
        printf ("%s", tempLine);
        /*Read line, detect character then second char if it is word, then store into data, then prep the next struct */
        /*Check first character if its a digit, alphabetical character, hyphen or apostrophe*/
        if (isdigit(tempLine[0]) != 0 || isalpha(tempLine[0]) != 0) {
            /**/
            tempWord[0] = tempLine[0];
            for (i = 1; i < strlen(tempLine); i++) {
                if ((isdigit(tempLine[i]) == 0 && isalpha(tempLine[i]) == 0) || (tempLine[i] == '-' && tempLine[i+1] == '-') || tempLine[i] == '"') { /*Next char is not a digit nor alpha, or its is a double hyphen, or a double apostrophe*/
                    /*Stop loop*/
                    break;
                }
                else {
                    tempWord[i] = tempLine[i];
                }
            }
            printf ("%s\n", tempWord);

        }
        else if (strcmp (&tempLine[0], "/n") == 0) {
            /*just store newline*/
            tempWord[0] = tempLine[0];
            printf ("%s\n", tempWord);
        }
        else {
            tempWord[0] = tempLine[0];
            if (isdigit(tempLine[1]) != 0 || isalpha(tempLine[1] != 0)) { /*Is collection of symbols*/
                for (i = 1; i < strlen(tempLine); i++) {
                    if (tempLine[0] != tempLine[i]) { /*Symbols match*/
                        /*Stop loop*/
                        break;
                    }
                    else {
                        tempWord[i] = tempLine[i];
                    }
                }
            }
            else { /*This is type 1 word e.g. regular word*/
                for (i = 1; i < strlen(tempLine); i++) {
                    if ((isdigit(tempLine[i]) == 0 && isalpha(tempLine[i]) == 0) || (tempLine[i] == '-' && tempLine[i+1] == '-') || tempLine[i] == '"') { /*Next char is not a digit nor alpha, or its is a double hyphen, or a double apostrophe*/
                        /*Stop loop*/
                        break;
                    }
                    else {
                        tempWord[i] = tempLine[i];
                    }
                }
            }
            printf ("%s\n", tempWord);
        }
        /*If first char is char or num, type 1
         * If first char is newline, type3
         * If something else, type 2 (symbol repeated)
         * Else type 1*/
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

    return 0;
}

void free_list (struct node_struct *list, int free_data) {


}