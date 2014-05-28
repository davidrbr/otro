
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
	tvehiculo vehicle(1,200,3);

	//dat->mostrarlistado();
	ruta_parcial ruth(mat, dat);
	//mat.mostrar_demandas();
	ruth.buscar(vehicle);
	vehicle.impr_recorrido();
//	mdata dati = ruth.candidatos(1);
//	cout << "candidato: " << dati.get_indx() << ", y es alcanzable: " << dati.alcanzable() << endl;
	return 0;
}
