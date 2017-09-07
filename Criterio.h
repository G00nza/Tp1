//
// Created by jdurazzo on 06/09/17.
//

#ifndef TP1_CRITERIO_H
#define TP1_CRITERIO_H
#include <tuple>
#include <vector>
#include "Dato.h"
using namespace std;

class Criterio {

public:

    //generador
    Criterio(vector<tuple <string, Dato, bool> > restricciones);

    //gen
    void usar();

    //obs
    int uso() const ;

    //obs
    vector <tuple <string, Dato, bool> > restricciones() const;



private:
    vector<tuple <string, Dato, bool> > _restricciones;
    int _vecesUsado;
};

bool operator==(const Criterio& , const Criterio&);

#endif //TP1_CRITERIO_H
