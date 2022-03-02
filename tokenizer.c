#include "tokenizer.h"
#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static TokenNode* create_token_node(char* text, int length, int line);


Token* pop_token(TokenStack* token_stack) {
	if(!token_stack)
		return NULL;

    Token* ret = malloc(sizeof(Token));
    memcpy(ret, &token_stack->top->token, sizeof(Token));

    TokenNode* new_top = token_stack->top->prev;
    free(token_stack->top);
    token_stack->top = new_top;
    
    return ret;
}

static bool is_delim(char c) {
    return isspace(c)
       || c == '(' 
       || c == ')'
       || c == '{'
       || c == '}'
       || c == ','
       || c == ';';
}

int read_next_token(TokenStack* token_stack, char* text) {
    if(*text == '\0') 
       return 0;

    int whitespace  = 0;
    while(is_delim(*text)) {
        token_stack->current_line += (*text == '\n' ? 1 : 0);
        text +=1;
        if(*text == '\0')
            return 0;
        whitespace +=1;
    }
    
    int length = 1;
    bool end_of_string = false;
    while(!is_delim(text[length]))
    {
        if(!text[length]){
            end_of_string = true;
            break;
        }
        length += 1;
    }
    
    TokenNode* new_token = create_token_node(
        text, 
        length, 
        token_stack->current_line);

    new_token->prev = token_stack->top;
    token_stack->top = new_token;

    return length + whitespace + (!end_of_string ? 1 : 0);
}

static inline TokenNode* create_token_node(char* text, int length, int line) {
    TokenNode* node = malloc(sizeof(TokenNode));
    node->token.line_number = line;
    node->token.identifier = malloc(sizeof(char)*length+1);
    strncpy(node->token.identifier, text, length);
    node->token.identifier[length] = '\0';
    
    return node;
}
