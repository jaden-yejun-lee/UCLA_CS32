#include "Map.h"
#include <iostream>
using namespace std;

Map::Map() {
	// initialize empty set
	m_size = 0;
	head = nullptr;
	tail = nullptr;
}

Map::~Map() {
	Node* p;
	p = head;

	// iterate through linked list and destory nodes
	while (p != nullptr) {
		Node* n = p->next;
		delete p;
		p = n;
	}

	head = nullptr;
	tail = nullptr;
	m_size = 0;
}

Map::Map(const Map& copy) {													

	// if head node for copy is null, set this map to null
	if (copy.head == nullptr) {
		head = nullptr;
		tail = nullptr;
		m_size = 0;
		return;
	}

	// copies size
	m_size = copy.m_size;

	// allocate a new copy of linked list 

	// create a new head pointer
	head = new Node;
	head->previous = nullptr;
	head->m_map.key = copy.head->m_map.key;
	head->m_map.value = copy.head->m_map.value;

	Node* copyNode = copy.head;
	Node* otherNode = head;

	// copy over contents from original to new linked list
	while (copyNode->next != nullptr) {
		otherNode->m_map.key = copyNode->m_map.key;
		otherNode->m_map.value = copyNode->m_map.value;
		Node* n = new Node;
		otherNode->next = n;
		n->previous = otherNode;
		otherNode = n;
		copyNode = copyNode->next;
	}

	// after while loop last node is still uninitialized
	otherNode->m_map.key = copyNode->m_map.key;
	otherNode->m_map.value = copyNode->m_map.value;
	otherNode->next = nullptr;

	// set tail equal to last node
	tail = otherNode;

}

Map& Map::operator=(const Map& src) {

	if (&src == this) {
		return *this;
	}

	// create a new temp map with src
	Map temp(src);
	// swap temp with this
	swap(temp);
	return *this;
}

