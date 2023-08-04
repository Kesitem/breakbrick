#pragma once

#include "core.h"

namespace ugly
{
    enum class buffer_data_type
    {
        FLOAT2,
        FLOAT3
    };

    static uint32_t get_buffer_data_type_size(buffer_data_type type)
    {
        switch (type)
        {
        case buffer_data_type::FLOAT2:   return 4 * 2;
        case buffer_data_type::FLOAT3:   return 4 * 3;
        }

        return 0;
    }

    static uint32_t get_buffer_data_type_component_count(buffer_data_type type)
    {
        switch (type)
        {
        case buffer_data_type::FLOAT2:   return 2;
        case buffer_data_type::FLOAT3:   return 3;

        }

        return 0;
    }
    
    static uint32_t get_buffer_data_type_component_opengl_type(buffer_data_type type)
    {
        switch (type)
        {
        case buffer_data_type::FLOAT2:    return GL_FLOAT;
        case buffer_data_type::FLOAT3:    return GL_FLOAT;
        }

        return 0;
    }

    struct buffer_element
    {
        std::string name;
        buffer_data_type type;
        uint32_t size;
        size_t offset;
        bool normalized;

        buffer_element() = default;

        buffer_element(std::string name, buffer_data_type type, bool normalized) : name(name), type(type), size(get_buffer_data_type_size(type)), offset(0), normalized(normalized)
        {
        }
    };

    class buffer_layout
    {
    public:

        /**
         * @brief Default constructor.
         */
        buffer_layout() {}
        
        /**
         * @brief Constructor with initializer list.
         * 
         * @param   elements    Initializer list of elements
         */
        buffer_layout(std::initializer_list<buffer_element> elements);

        /**
         * @brief Get buffer stride.
         *
         * @return Layout stride
         */
        uint32_t get_stride() const;

        /**
         * @brief Get elements.
         *
         * @return Elements
         */
        const std::vector<buffer_element>& get_elements() const;

    private:

        void calculate_offsets_and_stride();

    private:

        /*! Elements */
        std::vector<buffer_element> _elements;

        /*! Stride */
        uint32_t _stride = 0;
    };


    /**
     * @brief Vertex buffer. 
     */
    class vertex_buffer
    {
    public:

        /**
         * @brief Constructor.
         * 
         * * @param size     Size in bytes
         */
        vertex_buffer(size_t size);

        /**
         * @brief Constructor with initialization.
         * 
         * @param size     Size in bytes
         * @param data     Data or nullptr
         */
        vertex_buffer(size_t size, const void* data);

        /**
         * @brief Destructor.
         */
        virtual ~vertex_buffer();

        /**
         * @brief Set Data of the buffer.
         *  
         * @param size     Size in bytes
         * @param data     Data or nullptr
         */
        void set_data(size_t size, const void * data);

        /**
         * @brief Set buffer layout.
         *
         * @param   layout Buffer layout
         */
        void set_layout(const buffer_layout& _layout);

        /**
         * @brief Get buffer layout.
         *
         * @return Buffer layout
         */
        buffer_layout get_layout() const;
        
        /**
         * @brief Bind the vertex buffer.
         */
        void bind();

        /**
         * @brief Unbind the vertex buffer.
         */
        void unbind();

    private:

        /** Object id */
        uint32_t _id;

        /** Layout */
        buffer_layout _layout;
    };
}