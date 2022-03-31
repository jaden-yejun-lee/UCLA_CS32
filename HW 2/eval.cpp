#include <stack>
#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
#include "Map.h"
using namespace std;


bool validInfix(string initial);
void deleteSpaces(string& s);
void infixToPostfix(string infix, string& postfix);
bool checkMap(string infix, const Map& values);
bool precedence(char x, char y);


// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.
int evaluate(string infix, const Map& values, string& postfix, int& result) {



	// delete spaces in infix
	deleteSpaces(infix);


		// If infix is a syntactically valid infix integer expression whose
		//   only operands are single lower case letters (whether or not they
		//   appear in the values map), then postfix is set to the postfix
		//   form of the expression; otherwise postfix may or may not be
		//   changed, result is unchanged, and the function returns 1. 
	if (!validInfix(infix)) {
		return 1;
	}

		// set postfix to the postfix form of expression
	infixToPostfix(infix, postfix);

	
		//   If infix is syntactically valid but contains at least one lower
		//   case letter operand that does not appear in the values map, then
		//   result is unchanged and the function returns 2.
	
	if (!checkMap(infix, values)) {
		return 2;
		}


		//	If infix is
		//   syntactically valid and all its lower case operand letters
		//   appear in the values map, then if evaluating the expression
		//   (using for each letter in the expression the value in the map
		//   that corresponds to it) attempts to divide by zero, then result
		//   is unchanged and the function returns 3


	// if evaluating the expression attempts to divide by zero then return 3
		
	stack <int> operandStack;
	for (int i = 0; i != postfix.size(); i++) {
	
		char ch = postfix[i];
		if (islower(ch)) {
			int p;
			values.get(ch, p);
			operandStack.push(p);
		}
		// ch is a binary operator
		else {
		
			int operand2 = operandStack.top();
			operandStack.pop();
			int operand1 = operandStack.top();
			operandStack.pop();

			switch (ch) {
			case ('+'): 
				operandStack.push(operand1 + operand2);
				break;
			case ('-'): 
				operandStack.push(operand1 - operand2);
				break;
			case('*'): 
				operandStack.push(operand1 * operand2);
				break;
			case('/'): 
				if (operand2 == 0) {
					return 3;
				}
				else {
					operandStack.push(operand1 / operand2);
					break;
				}
			}

		}
	}

	result = operandStack.top();
	return 0;
}



// delete spaces in string
void deleteSpaces(string& s) {

	string p;
	for (int i = 0; i != s.size(); i++) {
		if (s[i] != ' ') {
			p += s[i];
		}
	}
	s = p;
}

bool checkMap(string infix, const Map& values) {

	for (int i = 0; i != infix.size(); i++) {
		char ch = infix[i];
		// if ch does not appear in values map
		if (islower(ch) && !values.contains(ch)) {
			return false;
		}
	}

	return true;
}


// return true if x is less than y
bool precedence(char x, char y) {
	if (x == '+' || x == '-') {
		return true;
	}
	return false;
}

// convert infix expression to postfix expression
void infixToPostfix(string infix, string& postfix) {
	postfix = "";
	stack <char> stackOfChars;
	
	for (int i = 0; i != infix.size(); i++) {
		// do smth
		char ch = infix[i];
		switch (ch) {
			// case operand
		case ('a'):
		case ('b'): 
		case ('c'):
		case ('d'):
		case ('e'):
		case ('f'):
		case ('g'):
		case ('h'):
		case ('i'):
		case ('j'):
		case ('k'):
		case ('l'):
		case ('m'):
		case ('n'):
		case ('o'):
		case ('p'):
		case ('q'):
		case ('r'):
		case ('s'):
		case ('t'):
		case ('u'):
		case ('v'):
		case ('w'):
		case ('x'):
		case ('y'):
		case ('z'):
			postfix += ch;
			break;

		case ('('): 
			stackOfChars.push(ch);
			break;

		case (')'): 
			while (stackOfChars.top() != '(') {
				postfix += stackOfChars.top();
				stackOfChars.pop();
			}
			stackOfChars.pop();
			break;
			
		case ('+'):
		case ('-'):
		case ('*'):
		case ('/'):
			while (!stackOfChars.empty() && stackOfChars.top() != '(' && precedence(ch, stackOfChars.top())) {

				postfix += stackOfChars.top();
				stackOfChars.pop();

			}
			stackOfChars.push(ch);
			break;

		}
	}

	while (!stackOfChars.empty()) {
		postfix += stackOfChars.top();
		stackOfChars.pop();
	}


}


// return true if infix is syntactically valid
bool validInfix(string infix) {


	if (infix == "") {
		return false;
	}

	int closedPar = 0;
	int openPar = 0;

	for (int i = 0; i != infix.size(); i++) {

		char c = infix[i];

		// if c is not a lowercase letter or an operator return false
		if (!islower(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')') {
			return false;
		}

		// if c is a lower case letter
		if (islower(c)) {

			char prev = '@';

			// if looking past first letter, look at previous character
			if (i > 0) {
				prev = infix[i - 1];
			}
			// if previous character is also a letter, return false
			if (islower(prev)) {
				return false;
			}
		}

		// if c is a operator, return false if the previous character is also an operator
		if (c == '+' || c == '-' || c == '*' || c == '/') {
			char prev = '@';
			char next = '#';

			if (i > 0) {
				prev = infix[i - 1];
			}

			if (prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '(') {
				return false;
			}

			// check next character
			if (i != infix.size() + 1) {
				next = infix[i + 1];
			}

			if (next == '+' || next == '-' || next == '*' || next == '/' || next == ')') {
				return false;
			}

			if (infix[infix.size() - 1] == '+' || infix[infix.size() - 1] == '-' || infix[infix.size() - 1] == '*' || infix[infix.size() - 1] == '/') {
				return false;
			}

			// if prev and next are not
			// prev and next need to be letters or parentheses

			if ((!islower(prev) && prev != '(' && prev != ')') || (!islower(next) && next != '(' and next != ')')) {
					return false;
			}

		}

		// if c is an open parentheses
		if (c == '(') {
			openPar++;
			char prev = '@';

			if (i > 0) {
				prev = infix[i - 1];
			}

			if (islower(prev)) {
				return false;
			}
		}

		// if c is closed parentheses
		if (c == ')') {
			closedPar++;
			char prev = '@';

			if (i > 0) {
				prev = infix[i - 1];
			}

			if (prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '(') {
				return false;
			}
		}

		
	}

	if (closedPar != openPar) {
		return false;
	}

	return true;
}

int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+" && answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*" && answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+" && answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/" && answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a" && answer == 3);


	
	cout << "Passed all tests" << endl;
}