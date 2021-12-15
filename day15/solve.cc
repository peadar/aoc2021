#include <cassert>
#include <list>
#include <iterator>
#include <stack>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;
struct Node {
   Node(int row_, int col_, unsigned cost_)
      : row(row_), col(col_), cost(cost_),prev(),distance(numeric_limits<unsigned>::max()) {}
   int row, col; // Using an array rather than vector-of-vector-of-unsigned would obviate the need to keep these.
   unsigned cost; // of this node.
   Node *prev; // in path to starting point.
   unsigned distance; // to destination of dijkstra subject
};
// dumb priority queue - we just bucket all nodes by their cost.  If the cost
// changes, we have to move from one bucket to the other. Because we are always
// dealing with nodes in priority order, and there are few distinct cost
// values, we use very few buckets indeed.
//
class Priority {
   using Nodes = map<unsigned long, set<Node *>>;
   Nodes nodes;
   template<typename Node> void eraseFromBucket(Nodes::iterator it, Node node) {
      it->second.erase(node);
      if (it->second.empty())
         nodes.erase(it);
   }
public:
   void insert(Node *n) { nodes[n->distance].insert(n); }
   void remove(Node *n) { eraseFromBucket(nodes.find(n->distance), n); }
   Node *removeLowest() {
      auto lowest = nodes.begin();
      auto key = lowest->second.begin();
      auto rv = *key;
      eraseFromBucket(lowest, key);
      return rv;
   }
   void updateDistance(Node *n, unsigned distance) {
      remove(n);
      n->distance = distance;
      insert(n);
   }
   bool empty() { return nodes.empty(); }
};

void ppm(ostream &, const Node *, const vector<vector<Node>> &); // dump ppm file.
int main(int argc, char *argv[]) {
   int part = argc >= 2 ? strtol(argv[1], 0, 0) : 1;
   vector<string> input; // read entire input into string vector we can pass over.
   copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(input));
   int replicas = part == 1 ? 1 : 5; // number of times to replicate each row/col (part1 vs part2)
   // Build 2-d vector of nodes.
   vector<vector<Node>> nodes;
   for (int r = 0; r < replicas; ++r) {
      for (auto &tilerow : input) {
         nodes.push_back({});
         auto &row = nodes.back();
         for (int c = 0; c < replicas; ++c) {
            for (auto &chr : tilerow) {
               auto neuval = ((chr - '0') + ((r + c)));
               if (neuval > 9)
                  neuval -= 9;
               row.emplace_back(nodes.size() - 1, row.size(), neuval);
            }
         }
      }
   }
   // Nodes default distance is "infinity". Mark the first node as being distance
   // of zero from itself.
   nodes[0][0].distance = 0;
   // Build a priority queue of all the nodes.
   Priority Q;
   for (size_t i = 0; i < nodes.size(); ++i)
      for (size_t j = 0; j < nodes[0].size(); ++j)
         Q.insert(&nodes[i][j]);
   // Dijkstra's algorithm:
   // As long as there are nodes left in the priority queue, find the node with
   // the smallest distance to the starting point, and potentially downwardly
   // adjust the distances to all its neighbours if the route through this node
   // is better
   while (!Q.empty()) {
      Node *u = Q.removeLowest();
      static int adjs[][2] = { { -1, 0 }, { 1, 0 }, {0, -1}, {0,1 } };
      for (auto adjust :  adjs ) {
         int adjrow = u->row + adjust[0];
         int adjcol = u->col + adjust[1];
         if (adjrow >= int(nodes.size()) || adjrow < 0 || adjcol >= int(nodes[adjrow].size()) || adjcol < 0)
            continue;
         Node *v = &nodes[adjrow][adjcol];
         unsigned alt = u->distance + v->cost;
         if (v->distance > alt) {
            // our graph has the interesting property that once we see a node
            // and update it's priority from "infinite", we'll never update
            // it's priority again - I guess that's a consequence of all the
            // links into a given node having the same weight.
            assert(v->distance == numeric_limits<unsigned>::max());
            Q.updateDistance(v, alt);
            v->prev = u;
         }
      }
   }
   // Display answer as an integer result, or plot as a PPM.
   Node *endNode = &nodes[nodes.size()-1][nodes[0].size() - 1];
   if (argc == 3 && string("ppm") == argv[2])
      ppm(cout, endNode, nodes);
   else
      cout << "part " << part << ": " << endNode->distance << endl;
}
void ppm(ostream &os, const Node *end, const vector<vector<Node>> &nodes) {
   unsigned maxDist = 0;
   for (auto &row : nodes)
      for (auto &col : row)
         maxDist = max(col.distance, maxDist);
   set<const Node *> bestpath;
   for (const Node *n = end; n != &nodes[0][0]; n = n->prev)
      bestpath.insert(n);
   os << "P3 " << nodes[0].size() << " " << nodes.size() << " " << maxDist << "\n";
   for (auto &row : nodes) {
      for (auto &col : row) {
         if (bestpath.find(&col) != bestpath.end())
            os << col.distance << " " << col.distance << " " << col.distance << " ";
         else
            os << col.distance << " 0 0 ";
      }
      os << "\n";
   }
}
