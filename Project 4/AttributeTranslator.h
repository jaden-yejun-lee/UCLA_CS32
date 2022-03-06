#ifndef _ATTRIBUTETRANSLATOR_H
#define _ATTRIBUTETRANSLATOR_H
#include <iostream>
#include <string>
#include <vector>
#include "PersonProfile.h"
#include "RadixTree.h"


using namespace std;


class AttributeTranslator {
public:
	AttributeTranslator();
	~AttributeTranslator();
	bool Load(string filename);
	vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

private:
	RadixTree<vector<AttValPair>> compatiblePairs;
};

#endif
