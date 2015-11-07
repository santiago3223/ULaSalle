#include <iostream>
#include <queue>
#include <list>
#include <stack>
#include <limits>
#include <vector>
using namespace std;


template<class V,  class E>
class Vertex;


template<class V,  class E>
class Arista
{
   public:
     E               m_Dato;
     Vertex<V,E>  *  m_pIni;
     Vertex<V,E>  *  m_pDes;
   public:
      Arista(){};
      Arista(E a, Vertex<V,E> * p =0, Vertex<V,E> * i =0)
      {
           m_Dato = a;
           m_pIni = i;
           m_pDes = p;
      }


    bool operator==(Arista<V,E> & Ar)
    {
       return  m_Dato == Ar.m_Dato;
    }

    bool operator>(const Arista<V,E> & Ar)const
    {
       return  m_Dato > Ar.m_Dato;
    }

    bool operator<(const Arista<V,E> & Ar)const
    {
       return  m_Dato < Ar.m_Dato;
    }

};

template<class V,  class E>
class Vertex
{
   public:
     V   m_Dato;
     list< Arista <V,E> >  m_Aristas;
   public:
    Vertex(){};
    Vertex(V d)
    {
        m_Dato = d;
    }

    bool operator==(Vertex<V,E> & Ver)
    {
       return  m_Dato == Ver.m_Dato;
    }

    bool operator>(Vertex<V,E> & Ver)
    {
       return  m_Dato > Ver.m_Dato;
    }

    bool operator<(Vertex<V,E> & Ver)
    {
       return  m_Dato < Ver.m_Dato;
    }

    void print()
    {
        typedef typename list< Arista<V,E> >::iterator ITERATOR;
        ITERATOR it = m_Aristas.begin();
        for( ; it!= m_Aristas.end(); ++it)
            cout<<m_Dato << " (" << it->m_Dato << ")" <<it->m_pDes->m_Dato <<endl;

    }
};


template<class V, class E>
class Grafo
{
private:
     list< Vertex<V,E> >   m_grafito;
public:
    Grafo(){};
    void Add_Vertex(V v1)
    {
    	if(find_vertex(v1) != 0)return;
         m_grafito.push_back(Vertex<V,E>(v1));

    }

    Vertex<V,E> *   find_vertex(V v)
    {
        Vertex<V,E>  tmp(v);
        typedef typename list< Vertex<V,E> >::iterator ITERATOR;
        ITERATOR it = m_grafito.begin();
        for( ; it != m_grafito.end(); ++it)
        {
            if ( tmp == *it)
                return &(*it);
        }

        return 0;

    }

    void print()
    {

        typedef typename list< Vertex<V,E> >::iterator ITERATOR;
        ITERATOR it = m_grafito.begin();
        for( ; it != m_grafito.end(); ++it)
                 it->print();
    }

    void Add_Arista(V v1,  V v2, E ar)
    {
         Vertex<V,E>  * origen = find_vertex(v1);
         Vertex<V,E>  * destino = find_vertex(v2);
         if (origen != 0 && destino != 0)
         {
               Arista<V,E>  Aris(ar,destino,origen);
               origen->m_Aristas.push_back(Aris);
         }
    }

    int GetIndice(V v){
    	typedef typename list< Vertex<V,E> >::iterator ITERATORV;
    	ITERATORV itv = m_grafito.begin();
    	for(int cont =0 ; itv != m_grafito.end(); ++itv){
    		if(itv->m_Dato == v)
    			return cont;
    		cont++;
    	}
    	return 0;
    }

    bool TieneCeros(vector<int> v){
    	for(int i = 0 ; i< m_grafito.size();i++){
    		if(v[i]==0)return true;
		}
    	return false;
    }

    int MenorDikjstra(vector<int> C, vector<int> D){
    	int min = numeric_limits<int>::max();
    	int ind = 0;
    	for(int i = 0 ; i< m_grafito.size();i++){
			if(C[i]==0){
				//cout<<D[i]<<endl;
				if(D[i]<min){
					min = D[i];
					ind = i;
				}
			}
		}
    	return ind;
    }


