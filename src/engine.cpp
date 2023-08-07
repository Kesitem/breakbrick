#include "engine.h"
#include "log_formatter.h"
#include "config.h"


ugly::engine::engine()
{
    initialize_plog();

    auto path = std::filesystem::current_path();
    LOG_INFO << "Current path: " << path.c_str();
}


ugly::engine::~engine()
{
}


void ugly::engine::run(application* application)
{
    if(application == nullptr)
    {
        LOG_ERROR << "Invalid application";
        return;
    }
    _application.reset(application);

    try
    {
        initialize();
    }
    catch(const std::runtime_error& e)
    {
        LOG_ERROR << e.what();
        shutdown();
        return;
    }
    
    try
    {
        mainLoop();
    }
    catch(const std::runtime_error& e)
    {
        LOG_ERROR << e.what();
    }
    
    shutdown();
}


void ugly::engine::quit()
{
    _quit = true;
}


GLFWwindow* ugly::engine::get_window() const
{
    return _window;
}


int ugly::engine::get_window_width() const
{
    return _window_width;
}


int ugly::engine::get_window_height() const
{
    return _window_height;
}


ugly::display_manager* ugly::engine::get_display_manager() const
{
    return _display_manager.get();
}

ugly::input_manager* ugly::engine::get_input_manager() const
{
    return _input_manager.get();
}


void ugly::engine::initialize_plog()
{
    // Remove log file if exists
    struct stat buffer;
    if (stat(LOG_FILENAME.c_str(), &buffer) == 0)
    {
        if (remove(LOG_FILENAME.c_str()) != 0)
        {
            LOG_ERROR << "Cannnot remove log file";
        }
    }

    // Create log
    static plog::RollingFileAppender<plog::log_formatter> file_appender(LOG_FILENAME.c_str(), 0, 0);
    static plog::ConsoleAppender<plog::log_formatter> console_appender;

    plog::init(plog::debug, &console_appender).addAppender(&file_appender);
}



void ugly::engine::initialize()
{
    LOG_INFO << "Initialize engine";

    if (!glfwInit())
    {
        LOG_ERROR << "Failed to init GLFW";
        throw std::runtime_error("Failed to init GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    LOG_INFO << "Window size: " << _window_width << "x" << _window_height;
    _window = glfwCreateWindow(_window_width, _window_height, ugly::project::NAME.c_str(), NULL, NULL);
    if (!_window)
    {
        LOG_ERROR << "Failed to create GLFW window";
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(_window);

    _display_manager.reset(new display_manager()); 

    _input_manager.reset(new input_manager());

    _application->intialize();
}



void ugly::engine::shutdown()
{
    LOG_INFO << "Shutdown engine";

    if(_application.get() != nullptr)
    {
        _application->shutdown();
        _application.reset();
    }

    if(_input_manager.get() != nullptr)
        _input_manager.reset(nullptr);

    if(_display_manager.get() != nullptr)
        _input_manager.reset(nullptr);

    glfwTerminate();
}


void ugly::engine::mainLoop()
{
    LOG_INFO << "Enter main loop";

    while (!_quit)
    {
        if(glfwWindowShouldClose(_window))
            _quit = true;

        _application->update();
        _input_manager->update();

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}