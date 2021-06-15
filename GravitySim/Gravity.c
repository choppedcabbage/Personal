/*
Lucas Tung
Gravity Simulator
Gravity.c
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "Field.h"

int main() {

   int steps = 1;
   
   printf("hello\n");
   Field F = newField();
   add(F, 1, 1);
   add(F, 2, 7);
   add(F, 4, 3);
   printList(F);
   printField(F);
   
   while(steps != 0){
      printf("How many steps? type '0' to quit\n");   
      scanf("%d", &steps);
      for(int i = 0; i < steps; i++){
         updateVelAll(F);
         updatePosAll(F);
      }
      printField(F);
      printList(F);
   }
   
   printf("goodbye\n");
   return EXIT_SUCCESS;
}