/*
 * BTreeNode.h
 *
 *  Created on: 2 de dic. de 2015
 *      Author: santiago
 */

#ifndef BTREENODE_H_
#define BTREENODE_H_
#include <fstream>
#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;
template <class T>
class BTree;

template<class T>
class BTreeNode
{
    T *keys;
    int t;
    BTreeNode<T> **C;
    int n;
    bool leaf;
public:
    BTreeNode(int t1, bool leaf1){
    	t = t1;
		leaf = leaf1;

		keys = new int[t];
		C = new BTreeNode<T> *[t+1];

		n = 0;
    }

    //void insertNonFull(int k);

    void insertar(int & k, BTreeNode<T> * & p){
    	int i = n-1;
		if (leaf == true)
		{
			if(n == t){
				BTreeNode<T> *z = new BTreeNode(t, leaf);
				z->n = ((int)t / 2);
				int j = 0;
				for (j = 0; j < ((int )t / 2)-1; j++){
					z->keys[j] = keys[(int)(j+round(t / (double)2)+1)];
					//cout<<t<<endl;
					//cout<<round(t / (double)2)<<endl;
				}
				z->keys[j] = k;
				n = (int)round(t / (double)2);
				k = keys[(int)round(t / (double)2)];
				p = z;
			}else{
				while (i >= 0 && keys[i] > k)
				{
					keys[i+1] = keys[i];
					i--;
				}
				keys[i+1] = k;
				n = n+1;
				p = 0;
			}
		}
		else
		{
			while (i >= 0 && keys[i] > k)
				i--;

			C[i+1]->insertar(k,p);

			if(p){
				if(n == t){
					BTreeNode<T> *z = new BTreeNode(t, leaf);
					z->n = ((int)t / 2);
					int j = 0;
					for (j = 0; j < ((int )t / 2)-1; j++)
						z->keys[j] = keys[(int)(j+round(t / (double)2)+1)];

					z->keys[j] = k;
					//cout<<j<<": "<<k<<endl;
					//cout<<z->n<<endl;
					for (j = 0; j < ((int )t / 2); j++)
						z->C[j] = C[(int)(j+round(t / (double)2)+1)];

					z->C[j] = p;
					n = (int)round(t / (double)2);
					k = keys[(int)round(t / (double)2)];
					p = z;

				}else{
					while (i >= 0 && keys[i] > k)
					{
						keys[i+1] = keys[i];
						i--;
					}
					keys[i+1] = k;
					int j = 0;
					for (j = n; j > i+1; j--)
						C[j+1] = C[j];

					C[j+1] = p;
					n = n+1;
					p = 0;
				}
			}
		}
    }

    //void splitChild(int i, BTreeNode<T> *y);

    //bool hayEspacio(int k);

    //BTreeNode<T> *search(int k, BTreeNode<T> * &q);

    void printDot(ofstream& os){os<<"\""<<this <<"\""<<"[shape=record, label=\"{{ ";
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

    friend class BTree<T>;
};



#endif /* BTREENODE_H_ */
