add_executable(
	SDL_snake
	main.cpp
)

# link to SDL
target_link_libraries(SDL_snake PRIVATE SDL3::SDL3)
