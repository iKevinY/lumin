#pragma once

#include "common.hpp"
#include "player.hpp"
#include <vector>
#include <iostream>
#include <set>

struct EntityColor {
	float r, g, b, a;
};

class Entity : public Renderable {
public:
	virtual ~Entity() { Entity::destroy(); };

	virtual const char* get_texture_path() const = 0;

	virtual const char* get_lit_texture_path() const { return nullptr; }
	virtual bool is_player_collidable() const { return false; }
	virtual bool is_light_collidable() const { return false; }
	virtual bool is_light_dynamic() const { return false; }
	virtual EntityColor get_color() const { return EntityColor({1.0, 1.0, 1.0, 1.0}); }

	virtual void activate() {};
	virtual void deactivate() {};

	// Creates all the associated render resources and default transform
	bool init(int x_pos, int y_pos);

	// Releases all the associated resources
	void destroy();

	// Update logic for entities
	virtual void update(float elapsed_ms);

	// Renders the entity using the texture
	void draw(const mat3& projection) override;

	// Returns the current entity position
	vec2 get_position() const;

	// Sets the new entity position
	void set_position(vec2 position);

	// Returns the current entity screen position
	vec2 get_screen_pos() const;

	// Sets the new entity screen position
	void set_screen_pos(vec2 position);

	// Returns the wall's bounding box for collision detection, called by collides_with()
	vec2 get_bounding_box() const;

	virtual ParametricLines calculate_static_equations() const;
	virtual ParametricLines calculate_dynamic_equations() const;

	void set_lit(bool lit);
	bool get_lit() const;

	// Register an entity relationship
	void register_entity(Entity* entity);

private:
	Texture unlit_texture;
	Texture lit_texture;
	bool m_is_lit = false;

protected:
    // Window coordinates
    vec2 m_screen_pos;

	// pointer to the active texture
    Texture* texture;

    // 1.f in each dimension. 1.f is as big as the associated texture
    vec2 m_scale;
    vec2 m_position;
	std::set<Entity*> m_entities;
};