    void Dikjstra(V v){
    	vector<int> C(m_grafito.size());
    	vector<E> D(m_grafito.size());
    	Vertex<V,E>  * origen = find_vertex(v);
    	if(origen ==0) return;

    	C[GetIndice(v)] = 1;
    	for(int i = 0 ; i< m_grafito.size();i++){
    		D[i]=numeric_limits<int>::max();
    	}
    	typedef typename list< Vertex<V,E> >::iterator ITERATORV;
    	typedef typename list< Arista<V,E> >::iterator ITERATORA;
		ITERATORV itv = m_grafito.begin();

		for(int cont =0 ; itv != m_grafito.end(); ++itv){
			 ITERATORA ita = origen->m_Aristas.begin();
			 for( ; ita!= origen->m_Aristas.end(); ++ita){
				 if(ita->m_pDes->m_Dato == itv->m_Dato){
					D[cont]=ita->m_Dato;
				 }
			 }
			 cont++;
		}
		while(TieneCeros(C)){
			int p = MenorDikjstra(C,D);
			C[p] = 1;
			ITERATORV itv1 = m_grafito.begin();
			for(int cont = 0 ; cont< p; cont++){
				itv1++;
			}
			ITERATORA ita1 = itv1->m_Aristas.begin();
			for( ; ita1!= itv1->m_Aristas.end(); ++ita1){
				for(int i = 0 ; i<m_grafito.size();i++){
					if(GetIndice(ita1->m_pDes->m_Dato)== i){
						if(ita1->m_Dato + D[p] < D[i] && C[i] == 0){
							if(D[p] != numeric_limits<int>::max()){
							D[i]=ita1->m_Dato+D[p];
							}
						 }
					}
				}
			 }
		}


		itv = m_grafito.begin();
		for(int cont =0 ; itv != m_grafito.end(); ++itv){
			cout<<v << " - "<<itv->m_Dato <<" - "<<D[cont]<<endl;
			cont++;
		}

    }

    bool formaCiclo(vector<Vertex<V,E> *> vec, V dato){
    	for(int i =0; i<m_grafito.size(); i++){
    		if(vec[i] != 0 && vec[i]->m_Dato == dato){
    			return true;
    		}
    	}
    	return false;
    }

    bool formaCiclo(Arista<V,E>  a){
    	typedef typename list< Vertex<V,E> >::iterator ITERATORV;
    	ITERATORV itv = m_grafito.begin();
    	for(; itv != m_grafito.end(); ++itv){
			if(itv->m_Dato == a.m_pDes->m_Dato){
				return true;
			}
		}
    	return false;

    }

    Grafo<V,E> Kruskal(){
    	int cant = 0;
    	Grafo<V,E> S;
    	vector<Vertex<V,E> *> nodos(m_grafito.size());
    	for(int e =0; e<m_grafito.size(); e++){
			nodos[e]=0;
		}
    	typedef typename list< Vertex<V,E> >::iterator ITERATORV;
		typedef typename list< Arista<V,E> >::iterator ITERATORA;
		priority_queue<Arista<V,E> ,std::vector<Arista<V,E> >, greater<Arista<V,E> > >minHeap;

		ITERATORV itv = m_grafito.begin();
		for(; itv != m_grafito.end(); ++itv){

			 ITERATORA ita = itv->m_Aristas.begin();
			 for( ; ita!= itv->m_Aristas.end(); ++ita){
				 minHeap.push(*ita);
			}
		}

		while(cant < m_grafito.size() -1 && !minHeap.empty() ){
			//if(!S.formaCiclo(minHeap.top())){
			if(!formaCiclo(nodos, minHeap.top().m_pDes->m_Dato)){
				int i = 0;
				for(; i<m_grafito.size(); i++){
					if(nodos[i] == 0){
						break;
					}
				}
				//cout<<i<<endl;
				nodos[i] = minHeap.top().m_pDes;
				cant++;
				S.Add_Vertex(minHeap.top().m_pIni->m_Dato);
				S.Add_Vertex(minHeap.top().m_pDes->m_Dato);
				S.Add_Arista(minHeap.top().m_pIni->m_Dato,minHeap.top().m_pDes->m_Dato,minHeap.top().m_Dato);
			}
			minHeap.pop();
		}
		return S;
    }

