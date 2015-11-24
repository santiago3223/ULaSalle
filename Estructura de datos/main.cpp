/*
 * main.cpp
 *
 *  Created on: 16 de nov. de 2015
 *      Author: santiago
 */
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <fstream>
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

		NodoPatricia(string dato, bool fin){
			p_dato = dato;
			finPalabra = fin;
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
				q->finPalabra = false;
				q->p_son[1] = new NodoPatricia(datoAnterior,true);

				if(q->p_son[1]->p_dato[0] > dato[0]){
					q->p_son[1]->p_son[0] = new NodoPatricia(dato, true);
				}else{
					q->p_son[1]->p_son[2] = new NodoPatricia(dato, true);
				}
			}else{
				if(q->p_dato[0] > dato[0]){
					q->p_son[0] = new NodoPatricia(dato,true);
				}else{
					q->p_son[2] = new NodoPatricia(dato,true);
				}
			}
		}

		vector<string> Find(string dato){
//				NodoPatricia * p;
//				bool mod = 0;
//				int i = 0;
//				return Find(dato, p, mod, i);
			vector<string> v ;
			NodoPatricia * p;
			string s = "";
			if(Find(dato, p,s)){

			}
			v = List(p);
			for(int i = 0 ; i< v.size(); i++){
				v[i] = s + v[i];
			}
			return v;
		}

		vector<string> List(NodoPatricia * p){

			vector<string> v ;
			if (p->finPalabra){
				v.push_back(p->p_dato);
			}
			if(p->p_son[1]){
				vector <string> va1 = List(p->p_son[1]);
				for(int e = 0; e<va1.size(); e++){
					//cout<<p->p_dato+ va1[e]<<endl;
					v.push_back(p->p_dato +va1[e]);
				}
				if(p->p_son[1]->p_son[0]){
					vector <string> va1 = List(p->p_son[1]->p_son[0]);
					for(int e = 0; e<va1.size(); e++){
						v.push_back(p->p_dato + va1[e]);
					}
				}else if(p->p_son[1]->p_son[2]){
					vector <string> va1 = List(p->p_son[1]->p_son[2]);
					for(int e = 0; e<va1.size(); e++){
						v.push_back(p->p_dato  + va1[e]);
					}
				}
			}else if(p->p_son[0]){
				if(p->p_son[0]->p_son[0]){
					vector <string> va1 = List(p->p_son[0]->p_son[0]);
					for(int e = 0; e<va1.size(); e++){
						v.push_back( va1[e]);
					}
				}else if(p->p_son[0]->p_son[2]){
					vector <string> va1 = List(p->p_son[0]->p_son[2]);
					for(int e = 0; e<va1.size(); e++){
						v.push_back( va1[e]);
					}
				}
			} else if(p->p_son[2]){
				if(p->p_son[2]->p_son[0]){
					vector <string> va1 = List(p->p_son[2]->p_son[0]);
					for(int e = 0; e<va1.size(); e++){
						v.push_back( va1[e]);
					}
				}else if(p->p_son[2]->p_son[2]){
					vector <string> va1 = List(p->p_son[2]->p_son[2]);
					for(int e = 0; e<va1.size(); e++){
						v.push_back( va1[e]);
					}
				}
			}
			return v;
		}
		bool Find(string &dato, NodoPatricia *& q, string & res){
			if(!raiz){
				return false;
			}
			q = raiz;
			while(dato.size()>0){
				int i = 0;
				int mod = 0;
				while( q->p_dato[i] && q->p_dato[i] == dato[i]){
					if(i >= dato.size() - 1){
						return false;
					}
					res = res + dato[i];
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

		bool Find(string &dato, NodoPatricia *& q, bool &mod, int & i){
			if(!raiz){
				return false;
			}
			q = raiz;
			while(dato.size()>0){
				i = 0;
				mod = 0;
				while( q->p_dato[i] && q->p_dato[i] == dato[i] && i < dato.size()){
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
					if(dato.size()>0 ){
					return false;
					}
				}
			}
			return true;

		}
//		bool Find(string dato, NodoPatricia * & q, int & cant, int & cant2, bool & mod){
//			if(!raiz){
//				return false;
//			}
//			q = raiz;
//			cant = 0;
//			while(cant< dato.size()){
//				mod = 0;
//				cant2 = 0;
//				while(q->p_dato[cant2] == dato[cant]){
//					cant++;
//					cant2++;
//					mod = 1;
//				}
//				if(mod && q->p_son[1]){
//					q = q->p_son[1];
//				} else if(q->p_son[0] && q->p_dato[0] > dato[cant]){
//					q = q->p_son[0];
//				}else if(q->p_son[2] && q->p_dato[0] < dato[cant]){
//					q = q->p_son[2];
//				}else {
//					return false;
//				}
//			}
//			return true;
//		}

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
		char *obj;
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
			//p->obj = dato[i];
			//cout<<i<<"-"<< dato[i]<< endl;
			q = p;
			if(i == strlen(dato)-1){
				//q->obj = new char;
				q->obj = new char[100];
				strcpy(dato,q->obj);
			}
		}

	}

	vector<string> Find (char dato[]){
		vector <string> v;
		Pagina * q = raiz;
		for(int i = 0; i < strlen(dato);i++){
			if(q->paginas[(int)(dato[i])-(int)'a'] ){
				q = q->paginas[(int)(dato[i])-(int)'a'];
				//cout<< q->obj <<endl;
			}else{
				return v;
			}
		}

		//cout<<"llego aqui"<<q->obj<<endl;

		return List(q);
	}

	vector<string> List (Pagina * q){
		//cout<<q->obj<<endl;
		vector <string> v;

		if (q->obj){
			stringstream ss;
			string s;
			ss<<q->obj;
			ss>>s;
			v.push_back(s);
		}
		for(int i = 0; i < size;i++){
			if(q->paginas[i]){
				vector <string> va1 = List(q->paginas[i]);
				for(int e = 0; e<va1.size(); e++){
					v.push_back(va1[e]);
				}
			}
		}

//		for(int i = 0; i < v.size();i++){
//			v[i] = q->obj + v[i];
//		}
//		if(v.size() == 0){
//
//			stringstream ss;
//			string s;
//			ss<<q->obj;
//			ss>>s;
//			//cout<<s<<endl;
//			v.push_back(s);
//		}
		return v;
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

	//dig.Add("angola");
	//dig.Add("amana");
	//dig.Add("ababol");
	//dig.Add("abacero");
	//dig.Add("abaco");
//	//dig.Add("abadejo");
	ifstream file("es_ES.dic");
     char buffer;
      while(!file.eof())
      {
    	  //buffer = new char[100];
    	  file>>buffer;
    	  //cout<<buffer<<endl;
    	  dig.Add(buffer);
      }

      dig.printDot("archivo.dot");

      vector<string>  v = dig.Find("zap");



//	Patricia pat;
//	pat.Add("amanecer");
//	pat.Add("anaconda");
//	pat.Add("amigo");
//	pat.Add("amistad");
//	pat.Add("amorio");
//	//pat.Add("amparo");
//	//cout<<pat.Find("amigoso")<<endl;
//	vector<string>  v = pat.Find("am");
	//pat.printDot("archivo.dot");

	for (int i = 0 ; i < v.size(); i++){
			cout <<v[i]<< endl;
	}
	system("dot -Tpng archivo.dot -o archivo.png");
	//Pagina<int> Pagina(10);
	//cout<<"aaa"<<endl;

 return 0;
}
