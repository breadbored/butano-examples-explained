/*
 * Copyright (c) 2020-2025 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_map_cell_info.h"

#include "bn_sprite_items_dog.h"
#include "bn_regular_bg_items_map.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"

int main()
{
    // Initialize Butano
    bn::core::init();

    // Text for demo context
    constexpr bn::string_view info_text_lines[] = {
        "PAD: move dog"
    };
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    common::info info("Map collision", info_text_lines, text_generator);

    // Create a `regular_bg` pointer from "map"
    bn::regular_bg_ptr map_bg = bn::regular_bg_items::map.create_bg(0, 0);
    // ... and a sprite pointer for the dog
    bn::sprite_ptr dog_sprite = bn::sprite_items::dog.create_sprite(0, 0);

    // Get the map_item from the bg
    // See: https://gvaliente.github.io/butano/classbn_1_1regular__bg__map__item.html
    const bn::regular_bg_map_item& map_item = bn::regular_bg_items::map.map_item();
    // Get the cell at coordinates (0,0) from the above item
    // See: https://gvaliente.github.io/butano/namespacebn.html#a6095e8103771dcb0c6ca117cd14a3a98
    // A regular_bg_map_cell is represented as 16 bit number (u16)
    bn::regular_bg_map_cell valid_map_cell = map_item.cell(0, 0);
    // ... and we use that number to get the index of that cell
    int valid_tile_index = bn::regular_bg_map_cell_info(valid_map_cell).tile_index();

    // Create a 2D XY vector representing the position of the dog sprite
    bn::point dog_map_position(16, 16);

    // This is the game loop which keeps the program running
    // Each frame is drawn at `bn::core::update()`, which is typically at the end of the loop
    while(true)
    {
        // Create a second 2D vector that will be used to calculate the dog sprite's position
        bn::point new_dog_map_position = dog_map_position;

        // Check each of the buttons to register movement
        // Also you may need to flip a sprite to make sure it's facing the correct direction
        if(bn::keypad::left_pressed())
        {
            new_dog_map_position.set_x(new_dog_map_position.x() - 1);
            dog_sprite.set_horizontal_flip(true);
        }
        else if(bn::keypad::right_pressed())
        {
            new_dog_map_position.set_x(new_dog_map_position.x() + 1);
            dog_sprite.set_horizontal_flip(false);
        }
        // The sprite doesn't have a Y flipped sprite, so we don't flip them here
        if(bn::keypad::up_pressed())
        {
            new_dog_map_position.set_y(new_dog_map_position.y() - 1);
        }
        else if(bn::keypad::down_pressed())
        {
            new_dog_map_position.set_y(new_dog_map_position.y() + 1);
        }

        // On line 35-43, I described getting a map's cell index at a particular position
        // We are doing the same here to compare this value to the cell index we got earlier
        bn::regular_bg_map_cell dog_map_cell = map_item.cell(new_dog_map_position);
        int dog_tile_index = bn::regular_bg_map_cell_info(dog_map_cell).tile_index();

        // If the cell index we just got matches the cell index we considered valid on lines 35-43
        // then we can move! This is because the cell index is one we consider to be valid
        if(dog_tile_index == valid_tile_index)
        {
            // Update the dog's intended position
            dog_map_position = new_dog_map_position;
        }

        // Update the dog's sprite's current position
        bn::fixed dog_sprite_x = (dog_map_position.x() * 8) - (map_item.dimensions().width() * 4) + 4;
        bn::fixed dog_sprite_y = (dog_map_position.y() * 8) - (map_item.dimensions().height() * 4) + 4;
        dog_sprite.set_position(dog_sprite_x, dog_sprite_y);

        // update the demo text 
        info.update();

        // Draw the frame
        bn::core::update();
    }
}
