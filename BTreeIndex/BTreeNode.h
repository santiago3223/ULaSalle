/*
 * BTreeNode.h
 *
 *  Created on: 2 de dic. de 2015
 *      Author: santiago
 */

#ifndef BTREENODE_H_
#define BTREENODE_H_
#include <fstream>
#include <iostream>
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
    int *pos;
    int *c;
    int t;
    int n;
    bool leaf;
public:
    BTreeNode(int t1, bool leaf1){
    	t = t1;
		leaf = leaf1;
		pos = new int[t];
		keys = new T[t];
		c = new int[t+1];
		for(int i = 0; i<t; i++){
			keys[i] =0;
			c[i] = 0;
			c[i+1] = 0;
			pos[i] = 0;
		}

		n = 0;
    }

    //void insertNonFull(int k);

    void insertar(T & k, int & ps, int & pe){
    	int i = n-1;
		if (leaf == true)
		{
			if(n == t){
				BTreeNode<T> *z = new BTreeNode(t, leaf);
				z->n = ((int)t / 2);

				if(k < keys[t-1]){
					int x = k;
					k = keys[t-1];
					keys[t-1] = x;
					x = ps;
					ps = pos[t-1];
					pos[t-1] = x;
					int e = t-1;
					while(keys[e]<keys[e-1] && i>0){
						int x = keys[e-1];
						keys[e-1] = keys[e];
						keys[e] = x;
						x = pos[e-1];
						pos[e-1] = pos[e];
						pos[e] = x;
						e--;
					}
				}
				int j = 0;
				for (j = 0; j < ((int )t / 2)-1; j++){
					z->keys[j] = keys[(int)(j+round(t / (double)2)+1)];
					z->pos[j] = pos[(int)(j+round(t / (double)2)+1)];
					//cout<<t<<endl;
					//cout<<round(t / (double)2)<<endl;
				}
				z->keys[j] = k;
				z->pos[j] = ps;
				n = (int)round(t / (double)2);
				k = keys[(int)round(t / (double)2)];
				ps = pos[(int)round(t / (double)2)];
				serialize("data.bin",pe);
				cout<<"ene"<<z->n<<endl;
				pe = z->serialize("data.bin");
			}else{
				while (i >= 0 && keys[i] > k)
				{
					keys[i+1] = keys[i];
					pos[i+1] = pos[i];
					i--;
				}
				keys[i+1] = k;
				pos[i+1] = ps;
				n = n+1;
				serialize("data.bin",pe);
				pe = 0;
			}
		}
		else
		{
			int ptemp= pe;
			while (i >= 0 && keys[i] > k)
				i--;

			BTreeNode<T> temporal(t,true);
			pe = c[i+1];
			temporal.deserialize("data.bin",pe);
			temporal.insertar(k,ps,pe);
			//C[i+1]->insertar(k,ps,p, pe);

			if(pe){
				if(n == t){
					BTreeNode<T> *z = new BTreeNode(t, leaf);
					z->n = ((int)t / 2);

					int j = 0;
					for (j = 0; j < ((int )t / 2)-1; j++){
							z->keys[j] = keys[(int)(j+round(t / (double)2)+1)];
							z->pos[j] = pos[(int)(j+round(t / (double)2)+1)];
					}
					z->keys[j] = k;
					z->pos[j] = ps;
					//cout<<j<<": "<<k<<endl;
					//cout<<z->n<<endl;
					for (j = 0; j < ((int )t / 2); j++){
						z->c[j] = c[(int)(j+round(t / (double)2)+1)];
					}
					z->c[j] = pe;
					n = (int)round(t / (double)2);
					k = keys[(int)round(t / (double)2)];
					ps = pos[(int)round(t / (double)2)];
					serialize("data.bin",ptemp);
					pe = z->serialize("data.bin");

				}else{
					while (i >= 0 && keys[i] > k)
					{
						keys[i+1] = keys[i];
						pos[i+1] = pos[i];
						i--;
					}
					keys[i+1] = k;
					pos[i+1] = ps;
					int j = 0;
					for (j = n; j > i+1; j--){
						c[j+1] = c[j];
					}
					c[j+1] = pe;
					n = n+1;
					serialize("data.bin",ptemp);
					pe = 0;
				}
			}
		}
    }

    void printDot(ofstream& os, int pe){
    		os<<"\""<<pe <<"\""<<"[shape=record, label=\"{{ ";
    		os<<keys[0];
    		os<<":"<<pos[0];
    		for(int i = 1; i<n; i++){
    				os<<"|"<<keys[i]<<":"<<pos[i];
    		}
    		os<<"} } \"];"<<endl;

    		for(int i = 0 ; i<n+1; i++){
    			if(c[i]){
    				//cout<<c[i]<<endl;
    				BTreeNode<T> temporal(t,true);
    				temporal.deserialize("data.bin", c[i]);
    				temporal.printDot(os, c[i]);
    				//C[i]->printDot(os);
    			os<<"\""<<pe<<"\""<<"->"<<"\""<<c[i]<<"\""<<endl;
    			}
    		}
        }

    int serialize(char * ruta){
    	std::ifstream infile (ruta ,ios::in|ifstream::binary);
		  infile.seekg (0, infile.end);
		  serialize(ruta,infile.tellg());
		  return infile.tellg();
		  //cout<<"end:"<<infile.tellg()<<endl;
    }

    void serialize(char * ruta, int ps){
	  ofstream outfile (ruta,ios::in| ifstream::binary);
	  outfile.seekp(ps);
	  outfile.write ((char *)keys ,sizeof(T)*t);
	  outfile.write ((char *)pos ,sizeof(int)*t);
	  outfile.write ((char *)c ,sizeof(int)*(t+1));
	  outfile.write ((char *)&n ,sizeof(int));
	  outfile.write ((char *)&leaf ,sizeof(bool));

	  outfile.close();
    }


    void deserialize(char * ruta, int pos){
    	  std::ifstream infile (ruta ,ios::in |ifstream::binary);
    	  infile.seekg(pos);
    	  char* buffer = new char[t];
    	  char* buffer1 = new char[t];
    	  char* buffer2 = new char[t+1];
    	  char* buf = new char[t];
    	  char* buff = new char[t];
    	  infile.read (buffer,sizeof(T)*t);
    	  keys = (int *)buffer;
    	  for(int i = 0; i< t; i++){
				  cout<<i<<":"<<keys[i]<<endl;
			  }

    	  infile.read (buffer1,sizeof(T)*t);
    	  this->pos = (int *)buffer1;
    	  for(int i = 0; i< t; i++){
    	  				  cout<<i<<":"<<this->pos[i]<<endl;
    	  			  }

    	  infile.read (buffer2,sizeof(T)*(t+1));
    	  c = (int *)buffer2;
    	  for(int i = 0; i< t+1; i++){
    	  				  cout<<i<<":"<<c[i]<<endl;
    	  			  }
    	  infile.read (buf,sizeof(int));
    	  n =  *((int *)buf);
    	  infile.read (buff,sizeof(bool));
		  leaf = buff[0];
    	  infile.close();
    }


    friend class BTree<T>;
};



#endif /* BTREENODE_H_ */
