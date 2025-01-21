#ifndef H_Dependencias_H
#define H_Dependencias_H

//////////////////////////////////////////////////////////////////////////////////
//// Importações 
//////////////////////////////////////////////////////////////////////////////////

// Ferramentas de Teste
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

// Importações de Interface
#include <SDL2/SDL.h>

#include <math.h>

//////////////////////////////////////////////////////////////////////////////////
//// Variáveis De Tela
//////////////////////////////////////////////////////////////////////////////////

#define IMAGE_NAME "campo.bmp"
#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600
#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)  // in miliseconds.

// Borders Field Soccer
#define TOPLEFT_X 46 
#define TOPLEFT_Y 56
#define BOTTOMRIGHT_X 748
#define BOTTOMRIGHT_Y 555
#define MEDIUM_X 396
#define MEDIUM_Y 306

#define NUMBER_OF_PLAYERS 2
#define N_DIMENSIONS 2

//////////////////////////////////////////////////////////////////////////////////
//// Structs
//////////////////////////////////////////////////////////////////////////////////
// To save screen information.
typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *image_field;
} Display;

#endif  // H_Dependencias_H
