#include "./scanner.h"

int main(int argc, char** argv) {
    FILE* input = fopen(argv[1], "r");
    if(input == NULL){
        printf("Error. Could not open input file");
        exit(EXIT_FAILURE);
    }
    set_alpha_yyin(input);

    alpha_token_t *alphaTokenList = NULL;
    alpha_yylex(&alphaTokenList);

    while(alphaTokenList != NULL){
        printf("%d %d %s %s <-%s\n",alphaTokenList->numline,alphaTokenList->numToken,alphaTokenList->content,alphaTokenList->type,alphaTokenList->category);
        alphaTokenList = alphaTokenList->next;
    }
    fclose(input);
    return 0;
}