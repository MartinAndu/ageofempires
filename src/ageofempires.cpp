#include <iostream>
#include "Juego.h"

using namespace std;


int main(int argc, char **argv) {

	Juego *juego = new Juego();

	int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f;



	// Inicia SDL
	if (juego->initJuego() != 0)
		return 1;


	// Inicializo juego
	juego->cargarJuego();


   // Loop principal
	while (juego->estaCorriendo()) {
		// todo revisar tiempos
		prevTime = currentTime;
		currentTime = SDL_GetTicks(); // milisegundos desde que inicio
		delta = (currentTime - prevTime) / 1000.0f;


		// Tomo input del usuario
		juego->inputJuego();

		// Dibujo cosas en la pantalla
		juego->dibujarJuego(delta);

		// Update
	}


	// Elimino el juego
	juego->limpiarJuego();

	delete juego;
	cout << "FLOR llega hasta return :)" << endl;
	return 0;
}
