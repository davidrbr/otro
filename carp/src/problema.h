/*
 * problema.h
 *
 *  Created on: 25/05/2014
 *      Author: David
 */
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "datos.h"
#include <list>
using namespace std;

#ifndef PROBLEMA_H_
#define PROBLEMA_H_

class tvehiculo {
   int id; //identificador del vehiculo
   int ut; // unidades de carga total
   int ua; //unidades de carga actual
   float coste; //coste de la ruta
   //list <int> visitados;
   vector <int> visitados;
   bool usado;
public:
   tvehiculo();
   ~tvehiculo();
   tvehiculo(int i, int uut);
   void insertar (int i);
   void impr_recorrido ();
   int getid ();
   int getcarga_actual ();
   int getcarga_max ();
   void sumar_carga (int cg);
   void sumar_coste (float cost);
   void restar_carga (int cg);
   void set_carga(int cg);
   void set_coste(float cost);
   float get_coste ();
   string get_recorrido();
   bool enuso(); //sirve para detectar si un vehículo se ha utilizado o no
   vector <int> get_visitados();
   int get_visitado(int i);
   void set_visitado(int i, int valor);
   void set_visitados(vector <int> &vt);
   int visitados_size(); //devuelve el numero de puntos visitados;
};


class ruta_parcial {
private:
   //vector<tvehiculo> vehiculos;
   mdistancia mraw; //matriz de distancias sin modificar
   mdistancia mord; //matriz de distancias ordenada
   vector<int> visitados;
   datos * data;
public:
   ruta_parcial (const ruta_parcial &r);
   ruta_parcial (mdistancia &mat,datos * dat); //constructor con una matriz ya inicializada desde fuera
   ruta_parcial (string nombre);
   vector<mdata> ordenar_fila (int i);
   mdata candidatos (int i);
   bool buscar (tvehiculo &v);
   void insertar_visitado (int i);
   bool comprobar_visitado (int i);
   bool fin_visitas ();
   float getdistanciaij (int i, int j);
   vector <int> get_visitados();
};



#endif /* PROBLEMA_H_ */
