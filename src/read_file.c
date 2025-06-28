#include <stdio.h>
#include <stdlib.h>

char* read_file(char* filename){
    FILE* f = fopen(filename, "rb");

    fseek(f, 0, SEEK_END); // Sets file pointer to end of file
    long size = ftell(f);  // Returns current pointer position aka size of the file
    rewind(f);             // Resets pointer back to start of file

    char* file_contents = malloc(size + 1);
    
    fread(file_contents, sizeof(char), size, f);
    return file_contents;
}

int main(){
    char* file_contents = read_file("C:/Users/bailk/Desktop/Programs/Github-Projects/C-Python-Mini/tester.txt");
    free(file_contents);
}