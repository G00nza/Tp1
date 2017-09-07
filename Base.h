#ifndef BASE_H
#define BASE_H
#include "Tabla.h"
#include <string>
#include "Criterio.h"

using namespace std;

class Base {

public:

	//Generador
	Base(vector<string> nombres, vector<Tabla> tablas, vector<vector <Criterio> >);

	//Generador
	void agregarTabla(string nombre, Tabla t);

	//Generador
	void agregarRegistroATabla(string nombre, Registro r);

	//observador
	bool tablaDefinida(string nombre)const;

	//observador
	Tabla obtenerTabla (string nombre)const;

	//otrasOperaciones
	bool estaDefinidoEn(string nombre, Registro r);

    vector<string> nombre() const ;

    Tabla busqueda(string nombre, Criterio criterios);
	
	/** FALTA LA DE BUSQUEDA
	 */
private:

	vector<string> _nombres;
    vector<Tabla> _tablas;
	vector<vector <Criterio> > _criterios;
    //Criterio _masUsado;
};

bool operator==(const Base&, const Base&);


#endif
