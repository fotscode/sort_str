#include <stdio.h>
#include "str_vector.h"
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

// estos define van aca, no en el .h, no?
#define ERROR_FILE 1 // exit code when opening a file fails
#define ERROR_CONFLICT 2 // exit code when there's a conflict of orders

#define STRING_SIZE 512

void help(char *filename){
  printf("Usage: %s [OPTIONS]...\n",filename);
  puts("Sorts FILE lines to output FILE\n");
  puts("\t-i, --input  <INPUT_FILE>\treads from INPUT_FILE");
  puts("\t-o, --output <OUTPUT_FILE>\twrites on OUTPUT_FILE");
  puts("\t-r, --reverse\tinverts sort condition");
  puts("\t-s, --shuffle\trandomly sorts strings");
  puts("\t-c, --count\tcounts lines from file");
  puts("\t-h, --help\tdisplays this text\n");
  puts("If -r or -s were not specified the files it's sorted by ASCII order");
  puts("With no -i <INPUT_FILE> specified, reads standard input");
  puts("With no -o <OUTPUT_FILE> specified, writes on standard output");
  exit(EXIT_SUCCESS);
}

void myclose(FILE *in,FILE *out){
  if (in!=stdin) fclose(in);
  if (out!=stdout) fclose(out);
}

int count_lines(FILE *in){
  int c=0;
  char s[BUFSIZ]="\0";
  while (fgets(s,sizeof(s),in)) c++;
  return c;
}

void create_str_vec(str_vector_t *vector,FILE *in){
  // debo alocar mem para cada string
  char aux[BUFSIZ];
  while (fgets(aux,sizeof(char)*STRING_SIZE,in)){
    char *s=malloc(sizeof(char)*STRING_SIZE);
    strcpy(s,aux); // que otra forma en vez de esto?!?
    str_vector_append_sorted(vector,s,SEQ);
  }
}

void print_str_vec(str_vector_t vector,FILE *out){
  int i;
  for (i=0;i<vector.size;i++) {
    fputs(vector.data[i],out);
  }
}

void free_strings(str_vector_t *vector){
  int i;
  for(i=0;i<vector->size;i++){
    free(vector->data[i]);
  }
}

int main(int argc, char *argv[]){
  FILE *in=stdin;
  FILE *out=stdout;

  static int count_flag=0;
  static int rever_flag=0;
  static int shuff_flag=0;
  int o;
  static struct option long_options[] =
    {
      {"count",  no_argument,         0,  'c'},
      {"reverse",no_argument,         0,  'r'},
      {"shuffle",no_argument,         0,  's'},
      {"help",   no_argument,         0,  'h'},
      {"input",  required_argument,   0,  'i'},
      {"output", required_argument,   0,  'o'},
      {0, 0, 0, 0}
    };

  while ((o=getopt_long(argc,argv,"crshi:o:",long_options,0))!=-1){
    switch(o){
      case 'h':
      {
        help(argv[0]);
        break;
      }
      case 'i':
      {
        in=fopen(optarg,"r");
        if (!in){
          myclose(stdin,out);
          fprintf(stderr,"%s: %s: Error opening file",argv[0],optarg);
          exit(ERROR_FILE);
        }
        break;
      }
      case 'o':
      {
        out=fopen(optarg,"w");
        if (!out){
          myclose(in,stdout);
          fprintf(stderr,"%s: %s: Error opening file",argv[0],optarg);
          exit(ERROR_FILE);
        }
        break;
      }
      case 'c':
      {
        count_flag=1;
        break;
      }
      case 'r':
      {
        rever_flag=1;
        break;
      }
      case 's':
      {
        shuff_flag=1;
        break;
      }
    }
  }

  if (count_flag){
    if (rever_flag||shuff_flag||out!=stdout){
      fprintf(stderr,"WARNING: `-r`,`-s` and `-o` will be ignored\n");
    }
    printf("lines: %d\n",count_lines(in));
    exit(EXIT_SUCCESS);
  }

  if (rever_flag&&shuff_flag){
    fprintf(stderr,"%s: error: `-r` and `-s` flags where set at the same time\n",argv[0]);
    myclose(in,out);
    exit(ERROR_CONFLICT);
  }

  str_vector_t vec=str_vector_new();
  create_str_vec(&vec,in); // inits vec with data from in
  if (rever_flag){
    str_vector_sort(&vec,INVERTED);
  }
  if (shuff_flag){
    str_vector_sort(&vec,RANDOM);
  }
  print_str_vec(vec,out);
  myclose(in,out);
  free_strings(&vec); // lo debe hacer el str_vector_free a esto?
  str_vector_free(&vec);
  return 0;
}
