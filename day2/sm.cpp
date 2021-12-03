#include <stdio.h>
int i[11], *j=i+10;
int main() {
   while((i[9]=getc(stdin)-48) != -49) {
      if(i[1]&1) {
         if (i[9] > 0) {
            i[0] = i[0] * 10 + i[9];
            continue;
         }
         i[*j] += i[0];
         i[*j+1] += (i[4] - i[2] ) * *i;
         *j = *i = 0;
         i[1]++;
         continue;
      }
      i[i[9] == -16 ? 1 : 10]++;
   }
   printf("%d\n", i[8] * i[7]);
}
