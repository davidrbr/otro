
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

	resolver * res;
	res = new resolver(3,mat,dat);
	int num = -1;
	num = res->ejecutar();
	cout << "NUMERO DE NOVISITADOS: " << num << endl;
	cin.get();
	resolver * res2;
    res2 = new resolver(3,mat,dat);
	num = res2->ejecutar();
	cout << "NUMERO DE NOVISITADOS: " << num << endl;

	return 0;
}
