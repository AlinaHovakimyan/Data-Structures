#include "BinomialHeap.h"
#include <iostream>


Node* newNode(int key)
{
	Node *temp = new Node;
	temp->data = key;
	temp->degree = 0;
	temp->child = temp->parent = temp->sibling = nullptr;
	return temp;
}


Node* BinomialHeap::Create_Node(int k)
{
	Node* p = new Node;
	p->data = k;
	return p;
}


Node* BinomialHeap::Insert(Node* H, Node* x)
{
	x->parent = nullptr;
	x->child = nullptr;
	x->sibling = nullptr;
	x->degree = 0;
	H1 = x;
	H = Union(H, H1);
	return H;
}



int BinomialHeap::Display(Node* H)
{
	if (H == nullptr)
	{
		std::cout << "The Heap is empty" << std::endl;
		return 0;
	}
	std::cout << "The root Nodes are: " << std::endl;
	Node* p;
	p = H;
	while (p != nullptr)
	{
		std::cout << p->data;
		if (p->sibling != nullptr)
			std::cout << "-->";
		p = p->sibling;
	}
	std::cout << std::endl;
}
/*
* Extract Minimum
*/
Node* BinomialHeap::Extract_Min(Node* H1)
{
	Hr = nullptr;
	Node* t = nullptr;
	Node* x = H1;
	if (x == nullptr)
	{
		std::cout << "Nothing to Extract" << std::endl;
		return x;
	}
	int min = x->data;
	Node* p = x;
	while (p->sibling != nullptr)
	{
		if ((p->sibling)->data < min)
		{
			min = (p->sibling)->data;
			t = p;
			x = p->sibling;
		}
		p = p->sibling;
	}
	if (t == nullptr && x->sibling == nullptr)
		H1 = nullptr;
	else if (t == nullptr)
		H1 = x->sibling;
	else if (t->sibling == nullptr)
		t = nullptr;
	else
		t->sibling = x->sibling;
	if (x->child != nullptr)
	{
		Revert_list(x->child);
		(x->child)->sibling = nullptr;
	}
	H = Union(H1, Hr);
	return x;
}
/*
* Reverse List
*/
void BinomialHeap::Revert_list(Node* y)
{
	if (y->sibling != nullptr)
	{
		Revert_list(y->sibling);
		(y->sibling)->sibling = y;
	}
	else
	{
		Hr = y;
	}
}


Node * BinomialHeap::Union(Node* H1, Node* H2)
{
	Node *H = Initializeheap();
	H = Merge(H1, H2);
	if (H == nullptr)
		return H;
	Node* prev_x;
	Node* next_x;
	Node* x;
	prev_x = nullptr;
	x = H;
	next_x = x->sibling;
	while (next_x != nullptr)
	{
		if ((x->degree != next_x->degree) || ((next_x->sibling != nullptr)
			&& (next_x->sibling)->degree == x->degree))
		{
			prev_x = x;
			x = next_x;
		}
		else
		{
			if (x->data <= next_x->data)
			{
				x->sibling = next_x->sibling;
				Binomial_link(next_x, x);
			}
			else
			{
				if (prev_x == nullptr)
					H = next_x;
				else
					prev_x->sibling = next_x;
				Binomial_link(x, next_x);
				x = next_x;
			}
		}
		next_x = x->sibling;
	}
	return H;
}


void BinomialHeap::Binomial_link(Node* y, Node* z)
{
	y->parent = z;
	y->sibling = z->child;
	z->child = y;
	z->degree = z->degree + 1;
}

Node* BinomialHeap::Initializeheap()
{
	Node* np = nullptr;
	return np;
}

// This function merge two Binomial Trees. 
Node* BinomialHeap::Merge(Node *b1, Node *b2)
{
	// Make sure b1 is smaller 
	if (b1->data > b2->data)
		std::swap(b1, b2);

	// We basically make larger valued tree 
	// a child of smaller valued tree 
	b2->parent = b1;
	b2->sibling = b1->child;
	b1->child = b2;
	b1->degree++;

	return b1;
}
/*
list<Node*> extractMin(list<Node*> _heap)
{
	list<Node*> new_heap, lo;
	Node *temp;

	// temp contains the pointer of minimum value 
	// element in heap 
	temp = getMin(_heap);
	list<Node*>::iterator it;
	it = _heap.begin();
	while (it != _heap.end())
	{
		if (*it != temp)
		{
			// inserting all Binomial Tree into new 
			// binomial heap except the Binomial Tree 
			// contains minimum element 
			new_heap.push_back(*it);
		}
		it++;
	}
	lo = removeMinFromTreeReturnBHeap(temp);
	new_heap = unionBionomialHeap(new_heap, lo);
	new_heap = adjust(new_heap);
	return new_heap;
}
*/
// return pointer of minimum value Node 
// present in the binomial heap 
Node* BinomialHeap::getMin(list<Node*> _heap)
{
	list<Node*>::iterator it = _heap.begin();
	Node *temp = *it;
	while (it != _heap.end())
	{
		if ((*it)->data < temp->data)
			temp = *it;
		it++;
	}
	return temp;
}


// inserting a key into the binomial heap 
list<Node*> insert(list<Node*> _head, int key)
{
	Node *temp = newNode(key);
	return insertATreeInHeap(_head, temp);
}
*/