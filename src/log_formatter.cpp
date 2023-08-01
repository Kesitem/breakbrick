#include "log_formatter.h"
#include "config.h"

namespace plog
{

	/**
	 * \brief Header formatter.
	 */
	util::nstring log_formatter::header()
	{
		util::nostringstream ss;
		ss << "----- " << ugly::project::NAME.c_str() << " Log" << "\n";
		ss << "----- Version: " << ugly::version::FULLVERSION_STRING.c_str() << "\n";

		return ss.str();
	}


	/**
	 * \brief Record formatter.
	 */
	util::nstring log_formatter::format(const Record& record)
	{
		util::nostringstream ss;
		switch (record.getSeverity())
		{
		case Severity::none:
			ss << "NONE - ";
			break;
		case Severity::fatal:
			ss << "FATAL - ";
			break;
		case Severity::error:
			ss << "ERROR - ";
			break;
		case Severity::warning:
			ss << "WARNING - ";
			break;
		case Severity::info:
			ss << "INFO - ";
			break;
		case Severity::debug:
			ss << "DEBUG - ";
			break;
		case Severity::verbose:
			ss << "VERBOSE - ";
			break;
		}
		ss << record.getFunc() << " - ";
		ss << record.getMessage() << "\n"; // Produce a simple string with a log message.
		return ss.str();
	}

}//namespace plog