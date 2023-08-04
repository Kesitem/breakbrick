#pragma once

#include "core.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

namespace ugly
{
    class vertex_arrays
    {
    public:

        /**
         * @brief Constructor.
         */
        vertex_arrays();

        /**
         * @brief Destructor. 
         */
        virtual ~vertex_arrays();

        /**
         * @brief Add a vertex buffer.
         * 
         * @param vertex_buffer Vertex buffer
         */
        void add_vertex_buffer(const std::shared_ptr<vertex_buffer>& vertex_buffer);

        /**
         * @brief Set index buffer.
         *
         * @param index_buffer Index buffer
         */
        void set_index_buffer(const std::shared_ptr<index_buffer>& index_buffer);

        /**
         * @brief Get index buffer.
         * 
         * @return Index buffer
         */
        std::shared_ptr<index_buffer> get_index_buffer() const;

        /**
         * @brief Bind the vertex arrays.
         */
        void bind();

        /**
         * @brief Unbind the vertex arrays.
         */
        void unbind();

    private:

        /*! Vertex arrays id */
        uint32_t _id{0};

        /*! Number of vertex attrib */
        uint32_t _vertex_attrib_index{ 0 };

        /*! Vertex buffers */
        std::vector < std::shared_ptr<vertex_buffer> > _vertex_buffers;

        /*! Index buffer */
        std::shared_ptr<index_buffer> _index_buffer;
    };

}//namespace ugly