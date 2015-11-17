/*
 * main.cpp
 *
 *  Created on: 16 de nov. de 2015
 *      Author: santiago
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Pagina{
	public:
		Pagina** paginas;
		int sizeAlfabeto;
		char* obj;
	Pagina(){

	}

	Pagina(int size){
		this->sizeAlfabeto = size;
		obj = 0;
		paginas = new Pagina*[size];
		for(int i = 0; i< size; i++){
			paginas[i] = 0;
		}
	}
	void printDot(ofstream& os)
	{
		os<<"\""<<this <<"\""<<"[shape=record, label=\"{{ ";
		if(this->paginas[0]){
					os<<(char)((int)'a');
			}else{
				os<<"0";
			}
		for(int i = 1; i<sizeAlfabeto; i++){
			if(this->paginas[i]){
			os<<"|"<<(char)(i+(int)'a');
			}else{
				os<<"|0";
			}
		}

		os<<"} } \"];"<<endl;

		for(int i = 0 ; i<sizeAlfabeto; i++){
			if(paginas[i]){
				paginas[i]->printDot(os);
				os<<"\""<<this<<"\""<<"->"<<"\""<<paginas[i]<<"\""<<endl;
				}
			}
		}

};

class Digital
{
	public:
	Pagina* raiz;
	int size;
	Digital(int size){
		this->size = size;
		raiz = 0;
	}

	void Add(char dato[]){
		Pagina * q;
		int i = 0;
		if(Find(dato, q, i)){
			return;
		}
		if(!raiz){
			raiz = q;
		}
		for(; i < strlen(dato);i++){
			Pagina * p = new Pagina(size);
			q->paginas[(int)(dato[i])-(int)'a']= p;
			q = p;
			if(i == strlen(dato)-1){
				q->obj = dato;
			}
		}

	}

	bool Find(char dato[], Pagina * & q, int & i){
		if(!raiz){
			q = new Pagina(size);
			return false;
		}
		q = raiz;
		for(; i < strlen(dato);i++){
			if(q->paginas[(int)(dato[i])-(int)'a'] ){
				q = q->paginas[(int)(dato[i])-(int)'a'];
			}else{
				return false;
			}

		}
		return true;
	}

	void printDot(char* p)
	{
		ofstream file(p);
		file<<"digraph {"<<endl;
//		file<<"\""<<raiz <<"\""<<"[shape=record, label=\"{{ ";
//		if(raiz->paginas[0]){
//			file<<(char)((int)'a');
//			}else{
//				file<<"0";
//			}
//		for(int i = 1; i<size; i++){
//			if(raiz->paginas[i]){
//			file<<"|"<<(char)(i+(int)'a');
//			}else{
//				file<<"|0";
//			}
//		}
//		file<<"} } \"];"<<endl;
		raiz->printDot(file);
		file<<" }"<<endl;
	}

};



int main()
{
	Digital dig(26);
	dig.Add("perro");
	dig.Add("pollo");
	dig.Add("pez");
	dig.printDot("archivo.dot");
	system("dot -Tpng archivo.dot -o archivo.png");
	//Pagina<int> Pagina(10);
	cout<<"aaa"<<endl;

 return 0;
}
