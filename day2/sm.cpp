#include <stdio.h>
#include <stdlib.h>

enum {
   expect_space,
   expect_num,
   done
} s;

int num;
int *target;
int aim;
int mul;
int horiz;
int depth;
int c;

int
main()
{
   while (s != done) {
      switch (s) {
         case expect_space:
            switch (c = getc(stdin)) {
               case ' ':
                  s = expect_num;
                  break;
               case 'n':
                  target = &aim;
                  mul = 1;
                  break;
               case 'p':
                  target = &aim;
                  mul = -1;
                  break;
               case 'd':
                  target = &horiz;
                  mul = 1;
                  break;
               case -1:
                  s = done;
                  break;

            }
            break;

         case expect_num:
            switch (c = getc(stdin)) {
               case '0': case '1': case '2': case '3': case '4':
               case '5': case '6': case '7': case '8': case '9':
                  num = num * 10 + c - '0';
                  break;
               case '\n':
                  *target += num * mul;
                  if (target == &horiz)
                     depth += aim * num;
                  num = 0;
                  target = nullptr;
                  s = expect_space;
                  break;
               default:
                  abort();
            }
            break;
         case done:
            break;
      }
   }
   printf("%d\n", depth * horiz);
}

