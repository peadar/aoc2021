#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <unistd.h>
using namespace std;
namespace {
template <typename T> struct PPM {
   const T &value;
   PPM(T &value_) : value(value_) {}
};
class Game {
   using Grid = vector<vector<int>>;
   Grid grid;
   long cells {};
   void increment(size_t row, size_t col);
   void flash(size_t row, size_t col);
public:
   friend istream &operator >>(istream &, Game &);
   friend ostream &operator <<(ostream &, const Game &);
   friend ostream & operator <<(ostream &os, const PPM<Game> &game);
   long iterate();
   void randomize(size_t, size_t);
   long cellCount() const { return cells; }
};
void Game::randomize(size_t rows, size_t cols) {
   srandom(time(0)); // yeah, I know...
   for (size_t row = 0; row < rows; ++row) {
      grid.push_back({});
      auto &data = grid.back();
      for (size_t col = 0; col < cols; ++col) {
         data.push_back(random() % 10);
      }
   }
}
ostream & operator <<(ostream &os, const PPM<Game> &game) {
   os << "P3 " << game.value.grid[0].size() << " " << game.value.grid.size() << " " << 10 << std::endl;
   for (auto &col : game.value.grid) {
      for (auto &value : col)
         os << value / 3 << " " << value /2 << " " << value  << " " ;
      os << "\n";
   }
   return os;
}
istream & operator >>(istream &is, Game &game) {
   game.cells = 0;
   for (;;) {
      string in;
      getline(is, in);
      if (in == "")
         break;
      game.grid.push_back({});
      auto &thisrow = game.grid.back();
      for (auto c : in) {
         thisrow.push_back(c - '0');
         game.cells++;
      }
   }
   return is;
}
void Game::flash(size_t row, size_t col) {
   for (int dr = -1; dr <= 1; ++dr)
      for (int dc = -1; dc <= 1; ++dc)
         if (dr || dc)
            increment(row + dr, col + dc);
}
void Game::increment(size_t row, size_t col) {
   if (row >= grid.size() || col >= grid[row].size())
      return;
   if (++grid[row][col] != 10)
      return;
   flash(row, col);
}
long Game::iterate() {
   for (size_t row = 0; row < grid.size(); ++row)
      for (size_t col = 0; col < grid[row].size(); ++col)
         increment(row, col);
   long flashes= 0;
   for (auto &col : grid) {
      for (auto &v : col) {
         if (v >= 10) {
            flashes++;
            v = 0;
         }
      }
   }
   return flashes;
}
std::pair<int, int> solve(Game &g, int maxiter, string_view ppmpath) {
   long totalFlashes = 0, part1 = 0, part2 = 0;
   for (int step = 1; step < maxiter && (part1 == 0 || part2 == 0); ++step) {
      long flashes = g.iterate();
      totalFlashes += flashes;
      if (step == 100)
         part1 = totalFlashes;
      if (part2 == 0 && flashes == g.cellCount())
         part2 = step;
      if (ppmpath != "") {
         ostringstream oss;
         oss << ppmpath << "." << setfill('0') << setw(4) << step;
         ofstream fo(oss.str());
         fo << PPM(g);
      }
   }
   return std::make_pair<int, int>(part1, part2);
}
}
int main(int argc, char *argv[]) {
   int c;
   bool ppm = false;
   long genRows = 0, genCols = 0, maxIter = 1000;
   string ppmPath = "";
   while ((c = getopt(argc, argv, "r:c:m:pf:")) != -1)
      switch (c) {
         case 'r': genRows = strtoul(optarg, 0, 0); break;
         case 'c': genCols = strtoul(optarg, 0, 0); break;
         case 'm': maxIter = strtoul(optarg, 0, 0); break;
         case 'p': ppm=true; break;
         case 'f': ppmPath=optarg;
      }
   Game g;
   if (genCols && genRows)
      g.randomize(genRows, genCols);
   else
      cin >> g;
   auto [ part1, part2 ] = solve(g, maxIter, ppmPath);
   if (ppm)
      cout << PPM(g);
   else
      cout << "part1: " << part1 << "\n" << "part2: " << part2 << endl;
}
