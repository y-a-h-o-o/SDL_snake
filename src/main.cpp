#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct SDL_context {
	SDL_Window *window; 
	SDL_Renderer *renderer; 
}; 

// Global variables for screen width and height.
constexpr int screen_width = 640; 
constexpr int screen_height = 480; 
constexpr int fps = 60;

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
	test_rect.x = 0; 
	test_rect.y = (screen_height / 2) - 50; 
	test_rect.w = test_rect.h = 100; 

	Uint64 prev_time = SDL_GetTicksNS();
	Uint64 delta = 0; 
	Uint64 timer = 0; 
	int draw_count = 0; 

	auto render = [&]() {
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
		SDL_RenderClear(app.renderer); 	
		
		test_rect.x += 5; 
		if(test_rect.x >= screen_width) {
			test_rect.x = -test_rect.w;
		}

		SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, SDL_ALPHA_OPAQUE); 
		SDL_RenderFillRect(app.renderer, &test_rect); 
		SDL_RenderPresent(app.renderer);
	}; 

	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_EVENT_QUIT) {
				quit = true; 
			}	
		}
		
		constexpr Uint64 ns_per_frame = (1e9) / fps; 	
		const Uint64 now = SDL_GetTicksNS(); 
		delta += now - prev_time; 
		timer += now - prev_time; 
		prev_time = now;

		if(delta >= ns_per_frame) {
			render();
			draw_count++;
			delta -= ns_per_frame; 
		}
	
		if(timer >= 1e9) {
			SDL_Log("FPS: %d", draw_count); 
			timer = 0; 
			draw_count = 0; 
		}
		
	}	
	
	delete_context(app); 	
	return 0;
}
