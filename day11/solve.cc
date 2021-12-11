#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

class Game {
   using Grid = vector<vector<int>>;
   Grid grid;
   long cells;
   void increment(size_t row, size_t col);
   void flash(size_t row, size_t col);
public:
   friend std::istream &operator >>(std::istream &, Game &);
   long iterate();
   long cellCount() const { return cells; }
};

std::istream & operator >>(std::istream &is, Game &game) {
   game.cells = 0;
   for (;;) {
      std::string in;
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

int main(int argc, char *argv[]) {
   Game g;
   cin >> g;
   long totalFlashes = 0;
   int part1 = 0, part2 = 0;
   for (int step = 1; part1 == 0 || part2 == 0; ++step) {
      long flashes = g.iterate();
      totalFlashes += flashes;
      if (step == 100)
         part1 = totalFlashes;
      if (part2 == 0 && flashes == g.cellCount())
         part2 = step;
   }
   std::cout << "part1: " << part1 << std::endl;
   std::cout << "part2: " << part2 << std::endl;
}
