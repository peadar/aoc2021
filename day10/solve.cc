#include <stack>
#include <tuple>
#include <iostream>
#include <string>
#include <vector>
#include <string_view>

using namespace std;

namespace {
enum BracketType { OPEN, CLOSE, ERROR };
tuple<BracketType, char, unsigned> bracketClass(char c) {
   switch (c) {
      case '(': return { OPEN, ')', 3 };
      case ')': return { CLOSE, '(', 3 };
      case '[': return { OPEN, ']', 57 };
      case ']': return { CLOSE, '[', 57 };
      case '{': return { OPEN, '}', 1197 };
      case '}': return { CLOSE, '{', 1197 };
      case '<': return { OPEN, '>', 25137 };
      case '>': return { CLOSE, '<', 25137 };
      default:  return { ERROR, 0, -1 };
   }
}

unsigned long
processChunk(string_view s, stack<char> &brackets) {
   int total;
   for (auto c : s) {
      auto [ type, match, score ] = bracketClass(c);
      switch (type) {
         case OPEN:
            brackets.push(c);
            break;
         case CLOSE:
            if (brackets.empty())
               throw 999;
            if (brackets.top() != match)
               return score;
            brackets.pop();
            break;
         default:
            abort();
      }
   }
   return 0;
}
}

int main() {
   unsigned long part1 = 0;
   std::vector<long> scores;
   for (;;) {
      string l;
      getline(cin, l);
      if (l == "")
         break;
      stack<char> brackets;
      unsigned long rc = processChunk(l, brackets);
      if (rc) {
         part1 += rc;
      } else {
         unsigned long score = 0;
         while (!brackets.empty()) {
            score *= 5;
            switch (brackets.top()) {
               case '(': score += 1; break;
               case '[': score += 2; break;
               case '{': score += 3; break;
               case '<': score += 4; break;
               default: abort();
            }
            brackets.pop();
         }
         scores.push_back(score);
      }
   }
   sort(scores.begin(), scores.end());
   std::cout << "part1: " << part1 << std::endl;
   std::cout << "part2: " << scores[scores.size()/2] << std::endl;
}
