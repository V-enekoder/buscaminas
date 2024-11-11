#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Casilla
{
private:
    int x, y, minas_alrededor;
    bool mina, abierta,marcada, disponible;

public:
	Casilla();
    Casilla(int a, int b);
    void setX(int a);
    int getX();
	void setY(int a);
	int getY();
	void setMinasAlrededor(int minas);
	int getMinasAlrededor();
	void incrementarMinasAlrededor();
	void setMina(bool mina);
    bool getMina();
    void setAbierta(bool abierta);
    bool isOpen();
    void marcarCasilla(bool bandera);
    bool isMarcada();
    void setDisponible(bool disponible);
    bool isDisponible();
};

class Tablero
{
private:
    int filas, columnas, minas;
    int jugadas;
    bool guardado;
    Casilla *tablero[8][8];
    
	void crear(int filas, int columnas, int minas);
    void asignar_minas();
    void actualizar_minas_alrededor();
    void aumentar(int fila, int columna);
    bool dentro_limites(int fila, int columna);
    
public:
	Tablero();
    void setFilas(int filas);
	int getFilas();
   void setColumnas(int columnas);
    int getColumnas();
    void setMinas(int minas);
	int getMinas();
    void setJugadas(int jugadas);
    int getJugadas();
    void aumentarJugadas();
	void setGuardado(bool guardado);
	bool getGuardado();	
	Casilla* getCasilla(int fila, int columna);	
	void setDificultad(int Dificultad);
    bool seguir_partida();
    void abrir_alrededor(Casilla* casilla);
    vector<Casilla*> Obtener_Casillas_Alrededor(Casilla* casilla);
    int verificar_resultado();
    void limpiar();
};