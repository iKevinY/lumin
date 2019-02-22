//
// Created by Sherry Yuan on 2019-02-21.
//

#include "switchable_entity.hpp"

void SwitchableEntity::on_switch(bool state) {
    m_is_on = state;
    load_texture();

}

bool SwitchableEntity::get_is_on() {
    return m_is_on;
}
