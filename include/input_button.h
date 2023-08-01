#pragma once

#include "core.h"
#include "input_state.h"

namespace ugly
{

    /**
     * \brief Input button.
     * 
     * The button can be use in two ways:
     *  - as a simple state: the button is press or release
     *  - as an action: the button was just pressed or released
     */
    class input_button
    {
    public:

        /**
         * \brief Constructor.
         */
        input_button();

        /**
         * \brief Get current state.
         * 
         * \return Current state.
         */
        const input_state& get_state() const;

        /**
         * \brief Set state.
         * 
         * \param state State.
         */
        void set_state(const input_state& state);

        /**
         * \brief Get current action.
         * 
         * \return Currrent action.
         */
        const input_action& get_action() const;

        /**
         * \brief Set action.
         * 
         * \param action Action.
         */
        void set_action(const input_action& action);

    private:

        /*! Current state. */
        input_state _state {input_state::release};

        /*! Current action. */
        input_action _action {input_action::none};
    };

}//namespace ugly