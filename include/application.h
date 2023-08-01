#pragma once

#include "core.h"

namespace ugly
{

    class application
    {
    public:

        /**
         * \brief Constructor.
         */
        application();

        /**
         * brief Destructor.
        */
        virtual ~application();

        /**
         * \brief Initialize application
         */
        virtual void intialize();

        /**
         * \brief Shutdown application
         */
        virtual void shutdown();

        /**
         * \brief Update application
         */
        virtual void update();
    };

}//namespace ugly