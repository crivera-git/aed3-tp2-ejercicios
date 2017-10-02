#include "ejercicio_dos.h"
#define INFINITO INT_MAX
#define VISITADO 1
#define NO_VISITADO 0
#define DEBO_IMPLEMENTAR false

/*           dos.uno              */

//Faltan los parser para tomar la entrada.

class grafo_resultado crear_agm_para(struct grafo_parametro grafo_entrada)
{
  /* El AGM lo hago con el enfoque de PRIM */
  assert( DEBO_IMPLEMENTAR );


  class grafo_resultado grafo_respuesta;
  vector<int> visitados;
  inicializar_vector_con(NO_VISITADO, visitados, grafo_entrada.lista_adyacencias.size());
  grafo_respuesta.visitados = visitados;
  grafo_respuesta.peso_total = 0;

  /* Empiezo con el nodo 0 */
  int nodo_actual = 0;
  int recorridos = 0;
  while( recorridos < grafo_entrada.lista_adyacencias.size() )
  {
    if(grafo_respuesta.visitados.at(nodo_actual) == NO_VISITADO )
    {
      grafo_respuesta.visitados.at(nodo_actual) = VISITADO;
      recorridos++;
      grafo_respuesta.agregar_aristas_adyacentes_a(nodo_actual, grafo_entrada);

      struct arista una_arista = grafo_respuesta.minima_arista_que_no_forma_ciclos();
      grafo_respuesta.agregar_arista_al_agm(una_arista);
      recorridos++;
      nodo_actual = una_arista.otro_nodo;
    }else{
      struct arista una_arista = grafo_respuesta.minima_arista_que_no_forma_ciclos();
      grafo_respuesta.agregar_arista_al_agm(una_arista);
      nodo_actual = una_arista.otro_nodo;
    }

  }
  assert( visite_todos_los_nodos(grafo_respuesta.visitados) );
  return grafo_respuesta;
}

void grafo_resultado::agregar_arista_al_agm(struct arista una_arista)
{
  lista_adyacencias_agm.at(una_arista.un_nodo).push_back(una_arista.otro_nodo);
  lista_adyacencias_agm.at(una_arista.otro_nodo).push_back(una_arista.un_nodo);
  peso_total += una_arista.peso;
  return;
}

struct arista grafo_resultado::minima_arista_que_no_forma_ciclos()
{
  struct arista una_arista;
  while(true)
  {
    /* saco aristas hasta que me de una arista que no forma ciclos */
    una_arista = aristas_a_elegir.top();
    aristas_a_elegir.pop();
    if( not visite_a(una_arista.otro_nodo) ) break;
  }
  return una_arista;
}

bool grafo_resultado::visite_a(int otro_nodo)
{
  return visitados.at(otro_nodo) == VISITADO;
}

void grafo_resultado::agregar_aristas_adyacentes_a(int nodo_actual, grafo_parametro &grafo_entrada)
{
  for(int indice = 0; indice < grafo_entrada.lista_adyacencias.at(nodo_actual).size(); indice++)
  {
    int nodo_indice = grafo_entrada.lista_adyacencias.at(nodo_actual).at(indice);
    if( visitados.at(nodo_indice) == VISITADO) continue;
    struct arista una_arista;
    una_arista.un_nodo = nodo_actual;
    una_arista.otro_nodo = grafo_entrada.lista_adyacencias.at(nodo_actual).at(indice);
    una_arista.peso = grafo_entrada.lista_pesos.at(nodo_actual).at(indice);
    aristas_a_elegir.push(una_arista);
  }
  return;
}

bool visite_todos_los_nodos(vector<int> visitados)
{
  for(int indice = 0; indice < visitados.size(); indice++)
  {
    if(visitados.at(indice) == NO_VISITADO) return false;
  }
  return true;
}











/*            dos.dos           */
int elegir_master(vector<vector<int> > lista_adyacencias)
{
  //Elijo un nodo aleatorio y lo llamo "s"
  int nodo_s = 0;
  int nodo_v = nodo_mas_lejano_a(nodo_s, lista_adyacencias);
  int nodo_w = nodo_mas_lejano_a(nodo_v, lista_adyacencias);
  return elegir_nodo_intermedio_entre(nodo_v, nodo_w, lista_adyacencias);
}

int nodo_mas_lejano_a(int nodo_origen, vector<vector<int> > lista_adyacencias)
{
  vector<int> distancias = distancias_de_un_nodo_a_todos_los_demas(nodo_origen,lista_adyacencias);
  return indice_del_maximo_de(distancias);
}

