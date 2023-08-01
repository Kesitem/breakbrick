#pragma once

#include "core.h"

namespace plog
{

	/**
	 * \brief Custom formatter for plog.
	 */
	class log_formatter
	{
	public:

		/**
		 * \brief Header formatter.
		 */
		static util::nstring header();

		/**
		 * \brief Record formatter.
		 */
		static util::nstring format(const Record& record);
	};

}//namespace plog