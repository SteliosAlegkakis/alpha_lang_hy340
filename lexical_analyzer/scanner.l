%{
#if defined(WIN32)
#define YY_NO_UNISTD_H
static int isatty (int i) { return 0; }
#elif defined(_WIN32_WCE)
#define YY_NO_UNISTD_H
static int isatty (void *i) { return 0; }
#endif

#include "./scanner.h"
#define YY_DECL int yylex (void* yylval)
%}

%option noyywrap
%option yylineno
%option prefix = "alpha_yy"

%% 

[0-9]+          {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"INTEGER"),yylval);}
[a-zA-Z]+       {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"IDENTIFIER"),yylval);}
"="             {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"ASSIGN"),yylval);}
"+"             {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"ADD"),yylval);}
"-"             {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"SUB"),yylval);}
"*"             {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"MUL"),yylval);}
"/"             {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"DIV"),yylval);}
"("             {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LEFT_PAR"),yylval);}
")"             {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"RIGHT_PAR"),yylval);}
"\n"            /* Do nothing for newline */

[ \t]+          /* Do nothing for whitespace */

.               printf("ERROR\n");

%%

void add_token_to_list(alpha_token_t* token, alpha_token_t** head){
    if(*head == NULL){
        *head = token;
    }
    else{
        alpha_token_t* current = *head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = alpha_token_t_create(token->numline, token->numToken, token->content, token->type);
    }
}

alpha_token_t* alpha_token_t_create(unsigned int _numline, unsigned int _numToken, char *_content, char *_type){
    alpha_token_t *token = (alpha_token_t*) malloc(sizeof(alpha_token_t));
    if(token == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    token->numline = _numline;
    token->numToken = _numToken;
    token->content = deep_copy_string(_content);
    token->type = _type;
    token->next = NULL;
    return token;
}

char* deep_copy_string(const char* source) {
    if (source == NULL) {
        return NULL;
    }
    size_t length = strlen(source);
    char* destination = (char*) malloc(length + 1);
    if (destination == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(destination, source);
    return destination;
}
  
int main(int argc, char** argv) {
    yyin = fopen(argv[1], "r");
    if(alpha_yyin == NULL){
        printf("Error. Could not open input file");
        exit(EXIT_FAILURE);
    }

    alpha_token_t *alphaTokenList = NULL;
    alpha_yylex(&alphaTokenList);

    while(alphaTokenList != NULL){
        printf("%d %d %s %s\n",alphaTokenList->numline,alphaTokenList->numToken,alphaTokenList->content,alphaTokenList->type);
        alphaTokenList = alphaTokenList->next;
    }
    fclose(yyin);
    return 0;
}