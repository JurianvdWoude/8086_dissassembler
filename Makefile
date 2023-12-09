CC=g++
INCDIRS=-I.
OPT=-O0
CFLAGS=-Wall -Wextra -g $(INCDIRS) $(OPT)

CFILES=main.cpp 
OBJECTS=main.o

BINARY=bin 


all: $(BINARY)

# @ is whatever is on the left side of :
# ^ is whatever is on the right side of :
$(BINARY): $(OBJECTS)
				$(CC) -o $@ $^

# regular expression where % is a wildcard
# to generate %.o, it will depend on %.c
%.o:%.c 
				$(CC) $(CFLAGS) -c -o $@ $^

clean: 
				rm -rf $(BINARY) $(OBJECTS)
