//
// Created by jdurazzo on 06/09/17.
//
#include <iostream>
#include "Criterio.h"
#include "utils.h"


using namespace std;

Criterio::Criterio(vector<tuple <string, Dato, bool> > restricciones):
        _vecesUsado(0), _restricciones(restricciones){};

void Criterio::usar() {
    _vecesUsado++;
}

int Criterio::uso() const {
    return _vecesUsado;
}

vector <tuple <string, Dato, bool> > Criterio::restricciones() const{
    return _restricciones;
}

bool operator==(const Criterio& c1 , const Criterio& c2 ){
    if (c1.uso() != c2.uso()){
        return false;
    }else{
        return (seteq(c1.restricciones(), c2.restricciones()));
    }
}
