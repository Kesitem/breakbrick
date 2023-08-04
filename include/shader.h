#pragma once

#include "core.h"

namespace ugly
{
    enum class shader_type
    {
        VERTEX = 35633,
        FRAGMENT = 35632
    };

    class shader
    {
    public:

        shader(const shader& shader) = delete;

        /**
         * @brief Constructor from shader source.
         * 
         * @param shader_type  Type of shader
         * @param source       Source
         */
        shader(shader_type shader_type, const char* source);

        /**
         * @brief Constructor from shader source file.
         *
         * @param shader_type  Type of shader
         * @param path         Source file path
         */
        shader(shader_type shader_type, const std::filesystem::path& path);

        /**
         * @brief Destructor.
         */
        virtual ~shader();

        /**
         * @brief Create a shader from file source.
         * 
         * @param shader_type Type of shader
         * @param path        Path to the source
         * @return false if error
         */
        bool createFromFile(shader_type shader_type, const char* path);

        /**
         * @brief Get the Id object.
         * 
         * @return Id
         */
        uint32_t getId() const;

    private:

        /**
         * @brief Create the shader from source.
         *
         * @param   shader_type    Type of shader
         * @param   source         Source of the shader
         */
        void create(shader_type shader_type, const char* source);

    private:

        /*! shader id */
        uint32_t _id{0};
    };
}