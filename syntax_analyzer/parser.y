%{
#include "./symbol_table/symbol_table.hpp"
int alpha_yyerror(const char* yaccProvidedMessage);
int alpha_yylex(void);
extern int alpha_yylineno;
extern char* alpha_yytext;
extern FILE* alpha_yyin;
FILE* rulesFile = fopen("rules.txt", "w");
int anonymousCounter = 0;
extern bool isFormal;
char* make_anonymous_func();
bool is_libfunc(char* id);
void print_error(const char* msg);
const char* unionType_toString(int union_type);
%}



%error-verbose
%name-prefix="alpha_yy"

%union {
char* stringValue;
int intValue;
double realValue;
 struct SymtabEntry* exprNode;
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
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left PERIOD DPERIOD
%left LSQUARE RSQUARE 
%left LPAREN RPAREN 


%%

program:      statements {fprintf(rulesFile, "program -> statements\n");}
              ;

statements:   statements stmt {fprintf(rulesFile, "statements -> statements stmt\n");}
              |
              ;

stmt:         expr SEMICOLON {fprintf(rulesFile, "stmt -> expr SEMICOLON\n");}
              |ifstmt {fprintf(rulesFile, "stmt -> ifstmt\n");}
              |whilestmt {fprintf(rulesFile, "stmt -> whilestmt\n");}
              |forstmt {fprintf(rulesFile, "stmt -> forstmt\n");}
              |returnstmt {fprintf(rulesFile, "stmt -> returnstmt\n");}
              |BREAK SEMICOLON {fprintf(rulesFile, "stmt -> BREAK SEMICOLON\n");}
              |CONTINUE SEMICOLON {fprintf(rulesFile, "stmt -> CONTINUE SEMICOLON\n");}
              |block {fprintf(rulesFile, "stmt -> block\n");}
              |funcdef {fprintf(rulesFile, "stmt -> funcdef\n");} 
              |SEMICOLON {fprintf(rulesFile, "stmt -> SEMICOLON\n");}
              ;

expr:         assignment {fprintf(rulesFile, "expr -> assignment\n");}
              |expr ADD expr {fprintf(rulesFile, "expr -> expr ADD expr\n");}
              |expr SUB expr {fprintf(rulesFile, "expr -> expr SUB expr\n");}           
              |expr MUL expr {fprintf(rulesFile, "expr -> expr MUL expr\n");}           
              |expr DIV expr {fprintf(rulesFile, "expr -> expr DIV expr\n");}           
              |expr MODULO expr {fprintf(rulesFile, "expr -> expr MODULO expr\n");}        
              |expr GREATER expr {fprintf(rulesFile, "expr -> expr GREATER expr\n");}       
              |expr GREATER_EQUAL expr {fprintf(rulesFile, "expr -> expr GREATER_EQUAL expr\n");}
              |expr LESSER expr {fprintf(rulesFile, "expr -> expr LESSER expr\n");}        
              |expr LESSER_EQUAL expr {fprintf(rulesFile, "expr -> expr LESSER_EQUAL expr\n");}  
              |expr EQUAL expr {fprintf(rulesFile, "expr -> expr EQUAL expr\n");}         
              |expr NOT_EQUAL expr {fprintf(rulesFile, "expr -> expr NOT_EQUAL expr\n");}     
              |expr AND expr {fprintf(rulesFile, "expr -> expr AND expr\n");}           
              |expr OR expr  {fprintf(rulesFile, "expr -> expr OR expr\n");}           
              |term {fprintf(rulesFile, "expr -> term\n");}
              ;

term:         LPAREN expr RPAREN {fprintf(rulesFile, "term -> LPAREN expr RPAREN\n");}
              |SUB expr %prec UMINUS {fprintf(rulesFile, "term -> SUB expr\n");}
              |NOT expr  {fprintf(rulesFile, "term -> NOT expr\n");}
              |PLUS_PLUS lvalue {if($2->uniontype == function) print_error("error, function id used as lvalue"); fprintf(rulesFile, "term -> PLUS_PLUS lvalue\n");}
              |lvalue {if($1->uniontype == function) print_error("error, function id used as lvalue");} PLUS_PLUS {fprintf(rulesFile, "term -> lvalue PLUS_PLUS\n");}
              |MINUS_MINUS lvalue {if($2->uniontype == function) print_error("error, function id used as lvalue");fprintf(rulesFile, "term -> MINUS_MINUS lvalue\n");}
              |lvalue {if($1->uniontype == function) print_error("error, function id used as lvalue");} MINUS_MINUS {fprintf(rulesFile, "term -> lvalue MINUS_MINUS\n");} 
              |primary {fprintf(rulesFile, "term -> primary\n");}
              ;

assignment:   lvalue {if($1->uniontype == function) print_error("error, function id used as lvalue");} ASSIGN expr   {fprintf(rulesFile, "assignment -> lvalue ASSIGN expr\n");}
              ;

primary:      lvalue {fprintf(rulesFile, "primary -> lvalue\n");}
              |call {fprintf(rulesFile, "primary -> call\n");}
              |objectdef {fprintf(rulesFile, "primary -> objectdef\n");}
              |LPAREN funcdef RPAREN {fprintf(rulesFile, "primary -> LPAREN funcdef RPAREN\n");}
              |const {fprintf(rulesFile, "primary -> const\n");}
              ;

lvalue:       ID { 
                if(!symTab_lookup($1)) {
                  symTab_insert($1, alpha_yylineno, variable, local);
                  $$ = symTab_lookup($1, get_current_scope());
                }
                else{
                  $$ = symTab_lookup($1, get_current_scope());
                }
                 fprintf(rulesFile, "lvalue -> ID\n");
			        }
              |LOCAL ID {
                if(!symTab_lookup($2, get_current_scope())){
                  if(!is_libfunc($2)){
                    symTab_insert($2, alpha_yylineno, variable, local);
                    $$ = symTab_lookup($2, get_current_scope());
                  }
                  else
                    print_error("error, cannot overide library functions:");
                }
                else {
                  $$ = symTab_lookup($2, get_current_scope());
                }
                fprintf(rulesFile, "lvalue -> LOCAL ID\n");
              }
              |DCOLON ID {
                if(!symTab_lookup($2,0)) {
                  print_error("error, could not find global identifier:");
                }
                else{
                  $$ = symTab_lookup($2, 0);
                }
                fprintf(rulesFile, "lvalue -> DCOLON ID\n");
              }
              |member  {fprintf(rulesFile, "lvalue -> member\n");}
              ;

member:       lvalue PERIOD ID {fprintf(rulesFile, "member -> lvalue PERIOD ID\n");}
              |lvalue LSQUARE expr RSQUARE {fprintf(rulesFile, "member -> lvalue LSQUARE expr RSQUARE\n");}
              |call PERIOD ID {fprintf(rulesFile, "member -> call PERIOD ID\n");}
              |call LSQUARE expr RSQUARE {fprintf(rulesFile, "member -> call LSQUARE expr RSQUARE\n");}
              ;

call:         call LPAREN elist RPAREN {fprintf(rulesFile, "call -> call LPAREN elist RPAREN\n");}
              |lvalue {} callsuffix {fprintf(rulesFile, "call -> lvalue callsuffix\n");}
              |LPAREN funcdef RPAREN LPAREN elist RPAREN {fprintf(rulesFile, "call -> LPAREN funcdef RPAREN LPAREN elist RPAREN\n");}
              ;
              
callsuffix:   normcall {fprintf(rulesFile, "callsuffix -> normcall\n");}
              |methodcall {fprintf(rulesFile, "callsuffix -> methodcall\n");}
              ;
            
normcall:     LPAREN elist RPAREN {fprintf(rulesFile, "normcall -> LPAREN elist RPAREN\n");}
              ;
 
methodcall:   DPERIOD ID LPAREN elist RPAREN {fprintf(rulesFile, "methodcall -> DPERIOD ID LPAREN elist RPAREN\n");}
              ;

elist:        expr {fprintf(rulesFile, "elist -> expr\n");}
              |elist COMMA expr {fprintf(rulesFile, "elist -> elist COMMA expr\n");}
              | {fprintf(rulesFile, "elist -> \n");}
              ;

objectdef:    LSQUARE elist RSQUARE {fprintf(rulesFile, "objectdef -> LSQUARE elist RSQUARE\n");}
              |LSQUARE indexed RSQUARE {fprintf(rulesFile, "objectdef -> LSQUARE indexed RSQUARE\n");}
              ;

indexed:      indexedelem {fprintf(rulesFile, "indexed -> indexedelem\n");}
              |indexed COMMA indexedelem  {fprintf(rulesFile, "indexed -> indexed COMMA indexedelem\n");}
              ;

indexedelem:  LCURLY expr COLON expr RCURLY {fprintf(rulesFile, "indexedelem -> LCURLY expr COLON expr RCURLY\n");}
              ;

block:        LCURLY {increase_scope();} statements RCURLY {symTab_hide();decrease_scope(); fprintf(rulesFile, "block -> LCURLY statements RCURLY\n");} 
              ;

funcdef:      FUNCTION ID {
              if(!symTab_lookup($2, get_current_scope())) {
                if(is_libfunc($2)) print_error("error, cannot override library functions:");
                else symTab_insert($2, alpha_yylineno, function, userfunc);
              }
				      else print_error("error, redefinition of identifier:");
			        } LPAREN {increase_scope(); isFormal = true; } idlist RPAREN {decrease_scope(); isFormal = false;} block {fprintf(rulesFile, "funcdef -> FUNCTION ID LPAREN idlist RPAREN block\n");}
              |FUNCTION { symTab_insert(make_anonymous_func(), alpha_yylineno, function, userfunc); } LPAREN {increase_scope(); isFormal = true; } idlist RPAREN {decrease_scope(); isFormal = true; } block {fprintf(rulesFile, "funcdef -> FUNCTION LPAREN idlist RPAREN block\n");}
              ;

const:        INTEGER {fprintf(rulesFile, "const -> INTEGER\n");}
              |REAL {fprintf(rulesFile, "const -> REAL\n");}
              |STRING {fprintf(rulesFile, "const -> STRING\n");}
              |NIL {fprintf(rulesFile, "const -> NIL\n");}
              |TRUE {fprintf(rulesFile, "const -> TRUE\n");}
              |FALSE {fprintf(rulesFile, "const -> FALSE\n");}
              ;

idlist:       ID {
                if(isFormal){
                  if(symTab_lookup($1, get_current_scope())) {
                    print_error("error, redifinition of formal argument:");
                  }
                  else if (is_libfunc($1)){
                    print_error("error, cannot override library functions:");
                  }
                  else {
                    symTab_insert($1, alpha_yylineno, variable, formal);
                  }
                }
                else if(!symTab_lookup($1, get_current_scope())) {
                  symTab_insert($1, alpha_yylineno, variable, local);
                }
                {fprintf(rulesFile, "idlist -> ID\n");}
              }
              |idlist COMMA ID {
                if(isFormal){
                  if(symTab_lookup($3, get_current_scope())){
                    print_error("error, redifinition of formal argument:");
                  }
                  else if (is_libfunc($3)){
                    print_error("error, cannot override library functions:");
                  }
                  else {
                    symTab_insert($3, alpha_yylineno, variable, formal);
                  }
                }
                else if(!symTab_lookup($3, get_current_scope())){
                  symTab_insert($3, alpha_yylineno, variable, local);
                }
                {fprintf(rulesFile, "idlist -> idlist COMMA ID\n");}
			        }
              | {fprintf(rulesFile, "idlist -> \n");}
              ;

ifstmt:       IF LPAREN expr RPAREN stmt ELSE stmt {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt ELSE stmt\n");}
              |IF LPAREN expr RPAREN stmt {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt\n");}
              ;
              
whilestmt:    WHILE LPAREN expr RPAREN stmt {fprintf(rulesFile, "whilestmt -> WHILE LPAREN expr RPAREN stmt\n");}
              ;
              
forstmt:      FOR LPAREN elist SEMICOLON expr SEMICOLON elist RPAREN stmt {fprintf(rulesFile, "forstmt -> FOR LPAREN elist SEMICOLON expr SEMICOLON elist RPAREN stmt\n");}
              ;

returnstmt:   RETURN expr SEMICOLON {fprintf(rulesFile, "returnstmt -> RETURN expr SEMICOLON\n");}
              |RETURN SEMICOLON {fprintf(rulesFile, "returnstmt -> RETURN SEMICOLON\n");}
              ;

%%

int alpha_yyerror(const char* yaccProvidedMessage) {
	fprintf(stderr, "\033[1;31m%s: '%s' in line: %d\033[0m\n",yaccProvidedMessage, alpha_yytext, alpha_yylineno);
	return 0;
}

void print_error(const char* msg) { printf("\033[1;31m%s '%s' in line: %d\033[0m\n", msg, alpha_yytext, alpha_yylineno); }

bool is_libfunc(char* id) {
	if(!strcmp(id,"print")) return true;
	if(!strcmp(id,"input")) return true;
	if(!strcmp(id,"objectmemberkeys")) return true;
	if(!strcmp(id,"objectotalmember")) return true;
	if(!strcmp(id,"objectcopy")) return true;
	if(!strcmp(id,"totalarguments"))return true;
	if(!strcmp(id,"argument")) return true;
	if(!strcmp(id,"typeof")) return true;
	if(!strcmp(id,"strtonum")) return true;
	if(!strcmp(id,"sqrt")) return true;
	if(!strcmp(id,"cos")) return true;
	if(!strcmp(id,"sin")) return true;
	return false;
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
	if(!(alpha_yyin = fopen(argv[1], "r"))){
    printf("Could not open file\n");
    return 1;
  }
	init_library_func();
  yyparse();
  fprintf(rulesFile, "EOF\n");
  fclose(rulesFile);
  return 0;
}