#include "sn.h"
#include <cassert>
using namespace std;

struct SnailNum::ExplodeState {
   int *leftInt; // last int we saw before finding an explodey pair
   int rightInt; // RHS of the explodey pair.
   bool sawExplodingPair;
   bool done;
   void gotInt(int &val) {
      if (done)
         return;
      if (sawExplodingPair) {
         val += rightInt;
         done = true;
      } else {
         leftInt = &val;
      }
   }
   void explodePair(SnailNum &n) {
      if (leftInt != nullptr)
         *leftInt += get<int>(n.children[0]);
      rightInt = get<int>(n.children[1]);
      sawExplodingPair = true;
   }
};

// Print a pointer-to-snailnum as if it were a snailnum
ostream & operator << (ostream &os, const unique_ptr<SnailNum> &n) {
   return os << *n;
}

// For a branch, just visit whatever setting is there, and output that.
ostream & operator << (ostream &os, const SnailNum::Branch &n) {
   visit([&os] (const auto &v) { os << v; },  n);
   return os;
}

// Output a snailnum as a bracketed pair.
ostream & operator << (ostream &os, const SnailNum &n) {
   return os << "[" << n.children[0] << "," << n.children[1] << "]";
}

// Stream input a SnailNum - try and parse, and if we fail, set failbit.
// Otherwise, "reduce" it.
istream & operator >> (istream &is, SnailNum &n) {
   if (!n.parse(is))
      is.setstate(ios::failbit);
   else
      n.reduce();
   return is;
}

// Parse one half inside the brackets of a snailnum
void SnailNum::parseBranch(istream &in, SnailNum::Branch &b) {
   while (isspace(in.peek()))
      in.get();
   if (isdigit(in.peek())) {
      int val = 0;
      while (isdigit(in.peek()))
         val = val * 10 + in.get() - '0';
      b = val;
   } else {
      auto subnum = make_unique<SnailNum>();
      subnum->parse(in);
      b = move(subnum);
   }
}

// Parse a snailnum from an istream. Returns true if successful.
bool SnailNum::parse(istream &in) {
   while (isspace(in.peek()))
      in.get();
   if (in.get() != '[')
      return false;
   parseBranch(in, children[0]);
   while (in.peek() == ' ' || in.peek() == ',')
      in.get();
   parseBranch(in, children[1]);
   while (isspace(in.peek()))
      in.get();
   if (in.get() != ']')
      throw 999;
   return true;
}

// Test what type of object is in a branch.
bool isSnailBranch(const SnailNum::Branch &b) {
   bool result;
   visit([&result](const auto &v) { result = (is_same_v<decltype(v) &, const SnailNum::ChildPtr &>); }, b);
   return result;
};

bool isIntBranch(const SnailNum::Branch &b) {
   return !isSnailBranch(b);
}

void
copybranch(SnailNum::Branch &lhs, const SnailNum::Branch &rhs) {
   if (isSnailBranch(rhs))
      lhs = make_unique<SnailNum>(*get<unique_ptr<SnailNum>>(rhs));
   else
      lhs = get<int>(rhs);
}

void SnailNum::copybranches(const SnailNum &orig) {
   for (int i = 0; i < 2; ++i)
      copybranch(children[i], orig.children[i]);
}

SnailNum::SnailNum(const SnailNum &orig) {
   copybranches(orig);
}

SnailNum::SnailNum(const Branch &otherL, const Branch &otherR) {
   copybranch(children[0], otherL);
   copybranch(children[1], otherR);
}

SnailNum &SnailNum::operator = (const SnailNum &rhs) {
   copybranches(rhs);
   return *this;
}

SnailNum SnailNum::operator +(const SnailNum &orig) const {
   auto sn = SnailNum(Branch(make_unique<SnailNum>(*this)), Branch(make_unique<SnailNum>(orig)));
   sn.reduce();
   return sn;
}

void SnailNum::reduce() {
   while (explode() || split())
      ;
}

bool SnailNum::explode() {
   ExplodeState state{};
   explode(state, 0);
   return state.sawExplodingPair;
}

// return value indicates if parent should replace branch with "0"
bool SnailNum::explode(ExplodeState &state, int depth) {
   if (state.done)
      return false;
   if (depth == 4 && !state.sawExplodingPair) {
      assert(all_of(children, children + 2, isIntBranch));
      state.explodePair(*this);
      return true;
   }
   for (auto &branch : children)
      if (isIntBranch(branch))
         state.gotInt(get<int>(branch));
      else if (get<unique_ptr<SnailNum>>(branch)->explode(state, depth+1))
         branch = int(0); // child exploded - replace child with 0.
   return false;
}

long branchMagnitude(const SnailNum::Branch &b) {
   return isIntBranch(b) ?  get<int>(b) : get<SnailNum::ChildPtr>(b)->magnitude();
}

long SnailNum::magnitude() {
   return 3 * branchMagnitude(children[0]) + 2 * branchMagnitude(children[1]);
}

bool SnailNum::split() {
   for (auto &branch : children)
      if (isIntBranch(branch)) {
         int i = get<int>(branch);
         if (i >= 10) {
            branch = make_unique<SnailNum>(i/2, (i+1)/2);
            return true;
         }
      } else if (get<unique_ptr<SnailNum>>(branch)->split())
         return true;
   return false;
}
