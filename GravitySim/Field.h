/*
Lucas Tung
Gravity Simulator
Field.h
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct FieldObj* Field;

Field newField(void); // create new empty field, allocate memory?
void freeField(Field* pF); // clear field of all particles, free memory

void updateVelCursor(Field F); // updates velocity of particle at cursor

void updateVelAll(Field F); // calls updateVelCursor on all particles in a field

void updatePosAll(Field F); // change position of all particles
							

void moveFront(Field F); // moves cursor to front
void moveNext(Field F); // moves cursor to next item

void merge(Field F); // "merges" any particles occupying the same space, increasing mass of one while removing the other
void add(Field F, double x, double y); // adds particle to front of field list, with position x, y

void clear(Field F); // removes all particles from field, frees particles

void printList(Field F); // prints all particles in field in list form
void printField(Field F); // prints field form