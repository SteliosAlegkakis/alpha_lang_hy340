%{
#include "./parser_lib/parser_lib.hpp"
%}



%error-verbose
%name-prefix="alpha_yy"

%union {
  char* stringValue;
  int intValue;
  unsigned int uintValue;
  double realValue;
  struct SymtabEntry* symbol;
  struct expr* expr;
  struct call* call;
  struct stmt_t* stmt_stmt;
}

%start program

%token <stringValue> ADD SUB MUL DIV PLUS_PLUS MINUS_MINUS MODULO
%token <stringValue> EQUAL NOT_EQUAL GREATER LESSER LESSER_EQUAL GREATER_EQUAL
%token <stringValue> LPAREN RPAREN LCURLY RCURLY LSQUARE RSQUARE COLON SEMICOLON DCOLON COMMA PERIOD DPERIOD 
%token <stringValue> IF ELSE WHILE FOR FUNCTION RETURN AND NOT OR LOCAL ASSIGN 
%token <stringValue>  NIL TRUE FALSE 
%token <stringValue> STRING 
%token <stringValue> ID 
%token <intValue> INTEGER 
%token <realValue> REAL
%token <stmt_stmt> BREAK CONTINUE

%type <stmt_stmt> statements stmt  block ifstmt
%type <symbol> idlist whilestmt forstmt returnstmt funcprefix funcdef

%type <expr> lvalue assignment const expr primary member term elist call objectdef indexed indexedelem
%type <call> methodcall normcall callsuffix
%type <uintValue>ifprefix 
%type <stringValue> funcname
%type <uintValue> funcbody


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

statements:   statements stmt {$$ =  manage_statements($1, $2); fprintf(rulesFile, "statements -> statements stmt\n");}
              |
              ;

stmt:         expr SEMICOLON      {$$ = (stmt_t*) 0; fprintf(rulesFile, "stmt -> expr SEMICOLON\n");}
              |ifstmt             {$$ = $1; fprintf(rulesFile, "stmt -> ifstmt\n");}
              |whilestmt          {$$ = (stmt_t*) 0; fprintf(rulesFile, "stmt -> whilestmt\n");}
              |forstmt            {$$ = (stmt_t*) 0; fprintf(rulesFile, "stmt -> forstmt\n");}
              |returnstmt         {$$ = (stmt_t*) 0; fprintf(rulesFile, "stmt -> returnstmt\n");}
              |BREAK SEMICOLON    {$$ = $1;  manage_break(); fprintf(rulesFile, "stmt -> BREAK SEMICOLON\n");}
              |CONTINUE SEMICOLON {$$ = $1;  manage_continue(); fprintf(rulesFile, "stmt -> CONTINUE SEMICOLON\n");}
              |block              {$$ = $1; fprintf(rulesFile, "stmt -> block\n");}
              |funcdef            {$$ = (stmt_t*) 0; fprintf(rulesFile, "stmt -> funcdef\n");} 
              |SEMICOLON          {$$ = (stmt_t*) 0; fprintf(rulesFile, "stmt -> SEMICOLON\n");}
              ;

expr:         assignment               {$$ = $1; fprintf(rulesFile, "expr -> assignment\n");}
              |expr ADD expr           {$$ = manage_arithmetic_operation(_add, $1, $3); fprintf(rulesFile, "expr -> expr ADD expr\n");}
              |expr SUB expr           {$$ = manage_arithmetic_operation(_sub, $1, $3); fprintf(rulesFile, "expr -> expr SUB expr\n");}           
              |expr MUL expr           {$$ = manage_arithmetic_operation(_mul, $1, $3); fprintf(rulesFile, "expr -> expr MUL expr\n");}           
              |expr DIV expr           {$$ = manage_arithmetic_operation(_div, $1, $3); fprintf(rulesFile, "expr -> expr DIV expr\n");}           
              |expr MODULO expr        {$$ = manage_arithmetic_operation(_mod, $1, $3); fprintf(rulesFile, "expr -> expr MODULO expr\n");}        
              |expr GREATER expr       {$$ = manage_relative_operation(_if_greater, $1, $3); fprintf(rulesFile, "expr -> expr GREATER expr\n");}       
              |expr GREATER_EQUAL expr {$$ = manage_relative_operation(_if_greatereq, $1, $3); fprintf(rulesFile, "expr -> expr GREATER_EQUAL expr\n");}
              |expr LESSER expr        {$$ = manage_relative_operation(_if_less, $1, $3); fprintf(rulesFile, "expr -> expr LESSER expr\n");}        
              |expr LESSER_EQUAL expr  {$$ = manage_relative_operation(_if_lesseq, $1, $3); fprintf(rulesFile, "expr -> expr LESSER_EQUAL expr\n");}  
              |expr EQUAL expr         {$$ = manage_relative_operation(_if_eq, $1, $3); fprintf(rulesFile, "expr -> expr EQUAL expr\n");}         
              |expr NOT_EQUAL expr     {$$ = manage_relative_operation(_if_noteq, $1, $3); fprintf(rulesFile, "expr -> expr NOT_EQUAL expr\n");}     
              |expr AND expr           {$$ = manage_bool_operation(_and, $1, $3);fprintf(rulesFile, "expr -> expr AND expr\n");}           
              |expr OR expr            {$$ = manage_bool_operation(_or, $1, $3);fprintf(rulesFile, "expr -> expr OR expr\n");}           
              |term                    {$$ = $1; fprintf(rulesFile, "expr -> term\n");}
              ;

