#include<iostream>
#include <algorithm>
#include "AGP.h"
//MAT member functions definitions includind constructor
MAT::MAT(int rows, int columns) {
  affineMatrix = new float *[rows];
  for (int k=0; k<rows; k++) {
    affineMatrix[k] = new float[columns];
  }
}

float ** MAT::returnAffineMat() {
   return affineMatrix;
}

void MAT::printMatrix(string s1, string s2) {

  cout<<affineMatrix[1][0]<<endl;
  cout<<string(4, ' ')<<"*"<<" ";
  for (int k=0; k<s2.length(); k++) {
    cout<<s1[k]<<" ";
  }
  cout<<endl;
  for (int i=0; i<=s1.length(); i++) {
    if (i==0) {
      cout<<string(1, ' ')<<"*"<<string(2, ' ');
    } else {
      cout<<string(1, ' ')<<s1[i-1]<<string(2, ' ');
    }
    for (int j=0; j<=s2.length(); j++) {
      cout<<affineMatrix[i][j]<<string(1, ' ');
    }
    cout<<endl;
  }


}

//AGP member functions definitions includind constructor
AGP::AGP(int gap_open, int gap_extend, int match, int mismatch, string s1, string s2) {
	_gap_open = gap_open;
	_gap_extend = gap_extend;
	_match = match;
	_mismatch = mismatch;
  _s1 = s1;
  _s2 = s2;
  _rows = _s1.length() + 1;
  _columns = _s2.length() + 1;
  _M = new MAT(_rows, _columns);
  _X = new MAT(_rows, _columns);
  _Y = new MAT(_rows, _columns);
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

void AGP::initializeMatrices() {
  float **M = _M->returnAffineMat();
  float **X = _X->returnAffineMat();
  float **Y = _Y->returnAffineMat();
  const float negInfinity = -1 * numeric_limits<float>::infinity();

  M[0][0] = 0;
  X[0][0] = _gap_open;
  Y[0][0] = _gap_open;

  for (int k=1; k<_rows; k++) {
    X[k][0] = _gap_open + (k*_gap_extend);
    Y[k][0] = negInfinity;
    M[k][0] = negInfinity;
  }
  for (int k=1; k<_columns; k++) {
    Y[0][k] = _gap_open + (k*_gap_extend);
    X[0][k] = negInfinity;
    M[0][k] = negInfinity;
  }
}

int AGP::matchChars(char a, char b) {
  int score;
  if (a == b) {
    score = _match;
  } else {
    score = _mismatch;
  }
  return score;
}

void AGP::fillMatrices() {
  float **M = _M->returnAffineMat();
  float **X = _X->returnAffineMat();
  float **Y = _Y->returnAffineMat();
  int opt = 0;
  int max_val;
  char opt_matrix;
  char mat;
  for (int i=1; i<_rows; i++) {
    for (int j=1; j<_columns; j++) {
      max_val = 0;
      mat = 'q';
      M[i][j] = matchChars(_s1[i-1], _s2[j-1]) + max (
                          max (
                            M[i-1][j-1],
                            X[i-1][j-1]
                          ),
                          Y[i-1][j-1]
                );
      X[i][j] = max(
                  max (
                    M[i-1][j] + _gap_open + _gap_extend,
                    X[i-1][j] + _gap_open + _gap_extend
                  ),
                  Y[i-1][j] + _gap_open + _gap_extend
                );
      Y[i][j] = max(
                  max (
                    M[i][j-1] + _gap_open + _gap_extend,
                    X[i][j-1] + _gap_open + _gap_extend
                  ),
                  Y[i][j-1] + _gap_open + _gap_extend
                );
      if (M[i][j] > X[i][j] && M[i][j] > Y[i][j]) {
        max_val = M[i][j];
        mat = 'm';
      } else if (X[i][j] > M[i][j] && X[i][j] > Y[i][j]) {
        max_val = X[i][j];
        mat = 'x';
      } else {
        max_val = Y[i][j];
        mat = 'y';
      }

      if (max_val > opt) {
        opt = max_val;
        opt_matrix = mat;
      }
    }
  }
  cout<<"opt:"<<opt<<endl;
  cout<<"mat:"<<opt_matrix<<endl;
}

void AGP::printMatrix() {
  _M->printMatrix(_s1, _s2);
  // _X->printMatrix();
  // _Y->printMatrix();
}
