#include "Player.h"
#include <iostream>
#include <SDL2/SDL_image.h>

using namespace std;

Player::Player(SDL_Renderer *render, std::string archivo, int posX, int posY, int cantFramesX, int cantFramesY) {
	SDL_Surface *superficie = IMG_Load(archivo.c_str());
	if (superficie == NULL) {
		cout << "Error en superficie Player" << endl;
	} else {
		textura = SDL_CreateTextureFromSurface(render, superficie);
		if (textura == NULL)
			cout << "Error en textura Player" << endl;
	}

	SDL_FreeSurface(superficie); // borro superficie, ya la converti en textura

	SDL_QueryTexture(textura, NULL, NULL, &cropRect.w, &cropRect.h); // obtengo w y h de la textura

	// posicion inicial del jugador
	posicionPlayer.x = posX;
	posicionPlayer.y = posY;

	// defino w y h de la textura
	anchoTextura = cropRect.w;
	altoTextura = cropRect.h;

	// el rectangulo es w y h de la textura dividido la cantidad de dibujos
	cropRect.w /= cantFramesX;
	cropRect.h /= cantFramesY;

	anchoFrame = posicionPlayer.w = cropRect.w;
	altoFrame = posicionPlayer.h = cropRect.h;

	// el centro del jugador es el origen
	origenX = anchoFrame / 2;
	origenY = altoFrame / 2;

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
		cropRect.y = altoFrame * 1;
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
		}
	} else {
		contadorFrames = 0;
		cropRect.x = anchoFrame;
	}
}


void Player::Dibujar(SDL_Renderer *render, SDL_Rect camaraRect) {
	SDL_Rect drawingRect = { posicionPlayer.x - camaraRect.x, posicionPlayer.y - camaraRect.y, posicionPlayer.w, posicionPlayer.h};
	SDL_RenderCopy(render, textura, &cropRect, &drawingRect);
}


int Player::GetOrigenX() {
	return origenX + posicionPlayer.x;
}

int Player::GetOrigenY() {
	return origenY + posicionPlayer.y;
}
