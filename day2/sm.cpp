#include <stdio.h>
#include <stdlib.h>

enum { expect_space, expect_num, nextline, done };

int targets[9];
int c;
int l;

int
main()
{
   for(;;) {
      switch (targets[1]) {
         case 0:
            switch (c = getc(stdin)) {
               case ' ':
                  targets[1]++;
                  break;
               case -1:
                  targets[1]+=3;
                  break;
               default:
                  ++l;
                  break;
            }
            break;

         case 1:
            switch (c = getc(stdin)) {
               case '\n':
                  targets[l] += targets[0];
                  targets[l+1] += (targets[4] - targets[2] ) * targets[0];
                  targets[1]++;
                  break;
               default:
                  targets[0] = targets[0] * 10 + c - 48;
                  break;
            }
            break;

         case 2:
            l = 0;
            targets[0] = 0;
            targets[1]-=2;
            break;

         case 3:
            printf("%d\n", targets[8] * targets[7]);
            exit(0);
      }
   }
}

