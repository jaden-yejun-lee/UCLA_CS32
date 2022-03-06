#include "PersonProfile.h"
#include "RadixTree.h"
#include "AttributeTranslator.h"
#include "MatchMaker.h"
#include "MemberDataBase.h"

#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

AttributeTranslator::AttributeTranslator() {

}

AttributeTranslator::~AttributeTranslator() {

}

bool AttributeTranslator::Load(string filename) {
	ifstream file;
	file.open(filename);

	if (file) {
		string curLine;
		string pair;
		string sourceAttribute;
		string sourceValue;
		string compatibleAttribute;
		string compatibleValue;
		string sourcePair;
		while (getline(file, curLine)) {
			stringstream ss(curLine);
			getline(ss, sourceAttribute, ',');
			getline(ss, sourceValue, ',');
			getline(ss, compatibleAttribute, ',');
			getline(ss, compatibleValue, '\n');
			sourcePair = sourceAttribute + "," + sourceValue;
			AttValPair compatible(compatibleAttribute, compatibleValue);

			auto itr = compatiblePairs.search(sourcePair);

			if (itr == nullptr) {
				vector <AttValPair> temp;
				temp.push_back(compatible);
				compatiblePairs.insert(sourcePair, temp);
				cerr << sourcePair << ": " << compatibleAttribute << ", " << compatibleValue << endl;
			}
			else {
				itr->push_back(compatible);
				cerr << sourcePair << ": " << compatibleAttribute << ", " << compatibleValue << endl;
			}

		}
		return true;
	}
	else {
		return false;
	}
		
	
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
	string pair = source.attribute + "," + source.value;


	vector <AttValPair>* test = compatiblePairs.search(pair);
	for (int i = 0; i < (*test).size(); i++) {

		cerr << (*compatiblePairs.search(pair))[i].attribute << ", " << (*compatiblePairs.search(pair))[i].value << endl;
	}

	return *compatiblePairs.search(pair);
}
