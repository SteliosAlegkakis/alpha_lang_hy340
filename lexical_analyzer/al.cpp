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

    if(argc == 2) {
        while(alphaTokenList != NULL) {
            printf("%d:  #%d \"%s\" %s <-%s\n",alphaTokenList->numline,alphaTokenList->numToken,alphaTokenList->content,alphaTokenList->type,alphaTokenList->category);
            alphaTokenList = alphaTokenList->next;
        }
    } else if(argc == 3) {
        FILE* output = fopen(argv[2], "w");
        while(alphaTokenList != NULL) {
            fprintf(output, "%d: #%d \"%s\" %s <-%s\n",alphaTokenList->numline,alphaTokenList->numToken,alphaTokenList->content,alphaTokenList->type,alphaTokenList->category);
            alphaTokenList = alphaTokenList->next;
        }
        fclose(output);
    }
    fclose(input);

    return 0;
}