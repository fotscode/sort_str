#include "include/str_vector.h"
#include "include/str_vector_expanded.h"
#include "include/file_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

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
        my_close(in,out);
        help(argv[0]);
        exit(EXIT_SUCCESS);
        break;
      }
      case 'i':
      {
        in=fopen(optarg,"r");
        if (!in){
          my_close(stdin,out);
          fprintf(stderr,"%s: %s: Error opening file",argv[0],optarg);
          exit(ERROR_FILE);
        }
        break;
      }
      case 'o':
      {
        out=fopen(optarg,"w");
        if (!out){
          my_close(in,stdout);
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
    my_close(in,out);
    exit(EXIT_SUCCESS);
  }

  if (rever_flag&&shuff_flag){
    fprintf(stderr,"%s: error: `-r` and `-s` flags where set at the same time\n",argv[0]);
    my_close(in,out);
    exit(ERROR_CONFLICT);
  }

  str_vector_t vec;
  str_vector_create(&vec,in); // inits vec with data from in
  if (rever_flag){
    str_vector_sort(&vec,INVERTED);
  }
  if (shuff_flag){
    str_vector_sort(&vec,RANDOM);
  }
  str_vector_print(vec,out);
  my_close(in,out);
  str_vector_free_all_str(&vec);
  str_vector_free(&vec);
  return 0;
}
