# Compiler
CC = gcc

# Flex
FLEX = flex

# Executable name
EXEC = scanner.exe

# Source files
SRC = scanner.l
OBJ = lex.alpha_yy.c

# Rule to generate lex.yy.c from scanner.l
$(OBJ): $(SRC)
	$(FLEX) $(SRC)

# Rule to compile the program
$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

all: $(EXEC)

# Clean
clean:
	del -f $(EXEC) $(OBJ)
