#include "vertex_arrays.h"


ugly::vertex_arrays::vertex_arrays()
{
    glGenVertexArrays(1, &_id);
    bind();
}


ugly::vertex_arrays::~vertex_arrays()
{
    if (_id != 0)
    {
        glDeleteVertexArrays(1, &_id);
        _id = 0;
    }
}


void ugly::vertex_arrays::add_vertex_buffer(const std::shared_ptr<vertex_buffer>& vertex_buffer)
{
    bind();
    vertex_buffer->bind();

    const auto& layout = vertex_buffer->get_layout();
    for (const auto& element : layout.get_elements())
    {
        switch (element.type)
        {
        case buffer_data_type::FLOAT2:
        case buffer_data_type::FLOAT3:
            glEnableVertexAttribArray(_vertex_attrib_index);
            glVertexAttribPointer(_vertex_attrib_index,
                ugly::get_buffer_data_type_component_count(element.type),
                ugly::get_buffer_data_type_component_opengl_type(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.get_stride(),
                (const void*)element.offset);
            _vertex_attrib_index++;
            break;
        }
    }

    _vertex_buffers.push_back(vertex_buffer);
}


void ugly::vertex_arrays::set_index_buffer(const std::shared_ptr<index_buffer>& index_buffer)
{

    bind();
    index_buffer->bind();

    _index_buffer = index_buffer;
}


std::shared_ptr<ugly::index_buffer> ugly::vertex_arrays::get_index_buffer() const
{
    return _index_buffer;
}


void ugly::vertex_arrays::bind()
{
    glBindVertexArray(_id);
}


void ugly::vertex_arrays::unbind()
{
    glBindVertexArray(0);
}