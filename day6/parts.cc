#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
int main() {
   unsigned long counts[9] = {};
   while (!std::cin.eof()) {
      unsigned long i;
      char comma;
      std::cin >> i >> comma;
      counts[i]++;
   }
   for (size_t i = 0; i != 257; counts[(i + 7) % 9] += counts[i%9], ++i)
      if (i == 80 || i == 256)
         std::cout << "day " << i << ": " << std::accumulate(counts, counts + 9, 0UL) << std::endl;
}