bool Map::empty() const {

	// if map is empty return true
	if (head == nullptr && tail == nullptr && m_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

int Map::size() const {
	// return number of nodes
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) {

	// if key already exists return false

	// iterate through linked list
	for (Node* q = head; q != nullptr; q = q->next) {
		//if key already exists in linked list return false
		if (q->m_map.key == key) {
			return false;
		}
	}

	// add key/value pair
	
	// if list is empty
	if (head == nullptr && m_size == 0) {
		// add Node
		Node* p = new Node;
		// set new node's m_map values, new head, tail, next, previous pointer
		p->m_map.key = key;
		p->m_map.value = value;
		p->next = head;
		head = p;
		tail = p;
		p->previous = nullptr;
	}

	// create new node at end of linked list
	else {
		// add Node and set new Node's m_map values, head, tail, next, and previous pointer
		Node* p = new Node;
		p->m_map.key = key;
		p->m_map.value = value;
		tail->next = p;
		p->next = nullptr;
		p->previous = tail;
		tail = p;
	}

	// increment size
	m_size++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
	for (Node* p = head; p != nullptr; p = p->next) {

		// if key already exists
		if (p->m_map.key == key) {
			// change the value for that key to the value in the parameter
			p->m_map.value = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {

	// if key already exists in linked list, change the value for that key to the value in the parameter
	for (Node* q = head; q != nullptr; q = q->next) {
		if (q->m_map.key == key) {
			q->m_map.value = value;
			return true;
		}
	}

	// add key/value pair
	
	// if list is empty
	if (head == nullptr && m_size == 0) {
		// create new Node and set new node's m_map values, new head, tail, next, previous pointer
		Node* p = new Node;
		p->m_map.key = key;
		p->m_map.value = value;  
		p->next = head;
		head = p;
		tail = p;
		p->previous = nullptr;
	}

	// create new node at end of linked list
	else {
		// create new Node and set new node's m_map values, new head, tail, next, previous pointer
		Node* p = new Node;
		p->m_map.key = key;
		p->m_map.value = value;
		tail->next = p;
		p->next = nullptr;
		p->previous = tail;
		tail = p;
	}

	// increment size
	m_size++;
	return true;
	
}

bool Map::erase(const KeyType& key) {

	// if key already exists in linked list, remove the key/value pair and return true

	for (Node* p = head; p != nullptr; p = p->next) {
		// if key already exists
		if (p->m_map.key == key) {

			// if item we want to delete is the first node
			if (p == head) {
				Node* kill = head;
				Node* destroy = head;
				head = kill->next;
				destroy->previous = nullptr;
				destroy = nullptr;
				delete kill;
				kill = nullptr;
				m_size--;
				return true;
			}
			// else item we want to delete is in the middle or last node
			else {

				// points to node above node we want to delete
				Node* kill = head;
				while (kill != nullptr) {
					if (kill->next != nullptr && kill->next->m_map.key == key) {
						break;	
					}

					kill = kill->next;
				}

				// if node we want to delete is last node
				if (kill->next->next == nullptr && kill != nullptr) {
					// delete last node and update tail and node pointers
					Node* killMe = kill->next;
					kill->next = killMe->next;
					delete killMe;
					killMe = nullptr;
					tail = kill;
					m_size--;
					return true;
				}

				// else node we want to delete is in the middle of linked list
				else {
					if (kill != nullptr) {
						// delete node and update node pointers
						Node* killMe = kill->next;
						kill->next = killMe->next;
						delete killMe;
						killMe = nullptr;
						kill->next->previous = kill;
						m_size--;
						return true;
					}
	
				}


			}

		}
	}

	return false;
}

bool Map::contains(const KeyType& key) const {
	// iterate through linked list
	for (Node* p = head; p != nullptr; p = p->next) {
		//if key already exists in linked list return true
		if (p->m_map.key == key) {
			return true;
		}
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {


	// iterate through linked list
	for (Node* p = head; p != nullptr; p = p->next) {
		//if key already exists in linked list
		if (p->m_map.key == key) {
			// set value to the value in the map which that key maps to
			value = p->m_map.value;
			return true;

		}
	}

	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {

	// iterate through linked list
	if (i >= 0 && i < m_size) {
		for (Node* p = head; p != nullptr; p = p->next) {
			int count = 0;
			for (Node* q = head; q != nullptr; q = q->next) {
				// if p node is greater than q node increment count
				if (p->m_map.key > q->m_map.key) {
					count++;
				}
				
			}

			// if i is equal to count
			if (i == count) {
				// copy key/value pair into the parameters
				key = p->m_map.key;
				value = p->m_map.value;
				return true;
			}
		}
	}

	return false;
}

void Map::swap(Map& other) {
	//swap head
	Node* tempHead = head;
	head = other.head;
	other.head = tempHead;

	//swap tail
	Node* tempTail = tail;
	tail = other.tail;
	other.tail = tempTail;

	//swap size
	int temp = m_size;
	m_size = other.m_size;
	other.m_size = temp;

}

bool merge(const Map& m1, const Map& m2, Map& result) {

	// if m1 is empty, result is just m2
	if (m1.empty()) {
		result = m2;
		return true;
	}

	// if m2 is empty, result is just m1
	if (m2.empty()) {
		result = m1;
		return true;
	}

	// copy m1 into result  
	result = m1;

	KeyType key;
	ValueType value;
	ValueType valueTwo;
	bool noDuplicate = true;

	// iterate through m2 and copy m2 into result accordingly
	for (int i = 0; i < m2.size(); i++) {

		m2.get(i, key, value);

		// if key is not already in result, add key/value pair into result
		if (!result.contains(key)) {
			// add key/value pair into result
			result.insert(key, value);
		}

		// else key already exists in result
		else {

			// get value already present in result
			result.get(key, valueTwo);
		
			// if value equals value in key/value pair in map
			if (value == valueTwo) {
				// do nothing since result already has that key/value pair
				continue;
			}

			// else value has a different value than the one in result
			else {
				// erase that key/value type altogether and return false
				result.erase(key);
				noDuplicate = false;
				
			}
		}
	}

	return noDuplicate;
}


void reassign(const Map& m, Map& result) {

	// if m has only one pair, result copies that one pair from m

	// copy m into result
	result = m;

	// if m is just one pair, exit
	if (m.size() == 1) {
		return;
	}

	KeyType key;
	ValueType value;


	// iterate through m and put alphabetized order into result
	for (int i = 0; i < m.size(); i++) {

		// result becomes an alphabetized m
		m.get(i, key, value);
		result.insert(key, value);
	}

	KeyType k;
	ValueType v;

	KeyType kNext;
	ValueType vNext;

	ValueType temp = 0;
	ValueType tempSecond = 0;

	KeyType initial;
	ValueType initialV;

	// initial and initialV point to original head node
	result.get(0, initial, initialV);

	// increment through each pair in result
	for (int j = 0; j < result.size(); j++) {
		// if pair is at front
		if (j == 0) {
			// shift head node's value to the next node's value
			result.get(j, k, v);
			result.get(j + 1, kNext, vNext);
			temp = vNext;
			result.update(kNext, v);
		}
		// if pair is in middle
		else if (j > 0 && j < result.size() - 1) {
			// shift current node's value to the next node's value
			result.get(j, k, v);
			result.get(j + 1, kNext, vNext);
			tempSecond = vNext;
			result.update(kNext, temp);
			temp = tempSecond;
		}

		// if pair is at end
		else {
			// update head node's value with the last pair's value
			result.update(initial, temp);
		}
	}
}
