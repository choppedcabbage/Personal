/*
Lucas Tung
Gravity thing
Field.h
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct FieldObj* Field;

Field newField(void); // create new empty field, allocate memory?
void freeField(Field* pF); // clear field of all particles, free memory

void forceCur(Field F); // Calculate the force imparted on the current particle by
				        // all the other particles
void forceAll(Field F); // does forceCur for all particles

void move(Field F); // change position of all particles, update grid

void moveFront(Field F); // moves cursor to front
void moveNext(Field F); // moves cursor to next item

void merge(Field F); // "merges" any particles occupying the same space, increasing mass of one while removing the other
void add(Field F, double x, double y); // adds particle to front of field list, with position x, y

void clear(Field F); // removes all particles from field, frees particles

void printList(Field F); // prints all particles in field in list form
void printField(Field F); // prints field form