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
  struct SymtabEntry* exprNode;
  struct expr* expr;
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
%type <exprNode> term assignment primary
%type <exprNode> member call callsuffix normcall methodcall 
%type <exprNode> elist objectdef indexed indexedelem block  
%type <exprNode> const idlist ifstmt whilestmt forstmt returnstmt

%type <expr> lvalue

%type <stringValue> funcname
%type <uintValue> funcbody
%type <exprNode> funcprefix
%type <exprNode> funcdef


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

stmt:         expr SEMICOLON      {fprintf(rulesFile, "stmt -> expr SEMICOLON\n");}
              |ifstmt             {fprintf(rulesFile, "stmt -> ifstmt\n");}
              |whilestmt          {fprintf(rulesFile, "stmt -> whilestmt\n");}
              |forstmt            {fprintf(rulesFile, "stmt -> forstmt\n");}
              |returnstmt         {fprintf(rulesFile, "stmt -> returnstmt\n");}
              |BREAK SEMICOLON    {if(!loopCounter) print_error("error, cannot use break outside of loop:"); fprintf(rulesFile, "stmt -> BREAK SEMICOLON\n");}
              |CONTINUE SEMICOLON {if(!loopCounter) print_error("error, cannot use continue outside of loop:"); fprintf(rulesFile, "stmt -> CONTINUE SEMICOLON\n");}
              |block              {fprintf(rulesFile, "stmt -> block\n");}
              |funcdef            {fprintf(rulesFile, "stmt -> funcdef\n");} 
              |SEMICOLON          {fprintf(rulesFile, "stmt -> SEMICOLON\n");}
              ;

expr:         assignment               {fprintf(rulesFile, "expr -> assignment\n");}
              |expr ADD expr           {fprintf(rulesFile, "expr -> expr ADD expr\n");}
              |expr SUB expr           {fprintf(rulesFile, "expr -> expr SUB expr\n");}           
              |expr MUL expr           {fprintf(rulesFile, "expr -> expr MUL expr\n");}           
              |expr DIV expr           {fprintf(rulesFile, "expr -> expr DIV expr\n");}           
              |expr MODULO expr        {fprintf(rulesFile, "expr -> expr MODULO expr\n");}        
              |expr GREATER expr       {fprintf(rulesFile, "expr -> expr GREATER expr\n");}       
              |expr GREATER_EQUAL expr {fprintf(rulesFile, "expr -> expr GREATER_EQUAL expr\n");}
              |expr LESSER expr        {fprintf(rulesFile, "expr -> expr LESSER expr\n");}        
              |expr LESSER_EQUAL expr  {fprintf(rulesFile, "expr -> expr LESSER_EQUAL expr\n");}  
              |expr EQUAL expr         {fprintf(rulesFile, "expr -> expr EQUAL expr\n");}         
              |expr NOT_EQUAL expr     {fprintf(rulesFile, "expr -> expr NOT_EQUAL expr\n");}     
              |expr AND expr           {fprintf(rulesFile, "expr -> expr AND expr\n");}           
              |expr OR expr            {fprintf(rulesFile, "expr -> expr OR expr\n");}           
              |term                    {fprintf(rulesFile, "expr -> term\n");}
              ;

term:         LPAREN expr RPAREN     {fprintf(rulesFile,"term -> LPAREN expr RPAREN\n");}
              |SUB expr %prec UMINUS {fprintf(rulesFile,"term -> SUB expr\n");}
              |NOT expr              {fprintf(rulesFile,"term -> NOT expr\n");}
              |PLUS_PLUS lvalue      {if($2->sym->uniontype == function) print_error("error, function id used as lvalue"); fprintf(rulesFile,"term -> PLUS_PLUS lvalue\n");}
              |lvalue PLUS_PLUS      {if($1->sym->uniontype == function) print_error("error, function id used as lvalue"); fprintf(rulesFile,"term -> lvalue PLUS_PLUS\n");}
              |MINUS_MINUS lvalue    {if($2->sym->uniontype == function) print_error("error, function id used as lvalue");fprintf(rulesFile,"term -> MINUS_MINUS lvalue\n");}
              |lvalue MINUS_MINUS    {if($1->sym->uniontype == function) print_error("error, function id used as lvalue"); fprintf(rulesFile,"term -> lvalue MINUS_MINUS\n");} 
              |primary               {fprintf(rulesFile, "term -> primary\n");}
              ;

assignment:   lvalue {assert($1); if($1->sym->uniontype == function) print_error("error, function id used as lvalue");} ASSIGN expr {fprintf(rulesFile,"assignment -> lvalue ASSIGN expr\n");}
              ;

