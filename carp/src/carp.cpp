
#include <iostream>
#include "datos.h"
#include "problema.h"
#include <time.h>
using namespace std;

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
	ruth.buscar(vehicle);
	ruth.buscar(vehicle2);
	ruth.buscar(vehicle3);
	vehicle.impr_recorrido();
	vehicle2.impr_recorrido();
	vehicle3.impr_recorrido();
	vector<int> vis = ruth.get_no_visitados();
	cout << "puntos no visitados: " << vis.size() << endl;
	for (int i = 0; i < vis.size(); i++)
       cout << vis[i] << ", ";
	cout << endl;
//	mdata dati = ruth.candidatos(1);
	//cout << "candidato: " << dati.get_indx() << ", y es alcanzable: " << dati.alcanzable() << endl;
	return 0;
}
