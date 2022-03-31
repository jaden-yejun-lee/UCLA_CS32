#include <iostream>
#include "History.h"
#include "Mesa.h"
#include "globals.h"

using namespace std;



History::History(int nRows, int nCols) {

	m_rows = nRows;
	m_cols = nCols;

	for (int i = 0; i != m_rows; i++) {
		for (int j = 0; j != m_cols; j++) {
			m_mesa[i][j] = 0;
		}
	}
}

bool History::record(int r, int c) {

	if (r < 1 || r > m_rows || c < 1 || c > m_cols) {
		return false;
	}
	else {
		m_mesa[r - 1][c - 1]++;
		return true;
	}
}

void History::display() const {
	clearScreen();

	for (int i = 0; i != m_rows; i++) {
		for (int j = 0; j != m_cols; j++) {
			if (m_mesa[i][j] == 0) {

				cout << '.';
			}

			else if (m_mesa[i][j] >= 1 && m_mesa[i][j] <= 25) {
				char c = ('A' - 1) + m_mesa[i][j];
				cout << c;
			}

			else {
				cout << 'Z';
			}
		}
		cout << endl;
	}
	cout << endl;
}