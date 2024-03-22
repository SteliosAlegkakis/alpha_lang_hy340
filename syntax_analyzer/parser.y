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

program:      statements
              |/*empty*/
              ;

stmt:         expr SEMICOLON
              |ifstmt
              |whilestmt
              |forstmt
              |returnstmt
              |BREAK SEMICOLON
              |CONTINUE SEMICOLON
              |block
              |funcdef
              |SEMICOLON
              ;

expr:         assignment
              |expr ADD expr
              |expr MUL expr
              |expr DIV expr
              |expr MODULO expr
              |expr GREATER expr
              |expr GREATER_EQUAL expr
              |expr LESSER expr
              |expr LESSER_EQUAL expr
              |expr EQUAL expr
              |expr NOT_EQUAL expr
              |expr AND expr
              |expr OR expr
              |term
              ;

term:         LPAREN expr RPAREN
              |SUB expr %prec UMINUS
              |NOT expr
              |PLUS_PLUS lvalue
              |lvalue PLUS_PLUS
              |MINUS_MINUS lvalue
              |lvalue MINUS_MINUS
              |primary
              ;

assignment:   lvalue ASSIGN expr {;}
              ;

primary:      lvalue
              |call
              |objectdef
              |LPAREN funcdef RPAREN
              |const
              ;

lvalue:       ID
              |LOCAL ID
              |DCOLON ID
              |member
              ;

member:       lvalue PERIOD ID
              |lvalue LSQUARE expr RSQUARE
              |call PERIOD ID
              |call LSQUARE expr RSQUARE
              ;

call:         call LPAREN elist RPAREN
              |lvalue callsuffix
              |LPAREN funcdef RPAREN LPAREN elist RPAREN
              ;
              
callsuffix:   normcall
              |methodcall
              ;
            
normcall:     LPAREN elist RPAREN
              ;
 
methodcall:   DPERIOD ID LPAREN elist RPAREN
              ;

elist:        expr
              |expr COMMA expr
                  
              ;

objectdef:    LSQUARE {} RSQUARE
              |LSQUARE elist RSQUARE
              |LSQUARE indexed RSQUARE
              ;

indexed:      indexedelem
              |indexedelem COMMA indexedelem
              
              ;

indexedelem:  LCURLY expr COLON expr RCURLY
              ;

block:        LCURLY statements RCURLY 
              ;

funcdef:      FUNCTION ID LPAREN idlist RPAREN block
              |FUNCTION LPAREN idlist RPAREN
              ;

const:        INTEGER
              |REAL
              |STRING
              |NIL
              |TRUE
              |FALSE
              ;

idlist:       ID
              |ID COMMA ID
              |/*empty*/
              ;

ifstmt:       IF LPAREN expr RPAREN stmt ELSE stmt
              |IF LPAREN expr RPAREN stmt
              ;
              
whilestmt:    WHILE LPAREN expr RPAREN stmt
              ;
              
forstmt:      FOR LPAREN elist SEMICOLON expr SEMICOLON elist SEMICOLON RPAREN stmt
              ;

returnstmt:   RETURN expr SEMICOLON
              |RETURN SEMICOLON
              ;

// ides_comma:   ides_comma ID COMMA
//               |ID COMMA
//               |ID
//               ;

statements:   statements stmt
              |stmt
              ;

// expressions_comma: expressions_comma expr COMMA
//                   |expr COMMA
//                   |expr
//                   ;

// indexedelems_comma: indexedelems_comma indexedelem COMMA
//                     |indexedelem COMMA
//                     |indexedelem
//                     ;

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
