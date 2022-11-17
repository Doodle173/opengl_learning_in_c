#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<errno.h>
#include "util.h"

char *readFile(char *path)
{
   FILE *f = fopen(path, "rb");
   if(!f){
      fprintf(stderr, "fopen %s failed: %d %s\n", path, errno, strerror(errno));
      exit(1);
   }
   fseek(f, 0, SEEK_END);
   int length = ftell(f);
   rewind(f);
   char *data = calloc(length + 1, sizeof(char));
   fread(data, 1, length, f);
   fclose(f);
   return data;
}
