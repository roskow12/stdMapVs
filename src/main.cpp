#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <utility>
#include <deque>
#include <algorithm>
#include <fstream>
#include <chrono>

using std::cout;
using std::cin;
using namespace std::chrono;

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
  std::deque<NodePair> deq;

  auto insert(NodePair newObj) {    
    auto it = std::lower_bound(deq.begin(), deq.end(), newObj, 
      [](NodePair lhs, NodePair rhs) -> bool {return lhs.first < rhs.first;});
    
    if(it == deq.end() || newObj.first < (*it).first){ // element wasn't in map, insert it
      //cout << "inserting " << newObj.first << ", lower_bound == " << (*it).first << '\n';
      return std::make_pair(deq.insert(it, newObj), true);
    }
    else{ // element already exists
      //cout << "not inserting " << newObj.first << ", lower_bound == " << (*it).first << '\n';
      return std::make_pair(it, false);
    }
  }
};

struct sorted_vector {  
  std::vector<NodePair> v;

  auto insert(NodePair newObj) {    
    auto it = std::lower_bound(v.begin(), v.end(), newObj, 
      [](NodePair lhs, NodePair rhs) -> bool {return lhs.first < rhs.first;});
    
    if(it == v.end() || newObj.first < (*it).first){ // element wasn't in map, insert it
      return std::make_pair(v.insert(it, newObj), true);
    }
    else{ // element already exists
      return std::make_pair(it, false);
    }
  }
};

NodeObject::NodeObject() : x(0), y(0), z(0) {}
NodeObject::NodeObject(uint64_t x, uint64_t y, uint32_t z, bool bsVal) : x(x), y(y), z(z) {}

int main(){

  // std::map<uint32_t, NodeObject> ds;
  // std::unordered_map<uint32_t, NodeObject> ds;
  // deck ds;
  sorted_vector ds; ds.v.reserve(90000);

  std::ifstream ifs("input/input.txt");

  if(ifs.is_open())
    cout << "ifs open\n";
  else
    cout << "file not open\n";

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  int x;
  while(ifs >> x){
    ds.insert(NodePair(x, NodeObject()));
  }

  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  auto duration0 = duration_cast<microseconds>(t2-t1).count();
  cout << "insert duraton: " << duration0 << '\n';

  ifs.close();

  high_resolution_clock::time_point t3 = high_resolution_clock::now();

  // for(auto it = ds.begin(); it != ds.end(); ++it)
  for(auto it = ds.v.begin(); it != ds.v.end(); ++it)
    (*it).second.x += 100;

  high_resolution_clock::time_point t4 = high_resolution_clock::now();

  auto duration1 = duration_cast<microseconds>(t4-t3).count();
  cout << "iterate duraton: " << duration1 << '\n';

	return 0;
}