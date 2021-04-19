# Lucas Tung
# lwtung
# pa1
#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
#       make                   makes Gravity
#------------------------------------------------------------------------------

Gravity : Gravity.o Field.o
	gcc -o Gravity Gravity.o Field.o

Gravity.o : Gravity.c Field.h
	gcc -c -std=c99 -Wall Gravity.c

Field.o : Field.c Field.h
	gcc -c -std=c99 -Wall Field.c

clean :
	rm -f Gravity Gravity.o Field.o
 