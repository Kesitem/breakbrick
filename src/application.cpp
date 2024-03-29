#include "application.h"
#include "engine.h"
#include "vertex_buffer.h"

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

    engine->get_input_manager()->create_button("quit");
    engine->get_input_manager()->bind_key_to_button(GLFW_KEY_ESCAPE, "quit");

    /** Vertex shader source **/
    char* vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    /** Fragment shader source **/
    char* fragment_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    // Create program
    _program = std::make_unique<ugly::program>(vertex_shader_source, fragment_shader_source);

    // Create vertex buffer
    auto vb = std::make_shared<vertex_buffer>(sizeof(vertices), vertices);
    vb->set_layout(
        ugly::buffer_layout({
            ugly::buffer_element("a_vertex", ugly::buffer_data_type::FLOAT3, false) }));

    _vertex_array = std::make_unique<ugly::vertex_arrays>();
    _vertex_array->add_vertex_buffer(vb);
    
    engine->get_display_manager()->set_viewport(0, 0, engine->get_window_width(), engine->get_window_height());
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

    engine->get_display_manager()->set_clear_color(0.2f, 0.3f, 0.3f, 1.0f);
    engine->get_display_manager()->clear();

    _program->use();
    _vertex_array->bind();
    engine->get_display_manager()->draw_arrays(0, 3);
    _vertex_array->unbind();
}