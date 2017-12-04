#include<iostream>
#include "AGP.h"
//MAT member functions definitions includind constructor
MAT::MAT(int rows, int columns) {
  affineMatrix = new int *[rows];
  for (int k=0; k<rows; k++) {
    affineMatrix[k] = new int[columns];
  }
}
void MAT::printMatrix() {
  cout<<"hai";
  cout<<*affineMatrix;
}
//AGP member functions definitions includind constructor
AGP::AGP(int gap_open, int gap_extend, int match, int mismatch, string s1, string s2) {
	_gap_open = gap_open;
	_gap_extend = gap_extend;
	_match = match;
	_mismatch = mismatch;
  _s1 = s1;
  _s2 = s2;
  _M = new MAT(_s1.length(), _s2.length());
  _I = new MAT(_s1.length(), _s2.length());
  _Y = new MAT(_s1.length(), _s2.length());
}

int AGP::getParameter(char param) {
	int result;
	switch(param) {
		case 'o':
		 	result = _gap_open;
			break;
		case 'e':
			result = _gap_extend;
			break;
		case 'm':
			result = _match;
			break;
		case 'i':
			result = _mismatch;
			break;
	}
	return result;
}

void AGP::printMatrix() {
  _M->printMatrix();
  cout<<"hello"<<endl;
}
