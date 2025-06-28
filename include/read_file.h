#ifndef read_file_h
#define read_file_h

#include <stdio.h> 

char* read_file(const char* filename);
int fclose_safe(FILE* f);

#endif