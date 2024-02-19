%{
#if defined(WIN32)
#define YY_NO_UNISTD_H
static int isatty (int i) { return 0; }
#elif defined(_WIN32_WCE)
#define YY_NO_UNISTD_H
static int isatty (void *i) { return 0; }
#endif

#include <stdio.h>
#define YY_DECL int yylex (void* yylval)
%}

%option noyywrap
%option yylineno
%option prefix = "alpha_yy"

%% 

[0-9]+          {printf("INTEGER\n");printf("%d",yylineno);printf("%s",yytext);}
[a-zA-Z]+       {printf("IDENTIFIER\n");yylval->numline = yylineno;...;insert(LinkedList);}
"="             printf("ASSIGN\n");
"+"             printf("ADD\n");
"-"             printf("SUB\n");
"*"             printf("MUL\n");
"/"             printf("DIV\n");
"("             printf("LPAREN\n");
")"             printf("RPAREN\n");
"\n"            /* Do nothing for newline */

[ \t]+          /* Do nothing for whitespace */

.               printf("ERROR\n");

%%

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

Node* createNode(void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

void initList(LinkedList* list) {
    list->head = NULL;
}

void insert(LinkedList* list, void* data) {
    Node* newNode = createNode(data);
    if(list->head == NULL) {
        list->head = newNode;
    }
    else{
        Node* current = list->head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

void traverse(LinkedList* list, void (*action)(void*)) {
    Node* current = list->head;
    while (current) {
        action(current->data);
        current = current->next;
    }
}

typedef struct alpha_token_t {
  unsigned int     numline;
  unsigned int     numToken;
  char          *content;
  char          *type;
  struct alpha_token_t *alpha_yylex;
} alpha_token_t;

alpha_token_t *alpha_token_list;
  
int main(int argc, char** argv) {
    yyin = fopen(argv[1], "r");
    if(alpha_yyin == NULL){
        printf("Error. Could not open input file");
    }
    alpha_token_t *yylval = malloc(sizeof(alpha_token_t));
    alpha_yylex(yylval);
    fclose(yyin);
    return 0;
}