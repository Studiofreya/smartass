//==============================================================================
//
//	IRC.cpp:
//	
//
//		
//		
//
//==============================================================================

#include "IrcParser.hpp"

//	System dependencies ...
#include <iostream>
#include <functional>

//	Boost dependencies ...

//	Project dependencies ...
#include "Logger.hpp"

namespace smartass
{


	IrcParser::IrcParser()
		: m_Handles()
		, m_CommandHandlers()
	{
		// Run selftests
		selftest();

		using std::placeholders::_1;

		addIrcReadHandler(std::bind(&IrcParser::doCommandDispatch, this, _1));
	}

	IrcParser::~IrcParser()
	{
	}

	bool IrcParser::selftest()
	{
		//////////////////////////////////////////////////////////////////////////
		// 
		//  OK
		//
		//////////////////////////////////////////////////////////////////////////

		std::vector<std::string> tests = 
		{
			"PING :server",
			":server 001 beta2 :Hi, welcome to IRC",
			":server 002 beta2 :Your host is server, running version miniircd-0.4",
			":server 003 beta2 :This server was created sometime",
			":server 004 beta2 :server miniircd-0.4 o o",
			":server 251 beta2 :There are 2 users and 0 services on 1 server",
			":server 422 beta2 :MOTD File is missing",
			":beta2!beta2@10.0.0.34 JOIN #chan",
			":server 331 beta2 #chan :No topic is set",
			":server 353 beta2 = #chan :beta2 nd",
			":server 366 beta2 #chan :End of NAMES list",
			":beta2!beta2@10.0.0.34 JOIN #chan2",
			":server 331 beta2 #chan2 :No topic is set",
			":server 353 beta2 = #chan2 :beta2",
			":server 366 beta2 #chan2 :End of NAMES list"
		};

		for (const auto & msg : tests)
		{
			IrcMessage ircmsg = parseLine(msg);

			int baba=0;
		}


		return true;
	}

	IrcMessage IrcParser::parseLine(const std::string & message)
	{
		if (message.empty())
		{
			// Garbage in, garbage out
			return IrcMessage();
		}

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

		// Parameters... ?
		auto firstSpace = message.find(" ");
		bool haveFirstSpace = firstSpace != message.npos;

		// Parameters are between command and trail
		auto trailDivider = message.find(" :");
		bool haveTrailDivider = trailDivider != message.npos;

		std::string prefix;
		std::string command;

		// Get prefix, if present
		if (havePrefix)
		{
			// Should have space if we have a prefix
			if (!haveFirstSpace)
			{
				logLine("ERROR", "Something wrong: " + message);
				return IrcMessage();
			}

			pos = 1;
			len = firstSpace - pos;

			// Get prefix
			prefix = message.substr(pos, len);

			// Get command
			pos = firstSpace + 1;
			len = message.find(" ", firstSpace + 1) - pos;
			command = message.substr(pos, len);

			// Advance position to parameters or trail
			pos = pos + len + 1;
		}
		else
		{
			// Get command
			// We starts with command
			if (haveFirstSpace)
			{
				// Command, with possible parameters and/or trail
				command = message.substr(firstSpace);
				pos = firstSpace;

				// Check if we have parameters and trail
				if (haveTrailDivider)
				{
					size_t paramLength = trailDivider - firstSpace;

					if (paramLength == 0)
					{
						// No parameters
					}
					else
					{
						// Parameters
					}
				}
				else
				{
					// Rest is parameters
					parameters = message.substr(pos+1);
				}
			}
			else
			{
				// No parameters, only command
				command = message;
			}



		}


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

		// Construct an IrcMessage
		IrcMessage ircmsg(command, prefix, parameters, trail);
		m_Handles(ircmsg);

		return ircmsg;
	}


	std::string IrcParser::parseMessage(const IrcMessage & message)
	{
		int baba=0;

		return "<<< NOT IMPLEMENTED >>>";
	}



	void IrcParser::addIrcReadHandler(const IrcMessageHandle & handle)
	{
		m_Handles.addHandle(handle);
	}


	void IrcParser::addIrcCommandHandler(const std::string & cmd, const IrcMessageHandle & handler)
	{
		m_CommandHandlers[cmd].addHandle(handler);
	}

	void IrcParser::doCommandDispatch(const IrcMessage & msg) const
	{
		const auto & it = m_CommandHandlers.find(msg.command());

		if (it != m_CommandHandlers.end())
		{
			const auto & handles = it->second;

			// Call each handler
			handles(msg);
		}
	}
}


