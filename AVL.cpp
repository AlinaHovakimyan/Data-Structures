#include <iostream>
#include<iomanip>
#include <time.h>
#include <vector>
#include <fstream>
using namespace std;

vector<int> numbers;

struct node
{
public:
    int data, height;
    node *leftChild, *rightChild;
};

node* root = NULL;

int findMin(node *p) // finds the smallest node in the tree
{
    while (p->leftChild != NULL)
        p = p->leftChild;
    return p->data;
}
int findMax(node *p) // finds the largest node in the tree
{
    while(p->rightChild != NULL)
        p = p->rightChild;
    return p->data;
}
int max(int a, int b) // gets the max of two integers
{
    if(a > b)
        return a;
    else
        return b;
}
int height(node *p) // gets the height of the tree
{
    if(p == NULL)
        return -1;
    else
    {
        p->height = max(height(p->leftChild), height(p->rightChild)) + 1;
    }
    return p->height;
}
node* newNode(int element) // helper function to return a new node with empty subtrees
{
    node* newPtr = new node;
    newPtr->data = element;
    newPtr->leftChild = NULL;
    newPtr->rightChild = NULL;
    newPtr->height = 1;
    return newPtr;
}
node* rightRotate(node* p) // function to right rotate a tree rooted at p
{
    node* child = p->leftChild; // rotate the tree
    p->leftChild = child->rightChild;
    child->rightChild = p;

    // update the height for the nodes
    p->height = height(p);
    child->height = height(child);
    // return new root
    return child;

}
node* leftRotate(node* p) // function to left rotate a tree rooted at p
{
    node* child = p->rightChild; // perform the rotation
    p->rightChild = child->leftChild;
    child->leftChild = p;

    // update the heights for the nodes
    p->height = height(p);
    child->height = height(child);

    // return new root
    return child;
}

int getBalance(node *p)
{
    if(p == NULL)
        return 0;
    else
        return height(p->leftChild) - height(p->rightChild);
}
// recursive version of BST insert to insert the element in a sub tree rooted with root
// which returns new root of subtree
node* insert(node*& p, int element)
{
    // perform the normal BST insertion
    if(p == NULL) // if the tree is empty
        return(newNode(element));
    if(element < p->data)
    {
        p->leftChild = insert(p->leftChild, element);
    }
    else
    {
        p->rightChild = insert(p->rightChild, element);
    }

    // update the height for this node
    p->height = height(p);

    // get the balance factor to see if the tree is unbalanced
    int balance = getBalance(p);

    // the tree is unbalanced, there are 4 different types of rotation to make

    // Single Right Rotation (Left Left Case)
    if(balance > 1 && element < p->leftChild->data)
    {
        return rightRotate(p);
    }
    // Single Left Rotation (Right Right Case)
    if(balance < -1 && element > p->rightChild->data)
    {
        return leftRotate(p);
    }
    // Left Right Rotation (double left rotation)
    if(balance > 1 && element > p->leftChild->data)
    {
        p->leftChild = leftRotate(p->leftChild);
        return rightRotate(p);
    }
    // Right Left Rotation
    if(balance < -1 && element < p->rightChild->data)
    {
        p->rightChild = rightRotate(p->rightChild);
        return leftRotate(p);
    }
    // cout << "Height: " << n->height << endl;
    // return the unmodified root pointer in the case that the tree does not become unbalanced
    return p;
}
void inorder(node *p)
{
    if(p != NULL)
    {
        inorder(p->leftChild);
        cout << p->data << ", ";
        inorder(p->rightChild);
    }
}
void preorder(node *p)
{
    if(p != NULL)
    {
        cout << p->data << ", ";
        preorder(p->leftChild);
        preorder(p->rightChild);
    }
   /* else {
          cout << "p is  null" << endl;
      }
   */
}

void print(node* root)
{
    /*cout << "Min Value: " << findMin(root) << endl;
    cout << "Max Value: " << findMax(root) << endl;
    cout << "Pre Order: ";
    preorder(root); */
    cout << endl << "Inorder: ";
    inorder(root);
    cout << endl << endl << endl << endl;

}

void read()
{
    int num;
    ifstream file_save("data.txt");
    if(file_save.is_open())
    {
        while(!file_save.eof())
        {
            file_save >> num;
            numbers.push_back(num);
        }
        file_save.close();
    }
    else
    {
        cout << "Error in opening file!!" << endl;   //File can't be opened
    }
}

int main()
{
    double duration;
    time_t begin = time(0);

    read();
    int x = 0;
    int track = 0;
    for (std::vector<int>::const_iterator i = numbers.begin(); i != numbers.begin() + 100000; ++i)
    {
        root = insert(root, numbers[x]);
        x++;
        track++;
        if( (track % 10000) == 0)
        {
            cout << track << " iterations" << endl;
            time_t now = time(0);
            cout << now - begin << " seconds" << endl;
        }

    }
    time_t end = time(0);
    duration = end - begin;
    // print(root);
    cout << "The algorithm took " << duration << " seconds to complete." << endl;
    return 0;
}