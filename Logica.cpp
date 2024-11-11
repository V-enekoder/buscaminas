#include "logica.h"
#include "Visual.h"
#include <vector>

Casilla::Casilla(){}

Casilla::Casilla(int a, int b) : x(a), y(b), minas_alrededor(0),
								mina(false), abierta(false),
                                marcada(false),
								disponible(true) {}

void Casilla::setX(int a)
{
    x = a;
}

int Casilla::getX()
{
    return x;
}

void Casilla::setY(int a)
{
    y = a;
}

int Casilla::getY()
{
    return y;
}

void Casilla::setMinasAlrededor(int minas)
{
	this->minas_alrededor = minas;
}

int Casilla::getMinasAlrededor()
{
    return minas_alrededor;
}

void Casilla::incrementarMinasAlrededor()
{
    minas_alrededor++;
}

void Casilla::setMina(bool mina)
{
    this->mina = mina;
}

bool Casilla::getMina()
{
    return mina;
}

void Casilla::setAbierta(bool abierta)
{	
		this->abierta = abierta;	
		disponible = false;	
}

bool Casilla::isOpen()
{
    return abierta;
}

void Casilla::marcarCasilla(bool bandera)
{
	if(bandera){
		marcada = true;
    	disponible = false;
	}
    else{
    	marcada = false;
    	disponible = true;
	}
}

bool Casilla::isMarcada()
{
    return marcada;
}

void Casilla::setDisponible(bool disponible)
{
	this->disponible = disponible;
}

bool Casilla::isDisponible()
{
	return disponible;
}



Tablero::Tablero(){}

void Tablero::setFilas(int filas)
{
	this->filas = filas;
}

int Tablero::getFilas()
{
    return filas;
}

void Tablero::setColumnas(int columnas)
{
	this->columnas = columnas;
}

int Tablero::getColumnas()
{
    return columnas;
}

void Tablero::setMinas(int minas)
{
	this->minas = minas;
}

int Tablero::getMinas()
{
    return minas;
}

void Tablero::setJugadas(int jugadas)
{
	this->jugadas = jugadas;
}

int Tablero::getJugadas()
{
	return this->jugadas;
}

void Tablero::aumentarJugadas(){
	jugadas++;
}

void Tablero::setGuardado(bool guardado)
{
	this->guardado = guardado;
}

bool Tablero::getGuardado()
{
	return guardado;
}

Casilla *Tablero::getCasilla(int fila, int columna)
{
    return tablero[fila][columna];
}

void Tablero::setDificultad(int Dificultad){
	switch (Dificultad){
	case 1:
		crear(4,4,4);
		break;
	case 2:
		crear(6,6,10);
		break;
	case 3:
		crear(8,8,12);
		break;
	}
}

void Tablero::crear(int filas, int columnas, int minas)
{
    this->filas = filas;
    this->columnas = columnas;
    this->minas = minas;
    this->jugadas = 0;

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)

            tablero[i][j] = new Casilla(i, j);
    }

    asignar_minas();
    actualizar_minas_alrededor();
}

void Tablero::asignar_minas()
{
    int i, j, minas_generadas = 0;

    srand(time(nullptr));

    while (minas_generadas != minas)
    {
        i = rand() % filas;
        j = rand() % columnas;
        if (!tablero[i][j]->getMina())
        {
            tablero[i][j]->setMina(true);
            minas_generadas++;
        }
    }
}

void Tablero::actualizar_minas_alrededor()
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (tablero[i][j]->getMina())
                aumentar(i, j);
        }
    }
}

void Tablero::aumentar(int fila, int columna)
{
    for (int i = fila - 1; i <= fila + 1; i++)
    {
        for (int j = columna - 1; j <= columna + 1; j++)
        {
            if (dentro_limites(i, j) && (i != fila || j != columna) && !tablero[i][j]->getMina())
                tablero[i][j]->incrementarMinasAlrededor();
        }
    }
}

bool Tablero::dentro_limites(int fila, int columna)
{
    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas)
        return 1;
    return 0;
}

bool Tablero::seguir_partida()
{
    int casillas_abiertas = 0, minas_marcadas = 0;
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
        	if(tablero[i][j]->isMarcada() && tablero[i][j]->getMina())
        		minas_marcadas++;
            if (tablero[i][j]->isOpen())
                casillas_abiertas++;
            if(tablero[i][j]->isOpen() && tablero[i][j]->getMina())
				return 0;	
        }
    }
    if(minas_marcadas == minas || casillas_abiertas == filas * columnas - minas){
		return 0;	
	}
    return 1;
}

void Tablero::abrir_alrededor(Casilla* casilla)
{
	casilla->setAbierta(true);
	if(casilla->getMinasAlrededor() == 0)
	{
		vector<Casilla*> lista_alrededor = Obtener_Casillas_Alrededor(casilla);
		for(Casilla* casillas: lista_alrededor)
		{
			if(!casillas->isOpen())
				abrir_alrededor(casillas);
		}				
	}
}

vector<Casilla*> Tablero::Obtener_Casillas_Alrededor(Casilla* casilla)
{
	
	vector<Casilla*> alrededor;
	for (int i = casilla->getX() - 1; i <= casilla->getX() + 1; i++)
    {
        for (int j = casilla->getY() - 1; j <= casilla->getY() + 1; j++)
        {
            if (dentro_limites(i, j) && (i != casilla->getX() || j != casilla->getY()) && !tablero[i][j]->getMina())
				alrededor.push_back(getCasilla(i,j));	
        }
    }
	return alrededor;
}

int Tablero::verificar_resultado()
{
	int casillas_abiertas = 0, minas_marcadas = 0;	
	for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
        	if(tablero[i][j]->isMarcada() && tablero[i][j]->getMina())
        		minas_marcadas++;
            if (tablero[i][j]->isOpen())
                casillas_abiertas++;
            if(tablero[i][j]->isOpen() && tablero[i][j]->getMina())
            	return 0;
        }
    }
    if(minas_marcadas == minas)
    	return 1;
    else if(casillas_abiertas == filas * columnas - minas)
    	return 2;
    else if(guardado == true)
    	return 3;
    return 4;
}

void Tablero::limpiar(){
	this->filas = 0;
	this->columnas = 0;
	this->minas = 0;
	this->jugadas = 0;
	this->guardado = false;
	for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            tablero[i][j] = new Casilla(i, j);
    }
}

