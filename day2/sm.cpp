#include <stdio.h>

enum state {
   expect_space,
   expect_num,
};

state s = expect_space;
int num = 0;
int *target = 0;
int sign = 0;
int aim;
int mul;
int horiz;
int depth;

int
main()
{
   int c;
   int num = 0;
   while ((c = getc(stdin)) != EOF) {
      switch (s) {
         case expect_space:
            switch (c) {
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
            }
            break;

         case expect_num:
            switch (c) {
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
            }
            break;
      }
   }
   printf("%d\n", depth * horiz);
}

