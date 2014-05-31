/*
 * datos.cpp
 *
 *  Created on: 22/05/2014
 *      Author: david
 */

#include "datos.h"

punto :: punto () {
   id = -1; //numero de cliente
   x = -1;
   y = -1;
   demanda = -1;
}

punto :: punto (int aid, int ax, int ay, int ademanda) {
   id = aid;
   x = ax;
   y = ay;
   demanda = ademanda;
}

void punto :: insertar_adyacente(int ady) {
   adyacentes.push_back(ady);
}

void punto :: imprimir_adyacentes() {
   for (unsigned int i = 0; i < adyacentes.size(); i++) {
      cout << adyacentes[i] << ", ";
   }
   //cout << endl;
}
void punto :: imprimir_demandas() {
   for (unsigned int i = 0; i < demandas.size(); i++) {
      cout << demandas[i] << ", ";
   }
}

void punto :: insertar_demanda(int dmda) {
   demandas.push_back(dmda);
}

datos::datos() {
   nvehiculos = 0;
   nclientes = 0;
   capvehiculos = 0;
   maxX = 0;
   minX = 0;
}

datos :: datos(string nombre) {
   nvehiculos = 0;
   nclientes = 0;
   capvehiculos = 0;
   maxX = 0;
   minX = 0;
   ifstream file (nombre.c_str());
   string aux;
   for (int i = 0; i < 4; i++) //saltamos las cuatro primeras palabras
	   file >> aux;
   //cin.get();
   file >> nvehiculos;
   cout << "nvehiculos : " << nvehiculos << endl;
   file >> capvehiculos;
   cout << "capvehiculos: " << capvehiculos << endl;
   //cin.get();
   for (int i = 0; i < 8; i++) //saltamos las siguientes 9 palabras
      file >> aux;
   cout << "file: " << aux << endl;
   //cin.get();
   //empezamos a leer todos los numeros
   while (!file.eof()) {
      int num;
      punto p;
      file >> num;
      cout << "lectura: " << num;
      p.setId(num);
      file >> num;
      cout << ", " << num << endl;
      p.setX(num);
      file >> num;
      p.setY(num);
      //file >> num;
      //p.setDemanda(num);
      file >> num;
      for (int i = 0; i < num; i++) {
    	 int ad = -1;
    	 file >> ad;
         p.insertar_adyacente(ad);
      }
      for (int i = 0; i < num; i++) {
    	 int ad = -1;
    	 file >> ad;
         p.insertar_demanda(ad);
      }
      listado.push_back(p);
   }
   file.close();
   vector <mdata> dummy;
   for (unsigned int i = 0; i < listado.size(); i++) {
	   mdata dum;
	   dummy.push_back(dum);
   }
   for (unsigned int i = 0; i < listado.size(); i++)
	   matriz.push_back(dummy);
   nclientes = listado.size();
}

void datos :: mostrarlistado () {
   cout << "Numero de vehiculos: " << nvehiculos << endl;
   cout << "Capacidad de vehiculos: " << capvehiculos << endl;
   for (unsigned int i = 0; i < listado.size(); i++) {
	  cout << "Adyacentes: ";
	  listado[i].imprimir_adyacentes();
	  cout << ", demandas: ";
	  listado[i].imprimir_demandas();
	  cout << " X: " << listado[i].getX() << ", Y: " << listado[i].getY() << endl;
   }
}

void datos :: calcular_matriz() {
   for (unsigned int i = 0; i < listado.size(); i++) {
	   for (unsigned int j = 0; j < listado.size(); j++) {
		   matriz[i][j].set_valor(deuclidea(listado[j].getX(),listado[i].getX(),listado[j].getY(),listado[i].getY()));
		   matriz[i][j].set_indx(j);
		   //matriz[i][j].setDemanda(0);
		   //matriz[i][j].setDemanda(listado[j].getDemanda());
		   //cout << "valor: " << matriz[i][j] << endl;
		   //cin.get();
	   }
   }
}

float datos :: deuclidea(int x1, int x2, int y1, int y2) {
   return sqrt(pow((x2-x1),2) + pow((y2-y1),2));
}

/*
void datos :: mostrar_matriz() {
	cout << "Nclientes: " << nclientes << endl;
	cout << "matriz size: " << matriz.size() << endl;
	cout << "listado size: " << listado.size() << endl;
	for (unsigned int i = 0; i < matriz.size(); i++) {
		for (unsigned int j = 0; j < matriz.size(); j++)
		   if (matriz[i][j].alcanzable())
              cout << (int)matriz[i][j].get_valor() << "-";
		   else
			  cout << "I-";
        cout << endl;
	}
}
*/
void datos :: marcar_adyacentes() {
   for (unsigned int i = 0; i < listado.size(); i++) {
	  vector <int> aux = listado[i].getAdyacentes();
	  vector <int> demd = listado[i].getDemandas();
	  for (unsigned int j = 0; j < aux.size(); j++) {
         matriz[i][aux[j]].set_alcanzable();
         matriz[i][aux[j]].setDemanda(demd[j]);

	  }
   }
   for (unsigned int i = 0; i < matriz.size(); i++) {
	  for (unsigned int j = 0; j < matriz.size(); j++) {
         if(!matriz[i][j].alcanzable()) {
        	 matriz[i][j].set_valor(99999);
             matriz[i][j].setDemanda(0);
         }
	  }
   }

}




mdistancia datos :: get_matriz() {
   return matriz;
}

mdata mdistancia :: get(int i, int j) {
   return matriz[i][j];
}

datos::~datos() {
	// TODO Auto-generated destructor stub
}

mdata :: mdata() {
   demanda = 0;
   alcanza = false;
   valor = -1;
   indx = -1;
}
mdata :: mdata (bool alc, float vl,int in) {
   demanda = 0;
   alcanza = alc;
   valor = vl;
   indx = in;
}
void mdata :: set_alcanzable() {
   alcanza = true;
}
bool mdata :: alcanzable() {
   return alcanza;
}
void mdata :: set_valor(float val) {
   valor = val;
}
float mdata :: get_valor() {
   return valor;
}

void mdata :: set_indx(int in) {
   indx = in;
}

int mdata::getDemanda() const {
	return demanda;
}

void mdata::setDemanda(int demanda) {
	this->demanda = demanda;
}

bool mdata :: operator < (mdata p) const {
   if (valor < p.get_valor())
      return true;
/*   if alcanzable != true
      return true;
   if p.alcanzable == true
      return true;
*/
   return false;
};

int mdata :: get_indx() {
   return indx;
}

mdistancia :: mdistancia() {

}
mdistancia :: mdistancia (vector <vector <mdata> > &md) {
   matriz = md;
}

void mdistancia :: mostrar_matriz() {
	for (unsigned int i = 0; i < matriz.size(); i++) {
		for (unsigned int j = 0; j < matriz.size(); j++)
		   if (matriz[i][j].alcanzable())
              cout << (int)matriz[i][j].get_valor() << "-";
		   else
			  cout << "I-";
        cout << endl;
	}
}

int mdistancia :: getsize() {
   return matriz.size();
}
float mdistancia :: get_distancia(int i, int j) {
   return matriz[i][j].get_valor();
};

float mdistancia :: get_demandaij(int i, int j) {
   return matriz[i][j].getDemanda();
};

void mdistancia :: mostrar_demandas() {
	for (unsigned int i = 0; i < matriz.size(); i++) {
		for (unsigned int j = 0; j < matriz.size(); j++)
              cout << (int)matriz[i][j].getDemanda() << "-";
        cout << endl;
	}
};
