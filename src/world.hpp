#pragma once

// internal
#include "movable_wall.hpp"
#include "common.hpp"
#include "door.hpp"
#include "player.hpp"
#include "entity.hpp"
#include "screen.hpp"
#include "firefly.hpp"
#include "switch.hpp"
#include "level_screen.hpp"
#include "pause_screen.hpp"

// stlib
#include <vector>
#include <random>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>

// Container for all our entities and game logic. Individual rendering / update is
// deferred to the relative update() methods
class World
{
public:
	World();
	~World();

	// Creates a window, sets up events and begins the game
	bool init(vec2 screen);

	// Releases all associated resources
	void destroy();

	// Steps the game ahead by ms milliseconds
	bool update(float ms);

	// Renders our scene
	void draw();

	// Should the game be over ?
	bool is_over()const;

private:
	bool add_tile(int x_pos, int y_pos, StaticTile tile);

	void create_current_level();

	void create_firefly(vec2 pos);

	void print_grid(std::vector<std::vector<char>>& grid);

	void create_level(std::vector<std::vector<char>>& grid);

	void reset_game();

	void load_level_screen(int key_pressed_level);

	void update_level();

	// !!! INPUT CALLBACK FUNCTIONS
	void on_key(GLFWwindow*, int key, int, int action, int mod);

private:
	// Window handle
	GLFWwindow* m_window;

	// Screen texture
	// The draw loop first renders to this texture, then it is used for the water shader
	GLuint m_frame_buffer;
	Texture m_screen_tex;

	// Screen object, we draw everything to another buffer first and then draw the screen using that buffer
	Screen m_screen;
	LevelScreen m_level_screen;
	PauseScreen m_pause_screen;

	unsigned int m_points;

	unsigned int m_current_level;

	// number of levels that user has unlocked
	unsigned int m_unlocked_levels;

	// max level of the game
	unsigned int m_max_level;

	// Game entities
	Player m_player;
	std::vector<Entity*> m_entities;
	std::vector<Firefly*> m_fireflies;
	Door* m_exit_door;
	

	Mix_Music* m_background_music;

	// C++ rng
	std::default_random_engine m_rng;
	std::uniform_real_distribution<float> m_dist; // default 0..1

	bool m_should_load_level_screen;
	bool m_paused;
};
