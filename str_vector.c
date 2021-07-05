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
  str_vector_resize(vector,vector->size+1); 
  str_vector_set(vector,vector->size-1,string);
}

static int search_place(str_vector_t *vector, char *string, enum sort_mode mode){
  int i;
  switch(mode){
    case (RANDOM):
      break;
    case (SEQ):
      for (i=0; i<vector->size-1 && strcmp(str_vector_get(vector,i),string) < 0 ;i++);
      break;
    case (INVERTED):
      for (i=0; i<vector->size-1 && strcmp(str_vector_get(vector,i),string)>0 ;i++);
      break;
  }
  return i;
}

void str_vector_append_sorted(str_vector_t *vector, char *string,enum sort_mode mode){
  switch (mode){
    case (RANDOM): 
      break;
    case (SEQ):
    case (INVERTED):
      {
        str_vector_resize(vector,vector->size+1); 
        int j;
        int i=search_place(vector,string,mode);
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
        int i;
        for (i=vector->size-1; i>=0; i--){
          str_vector_append_sorted(&aux_vec,str_vector_get(vector,i),INVERTED);
        }
        break;
      }
    case (RANDOM): 
      {
        srand(getpid()); // sets random seed to be different every time
        str_vector_sort(vector,INVERTED); // sorts in case it wasn't sorted
        // filter repeated strings
        char aux_str[BUFSIZ]="\0";
        int i;
        for (i=0;i<vector->size;i++){ 
          if (strcmp(aux_str,(str_vector_get(vector,i)))){
            str_vector_append(&aux_vec,str_vector_get(vector,i));
            strcpy(aux_str,str_vector_get(vector,i));
          }else
            free(str_vector_get(vector,i)); // free repeated strings
        }
        // permutation
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

