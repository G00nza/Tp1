#include <iostream>
#include "Base.h"
#include "utils.h"
#include <cassert>

using namespace std;

Base::Base(vector<string> nombres, vector<Tabla> tablas, vector<vector <Criterio> > ) :
        _nombres(nombres), _tablas(tablas), _criterios(){}

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

bool Base::tablaDefinida(string nombre)const {
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
    if (!seteq(t.campos(), r.campos())){
        return false;
    }
    if (t.registros().size() == 0) {
        return false;
    } else {

        for (int j = 0; j < t.registros().size(); ++j) {
            bool esta = true;//no se repiten los datos
            for (int i = 0; i < t.claves().size(); ++i) {
                esta &= (t.registros()[j].dato(t.claves()[i]) == r.dato(t.claves()[i]));
            }
            if (esta){
                return esta;
            }

        }
    }
    return false;
}

bool cumpleCond (Registro r, Criterio c);
bool cumpleCond (Registro r, Criterio c){
    for (int i = 0; i < c.restricciones().size() ; ++i) {
        if ((r.dato(get <0>(c.restricciones()[i])) == get<1>(c.restricciones()[i])) != get<2>(c.restricciones()[i]) ){
            return false;
        }
    }
    return true;
}


bool criteriosValidos(Tabla t, Criterio c);
bool criteriosValidos(Tabla t, Criterio c){
    vector<string> camposCrit;
    for (int i = 0; i < c.restricciones().size(); ++i) {
        camposCrit.push_back(static_cast<basic_string<char> &&>(get <0>(c.restricciones()[i])));
    }
    for (int i = 0; i< camposCrit.size(); i++) {
        if(!pertenece(camposCrit[i], t.campos())){
            return false;
        }
        if(camposRepetidos(camposCrit)){
            return false;
        }

    }
    return true;
}


Tabla Base::busqueda(string nombre, Criterio criterios){
    int pos ;
    for (int i = 0; i < _nombres.size(); ++i) {
        if (_nombres[i] == nombre) {
            pos = i;
        }
    }
    if (!criteriosValidos(_tablas[pos],criterios)){
        cout << "criterios NO validos" << endl;
        assert(false);
    }

    vector <Dato> tipos;
    for (int j = 0; j <_tablas[pos].campos().size() ; ++j) {
        tipos.push_back(_tablas[pos].tipoCampo(_tablas[pos].campos()[j]));
    }
    Tabla res(_tablas[pos].campos(), _tablas[pos].claves(), tipos);

    for (int i = 0; i <_tablas[pos].registros().size() ; ++i) {
        //Dato test = _tablas[pos].registros()[i].dato(campo);

        if (cumpleCond(_tablas[pos].registros()[i], criterios)){
            res.agregarRegistro(_tablas[pos].registros()[i]);
        }
    }
    return res;
}

Tabla Base::obtenerTabla(string nombre)const {
    assert(this->tablaDefinida(nombre));
    for (int i =0; i < _tablas.size();i++){
        if (_nombres[i]==nombre){
            return _tablas[i];
        }
    }
}




bool operator==(const Base& b1,const Base& b2){
    if(not seteq(b1.nombre() , b2.nombre())){
        return false;
    }
    else{
        for(int i=0; i < b1.nombre().size(); i++){
            if(b1.obtenerTabla(b2.nombre()[i])!= b2.obtenerTabla(b2.nombre()[i])){
                return false;
            }

        }

    }

    return true;

}
