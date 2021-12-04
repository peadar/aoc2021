#include <bitset>
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
      bool rc = splitNumbers(is, [this, row, &col](size_t value) {
         numbers[value] = {row, col};
         ++col;
      });
      maxcol = std::max(col, maxcol);
      if (!rc)
         break;
   }
   rowCounts.resize(row);
   colCounts.resize(maxcol);
}

int
main()
{
   Game g(std::cin);

   std::bitset<100> called;
   bool won = false;
   for (auto caller : g.calledNumbers) {
      if (won)
         break;
      for (auto &board : g.boards) {
         called.set(caller);
         auto it = board.numbers.find(caller);
         if (it == board.numbers.end())
            continue;
         auto &num = it->second;
         board.rowCounts[num.row]++;
         board.colCounts[num.col]++;
         if (board.rowCounts[num.row] == board.colCounts.size() || board.colCounts[num.col] == board.rowCounts.size()){
            int total = 0;
            for (auto &num : board.numbers) {
               if (!called.test(num.first))
                  total += num.first;
            }
            std::cout << "board " << &board - &g.boards[0] << "  has winning row/col.Score is "
               << total * caller << std::endl;
            won = true;
            break;
         }
      }
   }
}
