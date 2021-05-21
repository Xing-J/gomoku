.POSIX:

NAME=gomoku

PREFIX=/usr/local
MANPREFIX=${PREFIX}/share/man

BIN=${NAME}
MAN1=${NAME:=.1}

OBJS=${NAME:=.o}

LIBS=-lncurses

all: ${BIN}

${BIN}: ${OBJS}
	${CC} ${LDFLAGS} ${LIBS} ${OBJS} -o ${BIN}

install: all
	mkdir -p ${PREFIX}/bin
	cp -f ${BIN} ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/${BIN}
	mkdir -p ${MANPREFIX}/man1
	cp -f ${MAN1} ${MANPREFIX}/man1
	chmod 644 ${MANPREFIX}/man1/${MAN1}

uninstall:
	rm -f ${PREFIX}/bin/${BIN} ${MANPREFIX}/man1/${MAN1}

clean:
	rm -f ${BIN} ${OBJS}

.PHONY: all install uninstall clean
