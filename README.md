# sort_str

## Compilacion

gcc main.c str_vector.c str_vector_expanded.c file_functions.c -o main -Wno-nonnull -Wall

uso -Wno-nonnull ya que las funciones string requieren un argumento no NULL, cuando se usa la macro de str_vector_get en la ultima iteracion de un for esta devuelve NULL pero no se procesa, tira el warning pero nunca podria haber problema.

## Uso

`./main`
ordena en ASCII ascendente las lineas leidas mediante stdin

`./main -i test.txt`
ordena en ASCII ascendente las lineas leidas del archivo 'test.txt', imprime en stdout

`./main -r test.txt`
ordena en ASCII descendente las lineas leidas del archivo 'test.txt', imprime en stdout

`./main -i test.txt -o output.txt`
ordena en ASCII ascendente las lineas leidas del archivo 'test.txt', guarda el resultado de la ordenacion en output.txt

`./main -c test.txt`
cuenta las lineas de 'test.txt'

`./main -h `
muestra la ayuda del programa
