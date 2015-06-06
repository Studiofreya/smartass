//==============================================================================
//
//	IrcParser.hpp:
//	
//
//		Just another IRC parser
//
//==============================================================================

#if !defined(SMARTASS_IRCPARSER_HPP_INCLUDED)
#	 define	 SMARTASS_IRCPARSER_HPP_INCLUDED


//	System dependencies ...
#include <string>
#include <functional>
#include <vector>
#include <map>

//	Boost dependencies ...

//	Project dependencies ...
#include "IrcMessage.hpp"


namespace smartass
{

	class IrcParser
	{
		public:
			typedef std::map<std::string, IrcMessageCommand>	CommandDispatcher;

		public:
			explicit IrcParser();
			virtual ~IrcParser();

		public:
			// Parse a string to an IrcMessage
			void parseLine(const std::string & message);

			// Construct a string from an IrcMessage
			std::string parseMessage(const IrcMessage & message);

			// All commands
			void addIrcReadHandler(const IrcMessageHandle & handle);

			// Specific commands
			void addIrcCommandHandler(const std::string & cmd, const IrcMessageHandle & handle);

		private:
			void doCommandDispatch(const IrcMessage & msg);

		private:

			IrcMessageCommand	m_Handles;
			CommandDispatcher	m_CommandHandlers;
			

	};

}

#endif	// SMARTASS_IRC_HPP_INCLUDED

