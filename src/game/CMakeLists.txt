add_library(game STATIC 
	game_logic.cpp 
	game_graphics.cpp
)

target_include_directories(game 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
) 

target_link_libraries(game PRIVATE SDL3::SDL3)
