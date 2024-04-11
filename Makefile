all:
	g++ -std=c++11 ./icode_generator/icode.cpp ./syntax_analyzer/parser.cpp ./symbol_table/symbol_table.cpp ./syntax_analyzer/parser_lib/parser_lib.cpp ./lexical_analyzer/scanner.cpp

clean:
	del -f a.exe