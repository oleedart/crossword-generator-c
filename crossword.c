/**
 * Crossword.c - generates crossword puzzle
 */

#include <stdio.h>
#include <stdlib.h>

#include "buildquestion.h"
#include "file.h"

typedef struct crossword {
    char **boxes;
    int num_rows;
    int num_columns;
} crossword_t;

crossword_t *crossword_new(int, int);
int crossword_print(crossword_t *crossword);
int crossword_delete(crossword_t *crossword);

//tests
int crossword_new_test(crossword_t*);

int main(int argc, char **argv) {
    //TODO: Read from command line. At the moment, hardcode values

    FILE *fp;

    fp = fopen("testquestions", "r");

    questions_t *questions = questions_new(fp);

    //test extraction
    question_t *question = grab_question(questions);
    while(question != NULL) {
        //printf("Word%*s with size of %*d has clue %*s\n", 10, question->word, 5, question->word_length, 20, question->clue);
        printf("Word%s with size of %d has clue %s\n", question->word, question->word_length, question->clue);
        question = grab_question(questions);
    }

    fclose(fp);



    // crossword_t *crossword;
    // crossword = crossword_new(15, 15);
    
    // int result_crossword_new_test = crossword_new_test(crossword);
    // if(result_crossword_new_test == 0) {
    //     printf("Crossword new test success\n");
    // } else {
    //     printf("Crossword new test failed wiht code %d\n", result_crossword_new_test);
    //     return 1;
    // }

    // crossword_print(crossword);

    // crossword_delete(crossword);



    return 0;
}

crossword_t *crossword_new(int num_rows, int num_columns) {
    crossword_t *crossword = malloc(sizeof(crossword_t));

    if(crossword != NULL) {
        //initilize components

        //allocate memory for char *'s for each row
        crossword->boxes = calloc(num_rows, sizeof(char*));

        //for each row, allocate memory for each char
        for(int i = 0; i < num_rows; i++) {
            crossword->boxes[i] = calloc(num_columns, sizeof(char));
        }
        crossword->num_rows = num_rows;
        crossword->num_columns = num_columns;
        return crossword;
    } else {
        return NULL;
    }
}

int crossword_print(crossword_t *crossword) {
    if(crossword == NULL) {
        return 1;
    }

    int rows = crossword->num_rows;
    int columns = crossword->num_columns;

    for(int i = 0; i < rows; i++) {
        for(int k = 0; k < columns; k++) {
            if(crossword->boxes[i][k] == 'X') {
                printf("|\u25A0\u25A0\u25A0");
            } else {
                printf("|%c  ", crossword->boxes[i][k]);
            }
            
        }
        printf("\n");
    }
    

    return 0;

}

int crossword_delete(crossword_t *crossword) {
    if(crossword == NULL) {
        return 1;
    }

    for(int i = 0; i < crossword->num_rows; i++) {
        free(crossword->boxes[i]);
    }
    free(crossword->boxes);
    free(crossword);

    return 0;

}

/* Fill a crossword with characters to test that memory was properly allocated */
int crossword_new_test(crossword_t *crossword) {
    if(crossword == NULL) {
        return 1;
    }

    int rows = crossword->num_rows;
    int columns = crossword->num_columns;

    printf("Generated a crossword with %d rows and %d columns.\n", rows, columns);

    //assign character to crossword;
    for(int i = 0; i < rows; i++) {
        for(int k = 0; k < columns; k++) {
            crossword->boxes[i][k] = 'X';
        }
    }

    //hardcoded test
    crossword->boxes[5][5] = '1';
    crossword->boxes[6][5] = ' ';
    crossword->boxes[7][5] = ' ';
    crossword->boxes[8][5] = '2';
    crossword->boxes[8][6] = ' ';
    crossword->boxes[8][7] = ' ';

    //return 0 for success
    return 0;
}

