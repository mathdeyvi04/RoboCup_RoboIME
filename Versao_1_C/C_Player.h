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

Player playables[
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
