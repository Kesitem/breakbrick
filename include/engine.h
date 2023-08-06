#pragma once

#include "core.h"
#include "display_manager.h"
#include "input_manager.h"
#include "application.h"


namespace ugly
{
    class engine
    {
        public:

            engine(const engine&) = delete;
            engine& operator=(const engine&) = delete;

            /**
             * @brief Get the instance of the engine.
             */
            static engine* get_instance()
            {
                if(!_instance)
                    _instance = new engine();
                return _instance;
            }

            /**
             * @brief Run the engine.
             * 
             * @param application   Application to run
             */
            void run(application* application);

            /**
             * @brief Quit the engine.
             */
            void quit();

            /**
             * @brief Get GLFW window
             * 
             * @return GLFW window 
             */
            GLFWwindow* get_window() const;

            /**
             * @brief Get window width
             * 
             * @return window's width 
             */
            int get_window_width() const;

            /**
             * @brief Get window height
             * 
             * @return window's height 
             */
            int get_window_height() const;

            /**
             * @brief Get display manager.
             * 
             * @return Display manager
            */
            display_manager* get_display_manager() const;

            /**
             * @brief Get input manager.
             * 
             * @return Input manager
            */
            input_manager* get_input_manager() const;

        private:

            /**
             * @brief Constructor.
             */
            engine();

            /**
             * @brief Destructor.
             */
            virtual ~engine();

            /**
             * @brief Initialize plog.
             */
            void initialize_plog();

            /**
             * @brief Initialize engine.
             */
            void initialize();

            /**
             * @brief Shutdown engine.
             */
            void shutdown();

            /**
             * @brief Main loop.
             */
            void mainLoop();

        private:

            /*! Singleton instance */
            inline static engine* _instance {nullptr};

            /*! Quit flag */
            bool _quit {false};

            /*! Window width */
            int _window_width {1280};

            /*! Window width */
            int _window_height {720};

            /*! GFLW window */
            GLFWwindow* _window {nullptr};

            /*! Display manager */
            std::unique_ptr<ugly::display_manager> _display_manager {nullptr};

            /*! Input manager */
            std::unique_ptr<ugly::input_manager> _input_manager {nullptr};

            /*! Application */
            std::unique_ptr<ugly::application> _application {nullptr};
    };
}