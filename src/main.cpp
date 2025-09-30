#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct SDL_context {
	SDL_Window *window; 
	SDL_Renderer *renderer; 
}; 

constexpr int screen_width = 640; 
constexpr int screen_height = 480; 

bool init_context(SDL_context& ctx) {
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL could not initalize! SDL error: %s\n", SDL_GetError());		
		return false;
	}
	
	if(!SDL_CreateWindowAndRenderer("Window Test", screen_width, screen_height, 0, &(ctx.window), &(ctx.renderer))) {
		SDL_Log("Couldn't create window/renderer: %s\n", SDL_GetError()); 
		return false; 
	}
	return true; 
}

void delete_context(SDL_context& ctx) {
	// Destroy Renderer before window. 

	SDL_DestroyRenderer(ctx.renderer);
	ctx.renderer = nullptr; 
	SDL_DestroyWindow(ctx.window); 	
	ctx.window = nullptr; 
}

int main(int arc, char** arv) {
	SDL_context app; 

	if(!init_context(app)) {
		SDL_Log("Unable to initalize program"); 	
		return 1; 
	}
	
	bool quit = false; 
	
	// SDL_Event object to check for events; I am using this instead of SDL_Callbacks
	// Because it is easier for me to understand.
	SDL_Event e; 
	SDL_zero(e); 
	
	SDL_FRect test_rect; 

	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_EVENT_QUIT) {
				quit = true; 
			}	
		}
		
		const Uint64 now = SDL_GetTicks(); 
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
		SDL_RenderClear(app.renderer); 	

		test_rect.x = (now % screen_width); 
		test_rect.y = (screen_height / 2) - 50; 
		test_rect.w = test_rect.h = 100; 
		
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); 
		SDL_RenderFillRect(app.renderer, &test_rect); 
		SDL_RenderPresent(app.renderer); 
	}	
	
	delete_context(app); 	
	return 0;
}
