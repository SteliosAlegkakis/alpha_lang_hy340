ifeq ($(OS),Windows_NT)
    RM = del -f
	EXE_EXTENSION = .exe
else
    RM = rm -f
	EXE_EXTENSION =	.out
endif

PROGRAM_NAME = ./a$(EXE_EXTENSION)

all:
	$(MAKE) -C ./lexical_analyzer
	$(MAKE) -C ./syntax_analyzer
	g++ -std=c++11 ./icode_generator/icode.cpp ./syntax_analyzer/parser.cpp ./symbol_table/symbol_table.cpp ./syntax_analyzer/parser_lib/parser_lib.cpp ./lexical_analyzer/scanner.cpp

clean:
	$(RM) a$(EXE_EXTENSION) rules.txt 
	$(MAKE) -C ./lexical_analyzer clean
	$(MAKE) -C ./syntax_analyzer clean

test:
	for testFile in ./testfiles/$(folder)/*.asc; do \
		echo ""; \
		echo "Running testfile: $$testFile"; \
		$(PROGRAM_NAME) $$testFile; \
		echo ""; \
	done



