#include "include/file_functions.h"
#include <stdlib.h>
#include <stdio.h>

void help(char *filename){
  printf("Usage: %s [OPTIONS]...\n",filename);
  FILE *help=fopen("help.txt","r");
  if (!help){
    my_close(help,stdout);
    fprintf(stderr,"%s: help.txt : Error opening file",filename);
    exit(ERROR_FILE);
  }
  char s[BUFSIZ]="\0";
  while (fgets(s,sizeof(s),help)) printf("%s",s);
  my_close(help,stdout);
}

void my_close(FILE *in,FILE *out){
  if (in!=stdin) fclose(in);
  if (out!=stdout) fclose(out);
}

int count_lines(FILE *in){
  int c=0;
  char s[BUFSIZ]="\0";
  while (fgets(s,sizeof(s),in)) c++;
  return c;
}
