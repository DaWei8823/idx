#include "tests.h"
#include "tokenizer.h"
#include <assert.h>
#include <string.h>

void test_tokenizer() {
    char* text = "void foo(int x) {\nint var = x;\n}";
    TokenStack stack = {
        .top = NULL,
        .current_line = 1
    };
    int len = 0;
    while((len = read_next_token(&stack, text))) {
        text+=len;
    }
    

   Token* third = pop_token(&stack);
   assert(third->line_number == 2);
   assert(strcmp(third->identifier, "x") == 0);
    
   Token* fourth = pop_token(&stack);
   assert(fourth->line_number == 2);
   assert(strcmp(fourth->identifier, "=") == 0);
    
   Token* fifth = pop_token(&stack);
   assert(fifth->line_number == 2);
   assert(strcmp(fifth->identifier, "var") == 0);

   Token* sixth = pop_token(&stack);
   assert(sixth->line_number == 2);
   assert(strcmp(sixth->identifier, "int") == 0);
   
    
   Token* sev = pop_token(&stack);
   assert(sev->line_number == 1);
   assert(strcmp(sev->identifier, "x") == 0);


   Token* eight = pop_token(&stack);
   assert(eight->line_number == 1);
   assert(strcmp(eight->identifier, "int") == 0);


   Token* nine = pop_token(&stack);
   assert(nine->line_number == 1);
   assert(strcmp(nine->identifier, "foo") == 0);


   Token* ten = pop_token(&stack);
   assert(ten->line_number == 1);
   assert(strcmp(ten->identifier, "void") == 0);
}