term:         LPAREN expr RPAREN     {$$ = $2; fprintf(rulesFile,"term -> LPAREN expr RPAREN\n");}
              |SUB expr              {$$ = manage_uminus_expr($2); fprintf(rulesFile,"term -> SUB expr\n");} %prec UMINUS
              |NOT expr              {$$ = manage_not_expr($2); fprintf(rulesFile,"term -> NOT expr\n");}
              |PLUS_PLUS lvalue      {$$ = manage_plusplus_lvalue($2); fprintf(rulesFile,"term -> PLUS_PLUS lvalue\n");}
              |lvalue PLUS_PLUS      {$$ = manage_lvalue_plusplus($1); fprintf(rulesFile,"term -> lvalue PLUS_PLUS\n");}
              |MINUS_MINUS lvalue    {$$ = manage_minusminus_lvalue($2); fprintf(rulesFile,"term -> MINUS_MINUS lvalue\n");}
              |lvalue MINUS_MINUS    {$$ = manage_lvalue_minusminus($1); fprintf(rulesFile,"term -> lvalue MINUS_MINUS\n");} 
              |primary               {$$ = $1; fprintf(rulesFile, "term -> primary\n");}
              ;

assignment:   lvalue ASSIGN expr { $$ = manage_assignment($1, $3); fprintf(rulesFile,"assignment -> lvalue ASSIGN expr\n");}
              ;

primary:      lvalue                  {$$ = emit_if_table_item($1); fprintf(rulesFile, "primary -> lvalue\n");}
              |call                   {$$ = $1; fprintf(rulesFile, "primary -> call\n");}
              |objectdef              {$$ = $1; fprintf(rulesFile, "primary -> objectdef\n");}
              |LPAREN funcdef RPAREN  {$$ = manage_primary_funcdef($2); fprintf(rulesFile, "primary -> LPAREN funcdef RPAREN\n");}
              |const                  {$$ = $1; fprintf(rulesFile, "primary -> const\n");}
              ;

lvalue:       ID          {$$ = manage_lvalue_id($1); fprintf(rulesFile, "lvalue -> ID\n");}
              |LOCAL ID   {$$ = manage_lvalue_local_id($2); fprintf(rulesFile,"lvalue -> LOCAL ID\n");}
              |DCOLON ID  {$$ = manage_lvalue_global_id($2); fprintf(rulesFile,"lvalue -> DCOLON ID\n");}
              |member     {$$ = $1; fprintf(rulesFile,"lvalue -> member\n");}
              ;

member:       lvalue PERIOD ID             {$$ = member_item($1, $3); fprintf(rulesFile, "member -> lvalue PERIOD ID\n");}
              |lvalue LSQUARE expr RSQUARE {$$ = manage_member_item_lvalue_lsquare_expr_rsquare($1, $3); fprintf(rulesFile, "member -> lvalue LSQUARE expr RSQUARE\n");}
              |call PERIOD ID              {$$ = member_item($1, $3); fprintf(rulesFile, "member -> call PERIOD ID\n");}
              |call LSQUARE expr RSQUARE   {$$ = manage_member_item_lvalue_lsquare_expr_rsquare($1, $3); fprintf(rulesFile, "member -> call LSQUARE expr RSQUARE\n");}
              ;

call:         call LPAREN elist RPAREN                   {$$ = make_call($1, $3); fprintf(rulesFile, "call -> call LPAREN elist RPAREN\n");}
              |lvalue callsuffix                         {$$ = manage_call_lvalue_callsuffix($1, $2); fprintf(rulesFile, "call -> lvalue callsuffix\n");}
              |LPAREN funcdef RPAREN LPAREN elist RPAREN {$$ = manage_call_funcdef($2 ,$5); fprintf(rulesFile, "call -> LPAREN funcdef RPAREN LPAREN elist RPAREN\n");}
              ;
              
callsuffix:   normcall    {$$ = $1; fprintf(rulesFile, "callsuffix -> normcall\n");}
              |methodcall {$$ = $1; fprintf(rulesFile, "callsuffix -> methodcall\n");}
              ;
            
normcall:     LPAREN elist RPAREN {$$ = manage_normcall($2); fprintf(rulesFile, "normcall -> LPAREN elist RPAREN\n");}
              ;
 
methodcall:   DPERIOD ID LPAREN elist RPAREN {$$ = manage_methodcall($4, $2); fprintf(rulesFile, "methodcall -> DPERIOD ID LPAREN elist RPAREN\n");}
              ;

