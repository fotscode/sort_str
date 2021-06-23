#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/str_vector.h"

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
          str_vector_set(vector,j,str_vector_get(vector,j-1));
        }
        str_vector_set(vector,i,string);
        break;
      }
    case (INVERTED):
      {
        str_vector_resize(vector,vector->size+1);
        int i,j;
        for (i=0; i<vector->size-1 && strcmp(vector->data[i],string)>0 ;i++);
        for (j=vector->size-1; j>i;j--) {
          str_vector_set(vector,j,str_vector_get(vector,j-1));
        }
        str_vector_set(vector,i,string);
        break; 
      }
    default:
      fprintf(stderr,"Unknown mode\n");
      break;
  }
}

void str_vector_resize(str_vector_t *vector, unsigned elements){
  vector->size=elements;
  vector->data=realloc(vector->data,sizeof(char *) * vector->size);
}

static void swap(int i,int j,str_vector_t *vec){
  char * temp= str_vector_get(vec,j);
  str_vector_set(vec,j,str_vector_get(vec,i));
  str_vector_set(vec,i,temp);
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
        for (i=vector->size-1; i>=0; i--){
          str_vector_set(&aux_vec,vector->size-1-i,str_vector_get(vector,i));
        }
        break;
      }
    case (RANDOM): 
      {
        str_vector_sort(vector,INVERTED); // me aseguro que este ordenado
        srand(getpid());
        //filtro los repetidos
        char aux_str[BUFSIZ]="\0";
        int i;
        for (i=0;i<vector->size;i++){ 
          if (strcmp(aux_str,vector->data[i])){
            str_vector_append(&aux_vec,str_vector_get(vector,i));
          }
          strcpy(aux_str,vector->data[i]);
        }
        for (i=1;i<aux_vec.size;i++){
          swap(i,rand() % i,&aux_vec);
        }
      }
      break;
    default:
      fprintf(stderr,"Unknown mode\n"); 
      break;
  }
  str_vector_free(vector);
  *vector=aux_vec;
}

void str_vector_free(str_vector_t *vector){
  free(vector->data);
  vector->size=0;
}

