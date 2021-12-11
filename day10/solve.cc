#include <stack>
#include <map>
#include <tuple>
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
using namespace std;

namespace {
map<char, int> scores { { ')', 3 }, { ']', 57 }, { '}', 1197 }, { '>', 25137 },
   { '(', 1 }, { '[', 2 }, { '{', 3 }, { '<', 4 } };
map<char, char> openFor { { ')', '(' }, { ']','[' }, { '}','{' }, { '>', '<' } };

unsigned long
processChunk(string_view s, stack<char> &brackets) {
   for (auto c : s) {
      auto o = openFor.find(c);
      if (o == openFor.end()) {
         brackets.push(c);
      } else {
         if (brackets.empty())
            throw 999;
         if (brackets.top() != o->second)
            return scores[c];
         brackets.pop();
      }
   }
   return 0;
}
unsigned long
scoreUnmatched(stack<char> &brackets) {
   unsigned long score = 0;
   for (; !brackets.empty(); brackets.pop())
      score = score * 5 + scores[brackets.top()];
   return score;
}
}
int main() {
   unsigned long part1 = 0;
   vector<unsigned long> scores;
   for (;;) {
      string l;
      getline(cin, l);
      if (l == "")
         break;
      stack<char> brackets;
      unsigned long rc = processChunk(l, brackets);
      if (rc)
         part1 += rc;
      else
         scores.push_back(scoreUnmatched(brackets));
   }
   sort(scores.begin(), scores.end());
   cout << "part1: " << part1 << endl;
   cout << "part2: " << scores[scores.size()/2] << endl;
}
