#include "tokenizer.h"
#include "AST.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


AST_Node* parser(TokenArr* t_arr){
    //Loops through all tokens
    AST_Node* program = create_node(NODE_PROGRAM);
    program = init_statement_arr(program);
    if(!program) return NULL;
    for(int i = 0; i < t_arr->count; i++){
        program = parse_statement(t_arr, program ,&i );
    }
    return program;
}

AST_Node* parse_statement(TokenArr* t_arr,AST_Node* program, int* i){
    Token** tokens = t_arr->tokens;
    while(*i < t_arr->count && tokens[*i]->type != TOKEN_NEWLINE){
        Token* t = tokens[*i];
        if(t->type == TOKEN_PRINT){
            //If print token, check next token, if its identifier create and store
            //identifier node to new print node
            (*i)++;
            Token* target = tokens[*i];
            if(target->type != TOKEN_IDENTIFIER){
                perror("Invalid print target");
                return NULL;
            }
            AST_Node* print = create_node(NODE_PRINT);
            AST_Node* var = create_node(NODE_VAR);

            var->var_name = strdup(target->value);
            print->type = NODE_PRINT;
            print->right = var;

            add_to_statement_arr(program, print);
            
        }
        else if(t->type == TOKEN_IDENTIFIER){
            //Take identifier and its values store as node check for operator equals
            //
            AST_Node* var = create_node(NODE_ASSIGN);
            var->var_name = strdup(t->value);
            (*i)++;
            Token* target = tokens[*i];
            if(target->type != TOKEN_OPERATOR){
                perror("Invalid Identifier Operation");
                return NULL;
            }
            if(strcmp(target->value, "=")){
                perror("Invalid Identifier Operation");
                return NULL;
            }
            var->operator = '=';
            (*i)++;
            target = tokens[*i];
            if(target->type != TOKEN_INT){
                perror("Invalid Assignment");
                return NULL;
            }
            var->int_value = atoi(target->value);
            add_to_statement_arr(program, var);
        }
        (*i)++;
    }
    return program;
}

AST_Node* create_node(NodeType type) {
    AST_Node* node = malloc(sizeof(AST_Node));
    if (!node) {
        perror("Failed to allocate AST_Node");
        return NULL;
    }

    node->type = type;

    // Common init
    node->var_name = NULL;
    node->int_value = 0;
    node->operator = '\0';

    node->left = NULL;
    node->right = NULL;
    node->expr = NULL;

    // Only relevant for NODE_PROGRAM
    node->statements = NULL;
    node->statement_count = 0;

    return node;
}

AST_Node* init_statement_arr(AST_Node* program){
    program->statement_capacity = 8;
    program->statement_count = 0;
    program->statements = malloc(sizeof(AST_Node*) * program->statement_capacity);
    return program;
}

AST_Node* add_to_statement_arr(AST_Node* program, AST_Node* node){
    if(program->statement_capacity == program->statement_count){
        program->statement_capacity *= 2;
        AST_Node** temp = realloc(program->statements, sizeof(AST_Node*) * program->statement_capacity);
        if(!temp){
            perror("Failed to allocate memory for token array struct");
            return NULL;
        }
        program->statements = temp;
    }
    program->statements[program->statement_count] = node;
    program->statement_count++;
    return program;
}