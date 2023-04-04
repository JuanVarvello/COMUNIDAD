#include "Comunidad.h"

using namespace std;
#include <map>

Comunidad::Comunidad(){
    this->cant_asociaciones = 0;
}

const set<int> & Comunidad::inscriptos() const{
    return this->_inscriptos;
}

string Comunidad::obtener_empresa(int id) const{

    auto it = this->_empresas.find(id);
    string s = it->second;

    return s;
}
const set<string> & Comunidad::obtener_socios(int id) const{

    auto it = this->_asociaciones.find(id);
    return it->second;
}

int Comunidad::cantidad_asociaciones() const{
    return this->cant_asociaciones;
}

void Comunidad::inscribir(string empresa, int id){
    //Agrego par a _empresas
    this->_empresas[id] = empresa;

    //Agrego par a _popularidad
    this->_popularidad[empresa] = false;

    //Agrego par a _asociaciones
    set<string> s = {};
    this->_asociaciones[id] = s;

    //Agrego a _inscriptos
    this->_inscriptos.insert(id);
}
void Comunidad::desinscribir(int id){

    //Saco de _popularidad
    string empresa = obtener_empresa(id);
    auto it = this->_popularidad.find(empresa);
    this->_popularidad.erase(it);

    //Saco a la empresa de _asociaciones de otras empresas
    set<string> asoc = obtener_socios(id);
    
    for(auto it3 = asoc.begin(); it3 != asoc.end(); it3++){
      desasociar(empresa, *it3);
    }
  
    //Borro asociaciones de la empresa
    auto it4 = this->_asociaciones.find(id);
    this->_asociaciones.erase(it4);

    //Saco de _empresas
    auto it5 = this->_empresas.find(id);
    this->_empresas.erase(it5);

    //Saco de _inscriptos
    auto it2 = this->_inscriptos.find(id);
    this->_inscriptos.erase(it2);

}

void Comunidad::asociar(string empresa_A, string empresa_B){
    this->cant_asociaciones++;

    int idA = obtener_id(empresa_A);
    int idB = obtener_id(empresa_B);

    //Agrego asociacion en A
    auto it = this->_asociaciones.find(idA);
    it->second.insert(empresa_B);

    //Cambiar la popularidad en caso de que tenga >= 5 asociaciones
    if(it->second.size() >= 5){
        this->_popularidad[empresa_A] = true;
    }

    //Agrego asociacion en B
    auto it2 = this->_asociaciones.find(idB);
    it2->second.insert(empresa_A);

    //Cambiar la popularidad en caso de que tenga >= 5 asociaciones
    if(it2->second.size() >= 5){
        this->_popularidad[empresa_B] = true;
    }
}

void Comunidad::desasociar(string empresa_A, string empresa_B){
    this->cant_asociaciones--;

    int idA = obtener_id(empresa_A);
    int idB = obtener_id(empresa_B);

    //Borro asociacion en A
    auto it = this->_asociaciones.find(idA);
    it->second.erase(empresa_B);

    //Cambiar la popularidad en caso de que tenga < 5 asociaciones
    if(it->second.size() < 5){
        this->_popularidad[empresa_A] = false;
    }

    //Borro asociacion en B
    auto it2 = this->_asociaciones.find(idB);
    it2->second.erase(empresa_A);

    //Cambiar la popularidad en caso de que tenga < 5 asociaciones
    if(it2->second.size() < 5){
        this->_popularidad[empresa_B] = false;
    }

}

int Comunidad::obtener_id(string empresa) const{
    int id;
    for(auto it = this->_empresas.begin(); it != this->_empresas.end(); it++){
        if(it->second == empresa){
            id = it->first;
        }
    }
    return id;
}
bool Comunidad::es_empresa_popular(string empresa) const{
    
    //Busco la posicion de mi clave(empresa) en el mapa
    auto it = this->_popularidad.find(empresa);

    //Devuelvo el valor asociado a la clave
    bool res = it->second;

    return res;

}