#include <string>
using namespace std;

class MAT {
  private:
    int **affineMatrix;
  public:
    MAT(int r, int c);
    void printMatrix();
    //MARK:methods to insert
};

class AGP {
	private:
		int _gap_open;
		int _gap_extend;
		int _match;
		int _mismatch;
    string _s1;
    string _s2;
    MAT *_M;
    MAT *_I;
    MAT *_Y;
	public:
		AGP(int gap_open, int gap_extend, int match, int mismatch, string s1, string s2); //constructor
		int getParameter(char param);
    void printMatrix();
};
