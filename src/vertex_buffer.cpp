#include "vertex_buffer.h"


ugly::buffer_layout::buffer_layout(std::initializer_list<buffer_element> elements)
    : _elements(elements)
{
    calculate_offsets_and_stride();
}


void ugly::buffer_layout::calculate_offsets_and_stride()
{
    size_t offset = 0;
    _stride = 0;
    for (auto& element : _elements)
    {
        element.offset = offset;
        offset += element.size;
        _stride += element.size;
    }
}


uint32_t ugly::buffer_layout::get_stride() const 
{ 
    return _stride; 
}


const std::vector<ugly::buffer_element>& ugly::buffer_layout::get_elements() const 
{ 
    return _elements; 
}


ugly::vertex_buffer::vertex_buffer(size_t size)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
}


ugly::vertex_buffer::vertex_buffer(size_t size, const void * data)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


ugly::vertex_buffer::~vertex_buffer()
{
    if (_id != 0)
    {
        glDeleteBuffers(1, &_id);
        _id = 0;
    }
}


void ugly::vertex_buffer::set_data(size_t size, const void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


void ugly::vertex_buffer::set_layout(const buffer_layout& layout) 
{ 
    _layout = layout; 
}


ugly::buffer_layout ugly::vertex_buffer::get_layout() const 
{ 
    return _layout; 
}


void ugly::vertex_buffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}


void ugly::vertex_buffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}