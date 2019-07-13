#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

// A Binomial heap Node. 
struct Node
{
	int data;
	int degree;
	Node* child;
	Node* sibling;
	Node* parent;
};

class BinomialHeap {
public:
	Node* Create_Node(int);
	Node* Insert(Node*, Node*);
	Node* Union(Node*, Node*);
	Node* Merge(Node*, Node*);
	Node* Extract_Min(Node*);
	Node* getMin(Node*);
	int Display(Node* H);
private:
};

#endif
