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
	$(MAKE) -C ./lexical_analyzer
	$(MAKE) -C ./syntax_analyzer
	g++ -std=c++11 ./icode_generator/icode.cpp ./syntax_analyzer/parser.cpp ./symbol_table/symbol_table.cpp ./syntax_analyzer/parser_lib/parser_lib.cpp ./lexical_analyzer/scanner.cpp ./tcode_generator/tcode.cpp -o alphac$(EXE_EXTENSION)

.PHONY: alphavm
alphavm: ./avm/loader.cpp
	g++ -std=c++11 ./avm/loader.cpp ./avm/avm.cpp ./avm/dispatcher.cpp ./avm/lib_funcs.cpp ./avm/executors/assign.cpp ./avm/executors/arithmetic.cpp ./avm/executors/function.cpp ./avm/executors/table.cpp ./avm/executors/jump.cpp  -o alphavm$(EXE_EXTENSION)

all: alphac alphavm

clean:
	$(RM) alphac$(EXE_EXTENSION) alphavm$(EXE_EXTENSION) *.txt *.abc
	$(MAKE) -C ./lexical_analyzer clean
	$(MAKE) -C ./syntax_analyzer clean

test:
	for testFile in ./testfiles/$(folder)/*.asc; do \
		echo ""; \
		echo "Running testfile: $$testFile"; \
		$(PROGRAM_NAME) $$testFile; \
		echo ""; \
	done



