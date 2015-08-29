#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"

#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 480
#define FPS 60

using namespace std;

SDL_Texture *LoadTexture(string archivo, SDL_Renderer *renderTarget) {
	SDL_Surface *surface = IMG_Load(archivo.c_str());
	SDL_Texture *textura = nullptr;
	if (surface == NULL) {
		cout << "Error surface LoadTexture" << endl;
	} else {
		textura = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (textura == NULL)
			cout << "Error textura LoadTexture" << endl;
	}

	SDL_FreeSurface(surface);
	return textura;
}


int main(int argc, char **argv) {

	bool corriendo = true;
	SDL_Event evento;
	SDL_Window *ventana = nullptr;
	SDL_Renderer *renderTargetPlayer = nullptr;
	SDL_Texture *imagenPlayer = nullptr;
	SDL_Texture *textura = nullptr;
	SDL_Rect playerRect;
	SDL_Rect posicionPlayer;
	posicionPlayer.x = posicionPlayer.y = 0;
	posicionPlayer.w = posicionPlayer.h = 32;
	SDL_Rect camaraRect = {0, 0, ANCHO_PANTALLA, ALTO_PANTALLA};

	int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f;
	const Uint8 *keyState;


	// Inicia SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error en SDL_Init" << SDL_GetError() << endl;
		return 1;
	}


	// Pantalla principal
	ventana = SDL_CreateWindow("Age of Empires",
		   	   	   	   	   	  SDL_WINDOWPOS_CENTERED,
		   	   	   	   	   	  SDL_WINDOWPOS_CENTERED,
		   	   	   	   	   	  ANCHO_PANTALLA,
		   	   	   	   	   	  ALTO_PANTALLA,
		   	   	   	   	   	  SDL_WINDOW_RESIZABLE   );
	if (ventana == NULL)
		cout << "Error en ventana" << endl << SDL_GetError() << endl;


	// Flags para las imagenes
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(imgFlags) != imgFlags)
		cout << "Error imgFLags" << IMG_GetError() << endl;


	renderTargetPlayer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED |
											SDL_RENDERER_PRESENTVSYNC);


	// Personaje
	Player player1(renderTargetPlayer, "img/charac.png", 0, 0, 3, 4);

	SDL_SetRenderDrawColor(renderTargetPlayer, 0xFF, 0, 0, 0xFF); // color de fondo rojo

	textura = LoadTexture("img/back.png", renderTargetPlayer);


   // Loop principal
	while (corriendo) {
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - prevTime) / 1000.0f;
		// recibo eventos
		while (SDL_PollEvent( &evento ) != 0) {
			switch (evento.type) {
			// Cerrar pantalla
			case SDL_QUIT:
				corriendo = false;
				break;
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		player1.Update(delta, keyState);

		camaraRect.x = player1.GetOriginX() - (ANCHO_PANTALLA / 2);
		camaraRect.y = player1.GetOriginY() - (ALTO_PANTALLA / 2);

		if (camaraRect.x < 0)
			camaraRect.x = 0;
		if (camaraRect.y < 0)
			camaraRect.y = 0;

		SDL_RenderClear(renderTargetPlayer);
		SDL_RenderCopy(renderTargetPlayer, textura, &camaraRect, NULL);
		player1.Dibujar(renderTargetPlayer, camaraRect);
		SDL_RenderPresent(renderTargetPlayer),
		SDL_UpdateWindowSurface(ventana); // actualizo ventana!
	}

	ventana = nullptr;
	renderTargetPlayer = nullptr;

	SDL_Delay(100); // tardar al cerrar
	SDL_DestroyWindow(ventana);
	SDL_DestroyTexture(textura);
	SDL_DestroyRenderer(renderTargetPlayer);
	IMG_Quit();
	SDL_Quit();

	cout << "FLOR llega hasta return :)" << endl;
	return 0;
}
