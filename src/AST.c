#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum NodeType {
    NODE_VAR,
    NODE_INT,
    NODE_OPERATION,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_PROGRAM
} NodeType;

typedef struct AST_Node {
    NodeType type;

    char* var_name;       
    int int_value;        
    char operator;              

    struct AST_Node* left; 
    struct AST_Node* right;
    struct AST_Node* expr; 
    
    AST_Node** statements;
    int statement_count;
} AST_Node;

AST_Node* parser(TokenArr* t_arr);
void parse_statement(TokenArr* t_arr, int* i);
AST_Node* create_program_node();

AST_Node* parser(TokenArr* t_arr){
    //Loops through all tokens
    AST_Node* program = create_program_node();
    if(!program) return NULL;
    for(int i = 0; i < t_arr->count; i++){
        Token* t = t_arr->tokens[i];
    }
}

void parse_statement(TokenArr* t_arr, int* i){
    Token** tokens = t_arr->tokens;
    Token* t = tokens[*i];
    while(t->type != TOKEN_NEWLINE){
        if(t->type == TOKEN_PRINT){
            AST_Node* print = create_node(NODE_PRINT);
            i++;
            Token* target = tokens[*i];
            if(target->type != TOKEN_IDENTIFIER){
                perror("Invalid print target");
                return NULL;
            }
            print->type = NODE_PRINT;
            print->right = target->value;
            
            
        }
    }
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
    node->int_value = NULL;
    node->operator = NULL;

    node->left = NULL;
    node->right = NULL;
    node->expr = NULL;

    // Only relevant for NODE_PROGRAM
    node->statements = NULL;
    node->statement_count = 0;

    return node;
}