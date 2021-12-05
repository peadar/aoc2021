#include<iostream>
#include<iterator>
#include<vector>
#include<string>
using namespace std;
struct P { int x, y; };
struct L { P a, b; };
struct Pixel { unsigned p1 : 2, p2: 2; }; // part1 and part2 counts. saturate at 2. We could pack two of these in a byte...
template <typename T> T &tmpval() { static T t{}; return t; }
istream &operator >> (istream &is, P &p) { return is >> p.x >> tmpval<char>() >> p.y; }
istream &operator >> (istream &is, L &l) { return is >> l.a >> tmpval<string>() >> l.b; }
int main() {
   int part1=0, part2=0;
   std::vector<Pixel> pixels(1'000'000);
   for (auto i = istream_iterator<L>(cin); i != istream_iterator<L>(); ++i) {
      int dx = i->a.x == i->b.x ? 0 : i->a.x < i->b.x ? 1 : -1;
      int dy = i->a.y == i->b.y ? 0 : i->a.y < i->b.y ? 1 : -1;
      for (int x = i->a.x, y = i->a.y; x != i->b.x + dx || y != i->b.y + dy; x += dx, y += dy ) {
         auto &counter = pixels[y * 1000 + x];
         if (dx == 0 || dy == 0)
            if (counter.p1 < 2 && ++counter.p1 == 2)
               part1++;
         if (counter.p2 < 2 && ++counter.p2 == 2)
            part2++;
      }
   }
   cout << "part1: " << part1 << endl << "part2: " << part2 << endl;
}
