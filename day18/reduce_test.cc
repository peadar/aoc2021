#include "sn.h"
#include <sstream>

template <typename T> std::string stringify(const T &streamable) {
   std::ostringstream os;
   os << streamable;
   return os.str();
}

int main() {
   SnailNum l, r, expected;
   std::stringstream("[[[[4,3],4],4],[7,[[8,4],9]]]") >> l;
   std::stringstream("[1,1]") >> r;
   std::stringstream("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]") >> expected;
   SnailNum sum = l + r;
   assert(stringify(sum) == stringify(expected));
}
