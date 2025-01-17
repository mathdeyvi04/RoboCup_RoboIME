#ifndef H_Dependencias_H
#define H_Dependencias_H

///////////////////////////////// Importações ///////////////////////

// Ferramentas de Teste
#include <stdlib.h>
#include <stdio.h>

// Importações de Interface
#include <SDL2/SDL.h>

//////////////////////////////// Variáveis //////////////////////////

#define IMAGE_NAME "campo.bmp"
#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600
#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)  // in miliseconds.

#define N_DIMENSIONS 2


#define NUMBER_OF_PLAYERS 1



/////////////////////////////// Structs /////////////////////////////

// To save screen information.
typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *image_field;
} Display;

#endif  // H_Dependencias_H
