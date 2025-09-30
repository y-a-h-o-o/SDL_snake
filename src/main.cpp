#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int arc, char** arv) {
	if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
		std::cout << "Failed!" << std::endl; 
		return -1; 
	} 
	
	std::cout << "Success!" << std::endl; 
	
	SDL_Quit(); 
	return 0; 
}
