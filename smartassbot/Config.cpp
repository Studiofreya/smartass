//==============================================================================
//
//	Config.cpp:
//	
//
//		
//		
//
//==============================================================================

#include "Config.hpp"

//	System dependencies ...
#include <fstream>

//	Boost dependencies ...
#include <boost/algorithm/string.hpp>

//	Project dependencies ...


namespace smartass
{

	Config::Config(const std::string & filename)
	{
		std::ifstream file(filename);
		std::string line;

		while (getline(file, line))
		{
			if (line[0] != '#')
			{
				size_t found = line.find(" ");

				if (found != std::string::npos)
				{
					// Divide and conquer
					std::string key = line.substr(0, found);
					std::string val = line.substr(found + 1);

					// Trim excess fat
					boost::trim(key);
					boost::trim(val);

					// Don't add to skinny keys and values
					if (!key.empty() && !val.empty())
					{
						m_Config[key] = val;
					}

				}

			}

		}

	}

	Config::~Config()
	{

	}

	std::string Config::server() const
	{
		return getIfExists("IRC_SERVER");
	}

	std::string Config::port() const
	{
		return getIfExists("IRC_SERVER_PORT");
	}

	std::string Config::nick() const
	{
		return getIfExists("NICK");
	}

	std::string Config::channels() const
	{
		return getIfExists("CHANNELS");
	}

	std::string Config::getIfExists(const std::string & key) const
	{
		const auto it = m_Config.find(key);

		if (it != m_Config.end())
		{
			return (*it).second;
		}

		return std::string();
	}

}


