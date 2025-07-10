#include <string.h>
#ifdef _WIN32
#include <malloc.h>  // THIS is where _strdup is declared
#define strdup _strdup
#endif
#include "read_file.h"
#include "tokenizer.h"
#include "AST.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct variable {
    int value;
    char* name;
} variable;

typedef struct variables {
    variable** v_arr;
    int count;
    int capacity;
} variables;

void eval_ast(AST_Node* program);
variables* modify_variable(variables* variables, variable* v);
variables* create_var_array();
variable* create_var(char* name,int value);
void free_var_arr(variables* variables);
void free_variable(variable* v);

int main(){
    const char filename[] = "C:/Users/bailk/Desktop/Programs/Github-Projects/C-Python-Mini/tester.txt";
    //Read file
    char* file_contents = read_file(filename);
    if(!file_contents){
        perror("File Contents are Null");
        return -1;
    }

    long size = strlen(file_contents);
    int line_start = 0;
    char c;
    while(c != '\0'){
        c = file_contents[line_start];
        int line_size = 0;
        while(c != '\n' && c != '\0'){
            line_size++;
            c = file_contents[line_size + line_start];
        }
        int line_end = line_start + line_size;
        TokenArr* t_arr = tokenize_line(file_contents, line_start, line_end);
        print_tokens(t_arr);
        free_token_arr(t_arr);



        line_start = line_end + 1;
    }

    //AST_Node* program = parser(t_arr);
    //eval_ast(program);


    //free_ast(program);
    free(file_contents);
    return 0;
}

void eval_ast(AST_Node* program){
    variables* temp_variables;
    int length = program->statement_count;
    variables* variables = create_var_array();
    if(!variables){
        perror("Error allocating memory for variables struct");
    }

    for(int i = 0; i < length; i++){
        AST_Node* current = program->statements[i];
        while(current != NULL){
            if(current->type == NODE_ASSIGN){
                variable* v = create_var(current->var_name, current->right->int_value);
                if(!v){
                    perror("Error allocating memory for variable");
                    break;
                }

                temp_variables = modify_variable(variables, v);

                if (!temp_variables) {
                    perror("Error reallocating memory for variables");
                    free_variable(v);        // free the new variable you created but failed to add
                    free_var_arr(variables); // free the original variables properly
                    variables = NULL;
                    break;                  // or return to avoid further use of variables
                }
                variables = temp_variables;
                break;
            }
            else if(current->type == NODE_PRINT){
                if(!current->right){
                    break;
                }
                AST_Node* next = current->right;
                int count = variables->count;
                char* name = next->var_name;
                int value = 0;

                for(int j = 0; j < count; j++){
                    variable* v = variables->v_arr[j];
                    if(strcmp(v->name, name) == 0){
                        value = v->value;
                    }
                }
                printf("%s : %d \n", next->var_name, value);
                break;
            }
            else if(current->type == NODE_OPERATION){
                char operator = current->operator;
                char leftVal = current->left->int_value;
                char rightVal = current->right->int_value;
                int result;
                if(operator == '+') {result = leftVal + rightVal;}
                if(operator == '-') {result = leftVal - rightVal;}
                if(operator == '*') {result = leftVal * rightVal;}
                if(operator == '/') {result = leftVal / rightVal;}
            }
            current = current->right;
        }
    }
    free_var_arr(variables);
}

variables* modify_variable(variables* variables, variable* v){
    int count = variables->count;
    char* name = v->name;
    for(int i = 0; i < count; i++){
        variable* tmp = variables->v_arr[i];
        if(strcmp(tmp->name, name) == 0){
            tmp->value = v->value;
            free_variable(v);
            return variables;
        }
    }
    if(variables->capacity == variables->count){
        variables->capacity *= 2;
        variable** temp = realloc(variables->v_arr, sizeof(variable*) * variables->capacity);
        if(!temp){
            perror("Failed to realloc token array");
            return NULL; 
        }
        variables->v_arr = temp;
    }
    variables->v_arr[variables->count] = v;
    variables->count++;
    return variables;
}   

variables* create_var_array(){
    variables* variables = malloc(sizeof(variables));

    if(!variables){
        perror("Failed to allocate memory for token array struct");
        return NULL;
    }

    variables->capacity = 4;
    variables->count = 0;
    variables->v_arr = malloc(sizeof(variable*) * variables->capacity);

    if(!variables->v_arr){
        perror("Failed to allocate memory for token array");
        free(variables);
        return NULL;
    }

    return variables;
}

variable* create_var(char* name,int value){
    variable* v = malloc(sizeof(variable));

    if(!v){
        perror("Failed to allocate memory for token value");
        return NULL;
    }
    v->name = strdup(name);
    v->value = value;
    return v;
}

void free_var_arr(variables* variables){
    variable** v_arr = variables->v_arr;
    for(int i = 0; i < variables->count; i++){
        free_variable(v_arr[i]);
    }
    free(v_arr);
    free(variables);
}

void free_variable(variable* v){
    free(v->name);
    free(v);
}