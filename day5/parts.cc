#include<iostream>
#include<iterator>
#include<vector>
#include<string>
using namespace std;
struct P { int x, y; };
struct L { P a, b; };
template <typename T> T &tmpval() { static T t{}; return t; }
istream &operator >> (istream &is, P &p) { return is >> p.x >> tmpval<char>() >> p.y; }
istream &operator >> (istream &is, L &l) { return is >> l.a >> tmpval<string>() >> l.b; }
int main() {
   int part1=0, part2=0;
   // each byte is 2 pixels. Each pixel is 2 nibbles, each nibble is the number
   // of lines crossing that point, saturated to 2.
   std::vector<uint8_t> pixels(500'000);
   for (auto i = istream_iterator<L>(cin); i != istream_iterator<L>(); ++i) {
      int dx = i->a.x == i->b.x ? 0 : i->a.x < i->b.x ? 1 : -1;
      int dy = i->a.y == i->b.y ? 0 : i->a.y < i->b.y ? 1 : -1;
      for (int x = i->a.x, y = i->a.y; x != i->b.x + dx || y != i->b.y + dy; x += dx, y += dy ) {
         auto &counter = pixels[y * 500 + x/2];
         int shift = x % 2 == 0 ? 0 : 4;
         auto p1 = (counter >> shift) & 0x3;
         auto p2 = (counter >> (shift + 2)) & 0x3;
         if (dx == 0 || dy == 0) {
            if (p1 < 2 && ++p1 == 2)
               part1++;
         }
         if (p2 < 2 && ++p2 == 2)
            part2++;
         counter &= ~(0xf << shift);
         counter |= (p1 | p2 << 2)  << shift;
      }
   }
   cout << "part1: " << part1 << endl << "part2: " << part2 << endl;
}
