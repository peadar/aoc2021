#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int
main(int argc, char *argv[])
{
   string polymer, ignore;
   getline(cin, polymer);
   getline(cin, ignore);
   int iterations = 10;

   int c;
   while ((c = getopt(argc, argv, "i:")) != -1) {
      switch (c) {
         case 'i':
            iterations = strtoul(optarg, 0, 0);
            break;
      }
   }

   map<pair<char, char>, char> rules;
   for (;;) {
      string ruleText;
      getline(cin, ruleText);
      if (ruleText == "")
        break;
      rules[std::make_pair(ruleText[0], ruleText[1])] = ruleText[6];
   }

   for (int i = 0; i < iterations; ++i) {
      std::string newPoly;
      char c1 = polymer[0];
      newPoly.push_back(c1);
      for (size_t i = 1; i < polymer.size(); ++i) {
         char c2 = polymer[i];
         char extra = rules[{c1, c2}];
         newPoly.push_back(extra);
         newPoly.push_back(c2);
         c1 = c2;
      }
      polymer = std::move(newPoly);
      newPoly = "";
      std::cout << "iter " << i << ": " << polymer << std::endl;
   }
   vector<long> counts('Z' + 1 - 'A');

   for (size_t i = 0; i < polymer.size(); ++i)
      counts[polymer[i] - 'A']++;

   char smallChar = '_', bigChar = '_';
   long smallCount=numeric_limits<long>::max(), bigCount = -1;
   for (int i = 0; i < 26; ++i) {
      if (counts[i] == 0)
         continue;
      if (counts[i] > bigCount) {
         bigCount = counts[i];
         bigChar = i + 'A';
      }
      if (counts[i] < smallCount) {
         smallCount = counts[i];
         smallChar = i + 'A';
      }
   }
   std::cout << bigCount - smallCount << std::endl;
}
