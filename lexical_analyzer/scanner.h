#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct alpha_token_t {
  unsigned int     numline;
  unsigned int     numToken;
  char          *content;
  char          *type;
  struct alpha_token_t *next;
} alpha_token_t;

unsigned int tokensCount = 0;

alpha_token_t* alpha_token_t_create(unsigned int _numline, unsigned int _numToken, char *_content, char *_type);
void add_token_to_list(alpha_token_t* token, alpha_token_t** head);
char* deep_copy_string(const char* source);
void check_escape_characters(char* source);