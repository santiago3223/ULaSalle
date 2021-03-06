/*
 * Puzzle.cpp
 *
 *  Created on: size - 1size de nov. de size - 1015
 *      Author: santiago
 */

#include "Puzzle.h"

Puzzle::Puzzle(int size) {
	this->size = size;
	CrearPuzzleAleatorio(size);
}

int Puzzle::getCantidadMovimientos() const {
	return cantidadMovimientos;
}

void Puzzle::setCantidadMovimientos(int cantidadMovimientos) {
	this->cantidadMovimientos = cantidadMovimientos;
}

int* Puzzle::getDatos() const {
	return datos;
}

void Puzzle::setDatos(int* datos) {
	this->datos = datos;
}

int Puzzle::getPosActual() const {
	return posActual;
}

void Puzzle::setPosActual(int posActual) {
	this->posActual = posActual;
}

int Puzzle::getSize() const {
	return size;
}

void Puzzle::setSize(int size) {
	this->size = size;
}

Puzzle::Puzzle(char* items, int size) {
}

void Puzzle::CrearPuzzleAleatorio(int size) {
	datos = new int[size*size];

	for(int i = 1; i<=size*size ; i++){
		datos[i-1] = i;
	}
	datos[size*size-1] = 0;
	posActual = size*size-1;
	srand (time(0));
	for(int i = 0 ; i< 25 ; i++){
	MezclarPuzzle();
	}
	cantidadMovimientos= 0;
	pasos.push_back(datos);
	ImprimirPaso(0);
}

void Puzzle::MezclarPuzzle(){

	int num = rand() % 2;
	if(posActual % size != size - 1 && num == 1){
		datos[posActual] = datos[posActual+1];
		datos[posActual+1] = 0;
		posActual++;
	}
	else if(posActual % size != 0 && num == 1){
		datos[posActual] = datos[posActual-1];
		datos[posActual-1] = 0;
		posActual--;
	}
	else if((int)(posActual / size) != 0 && num == 0){
		datos[posActual] = datos[posActual-size];
		datos[posActual-size] = 0;
		posActual-=size;
	}
	else if((int)(posActual / size) != size - 1 && num == 0){
		datos[posActual] = datos[posActual+size];
		datos[posActual+size] = 0;
		posActual+=size;
	}

}

void Puzzle::ResolverPuzzle() {
	int * q = datos;
	while(Similitud(q) < size*size -1){
		//cout<<Similitud(q)<<endl;
		int * p1 = new int[size*size];
		int * p2 = new int[size*size];
		int * p3 = new int[size*size];
		int * p4 = new int[size*size];
		memcpy(p1,q,sizeof(int)*size*size);
		memcpy(p2,q,sizeof(int)*size*size);
		memcpy(p3,q,sizeof(int)*size*size);
		memcpy(p4,q,sizeof(int)*size*size);
		int num= 0;
		int sim= 0;
		if(posActual % size != size - 1){
			p1[posActual] = p1[posActual+1];
			p1[posActual+1] = 0;
			sim = Similitud(p1);
		}
		if(posActual % size != 0){
			p2[posActual] = p2[posActual-1];
			p2[posActual-1] = 0;
			if(Similitud(p2)>sim){
				sim = Similitud(p2);
				num = 1;
			}
		}
		if((int)(posActual / size) != 0){
			p3[posActual] = p3[posActual-size];
			p3[posActual-size] = 0;
			if(Similitud(p3)>sim) {
				sim = Similitud(p3);
				num = 2;
			}
		}
		if((int)(posActual / size) != size - 1){
			p4[posActual] = p4[posActual+size];
			p4[posActual+size] = 0;
			if(Similitud(p4)>sim)num=3;
		}

		switch (num){
		case 0:
			pasos.push_back(p1);
			posActual++;
			q = p1;
			delete p2;
			delete p3;
			delete p4;
			break;
		case 1:
			pasos.push_back(p2);
			posActual--;
			q = p2;
			delete p1;
			delete p3;
			delete p4;
			break;
		case 2:
			pasos.push_back(p3);
			posActual-=size;
			q = p3;
			delete p2;
			delete p1;
			delete p4;
			break;
		case 3:
			pasos.push_back(p4);
			posActual+=size;
			q = p4;
			delete p2;
			delete p3;
			delete p1;
			break;
		}

		cantidadMovimientos++;
		ImprimirPaso(cantidadMovimientos);
	}

}

void Puzzle::ImprimirPaso(int num) {
	for (int i = 0;i<size;i++){
		for(int e = 0; e<size;e++){
			cout<<pasos[num][i*size+e]<<"-";
		}
		cout<<endl;
	}
	cout<<endl;
}

int Puzzle::Similitud(int * dat) {
	int res = 0;
	for(int i = 0; i< size*size; i++){
		if(dat[i] == i+1)res++;
	}
	return res;
}

Puzzle::~Puzzle() {
	// TODO Auto-generated destructor stub
}

