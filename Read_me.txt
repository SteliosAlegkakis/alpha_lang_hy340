Compile:    1) Inside the folder "lexical_analyzer" do: make all
            2) Inside the folder "syntax_analyzer" do: make all
            3) Inside the folder "alpha_compiler_hy340" do: make all

Run:        ./a.out input_file_path

Print for every input file:     The elements of symbol table in the terminal and
                                the syntax rules inside an output file "rules.txt"

We didn't make the doing of hide/show of active elements that exist in the symbol table
and they belong to previous scopes every time we see a function in the input file.