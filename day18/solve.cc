#include "sn.h"
using namespace std;

int main(int argc, char *argv[]) {
   vector<SnailNum> nums;

   copy(istream_iterator<SnailNum>(cin),istream_iterator<SnailNum>(),back_inserter(nums));

   SnailNum total = nums[0];
   for (size_t i = 1; i < nums.size(); ++i)
      total = total + nums[i];
   cout << "part 1: magnitude: " << total.magnitude() << "\n";

   long best = 0;
   for (size_t i = 0; i < nums.size() - 1; ++i)
      for (size_t j = i + 1; j < nums.size(); ++j)
         best = max(best, (nums[i] + nums[j]).magnitude());
   cout << "part 2: best: " << best << "\n";
}
