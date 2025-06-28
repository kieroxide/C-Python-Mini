#include "my_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    const char filename[] = "C:/Users/bailk/Desktop/Programs/Github-Projects/C-Python-Mini/tester.txt";
    char* file_contents = read_file(filename);
    if(!file_contents){
        perror("File Contents are Null");
        return -1;
    }
    // Tokenize
    
    //printf("%s",file_contents);
    free(file_contents);
    return 0;
}