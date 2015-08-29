#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define ANCHO_PANTALLA 500
#define ALTO_PANTALLA 300
#define FPS 60

using namespace std;


// Limita FPS ---> todo REVISAR
void cap_framerate(Uint32 starting_tick) {
	   if ( (1000 / FPS) > SDL_GetTicks() - starting_tick) {
		   SDL_Delay(1000 / FPS - (SDL_GetTicks() - starting_tick));
	   }
}

// cuando trabajo con texturas necesito un renderer
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

	const int FPSSS = 60;
	int frameTime = 0;

	const Uint8 *keyState;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout << "Error en SDL_Init" << SDL_GetError() << endl;
		return 1;
	}


	SDL_Window *ventana;
	ventana = SDL_CreateWindow("Age of Empires",
		   	   	   	   	   	  SDL_WINDOWPOS_UNDEFINED,
		   	   	   	   	   	  SDL_WINDOWPOS_UNDEFINED,
		   	   	   	   	   	  ANCHO_PANTALLA,
		   	   	   	   	   	  ALTO_PANTALLA,
		   	   	   	   	   	  SDL_WINDOW_RESIZABLE   );

	if (ventana == NULL) {
		cout << "Error en ventana" << endl << SDL_GetError() << endl;
	}

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(imgFlags) != imgFlags)
		cout << "Error imgFLags" << IMG_GetError() << endl;


	// Personaje
	SDL_Renderer *renderTarget = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//SDL_Renderer *renderTarget = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
	SDL_Rect playerRect;
	SDL_Rect playerPosition;
	playerPosition.x = playerPosition.y = 0;
	playerPosition.w = playerPosition.h = 32;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;

	SDL_Texture *imagencita = LoadTexture("images/thor.png", renderTarget);
	SDL_QueryTexture(imagencita, NULL, NULL, &textureWidth, &textureHeight);

	///////////////////////////////////
	frameWidth = textureWidth / 3;
	frameHeight = textureHeight / 4;

	playerRect.x = playerRect.y = 0;
	playerRect.w = frameWidth;
	playerRect.h = frameHeight;

	SDL_SetRenderDrawColor(renderTarget, 0xFF, 0, 0, 0xFF);

	///////////////////////////////////


/*
   // Colores e imagenes de fondo
   SDL_Surface *pantalla = SDL_GetWindowSurface(ventana);
   Uint32 pink = SDL_MapRGB(pantalla->format, 255, 192, 203);

   SDL_Surface *imagenPantalla = SDL_LoadBMP("images/lena.bmp");
   if (imagenPantalla == NULL) {
	   cout << "Error en imagenPantalla" << endl << SDL_GetError() << endl;
   }

   SDL_Surface *imagenUno = SDL_LoadBMP("images/pepper.bmp");
   SDL_Surface *imagenDos = SDL_LoadBMP("images/color.bmp");
   SDL_Surface *currentImagen = imagenPantalla;

   bool conImagen = false;

   if (conImagen) {
	   // dibujo una Surface sobre otra Surface
	   SDL_BlitSurface(imagenPantalla, NULL, pantalla, NULL);
   } else {
	   // colorea toda la pantalla
	   //SDL_FillRect(pantalla, NULL, pink);
	   cout << "Nada" << endl;
   }
*/

   // Eventos
   SDL_Event evento;
   bool corriendo = true;

   //Uint32 starting_tick; // para limitar fps

   while (corriendo) {
	   //starting_tick = SDL_GetTicks();
	   while (SDL_PollEvent( &evento ) != 0) {

		   // Evento para cerrar pantalla
		   if (evento.type == SDL_QUIT) {
			   corriendo = false;
			   break;
		   }
/*
		   // Evento para teclado
		   if ((evento.type == SDL_KEYDOWN) && conImagen) {
			   switch (evento.key.keysym.sym) {
			   	   case SDLK_1:
			   		   currentImagen = imagenUno;
			   		   break;
			   	   case SDLK_2:
			   		   currentImagen = imagenPantalla;
			   		   break;
			   }
		   }

		   // Evento para mouse
		   if ((evento.type == SDL_MOUSEBUTTONDOWN) && conImagen) {

			   // boton derecho / izquierdo
			   if (evento.button.button == SDL_BUTTON_LEFT) {
				   currentImagen = imagenUno;
			   } else if (evento.button.button == SDL_BUTTON_RIGHT) {
				   currentImagen = imagenPantalla;
			   }

			   // doble click
			   if (evento.button.clicks == 2) {
				   currentImagen = imagenDos;
			   }
		   }
*/
	   }

/*
	   if (conImagen)
		   SDL_BlitSurface(currentImagen, NULL, pantalla, NULL);

*/

	   keyState = SDL_GetKeyboardState(NULL);

	   frameTime++;
	   if (FPSSS / frameTime == 4) {
		   frameTime = 0;
		   playerRect.x += frameWidth;
		   if (playerRect.x >= textureWidth)
			   playerRect.x = 0;
	   }

	   SDL_RenderClear(renderTarget);
	   SDL_RenderCopy(renderTarget, imagencita, &playerRect, &playerPosition);
	   SDL_RenderPresent(renderTarget),


	   SDL_UpdateWindowSurface(ventana); // actualizo!
	   //cap_framerate(starting_tick);
   }

   /*
   SDL_FreeSurface(imagenUno);
   SDL_FreeSurface(imagenPantalla);
*/

   SDL_Delay(100); // tardar al cerrar
   SDL_DestroyWindow(ventana);
   SDL_Quit();

   cout << "FLOR llega hasta return" << endl;
   return 0;
}
