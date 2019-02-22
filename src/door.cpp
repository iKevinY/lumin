//
// Created by Sherry Yuan on 2019-02-22.
//

#include "common.hpp"
#include "door.hpp"

bool Door::get_player_in(vec2 player_pos) {
    int door_width = (int) (texture.width * m_scale.x);
    int door_height = (int) (texture.height * m_scale.y);

    m_is_player_in = CollisionManager::GetInstance().DoorTrace(get_bounding_box(), m_position, door_width, door_height, player_pos);
    return m_is_player_in;
}
