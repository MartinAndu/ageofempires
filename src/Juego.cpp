#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Juego.h"
#include "Player.h"

using namespace std;

SDL_Texture *CargarTextura(string archivo, SDL_Renderer *render) {
	SDL_Surface *superficie = IMG_Load(archivo.c_str());
	SDL_Texture *textura = nullptr;
	if (superficie == NULL) {
		cout << "Error superficie CargarTextura en Juego" << endl;
	} else {
		textura = SDL_CreateTextureFromSurface(render, superficie);
		if (textura == NULL)
			cout << "Error textura CargarTextura en Juego" << endl;
	}

	SDL_FreeSurface(superficie);
	return textura;
}

Juego::Juego() {
	ventana = nullptr;
	render = nullptr;
	textura = nullptr;
	player = nullptr;
	juegoCorriendo = false;
}

Juego::~Juego() {
	ventana = nullptr;
	render = nullptr;
	textura = nullptr;
	player = nullptr;
}

int Juego::initJuego() {
	juegoCorriendo = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error en SDL_Init" << SDL_GetError() << endl;
		return 1;
	}
	return 0;
}

void Juego::cargarJuego() {

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

	// Flags para las imagenes
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(imgFlags) != imgFlags)
		cout << "Error en imgFLags" << IMG_GetError() << endl;

	textura = CargarTextura("img/back.png", render);

	player = new Player(render, "img/charac.png", 0, 0, FRAMES_X_PJ, FRAMES_Y_PJ);

	camaraRect = {0, 0, ANCHO_PANTALLA, ALTO_PANTALLA};
}

void Juego::inputJuego() {
	SDL_Event evento;
	while (SDL_PollEvent( &evento ) != 0) {
		if (evento.type == SDL_QUIT) {
			juegoCorriendo = false;
			break;
		}
	}
}

// todo Limpiar esta chanchada
void Juego::dibujarJuego(float delta) {
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);
	player->Update(delta, keyState);
	// todo para el scroll
	camaraRect.x = player->GetOrigenX() - (ANCHO_PANTALLA / 2);
	camaraRect.y = player->GetOrigenY() - (ALTO_PANTALLA / 2);

	if (camaraRect.x < 0)
		camaraRect.x = 0;
	if (camaraRect.y < 0)
		camaraRect.y = 0;
	SDL_RenderClear(render);
	SDL_RenderCopy(render, textura, &camaraRect, NULL);
	player->Dibujar(render, camaraRect);
	SDL_RenderPresent(render);
}

// todo juntarlo con dibujarJuego
void Juego::updateJuego() {

}

void Juego::limpiarJuego() {
	SDL_Delay(100); // tardar al cerrar
	delete player;
	SDL_DestroyWindow(ventana);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(textura);
	IMG_Quit();
	SDL_Quit();
}

bool Juego::estaCorriendo() {
	return juegoCorriendo;
}
