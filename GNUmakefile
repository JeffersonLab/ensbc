# $Id: GNUmakefile,v 1.11 2001/06/02 02:10:47 edwards Exp $ ($Date: 2001/06/02 02:10:47 $)

LEX = flex
##LFLAGS = -Ib
LFLAGS = -I
BISON = bison
##BISONFLAGS = -tv
BISONFLAGS = 

CC = gcc
CFLAGS = -O -Wall -std=c99
##CC = xlc
##CFLAGS = -O
#LIBS = -L/usr/local/lib -lfl -lm
LIBS = -L/usr/local/lib -L/usr/local/Cellar/flex/2.6.4_1/lib -lfl -lm


# CC = cc -g 
# LIBS = -L$(HOME)/lib/$(HOSTTYPE) -lfl

all: ensbc calc calcbc

ensbc-parse.c ensbc-parse.h: ensbc-parse.y ensbc.h
	$(BISON) $(BISONFLAGS) -d ensbc-parse.y -o ensbc-parse.c

ensbc-lex.c: ensbc-lex.l ensbc.h ensbc-parse.h
	$(LEX) $(LFLAGS) ensbc-lex.l 
	mv -f lex.yy.c $@

ensbc.o: ensbc.c ensbc-parse.h ensbc.h
	$(CC) -c $(CFLAGS) $< -o $@

ensem.o: ensem.c ensbc.h
	$(CC) -c $(CFLAGS) $< -o $@

ensbc: ensbc-parse.o ensbc-lex.o ensem.o ensbc.o
	$(CC) $^ -o ensbc $(LIBS)

calc.o: calc.c ensbc.h
	$(CC) -c $(CFLAGS) $< -o $@

calc: calc.o ensem.o
	$(CC) $^ -o calc $(LIBS)

calcbc.o: calcbc.c ensbc-parse.h ensbc.h
	$(CC) -c $(CFLAGS) $< -o $@

calcbc: ensbc-parse.o ensbc-lex.o ensem.o calcbc.o
	$(CC) $^ -o calcbc $(LIBS)

solve.o: solve.c ensbc.h
	$(CC) -c $(CFLAGS) $< -o $@

solve: solve.o ensem.o
	$(CC) $^ -o solve $(LIBS)


clean:
	rm -f ensbc calcbc calc calcbc.o calc.o
	rm -f ensbc-parse.output lex.backup
	rm -f ensbc-parse.o ensem.o ensbc-lex.o obstack.o ensbc.o
	rm -f ensbc-parse.c ensbc-parse.h ensbc-lex.c

