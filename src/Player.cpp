#include "Player.h"
#include <iostream>
#include <SDL2/SDL_image.h>

using namespace std;

Player::Player(SDL_Renderer *renderTarget, std::string archivo, int x, int y, int framesX, int framesY) {
	SDL_Surface *surface = IMG_Load(archivo.c_str());
	if (surface == NULL) {
		cout << "Error textura" << endl;
	} else {
		textura = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (textura == NULL)
			cout << "Error optimizedSurface" << endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(textura, NULL, NULL, &cropRect.w, &cropRect.h);

	// posicion inicial del jugador
	posicionPlayer.x = x;
	posicionPlayer.y = y;

	anchoTextura = cropRect.w;
	altoTextura = cropRect.h;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	anchoFrame = posicionPlayer.w = cropRect.w;
	altoFrame = posicionPlayer.h = cropRect.h;

	originX = anchoFrame / 2;
	originY = altoFrame / 2;

	contadorFrames = 0;
	estaActivo = false;

	static int playerNumber = 0;
	playerNumber ++;

	if (playerNumber == 1) {
		keys[0] = SDL_SCANCODE_UP;
		keys[1] = SDL_SCANCODE_DOWN;
		keys[2] = SDL_SCANCODE_LEFT;
		keys[3] = SDL_SCANCODE_RIGHT;
	}

	velocidadMov = 200.0f;
}

Player::~Player() {
	SDL_DestroyTexture(textura);
}

void Player::Update(float tiempoDelta, const Uint8 *keyState) {
	estaActivo = true;
	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[keys[0]]) {
		posicionPlayer.y -= velocidadMov * tiempoDelta;
		cropRect.y = altoFrame * 3;
	}
	else if (keyState[keys[1]]) {
		posicionPlayer.y += velocidadMov * tiempoDelta;
		cropRect.y = 0;
	}
	else if (keyState[keys[2]]) {
		posicionPlayer.x -= velocidadMov * tiempoDelta;
		cropRect.y = altoFrame;
	}
	else if (keyState[keys[3]]) {
		posicionPlayer.x += velocidadMov * tiempoDelta;
		cropRect.y = altoFrame * 2;
	}
	else
		estaActivo = false;

	if (estaActivo) {
		contadorFrames += tiempoDelta;

		if (contadorFrames >= 0.25f) {
			contadorFrames = 0;
			cropRect.x += anchoFrame;
			if (cropRect.x >= anchoTextura)
				cropRect.x = 0;
		} else {
			contadorFrames = 0;
			cropRect.x = anchoFrame;
		}
	}
}

void Player::Dibujar(SDL_Renderer *renderTarget, SDL_Rect camaraRect) {
	SDL_Rect drawingRect = {posicionPlayer.x - camaraRect.x, posicionPlayer.y - camaraRect.y, posicionPlayer.w, posicionPlayer.h};
	SDL_RenderCopy(renderTarget, textura, &cropRect, &drawingRect);
}


int Player::GetOriginX() {
	return originX;
}

int Player::GetOriginY() {
	return originY;
}
