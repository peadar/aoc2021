#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <cstdlib>

using namespace std;
using TwoChars = pair<char, char>; // Adjacent pair of characters.
using Rules = map<TwoChars, char>; // Rules: XY->Z
using Counts = map<TwoChars, unsigned long>; // Counts of specific pairs.

int
main(int argc, char *argv[])
{
   int iterations = argc >= 2 ? strtoul(argv[1], 0, 0) : 10;

   string polymer, s;
   getline(cin, polymer);
   getline(cin, s);

   Rules rules;
   for (;;) {
      getline(cin, s);
      if (s == "")
        break;
      rules[{s[0], s[1]}] = s[6];
   }

   Counts counts; // count the pairs in the initial polymer string.
   for (size_t i = 0; i < polymer.size() - 1; ++i)
      counts[{polymer[i], polymer[i+1]}]++;

   // Each replacement destroys all pairs of one type, and creates two new
   // distinct pairs from each.  Count the numbers of each pair.
   for (auto i = 0; i < iterations; ++i) {
      Counts newCounts;
      for (auto &old : counts) {
         char neu = rules.at(old.first);
         newCounts[ { old.first.first, neu } ] += old.second;
         newCounts[ { neu, old.first.second } ] += old.second;
      }
      counts = std::move(newCounts);
   }

   // we know how many of each pair we have. Count the individual characters...
   std::map<char, unsigned long> charCounts;
   for (auto &old : counts) {
      charCounts[old.first.first]+=old.second;
      charCounts[old.first.second]+=old.second;
   }

   // ... but each actual character appears in *2* pairs, so divide by two ...
   // ... except the first and last chars appear in only *one* pair. All
   // characters will have an even count except potentially for the first and
   // last, which will have an odd count, so we round the odd numbers up.
   unsigned long low = std::numeric_limits<unsigned long>::max(), high=0;
   for (auto &c : charCounts) {
      auto v = c.second = (c.second + 1) / 2;
      low = min(low, v);
      high = max(high, v);
   }
   std::cout << high - low << std::endl;
}
