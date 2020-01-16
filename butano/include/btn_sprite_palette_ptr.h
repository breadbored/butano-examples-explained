#ifndef BTN_SPRITE_PALETTE_PTR_H
#define BTN_SPRITE_PALETTE_PTR_H

#include "btn_span_fwd.h"
#include "btn_fixed_fwd.h"
#include "btn_functional.h"
#include "btn_palette_ptr.h"
#include "btn_optional_fwd.h"

namespace btn
{

class sprite_palette_ptr : public palette_ptr
{

public:
    [[nodiscard]] static optional<sprite_palette_ptr> find(const span<const color>& colors_ref);

    [[nodiscard]] static sprite_palette_ptr create(const span<const color>& colors_ref);

    [[nodiscard]] static optional<sprite_palette_ptr> optional_create(const span<const color>& colors_ref);

    [[nodiscard]] static sprite_palette_ptr find_or_create(const span<const color>& colors_ref);

    [[nodiscard]] static optional<sprite_palette_ptr> find_or_optional_create(const span<const color>& colors_ref);

    sprite_palette_ptr(const sprite_palette_ptr& other);

    sprite_palette_ptr& operator=(const sprite_palette_ptr& other);

    sprite_palette_ptr(sprite_palette_ptr&& other);

    sprite_palette_ptr& operator=(sprite_palette_ptr&& other);

    ~sprite_palette_ptr()
    {
        _destroy();
    }

    [[nodiscard]] span<const color> colors_ref() const;

    void set_colors_ref(const span<const color>& colors_ref);

    void reload_colors_ref();

    [[nodiscard]] int colors_count() const;

    [[nodiscard]] bool eight_bits_per_pixel() const;

    [[nodiscard]] fixed inverse_intensity() const;

    void set_inverse_intensity(fixed intensity);

    [[nodiscard]] fixed grayscale_intensity() const;

    void set_grayscale_intensity(fixed intensity);

    [[nodiscard]] color fade_color() const;

    [[nodiscard]] fixed fade_intensity() const;

    void set_fade(color color, fixed intensity);

    [[nodiscard]] int rotate_count() const;

    void set_rotate_count(int count);

    [[nodiscard]] friend bool operator==(const sprite_palette_ptr& a, const sprite_palette_ptr& b)
    {
        return a._id == b._id;
    }

    [[nodiscard]] friend bool operator!=(const sprite_palette_ptr& a, const sprite_palette_ptr& b)
    {
        return ! (a == b);
    }

private:
    using palette_ptr::palette_ptr;

    void _destroy();
};


template<>
struct hash<sprite_palette_ptr>
{
    [[nodiscard]] size_t operator()(const sprite_palette_ptr& value) const
    {
        return make_hash(value.id());
    }
};

}

#endif
