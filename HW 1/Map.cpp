#include "Map.h"
#include <iostream>
using namespace std;


Map::Map() {
	m_size = 0;
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
	if (m_size >= DEFAULT_MAX_ITEMS) {
		return false;
	}

	// if key already exists in map, return false		
	for (int i = 0; i < m_size; i++) {
		if (m_map[i].key == key) {
			return false;
		}
	}

	//add key/value pair to the map						
	m_size++;
	m_map[m_size-1].key = key;
	m_map[m_size - 1].value = value;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {

	// if key is already equal to a key on the map, change the value for that key to the new value
	for (int i = 0; i < m_size; i++) {
		if (m_map[i].key == key) {
			m_map[i].value = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {

	// if key is already equal to a key on the map, change the value for that key to the new value
	for (int i = 0; i < m_size; i++) {
		if (m_map[i].key == key) {
			m_map[i].value = value;
			return true;
		}
	}

	// if map is full, return false
	if (m_size >= DEFAULT_MAX_ITEMS) {
		return false;
	}

	//add key/value pair to the map						
	m_size++;
	m_map[m_size - 1].key = key;
	m_map[m_size - 1].value = value;
	return true;
}

bool Map::erase(const KeyType& key) {
	
	for (int i = 0; i < m_size; i++) {
		if (m_map[i].key == key) {
			for (int j = i; j < m_size; j++) {
				m_map[j] = m_map[j + 1];				
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
		if (m_map[i].key == key) {
			return true;
		}
	}

	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
	for (int i = 0; i < m_size; i++) {
		if (m_map[i].key == key) {
			value = m_map[i].value;						
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
				if (m_map[j].key > m_map[k].key) {
					count++;
				}
			}
			if (count == i) {
				key = m_map[j].key;
				value = m_map[j].value;
				return true;
			}
		}

		return false;
	}
	return false;
}

void Map::swap(Map& other) {
							
		Map tempMap;

		// swap content in arrays
		for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
			tempMap.m_map[i] = m_map[i];
		}

		// swap size with temp map
		tempMap.m_size = m_size;
		
		for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
			m_map[i] = other.m_map[i];
		}
		m_size = other.m_size;

		for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
			other.m_map[i] = tempMap.m_map[i];
		}
		other.m_size = tempMap.m_size;
}


void Map::dump() const {									
	for (int i = 0; i < m_size; i++) {
		cerr << m_map[i].key << "   " << m_map[i].value << endl;
	}
}