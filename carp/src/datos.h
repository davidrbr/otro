#include <fstream>
#include <vector>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

#ifndef DATOS_H_
#define DATOS_H_

class punto {
private:
   int id; //numero de cliente
   int x;
   int y;
   int demanda;
   vector <int> adyacentes; //lista de puntos adyacentes
   vector <int> demandas; //lista de las demandas de los arcos formados por los puntos adyacentes ordenados de forma que correspondan a los adyacentes
public:
   punto();
   punto(int aid, int ax, int ay, int ademanda);
   void insertar_adyacente(int ady);
   void imprimir_adyacentes();
   void imprimir_demandas();
   void insertar_demanda(int dmda);

	const vector<int>& getAdyacentes() const {
		return adyacentes;
	}

	void setAdyacentes(const vector<int>& adyacentes) {
		this->adyacentes = adyacentes;
	}

	int getDemanda() const {
		return demanda;
	}

	void setDemanda(int demanda) {
		this->demanda = demanda;
	}

	int getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

	const vector<int>& getDemandas() const {
		return demandas;
	}

	void setDemandas(const vector<int>& demandas) {
		this->demandas = demandas;
	}
};


class mdata {
private:
   bool alcanza;
   float valor;
   int indx; //indice original usado posteriormente para ordenar los 3 mejores
   int demanda;
public:
   mdata();
   mdata(bool alc, float vl, int in);
   void set_alcanzable();
   bool alcanzable();
   void set_valor(float val);
   float get_valor();
   void set_indx(int in);
   int get_indx();
   bool operator < (mdata p) const;
	int getDemanda() const;
	void setDemanda(int demanda);
};

class mdistancia {
private:
   vector <vector <mdata> > matriz;
public:
   mdistancia();
   mdistancia(vector <vector <mdata> > &md);
   void mostrar_matriz();
   int getsize();
   mdata get(int i, int j);
   //int menor(int ind);
   float get_distancia(int i, int j);
   float get_demandaij(int i, int j);
   void mostrar_demandas();
};

class datos {
private:
   int nvehiculos;
   int nclientes;
   int capvehiculos;
   vector <punto> listado;
   vector <vector <mdata> > matriz;
   int maxX;
   int minX;
public:
   datos();
   datos (string nombre);
   virtual ~datos();
   void mostrarlistado();
   void calcular_matriz();
   float deuclidea(int x1, int x2, int y1, int y2);
   //void mostrar_matriz();
   void marcar_adyacentes(); //se encarga de marcar los puntos adyacentes en la matriz de distancias
   void situar_demandas();
   mdistancia get_matriz();

	const vector<punto>& getListado() const {
		return listado;
	};

	void setListado(const vector<punto>& listado) {
		this->listado = listado;
	};
};



#endif /* DATOS_H_ */
