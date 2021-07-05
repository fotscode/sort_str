#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

#include <stdio.h>

#define ERROR_FILE 1 // exit code when opening a file fails
#define ERROR_CONFLICT 2 // exit code when there's a conflict of orders
#define ERROR_INDEX 3 // exit code when non valid index is specified

#define STRING_SIZE 512 // string size

// displays help text
void help(char *filename);

// closes in and out if they're not stdin nor stdout respectively
void my_close(FILE *in,FILE *out);

// returns file's number of lines
int count_lines(FILE *in);

#endif
