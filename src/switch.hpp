#pragma once

#include "entity.hpp"
#include <iostream>

class Switch : public Entity {
public:
	const char* get_texture_path() const override { return textures_path("switch_off.png"); }
	const char* get_lit_texture_path() const override { return textures_path("switch_on.png"); }
	bool is_light_dynamic() const override { return true; }

	void activate() override;
	void deactivate() override;

	bool get_audio_played();
	void set_audio_played();

private:
	bool m_audio_played = false;
};