elist:        expr              {$$ = $1; $$->next = NULL; fprintf(rulesFile, "elist -> expr\n");}
              |expr COMMA elist {$$ = manage_elist($1,$3); fprintf(rulesFile, "elist -> elist COMMA expr\n");}
              |                 {$$ = (expr*) 0; fprintf(rulesFile, "elist -> \n");}
              ;

objectdef:    LSQUARE elist RSQUARE    {$$ = manage_objectdef_elist($2); fprintf(rulesFile, "objectdef -> LSQUARE elist RSQUARE\n");}
              |LSQUARE indexed RSQUARE {$$ = manage_objectdef_indexed($2); fprintf(rulesFile, "objectdef -> LSQUARE indexed RSQUARE\n");}
              ;

indexed:      indexedelem                 {$$ = $1; fprintf(rulesFile, "indexed -> indexedelem\n");}
              |indexedelem COMMA indexed  {$$ = manage_indexed($1, $3); fprintf(rulesFile, "indexed -> indexed COMMA indexedelem\n");}
              ;

indexedelem:  LCURLY expr COLON expr RCURLY {$$ = manage_indexedelem($2, $4); fprintf(rulesFile, "indexedelem -> LCURLY expr COLON expr RCURLY\n");}
              ;

block:        LCURLY {if(!block_b) increase_scope();} statements RCURLY {if(!block_b){symTab_hide();decrease_scope();} fprintf(rulesFile, "block -> LCURLY statements RCURLY\n");} 
              ;

funcname:     ID {$$ = manage_funcname_named($1); assert($$); fprintf(rulesFile, "funcname -> ID\n");}
              |  {$$ = manage_funcname_anonymous(); assert($$); fprintf(rulesFile, "funcname -> \n");}
              ;

funcprefix:   FUNCTION funcname { assert($2); $$ = manage_funcprefix($2); assert($$); fprintf(rulesFile, "funcprefix -> FUNCTION funcname\n");}
              ;

funcargs:     LPAREN idlist RPAREN {manage_funcargs(); fprintf(rulesFile, "funcargs -> LPAREN idlist RPAREN\n");}
              ;

funcbody:     block {$$ = manage_funcbody(); fprintf(rulesFile, "funcbody -> block\n");}
              ;

funcdef:      funcprefix funcargs funcbody {$$ = manage_funcdef($1,$3); assert($$); assert($1); }
              ;

const:        INTEGER   {$$ = new_expr_const_num($1); fprintf(rulesFile, "const -> INTEGER\n");}
              |REAL     {$$ = new_expr_const_num($1); fprintf(rulesFile, "const -> REAL\n");}
              |STRING   {$$ = new_expr_const_string($1); fprintf(rulesFile, "const -> STRING\n");}
              |NIL      {$$ = new_expr(nil_e); fprintf(rulesFile, "const -> NIL\n");}
              |TRUE     {$$ = new_expr_const_bool(1); fprintf(rulesFile, "const -> TRUE\n");}
              |FALSE    {$$ = new_expr_const_bool(0); fprintf(rulesFile, "const -> FALSE\n");} 
              ;

idlist:       ID                {manage_idlist_id($1); fprintf(rulesFile,"idlist -> ID\n");}
              |idlist COMMA ID  {manage_idlist_comma_id($3); fprintf(rulesFile,"idlist -> idlist COMMA ID\n");}
              |                 {fprintf(rulesFile,"idlist -> \n");}
              ;

ifprefix:     IF LPAREN expr RPAREN {$$ = manage_ifprefix($3);}

ifstmt:       ifprefix stmt ELSE stmt {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt ELSE stmt\n");}
              | ifprefix stmt {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt\n");}
              ;

loopstart:    {++loopCounter;}
              ;
loopend:      {--loopCounter;}
              ;
loopstmt:     loopstart stmt loopend {}
              ;

whilestmt:    WHILE LPAREN expr RPAREN{block_b = true;} loopstmt{block_b = false;}
              ;

forstmt:      FOR LPAREN elist SEMICOLON expr SEMICOLON elist RPAREN {block_b = true;} loopstmt {block_b = false;}
              ;

returnstmt:   RETURN expr SEMICOLON { manage_return_expr($2);  fprintf(rulesFile, "returnstmt -> RETURN expr SEMICOLON\n");}
              |RETURN SEMICOLON     { manage_return(); fprintf(rulesFile, "returnstmt -> RETURN SEMICOLON\n");}
              ;

%%

int main(int argc, char** argv) {
	if(!(alpha_yyin = fopen(argv[1], "r"))){
    printf("Could not open input file\n");
    return 1;
  }
  if(!(rulesFile = fopen("rules.txt", "w"))){
    printf("Could not open rules file\n");
    return 1;
  }
	init_library_func();
  yyparse();
  fprintf(rulesFile, "EOF\n");
  fclose(rulesFile);
}
