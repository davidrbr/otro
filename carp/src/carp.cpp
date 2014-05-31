
#include <iostream>
#include "datos.h"
#include "problema.h"
#include <time.h>
using namespace std;
/*
int insertar_pvehiculos (vector<tvehiculo> &v, int pvisitado, int pnuevo) {
   for (int i = 0; i < v.size(); i++) {
      if (v[i].insertar_npos(51,57))
         return v[i].getid();
   }
   return -1;
}
*/

int main() {
	srand (time(NULL));
	datos * dat;
	dat = new datos("ficherocarp3.txt");
	//dat.mostrarlistado();
	dat->calcular_matriz();

	dat->marcar_adyacentes();
	//dat.mostrar_matriz();
	mdistancia mat = dat->get_matriz();
	//mat.mostrar_matriz();
	tvehiculo vehicle(1,200,1);
	tvehiculo vehicle2(2,200,8);
	tvehiculo vehicle3(3,200,4);
	//dat->mostrarlistado();
	ruta_parcial ruth(mat, dat);
	//mat.mostrar_demandas();
	vector<tvehiculo> vs;
	vs.push_back(vehicle);
	vs.push_back(vehicle2);
	vs.push_back(vehicle3);
	for (int i = 0; i < vs.size(); i++)
       ruth.buscar(vs[i]);
	//ruth.buscar(vehicle);
	//ruth.buscar(vehicle2);
	//ruth.buscar(vehicle3);
	for (int i = 0; i < vs.size(); i++)
       vs[i].impr_recorrido();
	cin.get();
	//vehicle.impr_recorrido();
	//vehicle2.impr_recorrido();
	//vehicle3.impr_recorrido();
	vector<int> vis = ruth.get_no_visitados();
	cout << "puntos no visitados: " << vis.size() << endl;
	for (int i = 0; i < vis.size(); i++)
       cout << vis[i] << ", ";
	cout << endl;
    ruth.completar_rutas(vs);
	//vector<tvehiculo> dum;
	//ruth.completar_rutas(dum);
	//vehicle.insertar_npos(51,57);
	//vehicle.impr_recorrido();
//	mdata dati = ruth.candidatos(1);
	//cout << "candidato: " << dati.get_indx() << ", y es alcanzable: " << dati.alcanzable() << endl;
	for (int i = 0; i < vs.size(); i++)
       vs[i].impr_recorrido();
	return 0;
}
