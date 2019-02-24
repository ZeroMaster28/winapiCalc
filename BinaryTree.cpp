#include"BinaryTree.h"
#define TYP_LICZB_KALKULATORA double
#define TYP TYP_LICZB_KALKULATORA




template < typename typ >
NumberLeaf<typ>::NumberLeaf()
{
	son1 = NULL;
	son2 = NULL;
	father = NULL;
	identifier = -1;
	c = '\0';

}

NumberLeaf<TYP>::NumberLeaf(NumberLeaf* n1, NumberLeaf* n2, NumberLeaf* n3, char c='\0')
{
	this->son1 = n1;
	this->son2 = n2;
	this->father = n3;
	this->identifier = -1;
	this->c = c;

}

void cBinaryTree::add(NumberLeaf<TYP_LICZB_KALKULATORA>* its, NumberLeaf<TYP_LICZB_KALKULATORA>* son1, NumberLeaf<TYP_LICZB_KALKULATORA>* son2)
{
	binaryTab.push_back(its);
	its->identifier = binaryTab.size() - 1;
	its->son1 = son1;
	its->son2 = son2;
}