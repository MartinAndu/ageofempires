#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <SDL2/SDL.h>

class Player {

private:
	SDL_Rect cropRect;
	SDL_Texture *textura;
	float velocidadMov;
	float contadorFrames;
	float anchoFrame;
	float altoFrame;
	float estaActivo;
	int anchoTextura;
	int altoTextura;
	SDL_Scancode keys[4];
	int originX, originY;

public:
	Player(SDL_Renderer *renderTarget, std::string archivo, int x, int y, int framesX, int framesY);
	virtual ~Player();

	void Update(float tiempoDelta, const Uint8 *keyState);
	void Dibujar(SDL_Renderer *renderTarget, SDL_Rect camaraRect);

	SDL_Rect posicionPlayer;
	int GetOriginX();
	int GetOriginY();
};

#endif /* PLAYER_H_ */