int elegir_nodo_intermedio_entre(int nodo_origen, int nodo_destino, vector<vector<int> > lista_adyacencias)
{
  /* La idea es que el nodo_origen es el de distancia 0 y el nodo_destino es
  el de distancia maxima pero todos en el medio existen, osea que yo elijo a
  uno en el médio y es el que devuelvo. La otra forma es reconstruir el camino
  entre nodo_origen y nodo_destino y tomar un nodo en el medio pero no se
  como reconstruirlo... */
  /* Esto en realidad está mal porque puede haber un nodo a la distancia que
  yo elijo pero que en realidad no está en el camino entre los dos nodos. */

  //vector<int> distancias = distancias_de_un_nodo_a_todos_los_demas(nodo_origen, lista_adyacencias);
  //assert( indice_del_maximo_de(distancias) == nodo_destino );
  //assert( indice_del_minimo_de(distancias) == nodo_origen );
  //int distancia_intermedia = ((int) maximo_valor_de(distancias) / 2);
  //return nodo_cuya_distancia_es_igual_a(distancia_intermedia, distancias);

  vector<int> camino;
  vector<int> visitados;
  inicializar_vector_con(0,visitados, lista_adyacencias.size());

  struct camino_entre_dos_nodos parametros;
  parametros.nodo_origen = nodo_origen;
  parametros.nodo_destino = nodo_destino;
  parametros.lista_adyacencias = lista_adyacencias;
  parametros.camino = camino;
  parametros.visitados = visitados;

  visitados.at(nodo_origen) = VISITADO;
  aux_elegir_nodo_intermedio_entre(nodo_origen, parametros);
  int respuesta = camino.at( ((int) camino.size() / 2) );
  return respuesta;
}

bool aux_elegir_nodo_intermedio_entre(int nivel, struct camino_entre_dos_nodos &parametros)
{
  bool respuesta = false;

  if(parametros.visitados.at(nivel) == VISITADO) return respuesta;

  parametros.visitados.at(nivel) = VISITADO;
  if(nivel == parametros.nodo_destino)
  {
    respuesta = true;
    parametros.camino.push_back(nivel);
  }else{
    int adyacente;
    for(int un_adyacente; un_adyacente < parametros.lista_adyacencias.at(nivel).at(un_adyacente); un_adyacente++)
    {
      adyacente = parametros.lista_adyacencias.at(nivel).at(un_adyacente);
      respuesta = aux_elegir_nodo_intermedio_entre(adyacente, parametros);
      if(respuesta) break;
    }
    if(respuesta) parametros.camino.push_back(nivel);
  }
  return respuesta;
}

int nodo_cuya_distancia_es_igual_a( int valor_a_buscado, vector<int> &distancias)
{
  for(int indice = 0; indice < distancias.size(); indice++)
    if(distancias.at(indice) == valor_a_buscado) return distancias.at(indice);

  assert( false ); /* NO DEBO LLEGAR ACÁ PORQUE EL ELEMENTO QUE BUSCO EXISTE */
}

vector<int> distancias_de_un_nodo_a_todos_los_demas(int nodo_origen, vector<vector<int> > lista_adyacencias)
{
  /*Elijo un enfoque BFS para encontrar el nodo más lejano a nodo_origen */
  vector<int> elementos_visitados;
  inicializar_vector_con( 0, elementos_visitados , lista_adyacencias.size() );
  vector<int> distancias;
  inicializar_vector_con( INFINITO, distancias, lista_adyacencias.size() );
  queue<int> cola;

  cola.push(nodo_origen);
  elementos_visitados.at(nodo_origen) = VISITADO;
  distancias.at(nodo_origen) = 0;
  while( not cola.empty() ){
    int un_nodo = cola.front();
    cola.pop();
    int adyacente_a_un_nodo;
    for(int un_adyacente = 0; un_adyacente < lista_adyacencias.at(un_nodo).size(); un_adyacente++)
    {
      adyacente_a_un_nodo = lista_adyacencias.at(un_nodo).at(un_adyacente);
      if( elementos_visitados.at(adyacente_a_un_nodo) == NO_VISITADO )
      {
        elementos_visitados.at(adyacente_a_un_nodo) = VISITADO;
        distancias.at(adyacente_a_un_nodo) = distancias.at(un_nodo) + 1;
        cola.push(adyacente_a_un_nodo);
      }
    } /* ya mire todos los adyacentes a un_nodo */
  } /* ya mire todos los nodos del arbol */
  return distancias;
}

void inicializar_vector_con(int inicializador, vector<int> &un_vector, int mi_size )
{
  for(int i = 0; i < mi_size; i++)
  {
    un_vector.push_back( inicializador );
  }
  un_vector.resize(mi_size);
}

int indice_del_maximo_de(vector<int> &distancias)
{
  int maximo = 0;
  for(int indice = 1; indice < distancias.size(); indice++ )
    if( distancias.at(maximo) < distancias.at(indice) ) maximo = indice;

  return maximo;
}

int indice_del_minimo_de(vector<int> &distancias)
{
  int minimo = 0;
  for(int indice = 1; indice < distancias.size(); indice++ )
    if( distancias.at(minimo) >  distancias.at(indice) ) minimo = indice;

  return minimo;
}

int maximo_valor_de(vector<int> &distancias)
{
  int maximo = INT_MIN;
  for(int indice = 0; indice < distancias.size(); indice++)
    if( maximo < distancias.at(indice) ) maximo = distancias.at(indice);

  return maximo;
}
