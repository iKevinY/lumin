#pragma once

#include "switchable_entity.hpp"
#include "CollisionManager.hpp"

class Door : public SwitchableEntity {
public:
    ~Door() override { Entity::destroy(); }

    char* get_texture_path() const override {
        if (m_is_on) {
            return textures_path("door_open.png");
        } else {
            return textures_path("door_closed.png");
        }
    }
    bool is_player_collidable() const override { return true; }

    bool is_light_collidable() const override { return false; }

    bool is_light_dynamic() const override { return false; }

    EntityColor get_color() const override { return EntityColor({1.0, 1.0, 1.0, 1.0}); }

    void set_lit(bool lit) override {}

    bool get_player_in(vec2 player_pos);
private:
    bool m_is_player_in;
};