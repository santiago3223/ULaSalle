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

class NodoPatricia{
	public:
		string p_dato;
		bool finPalabra;
		NodoPatricia* p_son[3];
		NodoPatricia(){
			finPalabra = false;
			p_son[0] = p_son[1] = p_son[2] = 0;
		}
		NodoPatricia(string dato){
			p_dato = dato;
			finPalabra = false;
			p_son[0] = p_son[1] = p_son[2] = 0;
		}
		void printDot(ofstream& os)
		{
			if(p_son[0]){
				os<<p_dato<<"->"<<p_son[0]->p_dato<<endl;
				p_son[0]->printDot(os);
			}
			if(p_son[1]){
					os<<p_dato<<"->"<<p_son[1]->p_dato<<endl;
					p_son[1]->printDot(os);
				}
			if(p_son[2]){
					os<<p_dato<<"->"<<p_son[2]->p_dato<<endl;
					p_son[2]->printDot(os);
				}
		}
};

class Patricia{
	public:
		NodoPatricia * raiz;
		Patricia(){
			raiz = 0;
		}
		void Add(string dato){
			NodoPatricia* q = raiz;
			int cant = 0;
			bool mod;
			if(Find(dato,q,mod, cant)){
				return;
			}
			if(!q){
				raiz = new NodoPatricia(dato);
				return;
			}


			if(mod){
				string datoAnterior = q->p_dato.substr(cant,(q->p_dato.size()) -cant);
				q->p_dato = q->p_dato.substr(0,cant );
				q->p_son[1] = new NodoPatricia(datoAnterior);

				if(q->p_son[1]->p_dato[0] > dato[0]){
					q->p_son[1]->p_son[0] = new NodoPatricia(dato);
				}else{
					q->p_son[1]->p_son[2] = new NodoPatricia(dato);
				}
			}else{
				if(q->p_dato[0] > dato[0]){
					q->p_son[0] = new NodoPatricia(dato);
				}else{
					q->p_son[2] = new NodoPatricia(dato);
				}
			}
		}

		bool Find(string dato){
				NodoPatricia * p;
				bool mod = 0;
				int i = 0;
				return Find(dato, p, mod, i);
			}

		bool Find(string &dato, NodoPatricia *& q, bool &mod, int & i){
			if(!raiz){
				return false;
			}
			q = raiz;
			while(dato.size()>0){
				i = 0;
				mod = 0;
				while( q->p_dato[i] && q->p_dato[i] == dato[i]){
					i++;
					mod = 1;
				}
				dato = dato.substr(i, dato.size()- i);
				if(mod && q->p_son[1]){
					q = q->p_son[1];
				} else if(!mod && q->p_son[0] && q->p_dato[0] > dato[0]){
					q = q->p_son[0];
				}else if(!mod && q->p_son[2] && q->p_dato[0] < dato[0]){
					q = q->p_son[2];
				}else {
					if(dato.size()>0){
					return false;
					}
				}
			}
			return true;

		}
		bool Find(string dato, NodoPatricia * & q, int & cant, int & cant2, bool & mod){
			if(!raiz){
				return false;
			}
			q = raiz;
			cant = 0;
			while(cant< dato.size()){
				mod = 0;
				cant2 = 0;
				while(q->p_dato[cant2] == dato[cant]){
					cant++;
					cant2++;
					mod = 1;
				}
				if(mod && q->p_son[1]){
					q = q->p_son[1];
				} else if(q->p_son[0] && q->p_dato[0] > dato[cant]){
					q = q->p_son[0];
				}else if(q->p_son[2] && q->p_dato[0] < dato[cant]){
					q = q->p_son[2];
				}else {
					return false;
				}
			}
			return true;
		}

		void printDot(char* p)
			{
				ofstream file(p);
				file<<"digraph {"<<endl;
				raiz->printDot(file);
				file<<" }"<<endl;
			}


};
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
		NodoPatricia * p;
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

	//Patricia pat;
	//pat.Add("amanecer");
	//pat.Add("amigo");
	//pat.Add("amiga");
	//pat.Add("amparo");
	//cout<<pat.Find("amigoso")<<endl;

	//pat.printDot("archivo.dot");
	system("dot -Tpng archivo.dot -o archivo.png");
	//Pagina<int> Pagina(10);
	cout<<"aaa"<<endl;

 return 0;
}
