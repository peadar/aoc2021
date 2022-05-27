#include "sn.h"
#include <sstream>

static std::string explodeOne(const std::string &in) {
   std::istringstream is(in);
   SnailNum sn;
   sn.parse(is);
   sn.explode();
   std::ostringstream os;
   os << sn;
   return os.str();
}

int main() {
   std::pair<std::string, std::string> cases[] {
      { "[[[[[9,8],1],2],3],4]", "[[[[0,9],2],3],4]" },
      { "[7,[6,[5,[4,[3,2]]]]]", "[7,[6,[5,[7,0]]]]" },
      { "[[6,[5,[4,[3,2]]]],1]", "[[6,[5,[7,0]]],3]" },
      { "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]" },
      { "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[7,0]]]]" }
   };

   for (auto &&[ input, expected ] : cases) {
      auto generated = explodeOne(input);
      if (generated != expected) {
         std::cout << "<" << generated <<  "> != <" << expected << ">!\n";
         abort();
      }
   }
}