    Grafo<V,E>  Prim(){
    	typedef typename list< Arista<V,E> >::iterator ITERATORA;
        	int cant = 0;
        	Grafo<V,E> S;
        	Vertex<V,E> *p = &m_grafito.front();
        	vector<Vertex<V,E> *> nodos(m_grafito.size());
        	nodos[cant] = p;
        	S.Add_Vertex(p->m_Dato);
        	cant++;
        	priority_queue<Arista<V,E> ,std::vector<Arista<V,E> >, greater<Arista<V,E> > >minHeap;
        	while(cant < m_grafito.size() ){
        		ITERATORA ita = p->m_Aristas.begin();
				 for( ; ita!= p->m_Aristas.end(); ++ita){
					 minHeap.push(*ita);
					 //cout<<ita->m_Dato<<"-";
				 }
				 //cout<<endl;
				 //cout<<minHeap.top().m_Dato<<endl;
				 if(!formaCiclo(nodos, minHeap.top().m_pDes->m_Dato)){
					 p = minHeap.top().m_pDes;
					 //cout<<minHeap.top().m_Dato<<endl;
					 //cout<<p->m_Dato<<endl;
					 S.Add_Vertex(p->m_Dato);
					 S.Add_Arista(minHeap.top().m_pIni->m_Dato, minHeap.top().m_pDes->m_Dato, minHeap.top().m_Dato) ;
					 nodos[cant] = p;
					 cant++;
				 }
				 minHeap.pop();
        	}
    		return S;
    }

    void profundidad(){
    	typedef typename list< Arista<V,E> >::iterator ITERATORA;
    	stack<Vertex<V,E> *> s;
    	int cant = 0;
    	vector<Vertex<V,E> *> nodos(m_grafito.size());
    	s.push(&m_grafito.front());
		nodos[cant] = &m_grafito.front();
		cant++;
    	while (!s.empty()) {
    		Vertex<V,E> * p = s.top();
    		ITERATORA ita = p->m_Aristas.begin();
    		cout<<p->m_Dato<<" ";
    		s.pop();
    		for( ; ita!= p->m_Aristas.end(); ++ita){
    			if(!formaCiclo(nodos, ita->m_pDes->m_Dato)){
    	    		nodos[cant] = ita->m_pDes;
    	    		cant++;
    				s.push(ita->m_pDes);
    			}
		 	}

    	  }
    }

    void amplitud(){
        	typedef typename list< Arista<V,E> >::iterator ITERATORA;
        	queue<Vertex<V,E> *> s;
        	int cant = 0;
        	vector<Vertex<V,E> *> nodos(m_grafito.size());
        	s.push(&m_grafito.front());
        	while (!s.empty()) {
        		Vertex<V,E> * p = s.front();
        		ITERATORA ita = p->m_Aristas.begin();
        		cout<<p->m_Dato<<" ";

        		s.pop();
        		for( ; ita!= p->m_Aristas.end(); ++ita){
        			if(!formaCiclo(nodos, ita->m_pDes->m_Dato)){
        				nodos[cant] = ita->m_pDes;
        				    	    		cant++;
        				s.push(ita->m_pDes);
        			}
    		 	}

        	  }
        }
};

int main()
{
    Grafo<int,int>  G;
    /*G.Add_Vertex("Lima");
    G.Add_Vertex("Arequipa");
    G.Add_Vertex("Cusco");
    G.Add_Vertex("Puno");
    G.Add_Arista("Lima","Arequipa",800);
    G.Add_Arista("Puno","Arequipa",200);
    G.Add_Arista("Arequipa","Puno",200);
    //G.print();
     *
     */
    G.Add_Vertex(0);
    G.Add_Vertex(1);
    G.Add_Vertex(2);
    G.Add_Vertex(3);
    G.Add_Vertex(4);
    G.Add_Vertex(5);
    G.Add_Vertex(6);
    G.Add_Vertex(7);
    G.Add_Vertex(8);
    G.Add_Arista(0,1,4);
    G.Add_Arista(0,7,8);
    G.Add_Arista(1,2,8);
    G.Add_Arista(1,7,11);
    G.Add_Arista(2,8,2);
    G.Add_Arista(2,3,7);
    G.Add_Arista(3,4,9);
    G.Add_Arista(3,5,10);
    G.Add_Arista(5,2,4);
    G.Add_Arista(5,4,10);
    G.Add_Arista(6,5,2);
    G.Add_Arista(6,8,6);
    G.Add_Arista(7,6,1);
    G.Add_Arista(7,8,7);

    G.Dikjstra(0);
    //G.Kruskal();

    //G.Prim().print();
    //G.profundidad();
    //G.amplitud();
    cout << "Hello world!" << endl;
    return 0;
}
