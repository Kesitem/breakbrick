#include "application.h"
#include "engine.h"


ugly::application::application()
{
}


ugly::application::~application()
{
}


void ugly::application::intialize()
{
    PLOG_INFO << "Initialize application";

    auto engine = ugly::engine::get_instance();

    glViewport(0, 0, engine->get_window_width(), engine->get_window_height());

    engine->get_input_manager()->create_button("quit");
    engine->get_input_manager()->bind_key_to_button(GLFW_KEY_ESCAPE, "quit");
}



void ugly::application::shutdown()
{
    PLOG_INFO << "Shutdown application";
}


void ugly::application::update()
{
    auto engine = ugly::engine::get_instance();

    if(engine->get_input_manager()->get_button_action("quit") == ugly::input_action::released)
        engine->quit();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}