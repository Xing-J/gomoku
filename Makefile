.POSIX:

NAME=gomoku

PREFIX=/usr/local
MANPREFIX=${PREFIX}/share/man

BIN=${NAME}
MAN6=${NAME:=.6}

OBJS=${NAME:=.o}

LIBS=-lncurses

all: ${BIN}

${BIN}: ${OBJS}
	${CC} ${LDFLAGS} ${LIBS} ${OBJS} -o ${BIN}

install: all
	mkdir -p ${PREFIX}/bin
	cp -f ${BIN} ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/${BIN}
	mkdir -p ${MANPREFIX}/man6
	cp -f ${MAN6} ${MANPREFIX}/man6
	chmod 644 ${MANPREFIX}/man6/${MAN6}

uninstall:
	rm -f ${PREFIX}/bin/${BIN} ${MANPREFIX}/man6/${MAN6}

clean:
	rm -f ${BIN} ${OBJS}

.PHONY: all install uninstall clean
