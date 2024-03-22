all:
	g++ -std=c++11 ./syntax_analyzer/parser.cpp ./lexical_analyzer/scanner.cpp

clean:
	del -f a.exe