all:
	g++ -std=c++11 ./syntax_analyzer/parser.cpp ./syntax_analyzer/symbol_table/symbol_table.cpp ./syntax_analyzer/parser_lib/parser_lib.cpp ./lexical_analyzer/scanner.cpp

clean:
	del -f a.exe