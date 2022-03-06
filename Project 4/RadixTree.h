#ifndef _RADIXTREE_H_
#define _RADIXTREE_H_
#include <map>
#include <string>
using namespace std;

template <typename ValueType>
class RadixTree {
public:
	RadixTree() {
		
	}
	~RadixTree() {
		
	}
	void insert(std::string key, const ValueType& value) {

		ValueType* t = new ValueType(value);
		fakeTree.insert(pair<string, ValueType*>(key, t));

	}
	ValueType* search(std::string key) const {
	    typename map<string, ValueType*> :: const_iterator it; 

		it = fakeTree.find(key);

		if (it == fakeTree.end()) {
			return nullptr;
		}

		else {
			return it->second;
		}

	}

private:
	map<string, ValueType*> fakeTree;

};



#endif

// struct Node {
// string s
// bool isEnd, 
// Node* arr[26]
// ValueType* value
// }  

