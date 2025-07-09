#ifndef AST_h
#define AST_h

#include "tokenizer.h"

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
    
    struct AST_Node** statements;
    int statement_count;
    int statement_capacity;
} AST_Node;

AST_Node* parser(TokenArr* t_arr);
AST_Node* parse_statement(TokenArr* t_arr,AST_Node* program, int* i);
AST_Node* create_node(NodeType type);
AST_Node* init_statement_arr(AST_Node* program);
AST_Node* add_to_statement_arr(AST_Node* program, AST_Node* node);
void free_statements(AST_Node* head);
void free_ast(AST_Node* head);

#endif