/*
Lucas Tung
Gravity Simulator
Particle.c
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "Field.h"

#define GRAV 6.67408 // grav constant
#define SLOW 10 // reduces change in position of particles
#define SIZE 20 // size of field/grid


typedef struct PartObj {
   int mass;
   double xpos;
   double ypos;
   double xvel;
   double yvel;
   struct PartObj* next;
} PartObj;

typedef PartObj* Part;

Part newPart(double x, double y) {
   Part P = malloc(sizeof(PartObj));
   assert(P != NULL);
   P->mass = 1;
   P->xpos = x;
   P->ypos = y;
   P->xvel = 0;
   P->yvel = 0;
   P->next = NULL;
   return P;
}

void freePart(Part* pP) {
   if(pP != NULL && *pP != NULL) {
      free(*pP);
      *pP = NULL;
   }
}

typedef struct FieldObj {
   Part front;
   Part back;
   Part cursor;
   int grid[SIZE][SIZE];
} FieldObj;

Field newField(void) {
   Field F = malloc(sizeof(FieldObj));
   assert(F != NULL);
   F->front = NULL;
   F->back = NULL;
   F->cursor = NULL;
   return F;
}
void freeField(Field* pF) {
   if(pF != NULL && *pF != NULL) {
      clear(*pF);
      free(*pF);
      *pF = NULL;
   }
}


void add(Field F, double x, double y){
   if(F == NULL) {
      printf("Field Error: calling add() on NULL Field reference\n");
      exit(1);
   }
   Part P = newPart(x, y);
   if(F->back == NULL) F->back = P;
   P->next = F->front;
   F->front = P;
}

void clear(Field F) {
   if(F == NULL) {
      printf("Field Error: calling clear() on NULL Field reference\n");
      exit(1);
   }
   Part P = F->front;
   while(P != NULL) {
      Part Q = P;
      P = P->next;
      freePart(&Q);
   }
}

void moveFront(Field F) {
   if(F == NULL) {
      printf("Field Error: calling forceCur() on NULL Field reference\n");
      exit(1);
   }
   F->cursor = F->front;
}

void moveNext(Field F) {
   if(F == NULL) {
      printf("Field Error: calling forceCur() on NULL Field reference\n");
      exit(1);
   }
   F->cursor = F->cursor->next;

}

// void forceCur(Field F){
//    if(F == NULL) {
//       printf("Field Error: calling forceCur() on NULL Field reference\n");
//       exit(1);
//    }
//    Part P = F->cursor;
//    if(P == NULL) {
//       printf("Field Error: calling forceCur() on NULL cursor\n");
//       exit(1);
//    }
//    Part Q = F->front;
//    double xforce = 0, yforce = 0; // total force of all Q's on P
//    double dist, aforce; // aforce is magnitude of the force of Q on P
//    while(Q != NULL) {
//       dist = Q->xpos - P->xpos;
//       if(dist > 0.5 || dist < -0.5) {
//          aforce = (GRAV * (P->mass) * (Q->mass) * pow(dist, -2));
//          if(dist > 0) xforce += aforce;
//          else xforce -= aforce;
//       }
//       dist = Q->ypos - P->ypos;
//       if(dist > 0.5 || dist < -0.5) {
//          aforce = (GRAV * (P->mass) * (Q->mass) * pow(dist, -2));
//          if(dist > 0) yforce += aforce;
//          else yforce -= aforce;
//       }
//       Q = Q->next;
//    }
//    P->xvel += (xforce / P->mass);
//    P->yvel += (yforce / P->mass);
//    if(xforce == 0) P->xvel = 0;
//    if(yforce == 0) P->yvel = 0;
// }


// this doesnt account for 2 particles touching
void updateVelCursor(Field F){
   	if(F == NULL) {
      	printf("Field Error: calling updateVel() on NULL Field reference\n");
      	exit(1);
   	}
   	Part P = F->cursor;
   	Part Q = F->front;
   	double xdist, ydist, dist, force, xforce = 0, yforce = 0;
	while(Q != NULL) {
   		xdist = Q->xpos - P->xpos;
   		ydist = Q->ypos - P->ypos;
   		dist = sqrt((pow(xdist, 2) + pow(ydist, 2)));
   		if(dist > 0.5) {
   			force = GRAV * P->mass * Q->mass / pow(dist, 2);
   			xforce += force * xdist / dist;
   			yforce += force * ydist / dist;
   		}
   		Q = Q->next;
   	}
   	P->xvel += (xforce / P->mass);
	P->yvel += (yforce / P->mass);
}


// void forceAll(Field F) {
//    if(F == NULL) {
//       printf("Field Error: calling forceAll() on NULL Field reference\n");
//       exit(1);
//    }
//    F->cursor = F->front;
//    while(F->cursor != NULL) {
//       forceCur(F);
//       F->cursor = F->cursor->next;
//    }
// }


void updateVelAll(Field F) {
	if(F == NULL) {
      	printf("Field Error: calling updateVelAll() on NULL Field reference\n");
      	exit(1);
   	}
   	F->cursor = F->front;
   	while(F->cursor != NULL) {
      	updateVelCursor(F);
      	F->cursor = F->cursor->next;
   	}
}

void updatePosAll(Field F) {
   if(F == NULL) {
      printf("Field Error: calling move() on NULL Field reference\n");
      exit(1);
   }
   Part P = F->front;
   while(P != NULL) {
      P->xpos += (P->xvel) / SLOW;
      P->ypos += (P->yvel) / SLOW;
      P = P->next;
   }
}

void printList(Field F) {
   if(F == NULL) {
      printf("Field Error: calling forceCur() on NULL Field reference\n");
      exit(1);
   }
   Part P = F->front;
   while(P != NULL) {
      printf("xp: %f, yp: %f, xv: %f, yv: %f\n", P->xpos, P->ypos, P->xvel, P->yvel);
      P = P->next;
   }
}

void printField(Field F) {
   if(F == NULL) {
      printf("Field Error: calling printField() on NULL Field reference\n");
      exit(1);
   }
   int i, j;
   for(i = 0; i < SIZE; i++) {
      for(j = 0; j < SIZE; j++) {
         F->grid[i][j] = 0;
      }
   }
   Part P = F->front;
   while(P != NULL){
      i = P->xpos;
      j = P->ypos;
      F->grid[i][j] += P->mass;
      P = P->next;
   }
   for(int j = SIZE - 1; j >= 0; j--) {
      for(int i = 0; i < SIZE; i++) {
         printf("%d ", F->grid[i][j]);
      }
      printf("\n");
   }
}

void merge(Field F) {
   if(F == NULL) {
      printf("Field Error: calling merge() on NULL Field reference\n");
      exit(1);
   }
   int ydist, xdist;
   Part P = F->front;
   while(P != NULL) {
      Part R = P;
      Part Q = R->next;
      while(Q != NULL) {
         xdist = Q->xpos - P->xpos;
         ydist = Q->ypos - P->ypos;
         if(xdist <= 0.5 && xdist >= -0.5 && ydist <= 0.5 && ydist >= -0.5) {
            P->xvel = (P->xvel * P->mass) + (Q->xvel * Q->mass); // 1st step of momentum
            P->yvel = (P->yvel * P->mass) + (Q->yvel * Q->mass); 
            P->mass += Q->mass;
            P->xvel /= P->mass; // done w conservation of momentum?
            P->yvel /= P->mass;
            R->next = Q->next;
            freePart(&Q);
            Q = R->next;
         } else {
            R = R->next;
            Q = Q->next;
         }
      }
      P = P->next;
   }
}


