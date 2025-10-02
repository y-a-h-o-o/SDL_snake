#ifndef GRAPHICS_HANDLER_H

#define GRAPHICS_HANDLER_H

#include <SDL3/SDL.h>
#include "game/game_logic.h"

constexpr int screen_width = block_size * game_width;  
constexpr int screen_height = block_size * game_height; 
constexpr int fps = 16; 

struct SDL_context {
	SDL_Window *window; 
	SDL_Renderer *renderer; 
}; 

bool init_context(SDL_context& ctx); 

void delete_context(SDL_context& ctx); 

void fill_rect(const SDL_FRect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer);

// TODO: Implement graphics handling for text 
void draw_text(); 

void render(SDL_Renderer* renderer, void (*render_game)(SDL_Renderer* renderer)); 

#endif
