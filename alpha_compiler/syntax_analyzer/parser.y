%{
#include "./parser_lib/parser_lib.hpp"
#include "../tcode_generator/tcode.hpp"
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
  struct forprefix* _forprefix;
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

%type <stmt_stmt> statements stmt stmts block ifstmt whilestmt forstmt loopstmt
%type <symbol> idlist returnstmt funcprefix funcdef
%type <_forprefix> forprefix

%type <expr> lvalue assignment const expr primary member term elist call objectdef indexed indexedelem
%type <call> methodcall normcall callsuffix
%type <uintValue> ifprefix elseprefix whilecond whilestart N_rule M_rule
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

program:      statements
              ;

statements:   stmts { $$ = $1; }
              |     { $$ = new_stmt(); }
              ;

stmts:        stmt { _resettemp(); $$ = $1; }
              |stmts stmt { $$ = manage_statements($1, $2); }
              ;

stmt:         expr SEMICOLON      {$$ = new_stmt();}
              |ifstmt             {$$ = new_stmt();}
              |whilestmt          {$$ = $1;}
              |forstmt            {$$ = $1;}
              |returnstmt         {$$ = new_stmt();}
              |BREAK SEMICOLON    {$$ = manage_break();}
              |CONTINUE SEMICOLON {$$ = manage_continue();}
              |block              {$$ = $1;}
              |funcdef            {$$ = new_stmt();} 
              |SEMICOLON          {$$ = new_stmt();}
              ;

expr:         assignment               {$$ = $1;}
              |expr ADD expr           {$$ = manage_arithmetic_operation(_add, $1, $3);}
              |expr SUB expr           {$$ = manage_arithmetic_operation(_sub, $1, $3);}           
              |expr MUL expr           {$$ = manage_arithmetic_operation(_mul, $1, $3);}           
              |expr DIV expr           {$$ = manage_arithmetic_operation(_div, $1, $3);}           
              |expr MODULO expr        {$$ = manage_arithmetic_operation(_mod, $1, $3);}        
              |expr GREATER expr       {$$ = manage_relative_operation(_if_greater, $1, $3);}       
              |expr GREATER_EQUAL expr {$$ = manage_relative_operation(_if_greatereq, $1, $3);}
              |expr LESSER expr        {$$ = manage_relative_operation(_if_less, $1, $3);}        
              |expr LESSER_EQUAL expr  {$$ = manage_relative_operation(_if_lesseq, $1, $3);}  
              |expr EQUAL expr         {$$ = manage_relative_operation(_if_eq, $1, $3);}         
              |expr NOT_EQUAL expr     {$$ = manage_relative_operation(_if_noteq, $1, $3);}     
              |expr AND expr           {$$ = manage_bool_operation(_and, $1, $3);}           
              |expr OR expr            {$$ = manage_bool_operation(_or, $1, $3);}           
              |term                    {$$ = $1;}
              ;

term:         LPAREN expr RPAREN     {$$ = $2;}
              |SUB expr              {$$ = manage_uminus_expr($2);} %prec UMINUS
              |NOT expr              {$$ = manage_not_expr($2);}
              |PLUS_PLUS lvalue      {$$ = manage_plusplus_lvalue($2);}
              |lvalue PLUS_PLUS      {$$ = manage_lvalue_plusplus($1);}
              |MINUS_MINUS lvalue    {$$ = manage_minusminus_lvalue($2);}
              |lvalue MINUS_MINUS    {$$ = manage_lvalue_minusminus($1);} 
              |primary               {$$ = $1;}
              ;

assignment:   lvalue ASSIGN expr { $$ = manage_assignment($1, $3);}
              ;

primary:      lvalue                  {$$ = emit_if_table_item($1);}
              |call                   {$$ = $1;}
              |objectdef              {$$ = $1;}
              |LPAREN funcdef RPAREN  {$$ = manage_primary_funcdef($2);}
              |const                  {$$ = $1;}
              ;

lvalue:       ID          {$$ = manage_lvalue_id($1);}
              |LOCAL ID   {$$ = manage_lvalue_local_id($2);}
              |DCOLON ID  {$$ = manage_lvalue_global_id($2);}
              |member     {$$ = $1;}
              ;

member:       lvalue PERIOD ID             {$$ = member_item($1, $3);}
              |lvalue LSQUARE expr RSQUARE {$$ = manage_member_item_lvalue_lsquare_expr_rsquare($1, $3);}
              |call PERIOD ID              {$$ = member_item($1, $3);}
              |call LSQUARE expr RSQUARE   {$$ = manage_member_item_lvalue_lsquare_expr_rsquare($1, $3);}
              ;

call:         call LPAREN elist RPAREN                   {$$ = make_call($1, $3);}
              |lvalue callsuffix                         {$$ = manage_call_lvalue_callsuffix($1, $2);}
              |LPAREN funcdef RPAREN LPAREN elist RPAREN {$$ = manage_call_funcdef($2 ,$5);}
              ;
              
callsuffix:   normcall    {$$ = $1;}
              |methodcall {$$ = $1;}
              ;
            
normcall:     LPAREN elist RPAREN {$$ = manage_normcall($2);}
              ;
 
methodcall:   DPERIOD ID LPAREN elist RPAREN {$$ = manage_methodcall($4, $2);;}
              ;

elist:        expr              {$$ = $1; $$->next = NULL;}
              |expr COMMA elist {$$ = manage_elist($1,$3);}
              |                 {$$ = (expr*) 0;}
              ;

objectdef:    LSQUARE elist RSQUARE    {$$ = manage_objectdef_elist($2);}
              |LSQUARE indexed RSQUARE {$$ = manage_objectdef_indexed($2);}
              ;

indexed:      indexedelem                 {$$ = $1;}
              |indexedelem COMMA indexed  {$$ = manage_indexed($1, $3);}
              ;

indexedelem:  LCURLY expr COLON expr RCURLY {$$ = manage_indexedelem($2, $4);}
              ;

block:        LCURLY {if(!block_b) increase_scope();} statements RCURLY {$$ = $3;if(!block_b){symTab_hide();decrease_scope();}} 
              ;

funcname:     ID {$$ = manage_funcname_named($1); assert($$);}
              |  {$$ = manage_funcname_anonymous(); assert($$);}
              ;

funcprefix:   FUNCTION funcname { assert($2); $$ = manage_funcprefix($2); assert($$);}
              ;

funcargs:     LPAREN idlist RPAREN {manage_funcargs();}
              ;

funcbody:     block {$$ = manage_funcbody();}
              ;

funcdef:      funcprefix funcargs funcbody {$$ = manage_funcdef($1,$3);}
              ;

const:        INTEGER   {$$ = new_expr_const_num($1);}
              |REAL     {$$ = new_expr_const_num($1);}
              |STRING   {$$ = new_expr_const_string($1);}
              |NIL      {$$ = new_expr(nil_e);}
              |TRUE     {$$ = new_expr_const_bool(1);}
              |FALSE    {$$ = new_expr_const_bool(0);} 
              ;

idlist:       ID                {manage_idlist_id($1);}
              |idlist COMMA ID  {manage_idlist_comma_id($3);}
              |                 {}
              ;

ifprefix:     IF LPAREN expr RPAREN {$$ = manage_ifprefix($3);}
	      ;

elseprefix:   ELSE{$$ = manage_else();}
	      ;

ifstmt:       ifprefix stmt elseprefix stmt {manage_if_else($1,$3);}
              | ifprefix stmt {patch_label($1, next_quad_label());}
              ;

loopstart:    {++loopCounter; contList.push_back(std::vector<int>()); breakList.push_back(std::vector<int>()); block_b = true;}
              ;

loopend:      {--loopCounter; block_b = false;}
              ;

loopstmt:     loopstart stmt loopend {$$ = $2;}
              ;

whilestart:   WHILE { $$ = next_quad_label();}
              ;

whilecond:    LPAREN expr RPAREN { $$ = manage_whilecond($2); }
              ;

whilestmt:    whilestart whilecond loopstmt { $$ = manage_whilestmt($1, $2 , $3);}
	      ;

N_rule:       {$$ = manage_N_rule();}
              ;

M_rule:       {$$ = next_quad_label();}
              ;

forprefix:    FOR LPAREN elist SEMICOLON M_rule expr SEMICOLON {$$ = manage_forprefix($5, $6);}
              ;

forstmt:      forprefix N_rule elist RPAREN N_rule loopstmt N_rule {$$ = manage_forstmt($1, $2, $5, $6, $7);}
              ;

returnstmt:   RETURN expr SEMICOLON { manage_return_expr($2); }
              |RETURN SEMICOLON     { manage_return(); }
              ;

%%

int main(int argc, char** argv) {

  if((argc == 3 || argc == 5) && strcmp(argv[1], "-g") != 0) {
    printf("Invalid arguments!\n");
    return 1;
  }
  if(argc == 4 && strcmp(argv[2], "-o") != 0) {
    printf("Invalid arguments!\n");
    return 1;
  }
  if(argc == 5 && strcmp(argv[3], "-o") != 0) {
    printf("Invalid arguments!\n");
    return 1;
  }

	if(argc == 2 && !(alpha_yyin = fopen(argv[1], "r"))){
    printf("Could not open input file: %s!\n", argv[1]);
    return 1;
  }
  else if((argc == 3 || argc == 5) && !(alpha_yyin = fopen(argv[2], "r"))){
    printf("Could not open input file: %s!\n", argv[2]);
    return 1;
  }
  else if(argc == 4 && !(alpha_yyin = fopen(argv[1],"r"))) {
    printf("Could not open input file: %s!\n", argv[1]);
    return 1;
  }
  else if(argc > 5){
    printf("Too many arguments!\n");
    return 1;
  }
  else if(argc < 2){
    printf("Too few arguments!\n");
    return 1;
  }

	init_library_func();
  yyparse();
  if(error) {
    return 1;
  }

  tcode_generate();

  if(argc == 4 && strcmp(argv[2],"-o") == 0) {
    char* suffix = (char*)".abc";
    int len = strlen(argv[3]) + strlen(suffix) + 1;
    char result[len];
    strcpy(result, argv[3]);
    strcat(result, suffix);
    tcode_generate_binary(result);
  }
  else if(argc == 5 && strcmp(argv[3],"-o") == 0) {
    char* suffix = (char*)".abc";
    int len = strlen(argv[4]) + strlen(suffix) + 1;
    char result[len];
    strcpy(result, argv[4]);
    strcat(result, suffix);
    tcode_generate_binary(result);
  }
  else if(argc == 2 || argc == 3) {
    tcode_generate_binary((char*)"a.abc");
  }
  else {
    printf("Invalid arguments!\n");
    return 1;
  }

  if(argc > 2 && strcmp(argv[1], "-g") == 0) {
    print_quads();
    tcode_print_instructions();
  }

  // tcode_generate_binary((char*)"binary.abc");
}
