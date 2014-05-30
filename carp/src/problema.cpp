/*
 * problema.cpp
 *
 *  Created on: 25/05/2014
 *      Author: David
 */
#include "problema.h"
tvehiculo :: tvehiculo () {
   id = -1;
   ut = 0;
   ua = 0;
   coste = 0.0;
   //visitados.push_back(0);
   usado = false;
   origen = 0;
};

tvehiculo :: ~tvehiculo() {
   //visitados.clear();
};

tvehiculo :: tvehiculo (int i, int uut, int org) {
   //coste = 0;
   id = i;
   ut = uut;
   ua = 0;
   usado = false;
   coste = 0.0;
   origen = org;
   visitados.push_back(origen);
};

void tvehiculo :: insertar (int i) {
   usado = true;
   visitados.push_back(i);
};

void tvehiculo :: impr_recorrido () {
   ofstream file;
   file.open("vehiculo.txt");
   cout << "Recorrido del vehiculo "<< id << ": " << endl;
   for (vector<int> :: iterator it = visitados.begin(); it != visitados.end(); it++) {
      cout << "," << (*it);
      file << "," << (*it);
   }
   cout << endl << endl;
   file << endl << endl;
   file.close();

};

string tvehiculo ::  get_recorrido() {
   stringstream aux;
   for (vector<int> :: iterator it = visitados.begin(); it != visitados.end(); it++) {
      aux << (*it) << " ";
   }
   return aux.str();
};

int tvehiculo :: getid() {
   return id;
};

int tvehiculo :: getcarga_actual () {
   return ua;
};

void tvehiculo :: set_carga(int cg) {
   ua = cg;
};

int tvehiculo :: getcarga_max () {
   return ut;
};

void tvehiculo :: sumar_carga (int cg) {
   ua += cg;
};

void tvehiculo :: sumar_coste (float cost) {
   //cout << "suma coste: " << coste << endl;
   //cin.get();
   coste+=cost;
};

float tvehiculo :: get_coste () {
   if (!enuso())
      return 0.0;
   return coste;
};

bool tvehiculo :: enuso() {
   return usado;
};

vector <int> tvehiculo :: get_visitados() {
   return visitados;
};

void tvehiculo ::  restar_carga (int cg) {
   ua = ua - cg;
};

void tvehiculo ::  set_coste(float cost) {
   coste = cost;
};

void tvehiculo :: set_visitados(vector <int> &vt) {
   visitados = vt;
};

int tvehiculo :: visitados_size() {
   return visitados.size();
};

int tvehiculo :: get_visitado(int i) {
   return visitados[i];
};

void tvehiculo :: set_visitado(int i, int valor) {
   visitados[i] = valor;
};

bool tvehiculo :: insertar_npos(int i, int j) {
   std::vector<int>::iterator it;
   it = visitados.begin();
   while (((*it) != i) && (it != visitados.end())) {
      it++;
   }
   if (it == visitados.end()) {
      visitados.push_back(j);
      visitados.push_back(i);
   }
   else {
      visitados.insert(it+1,j);
      visitados.insert(it+2,i);
   }
   return true;
};

ruta_parcial :: ruta_parcial (mdistancia &mat,datos * dat) {
   mraw = mat;
   mord = mat;    //nn
   //mord.ordenar_matriz();
   data = dat;
   //insertar_visitado(origen);
}

ruta_parcial :: ruta_parcial (string nombre) {
   //mdistancia aux(nombre.c_str());
  // mraw = aux;
   //mord = aux;
   //insertar_visitado(origen);
}

ruta_parcial :: ruta_parcial (const ruta_parcial &r) {
	mraw = r.mraw;
	mord = r.mord;
	visitados = r.visitados;
	data = r.data;
	//origen = r.origen;

};

vector<mdata> ruta_parcial :: ordenar_fila (int i) {
   vector <mdata> candidatos;
   int j = 0;
   while (j < mraw.getsize() && !fin_visitas()) {
      if ((!comprobar_visitado(mraw.get(i,j).get_indx()) && mraw.get(i,j).get_valor() != 0) && (mraw.get(i,j).alcanzable()))
         candidatos.push_back(mraw.get(i,j));
      j++;
   }
   std :: sort(candidatos.begin(), candidatos.end());
   cout << "candidatos: " << endl;
   for (unsigned int i = 0; i < candidatos.size();i++)
      cout << candidatos[i].get_indx() << ", ";
   cout << endl;
   if (candidatos.empty())
   cout << "NO HAY CANDIDATOS!!" << endl;
   return candidatos;
};

