#include <iostream>
#include <time.h>  //libreria con la que se maneja la hora y la fecha real
#include <ctime>   // Obtener tiempo real del juego
#include <fstream> //para el manejo de los archivos
#include <iomanip>
#include "Archivos.h"
#include "Logica.h"

using namespace std;

LOG::LOG(): nombre(""), historial(""){}


void LOG::setNombre(string nombre)
{
	this->nombre = nombre;
}

string LOG::getNombre()
{
        return this->nombre;
}

string LOG::getHistorial()
{
	return this->historial;
}

int LOG::crearHistorial(){
	ofstream archivo("Historial.txt");
	
	if(!archivo.is_open())
		return 1;
	
	archivo << "Nombre     " << "Fecha        " << "Hora     " << "Tablero     " <<
		"Minas     " << "Jugadas     " << "Resultado     " << endl;
	archivo.close();
	return 0;
}

int LOG::cargarTablero(Tablero* tablero)
{
    ifstream archivo("Partida Guardada.txt");
    
    if(!archivo.is_open())
    	return 5;

	int filas, columnas, minas, jugadas;
	int x, y, minas_alrededor;
    bool mina, abierta, marcada, disponible;
    Casilla* nuevaCasilla;
    archivo >> filas >> columnas >> minas >> jugadas;  
    tablero->setFilas(filas);
    tablero->setColumnas(columnas);
    tablero->setMinas(minas);
    tablero->setJugadas(jugadas);
    tablero->setGuardado(false);
    
    for (int i = 0; i < tablero->getFilas(); i++)
    {
        for (int j = 0; j < tablero->getColumnas(); j++)
        {
        	nuevaCasilla = tablero->getCasilla(i,j);
            archivo >> x >> y >> minas_alrededor >> mina >> abierta >> marcada >> disponible;
			nuevaCasilla->setX(x);
			nuevaCasilla->setY(y);
			nuevaCasilla->setMinasAlrededor(minas_alrededor);
			nuevaCasilla->setMina(mina);
			nuevaCasilla->setAbierta(abierta);
			nuevaCasilla->marcarCasilla(marcada);
			nuevaCasilla->setDisponible(disponible);
        }
    }
    archivo.close(); 
    return 0;
}

int LOG::recuperarHistorial()
{

    ifstream archivo("Historial.txt");
	
	if(!archivo.is_open())
		return 3;

    string line;
    while (getline(archivo, line))
    {
        historial += line + "\n";  
    }

    archivo.close();
    return 0;
}

int LOG::guardarTablero(Tablero* tablero)
{
	ofstream archivo("Partida Guardada.txt",ios::trunc);
    
	if(!archivo.is_open())
		return 4;
	
	tablero->setGuardado(true);
    archivo << tablero->getFilas() << " " << tablero->getColumnas() << " " << tablero->getMinas() 
	<<" "<< tablero->getJugadas() << "\n"; 
	
	Casilla* casilla;
	
    for (int i = 0; i < tablero->getFilas(); i++)
    {
        for (int j = 0; j < tablero->getColumnas(); j++)
        {
        	casilla = tablero->getCasilla(i,j);
            archivo << casilla->getX() << " " << casilla->getY() << " "
                    << casilla->getMinasAlrededor() << " " << casilla->getMina() << " "
                    << casilla->isOpen() << " " << casilla->isMarcada() << " "
                    << casilla->isDisponible() << "\n";
        }
    }

    archivo.close();
    return 0;
}

int LOG::agregarHistorial(Tablero* tablero)
{
	ofstream archivo("Historial.txt", std::ios::app);
	
	if(!archivo.is_open())
		return 2;
	
	string resultado;

	if(tablero->verificar_resultado() == 1 || tablero->verificar_resultado() == 2)
		resultado = "Victoria.";
	else if(tablero->verificar_resultado() == 3)
		resultado = "Inconclusa.";
	else
		resultado = "Derrota.";
				
	archivo << nombre <<"     "<< this->FechaActual() <<"     "<< this->HoraActual()
		<<"     " << tablero->getFilas() << "x" << tablero->getColumnas() << "          " 
		<< tablero->getMinas() <<"          "<< tablero->getJugadas() <<"          "<< resultado << endl;		
	archivo.close();
	return 0;
}

// Funcion para obtener fecha actual en formato DD/MM/YY
string LOG::FechaActual()
{
    time_t tiempoActual = time(0); // guarda el tiempo actual.
    tm *time = localtime(&tiempoActual);
    char fecha[9];
    strftime(fecha, sizeof(fecha), "%d/%m/%y", time);
    return fecha;
}

// Funcion que permite obtener la hora actual en formato HH:MM
string LOG::HoraActual()
{
    time_t tiempoActual = time(0); 
    tm *tiempo = localtime(&tiempoActual);
    char hora[6];
    strftime(hora, sizeof(hora), "%H:%M", tiempo); 
    string horaFormateada(hora);                  
    return horaFormateada;
}

void LOG::limpiar(){
	this->nombre = "";
	this->historial = "";
}