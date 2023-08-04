#pragma once

#include "core.h"

namespace ugly
{
    class shader;

    /**
     * @brief OpenGL program.
     */
    class program
    {
    public:

        /**
         * @brief Constructor from Shader objects.
         * 
         * @param vertex_shader    Vertex shader 
         * @param fragment_shader  Program shader
         */
        program(const shader& vertex_shader, const shader& fragment_shader);

        /**
         * @brief Constructor from shader source code.
         *
         * @param vertex_shader_source    Vertex shader code
         * @param fragment_shader_source  Program shader code
         */
        program(const char* vertex_shader_source, const char* fragment_shader_source);

        /**
         * @brief Constructor from path to shader files.
         *
         * @param vertex_shader_path    Vertex shader path
         * @param fragment_shader_path  Program shader path
         */
        program(const std::filesystem::path& vertex_sharder_path, const std::filesystem::path& fragment_shader_path);

        /**
         * @brief Destructor.
         */
        virtual ~program();

        /**
         * @brief Use shader program.
         */
        void use();

        /**
         * @brief Set the Uniform float value
         * 
         * @param name     Uniform name
         * @param value    Value
         */
        void set_uniform(const std::string &name, float value);

        /**
         * @brief Set the Uniform vec4 value
         * 
         * @param name     Uniform name
         * @param value    Value
         */
        void set_uniform(const std::string &name, const glm::vec4 &value);

        /**
         * @brief Set the Uniform mat4 value
         *
         * @param name     Uniform name
         * @param value    Value
         */
        void set_uniform(const std::string& name, const glm::mat4& value);

        /**
         * @brief Set the Uniform unsigned int value
         *
         * @param name     Uniform name
         * @param value    Value
         */
        void set_uniform(const std::string& name, const uint32_t& value);

        /**
         * @brief Set the Uniform unsigned int value
         *
         * @param name     Uniform name
         * @param value    Value
         */
        void set_uniform(const std::string& name, const int32_t& value);

    private:

        /**
         * @brief Get the uniform location.
         * 
         * @param name     Location name
         * @return GLint    Location
         */
        GLint get_uniform_location(const std::string &name);
        
    private: 

        /*! Program id */
        GLuint _id{0};

        /*! Uniforms location */
        std::map<std::string, GLint> _uniforms_location;
    };
}