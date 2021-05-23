PROGRAM=tic-tac-toe
CFLAGS=-g
LDFLAGS=-lcurses

all: ${PROGRAM}

${PROGRAM}:
	@ gcc src/* ${CFLAGS} ${LDFLAGS} -o ${PROGRAM}.app

clean:
	@ rm -rf ${PROGRAM}
.phony: all clean