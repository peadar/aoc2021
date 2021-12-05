#include<iostream>
#include<vector>
#include<map>
#include<iterator>
#include<string>
using namespace std;
struct P { int x, y; };
struct L { P a, b; };
bool operator < (const P &lhs, const P&rhs) noexcept { return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); }
template <typename T> T &tmpval() { static T t{}; return t; }
istream &operator >> (istream &is, P &p) { return is >> p.x >> tmpval<char>() >> p.y; }
istream &operator >> (istream &is, L &l) { return is >> l.a >> tmpval<string>() >> l.b; }
int main(int argc, char *argv[]) {
   std::vector<pair<int, int>> pixels(1000000);
   int part1 = 0, part2 = 0, imax = 0, xmax = 0, ymax = 0;
   for (auto i = istream_iterator<L>(cin); i != istream_iterator<L>(); ++i) {
      int dx = i->a.x == i->b.x ? 0 : i->a.x < i->b.x ? 1 : -1;
      int dy = i->a.y == i->b.y ? 0 : i->a.y < i->b.y ? 1 : -1;
      for (int x = i->a.x, y = i->a.y; x != i->b.x + dx || y != i->b.y + dy; x += dx, y += dy ) {
         auto &counter = pixels[y * 1000 + x];
         if ((dx == 0 || dy == 0) && ++counter.first == 2)
            part1++;
         if (++counter.second == 2)
            part2++;
         imax = max(counter.second, imax);
      }
      xmax = max(xmax, max(i->b.x, i->a.x));
      ymax = max(ymax, max(i->b.y, i->a.y));
   }
   if (argc == 2 && std::string(argv[1]) == "ppm") {
      cout << "P3 " << xmax << " " << ymax << " "<< imax << std::endl;
      for (auto y = 0; y < ymax; ++y) {
         for (auto x = 0; x < xmax; ++x) {
            int intensity = pixels[y * 1000 + x].second;
            for (int i = 0; i < 3; ++i)
               cout << intensity << " ";
         }
         cout << endl;
      }
   } else {
      cout << "part1: " << part1 << endl << "part2: " << part2 << endl ;
   }
}
