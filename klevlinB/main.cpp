/*
 * =============================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/12/15 10:52:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kelvin Helmut Provincia Quispe (), aek6.io@gmail.com
 *   Organization:  
 *
 * =============================================================================
 */

#include "btree.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void binarizar() {
    ifstream in("/home/santiago/BTreeV/cities.txt");
    ofstream out("cubso.dat", ios::out | ios::binary);

    if (in.is_open()) {
        cout << "init binary data..." << endl;

        char data[200];
        int i = 0;
        double x,y;
        while (in.getline(data, 200, '\t')) {
            in>>x;
            in>>y;
            int key ;
            in>>key;
            out.write((char*)&key, sizeof(int));
            out.write(data, sizeof(char)*200);
            cout << "\r" << ++i;
        }
        in.close();
        cout << endl << "finish binary data..." << endl;
    }
}

int main(int args, char ** argv) {
    BTree<int> tree(4);
    tree.create((char*)"tree.dat");

   // binarizar();

    ifstream in("cubso.dat", ios::in | ios::binary);
    in.seekg(0L, ios::end);
    long size = in.tellg();
    long e = 0;
    int i = 0;
    int len = (sizeof(int) + sizeof(char)*200);
    char data[len];
    int key;
    
    cout << "init add BTree.." << endl;
    while (e < size) {
        in.seekg(e, ios::beg);
        in.read(data, len);
        key = ((int*)data)[0];
        tree.add(key, e);
        e += len;
        cout << "\r" << ++i;
        /* if (i > 500) break; */
    }
    cout << endl << "finish add BTree.." << endl;

    return 0;
    while (true) {
        int val;
        cout << "Buscar: ";
        cin >> val;
        if (val == -1) break;
        long pos = tree.find(val);
        if (pos == -1) cout << "Not Found: " << val << endl;
        else {
            in.seekg(pos, ios::beg);
            in.read(data, len);
            key = ((int*)data)[0];
            cout << "DISK:\t" << pos << endl;
            cout << "KEY:\t" << key << endl;
            cout << "DATA:\t" << (data+sizeof(int)) << endl;
        }
    }

    in.close();

    /* tree.add(10000000); */
    /* tree.add(10100000); */
    /* tree.add(10101500); */
    /* tree.add(10101501); */
    /* tree.add(10101502); */
    /* tree.add(10101504); */
    /* tree.add(10101505); */
    /* for (char i = 'a'; i <= 'z'; i++) */ 
    /*     tree.add(i); */


    /* tree.add("juan"); */
    /* tree.add("ana"); */
    /* tree.add("maria"); */
    /* tree.add("pipila"); */
    /* tree.add("luna"); */
    /* tree.add("mirana"); */
    /* tree.add("lina"); */
    /* tree.add("yuki"); */

    /* for (char i = 'a'; i <= 'z'; i++) */ 
    /*     tree.add(i); */

    /* for (int i = 1; i <= atoi(argv[1]); i++) */
    /* for (int i = atoi(argv[1]); i > 0; i--) */
        /* tree.add(i); */
    /* tree.add(0); */

    /* tree.dot((char*)"btree.dot"); */
    /* system("dot -Tpng btree.dot -o btree.png && feh btree.png"); */

    /* tree.destroy(); */

    return 0;
}
