#include "input_manager.h"
#include "input_button.h"
#include "engine.h"


/**
 * \brief GLFW key callback.
 */
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static auto engine = ugly::engine::get_instance();

    engine->get_input_manager()->process_key_change(key, action);
}


ugly::input_manager::input_manager()
{
}


void ugly::input_manager::initialize()
{
    LOG_INFO << "Initialize input manager...";
    
    // Register input callbacks
    glfwSetKeyCallback(ugly::engine::get_instance()->get_window(), glfw_key_callback);
}


void ugly::input_manager::shutdown()
{
    LOG_INFO << "Shutdown input manager...";
}


void ugly::input_manager::update()
{
    for(auto button_itor: _buttons)
    {
        auto button = button_itor.second;
        if(button.get_action() == input_action::pressed || button.get_action() == input_action::repeated || button.get_action() == input_action::released)
        {
            LOG_DEBUG << "Button: " << button_itor.first << "action is set to NONE";
            button.set_action(input_action::none);
        }
    }
}


void ugly::input_manager::process_key_change(int key_name, int action)
{
    // Check if key is binded
    auto key_button_mapping_itor = _key_button_mapping.find(key_name);
    if(key_button_mapping_itor == _key_button_mapping.end())
        return;

    // Update button
    if(action == GLFW_PRESS)
    {
        _buttons[key_button_mapping_itor->second].set_state(input_state::press);
        _buttons[key_button_mapping_itor->second].set_action(input_action::pressed);
    }
    else if(action == GLFW_REPEAT)
    {
        _buttons[key_button_mapping_itor->second].set_action(input_action::repeated);
    }
    else //(action == GLFW_RELEASE)
    {
        _buttons[key_button_mapping_itor->second].set_state(input_state::release);
        _buttons[key_button_mapping_itor->second].set_action(input_action::released);
    }
}


void ugly::input_manager::create_button(const std::string& button_name)
{
    PLOG_INFO << "Create input button: " << button_name;

    auto button_map_itor = _buttons.find(button_name);
    if( button_map_itor != _buttons.end())
    {
        PLOG_WARNING << "Trying to create a button already existing: " << button_name;
        return;
    }

    _buttons.insert(std::make_pair(button_name, input_button()));
}


void ugly::input_manager::bind_key_to_button(int key_name, const std::string& button_name)
{
    LOG_INFO << "Bind key: " <<  key_name << " to input button: " << button_name; 

    auto key_button_mapping_itor = _key_button_mapping.find(key_name);
    if(key_button_mapping_itor != _key_button_mapping.end())
    {
        LOG_ERROR << "Key is already bind to button: " << key_button_mapping_itor->second;
        return;
    }

    auto button_itor = _buttons.find(button_name);
    if(button_itor == _buttons.end())
    {
        LOG_ERROR << "Button: " << button_name << " not found.";
        return;
    }

    _key_button_mapping[key_name] = button_name;
}


const ugly::input_state& ugly::input_manager::get_button_state(const std::string& button_name) const
{
    auto button_map_itor = _buttons.find(button_name);
    if(button_map_itor == _buttons.end())
    {
        LOG_WARNING << "input_button: " << button_name << " not found";
        throw std::invalid_argument("Invalid button name");
    }

    return button_map_itor->second.get_state();
}


const ugly::input_action& ugly::input_manager::get_button_action(const std::string& button_name) const
{
    auto button_map_itor = _buttons.find(button_name);
    if (button_map_itor == _buttons.end())
    {
        LOG_WARNING << "input_button: " << button_name << " not found.";
        throw std::invalid_argument("Invalid button name");
    }

    return button_map_itor->second.get_action();
}

