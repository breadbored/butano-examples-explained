#include "bf_stats.h"

#include "btn_core.h"
#include "btn_string.h"
#include "btn_display.h"
#include "btn_input_string_stream.h"
#include "btn_sprite_text_generator.h"

namespace bf
{

stats::stats(const btn::sprite_text_generator& text_generator) :
    _text_generator(text_generator)
{
    set_mode(_mode);
}

void stats::set_mode(mode_type mode)
{
    btn::point display_center = btn::display::center();
    int text_x = 8 - display_center.x();
    int text_height = _text_generator.font().item().shape_size().height() + 4;
    _mode = mode;
    _static_text_sprites.clear();
    _text_sprites.clear();
    _max_cpu_usage = 0;
    _counter = 0;

    switch(mode)
    {

    case mode_type::DISABLED:
        break;

    case mode_type::SIMPLE:
        _text_position = btn::fixed_point(text_x, text_height - display_center.y());
        break;

    case mode_type::DETAILED:
        {
            btn::string_view cpu_label = "CPU: ";
            btn::fixed cpu_label_width = _text_generator.width(cpu_label);
            _text_position = btn::fixed_point(text_x + cpu_label_width, text_height - display_center.y());

            btn::string<32> text;
            btn::input_string_stream text_stream(text);
            text_stream.append(cpu_label);
            _text_generator.generate(text_x, _text_position.y(), text, _static_text_sprites);

            text_stream.clear();
            text_stream.append("IWR: ");
            text_stream.append(btn::memory::used_static_iwram());
            text_stream.append("B");
            _text_generator.generate(text_x, _text_position.y() + text_height, text, _static_text_sprites);

            text_stream.clear();
            text_stream.append("EWR: ");
            text_stream.append(btn::memory::used_static_ewram());
            text_stream.append("B");
            _text_generator.generate(text_x, _text_position.y() + (text_height * 2), text, _static_text_sprites);
        }
        break;
    }
}

void stats::update()
{
    switch(_mode)
    {

    case mode_type::DISABLED:
        return;

    case mode_type::SIMPLE:
        break;

    case mode_type::DETAILED:
        break;
    }

    _max_cpu_usage = btn::max(_max_cpu_usage, btn::core::cpu_usage());

    if(! _counter)
    {
        btn::fixed max_cpu_pct = _max_cpu_usage * 100;
        btn::string<32> text;
        btn::input_string_stream text_stream(text);

        switch(_mode)
        {

        case mode_type::DISABLED:
            break;

        case mode_type::SIMPLE:
            text_stream.append(max_cpu_pct.integer());
            break;

        case mode_type::DETAILED:
            text_stream.append(max_cpu_pct);
            break;
        }

        text_stream.append("%");
        _text_sprites.clear();
        _text_generator.generate(_text_position, text, _text_sprites);

        _max_cpu_usage = 0;
        _counter = 60;
    }

    --_counter;
}

}
