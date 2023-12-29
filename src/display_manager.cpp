#include "display_manager.h"


/**
 * @brief OpenGL message callback.
 */
void GLAPIENTRY opengl_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* user_param)
{
    static std::string source_desc;
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        source_desc = "OpenGL API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        source_desc = "Window - system API";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        source_desc = "Shading language compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        source_desc = "Third party application";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        source_desc = "Source application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        source_desc = "Other";
        break;
    }

    static std::string type_desc;
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        type_desc = "Error API";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        type_desc = "deprecated behavior"; 
        break; 
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        type_desc = "Undefined behavior";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        type_desc = "Functionality not portable";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        type_desc = "Performance issues";
        break;
    case GL_DEBUG_TYPE_MARKER:
        type_desc = "Command stream annotation";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        type_desc = "Group pushing";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        type_desc = "Group popping";
        break;
    case GL_DEBUG_TYPE_OTHER:
        type_desc = "Other";
        break;
    }

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        LOG_ERROR << "Source: " << source_desc << " - Type: " << type_desc << " - Message: " << message;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        LOG_WARNING << "Source: " << source_desc << " - Type: " << type_desc << " - Message: " << message;
        break;
    case GL_DEBUG_SEVERITY_LOW:
        LOG_INFO << "Source: " << source_desc << " - Type: " << type_desc << " - Message: " << message;
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        LOG_DEBUG << "Source: " << source_desc << " - Type: " << type_desc << " - Message: " << message;
        break;
    }
}


ugly::display_manager::display_manager()
{
    PLOG_INFO << "Initialize display manager";

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PLOG_ERROR << "Failed to initialize GLAD";
        throw new std::runtime_error("Failed to initialize GLAD");
    }

    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(opengl_message_callback, 0);

    // Display OpenGL infos
    PLOG_INFO << "OpenGL Vendor: " << glGetString(GL_VENDOR);
    PLOG_INFO << "OpenGL Renderer: " << glGetString(GL_RENDERER);
    PLOG_INFO << "OpenGL Version: " << glGetString(GL_VERSION);
    PLOG_INFO << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
}


ugly::display_manager::~display_manager()
{
    PLOG_INFO << "Shutdown display manager";
}


void ugly::display_manager::set_viewport(int x, int y, unsigned int width, unsigned int height)
{
    // Set default viewport
    glViewport(x, y, width, height);
}


void ugly::display_manager::set_clear_color(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}


void ugly::display_manager::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}


void ugly::display_manager::set_polygon_mode(polygon_mode mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
}


void ugly::display_manager::draw_arrays(int32_t first, uint32_t count)
{
    glDrawArrays(GL_TRIANGLES, first, count);
}


void ugly::display_manager::draw_elements(uint32_t count)
{
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}