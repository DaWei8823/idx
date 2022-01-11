#ifndef TOKEN
#define TOKEN

typedef struct {
    char* identifier;
    int line_number;
} Token;

typedef struct TokenNode {
    Token token;
    struct TokenNode* prev;
} TokenNode;

typedef struct {
    struct TokenNode* top;
    int current_line;
} TokenStack;

Token* pop_token(TokenStack* token_stack);
char* read_next_token(TokenStack* token_stack, char** ptxt);
#endif
