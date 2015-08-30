#ifndef JUEGO_H_
#define JUEGO_H_

#include <SDL2/SDL.h>
#include <string>
#include "defs.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Player.h"

using namespace std;

class Juego {

private:
	bool juegoCorriendo;
	SDL_Window *ventana = nullptr;
	SDL_Renderer *render = nullptr;
	SDL_Texture *textura = nullptr;
	Player *player;
	SDL_Rect camaraRect;

public:
	Juego();
	virtual ~Juego();
	void cargarJuego();
	int initJuego();
	void inputJuego();
	void dibujarJuego(float delta);
	void updateJuego();
	void limpiarJuego();
	bool estaCorriendo();
};

#endif /* JUEGO_H_ */
