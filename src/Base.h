#ifndef BASE_H
#define BASE_H
#include "Tabla.h"
#include <string>

using namespace std;

class Base {

public:

	//Generador
	Base(vector<string> nombres, vector<Tabla> tablas);

	//Generador
	void agregarTabla(string nombre, Tabla t);

	//Generador
	void agregarRegistroATabla(string nombre, Registro r);

	//observador
	bool tablaDefinida(string nombre);

	//observador
	//Tabla obtenerTabla (string nombre);

	//otrasOperaciones
	bool estaDefinidoEn(string nombre, Registro r);

    vector<string> nombre() const ;

	
	/** FALTA LA DE BUSQUEDA
	 */
private:

	vector<string> _nombres;
    vector<Tabla> _tablas;
};

#endif
