#include "PersonProfile.h"
#include <iostream>
PersonProfile::PersonProfile(string name, string email) {
	m_name = name;
	m_email = email;

}

string PersonProfile::GetName() const{
	return m_name;
}

string PersonProfile::GetEmail() const {
	return m_email;
}



void PersonProfile::AddAttValPair(const AttValPair& attval) {

	vector<string>* val = m_tree.search(attval.attribute);

	// if attribute is not there, create new attribute
	if (val == nullptr) {
		vector<string> tempValue;
		tempValue.push_back(attval.value);
		m_tree.insert(attval.attribute, tempValue);
		m_personVector.push_back(attval);
	}

	else {
		bool isDuplicate = false;
		auto it = val->begin();
		while (it != val->end()) {
			if (attval.value == (*it)) {
				isDuplicate = true;
			}
			it++;
		}

		if (isDuplicate == false) {
			val->push_back(attval.value);
			m_tree.insert(attval.attribute, *val);
			m_personVector.push_back(attval);
		}

	}
	


}

int PersonProfile::GetNumAttValPairs() const {
	// assuming that vector can distinguish between the same attribute-value pairs
	cerr << "Number of AttValPairs: " << m_personVector.size() << endl << endl;
	return m_personVector.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
	
	int x = m_personVector.size();
	if (attribute_num < 0 || attribute_num >= x) {
		return false;
	}

	vector<string>* end = m_tree.search(m_personVector[attribute_num].attribute);
	for (int i = 0; i < (*end).size(); i++) {
		if ((*end)[i] == m_personVector[attribute_num].value) {
			attval.attribute = m_personVector[attribute_num].attribute;
			attval.value = (*end)[i];
			cerr << "GetAttVal: Attribute = " << m_personVector[attribute_num].attribute << endl;
			cerr << "GetAttVal: Value = " << m_personVector[attribute_num].value << endl << endl;
			return true;
		}
	}

	return false;

}

PersonProfile::~PersonProfile() {
	for (int i = 0; i < m_personVector.size(); i++) {
		cerr <<  m_personVector[i].attribute << endl;
		cerr << m_personVector[i].value << endl << endl;

	}
}

// create a radixtree which maps the attributes to a vector of values
// create a vector with elements inside vector being radix tree attribute-value pairs
// if i need to return size i just have to return vector size
// and if i need to return the actual attVal pair, I can just use index to find element in vector
