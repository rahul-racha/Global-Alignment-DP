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
  cout<<string(4, ' ')<<"*"<<string(6, ' ');
  for (int k=0; k<s2.length(); k++) {
    cout<<s2[k]<<string(6, ' ');
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
          cout<<affineMatrix[i][j]<<string(6, ' ');
      } else {
          //to do
      }
    }
    cout<<endl;
  }
}


void MAT::printPointerMatrix(string s1, string s2) {
  cout<<pointerMatrix[1][0]<<endl;
  cout<<string(4, ' ')<<"*"<<string(6, ' ');
  for (int k=0; k<s2.length(); k++) {
    cout<<s2[k]<<string(6, ' ');
  }
  cout<<endl;
  for (int i=0; i<=s1.length(); i++) {
    if (i==0) {
      cout<<string(1, ' ')<<"*"<<string(2, ' ');
    } else {
      cout<<string(1, ' ')<<s1[i-1]<<string(2, ' ');
    }
    for (int j=0; j<=s2.length(); j++) {
      //cout<<to_string((int)pointerMatrix[i][j]).length()<<":FDF:"<<to_string((int)pointerMatrix[i][j])<<endl;
      if (to_string(pointerMatrix[i][j]) == "-inf") {
          cout<<pointerMatrix[i][j]<<string(3, ' ');
      } else if (to_string((int)pointerMatrix[i][j]).length() == 4) {
          cout<<pointerMatrix[i][j]<<string(3, ' ');
      } else if (to_string((int)pointerMatrix[i][j]).length() == 3) {
          cout<<pointerMatrix[i][j]<<string(4, ' ');
      } else if (to_string((int)pointerMatrix[i][j]).length() == 2) {
          cout<<pointerMatrix[i][j]<<string(5, ' ');
      } else if (to_string((int)pointerMatrix[i][j]).length() == 1) {
          cout<<pointerMatrix[i][j]<<string(6, ' ');}
      // } else {
      //     cout<<pointerMatrix[i][j]<<string(4, ' ');
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
  _negInfinity = -1 * numeric_limits<float>::infinity();
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

void AGP::reverseStr(string &str) {
  string temp = str;
  int max_index = str.length()-1;
  for (int k=max_index; k>=0; k--) {
    temp[max_index-k] = str[k];
  }
  str = temp;
}

void AGP::initializeMatrices() {
  float **M = _M->returnAffineMat();
  float **X = _X->returnAffineMat();
  float **Y = _Y->returnAffineMat();
  char **PM = _M->returnPointerMat(); //pointer matrix for _M
  char **PX = _X->returnPointerMat();
  char **PY = _Y->returnPointerMat();
  //const float negInfinity = -1 * numeric_limits<float>::infinity();

  M[0][0] = 0;
  X[0][0] = 0;
  Y[0][0] = 0;
  PM[0][0] = 'm';
  PX[0][0] = 'x';
  PY[0][0] = 'y';

  for (int k=1; k<_columns; k++) {
    X[0][k] = _gap_open + ((k-1)*_gap_extend);
    Y[0][k] = _negInfinity;
    M[0][k] = _negInfinity;
    PM[0][k] = 'x';
    PX[0][k] = 'x';
    PY[0][k] = 'x';
  }
  for (int k=1; k<_rows; k++) {
    Y[k][0] = _gap_open + ((k-1)*_gap_extend);
    X[k][0] = _negInfinity;
    M[k][0] = _negInfinity;
    PM[k][0] = 'y';
    PX[k][0] = 'y';
    PY[k][0] = 'y';
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
  //const float negInfinity = -1 * numeric_limits<float>::infinity();
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
                (Y[i][j-1] + _gap_open), pMat);//(Y[i][j-1] + _gap_open)
      PX[i][j] = *pMat;

      Y[i][j] = this->getMax((M[i-1][j] + _gap_open), (X[i-1][j] + _gap_open),
                (Y[i-1][j] + _gap_extend), pMat);//(X[i-1][j] + _gap_open)
      PY[i][j] = *pMat;

      max_val = this->getMax(M[i][j], X[i][j], Y[i][j], mat);
      indexX = i;
      indexY = j;

      if (max_val >= opt_matrix[0]) {
        //opt = max_val;
        opt_matrix[0] = max_val;
        opt_matrix[1] = indexX;
        opt_matrix[2] = indexY;
        *refMatrix = *mat;
      }
    }
  }
  // cout<<"opt:"<<opt_matrix[0]<<endl;
  // cout<<"mat:"<<*refMatrix<<endl;
  // cout<<"xindex:"<<opt_matrix[1]<<endl;
  // cout<<"yindex:"<<opt_matrix[2]<<endl;
  return opt_matrix;
}

int AGP::performRecursion(string &seq1, string &seq2, int indexX, int indexY, char refMatrix) {
  char **PM = _M->returnPointerMat(); //pointer matrix for _M
  char **PX = _X->returnPointerMat();
  char **PY = _Y->returnPointerMat();
  //char matName = 'u';
  if ((indexX == 0 && indexY == 0) || (indexX < 0 || indexY < 0)) {
    // if (indexX == 0 && indexY == 1) {
    //   seq1 += '_';
    //   seq2 += _s2[0];
    // } else if (indexX == 1 && indexY == 0) {
    //   seq1 += _s1[0];
    //   seq2 += '_';
    // } else {
    //   //Do nothing
    // }
    return 1;
  } else {
    if (refMatrix == 'm') {
       refMatrix = PM[indexX][indexY];
       //cout<<"M CORDINAE:("<<indexX<<","<<indexY<<") --"<<refMatrix<<endl;
       if (indexX >= 1 && indexY >= 1) {
         seq1 += _s1[indexX - 1];
         seq2 += _s2[indexY - 1];
       }
       indexX -= 1;
       indexY -= 1;
       // cout<<"PATH:M: "<<refMatrix<<endl;
       // cout<<"REC S1:"<<seq1<<endl;
       // cout<<"REC S2:"<<seq2<<endl;
       // cout<<"X:"<<indexX<<endl;
       // cout<<"Y:"<<indexY<<endl;
       return this->performRecursion(seq1, seq2, indexX, indexY, refMatrix);
    } else if (refMatrix == 'x') {
      refMatrix = PX[indexX][indexY];
      //cout<<"X CORDINAE:("<<indexX<<","<<indexY<<") --"<<refMatrix<<endl;
      if (indexY >= 1) {
        //if (indexX == 1 && indexY == 1) {
        //   seq1 += _s1[indexX - 1];
        //} else {
          seq1 += '_';
        //}
        seq2 += _s2[indexY - 1];
      }
      indexY -= 1;
      // cout<<"PATH:X: "<<refMatrix<<endl;
      // cout<<"REC S1:"<<seq1<<endl;
      // cout<<"REC S2:"<<seq2<<endl;
      // cout<<"X:"<<indexX<<endl;
      // cout<<"Y:"<<indexY<<endl;
      return this->performRecursion(seq1, seq2, indexX, indexY, refMatrix);
    } else {
      refMatrix = PY[indexX][indexY];
      //cout<<"Y CORDINAE:("<<indexX<<","<<indexY<<") --"<<refMatrix<<endl;
      if (indexX >= 1) {
        seq1 += _s1[indexX - 1];
        //if (indexX == 1 && indexY == 1) {
        //  seq2 += _s2[indexY - 1];
        //} else {
          seq2 += '_' ;
        //}
      }
      indexX -= 1;
      // cout<<"PATH:Y: "<<refMatrix<<endl;
      // cout<<"REC S1:"<<seq1<<endl;
      // cout<<"REC S2:"<<seq2<<endl;
      // cout<<"X:"<<indexX<<endl;
      // cout<<"Y:"<<indexY<<endl;
      return this->performRecursion(seq1, seq2, indexX, indexY, refMatrix);
    }
  }
}

string * AGP::performBacktrace(int indexX, int indexY, char *refMatrix) {
  indexX = _rows - 1;
  indexY = _columns - 1;
  char **PM = _M->returnPointerMat(); //pointer matrix for _M
  char **PX = _X->returnPointerMat();
  char **PY = _Y->returnPointerMat();

  string seq1, seq2;
  char matName = *refMatrix;
  seq1 += _s1[indexX - 1];
  seq2 += _s2[indexY - 1];

  if (*refMatrix == 'm') {
     matName = PM[indexX][indexY];
     indexX -= 1;
     indexY -= 1;
  } else if (*refMatrix == 'x') {
    matName = PM[indexX][indexY];
    indexY -= 1;
  } else {
    matName = PM[indexX][indexY];
    indexX -= 1;
  }

  // cout<<"PATH:"<<matName<<endl;
  // cout<<"X:"<<indexX<<endl;
  // cout<<"Y:"<<indexY<<endl;
  this->performRecursion(seq1, seq2, indexX, indexY, matName);
  // cout<<"***s1:"<<seq1<<endl;
  // cout<<"***s2:"<<seq2<<endl;
  //reverse(seq1.begin(), seq1.end());
  //reverse(seq1.begin(), seq2.end());
  this->reverseStr(seq1);
  this->reverseStr(seq2);
  string *sequences = new string[2];
  sequences[0] = seq1;
  sequences[1] = seq2;
  return sequences;
}

void AGP::printMatrix() {
  cout<<endl;
  cout<<"***F(i,j)***"<<endl;
  _M->printMatrix(_s1, _s2);
  //_M->printPointerMatrix(_s1, _s2);
  cout<<endl;
  cout<<"***X(i,j)***"<<endl;
  _X->printMatrix(_s1, _s2);
  //_X->printPointerMatrix(_s1, _s2);
  cout<<endl;
  cout<<"***Y(i,j)***"<<endl;
  _Y->printMatrix(_s1, _s2);
  //_Y->printPointerMatrix(_s1, _s2);

}
