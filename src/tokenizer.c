#include <stdlib.h>
#include <string.h>

typedef enum {
    TOKEN_INT,        
    TOKEN_IDENTIFIER, 
    TOKEN_PLUS,       
    TOKEN_MINUS       
} TokenType;

typedef struct {
    TokenType type;
    char* value;    
} Token;

typedef struct {
    Token** tokens;
    int count;    
    int capacity;
} TokenArr;

Token* create_token(TokenType type, char* value);

Token** tokenize(char* file_contents){
    TokenArr* t_arr = create_token_array();

    long size = strlen(file_contents);
    for(long i = 0; i < size; i++){
        char c = file_contents[i];

    }
}

TokenArr* add_token_to_array(TokenArr* t_arr, Token* t){
    if(t_arr->capacity == t_arr->count){
        t_arr->capacity *= 2;
        Token** temp = realloc(t_arr->tokens, sizeof(Token*) * t_arr->capacity);
        if(!temp){
            perror("Failed to realloc token array");
            return NULL; 
        }
        t_arr->tokens = temp;
    }
    t_arr->tokens[t_arr->count] = t;
    t_arr->count++;
    return t_arr;
}   

TokenArr* create_token_array(){
    TokenArr* t_arr = malloc(sizeof(TokenArr));

    if(!t_arr){
        perror("Failed to allocate memory for token array struct");
        return NULL;
    }

    t_arr->capacity = 4;
    t_arr->count = 0;
    t_arr->tokens = malloc(sizeof(Token*) * t_arr->capacity);

    if(!t_arr->tokens){
        perror("Failed to allocate memory for token array");
        free(t_arr);
        return NULL;
    }

    return t_arr;
}

Token* create_token(TokenType type, char* value){
    Token* t = malloc(sizeof(Token));

    if(!t){
        perror("Failed to allocate memory for token value");
        return NULL;
    }

    t->type = type;
    if(value){
        t->value = strdup(value);
        if (!t->value) {
            perror("Failed to allocate memory for token value");
            free(t);
            return NULL;
        }
    } else {
        t->value = NULL;
    }
    return t;
}