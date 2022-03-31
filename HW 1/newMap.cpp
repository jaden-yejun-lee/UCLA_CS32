#include "newMap.h"
#include <iostream>
using namespace std;


Map::Map() {
	m_size = 0;
	m_max = DEFAULT_MAX_ITEMS;
	m_arr = new mapValue[m_max];
}

Map::Map(int size) {
	m_size = 0;
	m_max = size;
	m_arr = new mapValue[size];
}


Map::~Map() {
	delete[] m_arr;
}

Map::Map(const Map& copy) {
	m_size = copy.m_size;
	m_max = copy.m_max;
	m_arr = new mapValue[m_size];

	for (int i = 0; i < m_size; i++) {
		m_arr[i].key = copy.m_arr[i].key;
		m_arr[i].value = copy.m_arr[i].value;
	}
}

Map& Map::operator=(const Map& src) {

	if (&src == this) {
		return *this;
	}

	Map temp(src);
	swap(temp);
	return *this;
}

bool Map::empty() const {
	if (m_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

int Map::size() const {
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) {

	// if map is full, return false
	if (m_size >= m_max) {
		return false;
	}

	// if key already exists in map, return false		
	for (int i = 0; i < m_size; i++) {
		if (m_arr[i].key == key) {
			return false;
		}
	}

	//add key/value pair to the map						
	m_size++;
	m_arr[m_size - 1].key = key;
	m_arr[m_size - 1].value = value;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {

	// if key is already equal to a key on the map, change the value for that key to the new value
	for (int i = 0; i < m_size; i++) {
		if (m_arr[i].key == key) {
			m_arr[i].value = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {

	// if key is already equal to a key on the map, change the value for that key to the new value
	for (int i = 0; i < m_size; i++) {
		if (m_arr[i].key == key) {
			m_arr[i].value = value;
			return true;
		}
	}

	// if map is full, return false
	if (m_size >= m_max) {
		return false;
	}

	//add key/value pair to the map						
	m_size++;
	m_arr[m_size - 1].key = key;
	m_arr[m_size - 1].value = value;
	return true;
}

bool Map::erase(const KeyType& key) {

	for (int i = 0; i < m_size; i++) {
		if (m_arr[i].key == key) {
			for (int j = i; j < m_size; j++) {
				m_arr[j] = m_arr[j + 1];
			}
			m_size--;
			return true;
		}
	}

	return false;
}

bool Map::contains(const KeyType& key) const {
	// if key equals a key currently in map, return true
	for (int i = 0; i < m_size; i++) {
		if (m_arr[i].key == key) {
			return true;
		}
	}

	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
	for (int i = 0; i < m_size; i++) {
		if (m_arr[i].key == key) {
			value = m_arr[i].value;
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {



	if (i >= 0 && i < m_size) {
		for (int j = 0; j < m_size; j++) {
			int count = 0;
			for (int k = 0; k < m_size; k++) {
				//chekc if bigger
				if (m_arr[j].key > m_arr[k].key) {
					count++;
				}
			}
			if (count == i) {
				key = m_arr[j].key;
				value = m_arr[j].value;
				return true;
			}
		}

		return false;
	}
	return false;
}

void Map::swap(Map& other) {

	// swapping arrays
	mapValue* temp = m_arr;
	m_arr = other.m_arr;
	other.m_arr = temp;

	//swap size
	int tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;

	// swap max
	int tempMax = m_max;
	m_max = other.m_max;
	other.m_max = tempMax;
}


void Map::dump() const {
	for (int i = 0; i < m_size; i++) {
		cerr << m_arr[i].key << "   " << m_arr[i].value << endl;
	}
}