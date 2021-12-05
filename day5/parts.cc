#include<iostream>
#include<map>
#include<iterator>
#include<string>
using namespace std;
struct P {
   int x, y;
   bool operator < (const P &rhs) const noexcept { return x < rhs.x || (x == rhs.x && y < rhs.y); }
};
struct L { P a, b; };
istream &operator >> (istream &is, P &p) {
   char comma;
   return is >> p.x >> comma >> p.y;
}
istream &operator >> (istream &is, L &l) {
   string arrow;
   return is >> l.a >> arrow >> l.b;
}
int main() {
   std::map<P, std::pair<int, int>> pixels;
   int part1 = 0, part2 = 0;
   for (auto i = istream_iterator<L>(cin); i != istream_iterator<L>(); ++i) {
      int dx = i->a.x == i->b.x ? 0 : i->a.x < i->b.x ? 1 : -1;
      int dy = i->a.y == i->b.y ? 0 : i->a.y < i->b.y ? 1 : -1;
      for (int x = i->a.x, y = i->a.y;; x += dx, y += dy ) {
         auto &count = pixels[P{x, y}];
         if ((dx == 0 || dy == 0) && ++count.first == 2)
            part1++;
         if (++count.second == 2)
            part2++;
         if (x == i->b.x && y == i->b.y)
            break;
      }
   }
   cout << "part1: " << part1 << std::endl << "part2: " << part2 << "\n";
}
