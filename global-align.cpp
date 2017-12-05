#include<iostream>
#include "AGP.h"
#include <typeinfo>
//using namespace std;

int main() {
	AGP *agp = new AGP(2,1,1,0,"acgt","cg");
	agp->initializeMatrices();
	agp->fillMatrices();
	agp->printMatrix();
	// cout << std::string( 4, ' ' );
	// cout<<"happy"<<endl;
	return 0;
}
