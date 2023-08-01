#pragma once

#include "core.h"

namespace ugly
{

    /*! State enumeration */
    enum class input_state
    {
        press,      /*! InputButton is press. */
        release     /*! InputButton is release. */
    };


    /*! Action enumeration */
    enum class input_action
    {
        none,       /*! No button action. */
        pressed,    /*! The button was pressed. */
        repeated,   /*! The button as press Repeated. */
        released    /*! The button was released. */
    };

}//namespace ugly