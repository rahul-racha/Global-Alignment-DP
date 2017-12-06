#include<iostream>
#include "AGP.h"
#include <typeinfo>
//using namespace std;
// void maxi(char *q) {
// 	*q = 'I';
// }

// void dummy(string &s) {
// 	// s[0] = 'h';
// 	// s[1] = 'e';
// 	char f = 'L';
// 	cout<<to_string(f);
// 	s += f;//.append(to_string(f));
// }
int main() {
	char temp = 'u';
	char *refMatrix = &temp;
	int *refInfo = 0;
	AGP *agp = new AGP(-15,-5,10,-5,"acgt","cg");
	agp->initializeMatrices();
	refInfo = agp->fillMatrices(refMatrix);
	agp->printMatrix();


	// string m = "s";
	// //*m = "bye";
	// cout<<"original:"<<m<<endl;
	// dummy(m);
	// cout<<"updated:"<<m<<endl;
	//int a = max(6,5);
	//cout<<"A:"<<a<<endl;
	// cout << std::string( 4, ' ' );
	// cout<<"happy"<<endl;
	// char t = 's';
	// char *w = &t;
	// cout<<"original:"<<(*w)<<endl;
	// maxi(w);
	// cout<<"update:"<<(*w)<<endl;

	// M[i][j] = matchChars(_s1[i-1], _s2[j-1]) + max (
	// 										max (
	// 											M[i-1][j-1],
	// 											X[i-1][j-1]
	// 										),
	// 										Y[i-1][j-1]
	// 					);
	// X[i][j] = max(
	// 						max (
	// 							M[i][j-1] + _gap_open,
	// 							X[i][j-1] + _gap_extend
	// 						),
	// 						Y[i][j-1] + _gap_open
	// 					);
	// Y[i][j] = max(
	// 						max (
	// 							M[i-1][j] + _gap_open,
	// 							X[i-1][j] + _gap_open
	// 						),
	// 						Y[i-1][j] + _gap_extend
	// 					);

	// if (M[i][j] > X[i][j] && M[i][j] > Y[i][j]) {
	// 	max_val = M[i][j];
	// 	//mat = 'm';
	// } else if (X[i][j] > M[i][j] && X[i][j] > Y[i][j]) {
	// 	max_val = X[i][j];
	// 	//mat = 'x';
	// } else {
	// 	max_val = Y[i][j];
	// 	//mat = 'y';
	// }

	return 0;
}
