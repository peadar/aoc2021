#include <stdio.h>
#include <stdlib.h>

enum {
   expect_space,
   expect_num,
   nextline,
   done
};

int targets[10];
int c;
int l;

int
main()
{
   while (targets[1] != done) {
      switch (targets[1]) {
         case nextline:
            l = 0;
            targets[1] = expect_space;
            break;

         case expect_space:
            switch (c = getc(stdin)) {
               case ' ':
                  targets[1] = expect_num;
                  break;
               case -1:
                  targets[1] = done;
                  break;
               default:
                  ++l;
                  break;
            }
            break;

         case expect_num:
            switch (c = getc(stdin)) {
               case '0': case '1': case '2': case '3': case '4':
               case '5': case '6': case '7': case '8': case '9':
                  targets[0] = targets[0] * 10 + c - '0';
                  break;
               case '\n':
                  targets[l] += targets[0];
                  targets[l+1] += (targets[4] - targets[2] ) * targets[0];
                  targets[0] = 0;
                  targets[1] = nextline;
                  break;
               default:
                  abort();
            }
            break;
         case done:
            break;
      }
   }
   printf("%d\n", targets[8] * targets[7]);
}

