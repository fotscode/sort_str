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
  if (!string){
    fprintf(stderr,"WARNING: string is equal to NULL, vector wasn't modified\n");
    return;
  }
  if (!vector) *vector=str_vector_new();
  str_vector_resize(vector,vector->size+1); 
  str_vector_set(vector,vector->size-1,string);
}

static int search_place(str_vector_t *vector, char *string, enum sort_mode mode){
  int i;
  switch(mode){
    case (RANDOM):
      fprintf(stderr,"WARNING: RANDOM is not a valid mode, -1 is returned\n");
      return -1;
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
  if (!string){
    fprintf(stderr,"WARNING: string is equal to NULL, vector wasn't modified\n");
    return;
  }
  if (!vector) *vector=str_vector_new();
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
  if(!vector||vector->size<2) return;
  switch(mode){
    case (SEQ): 
      return;
      break;
    case (INVERTED):
      {
        int i;
        char aux[STRING_SIZE];
        for (i=0; i<vector->size/2;i++){
          strcpy(aux,str_vector_get(vector,i));
          swap(i,vector->size-1-i,vector);
        }
        break;
      }
    case (RANDOM): 
      {
        // assumes vector was sorted as SEQ
        srand(getpid()); // sets random seed to be different every time
        int i=0;
        int j,count_elim;
        while(i<vector->size-1){
          count_elim=0;
          j=i;
          while (j<vector->size-1&&!strcmp(str_vector_get(vector,i),str_vector_get(vector,j+1))){
            count_elim++;
            j++;
            free(str_vector_get(vector,j)); // frees repeated strings
          }
          if (count_elim){
            for (j=i+1;j<vector->size-count_elim;j++){
              str_vector_set(vector,j,str_vector_get(vector,j+count_elim));
            }
            str_vector_resize(vector,vector->size-count_elim);
          }
          i++;
        }
        for (i=1;i<vector->size;i++){
          swap(i,rand() % i,vector);
        }
        break;
      }
  }
}

void str_vector_free(str_vector_t *vector){
  free(vector->data);
  vector->size=0;
}

