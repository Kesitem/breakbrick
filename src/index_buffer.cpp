#include "index_buffer.h"

ugly::index_buffer::index_buffer(uint32_t count, uint32_t* indices) : _count(count)
{
	glCreateBuffers(1, &_id);

	// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
	// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
	glBindBuffer(GL_ARRAY_BUFFER, _id);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}


ugly::index_buffer::~index_buffer()
{
	glDeleteBuffers(1, &_id);
}


void ugly::index_buffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}


void ugly::index_buffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t ugly::index_buffer::get_count() const
{
	return _count;
}
