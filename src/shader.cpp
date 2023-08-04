#include "shader.h"

ugly::shader::shader(shader_type shader_type, const char* source)
{
    create(shader_type, source);
}


ugly::shader::shader(shader_type shader_type, const std::filesystem::path& path)
{
    // Open file
    std::ifstream ifs(path, std::ios::in);
    if (!ifs)
    {
        PLOG_ERROR << "Failed to open shader file: " << path.c_str();
        throw new std::runtime_error("Failed to open shader file");
    }

    // Read file buffer
    std::ostringstream sstr;
    sstr << ifs.rdbuf();

    // Close stream
    ifs.close();

    create(shader_type, sstr.str().c_str());
}


ugly::shader::~shader()
{
    if (_id != 0)
    {
        glDeleteShader(_id);
        _id = 0;
    }
}


uint32_t ugly::shader::getId() const
{
    return _id;
}


void ugly::shader::create(shader_type shader_type, const char* source)
{
    _id = glCreateShader((uint32_t)shader_type);
    glShaderSource(_id, 1, &source, NULL);
    glCompileShader(_id);

    int  success;
    char info_log[512];
    glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_id, 512, NULL, info_log);
        PLOG_ERROR << (shader_type == shader_type::VERTEX ? "Vertex" : "Fragment") << " shader compilation failed: " << info_log;
        PLOG_DEBUG << "shader source: " << source;
        glDeleteShader(_id);
        throw new std::runtime_error("Failed to create shader");
    }
}