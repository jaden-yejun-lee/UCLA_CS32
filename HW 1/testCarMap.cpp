#include "CarMap.h"
#include <iostream>

using namespace std;

int main() {
	
	CarMap c;
	c.addCar("a");
	c.addCar("b");
	c.addCar("c");
	c.addCar("d");
	c.addCar("e");
	c.addCar("a");

	c.drive("a", 10);
	c.drive("b", 10);
	c.drive("b", 10);
	c.drive("c", 10);
	c.drive("c", 10);
	c.drive("c", 10);
	c.drive("d", 10);
	c.drive("d", 10);
	c.drive("d", 10);
	c.drive("d", 10);
	c.drive("e", 10);
	c.drive("e", 10);
	c.drive("e", 10);
	c.drive("e", 10);
	c.drive("e", 10);

	c.miles("a");
	c.miles("b");
	c.miles("c");
	c.miles("d");
	c.miles("e");

	c.fleetSize();

	c.print();
}