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

int start_multi_comment,end_line_comment;
char str[100]; 

%}

%option noyywrap
%option yylineno
%option prefix = "alpha_yy"
%x COMMENT

%% 
"if"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD IF"),yylval);}
"else"                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD ELSE"),yylval);}
"while"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD WHILE"),yylval);}
"for"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD FOR"),yylval);}
"function"              {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD FUNCTION"),yylval);}
"return"                {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD RETURN"),yylval);}
"break"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD BREAK"),yylval);}
"continue"              {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD CONTINUE"),yylval);}
"and"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD AND"),yylval);}
"not"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD NOT"),yylval);}
"or"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD OR"),yylval);}
"local"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD LOCAL"),yylval);}
"true"                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD TRUE"),yylval);}
"false"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD FALSE"),yylval);}
"nil"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD NIL"),yylval);}
\"([^\"]|(\\\"))*\"      {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"STRING"),yylval);}
[0-9]+                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"INTCONST"),yylval);}
[0-9]+\.[0-9]+          {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"REALCONST"),yylval);}
[a-zA-Z]+[_0-9]*        {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"IDENTIFIER"),yylval);}
"="                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"ASSIGN"),yylval);}
"+"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"ADD"),yylval);}
"-"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"SUB"),yylval);}
"*"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"MUL"),yylval);}
"/"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"DIV"),yylval);}
"%"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"MODULO"),yylval);}
"=="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"EQUAL"),yylval);}
"!="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"NOT EQUAL"),yylval);}
"++"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PLUS_PLUS"),yylval);}
"--"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"MINUS_MINUS"),yylval);}
">"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"GREATER_THAN"),yylval);}
"<"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LESSER_THAN"),yylval);}
">="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"GREATER_OR_EQUAL"),yylval);}
"<="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LESS_OR_EQUAL"),yylval);}
"{"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LEFT_CURLY_BR"),yylval);}
"}"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"RIGHT_CURLY_BR"),yylval);}
"["                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LEFT_SQUARE_BR"),yylval);}
"]"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"RIGHT_SQUARE_BR"),yylval);}
"("                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LEFT_PAR"),yylval);}
")"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"RIGHT_PAR"),yylval);}
";"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"SEMICOLON"),yylval);}
","                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"COMMA"),yylval);}
":"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"COLON"),yylval);}
"::"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"DOUBLE_COLON"),yylval);}
"."                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PERIOD"),yylval);}
".."                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"DOUBLE_PERIOD"),yylval);}
"\n"                    /* Do nothing for newline */
[ \t\n\r]+              /* Do nothing for whitespace */
.                       {printf("Undefined input %s in line %d\n",yytext,yylineno);exit(EXIT_FAILURE);}

"//".*
"/*" BEGIN(COMMENT); {start_multi_comment=yylineno;} 
<COMMENT>[^*]+
<COMMENT>[^*/]*        
<COMMENT>"*"+[^*/]*
<COMMENT>"*"+"/" BEGIN(INITIAL);{
                end_line_comment = yylineno;
                sprintf(str,"%d - %d",start_multi_comment,end_line_comment);
                add_token_to_list(alpha_token_t_create(start_multi_comment,++tokensCount,str,"COMMENT BLOCK_COMMENT"),yylval);
          }  
<COMMENT><<EOF>> {printf("There is a unclosed comment\n");exit(EXIT_FAILURE);}


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
