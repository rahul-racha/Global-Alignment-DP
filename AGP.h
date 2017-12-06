#include <string>
using namespace std;

class MAT {
  private:
    float **affineMatrix;
    char **pointerMatrix;
  public:
    MAT(int r, int c);
    float ** returnAffineMat();
    char ** returnPointerMat();
    void printMatrix(string s1, string s2);
    void printPointerMatrix(string s1, string s2);
};

class AGP {
	private:
		int _gap_open;
		int _gap_extend;
		int _match;
		int _mismatch;
    float _negInfinity;
    string _s1;
    string _s2;

    int _rows;
    int _columns;
    MAT *_M;
    MAT *_X;
    MAT *_Y;

	public:
		AGP(int gap_open, int gap_extend, int match, int mismatch, string s1, string s2); //constructor
		int getParameter(char param);
    void initializeMatrices();
    void reverseStr(string &str);
    int matchChars(char a, char b);
    float getMax(float mTrix, float xTrix, float yTrix, char *matrix);
    int * fillMatrices(char *refMatrix);
    string * performBacktrace(int indexX, int indexY, char *refMatrix);
    int performRecursion(string &seq1, string &seq2, int indexX, int indexY, char refMatrix);
    void printMatrix();
};
