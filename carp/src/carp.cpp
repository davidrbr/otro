
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
	int num = 9999;
	num = res->ejecutar();
	resolver * menor;
	menor = NULL;
	cout << "NUMERO DE NOVISITADOS: " << num << endl;
	int n_actual = -1;
    for (int i = 0; i < 100; i++) {
    	res = new resolver(3,mat,dat);
    	n_actual = res->ejecutar();
    	if (n_actual < num) {
    	   num = n_actual;
    	   menor = res;
    	}
    	else
    	   delete res;
    }
    cout << "fin" << endl;
    cout << "Num: " << num << endl;
    menor->imprimir_rutas();
	delete menor;
	return 0;
}
