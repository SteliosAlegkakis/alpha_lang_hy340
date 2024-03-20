%{
#include "../syntax_analyzer/parser.hpp"
#include "./scanner.h"
unsigned int start_multi_comment;
unsigned int end_line_comment;
unsigned int tokensCount = 0;
int quotes_removed = -1;
int nested_comment = 0;
%}

%option noyywrap
%option yylineno
%option prefix = "alpha_yy"
%option outfile = "scanner.cpp"

%x COMMENT

%% 

"if"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD IF","enumerated"),(alpha_token_t**)yylval);return IF;} 
"else"                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD ELSE","enumerated"),(alpha_token_t**)yylval);return ELSE;}
"while"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD WHILE","enumerated"),(alpha_token_t**)yylval); return WHILE;}
"for"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD FOR","enumerated"),(alpha_token_t**)yylval);return FOR;}
"function"              {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD FUNCTION","enumerated"),(alpha_token_t**)yylval);return FUNCTION;}
"return"                {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD RETURN","enumerated"),(alpha_token_t**)yylval); return RETURN;}
"break"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD BREAK","enumerated"),(alpha_token_t**)yylval);return BREAK;}
"continue"              {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD CONTINUE","enumerated"),(alpha_token_t**)yylval);return CONTINUE;}
"and"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD AND","enumerated"),(alpha_token_t**)yylval);return AND;}
"not"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD NOT","enumerated"),(alpha_token_t**)yylval);return NOT;}
"or"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD OR","enumerated"),(alpha_token_t**)yylval);return OR;}
"local"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD LOCAL","enumerated"),(alpha_token_t**)yylval);return LOCAL;}
"true"                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD TRUE","enumerated"),(alpha_token_t**)yylval);return TRUE;}
"false"                 {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD FALSE","enumerated"),(alpha_token_t**)yylval);return FALSE;}
"nil"                   {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"KEYWORD NIL","enumerated"),(alpha_token_t**)yylval);return NIL;}
[0-9]+                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"INTCONST","integer"),(alpha_token_t**)yylval);return INTEGER;}
[0-9]+\.[0-9]+          {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"REALCONST","real"),(alpha_token_t**)yylval);return REAL;}
[a-zA-Z]+[_a-zA-Z0-9]*  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"IDENTIFIER","char*"),(alpha_token_t**)yylval);return ID;}
\"([^\"]|"\\\"")*\"     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"STRING","char*"),(alpha_token_t**)yylval);return STRING;}
"="                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR ASSIGN","enumerated"),(alpha_token_t**)yylval);return ASSIGN;}
"+"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR PLUS","enumerated"),(alpha_token_t**)yylval);return ADD;}
"-"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR MINUS","enumerated"),(alpha_token_t**)yylval);return SUB;}
"*"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR MUL","enumerated"),(alpha_token_t**)yylval);return MUL;}
"/"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR DIV","enumerated"),(alpha_token_t**)yylval);return DIV;}
"%"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR MODULO","enumerated"),(alpha_token_t**)yylval);return MODULO;}
"=="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR EQUAL","enumerated"),(alpha_token_t**)yylval);return EQUAL;}
"!="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR NOT_EQUAL","enumerated"),(alpha_token_t**)yylval);return NOT_EQUAL;}
"++"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR PLUS_PLUS","enumerated"),(alpha_token_t**)yylval);return PLUS_PLUS;}
"--"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR MINUS_MINUS","enumerated"),(alpha_token_t**)yylval);return MINUS_MINUS;}
">"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR GREATER_THAN","enumerated"),(alpha_token_t**)yylval);return GREATER;}
"<"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR LESSER_THAN","enumerated"),(alpha_token_t**)yylval);return LESSER;}
">="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR GREATER_OR_EQUAL","enumerated"),(alpha_token_t**)yylval);return GREATER_EQUAL;}
"<="                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"OPERATOR LESSER_OR_EQUAL","enumerated"),(alpha_token_t**)yylval);return LESSER_EQUAL;}
"{"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION LEFT_CURLY_BR","enumerated"),(alpha_token_t**)yylval);return LCURLY;}
"}"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION RIGHT_CURLY_BR","enumerated"),(alpha_token_t**)yylval);return RCURLY;}
"["                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION LEFT_SQUARE_BR","enumerated"),(alpha_token_t**)yylval);return LSQUARE;}
"]"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION RIGHT_SQUARE_BR","enumerated"),(alpha_token_t**)yylval);return LSQUARE;}
"("                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION LEFT_PAR","enumerated"),(alpha_token_t**)yylval);return LPAREN;}
")"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION RIGHT_PAR","enumerated"),(alpha_token_t**)yylval);return RPAREN;}
";"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION SEMICOLON","enumerated"),(alpha_token_t**)yylval);return SEMICOLON;}
","                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION COMMA","enumerated"),(alpha_token_t**)yylval);return COMMA;}
":"                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION COLON","enumerated"),(alpha_token_t**)yylval);return COLON;}
"::"                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION DOUBLE_COLON","enumerated"),(alpha_token_t**)yylval);return DCOLON;}
"."                     {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION PERIOD","enumerated"),(alpha_token_t**)yylval);return PERIOD;}
".."                    {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,yytext,"PUNCTUATION DOUBLE_PERIOD","enumerated"),(alpha_token_t**)yylval);return DPERIOD;}
[ \t\n\r]+              /* Do nothing for whitespace */
.                       {
                            if(!strcmp(yytext,"\"")) printf("There is an unclosed string in line %d",yylineno);
                            else printf("Undefined input %s in line %d\n",yytext,yylineno);
                            exit(EXIT_FAILURE);
                        }
"//".*                  {add_token_to_list(alpha_token_t_create(yylineno,++tokensCount,(char*)"","COMMENT LINE_COMMENT","enumerated"),(alpha_token_t**)yylval);}

"/*" {
    if (nested_comment == 0) {
        BEGIN(COMMENT);
    }
    ++nested_comment;
   
    start_multi_comment=yylineno;
}

<COMMENT>{
    "/*" {
        ++nested_comment;
    }
    "*/" {
        --nested_comment;
        if (nested_comment == 0) {
            BEGIN(INITIAL);
            {end_line_comment = yylineno;
                char str[100];
                sprintf(str,"%d - %d",start_multi_comment,end_line_comment);
                add_token_to_list(alpha_token_t_create(start_multi_comment,++tokensCount,str,"COMMENT BLOCK_COMMENT","enumerated"),(alpha_token_t**)yylval);}
        }
    }
    .|\n {}
}


<COMMENT><<EOF>> {
        printf("Unclosed comment detected starting at line %d\n", start_multi_comment);
        exit(EXIT_FAILURE);
}
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

alpha_token_t* alpha_token_t_create(unsigned int _numline, unsigned int _numToken, char* _content,const char* _type, const char* _category){
    alpha_token_t *token = (alpha_token_t*) malloc(sizeof(alpha_token_t));
    if(token == NULL){
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    token->numline = _numline;
    token->numToken = _numToken;
    token->content = strdup(_content);
    token->type = (char*)_type;
    token->category = (char*)_category;
    token->next = NULL;
    if(_type == "STRING"){ 
        check_escape_characters(token->content);
        remove_quotes(token->content);
    }
    return token;
}

void check_escape_characters(char* str){
    int length = strlen(str);
    char* result = (char*)malloc(sizeof(char)*(length+1)); // +1 for the null terminator
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
                    result[j++] = '\\';//escape
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
                    // break;
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