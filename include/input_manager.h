#pragma once

#include "core.h"
#include "input_state.h"
#include "input_button.h"

namespace ugly
{

/**
 * \class input_manager
 * \brief Input manager
 */
class input_manager
{
public:

    /**
     *  \brief Constructor.
     */
    input_manager();

    /**
     * \brief Initialize manager.
     */
    void initialize();

    /**
     * \brief Shutdown.
     */
    void shutdown();

    /**
     * \brief Update state manager.
     *
     * This function updates state(for exemple pass key state from released to none).
     * It must be call after event processing and before polling events.
     */
    void update();

    /**
     * \brief Process a key change.
     * 
     * This method is mainly used by GLFW key callback.
     * If key is not bind, nothing happens.
     * \param key_name  GLFW key name
     * \param action    GLFW action
     */
    void process_key_change(int key_name, int action);

    /**
     * \brief Create a button.
     * 
     * \param button_name   input_button name
     */
    void create_button(const std::string& button_name);

    /**
     * \brief Bind a key to a button.
     * 
     * \param key_name      GFLW key name
     * \param button_name   Button name
     */
    void bind_key_to_button(int key_name, const std::string& button_name);

    /**
     * \brief Get a button state.
     * 
     * \param button_name   input_button name
     * \return input_button state
     */
    const input_state& get_button_state(const std::string& button_name) const;

    /**
     * \brief Get a button action.
     * 
     * \param button_name   input_button name
     * \return input_button last action
     */
    const input_action& get_button_action(const std::string& button_name) const;

private:

    /*! input_button list. */
    std::map<std::string, input_button> _buttons;

    /*! Key to button mapping*/
    std::map<int, std::string> _key_button_mapping;
};

}//namespace ugly