#include "btn_sprite_tiles_item.h"

#include "btn_optional.h"
#include "btn_sprite_tiles_ptr.h"

namespace btn
{

optional<sprite_tiles_ptr> sprite_tiles_item::find_tiles() const
{
    return sprite_tiles_ptr::find(*this);
}

optional<sprite_tiles_ptr> sprite_tiles_item::find_tiles(int graphics_index) const
{
    return sprite_tiles_ptr::find(*this, graphics_index);
}

sprite_tiles_ptr sprite_tiles_item::create_tiles() const
{
    return sprite_tiles_ptr::find_or_create(*this);
}

sprite_tiles_ptr sprite_tiles_item::create_tiles(int graphics_index) const
{
    return sprite_tiles_ptr::find_or_create(*this, graphics_index);
}

sprite_tiles_ptr sprite_tiles_item::create_new_tiles() const
{
    return sprite_tiles_ptr::create(*this);
}

sprite_tiles_ptr sprite_tiles_item::create_new_tiles(int graphics_index) const
{
    return sprite_tiles_ptr::create(*this, graphics_index);
}

optional<sprite_tiles_ptr> sprite_tiles_item::create_tiles_optional() const
{
    return sprite_tiles_ptr::find_or_create_optional(*this);
}

optional<sprite_tiles_ptr> sprite_tiles_item::create_tiles_optional(int graphics_index) const
{
    return sprite_tiles_ptr::find_or_create_optional(*this, graphics_index);
}

optional<sprite_tiles_ptr> sprite_tiles_item::create_new_tiles_optional() const
{
    return sprite_tiles_ptr::create_optional(*this);
}

optional<sprite_tiles_ptr> sprite_tiles_item::create_new_tiles_optional(int graphics_index) const
{
    return sprite_tiles_ptr::create_optional(*this, graphics_index);
}

}
