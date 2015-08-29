#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define ANCHO_PANTALLA 500
#define ALTO_PANTALLA 300
#define FPS 60

using namespace std;


SDL_Texture *LoadTexture(string filePath, SDL_Renderer *renderTarget) {
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	SDL_Texture *texture;
	if (surface == NULL) {
		cout << "Error textura" << endl;
	} else {
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			cout << "Error optimizedSurface" << endl;
	}
	SDL_FreeSurface(surface);
	return texture;
}


int main(int argc, char **argv) {

	bool corriendo = true;
	SDL_Event evento;
	SDL_Window *ventana = nullptr;
	SDL_Renderer *renderTargetPlayer = nullptr;
	SDL_Texture *imagenPlayer = nullptr;
	SDL_Rect playerRect;
	SDL_Rect posicionPlayer;
	posicionPlayer.x = posicionPlayer.y = 0;
	posicionPlayer.w = posicionPlayer.h = 32;
	int anchoFrame, altoFrame;
	int anchoTextura, altoTextura;
	// para que corra igual sin importar la velocidad de las computadoras
	float frameTime = 0;
	int prevTime = 0;
	int currentTime = 0;
	float tiempoDelta = 0;
	float velocidadMov = 200.0f;
	// para que no tarde en arrancar el personaje
	const Uint8 *keyState;


	// Inicia SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error en SDL_Init" << SDL_GetError() << endl;
		return 1;
	}


	// Pantalla principal
	ventana = SDL_CreateWindow("Age of Empires",
		   	   	   	   	   	  SDL_WINDOWPOS_UNDEFINED,
		   	   	   	   	   	  SDL_WINDOWPOS_UNDEFINED,
		   	   	   	   	   	  ANCHO_PANTALLA,
		   	   	   	   	   	  ALTO_PANTALLA,
		   	   	   	   	   	  SDL_WINDOW_RESIZABLE   );
	if (ventana == NULL)
		cout << "Error en ventana" << endl << SDL_GetError() << endl;


	// Flags para las imagenes
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(imgFlags) != imgFlags)
		cout << "Error imgFLags" << IMG_GetError() << endl;


	// Personaje
	renderTargetPlayer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED |
											SDL_RENDERER_PRESENTVSYNC);
	imagenPlayer = LoadTexture("img/charac.png", renderTargetPlayer);
	SDL_QueryTexture(imagenPlayer, NULL, NULL, &anchoTextura, &altoTextura);

	anchoFrame = anchoTextura / 3;
	altoFrame = altoTextura / 4;

	playerRect.x = playerRect.y = 0;
	playerRect.w = anchoFrame;
	playerRect.h = altoFrame;

	SDL_SetRenderDrawColor(renderTargetPlayer, 0xFF, 0, 0, 0xFF); // color de fondo rojo


   // Loop principal
	while (corriendo) {

		prevTime = currentTime;
		currentTime = SDL_GetTicks(); // milisegundos desde que corre el juego
		// cuanto paso desde el frame anterior
		tiempoDelta = (currentTime - prevTime) / 1000.0f;

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
		if (keyState[SDL_SCANCODE_RIGHT])
			posicionPlayer.x += velocidadMov * tiempoDelta;
		else if (keyState[SDL_SCANCODE_LEFT])
			posicionPlayer.x -= velocidadMov * tiempoDelta;

		if (keyState[SDL_SCANCODE_DOWN])
			posicionPlayer.y += velocidadMov * tiempoDelta;
		else if (keyState[SDL_SCANCODE_UP])
			posicionPlayer.y -= velocidadMov * tiempoDelta;

		frameTime += tiempoDelta;
		if (frameTime >= 0.25f) {
			frameTime = 0;
			playerRect.x += anchoFrame;
			if (playerRect.x >= anchoTextura)
				playerRect.x = 0;
		}

		SDL_RenderClear(renderTargetPlayer);
		SDL_RenderCopy(renderTargetPlayer, imagenPlayer, &playerRect, &posicionPlayer);
		SDL_RenderPresent(renderTargetPlayer),
		SDL_UpdateWindowSurface(ventana); // actualizo!
	}

	SDL_Delay(100); // tardar al cerrar
	SDL_DestroyWindow(ventana);
	SDL_Quit();

	cout << "FLOR llega hasta return :)" << endl;
	return 0;
}
