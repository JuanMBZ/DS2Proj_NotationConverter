#include <stdio.h>
#include <string.h>

enum Format {
  infix, prefix, postfix
}

void print_usage(char *prog_name) {
  fprintf(stderr, "Usage: %s --from <input_format> --to <input_format> \"<expression_string>\" ", prog_name);
  exit(1);
}

int main(int argc, char *argv[]) {
  enum in_format, out_format;
  char option[100];
  
  for(int i=1; i<argc; i++) {
      if(*argv[i] != '-') {
        break;
      }

      // Check user input expression format
      if(strcmp(&(argv[i][1]), "-from") == 0) {      
        if(strcmp(argv[i+1], "infix") == 0)
          in_format=infix;
        else if(strcmp(argv[i+1], "prefix") == 0) 
          in_format=prefix;
        else if(strcmp(argv[i+1], "postfix") == 0)
          in_format=postfix;
        else {
          fprintf(stderr, "Unknown format: --from %s", argv[i+1]);
          exit(1);
        }
      }

      if(strcmp(&(argv[i][1]), "-to") == 0) {
        if(strcmp(argv[i+1], "infix") == 0)
          out_format=infix;
        else if(strcmp(argv[i+1], "prefix") == 0) 
          out_format=prefix;
        else if(strcmp(argv[i+1], "postfix") == 0)
          out_format=postfix;
        else {
          fprintf(stderr, "Unknown format: --to %s", argv[i+1]);
          exit(1);
        }
      }
      
  }

  if(i>=argc)
    print_usage(argv[0]);

  printf("Input form=%d, Output form=%d", in_format, out_format);
  
  return 0;
}
