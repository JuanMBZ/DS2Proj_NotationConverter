#include <stdio.h>

enum Format {
  infix, prefix, postfix
}

void print_usage(char *prog_name) {
  fprintf(stderr, "Usage: %s [--from <input_format>] [--to <input_format>] \"<expression_string>\" ", prog_name);
}

int main(int argc, char *argv[]) {
  enum in_format, out_format;
  
  for(int i=1; i<argc; i++) {
      if(*argv[i] != '-') {
        break;
      }

    
  }
  
  return 0;
}
