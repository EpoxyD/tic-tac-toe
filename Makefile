PROGRAM=tic-tac-toe
CFLAGS=-g -Wall -Werror
LFLAGS=-Iinc
LDFLAGS=-lcurses

all: ${PROGRAM}

${PROGRAM}:
	gcc src/* ${CFLAGS} ${LFLAGS} ${LDFLAGS} -o ${PROGRAM}.app

clean:
	rm -rf ${PROGRAM}.app

format:
	clang-format src/main.c > /tmp/main_format.c
	mv /tmp/main_format.c src/main.c

.phony: all clean
