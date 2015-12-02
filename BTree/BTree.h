/*
 * BTree.h
 *
 *  Created on: 2 de dic. de 2015
 *      Author: santiago
 */

#ifndef BTREE_H_
#define BTREE_H_
#include <fstream>
#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "BTreeNode.h"
using namespace std;

template<class T>
class BTree
{
    BTreeNode<T> *root;
    int t;
public:
    BTree(int _t)
    {  root = NULL;  t = _t; }

    //BTreeNode* search(int k)
    //{
    //	BTreeNode<T> * q = 0;
    //	return (root == NULL)? NULL : root->search(k, q);
    //}

    //void insert(int k);
    void insertar(int k){
    	if (root == NULL)
    		{
    		        root = new BTreeNode<T>(t, true);
    		        root->keys[0] = k;
    		        root->n = 1;
    		}else{
    			BTreeNode<T> * p = 0;
    			root->insertar(k,p);
    			if(p){
    					BTreeNode<T> *s = new BTreeNode<T>(t, false);
    					s->C[0] = root;
    					s->C[1] = p;
    					s->n = 1;
    					cout<<s->C[1]<<endl;
    					s->keys[0] = k;
    					root = s;
    			}
    			//root->insertar(k);
    		}
    }
    void printDot(char* p){
    	ofstream file(p);
    			file<<"digraph {"<<endl;
    			root->printDot(file);
    			file<<" }"<<endl;
    }
};



#endif /* BTREE_H_ */
