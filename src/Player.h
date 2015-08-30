#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <SDL2/SDL.h>

class Player {

private:
	float estaActivo;

	SDL_Texture *textura; // imagen inicial para animacion
	int anchoTextura;
	int altoTextura;
	SDL_Rect cropRect; // para obtener w y h de la textura
	float anchoFrame;
	float altoFrame;

	float contadorFrames;
	float velocidadMov;

	SDL_Scancode keys[4]; // teclas que utiliza el jugador

	int origenX, origenY;

public:
	Player();
	Player(SDL_Renderer *render, std::string archivo, int posX, int posY, int cantFramesX, int cantFramesY);
	virtual ~Player();

	void Update(float tiempoDelta, const Uint8 *keyState);
	void Dibujar(SDL_Renderer *render, SDL_Rect camaraRect);

	SDL_Rect posicionPlayer;
	int GetOrigenX();
	int GetOrigenY();
};

#endif /* PLAYER_H_ */
