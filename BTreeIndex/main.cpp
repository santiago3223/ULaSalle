/*
 * main.cpp
 *
 *  Created on: 17 de nov. de 2015
 *      Author: santiago
 */

#include <fstream>
#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "BTreeNode.h"
#include "BTree.h"
using namespace std;

int main()
{
    BTree<int> t(7);
    for(int i = 0 ; i<= 20; i++){
    	t.insertar(i, i+1);
    }

    //int k = t.find(9);
    //cout<<"buscando clave nueve, retorna"<<"linea: "<<k<<endl;

    //cout<<"pos"<<t.find(5)<<endl;
    //cout<<"pos"<<t.find(40)<<endl;
    t.printDot("archivo.dot");
	system("dot -Tpng archivo.dot -o archivo.png");
    cout<<"fin"<<endl;

    return 0;
}

