#ifndef H_Dependencias_H
#define H_Dependencias_H

//////////////////////////////////////////////////////////////////////////////////
//// Importa��es 
//////////////////////////////////////////////////////////////////////////////////

// Ferramentas de Teste
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <time.h> // For the srand()

// Importa��es de Interface
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Para c�lculos
#include <math.h>

// Importa��o de Multiprocessamento.
#include <pthread.h>

//////////////////////////////////////////////////////////////////////////////////
//// Vari�veis De Tela
//////////////////////////////////////////////////////////////////////////////////

#define IMAGE_NAME "campo.bmp"
#define WIDTH_SCREEN 1500
#define HEIGHT_SCREEN 800
#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)  // in miliseconds.
int last_position_mouse[2];

// Borders Field Soccer
#define TOPLEFT_X 0.053 * WIDTH_SCREEN + 0.7 
#define TOPLEFT_Y 0.085 * HEIGHT_SCREEN + 0.8
#define BOTTOMRIGHT_X 0.94 * WIDTH_SCREEN + 0.2
#define BOTTOMRIGHT_Y 0.926 * HEIGHT_SCREEN + 0.8
#define MEDIUM_X WIDTH_SCREEN / 2 - 5
#define MEDIUM_Y HEIGHT_SCREEN / 2 + 5
#define TOP_GOAL 0.42 * HEIGHT_SCREEN + 0.8
#define BOTTOM_GOAL 0.926 * HEIGHT_SCREEN + 0.8

#define NUMBER_OF_ROWS (BOTTOMRIGHT_X - TOPLEFT_X) / (7 * MINOR_SIZE_SQUARE)
#define NUMBER_OF_COLUMNS (BOTTOMRIGHT_Y - TOPLEFT_Y) / (7 * MINOR_SIZE_SQUARE)

#define NUMBER_OF_PLAYERS 9
#define N_DIMENSIONS 2

//////////////////////////////////////////////////////////////////////////////////
//// Variaveis Diversas
//////////////////////////////////////////////////////////////////////////////////

// To save screen information.
typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *image_field;
} Display;

TTF_Font *font_to_be_used;
#define TAM_FONT 20

#define BUFFER_SIZE_TIME_MATCH 11
char buffer_time_match[BUFFER_SIZE_TIME_MATCH];

#define BUFFER_SIZE_GOALS 5
char buffer_goals[BUFFER_SIZE_GOALS];


//////////////////////////////////////////////////////////////////////////////////
///// Fun��es
//////////////////////////////////////////////////////////////////////////////////

void
display_error(
	const char*
);

double 
get_module_squared(
	double*
);





#endif  // H_Dependencias_H
