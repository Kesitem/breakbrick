#pragma once

#include "core.h"
#include "program.h"

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

    private:

        /*! Program */
        std::unique_ptr<ugly::program> _program {nullptr};
    };

}//namespace ugly