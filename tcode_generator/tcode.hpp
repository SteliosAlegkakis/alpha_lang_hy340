struct incomplete_jump{
    unsigned         instrNo;
    unsigned         iaddress;
};

void tcode_generate(void);
void print_instructions(void);
void tcode_generate_binary(char* filename);

