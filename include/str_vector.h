#ifndef H_STR_VECTOR
#define H_STR_VECTOR

#include <stddef.h>
#include "file_functions.h"

typedef struct {
  size_t size;
  char **data;
} str_vector_t;


enum sort_mode { SEQ , INVERTED , RANDOM };

/******************************************************************
*                             Macros                              *
******************************************************************/
 
// Retorna el elemento en la posición index del vector, si la
// posición index no existe retorna NULL.
#define str_vector_get(vector, index) \
  (index>=0&&index<(vector)->size) ? (vector)->data[index] : NULL


// Guarda el elemento en la posición index del vector
// CAMBIAR EXIT
#define str_vector_set(vector, index, elemento) \
  if (index<0) {fprintf(stderr,"Non valid index\n"); exit(ERROR_INDEX); } \
  else if ((index)>(vector)->size) {str_vector_resize((vector),(index)+1);}\
  (vector)->data[index]=elemento


/******************************************************************
*                            Funciones                            *
******************************************************************/

// Retorna un vector vacío.
str_vector_t str_vector_new();

// Agrega un nuevo elemento al vector. Se almacena el puntero.
void str_vector_append(str_vector_t *vector, char *string);

/* Agrega un nuevo elemento al vector siguiendo el orden especificado
* por `mode` (excepto el modo random o aleatorio). Se almacena el puntero.*/
void str_vector_append_sorted(str_vector_t *vector, char *string,
enum sort_mode mode);

// Redimensiona el vector para contener `elements` elementos.
void str_vector_resize(str_vector_t *vector, unsigned elements);

// Ordena el vector de acuerdo a el modo elegido.
void str_vector_sort(str_vector_t *vector, enum sort_mode mode);

//Libera la memoria alocada para el vector.
void str_vector_free(str_vector_t *vector);

#endif
