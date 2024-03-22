%{
#include "../syntax_analyzer/parser.hpp"
#include "scanner.hpp"
unsigned int start_multi_comment;
unsigned int end_line_comment;
unsigned int tokensCount = 0;
int quotes_removed = -1;
int nested_comment = 0;
%}

%option noyywrap
%option yylineno
%option outfile = "scanner.cpp"

%x COMMENT

%% 

"if"                    {return IF;} 
"else"                  {return ELSE;}
"while"                 {return WHILE;}
"for"                   {return FOR;}
"function"              {return FUNCTION;}
"return"                {return RETURN;}
"break"                 {return BREAK;}
"continue"              {return CONTINUE;}
"and"                   {return AND;}
"not"                   {return NOT;}
"or"                    {return OR;}
"local"                 {return LOCAL;}
"true"                  {return TRUE;}
"false"                 {return FALSE;}
"nil"                   {return NIL;}
[0-9]+                  {return INTEGER;}
[0-9]+\.[0-9]+          {return REAL;}
[a-zA-Z]+[_a-zA-Z0-9]*  {return ID;}
\"([^\"]|"\\\"")*\"     {return STRING;}
"="                     {return ASSIGN;}
"+"                     {return ADD;}
"-"                     {return SUB;}
"*"                     {return MUL;}
"/"                     {return DIV;}
"%"                     {return MODULO;}
"=="                    {return EQUAL;}
"!="                    {return NOT_EQUAL;}
"++"                    {return PLUS_PLUS;}
"--"                    {return MINUS_MINUS;}
">"                     {return GREATER;}
"<"                     {return LESSER;}
">="                    {return GREATER_EQUAL;}
"<="                    {return LESSER_EQUAL;}
"{"                     {return LCURLY;}
"}"                     {return RCURLY;}
"["                     {return LSQUARE;}
"]"                     {return LSQUARE;}
"("                     {return LPAREN;}
")"                     {return RPAREN;}
";"                     {return SEMICOLON;}
","                     {return COMMA;}
":"                     {return COLON;}
"::"                    {return DCOLON;}
"."                     {return PERIOD;}
".."                    {return DPERIOD;}
[ \t\n\r]+              /* Do nothing for whitespace */
.                       {
                            if(!strcmp(yytext,"\"")) printf("There is an unclosed string in line %d",yylineno);
                            else printf("Undefined input %s in line %d\n",yytext,yylineno);
                            exit(EXIT_FAILURE);
                        }
"//".*                  {}

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
            }
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