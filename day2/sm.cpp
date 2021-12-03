#include <stdio.h>
int i[11];
int main() {
   while((i[9]=getc(stdin)) != -1) {
      if(i[1]&1) {
         if (i[9] > 32) {
            i[0] = i[0] * 10 + i[9] - 48;
            continue;
         }
         i[i[10]] += i[0];
         i[i[10]+1] += (i[4] - i[2] ) * i[0];
         i[10] = i[0] = 0;
         i[1]++;
         continue;
      }
      i[i[9] == ' ' ? 1 : 10]++;
   }
   printf("%d\n", i[8] * i[7]);
}
