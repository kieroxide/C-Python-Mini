#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "./tokenizer.h"

TokenArr* tokenize(char* file_contents){
    TokenArr* t_arr = create_token_array();

    long size = strlen(file_contents);
    for(long i = 0; i < size; i++){
        const char c = file_contents[i];
        if(isalpha(c)){
            t_arr = handle_token(t_arr, file_contents, size, &i, isalpha, TOKEN_IDENTIFIER);
            if(!t_arr){
                perror("Failed to handle token");
                free_token_arr(t_arr);
                return NULL; 
            }
        }
        if(isdigit(c)){
            t_arr = handle_token(t_arr, file_contents, size, &i, isdigit, TOKEN_INT);
            if(!t_arr){
                perror("Failed to handle token");
                free_token_arr(t_arr);
                return NULL; 
            }
        }
        if(is_operator(c)){
            t_arr = handle_token(t_arr, file_contents, size, &i, is_operator, TOKEN_OPERATOR);
            if(!t_arr){
                perror("Failed to handle token");
                free_token_arr(t_arr);
                return NULL; 
            }
        }
        if(is_newline(c)){
            t_arr = handle_token(t_arr, file_contents, size, &i, is_newline, TOKEN_NEWLINE);
            if(!t_arr){
                perror("Failed to handle token");
                free_token_arr(t_arr);
                return NULL; 
            }
        }
    }
    return t_arr;
}

int is_newline(int c){
    if(c == '\n'){
        return 1;
    }
    return 0;
}

int is_operator(int c){
    if(c == '=' || c == '+' || c == '-'){
        return 1;
    }
    return 0;
}

TokenArr* handle_token(TokenArr* t_arr, char* file_contents, long size, long* i, int (*cond)(int), int token_type){
    int start = *i;
    char* slice = &file_contents[start];
    while((*i) + 1 < size && cond(file_contents[(*i)+1])){
        (*i)++;
    }
    int length = (*i) - start + 1;
    char* substring = malloc(length + 1);
    if(!substring){
        perror("Failed to allocate substring memory");
        return NULL; 
    }
    memcpy(substring, slice, length);
    substring[length] = '\0';

    if(strcmp(substring, "print")){ token_type = TOKEN_PRINT;}
    Token* t = create_token(token_type, substring);
    if(!t){
        perror("Failed to create token");
        free(substring);
        return NULL; 
    }
    free(substring);
    t_arr = add_token_to_array(t_arr, t);
    if(!t_arr){
        perror("Failed to add token to token array");
        free(substring);
        return NULL; 
    }
    return t_arr;
}

void print_tokens(TokenArr* t_arr){
    for(int i = 0; i < t_arr->count; i++){
        printf("Token: %d, ", i);
        char* val = t_arr->tokens[i]->value;
        if(*val == '\n'){printf("Token Value: new_line, ");}
        else{
            printf("Token Value: %s, ", t_arr->tokens[i]->value);
        }
        printf("Token Indentifier: %d\n", t_arr->tokens[i]->type);
    }
}

void free_token_arr(TokenArr* t_arr){
    for(int i = 0; i < t_arr->count; i++){
        free_token(t_arr->tokens[i]);
    }
    free(t_arr->tokens);
    free(t_arr);
}

void free_token(Token* t){
    free(t->value);
    free(t);
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