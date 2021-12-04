#include <bitset>
#include <assert.h>
#include <unistd.h>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <iostream>

template <typename Q> bool splitNumbers(std::istream &is, Q q) {
   int v = -1;
   std::string s;
   std::getline(is, s);
   if (s == "")
      return false;
   for (auto c : s) {
      if (isdigit(c)) {
         if (v == -1)
            v = 0;
         v = v * 10 + (c - '0');
      } else {
         if (v != -1) {
            q(v);
            v = -1;
         }
      }
   }
   q(v);
   return true;
}

struct Number {
   int row;
   int col;
};

struct Board {
   std::unordered_map<int, Number> numbers;
   std::vector<int> rowCounts;
   std::vector<int> colCounts;
   bool won = false;
   Board(std::istream &);
};

struct Game {
   std::vector<int> calledNumbers;
   std::vector<Board> boards;
   Game(std::istream &);
};

Game::Game(std::istream &is) {
   splitNumbers(is, [this] (int i){ calledNumbers.push_back(i); } );
   std::string s;
   std::getline(is, s);
   while (!is.eof())
      boards.emplace_back(is);
}

Board::Board(std::istream &is) {
   std::string s;
   int row = 0, maxcol = 0;
   for (;; ++row) {
      int col = 0;
      bool rc = splitNumbers(is, [this, row, &col](size_t value) { numbers[value] = {row, col++}; });
      maxcol = std::max(col, maxcol);
      if (!rc)
         break;
   }
   // size up row/col counters for counting hits on each row/col in bingo game.
   rowCounts.resize(row);
   colCounts.resize(maxcol);
}

int main() {
   Game g(std::cin);
   std::bitset<100> called;
   int won = 0;
   int round = 0;

   for (auto caller : g.calledNumbers) {

      if (won == g.boards.size()) // stop if all boards have "won"
         break;

      round++;
      // check each board against the called number, "caller".
      for (auto &board : g.boards) {
         if (board.won)
            // ignore boards that have already been finished.  we could remove
            // it from the boards vector, but it's awkward while we are
            // iterating.
            continue;

         // Accumulate the set of numbers called (needed to work out score later)
         called.set(caller);

         // if the board has this number, increment the row and column counters
         // for where it appears on this board.
         auto it = board.numbers.find(caller);
         if (it == board.numbers.end())
            continue;
         auto &num = it->second;
         board.rowCounts[num.row]++;
         board.colCounts[num.col]++;

         // If the updated row or column is now full, this is a winning board,
         // and this board no longer participates.
         if (board.rowCounts[num.row] == board.colCounts.size() ||
             board.colCounts[num.col] == board.rowCounts.size()) {

            // For the first and last board that wins, print the score.
            if (won == 0 || won == g.boards.size() - 1) {
               int total = 0;
               for (auto &num : board.numbers) {
                  if (!called.test(num.first))
                     total += num.first;
               }
               // Print first and last winning boards.
               std::cout << round << ": board " << &board - &g.boards[0]
                  << " has winning row/col.Score is " << total * caller << std::endl;
            }
            board.won = true;
            won++;
         }
      }
   }
}
