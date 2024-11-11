#pragma once
#include <iostream>
#include <time.h>  //para la hora y fecha actual o en tiempo real
#include <fstream> //manejo de archivos
#include "logica.h"

using namespace std;

class LOG
{
	private:
		string nombre,historial;
	    
		string HoraActual();
	    string FechaActual();
	public:
		LOG();
		LOG(string n);
		void setNombre(string nombre);
	    string getNombre();
		string getHistorial();
		int crearHistorial();
		int cargarTablero(Tablero* tablero);
		int recuperarHistorial();
		int guardarTablero(Tablero* tablero);
		int agregarHistorial(Tablero* tablero);
	    void limpiar();
};
