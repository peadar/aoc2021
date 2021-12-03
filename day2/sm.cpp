#include <stdio.h>
#include <stdlib.h>

enum { expect_space, expect_num, nextline, done };

int targets[9];
int c;
int l;

int
main()
{
   while((c=getc(stdin)) != -1) {
      switch (targets[1] % 2) {
         case 0:
            switch (c) {
               case ' ':
                  targets[1]++;
                  break;
               default:
                  ++l;
                  break;
            }
            break;
         case 1:
            if (c > 32) {
               targets[0] = targets[0] * 10 + c - 48;
               break;
            }
            targets[l] += targets[0];
            targets[l+1] += (targets[4] - targets[2] ) * targets[0];
            l = 0;
            targets[0] = 0;
            targets[1]++;
      }
   }
   printf("%d\n", targets[8] * targets[7]);
   exit(0);
}

