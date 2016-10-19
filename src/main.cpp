#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>
#include <deque>
#include <algorithm>

using std::cout;

class NodeObject {
public:
  uint64_t x;
  uint64_t y;
  uint32_t z;

  NodeObject();
  NodeObject(uint64_t, uint64_t, uint32_t, bool);
};

typedef std::pair<uint32_t, NodeObject> NodePair;

struct deck {  
  std::deque<NodePair> ds;

  auto insert(NodePair newObj) {    
    auto it = std::lower_bound(ds.begin(), ds.end(), newObj, 
      [](NodePair lhs, NodePair rhs) -> bool {return lhs.first < rhs.first;});
    
    if(it == ds.end() || newObj.first < (*it).first){ // element wasn't in map, insert it
      //cout << "inserting " << newObj.first << ", lower_bound == " << (*it).first << '\n';
      return std::make_pair(ds.insert(it, newObj), true);
    }
    else{ // element already exists
      //cout << "not inserting " << newObj.first << ", lower_bound == " << (*it).first << '\n';
      return std::make_pair(it, false);
    }
  }
};

NodeObject::NodeObject() : x(0), y(0), z(0) {}
NodeObject::NodeObject(uint64_t x, uint64_t y, uint32_t z, bool bsVal) : x(x), y(y), z(z) {}

int main(){

  std::map<uint32_t, NodeObject> ds1;
  std::unordered_map<uint32_t, NodeObject> ds2;
  deck ds3;

  ds3.insert(NodePair(1, NodeObject()));
  ds3.insert(NodePair(45, NodeObject()));
  ds3.insert(NodePair(2, NodeObject()));
  ds3.insert(NodePair(66, NodeObject()));
  ds3.insert(NodePair(5, NodeObject()));
  ds3.insert(NodePair(345, NodeObject()));
  ds3.insert(NodePair(13, NodeObject()));
  ds3.insert(NodePair(51, NodeObject()));
  ds3.insert(NodePair(331, NodeObject()));
  ds3.insert(NodePair(45731, NodeObject()));
  ds3.insert(NodePair(75431, NodeObject()));
  ds3.insert(NodePair(13, NodeObject()));
  ds3.insert(NodePair(51, NodeObject()));
  ds3.insert(NodePair(21, NodeObject()));
  ds3.insert(NodePair(11, NodeObject()));
  ds3.insert(NodePair(61, NodeObject()));
  ds3.insert(NodePair(7, NodeObject()));

  for(auto it = ds3.ds.begin(); it != ds3.ds.end(); ++it)
    std::cout << (*it).first << " ";
  std::cout << '\n';
	return 0;
}