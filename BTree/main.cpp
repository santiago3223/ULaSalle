/*
 * main.cpp
 *
 *  Created on: 17 de nov. de 2015
 *      Author: santiago
 */

#include <fstream>
#include<iostream>
#include <stdlib.h>
using namespace std;

// A BTree node
class BTreeNode
{
    int *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;
public:
    BTreeNode(int _t, bool _leaf);

    void insertNonFull(int k);

    void splitChild(int i, BTreeNode *y);

    BTreeNode *search(int k, BTreeNode * &q);

    void printDot(ofstream& os);

friend class BTree;
};

class BTree
{
    BTreeNode *root;
    int t;
public:
    BTree(int _t)
    {  root = NULL;  t = _t; }

    BTreeNode* search(int k)
    {
    	BTreeNode * q = 0;
    	return (root == NULL)? NULL : root->search(k, q);
    }

    void insert(int k);
    void printDot(char* p);
};

BTreeNode::BTreeNode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;

    keys = new int[t];
    C = new BTreeNode *[t+1];

    n = 0;
}

void BTree::printDot(char* p)
	{
		ofstream file(p);
		file<<"digraph {"<<endl;
		root->printDot(file);
		file<<" }"<<endl;
	}

void BTreeNode::printDot(ofstream& os){
	os<<"\""<<this <<"\""<<"[shape=record, label=\"{{ ";
	os<<keys[0];

	for(int i = 1; i<n; i++){
			os<<"|"<<keys[i];
	}
	os<<"} } \"];"<<endl;

	for(int i = 0 ; i<n+1; i++){
		if(C[i]){
		C[i]->printDot(os);
		os<<"\""<<this<<"\""<<"->"<<"\""<<C[i]<<"\""<<endl;
		}
	}
}

BTreeNode *BTreeNode::search(int k, BTreeNode * &q)
{
	q = this;
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->search(k, q);
}

void BTree::insert(int k)
{
    if (root == NULL)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
    	BTreeNode * q = 0;
    	BTreeNode * nn = root->search(k, q);
        if (root->n ==t && q->n == t)
        {
            BTreeNode *s = new BTreeNode(t, false);

            s->C[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        }
        else
            root->insertNonFull(k);
    }
}

void BTreeNode::insertNonFull(int k)
{
    int i = n-1;
    if (leaf == true)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }

        keys[i+1] = k;
        n = n+1;
    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;

        BTreeNode * q = 0;
        BTreeNode * nn = search(k, q);
        if (C[i+1]->n == t && q->n == t)
        {
            splitChild(i+1, C[i+1]);

            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y)
{
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = ((int)t / 2)-1;

    for (int j = 0; j < ((int )t / 2) -1; j++)
        z->keys[j] = y->keys[j+((int )t / 2)+1];

    if (y->leaf == false)
    {
        for (int j = 0; j < ((int )t / 2)+1; j++)
            z->C[j] = y->C[j+((int )t / 2) +1];
    }

    y->n = ((int )t / 2);

    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];

    C[i+1] = z;

    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    keys[i] = y->keys[(int )t / 2];

    n = n + 1;
}

int main()
{
    BTree t(4);
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    t.insert(8);
    t.insert(9);
    t.insert(10);
    t.insert(11);
    t.insert(12);
    t.insert(13);
    t.insert(14);
    t.insert(15);
    t.insert(16);
    t.insert(17);
    t.insert(18);
    t.insert(19);
    t.insert(20);
    t.insert(21);
    t.insert(22);
    t.insert(23);
    t.insert(24);
    t.insert(25);
    t.insert(26);

    t.printDot("archivo.dot");
	system("dot -Tpng archivo.dot -o archivo.png");
    cout<<"fin"<<endl;

    return 0;
}
