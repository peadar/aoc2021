#include <iostream>
#include <limits>
namespace {
using NUM = uint64_t;
constexpr NUM NUM_MAX = std::numeric_limits<NUM>::max();
constexpr NUM NUM_MIN = std::numeric_limits<NUM>::min();
static unsigned hexdigit(char c) { return c >= '0' && c <= '9' ? c - '0' :
   c >= 'a' && c <= 'f' ? c - 'a' + 10 : c >= 'A' && c <= 'F' ? c - 'A' + 10 : (abort(), 0); }
struct Bitstream {
   std::string input;
   size_t bit_offset;
   Bitstream(const std::string s) : input{s}, bit_offset{} {}
   NUM consume(size_t count) {
      NUM ans = 0;
      for (size_t endoff = bit_offset + count; bit_offset != endoff; ++bit_offset)
         ans = ans << 1|(hexdigit(input[bit_offset / 4]) >> (3 - bit_offset % 4) & 1);
      return ans;
   }
};
unsigned versionSum; // for part1.
NUM packet(Bitstream &bs); // required forward decl.
NUM literal(Bitstream &bs, NUM a = 0) {
   bool more = bs.consume(1);
   a = a << 4 | bs.consume(4);
   return more ? literal(bs, a) : a;
}
NUM op(Bitstream &bs, int type) {
   static const std::pair<NUM, NUM(*)(NUM, NUM)> ops[] { /* initial value, accumuator function */
      { 0,              [](NUM a, NUM b){ return a + b; } },
      { 1,              [](NUM a, NUM b){ return a * b; } },
      { NUM_MAX,        [](NUM a, NUM b){ return std::min(a, b); } },
      { NUM_MIN,        [](NUM a, NUM b){ return std::max(a, b); } },
      { }, // type 4 is a literal, handled separately.
      // binary ops for <, >, = : use a sentinel for first value so the accumulator works.
      { NUM_MAX,        [](NUM a, NUM b){ return a == NUM_MAX ? b : a > b; } },
      { NUM_MAX,        [](NUM a, NUM b){ return a == NUM_MAX ? b : a < b; } },
      { NUM_MAX,        [](NUM a, NUM b){ return a == NUM_MAX ? b : a == b; } },
   };
   auto [ init, accum ] = ops[type];
   if (bs.consume(1) == 0)
      for (auto len = bs.consume(15), start = bs.bit_offset; bs.bit_offset != len + start; )
         init = accum(init, packet(bs));
   else
      for (auto len = bs.consume(11); len; --len)
         init = accum(init, packet(bs));
   return init;
}
NUM packet(Bitstream &bs) {
   versionSum += bs.consume(3);
   auto type = bs.consume(3);
   if (type == 4)
      return literal(bs);
   return op(bs, type);
}
}
int main(int argc, char *argv[]) {
   std::string text;
   if (argc >= 2)
      text = argv[1];
   else
      getline(std::cin, text);
   Bitstream bs(text);
   auto result = packet(bs);
   std::cout << "part1: " << versionSum << "\n";
   std::cout << "part2: " << result << "\n";
}
