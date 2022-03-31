#include "CarMap.h"
#include <iostream>
using namespace std;

CarMap::CarMap() {
	m_car = 0;
}

bool CarMap::addCar(KeyType license) {
	// if there is room
	if (m_carMap.size() < DEFAULT_MAX_ITEMS) {
		// if license does not exist in carMap
		if (!m_carMap.contains(license)) {
			//insert licenseplate with 0 miles
			m_carMap.insert(license, 0);
			m_car++;
			return true;
		}
	}

	return false;
}

double CarMap::miles(KeyType license) const {

	// if carmap contains a car already with the same license plate
	if (m_carMap.contains(license)) {
		ValueType value;
		// return miles it has driven
		m_carMap.get(license, value);
		return value;
	}

	return -1;
}


bool CarMap::drive(KeyType license, ValueType distance) {
	//if distance is negative or if no car with the given license plate is in the map
	if (distance < 0 || !m_carMap.contains(license)) {
		return false;
	}



	//ValueType value = 0;
	//value += distance;
	//m_carMap.update(license, value);


	ValueType value = 0;

	ValueType y;
	m_carMap.get(license, y);
	value = y + distance;
	m_carMap.update(license, value);

	return true;
}


int CarMap::fleetSize() const {
	return m_car;
}

void CarMap::print() const {

	for (int i = 0; i < m_car; i++) {
		KeyType license;
		ValueType value;
		m_carMap.get(i, license, value);
		cout << license << " " << value << endl;
	}
}
