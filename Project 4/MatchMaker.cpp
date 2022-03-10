#include "MatchMaker.h"
#include "provided.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
	m_mdb = mdb;
	m_at = at;
}

MatchMaker::~MatchMaker() {

}


vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const {

	// retrieve person's PersonProfile from email 
	const PersonProfile* p = m_mdb.GetMemberByEmail(email);

	// obtain person's attribute-value pairs
	// push unique compatible attribute-value pairs into pairVectors
	vector<AttValPair> pairVectors;
	if (p != nullptr) {
		for (int i = 0; i < p->GetNumAttValPairs(); i++) {
			AttValPair pair;
			p->GetAttVal(i, pair);
			vector<AttValPair>tempVector = m_at.FindCompatibleAttValPairs(pair);
			for (int j = 0; j != tempVector.size(); j++) {
				auto itr = find(pairVectors.begin(), pairVectors.end(), tempVector[j]);
				if (itr == pairVectors.end()) {
					pairVectors.push_back(tempVector[j]);
				}
			}
		}
	}

	// NEED TO REWRITE THIS PART CUZ IT TAKES TOO LONG 
	// ITERATOR AND FOR LOOP NOT GOOD

	// iterate through compatible attributes and match attribute with
	// collection of members that have each compatible attribute-value pair
	auto it = pairVectors.begin();
	vector<EmailCount> emailCollection;
	while (it != pairVectors.end()) {

		AttValPair find(it->attribute, it->value);
		vector<string> matchingEmails = m_mdb.FindMatchingMembers(find);

		for (int i = 0; i != matchingEmails.size(); i++) {

			if (matchingEmails[i] == email) {
				continue;
			}

			bool duplicate = false;
			for (int j = 0; j != emailCollection.size(); j++) {
				if (matchingEmails[i] == emailCollection[j].email) {
					duplicate = true;
					emailCollection[j].count++;
				}
			}

			if (duplicate == false) {
				EmailCount tempEC(matchingEmails[i], 1);
				emailCollection.push_back(tempEC);
			}

		}

		it++;
	}


	// create a collection of members that have at least the 
	// threshold number of compatible attribute-value pairs

	// sort in descending order with ties broken by ascending alphabetical order
	 sort(emailCollection.begin(), emailCollection.end(), [](EmailCount x, EmailCount y) {
			 if (x.count == y.count) {
				 return x.email < y.email;
			 }
			 else {
				 return x.count > y.count;
			 }
		 });

	for (int i = 0; i != emailCollection.size(); i++) {
		// cerr << emailCollection[i].email << endl;
	}


	vector<EmailCount> v;

	for (int i = 0; i != emailCollection.size(); i++) {
		if (emailCollection[i].count >= threshold) {
			//insert
			v.push_back(emailCollection[i]);
		}
	}

	return v;


}

