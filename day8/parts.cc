#include <numeric>
#include <optional>
#include <vector>
#include <bitset>
#include <string>
#include <iostream>
using namespace std;
namespace {
using SegmentSet = bitset<7>;
SegmentSet SEG(string_view in) {
   SegmentSet out;
   for (auto c : in)
      out.set(c - 'a');
   return out;
}

string tok(istream &is = cin) {
   string s;
   is >> s;
   return s;
}

vector<SegmentSet> good { // actual 7-segment values for digits 0-9
   SEG("abcefg"), SEG("cf"), SEG("acdeg"), SEG("acdfg"), SEG("bcdf"),
   SEG("abdfg"), SEG("abdefg"), SEG("acf"), SEG("abcdefg"), SEG("abcdfg")
};

// Brute-force solution:
// Try each permutation of digits, and test if the result of mapping the
// ciphered digits to good produces a match for all digits we assert there's a
// single permutation that solves this input line
//
int solve(const vector<SegmentSet> &patterns, const vector<int> &code) {
   vector<int> perms { 0,1,2,3,4,5,6 };
   do {
      int digitmap[10];
      for (auto &in : patterns) {
         // apply permutation to input pattern.
         SegmentSet mapped;
         for (auto i = 0; i < 7; ++i)
            if (in[i])
               mapped.set(perms[i]);
         // See if there's a matching digit in the real 7-segment layout.
         auto f = find(good.begin(), good.end(), mapped);
         if (f == good.end())
            break; // the mapped pattern is not a valid digit - next permutation.
         digitmap[&in - &patterns[0]] = f - good.begin();
         if (&in == &patterns[0] + patterns.size() - 1) // matched all patterns - decipher the code and return it
            return accumulate( code.begin(), code.end(), 0, [&digitmap] (int a, int b) { return a * 10 + digitmap[b]; });
      }
   } while (next_permutation(perms.begin(), perms.end()));
   abort(); // all permutations tried and no solution.
}

optional<pair<vector<SegmentSet>, vector<int>>>
parseLine(istream &in) {
   pair<vector<SegmentSet>, vector<int>> rv;
   for (int i = 0; i < 10; ++i)
      rv.first.push_back(SEG(tok(in)));
   if (in.eof()) // we'll read some junk above, but it's harmless.
      return nullopt;
   if (tok(in) != "|")
      abort();
   for (int i = 0; i < 4; ++i) // map code digits directly to the index of the pattern for the associated display.
      rv.second.push_back(find(rv.first.begin(), rv.first.end(),SEG(tok(in))) - rv.first.begin());
   return optional(rv);
}

}
int main() {
   int part1 = 0, part2 = 0;
   for (;;) {
      auto parsed = parseLine(cin);
      if (!parsed)
         break;
      int code = solve(parsed->first, parsed->second);
      part2 += code;
      while (code) {
         auto res = code % 10;
         if (res == 1 || res == 4 || res == 7)
            part1++;
         code /= 10;
      }
   }
   cout << "part1: " << part1 << endl << "part2: " << part2 << endl;
}
