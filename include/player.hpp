#pragma once

#include "object.hpp"

#include <timer.hpp>

class player_object : public game_object {
public:

	int64 score = 0;

	player_object();
	
	void update(game_world* world) override;
	void draw() override;

private:

	int shoot_listener_id = -1;
	ne::timer last_shot;

};
