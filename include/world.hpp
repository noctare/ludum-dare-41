#pragma once

#include "player.hpp"

#include <graphics.hpp>
#include <engine.hpp>

#define TILE_BG_BOTTOM  0
#define TILE_BG_TOP     1
#define TILE_WALL       2
#define TILE_SLIME      3

#define TILE_EX_BONE_BASE_LEFT    0
#define TILE_EX_BONE_BASE_RIGHT   1
#define TILE_EX_BONE_TILE_LEFT    2
#define TILE_EX_BONE_TILE_RIGHT   3
#define TILE_EX_BONE_MID_LEFT     4
#define TILE_EX_BONE_MID_RIGHT    5
#define TILE_EX_BONE_TOP_LEFT     6
#define TILE_EX_BONE_TOP_RIGHT    7

class player_object;
class game_world;
class game_state;
class world_chunk;

class world_generator {
public:

	void normal(const ne::vector2i& index);
	void border(const ne::vector2i& index);

	bool add_bone(world_chunk& chunk, int i);
	bool add_spike(world_chunk& chunk, int i);

	game_world* world = nullptr;

};

struct tile_data {
	uint16 type = 0;
	int16 extra = -1;
};

class world_chunk {
public:

	static const int tile_pixel_size = 16;
	static const int tiles_per_row = 16;
	static const int tiles_per_column = 16;
	static const int total_tiles = tiles_per_row * tiles_per_column;
	static const int pixel_width = tiles_per_row * tile_pixel_size;
	static const int pixel_height = tiles_per_column * tile_pixel_size;

	static const bool offset_to_grid = false;

	game_world* world = nullptr;
	ne::transform3f transform;
	ne::vector2i index;
	bool needs_rendering = true;
	ne::drawing_shape shape;

	tile_data tiles[total_tiles];

	tile_data* at(int x, int y);
	void render_tile(int type);
	void render_tile_ex(int from, int to);
	void render();
	std::pair<tile_data*, ne::vector2i> tile_at_world_position(const ne::vector2f& position);

	world_chunk();

	void set_index(const ne::vector2i& index);
	void draw();

};

class bone_object {
public:
	ne::transform3f transform;
	int type = 0;
};

class game_world {
public:

	static const int chunks_per_row = 32;
	static const int chunks_per_column = 32;
	static const int total_chunks = chunks_per_row * chunks_per_column;

	game_state* game = nullptr;

	world_chunk chunks[total_chunks];

	player_object player;
	std::vector<enemy_blood_object> blood_enemies;
	std::vector<enemy_pimple_object> pimple_enemies;
	std::vector<enemy_worm_object> worm_enemies;
	std::vector<bullet_object> bullets;
	std::vector<item_object> pills;
	std::vector<item_object> injections;
	std::vector<spike_object> spikes;

	game_world();

	void update_items(std::vector<item_object>& items, int type, int max_of);

	void update();
	void draw(const ne::transform3f& view);

	world_chunk* at(int x, int y);
	world_chunk* chunk_at_world_position(const ne::vector2f& position);

	bool is_free_at(const ne::vector2f& position);

	world_generator generator;

};