mdata ruta_parcial :: candidatos (int i) { // dado un punto buscamos los 3 mas cercanos que no hayan sido visitados ya, para poder seleccionar uno de forma aleatoria
   vector <mdata> candidatos = ordenar_fila(i);
   int indice = 0;
   if (candidatos.size() >= 3) {
      indice = rand()% 3;
      //cout << "primera" << endl;
      if (candidatos[indice].alcanzable() == 0) {
    	  bool found = false;
    	  while ((indice >= 1) && (!found)) {
    		 //cout << "hola" << endl;
             indice--;
             if (candidatos[indice].alcanzable())
            	 found = true;
    	  }
      }
   }
   else  if (candidatos.size() >= 1){
      indice = rand()% candidatos.size(); // puede ser que en vez de 3 puntos tengamos dos o 1
   //cout << "indice original: " << i << "," << candidatos[indice].getid() << endl;
  // cout << "distancia: " << candidatos[indice].getdistancia() << endl;
      if (candidatos[indice].alcanzable() == 0) {
    	  bool found = false;
    	  while ((indice >= 1) && (!found)) {
    		 //cout << "hola" << endl;
             indice--;
             if (candidatos[indice].alcanzable())
            	 found = true;
    	  }
      }
   }
   else {
      mdata dummy;
      dummy.set_indx(-1);
      return dummy;
   }
   if (candidatos[indice].alcanzable())
      insertar_visitado(candidatos[indice].get_indx());
   return candidatos[indice];
};
bool ruta_parcial :: buscar (tvehiculo &v) { //ruta parcial
   //cout << "fin de visitas? " << fin_visitas() << endl;
   vector<mdata> visitando;
   if (!fin_visitas()) {
	   int cont = 0;
	   int siguiente = v.getOrigen();
	   //cout << "origen: " <<
	   insertar_visitado(siguiente);
	   //v.insertar(siguiente);
	   //float coste = 0.0;
	   mdata ret;
	   //int demanda = 0;
	   cout << "Carga antes de entrar: " << v.getcarga_actual() << endl;
	   mdata algo = mraw.get(v.getOrigen(),v.getOrigen());
	   cout << "algo: " << algo.get_indx() << endl;
//	   /visitando.push_back(v.getOrigen());
	   //cin.get();
	   visitando.push_back(algo);
	   //while (cont < mraw.getsize() && v.getcarga_actual()+ mraw.get_demandaij(ret.get_indx(), siguiente) <= v.getcarga_max() && !fin_visitas()) {
	   while (cont < mraw.getsize()&& !fin_visitas() && ret.get_indx() != 55 && ret.get_indx() != 54 && ret.get_indx() != 53 && ret.get_indx() != 52 && ret.get_indx() != 51) {
	   //while (cont < mraw.getsize() && v.getcarga_actual()+ listado[siguiente].  <= v.getcarga_max() && !fin_visitas()) {
		  ret = candidatos(siguiente);
		  cout << "----------->siguiente: " << ret.get_indx() << endl;
		  //demanda = ret.getdemanda();
		  //cout << "Demanda: " << demanda << endl;
		  //cin.get();
		  if (ret.get_indx() != -1)
		     visitando.push_back(ret);
		  cout << "tamanio visitando: " << visitando.size() << endl;
          for (int i = 0; i < visitando.size(); i++) {
             cout << visitando[i].get_indx() << ", ";
          }
          cout << endl;
          if (ret.alcanzable()) {

		     v.sumar_coste(ret.get_valor());
		  //cout << "ret: " << ret.getdistancia() << ", " << "getij: " << mraw.get_distancia(ret.getid(), siguiente) << " i: " << siguiente << ", j: " << ret.getid() << endl;
		  //cin.get();
		     v.sumar_carga(mraw.get_demandaij(ret.get_indx(), siguiente));
		     siguiente = ret.get_indx();
		     v.insertar(siguiente);
		     cont++;
          }
          else{
             cout << "Punto no alcanzable " << ret.get_indx() << endl;
             //if (!visitando.empty())
             //   visitando.pop_back();
             //ret = (*visitando.end());
             //cout << "Punto: " << ret.get_indx() << endl;
             //if (!visitando.empty())
             //   visitando.pop_back();
             //if (visitando.size() >= 1) {
             if (!visitando.empty())
                visitando.pop_back();
             cout << "visitando sise: " << visitando.size() << endl;
             if (visitando.size() > 0) {
                ret = visitando[visitando.size()-1];
                cout << "Nuevo punto: " << ret.get_indx()  << endl;
                siguiente = ret.get_indx();
                v.insertar(siguiente);
             }
           if (visitando.empty() && ret.get_indx() == -1) {
        	  cout << "BREIK" << endl;
              break;
           }
             //}
             //cout << "tamanio visitando: " << visitando.size() << endl;
             //cin.get();


          }
          cout << "Puntos ya visitados: " << visitados.size() << endl;
          //std :: sort (visitados.begin(),visitados.end());
          for (int i = 0; i < visitados.size(); i++) {
        	  cout << visitados[i] << ". ";
          }
          cout << endl;
          //cin.get();
		  //v.sumar_carga(demanda);
	   }
	   //cout << "vehiculo lleno" << endl;
	  /// v.sumar_coste(getdistanciaij(ret.get_indx(),0)); //añadimos el coste de ir desde el ultimo punto hasta el origen
	   //cout << "getij: " << mraw.get_distancia(ret.getid(), 0) << ", vs: " << getdistanciaij(ret.getid(),0) << " i: 0, j: "  << ret.getid() <<  endl;
	   //cout << "carga hasta el momento: " << v.get_coste() << endl;
	   //cin.get();
	   ////v.insertar(0); //añadimos al recorrido del vehiculo la vuelta al origen
	   //v.impr_recorrido();
	   //cin.get();
	   //cout << "distancia del ultimo punto al origen: " << getdistanciaij(ret.getid(),0) << endl
	   //cout << "ultimo punto visitado: " << ret.getid() << endl;
	   //cout << "cuenta: " << cont << endl;
	   //cout << "coste total del vehiculo: " << v.get_coste() << endl;
	   return true;
   }
   //cout << "Ya todos los puntos estan visitados" << endl;
   return false;
};



