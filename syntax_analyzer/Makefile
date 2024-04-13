ifeq ($(OS),Windows_NT)
    RM = del -f
else
    RM = rm -f
endif

all:
	bison --yacc --defines -v --output=parser.cpp parser.y

clean:
	$(RM) parser.cpp parser.hpp parser.output