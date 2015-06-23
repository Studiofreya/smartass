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
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

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
 			"PING",									// Command
 			"PING :server",							// Command + trail
			"PING param1 :server",					// Command + param + trail
			":origin PING",							// Prefix + command
			":origin PING :server",					// Prefix + command + trail
			":origin PING param1 param2",			// Prefix + command + params
			":origin PING param1 param2 :server",	// Prefix + command + params + trail

			// Broken msgs
			":",
			": PING"
			//":server 001 beta2 :Hi, welcome to IRC",
			//":server 002 beta2 :Your host is server, running version miniircd-0.4",
			//":server 003 beta2 :This server was created sometime",
			//":server 004 beta2 :server miniircd-0.4 o o",
			//":server 251 beta2 :There are 2 users and 0 services on 1 server",
			//":server 422 beta2 :MOTD File is missing",
			//":beta2!beta2@10.0.0.34 JOIN #chan",
			//":server 331 beta2 #chan :No topic is set",
			//":server 353 beta2 = #chan :beta2 nd",
			//":server 366 beta2 #chan :End of NAMES list",
			//":beta2!beta2@10.0.0.34 JOIN #chan2",
			//":server 331 beta2 #chan2 :No topic is set",
			//":server 353 beta2 = #chan2 :beta2",
			//":server 366 beta2 #chan2 :End of NAMES list"
		};

		std::vector<IrcMessage> results =
		{
 			IrcMessage("PING"),
 			IrcMessage("PING","", {}, "server"),
			IrcMessage("PING", "", {"param1"}, "server"),
			IrcMessage("PING", "origin"),
			IrcMessage("PING", "origin", {}, "server"),
			IrcMessage("PING", "origin", {"param1","param2"}, ""),
			IrcMessage("PING", "origin", {"param1","param2"}, "server"),
			IrcMessage(),
			IrcMessage()
		};

		size_t i=0;

		for (const auto & msg : tests)
		{
			IrcMessage ircmsg = parseLine(msg);

			const IrcMessage & res = results[i++];

			if (ircmsg != res)
			{
				int baba=0;
				IrcMessage secondtest = parseLine(msg);
			}
			else
			{
				int bobo=0;
			}

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


		// Parameters... ?
		auto firstSpace = message.find(" ");
		bool haveFirstSpace = firstSpace != message.npos;

		// Parameters are between command and trail
		auto trailDivider = message.find(" :");
		bool haveTrailDivider = trailDivider != message.npos;

		// Assemble outputs
		std::vector<std::string> parts;
		std::string prefix;
		std::string command;
		ParamType parameters;
		std::string trail;

		// With or without trail
		if (haveTrailDivider)
		{
			// Have trail, split by trail
			boost::split(parts, message.substr(0, trailDivider), boost::is_any_of(" "));
			trail = message.substr(trailDivider+2);
		}
		else
		{
			// No trail, everything are parameters
			boost::split(parts, message, boost::is_any_of(" "));
		}

		enum class DecoderState
		{
			PREFIX,
			COMMAND,
			PARAMETER
		} state;

		bool first = true;
		state = DecoderState::PREFIX;

		for (const std::string & part : parts)
		{
			//if (first)


			switch (state)
			{
				// Prefix, or command... have to be decided
				case DecoderState::PREFIX:
				case DecoderState::COMMAND:
				{
					// Prefix, aka origin of message
					bool havePrefix = part[0] == ':';

					if (havePrefix && first)
					{
						// Oh the sanity
						if (part.size() < 2)
						{
							return IrcMessage();
						}

						// Have prefix
						state = DecoderState::COMMAND;
						prefix = part.substr(1);
						first = false;
					}
					else
					{
						// Have command
						state = DecoderState::PARAMETER;
						command = part;
					}

					break;
				}
				case DecoderState::PARAMETER:
				{
					parameters.push_back(part);
					break;
				}
			}

		}


		// Construct an IrcMessage
		IrcMessage ircmsg(command, prefix, std::move(parameters), trail);
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


