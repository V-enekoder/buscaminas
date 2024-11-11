#include <iostream>
#include <iomanip>
#include "Visual.h"

int main()
{
	Visual visual;
	LOG d;
	LOG* datos = &d;
	Tablero t;
	Tablero* tablero = &t;
	int opcion, error, dificultad, accion;
	string nombre;
	
	error = datos->crearHistorial();
	if(error){
		visual.manejar_Error(error);
		return 0;
	}
	
	while(1)
	{
		datos->limpiar();
		tablero->limpiar();
		
		opcion = visual.menu();
		system("cls");
	
		switch (opcion)
		{
		case 1:
			cout << "\n" << "\n" << "\n" << setw(60) << "--> Nombre del jugador: ";
			cin >> nombre;
			datos->setNombre(nombre);
			dificultad = visual.configurar_partida(); 
			tablero->setDificultad(dificultad);
			break;
		case 2:
			error =  datos->cargarTablero(tablero);
				if(error)
					visual.manejar_Error(error);
			break;
		case 3:
			error = datos->recuperarHistorial();
			if(error){
				visual.manejar_Error(error);
				break;
			}
			visual.mostrar_Historial(datos);
			system("pause");
			break;
		case 4:
			cout << "\n" << "\n" << "\n";
			cout << setw(75) << "Hasta luego, presione una tecla para salir..." << endl;
			return 0;
		}
		
		if(opcion != 3 && error != 5){
	
			while(tablero->seguir_partida())
			{
				accion = visual.seleccionar_Accion(tablero);
				
				if(accion == 4)
					break;
				
				if(accion == 5){
					datos->guardarTablero(tablero);
					break;
				}
			
				Casilla* casilla = visual.seleccionar_Casilla(tablero);
				system("cls");
				switch(accion){
					case 1:
						if(!casilla->isOpen() && casilla->isDisponible()){
							visual.abrir_Casilla(casilla);
							tablero->aumentarJugadas();
							if(casilla->getMina())
								casilla->setAbierta(true);
							else
								tablero->abrir_alrededor(casilla);
						}
						else{
							cout << "La casilla ya abierta." << endl;
							system("pause");
						}
						break;
					case 2:
						if(!casilla->isMarcada() && casilla->isDisponible()){
							visual.marcar_Casilla(casilla);
							casilla->marcarCasilla(true);
							tablero->aumentarJugadas();	
						}
						else{
							cout << "Casilla ya marcada.";
							system("pause");
						}
						break;
					case 3:
						if(casilla->isMarcada() && !casilla->isDisponible()){
							visual.desmarcar_Casilla(casilla);
							casilla->marcarCasilla(false);	
							tablero->aumentarJugadas();
						}
						else{
							cout << "Accion invalida.";
							system("pause");
						}
						break;
					}
					cout << endl << endl;
					visual.mostrar_Tablero(tablero);
					system("pause");
			} 
			system("cls");
			datos->agregarHistorial(tablero);
			visual.mensaje_winOrLose(tablero);
		}
		system("cls");	
	}
	return 0;
}