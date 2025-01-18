#ifndef C_PLAYER_H
#define C_PLAYER_H

#include "D_FuncoesBasicas.h"

typedef struct {
	
	// Visual Attributes
	int radius;
	int color[3];  // RGB
	
	// Cinematic Attributes
	int mass;
	double pos[N_DIMENSIONS]; // Will be the center
	double vel[N_DIMENSIONS];
	double acel[N_DIMENSIONS];
	
} Player;

Player players[
	/*
	We will use the index as the type of the player.
	
	This number(index) is responsible for what kind of player we have.
	For example, 
	
		i = 0 -> Indicades the BALL;
		i = 1...x -> Jogadores, Goleiros, Reservas
		i = x + 1 -> Judge
	*/
	NUMBER_OF_PLAYERS
];

///////////////////////////////////////////////////////////////////////////////
/// Prot�tipos de Fun��es em Ordem
///////////////////////////////////////////////////////////////////////////////

int
draw_a_player(
	Player,
	Display
);


#endif // C_PLAYER_H
