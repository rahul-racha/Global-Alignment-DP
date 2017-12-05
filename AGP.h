#include <string>
using namespace std;

class MAT {
  private:
    float **affineMatrix;
  public:
    MAT(int r, int c);
    float ** returnAffineMat();
    void printMatrix(string s1, string s2);
};

class AGP {
	private:
		int _gap_open;
		int _gap_extend;
		int _match;
		int _mismatch;
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
    int matchChars(char a, char b);
    void fillMatrices();
    // void initializeX();
    // void initializeY();
    //void initializeMatrices();
    void printMatrix();
};
