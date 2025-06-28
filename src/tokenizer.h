#ifndef tokenizer_h
#define tokenizer_h

typedef enum {
    TOKEN_INT,        
    TOKEN_IDENTIFIER, 
    TOKEN_PLUS,       
    TOKEN_MINUS,
    TOKEN_EQUALS       
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


TokenArr* tokenize(char* file_contents);
Token* create_token(TokenType type, char* value);
TokenArr* create_token_array();
TokenArr* add_token_to_array(TokenArr* t_arr, Token* t);
void free_token(Token* t);
void free_token_arr(TokenArr* t_arr);
void print_tokens(TokenArr* t_arr);

#endif