#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Visual.h"
#include "logica.h"
#include "Archivos.h"

using namespace std;

Visual::Visual() {}

void Visual::manejar_Error(int error){
	switch(error){
		case 1:
			cout << "No se ha podido crear el historial" << endl;
			system("pause");
			break;
		case 2:
			cout << "No se ha podido agregar la partida al historial" << endl;
			system("pause");
			break;
		case 3:
			cout << "No se ha podido recuperar el historial" << endl;
			system("pause");
			break;
		case 4:
			cout << "No se ha podido guardar la partida" << endl;
			system("pause");
			break;
		case 5:
			cout << "No se ha podido cargar la partida" << endl;
			system("pause");
			break;
	}
}

int Visual::menu(){
	int opcion;
	cout << setw(70) << "-----------------------" << endl;
	cout << setw(70) << "| B U S C A M I N A S |" << endl;
	cout << setw(70) << "-----------------------" << endl << endl;
	cout << setw(62) << "1)  Nueva Partida. " << endl;
	cout << setw(74) << "2)  Renaudar Partida guardada. " << endl;
	cout << setw(64) << "3)  Mostrar Historial" << endl;
	cout << setw(64) << "4)  Salir del juego. " << endl << endl;
	
	opcion = validarNumero(1,4);
	return opcion;
}

int Visual::validarNumero(int minimo, int maximo){
	string opcion;
	do{
		cout << setw(66) << "Seleccione una opcion: ";
		cin >> opcion;
	}while(!esNumero(opcion) || stoi(opcion) < minimo || stoi(opcion) > maximo);
	return stoi(opcion);
}

bool Visual::esNumero(string s){
	for (char c : s) {
    	if (isdigit(c) == 0) 
			return false;
  }
  return true;
}

int Visual::configurar_partida()
{
	int opcion;
    system("cls");

	cout << "\n" << "\n" << "\n";
	cout << setw(70) << "Selecciona la dificultad de juego " << endl;
	cout << setw(70) << "-----------------------------------" << endl << endl;
	cout << setw(63) << "1) Fácil. (4x4 con 4 minas)." << endl;
	cout << setw(68) << "2) Intermedio. (6x6 con 10 minas)." << endl;
	cout << setw(65) << "3) Díficil.(8x8 con 12 minas)." << endl << endl;
	
	opcion = validarNumero(1,3);
	
	system("cls");
	return opcion;
};

void Visual::mostrar_Historial(LOG* datos){	
	cout << datos->getHistorial() << endl;
}

int Visual::seleccionar_Accion(Tablero* tablero)
{
	int opcion;
	system("cls");
	mostrar_Tablero(tablero);
	cout << "\n" << setw(62) << "--Opciones de juego--" << endl << "\n";
	cout << setw(60) << "1) Abrir casilla." << endl;
	cout << setw(62) << "2) Colocar bandera." << endl;
	cout << setw(61) << "3) Quitar bandera." << endl;
	cout << setw(55) << "4) Rendirse." << endl;
	cout << setw(62) << "5) Guardar partida." << endl << endl;
	
	opcion = validarNumero(1,5);
	
	return opcion;
}

Casilla* Visual::seleccionar_Casilla(Tablero* tablero){
	int fila, columna;
	cout << "Fila:" << endl;
	fila = validarNumero(0,7);
	cout << "Columna:" << endl;
	columna = validarNumero(0,7);
	
	return tablero->getCasilla(fila,columna);
}

void Visual::abrir_Casilla(Casilla* casilla)
{
	cout << "Abrirá la casilla (" << casilla->getX() << "," << casilla->getY() << ").";
}

void Visual::marcar_Casilla(Casilla* casilla)
{
	cout << "Marcará la casilla (" << casilla->getX() << "," << casilla->getY() << ").";
}

void Visual::desmarcar_Casilla(Casilla* casilla)
{
	cout << "Desmarcará la casilla (" << casilla->getX() << "," << casilla->getY() << ").";
}

void Visual::mostrar_Tablero(Tablero* t)
{
    cout << "\n" << "\n";
    cout << "  ";
    for (int col = 0; col < t->getColumnas(); col++)
        cout << col << " ";
    cout << endl << "  ";
	for (int col = 0; col < t->getColumnas(); col++)
        cout << "--";
    cout << endl;
    
    for (int fila = 0; fila < t->getFilas(); fila++)
    {
        cout << fila << "|";

        for (int columna = 0; columna < t->getColumnas(); columna++)
        {
            Casilla *casilla = t->getCasilla(fila, columna);
            if (casilla->isOpen())
            {
                if (casilla->getMina())
                    cout << "M ";
                else{
                	if(casilla->getMinasAlrededor() == 0)
                		cout << "  ";
                	else
                		cout << casilla->getMinasAlrededor() << " ";
				}
            }
            else if (casilla->isMarcada())
                cout << "B ";
            else
                cout << "* ";
        }
        cout << endl;
    }
}

void Visual::mensaje_winOrLose(Tablero* tablero)
{	
	switch(tablero->verificar_resultado()){
		case 0:
			cout << "BOOOOOM. Ha explotado una mina" << endl << endl;
			mostrar_Minas(tablero);
			cout << setw(63) << "--Juego finalizado--" << endl;
			cout << setw(63) << "¡Quiza la proxima!" << endl;
			system("pause");
			break;
		case 1:
			cout <<"Ha marcado todas las minas. Felicitaciones.";
			system("pause");
			break;
		case 2:
			cout <<"Ha abierto todas las casillas con éxito. Felicitaciones.";
			system("pause");
			break;
		case 3:
			cout << "Vuelve pronto a terminar tu partida. No te rindas";
			system("pause");
			break;
		case 4:
			cout << setw(63) << "Será para la proxima" << endl;
			cout << setw(63) << "No te rindas." << endl;
			system("pause");
			break;
	}
}

void Visual::mostrar_Minas(Tablero* t)
{
	cout << endl << endl << "Ubicacion de las Minas:" << endl;
    cout << " ";
    for (int col = 0; col < t->getColumnas(); col++)
        cout <<" "<< col;;
    cout << endl << "  ";
	for (int col = 0; col < t->getColumnas(); col++)
        cout << "--";
    cout << endl;
	
	for (int fila = 0; fila < t->getFilas(); fila++)
	{
		cout << fila << "|";
		for (int columna = 0; columna < t->getColumnas(); columna++)
		{
			Casilla *casilla = t->getCasilla(fila, columna);
			cout << casilla->getMina() << " ";
		}
		cout << endl;
	}
}




