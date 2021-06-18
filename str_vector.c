#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str_vector.h"

str_vector_t str_vector_new(){
  str_vector_t v;
  v.size=0;
  v.data=NULL;
  return v;
}

void str_vector_append(str_vector_t *vector, char *string){
  str_vector_resize(vector,vector->size+1); vector->data[vector->size-1]=string;
}

void str_vector_append_sorted(str_vector_t *vector, char *string,enum sort_mode mode){
  switch (mode){
    case (RANDOM): 
      break;
    case (SEQ):
      {
        str_vector_resize(vector,vector->size+1);
        int i,j;
        for (i=0; i<vector->size-1 && strcmp(vector->data[i],string)<0 ;i++);
        for (j=vector->size-1; j>i;j--) {
          vector->data[j]=vector->data[j-1];
        }
        vector->data[i]=string;
        break;
      }
    case (INVERTED):
      {
        str_vector_resize(vector,vector->size+1);
        int i,j;
        for (i=0; i<vector->size-1 && strcmp(vector->data[i],string)>0 ;i++);
        for (j=vector->size-1; j>i;j--) {
          vector->data[j]=vector->data[j-1];
        }
        vector->data[i]=string;
        break; 
      }
    default:
      fprintf(stderr,"Unknown mode\n");
      break;
  }
}

// que debo retornar? decia char *
void str_vector_resize(str_vector_t *vector, unsigned elements){
  vector->size=elements;
  vector->data=realloc(vector->data,sizeof(char *) * vector->size);
}

// va en el .h?
static void swap(int i,int j,str_vector_t vec){
  char * temp= vec.data[j];
  vec.data[j]=vec.data[i];
  vec.data[i]=temp;

}

void str_vector_sort(str_vector_t *vector, enum sort_mode mode){
  if(vector->size<2) return;
  str_vector_t aux_vec=str_vector_new();
  switch(mode){
    case (SEQ): 
      return;
      break;
    case (INVERTED):
      {
        str_vector_resize(&aux_vec,vector->size);
        int i;
        for (i=vector->size-1; i>=0; i--){ //hacer iterador
          aux_vec.data[vector->size-1-i]=vector->data[i];
        }
        break;
      }
    case (RANDOM): // cuenta con que si lo llaman esta ordenado por SEQ o por INVERTED
      srand(getpid());
      //filtra los repetidos
      char aux_str[BUFSIZ]="\0";
      int i;
      for (i=0;i<vector->size;i++){ //hacer iterador
        if (strcmp(aux_str,vector->data[i])){
          str_vector_append(&aux_vec,vector->data[i]);
        }
        strcpy(aux_str,vector->data[i]);
      }
      for (i=1;i<aux_vec.size;i++){//hacer iterador
        swap(i,rand() % i,aux_vec);
      }
      break;
    default:
      fprintf(stderr,"Unknown mode\n"); //debe hacer exit si ingreso modo desconocido?
      break;
  }
  str_vector_free(vector);
  *vector=aux_vec;
}

void str_vector_free(str_vector_t *vector){
  free(vector->data);
  vector->size=0;
}

