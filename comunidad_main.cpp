#include "Comunidad.h"
#include <iostream>
#include <set>
#include <string>

using namespace std;

void imprimir_set(set<string> s){
    for (string e: s)
        cout << e << " ";
    cout << endl;
}

int main(){
    // Usar main para hacer pruebas
    // No entregar.

    Comunidad rs;

    rs.inscribir("Empresa A", 5);
    rs.inscribir("Empresa B", 4);
    rs.inscribir("Empresa C", 3);
    rs.inscribir("Empresa D", 2);
    rs.inscribir("Empresa E", 1);

    rs.desinscribir(2);

    rs.asociar("Empresa E","Empresa D");
    rs.asociar("Empresa E","Empresa C");
    rs.asociar("Empresa B","Empresa A");

    rs.desinscribir(4);

    imprimir_set(rs.obtener_socios(1));
}