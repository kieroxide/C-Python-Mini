#ifndef tokenizer_h
#define tokenizer_h

typedef enum {
    TOKEN_INT,        
    TOKEN_IDENTIFIER, 
    TOKEN_OPERATOR,
    TOKEN_NEWLINE,
    TOKEN_PRINT      
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
TokenArr* handle_token(TokenArr* t_arr, char* file_contents, long size, long* i, int (*cond)(int), int token_type);
TokenArr* create_token_array();
TokenArr* add_token_to_array(TokenArr* t_arr, Token* t);
Token* create_token(TokenType type, char* value);
void free_token(Token* t);
void free_token_arr(TokenArr* t_arr);
void print_tokens(TokenArr* t_arr);
int is_operator(int c);
int is_newline(int c);


#endif