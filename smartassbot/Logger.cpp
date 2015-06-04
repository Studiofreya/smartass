//==============================================================================
//
//	Logger.cpp:
//	
//
//		
//		
//
//==============================================================================

#include "Logger.hpp"

//	System dependencies ...
#include <iostream>

//	Boost dependencies ...
#include <boost/date_time.hpp>

//	Project dependencies ...


namespace smartass
{
	void logLine(const std::string& type, const std::string& message)
	{
		//
		auto now		= boost::posix_time::second_clock::local_time();
		auto nowstring	= boost::posix_time::to_simple_string(now);

		std::cout << nowstring << " [" << type << "]:>>>" << message << "<<<" << std::endl;
	}
}

