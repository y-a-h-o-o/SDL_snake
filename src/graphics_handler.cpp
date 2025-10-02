#include "graphics_handler.h" 
#include <SDL3/SDL.h>

bool init_context(SDL_context& ctx) {
	if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
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

void fill_rect(const SDL_FRect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);	
	SDL_RenderFillRect(renderer, &rect);
} 

// RenderClear Sets to the color SDL is drawn with. 
void render(SDL_Renderer* renderer, void (*game_render)(SDL_Renderer* renderer)) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
	SDL_RenderClear(renderer); 

	game_render(renderer); 
	
	SDL_RenderPresent(renderer); 	
}
