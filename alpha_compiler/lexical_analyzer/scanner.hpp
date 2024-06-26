#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(WIN32)
#define YY_NO_UNISTD_H
static int isatty (int i) { return 0; }
#elif defined(_WIN32_WCE)
#define YY_NO_UNISTD_H
static int isatty (void *i) { return 0; }
#endif

#define YY_DECL int alpha_yylex (void)
int alpha_yylex(void);


typedef struct alpha_token_t {
  unsigned int          numline;
  unsigned int          numToken;
  char*                 content;
  char*                 type;
  char*                 category;
  struct alpha_token_t *next;
} alpha_token_t;

alpha_token_t* alpha_token_t_create(unsigned int _numline, unsigned int _numToken, char* _content, const char* _type, const char* _category);
void add_token_to_list(alpha_token_t* token, alpha_token_t** head);
void check_escape_characters(char* source);
void remove_quotes(char* str);
void set_alpha_yyin(FILE* inputFile);