/*
bool ruta_parcial :: buscar (tvehiculo &v) { //ruta parcial
   //cout << "fin de visitas? " << fin_visitas() << endl;
   if (!fin_visitas()) {
	   int cont = 0;
	   int siguiente = 0;
	   //float coste = 0.0;
	   mdata ret;
	   //int demanda = 0;
	   cout << "Carga antes de entrar: " << v.getcarga_actual() << endl;
	   while (cont < mraw.getsize() && v.getcarga_actual()+ mraw.get_demandaij(ret.get_indx(), siguiente) <= v.getcarga_max() && !fin_visitas()) {
	   //while (cont < mraw.getsize() && v.getcarga_actual()+ listado[siguiente].  <= v.getcarga_max() && !fin_visitas()) {
		  ret = candidatos(siguiente);
		  cout << "----------->siguiente: " << ret.get_indx() << endl;
		  //demanda = ret.getdemanda();
		  //cout << "Demanda: " << demanda << endl;
		  cin.get();
		  cont++;
		  v.sumar_coste(ret.get_valor());
		  //cout << "ret: " << ret.getdistancia() << ", " << "getij: " << mraw.get_distancia(ret.getid(), siguiente) << " i: " << siguiente << ", j: " << ret.getid() << endl;
		  //cin.get();
		  v.sumar_carga(mraw.get_demandaij(ret.get_indx(), siguiente));
		  siguiente = ret.get_indx();
		  v.insertar(siguiente);
		  //v.sumar_carga(demanda);
	   }
	   //cout << "vehiculo lleno" << endl;
	   v.sumar_coste(getdistanciaij(ret.get_indx(),0)); //añadimos el coste de ir desde el ultimo punto hasta el origen
	   //cout << "getij: " << mraw.get_distancia(ret.getid(), 0) << ", vs: " << getdistanciaij(ret.getid(),0) << " i: 0, j: "  << ret.getid() <<  endl;
	   //cout << "carga hasta el momento: " << v.get_coste() << endl;
	   //cin.get();
	   v.insertar(0); //añadimos al recorrido del vehiculo la vuelta al origen
	   //v.impr_recorrido();
	   //cin.get();
	   //cout << "distancia del ultimo punto al origen: " << getdistanciaij(ret.getid(),0) << endl
	   //cout << "ultimo punto visitado: " << ret.getid() << endl;
	   //cout << "cuenta: " << cont << endl;
	   //cout << "coste total del vehiculo: " << v.get_coste() << endl;
	   return true;
   }
   //cout << "Ya todos los puntos estan visitados" << endl;
   return false;
};
*/

