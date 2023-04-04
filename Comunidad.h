#ifndef __COMUNIDAD_H__
#define __COMUNIDAD_H__

#include <string>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

class Comunidad{
  public:
    Comunidad(); // O(1)

    const set<int> & inscriptos() const; // O(1)
    string obtener_empresa(int id) const; // O(log n)
    const set<string> & obtener_socios(int id) const; // O(log n)
    int cantidad_asociaciones() const; // O(1)
    int obtener_id(string empresa) const; // sin requerimiento
    bool es_empresa_popular(string empresa) const; // O(1) promedio

    void inscribir(string empresa, int id); // O(log n)
    void desinscribir(int id); // sin requerimiento
    void asociar(string empresa_A, string empresa_B); // sin requerimiento
    void desasociar(string empresa_A, string empresa_B); // sin requerimiento
    

  private:
    int cant_asociaciones;
    set<int> _inscriptos;
    map<int, string> _empresas; // id-> int y nombre-> string
    map<string, bool> _popularidad; // nombre-> string y popular-> bool
    map<int, set<string>> _asociaciones; // id-> int y asociaciones-> set<string>


    /*

    REP:
    > cant_asociaciones debe ser un valor positivo entero y debe ser igual a la (suma de todos los tamaños de los valores del mapa _asociaciones)/2.
    > _inscriptos debe contener valores enteros.
    > Ademas, todos estos valores de _inscriptos deben estar como claves en los mapas _empresas y _asociaciones.
    > El tamaño de todos los mapas(_empresas, _popularidad y _asociaciones) debe ser igual a la cantidad de inscriptos(tamaño de _inscriptos)
    > Todos los elementos del set de _asociaciones deben ser alguna clave del vector _popularidad o valor de _empresas.
    
    
    Ej cumple el invariante =
    cant_asociaciones = 1
    _inscriptos = (0,1)
    _empresas = { 0:"Accenture" ; 1: "Mercado Libre"}
    _popularidad = {"Accenture":false ; "Mercado Libre":false}
    _asociaciones = { 0:{"Mercado Libre"} ; 1:{"Accenture"}}

    Ej NO cumple el invariante =
    cant_asociaciones = 14   // esta contando la totalidad de asociaciones por empresa sin tener en cuenta que una asociacion entre dos empresas cuenta como 1.
    _inscriptos = (0,1,2,4,6)    //cantidad de inscriptos no coincide con el tamano de los mapas y el valor 6 no se encuentra como clave en _empresas y _asociaciones.
    _empresas = { 0:"Accenture" ; 1:"Mercado Libre" ; 2:"Amazon" ; 3:"Globant" ; 4:"Galicia" ; 5:"Samsung"}
    _popularidad = {"Accenture":false ; "Mercado Libre":false ; "Amazon":false ; "Globant":false ; "Galicia":false ; "Samsung":false}  //"Galicia" deberia tener el valor true ya que tiene 5 asociaciones.
    _asociaciones = { 0:{"Galicia","Globant"} ; 1:{"Galicia","Samsung"} ; 2:{"Galicia"} ; 3:{"Accenture","Galicia"} ; 4:{"Accenture","Mercado Libre","Amazon","Globant","Samsung"} ; 5:{"Mercado Libre","Galicia"}}
    */
};

#endif