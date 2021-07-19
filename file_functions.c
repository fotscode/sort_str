#include "include/file_functions.h"
#include <stdlib.h>
#include <stdio.h>

void help(char *filename){
  printf("Usage: %s [OPTIONS]...\n",filename);
  FILE *help=fopen("help.txt","r");
  if (!help){
    fprintf(stderr,"%s: help.txt : Error opening file",filename);
    exit(ERROR_FILE);
  }
  char s[128]="\0";
  while (fgets(s,sizeof(s),help)) printf("%s",s);
  fclose(help);
}

void my_close(FILE *in,FILE *out){
  if (in) fclose(in);
  if (out) fclose(out);
}

int count_lines(FILE *in){
  if (!in) {
    fprintf(stderr,"WARNING: file is equal to NULL, return value is 0\n");
    return 0;
  }
  int c=0;
  char s[STRING_SIZE]="\0";
  while (fgets(s,sizeof(s),in)) c++;
  return c;
}
