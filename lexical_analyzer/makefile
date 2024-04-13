ifeq ($(OS),Windows_NT)
    RM = del -f
else
    RM = rm -f
endif

all:
	flex scanner.l

clean:
	$(RM) scanner.cpp