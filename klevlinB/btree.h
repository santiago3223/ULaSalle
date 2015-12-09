/*
 * =============================================================================
 *
 *       Filename:  btree.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/11/15 09:25:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kelvin Helmut Provincia Quispe (), aek6.io@gmail.com
 *   Organization:  
 *
 * =============================================================================
 */

#ifndef BTREE_H
#define BTREE_H

#include "page.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

template<class T>
class BTree {
    public:
        ~BTree() {
        }
        BTree(int k) : k(k), root(0) {}
        BTree(char * file) : k(0), root(0) { load(file); }
        void add(T key, long dat);
        /* long add(T & key, long & root); */
        Page<T> * add(T & key, long & dat, long & root);
        long find(T key);
        long find(T & key, long & root);
        bool findB(T & key, Page<T> & page, int &);
        void dot(char * file) {
            /* cout << "en e dot" << endl; */
            ofstream out(file);
            out << "digraph G {" << endl;
            out << "node [shape=record]" << endl;
            dot(out, root);
            out << "}";
        }
        void create(char * file);
        void load(char * file);
        long write(Page<T> &);
        long write(Page<T> &, long);
        Byte * read(long, Page<T> &);
        /* void destroy() { destroy(root); } */
        /* void destroy(Page<T> *& root) { */
        /*     if (!root) return; */

        /*     if (root->links) { */
        /*         for (int i = 0; i <= root->b; i++) */
        /*             if (root->links[i]) destroy(root->links[i]); */
        /*         delete [] root->links; */
        /*     } */
        /*     if (root->keys) delete [] root->keys; */
        /*     delete root; */
        /* } */

    private:
        int k;
        /* Page<T> * root; */
        long root;
        char * file;

        void dot(ostream & out, long & root) {
            /* cout << root << endl; */
            Page<T> page(k);
            page.unserialize(read(root, page));

            /* cout << "el k " << page.k << endl; */
            /* cout << "el b " << page.b << endl; */

            out << "\"" << root << "\" [label=\"";
            int i;
            for (i = 0; i < page.b; i++) {
                /* cout << "value " << i << " " << page.keys[i] << endl; */
                out << "<" << i << ">" << page.keys[i] << "|";
            }
            for (i = page.b; i < k; i++)
                out << "<" << i << ">|";

            /* cout << "tamaño " << page.b << " it " << i << endl; */
            out << "<" << k << ">\"]" << endl;

            for (i = 0; i <= page.b; i++) {
                if (page.links[i]) {
                    out << "\"" << root << "\":" << i << "->"
                        << "\"" << page.links[i] << "\"" << endl;
                    dot(out, page.links[i]);
                }
            }
        }

        void changeRoot() {
            /* cout << "--cambiando root" << endl; */
            fstream fs(file, ios::out | ios::in | ios::binary);
            fs.seekp(0L, ios::beg);
            fs.write((char*)&root, sizeof(long));
            fs.close();
        }
        void readRoot() {
            ifstream fs(file, ios::in | ios::binary);
            char data[sizeof(long)];

            fs.seekg(0L, ios::beg);
            fs.read(data, sizeof(long));
            root = ((long*)data)[0];
            /* cout << "new root " << ((long*)data)[0] << endl; */
            /* cout << "new root " << root << endl; */
            fs.close();
        }
};

template<class T>
void BTree<T>::create(char * file) {
    this->file = file;
    ofstream fs(file, ios::out | ios::binary);

    Page<T> page(k);

    fs.seekp(0L, ios::beg);
    fs.write((char*)&root, sizeof(long));
    fs.write((char*)&k, sizeof(int));
    fs.close();

    root = write(page);
    changeRoot();
    /* fs.write(page.serialize(), page.getSerializedSize()); */

}

template<class T>
void BTree<T>::load(char * file) {
    this->file = file;
    ifstream fs(file, ios::in | ios::binary);

    char data[sizeof(long) + sizeof(int)];
    fs.read(data, sizeof(long) + sizeof(int));
    
    root = ((long*)data)[0];
    k = ((int*)(data + sizeof(long)))[0];

    /* cout << k << endl; */
    /* cout << root << endl; */

    fs.close();
}

template<class T>
void BTree<T>::add(T key, long dat) {
    /* cout << root << endl; */
    readRoot();
    /* cout << root  << endl; */
    Page<T> * nueva = add(key, dat, root);
    if (nueva) {
        Page<T> page(k);
        page.keys[0] = key;
        page.data[0] = dat;
        page.b++;
        page.links[0] = root;
        page.links[1] = write(*nueva);
        root = write(page);
        changeRoot();
    }
}

template<class T>
Page<T> * BTree<T>::add(T & key, long & dat, long & root) {
    /* cout << root << endl; */
    Page<T> page(k);
    page.unserialize(read(root, page));

    int i = 0;
    /* findB(key, page, i); */
    if (findB(key, page, i)) return 0;

    /* cout << "agregando.. " << key << " en " << i << endl; */

    if (page.links[i]) {
        /* cout << "en hijo" << endl; */
        Page<T> * cnew = add(key, dat, page.links[i]);
        if (cnew) {
            Page<T> * bnew = page.add(key, dat, i);
            if (bnew && i > k/2)
                bnew->links[i-k/2] = write(*cnew);
            else
                page.links[i+1] = write(*cnew);
            write(page, root);
            return bnew;
        }
        return 0;
    }
    Page<T> * pp = page.add(key, dat, i);
    write(page, root);
    /* cout << "agregado " << pp << endl; */
    return pp;
}

template<class T>
long BTree<T>::write(Page<T> & page) {
    ofstream fs(file, ios::out | ios::app | ios::binary);
    long p;

    fs.seekp(0L, ios::end);
    p = fs.tellp();
    /* cout << "nueva page en " << p << endl; */
    fs.write(page.serialize(), page.getSerializedSize());
    fs.close();

    return p;
}

template<class T>
long BTree<T>::write(Page<T> & page, long i) {
    /* cout << "cambiando page en " << i << endl; */
    fstream fs(file, ios::out | ios::in | ios::binary);

    fs.seekp(i, ios::beg);
    fs.write(page.serialize(), page.getSerializedSize());
    fs.close();

    return i;
}

template<class T>
Byte * BTree<T>::read(long i, Page<T> & page) {
    ifstream fs(file, ios::in | ios::binary);
    Byte * data = new Byte[page.getSerializedSize()];
    fs.seekg(i, ios::beg);
    fs.read(data, page.getSerializedSize());
    fs.close();

    return data;
}

template<class T>
long BTree<T>::find(T key) {
    return find(key, root);
}

template<class T>
long BTree<T>::find(T & key, long & root) {
    Page<T> page(k);
    page.unserialize(read(root, page));

    int i;
    if (findB(key, page, i)) return page.data[i];

    if (page.links[i])
        return find(key, page.links[i]);
    return -1;
}

template<class T>
bool BTree<T>::findB(T & key, Page<T> & page, int & i) {
    int ini = 0, end = page.b-1, mid;
    while (ini <= end) {
        mid = (ini+end)/2;
        i = mid;
        if (key == page.keys[mid]) return true;
        if (key < page.keys[mid])
            end = mid-1;
        else {
            ini = mid+1;
            i = ini;
        }
    }
    return false;
}

#endif
