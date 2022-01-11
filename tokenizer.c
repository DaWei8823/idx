#include "tokenizer.h"
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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

char* read_next_token(TokenStack* token_stack, char** ptxt) {
    char* text = *ptxt;
    if(*text == '\0') 
       return NULL;

    while(isspace(*text)) {
        token_stack->current_line += (*text == '\n' ? 1 : 0);
        text +=1;
    }

    int length = 0;
    while(!isspace(*(text+length)) 
        && !(*(text+length) == '(') 
        && !(*(text+length) == ')')
        && !(*(text+length) == '{')
        && !(*(text+length) == '}')
        && !(*(text+length) == ',')
        && !(*(text+length) == ';')
        )
        length += 1;
    
    length = length > 0 ? length : 1;
    TokenNode* new_token = create_token_node(
        text, 
        length, 
        token_stack->current_line);

    new_token->prev = token_stack->top;
    token_stack->top = new_token;
    *ptxt = text + length; 

    return new_token->token.identifier;
}

static inline TokenNode* create_token_node(char* text, int length, int line) {
    TokenNode* new_token_node = malloc(sizeof(TokenNode));
    new_token_node->token.line_number = line;
    new_token_node->token.identifier = malloc(sizeof(char)*length+1);
    
    for(int i = 0; i < length; i++)
        *(new_token_node->token.identifier + i) = *(text+i);
    *(new_token_node->token.identifier + length) = '\0';
    
    return new_token_node;
}
