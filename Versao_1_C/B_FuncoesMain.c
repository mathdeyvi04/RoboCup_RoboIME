#include "B_FuncoesMain.h"

///////////////////////////////////////////////////////////////////////////////
/// Vari�veis Main
///////////////////////////////////////////////////////////////////////////////

// Keep tracking the time of the last frame, in miliseconds.
int last_frame_time = 0;

///////////////////////////////////////////////////////////////////////////////
/// Fun��es Diversas
///////////////////////////////////////////////////////////////////////////////

SDL_Texture*
load_field(
	Display display,
	const char *name_image
){
	/*
	Description:
		Will load the image in the beginning.
	*/
	
	SDL_Surface *bmp_surface = SDL_LoadBMP(
		name_image
	);
	
	if(
		!bmp_surface
	){
		printf(
			"\n(B) Error loading field image.\n"
		);
		
		destroy_display(
			display
		);
	}
	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(
		display.renderer,
		bmp_surface
	);
	
	SDL_FreeSurface(
		bmp_surface
	);
	
	return texture;
}


///////////////////////////////////////////////////////////////////////////////
/// Fun��es Main
///////////////////////////////////////////////////////////////////////////////


Display
initialize_display(
	void
){
	/*
	Description:
		Function responsible for checking and initializing the window and the renderer.
		Since these are structures that we need together, it is more interesting to use
		a struct of the union of them.
	
	Return possibilities:
		Display in conditions to be used, being this composed of the window and the renderer;
		
		Display with NULL renderer, if only this one gave an error;
		
		NULL display.
	*/
	
	Display result = {
		NULL,
		NULL,
		NULL
	};
	
	if(
		SDL_Init(
			SDL_INIT_EVERYTHING
		) != 0
	){
		display_error(
			"\n(B) There was an error initializing SDL general tools.\n"
		);
		
		return result;
	}
	
	SDL_Window *window = SDL_CreateWindow(
		"My Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH_SCREEN,
		HEIGHT_SCREEN,
		SDL_WINDOW_SHOWN
	);
	
	if(
		!window
	){
		display_error(
			"\n(B) There was an error trying to create the window.\n"
		);
		
		return result;
	}
	
	result.window = window;
	
	SDL_Renderer *renderer = SDL_CreateRenderer(
		window,  // The window we are going to attach it to;
		-1,  // -1 defautl;
		0  // No special features.
	);
	
	if(
		!renderer
	){
		display_error(
			"\n(B)There was an error trying to create renderer."
		);
		
		return result;
	}
	
	result.renderer = renderer;
	
	result.image_field = load_field(
		result,
		IMAGE_NAME
	);
	
	return result;
}


int
destroy_display(
	Display display
){
	/*
	Description:
		Function responsible for correctly closing the display.
	
	Parameters:
		Self-explanatory.
	
	Return:
		Display closes.
	*/
	
	
	if (
		!display.renderer
	){
		SDL_DestroyRenderer(
			display.renderer
		);
	}
	
	if (
		!display.window
	){
		SDL_DestroyWindow(
			display.window
		);
	}
	
	SDL_Quit();
	
	return 0;
}


int
input_user(
	int *game_is_running
){
	/*
	Description:
		Function responsible for managing user input.
	
	Parameters:
	
	Return:
		Call to the respective input functions.
	*/
	
	SDL_Event event;
	
	SDL_PollEvent(
		&event
	);
	
	switch(
		event.type
	){
		case SDL_QUIT:
			*game_is_running = 0;
			
			return 0;
			
		case SDL_KEYDOWN:
		/**************************************************/
			
			switch(
				event.key.keysym.sym
			){
				case SDLK_ESCAPE:
					*game_is_running = 0;
					
					return 0;
									
				default:
					return 0;
			}
			
		/**************************************************/
			
		default:
			return 0;
	}
	
}


int
update(){
	/*
	Description:
		Function responsible for managing the respective
		updates of each simulation member.

	Parameters:

	Return:
		Simulation members updated in a multiprocessor way.
	*/
	
	/*
	In the past:
	
		Waste time until we reach the frame target time
		while(
			!SDL_TICKS_PASSED(
				SDL_GetTicks(),
				last_frame_time + FRAME_TARGET_TIME
			)
		);
		We can put the pthread_cond_wait here!
	*/
	int time_to_wait = FRAME_TARGET_TIME - (
		SDL_GetTicks() - last_frame_time
	);
	
	if(
		time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME
	){
		SDL_Delay(
			time_to_wait
		);
	}
	
	last_frame_time = SDL_GetTicks();
	
	// Example
	/*
	delta_time = (
		SDL_GetTicks() - last_frame_time
	) / 1000; -> In seconds
	
	So, with * delta_time, we will pixels per second.
	*/

	return 0;
}


int
render(
	Display display
){
	/*
	Description:
		Function responsible for managing screen updates.

	Parameters:

	Return:
		Screen updated according to rendering needs.
	*/
	
	SDL_SetRenderDrawColor(
		/*
		Set the color used for drawing operations
		*/
		display.renderer,
		100,  // R
		0,  // G
		0,  // B
		255  // Transparency.
	);
	
	SDL_RenderClear(
		display.renderer
	);
	
	SDL_RenderCopy(
		display.renderer,
		display.image_field,
		NULL,
		NULL
	);
	
	/*
	Aqui apresentaremos tudo que precisamos na tela.
	
	SDL_Rect -> Desenha um retangulo.
	SDL_SetRenderDrawColor -> Setar� a cor.
	SDL_RenderFillRect -> Preenche com a cor setada antes.
	*/
	
	SDL_RenderPresent(
		display.renderer
	);
}

















