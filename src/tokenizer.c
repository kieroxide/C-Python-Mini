#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "tokenizer.h"


TokenArr* tokenize(char* file_contents){
    TokenArr* t_arr = create_token_array();

    long size = strlen(file_contents);
    for(long i = 0; i < size; i++){
        char c = file_contents[i];
        if(isalpha(c)){
            int start = i;
            char* slice = &file_contents[start];
            while(i+1 < size && isalpha(file_contents[i+1])){
                i++;
            }
            int length = i - start + 1;
            char* substring = malloc(length + 1);
            if(!substring){
                perror("Failed to allocate substring memory");
                free_token_arr(t_arr);
                return NULL; 
            }
            memcpy(substring, slice, length);
            substring[length] = '\0';

            Token* t = create_token(TOKEN_IDENTIFIER, substring);
            if(!t){
                perror("Failed to create token");
                free(substring);
                free_token_arr(t_arr);
                return NULL; 
            }
            free(substring);
            t_arr = add_token_to_array(t_arr, t);
            if(!t_arr){
                perror("Failed to add token to token array");
                free(substring);
                free_token_arr(t_arr);
                return NULL; 
            }
        }
        if(isdigit(c)){
            int start = i;
            char* slice = &file_contents[start];
            while(i+1 < size && isdigit(file_contents[i+1])){
                i++;
            }
            int length = i - start + 1;
            char* substring = malloc(length + 1);
            if(!substring){
                perror("Failed to allocate substring memory");
                free_token_arr(t_arr);
                return NULL; 
            }
            memcpy(substring, slice, length);
            substring[length] = '\0';

            Token* t = create_token(TOKEN_INT, substring);
            if(!t){
                perror("Failed to create token");
                free(substring);
                free_token_arr(t_arr);
                return NULL; 
            }
            free(substring);
            t_arr = add_token_to_array(t_arr, t);
            if(!t_arr){
                perror("Failed to add token to token array");
                free(substring);
                free_token_arr(t_arr);
                return NULL; 
            }
        }
    }
    return t_arr;
}

void print_tokens(TokenArr* t_arr){
    for(int i = 0; i < t_arr->count; i++){
        printf("Token: %d, ", i);
        printf("Token Value: %s, ", t_arr->tokens[i]->value);
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