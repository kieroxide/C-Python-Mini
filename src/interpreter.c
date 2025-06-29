#include "read_file.h"
#include "tokenizer.h"
#include "AST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    const char filename[] = "C:/Users/bailk/Desktop/Programs/Github-Projects/C-Python-Mini/tester.txt";
    //Read file
    char* file_contents = read_file(filename);
    if(!file_contents){
        perror("File Contents are Null");
        return -1;
    }
    // Tokenize
    TokenArr* t_arr = tokenize(file_contents);
    AST_Node* program = parser(t_arr);
    free(program);
    free(file_contents);
    print_tokens(t_arr);
    free_token_arr(t_arr);
    return 0;
}