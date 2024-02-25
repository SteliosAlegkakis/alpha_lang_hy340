%{
#include "./scanner.h"
unsigned int start_multi_comment;
unsigned int end_line_comment;
unsigned int tokensCount = 0;
int quotes_removed = -1;
%}

%option noyywrap
%option yylineno
%option prefix = "alpha_yy"
%option outfile = "scanner.c"

%x COMMENT

%% 

"if"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"IF","enumerated"),yylval);}
"else"                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD ELSE","enumerated"),yylval);}
"while"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD WHILE","enumerated"),yylval);}
"for"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD FOR","enumerated"),yylval);}
"function"              {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD FUNCTION","enumerated"),yylval);}
"return"                {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD RETURN","enumerated"),yylval);}
"break"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD BREAK","enumerated"),yylval);}
"continue"              {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD CONTINUE","enumerated"),yylval);}
"and"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD AND","enumerated"),yylval);}
"not"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD NOT","enumerated"),yylval);}
"or"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD OR","enumerated"),yylval);}
"local"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD LOCAL","enumerated"),yylval);}
"true"                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD TRUE","enumerated"),yylval);}
"false"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD FALSE","enumerated"),yylval);}
"nil"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD NIL","enumerated"),yylval);}
\"([^\"]|(\\\"))*\"     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"STRING","char*"),yylval);}
[0-9]+                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"INTCONST","integer"),yylval);}
[0-9]+\.[0-9]+          {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"REALCONST","real"),yylval);}
[a-zA-Z]+[_0-9a-zA-z]*  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"IDENTIFIER","char*"),yylval);}
"="                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"ASSIGN","enumerated"),yylval);}
"+"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"ADD","enumerated"),yylval);}
"-"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"SUB","enumerated"),yylval);}
"*"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"MUL","enumerated"),yylval);}
"/"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"DIV","enumerated"),yylval);}
"%"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"MODULO","enumerated"),yylval);}
"=="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"EQUAL","enumerated"),yylval);}
"!="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"NOT EQUAL","enumerated"),yylval);}
"++"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PLUS_PLUS","enumerated"),yylval);}
"--"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"MINUS_MINUS","enumerated"),yylval);}
">"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"GREATER_THAN","enumerated"),yylval);}
"<"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LESSER_THAN","enumerated"),yylval);}
">="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"GREATER_OR_EQUAL","enumerated"),yylval);}
"<="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LESS_OR_EQUAL","enumerated"),yylval);}
"{"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LEFT_CURLY_BR","enumerated"),yylval);}
"}"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"RIGHT_CURLY_BR","enumerated"),yylval);}
"["                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LEFT_SQUARE_BR","enumerated"),yylval);}
"]"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"RIGHT_SQUARE_BR","enumerated"),yylval);}
"("                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"LEFT_PAR","enumerated"),yylval);}
")"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"RIGHT_PAR","enumerated"),yylval);}
";"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"SEMICOLON","enumerated"),yylval);}
","                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"COMMA","enumerated"),yylval);}
":"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"COLON","enumerated"),yylval);}
"::"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"DOUBLE_COLON","enumerated"),yylval);}
"."                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PERIOD","enumerated"),yylval);}
".."                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"DOUBLE_PERIOD","enumerated"),yylval);}
[ \t\n\r]+              /* Do nothing for whitespace */
.                       {printf("Undefined input %s in line %d\n",yytext,yylineno);exit(EXIT_FAILURE);}
"//".*                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,"\"\"","COMMENT LINE_COMMENT","enumerated"),yylval);}
"/*" BEGIN(COMMENT); {start_multi_comment=yylineno;} 
<COMMENT>[^*]+
<COMMENT>[^*/]*        
<COMMENT>"*"+[^*/]*
<COMMENT>"*"+"/" BEGIN(INITIAL);{
                end_line_comment = yylineno;
                char str[100];
                sprintf(str,"%d - %d",start_multi_comment,end_line_comment);
                add_token_to_list(alpha_token_t_create(start_multi_comment,++tokensCount,str,"COMMENT BLOCK_COMMENT","enumerated"),yylval);
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
        current->next = alpha_token_t_create(token->numline, token->numToken, token->content, token->type, token->category);
    }
}

alpha_token_t* alpha_token_t_create(unsigned int _numline, unsigned int _numToken, char* _content, char* _type, char* _category){
    alpha_token_t *token = (alpha_token_t*) malloc(sizeof(alpha_token_t));
    if(token == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    token->numline = _numline;
    token->numToken = _numToken;
    token->content = strdup(_content);
    token->type = _type;
    token->category = _category;
    token->next = NULL;
    if(_type == "STRING"){ 
        check_escape_characters(token->content);
        remove_quotes(token->content);
    }
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
                    continue;
            }
            i++;
        } else {
            result[j++] = str[i];
        }
    }

    result[j] = '\0';
    strcpy(str, result);
}

void remove_quotes(char *str) {
    int len = strlen(str);
    
    if (len >= 2 && str[0] == '"' && str[len-1] == '"' && quotes_removed % 2 !=0 ) {
        for (int i = 0; i < len - 1; i++) {
            str[i] = str[i + 1];
        }
        str[len - 2] = '\0';
    }
    quotes_removed++;
}

void set_alpha_yyin(FILE* inputFile){ yyin = inputFile; }