#include<iostream>
#include "AGP.h"
//using namespace std;

int main() {
	AGP *agp = new AGP(2,1,1,0,"a","b");
	cout<<agp->getParameter('o')<<endl;
	agp->printMatrix();
	return 0;
}
