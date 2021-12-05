#include<iostream>
#include<fstream>
#include<vector>
#include<iterator>
#include<string>
using namespace std;
struct P {
   int x, y;
   static P max;
};
P P::max;
struct L {
   P a, b;
};
istream &operator >> (istream &is, P &p) {
   char comma;
   is >> p.x >> comma >> p.y;
   P::max.x = max(P::max.x, p.x);
   P::max.y = max(P::max.y, p.x);
   return is;
}
istream &operator >> (istream &is, L &l) {
   string arrow;
   return is >> l.a >> arrow >> l.b;
}
int main(int argc, char *argv[]) {
   vector<L> v;
   copy(istream_iterator<L>(cin), istream_iterator<L>(), back_inserter(v));
   for (int part = 1; part <= 2; ++part) {
      vector<int> pixels((P::max.x + 1) * (P::max.y + 1));
      int count = 0;
      int crosses = 0;
      for (const auto &l : v) {
         int dx = l.a.x == l.b.x ? 0 : l.a.x < l.b.x ? 1 : -1;
         int dy = l.a.y == l.b.y ? 0 : l.a.y < l.b.y ? 1 : -1;
         if (part == 1 && dx != 0 && dy != 0)
            continue;
         for (int x = l.a.x, y = l.a.y;; x += dx, y += dy ) {
            if (++pixels[y * (P::max.x + 1) + x] == 2)
               crosses++;
            if (x == l.b.x && y == l.b.y)
               break;
         }
      }
      cout << "part " << part << ": " << crosses << "\n";
   }
}
