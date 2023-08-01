#include "input_button.h"


ugly::input_button::input_button()
{
}


const ugly::input_state& ugly::input_button::get_state() const
{
    return _state;
}


void ugly::input_button::set_state(const ugly::input_state& state)
{
    _state = state;
}


const ugly::input_action& ugly::input_button::get_action() const
{
    return _action;
}


void ugly::input_button::set_action(const ugly::input_action& action)
{
    _action = action;
}