#ifndef H_Dependencias_H
#define H_Dependencias_H

///////////////////////////////// Importa��es ///////////////////////

// Ferramentas de Teste
#include <stdlib.h>
#include <stdio.h>

// Importa��es de Interface
#include <SDL2/SDL.h>


//////////////////////////////// Vari�veis //////////////////////////

#define COMPRIMENTO_TELA 800
#define ALTURA_TELA 600

#define N_DIMENSIONS 2


#define QUANTIDADE_DE_PLAYERS 1



/////////////////////////////// Structs /////////////////////////////

// Para guardarmos as informa��es de tela.
typedef struct {
	SDL_Window *janela;
	SDL_Renderer *renderizador;
} Display;

#endif  // H_Dependencias_H
