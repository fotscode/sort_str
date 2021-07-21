#include "include/str_vector_expanded.h"
#include "include/str_vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void str_vector_create(str_vector_t *vector,FILE *in){
  if (!in||!vector) {
    fprintf(stderr,"WARNING: file or vector were equal to NULL, vector wasn't created\n");
    return;
  }
  *vector=str_vector_new();
  char aux[STRING_SIZE];
  while (fgets(aux,sizeof(char)*STRING_SIZE,in)){
    char *s=malloc(sizeof(char)*(strlen(aux)+1));
    strcpy(s,aux);
    str_vector_append_sorted(vector,s,SEQ);
  }
}

void str_vector_print(str_vector_t vector,FILE *out){
  if (!out){
    fprintf(stderr,"WARNING: file is equal to NULL, vector wasn't printed\n");
    return;
  }
  int i;
  for (i=0;i<vector.size;i++) {
    if(str_vector_get(&vector,i)){
      fputs(str_vector_get(&vector,i),out);
    }
  }
}

void str_vector_free_all_str(str_vector_t *vector){
  if (!vector){
    fprintf(stderr,"WARNING: vector is equal to NULL, no strings were freed\n");
    return;
  }
  int i;
  for(i=0;i<vector->size;i++){
    if (str_vector_get(vector,i)){
      free(str_vector_get(vector,i));
    }
  }
  str_vector_free(vector);
}
