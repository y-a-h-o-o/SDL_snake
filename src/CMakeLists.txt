add_subdirectory(game) 

add_executable(
	SDL_snake
	main.cpp
	graphics_handler.cpp
)

target_include_directories(SDL_snake
	PUBLIC ${PROJECT_SOURCE_DIR}/include
) 

target_link_libraries(SDL_snake 
	PRIVATE SDL3::SDL3 game
)
