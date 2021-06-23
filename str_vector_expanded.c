#include "include/str_vector_expanded.h"
#include "include/str_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void str_vector_create(str_vector_t *vector,FILE *in){
  char aux[BUFSIZ];
  while (fgets(aux,sizeof(char)*STRING_SIZE,in)){
    char *s=malloc(sizeof(char)*STRING_SIZE);
    strcpy(s,aux);
    str_vector_append_sorted(vector,s,SEQ);
  }
}

void str_vector_print(str_vector_t vector,FILE *out){
  int i;
  for (i=0;i<vector.size;i++) {
    fputs(vector.data[i],out);
  }
}

void str_vector_free_all_str(str_vector_t *vector){
  int i;
  for(i=0;i<vector->size;i++){
    free(vector->data[i]);
  }
}
