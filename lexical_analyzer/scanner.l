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
%x COMMENT

%% 

\"([^\"]|(\\\"))*\"      {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"STRING"),yylval);}
[0-9]+                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"INTCONST"),yylval);}
[0-9]+\.[0-9]+          {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"REALCONST"),yylval);}
[a-zA-Z]+[_0-9]*        {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"IDENTIFIER"),yylval);}
"="                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"ASSIGN"),yylval);}
"+"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"ADD"),yylval);}
"-"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"SUB"),yylval);}
"*"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"MUL"),yylval);}
"/"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"DIV"),yylval);}
"("                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LEFT_PAR"),yylval);}
")"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"RIGHT_PAR"),yylval);}
"\n"                    /* Do nothing for newline */
[ \t\n\r]+              /* Do nothing for whitespace */
.                       {printf("Undefined input %s in line %d\n",yytext,yylineno);exit(EXIT_FAILURE);}

"//".*
"/*" BEGIN(COMMENT);
<COMMENT>[^*/]*
<COMMENT>"*"+[^*/]*
<COMMENT>"*"+"/" BEGIN(INITIAL);

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
    token->content = strdup(_content);
    check_escape_characters(token->content);
    token->type = _type;
    token->next = NULL;
    return token;
}

void check_escape_characters(char* str){
    int length = strlen(str);
    char result[length + 1]; // +1 for the null terminator
    int j = 0;

    for (int i = 0; i < length; i++) {
        if (str[i] == '\\') {
            switch (str[i+1]) {
                case 'n':
                    result[j++] = '\n';
                    break;
                case 't':
                    result[j++] = '\t';
                    break;
                case '\"':
                    result[j++] = '\"';
                    break;
                case '\\':
                    result[j++] = 27;//escape
                    break;
                case 'a':
                    result[j++] = '\a';
                    break;
                case 'b':
                    result[j++] = '\b';
                    break;
                case 'e':
                    result[j++] = '\e';
                    break;
                case 'r':
                    result[j++] = '\r';
                    break;
                case 'v':
                    result[j++] = '\v';
                    break;
                default:
                    result[j++] = str[i];
                    break;
            }
            i++;
        } else {
            result[j++] = str[i];
        }
    }

    result[j] = '\0';
    strcpy(str, result);
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