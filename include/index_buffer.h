#pragma once

#include "core.h"

namespace ugly
{
	/**
	 * \brief Index buffer.
	 */
	class index_buffer
	{
	public:

		/**
		 * @brief Constructeur.
		 * 
		 * @param count	Number of indices
		 * @param data		Indices
		 */
		index_buffer(uint32_t count, uint32_t* data);

		/**
		 * @brief Destructor.
		 */
		virtual ~index_buffer();

		/**
		 * @brief Bind the buffer.
		 */
		void bind();

		/**
		 * @brief Unbind the buffer.
		 */
		void unbind();

		/**
		 * @brief Get number of indices.
		 *
		 * @return Number of indices
		 */
		uint32_t get_count() const;

	private:

		/*! Index buffer id */
		uint32_t _id;

		/*! Number of indices */
		uint32_t _count;
	};
}