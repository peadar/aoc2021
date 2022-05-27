#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <string>
#include <variant>
#include <vector>

class SnailNum {
public:
   using ChildPtr = std::unique_ptr<SnailNum>;
   using Branch = std::variant<int, ChildPtr>;

   SnailNum() = default;

   SnailNum(const SnailNum &orig);
   SnailNum(const Branch &lhs, const Branch &rhs);

   void copybranches(const SnailNum &orig);

   SnailNum operator+ (const SnailNum &rhs) const;
   SnailNum &operator= (const SnailNum &rhs);

   long magnitude();
   bool parse(std::istream &in);

   bool explode();
   bool split();

private:
   struct ExplodeState;
   bool explode(ExplodeState &, int level);
   Branch children[2];
   void parseBranch(std::istream &, Branch &);
   void reduce();
   friend std::ostream & operator << (std::ostream &os, const SnailNum &n);
   friend std::istream & operator >> (std::istream &is, SnailNum &n);
};
