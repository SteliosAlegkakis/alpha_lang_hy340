%{
#include <stdio.h>
int alpha_yyerror(const char* yaccProvidedMessage);
int alpha_yylex(void);
extern int alpha_yylineno;
extern char* alpha_yytext;
extern FILE* alpha_yyin;

%}

%error-verbose
%name-prefix="alpha_yy"

%union {
char* stringValue;
int intValue;
double realValue;
}

%start program

%token NUMBER
%token ADD SUB MUL DIV PLUS_PLUS MINUS_MINUS MODULO
%token EQUAL NOT_EQUAL GREATER LESSER LESSER_EQUAL GREATER_EQUAL
%token LPAREN RPAREN LCURLY RCURLY LSQUARE RSQUARE COLON SEMICOLON DCOLON COMMA PERIOD DPERIOD 
%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL ASSIGN 
%token ID INTEGER REAL NIL TRUE FALSE STRING 

%right ASSIGN
%left OR
%left AND
%nonassoc EQUAL NOT_EQUAL 
%nonassoc GREATER GREATER_EQUAL LESSER LESSER_EQUAL
%left ADD SUB
%left MUL DIV MODULO
%right NOT PLUS_PLUS MINUS_MINUS 
%nonassoc UMINUS
%left PERIOD DPERIOD
%left LSQUARE RSQUARE 
%left LPAREN RPAREN 

%%
program: expression
        /*empty*/
        ;

expression: INTEGER {printf("found an int");}
            |ID {printf("found an id");}     
            ;

%%

int alpha_yyerror(const char* yaccProvidedMessage) {
  fprintf(stderr, "%s %d %s\n",yaccProvidedMessage, alpha_yylineno, alpha_yytext);
  return 0;
}

int main(int argc, char** argv) {
  if(!(alpha_yyin = fopen(argv[1], "r"))) return 1;
  alpha_yyparse();
  return 0;
}
