#include <iostream>
#include <numeric>
int main(int argc, char *argv[]) {
   unsigned long counts[9] = {};
   while (!std::cin.eof()) {
      unsigned long i;
      char comma;
      std::cin >> i >> comma;
      counts[i]++;
   }
   int target_days = argc >= 2 ? strtoul(argv[1], 0, 0) : 80;
   for (int i = 0; i < target_days; ++i) {
      unsigned long spawncount = counts[i%9];
      counts[(i + 7) % 9] += spawncount;
      counts[(i + 9) % 9] = spawncount;
   }
   std::cout << std::accumulate(counts, counts + 9, 0UL) << std::endl;
}
