/*
 * =============================================================================
 *
 *       Filename:  page.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25/11/15 07:49:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kelvin Helmut Provincia Quispe (), aek6.io@gmail.com
 *   Organization:  
 *
 * =============================================================================
 */

#ifndef PAGE_H
#define PAGE_H

#include <string.h>
#include <iostream>

using namespace std;

typedef char Byte;

template<class T>
class Page {
    public:
        Page(int k) : k(k), b(0), keys(new T[k]), links(new long[k+1]), data(new long[k]) {
            for (int i = 0; i <= k; i++)
                links[i] = 0;
        }

        Page<T> * add(T & key, long & dat, int i) {
            if (b < k) {
                if (i < b) {
                    memcpy((T*)(keys+i+1), (T*)(keys+i), sizeof(T)*(b-i));
                    memcpy((long*)(links+i+2), (long*)(links+i+1), sizeof(long*)*(b-i));
                    memcpy((long*)(data+i+1), (long*)(data+i), sizeof(long*)*(b-i));
                }
                keys[i] = key;
                data[i] = dat;
                b++;
            } else {
                T tmp = key;
                long link = 0;
                long datt = dat;
                if (i == k-1) {
                    tmp = keys[k-1];
                    keys[i] = key;
                    link = links[k];
                    datt = data[k-1];
                    data[i] = dat;
                } else if (i < k) {
                    tmp = keys[k-1];
                    memcpy((T*)(keys+i+1), (T*)(keys+i), sizeof(T)*(k-i-1));
                    link = links[k];
                    memcpy((long*)(links+i+2), (long*)(links+i+1), sizeof(long*)*(b-i-1));
                    keys[i] = key;
                    datt = data[k-1];
                    memcpy((long*)(data+i+1), (long*)(data+i), sizeof(long*)*(k-i-1));
                    data[i] = dat;
                }

                // TODO: cambiar a b+1 para abarcar impares
                b /= 2;

                Page<T> * nueva = new Page<T>(k);
                memcpy((T*)nueva->keys, (T*)(keys+k/2+1), sizeof(T)*(k/2-1));
                nueva->keys[k/2 -1] = tmp;
                nueva->b = k/2;
                memcpy((long*)nueva->links, (long*)(links+k/2+1), sizeof(long*)*(k/2));
                nueva->links[k/2] = link;
                memcpy((long*)nueva->data, (long*)(data+k/2+1), sizeof(long*)*(k/2-1));
                nueva->data[k/2-1] = datt;
                
                key = keys[k/2];
                dat = data[k/2];
                return nueva;
            }
            return 0;
        }

        Byte * serialize() {
            Byte * serialized = new Byte[getSerializedSize()];
            ((int*)serialized)[0] = k;
            ((int*)serialized)[1] = b;

            memcpy(serialized + sizeof(int)*2, keys, sizeof(T)*k);
            memcpy(serialized + sizeof(int)*2 + sizeof(T)*k, links, sizeof(long)*(k+1));
            memcpy(serialized + sizeof(int)*2 + sizeof(T)*k + sizeof(long)*(k+1), data, sizeof(long)*k);

            return serialized;
        }

        void unserialize(Byte * data) {
            /* cout << "init unserialize" << endl; */
            k = ((int*)data)[0];
            b = ((int*)data)[1];
            /* cout << k << endl; */
            /* cout << b << endl; */

            /* cout << "a" << endl; */
            memcpy(keys, data + sizeof(int)*2, sizeof(T)*k);
            /* cout << "a" << endl; */
            memcpy(links, data + sizeof(int)*2 + sizeof(T)*k, sizeof(long)*(k+1));
            memcpy(this->data, data + sizeof(int)*2 + sizeof(T)*k + sizeof(long)*(k+1), sizeof(long)*k);
            /* cout << "a" << endl; */

            if (data) delete [] data;
            /* cout << "end unserialize" << endl; */
        }

        unsigned long getSerializedSize() {
            return sizeof(int)*2 + sizeof(T)*k + sizeof(long)*(k+1) + sizeof(long)*k;
        }

    /* private: */
        int k, b;
        T * keys;
        /* Page ** links; */
        long * links;
        long * data;
};

#endif
