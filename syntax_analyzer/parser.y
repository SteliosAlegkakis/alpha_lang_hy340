%{
#include <stdio.h>
#include "./symbol_table/symbol_table.hpp"
int alpha_yyerror(const char* yaccProvidedMessage);
int alpha_yylex(void);
extern int alpha_yylineno;
extern char* alpha_yytext;
extern FILE* alpha_yyin;
extern bool inFunc;
extern bool isFunc;
extern bool isFormal;
extern bool increase;
int anonymousCounter = 0;
char* make_anonymous_func();
%}

%error-verbose
%name-prefix="alpha_yy"

%union {
char* stringValue;
int intValue;
double realValue;
typedef struct SymtabEntry* exprNode;
}

%start program

%token <stringValue> ADD SUB MUL DIV PLUS_PLUS MINUS_MINUS MODULO
%token <stringValue> EQUAL NOT_EQUAL GREATER LESSER LESSER_EQUAL GREATER_EQUAL
%token <stringValue> LPAREN RPAREN LCURLY RCURLY LSQUARE RSQUARE COLON SEMICOLON DCOLON COMMA PERIOD DPERIOD 
%token <stringValue> IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND NOT OR LOCAL ASSIGN 
%token <stringValue>  NIL TRUE FALSE 
%token <stringValue> STRING 
%token <stringValue> ID 
%token <intValue> INTEGER 
%token <realValue> REAL

%type <exprNode> statements stmt
%type <exprNode> expr
%type <exprNode> term assignment primary lvalue
%type <exprNode> member call callsuffix normcall methodcall 
%type <exprNode> elist objectdef indexed indexedelem block funcdef
%type <exprNode> const idlist ifstmt whilestmt forstmt returnstmt


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
              ;

statements:   statements stmt
              |{}
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
              |expr SUB expr            
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

lvalue:       ID {if(!symTab_lookup($1, get_current_scope())) { symTab_insert($1,alpha_yylineno,variable,local); }}
              |LOCAL ID {if(!symTab_lookup($1, get_current_scope())) { symTab_insert($1,alpha_yylineno,variable,local); }}
              |DCOLON ID {if((!symTab_lookup($1,0)) && (inFunc)) { alpha_yyerror("Error: Not found variable in global scope: "); } if((!symTab_lookup($1,0)) && (!inFunc)) { symTab_insert($1,alpha_yylineno,variable,global); }}
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
              |elist COMMA expr
              |{}
              ;

objectdef:    LSQUARE elist RSQUARE
              |LSQUARE indexed RSQUARE
              ;

indexed:      indexedelem
              |indexed COMMA indexedelem
              
              ;

indexedelem:  LCURLY expr COLON expr RCURLY
              ;

block:        LCURLY {increase_scope();} statements RCURLY {decrease_scope();} 
              ;

funcdef:      FUNCTION {isFunc = true;} ID {if(!symTab_lookup($1,get_current_scope())) symTab_insert($1,alpha_yylineno,function,userfunc);} LPAREN {increase_scope();inFunc = true;isFormal = true;} idlist RPAREN {isFormal = false;} block
              |FUNCTION {isFunc = true; symTab_insert(make_anonymous_func(),alpha_yylineno,function,userfunc);} LPAREN {increase_scope();inFunc = true;isFormal = true;} idlist RPAREN {isFormal = true;} block
              ;

const:        INTEGER
              |REAL
              |STRING
              |NIL
              |TRUE
              |FALSE
              ;

idlist:       ID
              |idlist COMMA ID
              | {}
              ;

ifstmt:       IF LPAREN expr RPAREN stmt ELSE stmt
              |IF LPAREN expr RPAREN stmt
              ;
              
whilestmt:    WHILE LPAREN expr RPAREN stmt
              ;
              
forstmt:      FOR LPAREN elist SEMICOLON expr SEMICOLON elist RPAREN stmt
              ;

returnstmt:   RETURN expr SEMICOLON
              |RETURN SEMICOLON
              ;

%%

int alpha_yyerror(const char* yaccProvidedMessage) {
  fprintf(stderr, "%s %d %s\n",yaccProvidedMessage, alpha_yylineno, alpha_yytext);
  return 0;
}

char* make_anonymous_func() {
  char* func = (char*)"_anonymousFunc";
  int  length = strlen(func) + snprintf(NULL, 0, "%d", anonymousCounter) + 1;
  char* result = (char*)malloc(length);

  if(result) {
    sprintf(result, "%s%d", func, anonymousCounter++); 
    return result;
  }
  else {
    printf("Out of memmory\n"); 
    exit(EXIT_FAILURE);
  }
  
}

int main(int argc, char** argv) {
  if(!(alpha_yyin = fopen(argv[1], "r"))) return 1;
  init_library_func();
  alpha_yyparse();
  symTab_print();
  return 0;
}