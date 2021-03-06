/*
 * Puzzle.h
 *
 *  Created on: 23 de nov. de 2015
 *      Author: santiago
 */

#ifndef PUZZLE_H_
#define PUZZLE_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Puzzle {
public:
	int cantidadMovimientos;
	Puzzle(int size);
	Puzzle(char * items, int size);
	int getCantidadMovimientos() const;
	void setCantidadMovimientos(int cantidadMovimientos);
	int* getDatos() const;
	void setDatos(int* datos);
	int getPosActual() const;
	void setPosActual(int posActual);
	int getSize() const;
	void setSize(int size);
	void ImprimirPaso(int i);
	void ResolverPuzzle();
	virtual ~Puzzle();
private:
	int size;
	int posActual;
	int * datos;
	vector<int*> pasos;
	void CrearPuzzleAleatorio(int size);
	void MezclarPuzzle();
	int Similitud(int * dat);

};

#endif /* PUZZLE_H_ */
