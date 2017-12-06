#include<iostream>
#include "AGP.h"

//using namespace std;

int main() {
	char temp = 'u';
	char *refMatrix = &temp;
	int *refInfo = 0;
	string *sequences = 0;

	AGP *agp = new AGP(-15,-5,10,-5,"cg","acgt");
	agp->initializeMatrices();
	refInfo = agp->fillMatrices(refMatrix);
	//passing max_val, index-x, index-y, matrix key to start the tracing
	sequences = agp->performBacktrace(refInfo[1], refInfo[2], refMatrix);
	cout<<"Optimal Alignment Score: "<<refInfo[0]<<endl;
	cout<<"Optimal Alignment"<<"\n"<<"________________________"<<endl;
	cout<<"sequence 1: "<<sequences[0]<<endl;
	cout<<"sequence 2: "<<sequences[1]<<endl;
	agp->printMatrix();
	return 0;
}

/*
	Test Cases
	gap_open and gap_extend are both negative
	match is +ve and mismatch <= 0

a)AGP *agp = new AGP(-15,-5,10,-5,"DRAVPI","DPLYV");
b)AGP *agp = new AGP(-15,-5,10,-5,"cg","acgt");
c)AGP *agp = new AGP(-3,-1,10,-5,"AAT","ACACT");
d)AGP *agp = new AGP(-10,-1,5,-2,"CAT","CART");
e)AGP *agp = new AGP(-10,-1,5,-2,"AAKL","ADACKKK");
f)AGP *agp = new AGP(-10,-1,5,-2,"AAATCA","AAAGAATTCA");
*/
