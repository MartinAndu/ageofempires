#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"

#define ANCHO_PANTALLA 640
#define ALTO_PANTALLA 480
#define FPS 60

using namespace std;

SDL_Texture *LoadTexture(string archivo, SDL_Renderer *render) {
	SDL_Surface *superficie = IMG_Load(archivo.c_str());
	SDL_Texture *textura = nullptr;
	if (superficie == NULL) {
		cout << "Error superficie LoadTexture" << endl;
	} else {
		textura = SDL_CreateTextureFromSurface(render, superficie);
		if (textura == NULL)
			cout << "Error textura LoadTexture" << endl;
	}

	SDL_FreeSurface(superficie);
	return textura;
}


int main(int argc, char **argv) {

	bool corriendo = true;

	SDL_Window *ventana = nullptr;
	SDL_Renderer *render = nullptr;
	SDL_Texture *textura = nullptr;
	SDL_Event evento;

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


	// Flags para las imagenes
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(imgFlags) != imgFlags)
		cout << "Error en imgFLags" << IMG_GetError() << endl;


	// Pantalla principal
	ventana = SDL_CreateWindow("Age of Empires",
		   	   	   	   	   	  SDL_WINDOWPOS_CENTERED,
		   	   	   	   	   	  SDL_WINDOWPOS_CENTERED,
		   	   	   	   	   	  ANCHO_PANTALLA,
		   	   	   	   	   	  ALTO_PANTALLA,
		   	   	   	   	   	  SDL_WINDOW_RESIZABLE   );
	if (ventana == NULL)
		cout << "Error en ventana" << endl << SDL_GetError() << endl;


	render = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED |
											SDL_RENDERER_PRESENTVSYNC);
	if (render == NULL)
		cout << "Error en render" << endl;

	textura = LoadTexture("img/back.png", render);
	SDL_SetRenderDrawColor(render, 0xFF, 0, 0, 0xFF); // color de fondo rojo


	// Personaje
	Player player1(render, "img/charac.png", 0, 0, 3, 4);


   // Loop principal
	while (corriendo) {
		prevTime = currentTime;
		currentTime = SDL_GetTicks(); // milisegundos desde que inicio
		delta = (currentTime - prevTime) / 1000.0f;

		// recibo eventos
		while (SDL_PollEvent( &evento ) != 0) {
			switch (evento.type) {
			// cerrar pantalla
			case SDL_QUIT:
				corriendo = false;
				break;
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		player1.Update(delta, keyState);

		camaraRect.x = player1.GetOrigenX() - (ANCHO_PANTALLA / 2);
		camaraRect.y = player1.GetOrigenY() - (ALTO_PANTALLA / 2);

		if (camaraRect.x < 0)
			camaraRect.x = 0;
		if (camaraRect.y < 0)
			camaraRect.y = 0;

		SDL_RenderClear(render);
		SDL_RenderCopy(render, textura, &camaraRect, NULL);
		player1.Dibujar(render, camaraRect);
		SDL_RenderPresent(render),
		SDL_UpdateWindowSurface(ventana); // actualizo ventana!
	}

	ventana = nullptr;
	render = nullptr;
	textura = nullptr;

	SDL_Delay(100); // tardar al cerrar
	SDL_DestroyWindow(ventana);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(textura);
	IMG_Quit();
	SDL_Quit();

	cout << "FLOR llega hasta return :)" << endl;
	return 0;
}
