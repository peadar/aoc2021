#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
int main() {
   using Value = unsigned long;
   std::vector<Value> values;
   size_t maxbits = 0;
   std::transform(std::istream_iterator<std::string>(std::cin),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(values),
                  [&maxbits](const std::string &s) {
                     maxbits = std::max(maxbits, s.size());
                     return std::stol(s, 0, 2);
                  });
   std::sort(values.begin(), values.end());
   Value out = 1;
   for (int pass = 0; pass < 2; ++pass) {
      auto top = values.begin();
      auto bottom = values.end();
      for (Value key = Value(1) << (maxbits-1); bottom[-1] != *top; key /= 2) {
         auto partition = std::partition_point(top, bottom,
                                    [key] (auto a) { return (a & key) == 0; } );
         if (partition - top <= bottom - partition == bool(pass))
            top = partition;
         else
            bottom = partition;
      }
      out *= *top;
   }
   std::cout << out << std::endl;
}
