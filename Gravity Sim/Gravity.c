/*
Lucas Tung
Gravity thing
Gracity.c
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include "Field.h"

int main() {

   int papa = 1;
   
   printf("hello\n");
   Field F = newField();
   add(F, 1, 1);
   add(F, 2, 7);
   add(F, 4, 3);
   printList(F);
   printField(F);
   
   while(papa != 0){
      printf("How many steps? type '0' to quit\n");   
      scanf("%d", &papa);
      for(int i = 0; i < papa; i++){
         forceAll(F);
         move(F);
         merge(F);
      }
      printField(F);
      printList(F);
   
   }
   
   printf("goodbye\n");
   return EXIT_SUCCESS;
}