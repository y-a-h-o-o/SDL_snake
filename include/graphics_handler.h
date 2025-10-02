#ifndef GRAPHICS_HANDLER_H

#define GRAPHICS_HANDLER_H

#include <SDL3/SDL.h>

constexpr int screen_width = 640; 
constexpr int screen_height = 480; 
constexpr int fps = 60; 

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
