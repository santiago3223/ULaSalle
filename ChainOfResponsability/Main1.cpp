/*
 * Main1.cpp
 *
 *  Created on: 5 de nov. de 2015
 *      Author: santiago
 */


#include <iostream>
#include <vector>
#include <ctime>
#include <stdlib.h>
using namespace std;

class Base
{
    Base *next; // 1. "next" pointer in the base class
  public:
    Base()
    {
        next = 0;
    }
    void setNext(Base *n)
    {
        next = n;
    }
    void add(Base *n)
    {
        if (next)
          next->add(n);
        else
          next = n;
    }
    // 2. The "chain" method in the base class always delegates to the next obj
    virtual void handle(int i)
    {
        next->handle(i);
    }
};

class Handler1: public Base
{
  public:
     /*virtual*/void handle(int i)
    {
        if (rand() % 3)
        {
            // 3. Don't handle requests 3 times out of 4
            cout << "H1 passsed " << i << "  ";
            Base::handle(i); // 3. Delegate to the base class
        }
        else
          cout << "H1 handled " << i << "  ";
    }
};

class Handler2: public Base
{
  public:
     /*virtual*/void handle(int i)
    {
        if (rand() % 3)
        {
            cout << "H2 passsed " << i << "  ";
            Base::handle(i);
        }
        else
          cout << "H2 handled " << i << "  ";
    }
};

class Handler3: public Base
{
  public:
     /*virtual*/void handle(int i)
    {
        if (rand() % 3)
        {
            cout << "H3 passsed " << i << "  ";
            Base::handle(i);
        }
        else
          cout << "H3 handled " << i << "  ";
    }
};

class IAprobador
{
public:
	IAprobador * next;
public:
	void setNext(IAprobador *aprobador){
		next = aprobador;
	}
	IAprobador* getNext(){
		return next;
	}
	virtual void solicitarPrestamo(int monto){
		next->solicitarPrestamo(monto);
	}
};

class EjecutivoDeCuenta : public IAprobador{
	public:
	void solicitarPrestamo(int monto){
		if (monto <= 10000){
			cout<<"Manejado por el Ejecutivo de Cuenta"<<endl;

		}else{
			next->solicitarPrestamo(monto);
		}
	}
};

class Lider : public IAprobador{
	public:
	void solicitarPrestamo(int monto){
		if (monto > 10000 && monto <= 50000){
			cout<<"Manejado por el Lider"<<endl;

		}else{
			next->solicitarPrestamo(monto);
		}
	}
};

class Gerente : public IAprobador{
	public:
	void solicitarPrestamo(int monto){
		if (monto > 50000 && monto <= 100000){
			cout<<"Manejado por el Gerente"<<endl;

		}else{
			next->solicitarPrestamo(monto);
		}
	}
};

class Director : public IAprobador{
	public:
	void solicitarPrestamo(int monto){
		if (monto >= 100000){
			cout<<"Manejado por el Director"<<endl;

		}
	}
};

class Banco: public IAprobador{
public:
	void solicitarPrestamo(int monto){
		IAprobador* ejecutivo = new EjecutivoDeCuenta();
		this->setNext(ejecutivo);

		IAprobador* lider = new Lider();
		ejecutivo->setNext(lider);

		IAprobador* gerente = new Gerente();
		lider->setNext(gerente);

		IAprobador* director = new Director();
		gerente->setNext(director);

		next->solicitarPrestamo(monto);
}
};

int main()
{
//  srand(time(0));
//  Handler1 root;
//  Handler2 two;
//  Handler3 thr;
//  root.add(&two);
//  root.add(&thr);
//  thr.setNext(&root);
//  for (int i = 1; i < 10; i++)
//  {
//    root.handle(i);
//    cout << '\n';
//  }
	Banco banco;
	banco.solicitarPrestamo(150000);

}

