ifeq ($(OS),Windows_NT)
    RM = del -f
	EXE_EXTENSION = .exe
else
    RM = rm -f
	EXE_EXTENSION =
endif

PROGRAM_NAME = ./alphac$(EXE_EXTENSION)

.PHONY: alphac
alphac:
	$(MAKE) -C ./alpha_compiler/lexical_analyzer
	$(MAKE) -C ./alpha_compiler/syntax_analyzer
	g++ -std=c++11 ./alpha_compiler/icode_generator/icode.cpp ./alpha_compiler/syntax_analyzer/parser.cpp ./alpha_compiler/symbol_table/symbol_table.cpp ./alpha_compiler/syntax_analyzer/parser_lib/parser_lib.cpp ./alpha_compiler/lexical_analyzer/scanner.cpp ./alpha_compiler/tcode_generator/tcode.cpp -o alphac$(EXE_EXTENSION)

.PHONY: alphavm
alphavm:
	g++ -std=c++11 ./alpha_vm/loader.cpp ./alpha_vm/avm.cpp ./alpha_vm/dispatcher.cpp ./alpha_vm/lib_funcs.cpp ./alpha_vm/executors/assign.cpp ./alpha_vm/executors/arithmetic.cpp ./alpha_vm/executors/function.cpp ./alpha_vm/executors/table.cpp ./alpha_vm/executors/jump.cpp  -o alphavm$(EXE_EXTENSION)

all: alphac alphavm

clean:
	$(RM) alphac$(EXE_EXTENSION) alphavm$(EXE_EXTENSION) *.txt *.abc
	$(MAKE) -C ./alpha_compiler/lexical_analyzer clean
	$(MAKE) -C ./alpha_compiler/syntax_analyzer clean

test:
	for testFile in ./testfiles/$(folder)/*.asc; do \
		echo ""; \
		echo "Running testfile: $$testFile"; \
		$(PROGRAM_NAME) $$testFile; \
		echo ""; \
	done



