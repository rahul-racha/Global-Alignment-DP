#include<iostream>
#include <algorithm>
#include <math.h>
#include "AGP.h"
//MAT member functions definitions includind constructor
MAT::MAT(int rows, int columns) {
  affineMatrix = new float *[rows];
  for (int k=0; k<rows; k++) {
    affineMatrix[k] = new float[columns];
  }
  pointerMatrix = new char *[rows];
  for (int k=0; k<rows; k++) {
    pointerMatrix[k] = new char[columns];
  }
}

float ** MAT::returnAffineMat() {
   return affineMatrix;
}

char ** MAT::returnPointerMat() {
   return pointerMatrix;
}

void MAT::printMatrix(string s1, string s2) {

  cout<<affineMatrix[1][0]<<endl;
  cout<<string(4, ' ')<<"*"<<string(6, ' ');
  for (int k=0; k<s2.length(); k++) {
    cout<<s1[k]<<string(6, ' ');
  }
  cout<<endl;
  for (int i=0; i<=s1.length(); i++) {
    if (i==0) {
      cout<<string(1, ' ')<<"*"<<string(2, ' ');
    } else {
      cout<<string(1, ' ')<<s1[i-1]<<string(2, ' ');
    }
    for (int j=0; j<=s2.length(); j++) {
      //cout<<to_string((int)affineMatrix[i][j]).length()<<":FDF:"<<to_string((int)affineMatrix[i][j])<<endl;
      if (to_string(affineMatrix[i][j]) == "-inf") {
          cout<<affineMatrix[i][j]<<string(3, ' ');
      } else if (to_string((int)affineMatrix[i][j]).length() == 4) {
          cout<<affineMatrix[i][j]<<string(3, ' ');
      } else if (to_string((int)affineMatrix[i][j]).length() == 3) {
          cout<<affineMatrix[i][j]<<string(4, ' ');
      } else if (to_string((int)affineMatrix[i][j]).length() == 2) {
          cout<<affineMatrix[i][j]<<string(5, ' ');
      } else if (to_string((int)affineMatrix[i][j]).length() == 1) {
          cout<<affineMatrix[i][j]<<string(6, ' ');}
      // } else {
      //     cout<<affineMatrix[i][j]<<string(4, ' ');
      // }
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
  X[0][0] = 0;
  Y[0][0] = 0;

  for (int k=1; k<_columns; k++) {
    X[0][k] = _gap_open + ((k-1)*_gap_extend);
    Y[0][k] = negInfinity;
    M[0][k] = negInfinity;
  }
  for (int k=1; k<_rows; k++) {
    Y[k][0] = _gap_open + ((k-1)*_gap_extend);
    X[k][0] = negInfinity;
    M[k][0] = negInfinity;
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

float AGP::getMax(float mTrix, float xTrix, float yTrix, char *matrix) {
  float max_val;
  if (mTrix >= xTrix && mTrix >= yTrix) {
    max_val = mTrix;
    *matrix = 'm';
  } else if (xTrix >= mTrix && xTrix >= yTrix) {
    max_val = xTrix;
    *matrix = 'x';
  } else {
    max_val = yTrix;
    *matrix = 'y';
  }
  return max_val;
}

int * AGP::fillMatrices(char *refMatrix) {
  float **M = _M->returnAffineMat();
  float **X = _X->returnAffineMat();
  float **Y = _Y->returnAffineMat();
  char **PM = _M->returnPointerMat(); //pointer matrix for _M
  char **PX = _X->returnPointerMat();
  char **PY = _Y->returnPointerMat();

  //float opt = 0;
  float max_val;
  int *opt_matrix = new int[3];
  char temp = 'u';
  char pTemp = 'u';
  char *mat = &temp;
  char *pMat = &pTemp;
  int indexX = 0, indexY = 0;
  for (int i=1; i<_rows; i++) {
    for (int j=1; j<_columns; j++) {
      max_val = 0;
      //*mat = 'u'; //to re-initialize. not needed but for reader's understanding.
      //*pMat = 'u';
      M[i][j] = matchChars(_s1[i-1], _s2[j-1]) + this->getMax(M[i-1][j-1],
                X[i-1][j-1], Y[i-1][j-1], pMat);
      PM[i][j] = *pMat;

      X[i][j] = this->getMax((M[i][j-1] + _gap_open), (X[i][j-1] + _gap_extend),
                (Y[i][j-1] + _gap_open), pMat);
      PX[i][j] = *pMat;

      Y[i][j] = this->getMax((M[i-1][j] + _gap_open), (X[i-1][j] + _gap_open),
                (Y[i-1][j] + _gap_extend), pMat);
      PY[i][j] = *pMat;

      max_val = this->getMax(M[i][j], X[i][j], Y[i][j], mat);
      indexX = i;
      indexY = j;

      if (max_val > opt_matrix[0]) {
        //opt = max_val;
        opt_matrix[0] = max_val;
        opt_matrix[1] = indexX;
        opt_matrix[2] = indexY;
        *refMatrix = *mat;
      }
    }
  }
  cout<<"opt:"<<opt_matrix[0]<<endl;
  cout<<"mat:"<<*refMatrix<<endl;
  cout<<"xindex:"<<opt_matrix[1]<<endl;
  cout<<"yindex:"<<opt_matrix[2]<<endl;
  return opt_matrix;
}

int AGP::performRecursion(string &seq1, string &seq2, int indexX, int indexY, char refMatrix) {
  char **PM = _M->returnPointerMat(); //pointer matrix for _M
  char **PX = _X->returnPointerMat();
  char **PY = _Y->returnPointerMat();
  //char matName = 'u';
  if (indexX == 0 && indexY == 0) {
    return 1;
  } else {
    if (refMatrix == 'm') {
       refMatrix = PM[indexX][indexY];
       seq1 += _s1[indexX - 1];
       seq2 += _s2[indexY - 1];
       indexX -= 1;
       indexY -= 1;
       return this->performRecursion(seq1, seq2, indexX, indexY, refMatrix);
    } else if (refMatrix == 'x') {
      refMatrix = PM[indexX][indexY];
      seq1 += _s1[indexX - 1];
      seq2 += _s2[indexY - 1];
      indexY -= 1;
      return this->performRecursion(seq1, seq2, indexX, indexY, refMatrix);
    } else {
      refMatrix = PM[indexX][indexY];
      seq1 += _s1[indexX - 1];
      seq2 += _s2[indexY - 1];
      indexX -= 1;
      return this->performRecursion(seq1, seq2, indexX, indexY, refMatrix);
    }
  }
}

void AGP::performBacktrace(float max_val, int indexX, int indexY, char *refMatrix) {
  // float **M = _M->returnAffineMat();
  // float **X = _X->returnAffineMat();
  // float **Y = _Y->returnAffineMat();
  // char **PM = _M->returnPointerMat(); //pointer matrix for _M
  // char **PX = _X->returnPointerMat();
  // char **PY = _Y->returnPointerMat();
  // int max_length = max(_s1.length(), _s2.length());
  // char *seq1 = new char[max_length+1];
  // char *seq2 = new char[max_length+1];
  string seq1, seq2;
  this->performRecursion(seq1, seq2, indexX, indexY, *refMatrix);
  //performRecursion();
  //if (*refMatrix)
}

void AGP::printMatrix() {
  _M->printMatrix(_s1, _s2);
  _X->printMatrix(_s1, _s2);
  _Y->printMatrix(_s1, _s2);
}
