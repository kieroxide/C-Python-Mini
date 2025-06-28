#include "read_file.h"
#include <stdlib.h>

char* read_file(const char* filename){
    FILE* f = fopen(filename, "rb");
    if(!f){
        perror("Error opening file");
        return NULL;
    }

    // Sets file pointer to end of file
    if(fseek(f, 0, SEEK_END)){
        perror("Error with fseek");
        fclose(f);
        return NULL;
    }

    long size = ftell(f);  // Returns current pointer position aka size of the file
    if(size == -1L){
        perror("Error with ftell");
        fclose_safe(f);
        return NULL;
    }

    rewind(f);             // Resets pointer back to start of file

    char* file_contents = malloc(size + 1);
    if(!file_contents){
        perror("Error with file_contents malloc");
        fclose_safe(f);
        return NULL;
    }
    
    if(fread(file_contents, sizeof(char), size, f) != size){
        perror("Error with fread() returned wrong amount");
        free(file_contents);
        fclose_safe(f);
        return NULL;
    }

    file_contents[size] = '\0';
    fclose_safe(f);
    return file_contents;
}

int fclose_safe(FILE* f){
    if(fclose(f) == EOF){
        perror("Error closing file");
        return -1;
    }
    return 0;
}

