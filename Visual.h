#pragma once
#include <iostream>
#include "logica.h"
#include "Archivos.h"

using namespace std;

class Visual
{
public:
	Visual();
	void manejar_Error(int error);
	int menu();
	int validarNumero(int minimo, int maximo);
	bool esNumero(string s);
	int configurar_partida();
	void mostrar_Historial(LOG* datos);
	int seleccionar_Accion(Tablero* tablero);
	Casilla* seleccionar_Casilla(Tablero* tablero);
	void abrir_Casilla(Casilla* casilla);
	void marcar_Casilla(Casilla* casilla);
	void desmarcar_Casilla(Casilla* casilla);
	void mostrar_Tablero(Tablero* t);
	void mensaje_winOrLose(Tablero* tablero);
	void mostrar_Minas(Tablero* t);	
};