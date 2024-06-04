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
	$(MAKE) -C ./alphac/lexical_analyzer
	$(MAKE) -C ./alphac/syntax_analyzer
	g++ -std=c++11 ./alphac/icode_generator/icode.cpp ./alphac/syntax_analyzer/parser.cpp ./alphac/symbol_table/symbol_table.cpp ./alphac/syntax_analyzer/parser_lib/parser_lib.cpp ./alphac/lexical_analyzer/scanner.cpp ./alphac/tcode_generator/tcode.cpp -o alphac$(EXE_EXTENSION)

.PHONY: alphavm
alphavm:
	g++ -std=c++11 ./alphavm/loader.cpp ./alphavm/avm.cpp ./alphavm/dispatcher.cpp ./alphavm/lib_funcs.cpp ./alphavm/executors/assign.cpp ./alphavm/executors/arithmetic.cpp ./alphavm/executors/function.cpp ./alphavm/executors/table.cpp ./alphavm/executors/jump.cpp  -o alphavm$(EXE_EXTENSION)

all: alphac alphavm

clean:
	$(RM) alphac$(EXE_EXTENSION) alphavm$(EXE_EXTENSION) *.txt *.abc
	$(MAKE) -C ./alphac/lexical_analyzer clean
	$(MAKE) -C ./alphac/syntax_analyzer clean

test:
	for testFile in ./testfiles/$(folder)/*.asc; do \
		echo ""; \
		echo "Running testfile: $$testFile"; \
		$(PROGRAM_NAME) $$testFile; \
		echo ""; \
	done