void ruta_parcial :: insertar_visitado (int i) {
   visitados.push_back(i);
};

bool ruta_parcial :: comprobar_visitado (int i) {
  for (vector<int> :: iterator it = visitados.begin(); it != visitados.end(); it++)
     if (i == (*it))
        return true;
   return false;
};

bool ruta_parcial :: fin_visitas () {
   if ((int)visitados.size() == (int)mraw.getsize())
      return true;
   return false;
};

float ruta_parcial :: getdistanciaij (int i, int j) {
   mdata ret = mraw.get(i,j); //recuperamos el punto ij de la matriz sin alterar
   return ret.get_valor(); //devolvemos la distancia de un punto a otro
};

vector<int> ruta_parcial :: get_visitados() {
   return visitados;
};

vector<int> ruta_parcial :: get_no_visitados() {
   vector <int> aux = get_visitados();
   vector <int> ret;
   std :: sort (aux.begin(), aux.end());
   for (int i = 0; i < mraw.getsize(); i++) {
      bool found = false;
	  for (int j = 0; j < aux.size(); j++) {
         if (i == aux[j])
            found = true;
      }
	  if (!found)
	     ret.push_back(i);
   }
   /*
      //ret.push_back(i);
   cin.get();
   for (int i = 0; i < mraw.getsize(); i++) {
	   for (int j = 0; j < aux.size(); j++) {
          if (ret[i] == aux[j]){
             ret.erase(ret.begin()+i);
             break;
          }
	   }
   }
   */
   return ret;
}

void ruta_parcial :: completar_rutas(vector <tvehiculo> & vehiculos) {

   vector <int> nov = get_no_visitados();
   while (!fin_visitas()) {
	  int i = 0;
      while (i < nov.size()) {
         mdata candidato = adyacente_cercano(nov[i]); // nov[i] es el punto para el cual se quiere buscar un candidato adyacente que si este visitado
         if (candidato.get_indx() != -1)

         i++;
      }

   }

};
/*
vector<mdata> ruta_parcial :: ordenar_fila (int i) {
   vector <mdata> candidatos;
   int j = 0;
   while (j < mraw.getsize() && !fin_visitas()) {
      if ((!comprobar_visitado(mraw.get(i,j).get_indx()) && mraw.get(i,j).get_valor() != 0) && (mraw.get(i,j).alcanzable()))
         candidatos.push_back(mraw.get(i,j));
      j++;
   }
   std :: sort(candidatos.begin(), candidatos.end());
   cout << "candidatos: " << endl;
   for (unsigned int i = 0; i < candidatos.size();i++)
      cout << candidatos[i].get_indx() << ", ";
   cout << endl;
   if (candidatos.empty())
   cout << "NO HAY CANDIDATOS!!" << endl;
   return candidatos;
};

*/
mdata ruta_parcial :: adyacente_cercano(int i) {
   vector <mdata> adyacentes;
   mdata ret;
   ret.set_valor(-1);
   int j = 0;
   while (j < mraw.getsize() && !fin_visitas()) {
      if (comprobar_visitado(mraw.get(i,j).get_indx()) && (mraw.get(i,j).alcanzable())) {
    	 cout << "habba: " << mraw.get(i,j).get_indx() << endl;
         adyacentes.push_back(mraw.get(i,j));
      }
      j++;
   }
   cout << "Adyacentes: " << endl;
   for (int j = 0; j < adyacentes.size(); j++) {
      cout << adyacentes[j].get_indx() <<  ", ";
   }
   cout << endl;
   if (adyacentes.size() > 0) {
      std :: sort (adyacentes.begin(), adyacentes.end());
      cout << "mejor candidato es : " << (*adyacentes.begin()).get_indx() << ", para el punto: " << i <<  endl;
      cout << endl;
      ret = (*adyacentes.begin());
   }

   return ret;
}