primary:      lvalue                  {fprintf(rulesFile, "primary -> lvalue\n");}
              |call                   {fprintf(rulesFile, "primary -> call\n");}
              |objectdef              {fprintf(rulesFile, "primary -> objectdef\n");}
              |LPAREN funcdef RPAREN  {fprintf(rulesFile, "primary -> LPAREN funcdef RPAREN\n");}
              |const                  {fprintf(rulesFile, "primary -> const\n");}
              ;

lvalue:       ID          {$$ = manage_lvalue_id($1); fprintf(rulesFile, "lvalue -> ID\n");}
              |LOCAL ID   {$$ = manage_lvalue_local_id($2); fprintf(rulesFile,"lvalue -> LOCAL ID\n");}
              |DCOLON ID  {$$ = manage_lvalue_global_id($2); fprintf(rulesFile,"lvalue -> DCOLON ID\n");}
              |member     {fprintf(rulesFile,"lvalue -> member\n");}
              ;

member:       lvalue PERIOD ID             {fprintf(rulesFile, "member -> lvalue PERIOD ID\n");}
              |lvalue LSQUARE expr RSQUARE {fprintf(rulesFile, "member -> lvalue LSQUARE expr RSQUARE\n");}
              |call PERIOD ID              {fprintf(rulesFile, "member -> call PERIOD ID\n");}
              |call LSQUARE expr RSQUARE   {fprintf(rulesFile, "member -> call LSQUARE expr RSQUARE\n");}
              ;

call:         call LPAREN elist RPAREN                   {fprintf(rulesFile, "call -> call LPAREN elist RPAREN\n");}
              |lvalue callsuffix                         {if(!($1->sym == NULL)) $1->sym->uniontype = variable; fprintf(rulesFile, "call -> lvalue callsuffix\n");}
              |LPAREN funcdef RPAREN LPAREN elist RPAREN {fprintf(rulesFile, "call -> LPAREN funcdef RPAREN LPAREN elist RPAREN\n");}
              ;
              
callsuffix:   normcall    {fprintf(rulesFile, "callsuffix -> normcall\n");}
              |methodcall {fprintf(rulesFile, "callsuffix -> methodcall\n");}
              ;
            
normcall:     LPAREN elist RPAREN {fprintf(rulesFile, "normcall -> LPAREN elist RPAREN\n");}
              ;
 
methodcall:   DPERIOD ID LPAREN elist RPAREN {fprintf(rulesFile, "methodcall -> DPERIOD ID LPAREN elist RPAREN\n");}
              ;

elist:        expr              {fprintf(rulesFile, "elist -> expr\n");}
              |elist COMMA expr {fprintf(rulesFile, "elist -> elist COMMA expr\n");}
              |                 {fprintf(rulesFile, "elist -> \n");}
              ;

objectdef:    LSQUARE elist RSQUARE    {fprintf(rulesFile, "objectdef -> LSQUARE elist RSQUARE\n");}
              |LSQUARE indexed RSQUARE {fprintf(rulesFile, "objectdef -> LSQUARE indexed RSQUARE\n");}
              ;

indexed:      indexedelem                 {fprintf(rulesFile, "indexed -> indexedelem\n");}
              |indexed COMMA indexedelem  {fprintf(rulesFile, "indexed -> indexed COMMA indexedelem\n");}
              ;

indexedelem:  LCURLY expr COLON expr RCURLY {fprintf(rulesFile, "indexedelem -> LCURLY expr COLON expr RCURLY\n");}
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

const:        INTEGER   {fprintf(rulesFile, "const -> INTEGER\n");}
              |REAL     {fprintf(rulesFile, "const -> REAL\n");}
              |STRING   {fprintf(rulesFile, "const -> STRING\n");}
              |NIL      {fprintf(rulesFile, "const -> NIL\n");}
              |TRUE     {fprintf(rulesFile, "const -> TRUE\n");}
              |FALSE    {fprintf(rulesFile, "const -> FALSE\n");} 
              ;

idlist:       ID                {manage_idlist_id($1); fprintf(rulesFile,"idlist -> ID\n");}
              |idlist COMMA ID  {manage_idlist_comma_id($3); fprintf(rulesFile,"idlist -> idlist COMMA ID\n");}
              |                 {fprintf(rulesFile,"idlist -> \n");}
              ;

ifstmt:       IF LPAREN expr RPAREN stmt ELSE stmt {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt ELSE stmt\n");}
              |IF LPAREN expr RPAREN stmt {fprintf(rulesFile, "ifstmt -> IF LPAREN expr RPAREN stmt\n");}
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

returnstmt:   RETURN expr SEMICOLON {if(!functionCounter) print_error("error, cannot use return outside of function"); fprintf(rulesFile, "returnstmt -> RETURN expr SEMICOLON\n");}
              |RETURN SEMICOLON     {if(!functionCounter) print_error("error, cannot use return outside of function"); fprintf(rulesFile, "returnstmt -> RETURN SEMICOLON\n");}
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
  return 0;
}
