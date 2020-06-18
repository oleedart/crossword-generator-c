/**
 * Builds out questions used for crossword.
 * Assigns each line of a text file to a question struct
 * Array of question structs will be used.
*/

#include "buildquestion.h"
#include "file.h"

typedef struct questions {
    question_t **questions;
    int size;
} questions_t;

typedef struct question {
    char *word;
    char *clue;
    int word_length;
} question_t;

static question_t *question_new(char* rawLine);
static int get_number_of_questions(FILE *fp);
static int fill_questions(questions_t *questions, FILE *fp);
static void questions_print(questions_t *questions);
static question_t *question_copy(question_t *question);

questions_t *questions_new(FILE *fp) {
    questions_t *questions = malloc(sizeof(questions_t));

    if(questions != NULL) {
        int size = get_number_of_questions(fp);

        questions->questions = calloc(size, sizeof(question_t*));
        questions->size = size;

        //printf("Created questions\n");

        // for(int i = 0; i < size; i++) {
        //     questions->questions[i] = calloc()
        // }
    }

    fill_questions(questions, fp);

    //test
    // printf("\nIn Grab Question\n\n");
    // grab_question(questions);
    // printf("\n");
    // grab_question(questions);
    // printf("\n");
    // grab_question(questions);
    // printf("\n");
    // grab_question(questions);
    // printf("\n");
    // grab_question(questions);
    // printf("\n");
    // grab_question(questions);

    return questions;

}

question_t *grab_question(questions_t *questions) {
    if(questions == NULL) {
        return NULL;
    }

    if(questions->size == 0) {
        return NULL;
    }

    //test print out the questions
    //questions_print(questions);

    //pull out random index form questions array
    srand(time(NULL));
    int random_num = (rand() % (questions->size - 1 + 1)) + 0; 
    //printf("Random number is %d\n", random_num);

    question_t *copy = question_copy(questions->questions[random_num]);

    //printf("Attempting shift\n");
    //move questions on the right over
    for(int i = random_num; i < questions->size - 1; i++){
        
        //printf("Shifting %s to where %s was", questions, i);
        questions->questions[i] = questions->questions[i + 1];
        //break;
    }

    //set the last question to null and free
    // questions->questions[questions->size - 1]->word = NULL;
    // questions->questions[questions->size - 1]->clue = NULL;

    // questions->questions[questions->size - 1] = NULL;

    // free(questions->questions[questions->size - 1]);

    //decrement size
    questions->size--;

    //questions_print(questions);

    return copy;

}

char *getWord(question_t *question) {
    return question->word;
}

char *getClue(question_t *question) {
    return question->clue;
}
int getWordlength(question_t *question) {
    return question->word_length;
}

static int get_number_of_questions(FILE *fp) {
    return lines_in_file(fp);
}

//Future TODO: Check for numbers, bad characters, and spaces in the word category. 
static question_t *question_new(char *rawLine) {
    if(rawLine == NULL) {
        return NULL;
    }

    question_t *question = malloc(sizeof(question_t));

    //first token is our word
    char *token = strtok(rawLine, ",");
    char *word = calloc(strlen(token), sizeof(char));
    strcpy(word, token);

    question->word = word;

    question->word_length = strlen(word);

    int clue_size = 0;
    char *clue = calloc(0, sizeof(char));

    int index = 0;
    while( token != NULL ) {

        //skip first 
        if(index == 0) {
            token = strtok(NULL, ",");
            index++;
            continue;
        }

        int increment = (strlen(token) * sizeof(char));
        clue_size += increment;
        clue = realloc(clue, clue_size);

        strcat(clue, token);
        
        token = strtok(NULL, ",");

        //tack comma back on
        if(token != NULL) {
            strcat(clue, ",");
        }
    }

    question->clue = clue;

    //test that everythings right

    //printf("Word  %s  with size of %d  has clue  %s  \n", question->word, question->word_length, question->clue);

    return question;

}

//fill questions
static int fill_questions(questions_t *questions, FILE *fp) {
    if(questions == NULL) {
        return 1;
    }

    if(fp == NULL) {
        return 2;
    }

    int size = questions->size;

    for(int i = 0; i < size; i++) {
        char *line = freadlinep(fp);
        questions->questions[i] = question_new(line);
    }

    // printf("\nChecking correctness of assignmnet\n\n");
    // questions_print(questions);

    return 0;
}

static question_t *question_copy(question_t *question) {
    int word_length = question->word_length;
    int clue_length = strlen(question->clue + 1);

    char *new_word = calloc(word_length, sizeof(char));
    char *new_clue = calloc(clue_length, sizeof(char));

    strcpy(new_word, question->word);
    strcpy(new_clue, question->clue);

    question_t *new_question = malloc(sizeof(question_t));

    new_question->word = new_word;
    new_question->clue = new_clue;
    new_question->word_length = word_length;

    //printf("Checking if question_copy works\n");

    //printf("Word  %s  with size of %d  has clue  %s  \n", new_question->word, new_question->word_length, new_question->clue);

    //printf("Question copy success!!\n");

    return new_question;
}

static void questions_print(questions_t *questions) {

    //print out each question
    for(int i = 0; i < questions->size; i++) {
        printf("Word  %s  with size of %d  has clue  %s  \n", questions->questions[i]->word, questions->questions[i]->word_length, questions->questions[i]->clue);
    }
}