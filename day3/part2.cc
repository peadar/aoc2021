#include <vector>
#include <assert.h>
#include <algorithm>
#include <string>
#include <iostream>
int main() {
   using Value = unsigned long;
   std::vector<Value> values;
   size_t maxbits = 0;
   for (;;) {
      std::string s;
      std::cin >> s;
      if (s == "")
         break;
      maxbits = std::max(s.size(), maxbits);
      values.push_back(strtoul(s.c_str(), 0, 2));
   }
   std::sort(values.begin(), values.end());
   Value out = 1;
   for (int pass = 0; pass < 2; ++pass) {
      auto top = values.begin();
      auto bottom = values.end();
      for (Value key = Value(1) << (maxbits-1); bottom[-1] != *top; key /= 2) {
         auto searchtop = top;
         auto searchbottom = bottom;
         while (searchbottom - searchtop > 1) {
            auto center = searchtop + (searchbottom - searchtop) / 2;
            if ((*center & key) == 0)
               searchtop = center;
            else
               searchbottom = center;
         }
         if (searchbottom - top <= bottom - searchbottom == bool(pass))
            top = searchbottom;
         else
            bottom = searchbottom;
      }
      out *= *top;
   }
   std::cout << out << std::endl;
}
