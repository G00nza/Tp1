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

//tabla no se fija si se puede si se puede agregar el registro
bool Base::estaDefinidoEn(string nombre, Registro r){
    int pos;
    for (int i = 0; i < this->_nombres.size(); ++i) {
        if (this->_nombres[i] == nombre) {
            pos = i;
        }
    }
    bool esta = false;
    for (int i = 0; i < this->_tablas[pos].registros().size() && !esta; ++i) {
        if (this->_tablas[pos].registros()[i] == r) {
            esta = true;
        }
    }

    return esta;
}