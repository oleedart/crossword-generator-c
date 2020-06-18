
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct questions questions_t;
typedef struct question question_t;

questions_t *questions_new(FILE *fp);
question_t *grab_question(questions_t *questions);

char *getWord(question_t *question);
char *getClue(question_t *question);
int getWordlength(question_t *question);