#include "program.h"
#include "shader.h"


ugly::program::program(const ugly::shader& vertex_shader, const ugly::shader& fragment_shader)
{
    _id = glCreateProgram();
    glAttachShader(_id, vertex_shader.getId());
    glAttachShader(_id, fragment_shader.getId());
    glLinkProgram(_id);
    glValidateProgram(_id);

    int  success;
    char info_log[512];
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_id, 512, NULL, info_log);
        PLOG_ERROR << "program link failed: " << info_log;
        throw new std::runtime_error("Failed to link program");
    }
}


ugly::program::program(const char* vertex_shader_source, const char* fragment_shader_source): program(
    shader(shader_type::VERTEX, vertex_shader_source), ugly::shader(shader_type::FRAGMENT, fragment_shader_source))
{
}


ugly::program::program(const std::filesystem::path& vertex_sharder_path,
    const std::filesystem::path& fragment_shader_path) : program(
        shader(shader_type::VERTEX, vertex_sharder_path), shader(shader_type::FRAGMENT, fragment_shader_path))
{
}


ugly::program::~program()
{
    if (_id != 0)
    {
        glDeleteProgram(_id);
        _id = 0;
    }
}


void ugly::program::use()
{
    glUseProgram(_id);
}


void ugly::program::set_uniform(const std::string &name, float value)
{
    glUniform1f(get_uniform_location(name), value); 
}


void ugly::program::set_uniform(const std::string &name, const glm::vec4 &value)
{
    glUniform4f(get_uniform_location(name),
                value.x,
                value.y,
                value.z,
                value.w);
}


void ugly::program::set_uniform(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(value));
}


void ugly::program::set_uniform(const std::string& name, const uint32_t& value)
{
    glUniform1ui(get_uniform_location(name), value);
}


void ugly::program::set_uniform(const std::string& name, const int32_t& value)
{
    glUniform1i(get_uniform_location(name), value);
}


GLint ugly::program::get_uniform_location(const std::string &name)
{
    GLint location;
    auto it = _uniforms_location.find(name);
    if(it == _uniforms_location.end())
    {
        location = glGetUniformLocation(_id, name.c_str());
        _uniforms_location.insert(std::make_pair(name, location));
    }
    else
    {
        location = it->second;
    }

    return location;
}