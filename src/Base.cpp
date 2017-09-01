#include <iostream>
#include "Base.h"
#include "utils.h"


using namespace std;

Base::Base(vector<string> nombres, vector<Tabla> tablas) :
        _nombres(nombres), _tablas(tablas){}

void Base::agregarTabla(string nombre, Tabla t) {
    if (!this->tablaDefinida(nombre) ) {
        this->_nombres.push_back(nombre);
        this->_tablas.push_back(t);
    }
}

void Base::agregarRegistroATabla(string nombre, Registro r){
    if (this->tablaDefinida(nombre)){
        int pos;
        for (int i = 0; i < this->_nombres.size(); ++i) {
            if (this->_nombres[i] == nombre) {
                pos = i;
            }
        }
        if (!this->estaDefinidoEn(nombre,r)){
            this->_tablas[pos].agregarRegistro(r);
        }
    }
}

bool Base::tablaDefinida(string nombre){
    bool res = false;
    for (int i = 0; i < this->_nombres.size(); ++i) {
        if (this->_nombres[i] == nombre) {
            return true;
        }
    }
    return false;
}

vector<string> Base::nombre() const{
    return this->_nombres;
}

//Tabla Base::obtenerTabla (string nombre){

//}
bool registroEnTabla( Tabla t, Registro r);

//tabla no se fija si se puede si se puede agregar el registro
bool Base::estaDefinidoEn(string nombre, Registro r){
    int pos = 0;
    for (int i = 0; i < _nombres.size(); ++i) {
        if (_nombres[i] == nombre) {
            pos = i;
        }
    }
    Tabla tabla = _tablas[pos];
    return registroEnTabla( tabla, r);
}

//se fija si el refgisto esta en la tabla con las resticciones del tad tabla

bool registroEnTabla( Tabla t, Registro r){
    bool esta = true;
    if (!seteq(t.campos(), r.campos())){
        return false;
    }
    if (t.registros().size() == 0) {
        return false;
    } else {

        for (int j = 0; j < t.registros().size() && esta; ++j) { //no se repiten los datos
            for (int i = 0; i < t.claves().size(); ++i) {
                esta &= (t.registros()[j].dato(t.claves()[i]) == r.dato(t.claves()[i]));
            }
        }
    }
    return esta;
}



Tabla guardadIguales( Tabla t, string campo, Dato dato);

void guardarDistintos( Tabla& res, Tabla t, string campo, Dato dato);

Tabla Base::busqueda(string nombre, bool igualdad, string campo, Dato dato){
    int pos = 0;
    for (int i = 0; i < _nombres.size(); ++i) {
        if (_nombres[i] == nombre) {
            pos = i;
        }
    }

    vector <Dato> tipos;
    for (int j = 0; j <_tablas[pos].campos().size() ; ++j) {
        tipos.push_back(_tablas[pos].tipoCampo(_tablas[pos].campos()[j]));
    }
    Tabla res(_tablas[pos].campos(), _tablas[pos].claves(), tipos);

    for (int i = 0; i <_tablas[pos].registros().size() ; ++i) {
        Dato test = _tablas[pos].registros()[i].dato(campo);
        if ((_tablas[pos].registros()[i].dato(campo) == dato) == igualdad){
            res.agregarRegistro(_tablas[pos].registros()[i]);
        }
    }
    return res;
}
