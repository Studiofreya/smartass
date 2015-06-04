//==============================================================================
//
//	IRC.cpp:
//	
//
//		
//		
//
//==============================================================================

#include "IRC.hpp"

//	System dependencies ...

//	Boost dependencies ...

//	Project dependencies ...
#include "Logger.hpp"

namespace smartass
{


	IRC::IRC()
	{

	}

	IRC::~IRC()
	{

	}

	void IRC::parseLine(const std::string & message)
	{
		// https://tools.ietf.org/html/rfc1459
		// https://tools.ietf.org/html/rfc2812
		// <message>  ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
		// <prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
		// <command>  ::= <letter> { <letter> } | <number> <number> <number>
		// <SPACE>    ::= ' ' { ' ' }
		// <params>   ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
		// 
		// <middle>   ::= <Any *non-empty* sequence of octets not including SPACE
		//                or NUL or CR or LF, the first of which may not be ':'>
		// <trailing> ::= <Any, possibly *empty*, sequence of octets not including
		//                  NUL or CR or LF>
		// 
		// <crlf>     ::= CR LF

		// Extract with positions
		size_t pos = 0;
		size_t len = 0;

		// Prefix, aka origin of message
		bool havePrefix = message[0] == ':';

		auto firstSpace = message.find(" ");
		bool haveFirstSpace = firstSpace != message.npos;


		std::string prefix;
		std::string command;

		// Get prefix, if present
		if (havePrefix)
		{
			// Should have space if we have a prefix
			if (!haveFirstSpace)
			{
				logLine("ERROR", "Something wrong: " + message);
				return;
			}

			pos = 1;
			len = firstSpace - pos;

			// Get prefix
			prefix = message.substr(pos, len);

			// Get command
			pos = firstSpace + 1;
			len = message.find(" ", firstSpace + 1) - pos;
			command = message.substr(pos, len);

			// Advance position
			pos = pos + len + 1;
		}
		else
		{
			// We starts with command
			if (haveFirstSpace)
			{
				// Command, with parameters
				command = message.substr(firstSpace);
			}
			else
			{
				// No parameters, only command
				command = message;
			}
		}

		// Parameters are between command and trail
		auto trailDivider = message.find(" :");
		bool haveTrailDivider = trailDivider != message.npos;

		// Get command parameters
		std::string parameters;

		if (haveTrailDivider)
		{
			// We have trail
			len = trailDivider - pos;
			parameters = message.substr(pos, len);
		}
		else
		{
			// Rest is parameters (no trail)
			parameters = message.substr(pos);
		}

		// Trail is the remaining line
		pos = trailDivider + 2;
		std::string trail = message.substr(pos);


		int baba = 0;
	}

}


