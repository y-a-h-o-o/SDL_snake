#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// constexpr -> constant at compile time. 
constexpr int screen_width = 640; 
constexpr int screen_height = 480; 

/* Function Prototype */ 

// start SDL; create window
bool init(); 

// free media + shut down SDL
void close(); 

/* Global Variabls - Never use in actual code; Only for demos */ 

// pointer to window we are rendering to. 
SDL_Window* gWindow{ nullptr }; 

// surface contained by window
SDL_Surface* gScreenSurface{ nullptr }; 

// image loaded onto screen. 
SDL_Surface* gHelloWorld{ nullptr };

bool init() {
	// Initalize SDL
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL could not initalize! SDL error: %s\n", SDL_GetError());		
		return false;
	}
	
	// Create window
	if((gWindow = SDL_CreateWindow("Window", screen_width, screen_height, 0)) == nullptr) {
		SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());		
		return false; 
	}
	
	// Get Window Surface
	gScreenSurface = SDL_GetWindowSurface(gWindow); 

	return true; 
}

void close() {
	// Destroy Surface
	SDL_DestroySurface(gHelloWorld); 
	gHelloWorld = nullptr; 

	// Destroy Window
	SDL_DestroyWindow(gWindow); 
	gWindow = nullptr; 
	gScreenSurface = nullptr; 
	
	// Quit SDL subsystems
	SDL_Quit(); 
}

int main(int arc, char** arv) {
	if(!init()) {
		SDL_Log("Unable to initalize program"); 	
		return 1; 
	}
	
	bool quit = false; 

	SDL_Event e; 

	// Wrapper to initalize SDL_Event. 
	SDL_zero(e); 
	
	while(!quit) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_EVENT_QUIT) {
				quit = true; 
			}	
		}
		
		// Fill surface white 
		SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF)); 
		
		SDL_UpdateWindowSurface(gWindow); 
	}	
	
	close(); 
	return 0;
}
