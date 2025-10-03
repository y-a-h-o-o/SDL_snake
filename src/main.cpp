#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "graphics_handler.h" 
#include "game/game_logic.h"
#include "game/game_graphics.h"

int main(int arc, char** arv) {
	SDL_context app; 

	if(!init_context(app)) {
		SDL_Log("Unable to initalize program"); 	
		return 1; 
	}
	
	bool quit = false; 

	// SDL_Event object to check for events; I am using this instead of SDL_Callbacks
	// Because it is easier for me to understand.
	// Next project I will use SDL Callbacks
	SDL_Event e; 
	SDL_zero(e); 

	Uint64 prev_time = SDL_GetTicksNS();
	Uint64 delta = 0; 
	Uint64 timer = 0; 
	int draw_count = 0; 

	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_EVENT_QUIT) {
				quit = true; 
			}
			update_game_state(e); 
		}
		
		constexpr Uint64 ns_per_frame = (1e9) / fps; 	
		const Uint64 now = SDL_GetTicksNS(); 

		update_game(); 
		render(app.renderer, render_game);

		Uint64 updraw_time = SDL_GetTicksNS() - now; 
		
		if(ns_per_frame - updraw_time > 0) {
			SDL_DelayPrecise(ns_per_frame - updraw_time); 
		}
			
		if(quit) {
			delete_game(); 
		}
	}	
	
	delete_context(app); 	
	return 0;
}
