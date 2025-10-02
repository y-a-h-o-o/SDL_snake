#include <SDL3/SDL.h>
#include <vector>
#include <set>
#include <utility>
#include "game/game_logic.h" 

static game_state current_game_state = TITLE; 

static Game game; 

static player_direction next_direction = RIGHT; 

static std::set<std::pair<int, int>> filled; 

static void init_game() {
	game.player = new Player;
	game.player->body.resize(inital_body_size);
	for(int i = 0; i < game.player->body.size(); i++) {
		(game.player->body)[i] = {start_x - i, start_y, RIGHT}; 	
		filled.insert({start_x - i, start_y}); 
	}
	for(int i = 0; i < max_apples; i++) {
		int x = SDL_rand(game_width - 1);
		int y = SDL_rand(game_height - 1); 
		
		while(filled.find({x, y}) != filled.end()) { 
			x = SDL_rand(game_width - 1);
			y = SDL_rand(game_height - 1); 			
		}	
		
		game.apples[i] = {x, y}; 
		filled.insert({x, y});
	} 
}

static void reset_game() {
	filled.clear(); 
	next_direction = RIGHT;
	game.player->body.resize(inital_body_size);
	for(int i = 0; i < game.player->body.size(); i++) {
		game.player->body[i] = {start_x - i, start_y, RIGHT};
		filled.insert({start_x - i, start_y});
	}
	for(int i = 0; i < max_apples; i++) {
		int x = SDL_rand(game_width - 1);
		int y = SDL_rand(game_height - 1); 
		
		while(filled.find({x, y}) != filled.end()) { 
			x = SDL_rand(game_width - 1);
			y = SDL_rand(game_height - 1); 			
		}

		game.apples[i] = {x, y}; 
		filled.insert({x, y});
	}
}

static void close_game() {
	delete game.player; 
	game.player = nullptr;
	SDL_Log("Player Deleted ...");
	SDL_Log("Game Deleted...");
}

void update_game_state(const SDL_Event& e) {
	if(e.type == SDL_EVENT_QUIT) {
		SDL_Log("Shutting Down ...");
		current_game_state = CLOSING; 	
	} else if(e.type == SDL_EVENT_KEY_DOWN) {
		switch(e.key.scancode) {
			case SDL_SCANCODE_UP: next_direction = UP; break; 
			case SDL_SCANCODE_DOWN: next_direction = DOWN; break; 
			case SDL_SCANCODE_LEFT:  next_direction = LEFT; break;
			case SDL_SCANCODE_RIGHT: next_direction = RIGHT; break;
		}
	} 
}

static void update_cell(body_cell& c) {
	filled.erase({c.x, c.y}); 
	switch(c.cell_direction) {
		case UP: c.y -= 1; break; 
		case DOWN: c.y += 1; break; 
		case RIGHT: c.x += 1; break; 
		case LEFT: c.x -= 1; break; 
	}
	filled.insert({c.x, c.y}); 
}

static player_direction get_opposite(player_direction dir) {
	switch(dir) {
		case UP: return DOWN; 
		case DOWN: return UP;
		case RIGHT: return LEFT; 
		case LEFT: return RIGHT; 
	}	
	return RIGHT; 
}

static void move_player() { 
	Player*& p = game.player; 	
	if(
		p->body[HEAD].x < 0 || 
		p->body[HEAD].x >= game_width || 
		p->body[HEAD].y < 0 || 
		p->body[HEAD].y >= game_height) {
		current_game_state = END; 
		return; 
	} 
	
	for(int i = 1; i < p->body.size(); i++) {
		if(p->body[HEAD].x == p->body[i].x && p->body[HEAD].y == p->body[i].y) {
			current_game_state = END;
			return;
		}
	}

	std::vector<player_direction> cell_dirs(p->body.size());

	for(int i = 0; i < p->body.size(); i++) {
		cell_dirs[i] = p->body[i].cell_direction; 
	}
	
	for(int i = 1; i < p->body.size(); i++) {
		p->body[i].cell_direction = cell_dirs[i - 1]; 	
	}
	
	if(next_direction != get_opposite(p->body[HEAD].cell_direction)) {
		p->body[HEAD].cell_direction = next_direction; 
	}
	for(body_cell& cell : p->body) {
		update_cell(cell); 	
	} 
}

static void eat_apple() {
	Player*& p = game.player;
	for(int i = 0; i < max_apples; i++) {
		if(p->body[HEAD].x == game.apples[i].x && p->body[HEAD].y == game.apples[i].y) {
			int li = p->body.size() - 1; 
			body_cell cell; 
			cell.cell_direction = p->body[li].cell_direction; 
			switch(cell.cell_direction) {
				case UP: cell.x = p->body[li].x; cell.y = p->body[li].y + 1; break; 	
				case DOWN: cell.x = p->body[li].x; cell.y = p->body[li].y - 1; break;
				case LEFT: cell.x = p->body[li].x + 1; cell.y = p->body[li].y; break; 	
				case RIGHT: cell.x = p->body[li].x - 1; cell.y = p->body[li].y; break;
			}	
			p->body.push_back(cell);
			
			filled.insert({cell.x, cell.y}); 
			
			int x = SDL_rand(game_width - 1); 
			int y = SDL_rand(game_height - 1); 
		
			while(filled.find({x, y}) != filled.end()) {
				x = SDL_rand(game_width - 1); 
				y = SDL_rand(game_height - 1); 
			}
			
			filled.insert({x, y});
			game.apples[i] = {x, y}; 
			return; 
		}
	}	
}

void update_game() {
	switch (current_game_state) {
		// TODO: Title and End states have nothing right now. 
		case TITLE: current_game_state = RUNNING; init_game(); break;
		case RUNNING: 
		{
			move_player(); 
			eat_apple(); 
		} break; 	
		case END: reset_game(); current_game_state = RUNNING; break;
		case CLOSING: close_game(); break; 
	}		
}

const game_state get_game_state() {
	return current_game_state; 	
}

const Game& get_game() {
	return game; 
}
